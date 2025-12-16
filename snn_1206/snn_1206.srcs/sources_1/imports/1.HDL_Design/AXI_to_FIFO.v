/*-------------------------------------------------------------------------
--                                                                         
--   Copyright (c) Libertron Co., LTD. 2020                           
--   ALL RIGHTS RESERVED                                                   
--                                                                         
--   THIS PROGRAM IS THE PROPERTY OF Libertron Co., LTD. AND IS            
--   BEING PROVIDED TO YOU PURSUANT TO A LICENSE AGREEMENT THAT            
--   SETS FORTH CERTAIN TERMS AND CONDITIONS FOR USE OF THIS PROGRAM.      
--   YOU MAY NOT COPY, DISTRIBUTE, USE OR OTHERWISE CREATE DERIVATIVES     
--   OF THIS SOFTWARE EXCEPT AS PROVIDED IN THE LICENSE AGREEMENT.         
-- IP Name        : AXI_to_FIFO
-- IP Revision    :                                                         
-- File Name      : AXI_to_FIFO.v
-- File Revision  : 1.0                                                     
-- Date           : 2020/05/06
-- Tool Version   : Xilinx Vivado 2019.2                                    
-- Authors        : Libertron R&D Center, THYoon                            
-- IP Revision History                                                     
-- 2020/05/06     : start
-- 2020/05/06     : HDMI와 LCD를 동시에 출력하기 위하여 동작하도록 개발 방향 선회
-- 2020/05/24     : 오버레이 기능 추가
-- 2020/07/06     : AXI ARADDR 4KB boundary 문제 수정
-- 2020/07/09     : 파일 분할 및 기능 분할
-- 2020/09/24     : RLAST 지속에 따른 문제 해결
-------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////
//
//    본 IP는 buffer adderess / output size, sync signal 값을 받아 이에 맞게 데이터를 읽어와 외부 FIFO에 저장한다.
//    본 IP는 1개의 double frame buffer에서 odd_even_write의 선택에 따라 영상 데이터를 읽어 온다.
//
////////////////////////////////////////////////////////////////////////////////////////////////
`timescale 1ns/ 100ps

module AXI_to_FIFO
#(
   /***********************************************************************************************
   //    parameter for camera configuration
   ***********************************************************************************************/
   parameter IMG_HSIZE                             =  1920           ,
   parameter IMG_VSIZE                             =  1080           ,


   /***********************************************************************************************
   //    parameter for LCD configuration
   ***********************************************************************************************/
   parameter OUTPUT_IMG_HSIZE                      =  800            ,
   parameter OUTPUT_IMG_VSIZE                      =  480            ,


   /***********************************************************************************************
   //    parameter for LCD configuration
   //    If SYNC_FORCE_TO_CAM is enable, this module will select the double frame buffer based on odd_even_write signal.
   ***********************************************************************************************/
   parameter SYNC_FORCE_TO_CAM                     =  0              ,                


   /***********************************************************************************************
   //    parameter for AXI interface configuration
   ***********************************************************************************************/
   parameter M_AXI_ADDR_WIDTH	                     =  32             ,
   parameter M_AXI_DATA_WIDTH	                     =  32             ,
   parameter MAXIMUM_BURST_LEN                     =  16            

) // parameter list end
( // IO port list start
   /***********************************************************************************************
   //    I/O block for clock, reset
   ***********************************************************************************************/
   input    wire                                   m_axi_aclk        ,
   input    wire                                   m_axi_aresetn     ,


   /***********************************************************************************************
   //    I/O block for module control and configuration
   //    Note : The falling edge of module_enable generates reset signal of FIFO.
   //           So, you don't have to consider the behavior of subsequence modules(i.e : FIFO)
   ***********************************************************************************************/
   input    wire                                   odd_even_write                               ,
   input    wire     [M_AXI_ADDR_WIDTH - 1 : 0]    double_frame_buffer_odd_addr                 , 
   input    wire     [M_AXI_ADDR_WIDTH - 1 : 0]    double_frame_buffer_even_addr                , 
   input    wire     [31 : 0]                      output_left_top_coord_x                      ,
   input    wire     [31 : 0]                      output_left_top_coord_y                      ,
   input    wire                                   module_enable                                ,

   /***********************************************************************************************
   //    I/O block for AXI BUS
   ***********************************************************************************************/
   output   reg      [M_AXI_ADDR_WIDTH - 1 : 0]    m_axi_data_araddr                            ,
   output   wire     [1:0]                         m_axi_data_arburst                           ,
   output   wire     [3 : 0]                       m_axi_data_arcache                           ,
   output   wire     [5 : 0]                       m_axi_data_arid                              ,
   output   reg      [3:0]                         m_axi_data_arlen                             ,
   output   wire                                   m_axi_data_arlock                            ,
   output   wire     [2:0]                         m_axi_data_arprot                            ,
   output   wire     [3 : 0]                       m_axi_data_arqos                             ,
   input    wire                                   m_axi_data_arready                           ,
   output   wire     [2:0]                         m_axi_data_arsize                            ,
   output   reg                                    m_axi_data_arvalid                           ,
   input    wire      [5 : 0]                      m_axi_data_rid                               ,
   input    wire                                   m_axi_data_rlast                             ,
   output   wire                                   m_axi_data_rready                            ,
   input    wire     [M_AXI_DATA_WIDTH -1 :0]      m_axi_data_rdata                             ,
   input    wire                                   m_axi_data_rvalid                            ,
   output   wire      [1 : 0]                      m_axi_data_rresp                             ,


   /***********************************************************************************************
   //    I/O block for FIFO control
   //    module_rst_out  = falling edge of module enable
   //    Note : This module does not read memory if FIFO assert FIFO_prog_full.
   //    Note : We recommend that when you generate FIFO, threshold of FIFO_prog_full as big as possible to avoid pipe-line bubble.
   //    Note : Threshold of FIFO_prog_full is MUST smaller then (DEPTH_OF_FIFO_wr - (FIFO_WIDTH) / (WITHD_OF_AXI) * (MAXIMUM_BURST_SIZE) * 2))
   ***********************************************************************************************/
   output   wire     [31 : 0]                      FIFO_data                                    ,
   output   wire                                   FIFO_wr_clk                                  ,
   output   wire                                   FIFO_wr_en                                   ,
   input    wire                                   FIFO_prog_full                               ,
   output   wire                                   module_rst_out                                
); // IO port list end

/***********************************************************************************************
//
//    block for Local Parameter, function, macro Declaration              
//                      
***********************************************************************************************/
/***********************************************************************************************
//    local parameter for state machine
***********************************************************************************************/
localparam ST_AXI_IDLE                 = 4'b0001                                       ;
localparam ST_AXI_buffer_empty_wait    = 4'b0010                                       ;
localparam ST_AXI_AR_TR                = 4'b0100                                       ;
localparam ST_AXI_R_TR                 = 4'b1000                                       ;


/***********************************************************************************************
//    local parameter and macro for address calculation
//    OUTPUT_ROW_SIZE                  : Data size of one row of LCD display. unit : byte
//    ADDRESS_INC_PER_BURST            : Data size of one burst. (If burst size is MAXIMUM_BURST_LEN) unit : byte
//    NEXT_LINE                        : Data size of one row of original image. unit : byte
//    upward_nearlest_4kb_boundary(in) : This macro function return the address which is the nearlest 4kb boundary of input address.
//                                       i.e 1 : If input of this macro is 0x0020, the macro return 0x1000
//                                       i.e 2 : If input of this macro is 0x1000, the macro return 0x2000.
//                                               In other word, if input address is 4kb boundary, the macro return the address of next 4kb boudary.
***********************************************************************************************/
localparam OUTPUT_ROW_SIZE          =  OUTPUT_IMG_HSIZE * 2                            ;
localparam ADDRESS_INC_PER_BURST    =  MAXIMUM_BURST_LEN * (M_AXI_DATA_WIDTH / 8)      ;
localparam NEXT_LINE                =  (IMG_HSIZE) * 2                                 ;
`define     upward_nearlest_4kb_boundary(in)    ((in&(~32'h00000FFF))+32'h1000)


/***********************************************************************************************
//
//    block for Register / Wire Declaration            
//                                         
***********************************************************************************************/
/***********************************************************************************************
//    Declaration block for clock, reset, PLL/MMCM lock signal
//    module_enable_falling_d1   : one clock delayed signal of module_enable
***********************************************************************************************/
reg                                    module_enable_falling_d1            ; 


/***********************************************************************************************
//    Declaration block for AXI BUS address register
//    double_frame_buffer_odd_addr_load  : register for double frame buffer address 1
//    double_frame_buffer_even_addr_load : register for double frame buffer address 2
//    SOL_addr                            : Memory address of a first pixel of a line.(Start Of Line)
//                                          When this module read first line of image, SOL_addr store the first pixel of the first line.
//                                          When this module read second line of image, SOL_addr will change for second line of image.
//    output_frame_address_offset         : offset for read address
***********************************************************************************************/
reg   [M_AXI_ADDR_WIDTH - 1 : 0]       double_frame_buffer_odd_addr_load   ;    
reg   [M_AXI_ADDR_WIDTH - 1 : 0]       double_frame_buffer_even_addr_load  ;    
reg   [M_AXI_ADDR_WIDTH - 1 : 0]       output_left_top_coord_x_load        ;    
reg   [M_AXI_ADDR_WIDTH - 1 : 0]       output_left_top_coord_y_load        ;   
reg   [M_AXI_ADDR_WIDTH - 1 : 0]       SOL_addr                            ;
reg   [M_AXI_ADDR_WIDTH - 1 : 0]       output_frame_address_offset         ;



/***********************************************************************************************
//    Declaration block for state machine
//    AR_DONE  : If AXI AR handshake is done, this signal is asserted during 1 clock.
//    R_DONE   : If AXI R handshake is done, this signal is asserted during 1 clock.
***********************************************************************************************/
reg                                    AR_DONE                             ;
reg                                    R_DONE                              ;
reg [3 : 0]                            AXI_cs                              ;
reg [3 : 0]                            AXI_ns                              ;



/***********************************************************************************************
//    
//    block for Simple Wire Interconnect    
//                                                    
***********************************************************************************************/
/***********************************************************************************************
//    Wire Interconnect block for clock, reset, PLL/MMCM lock signal
***********************************************************************************************/
assign      rst                              =  ~m_axi_aresetn                                  ;
assign      module_rst_out                   = (module_enable_falling_d1) & (~module_enable)    ;   


/***********************************************************************************************
//    Wire Interconnect block for clock, reset, PLL/MMCM lock signal
***********************************************************************************************/
assign      FIFO_data                        = {m_axi_data_rdata[15:0],  m_axi_data_rdata[31:16]}  ;
assign      FIFO_wr_clk                      = m_axi_aclk                                          ;
assign      FIFO_wr_en                       = m_axi_data_rvalid                                   ;

/***********************************************************************************************
//    Wire Interconnect block for AXI BUS
***********************************************************************************************/
assign      m_axi_data_arprot                =  3'b000               ;
assign      m_axi_data_arcache               =  4'b0011              ;
assign      m_axi_data_arid                  =  0                    ;
assign      m_axi_data_arlock                =  0                    ;
assign      m_axi_data_arqos                 =  0                    ;
assign      m_axi_data_arsize                =  3'b010               ;  // 4 Byte per beats
assign      m_axi_data_arburst               =  2'b01                ;  // address increase
assign      m_axi_data_rready                =  1                    ;   


/***********************************************************************************************
//                                                                                              
//    block for CDC                                                                             
//                                                                                              
***********************************************************************************************/                    
/***********************************************************************************************
//    There is NO CDC block
***********************************************************************************************/


/***********************************************************************************************
//                                                                                              
//    block for IP Instance                                                                     
//                                                                                              
***********************************************************************************************/   
/***********************************************************************************************
//    There is NO IP instance
***********************************************************************************************/           


/***********************************************************************************************
//                                                                                              
//    block for excution                                                                        
//                                                                                              
***********************************************************************************************/
/***********************************************************************************************
//    block for state machine
***********************************************************************************************/
////////////////////// state macnine for AXI ////////////////////////
always @(posedge m_axi_aclk) begin
   if(!m_axi_aresetn) begin
      AXI_cs <= ST_AXI_IDLE;
   end else begin
      AXI_cs <= AXI_ns;
   end
end // AXI state machine 
////////////////////// state macnine for AXI ////////////////////////

always @(*) begin
   case (AXI_cs)
      /****************************************************************/
      ST_AXI_IDLE              : if(module_enable) begin
                                    AXI_ns <= ST_AXI_buffer_empty_wait  ;
                                 end
                                 else begin
                                    AXI_ns <= ST_AXI_IDLE               ;
                                 end
      /****************************************************************/
      ST_AXI_buffer_empty_wait : if(!module_enable) begin
                                    AXI_ns <= ST_AXI_IDLE  ;
                                 end
                                 else if (!FIFO_prog_full) begin
                                    AXI_ns <= ST_AXI_AR_TR;
                                 end
                                 else begin
                                    AXI_ns <= ST_AXI_buffer_empty_wait;
                                 end
      /****************************************************************/
      ST_AXI_AR_TR            :  if (AR_DONE) begin
                                    AXI_ns <= ST_AXI_R_TR;
                                 end
                                 else begin
                                    AXI_ns <= ST_AXI_AR_TR;
                                 end
      /****************************************************************/
      ST_AXI_R_TR             :  if (R_DONE) begin
                                    AXI_ns <= ST_AXI_buffer_empty_wait;
                                 end
                                 else begin
                                    AXI_ns <= ST_AXI_R_TR;
                                 end
      /****************************************************************/
      default: AXI_ns <= ST_AXI_IDLE;
      /****************************************************************/
   endcase
end // combination logic for AXI_ns


////////////////////////////////////////////////////////////////////////////////////////////////
//    block for buffer address load
//    Note : This block means that you can change the address of double_frame_buffer only when this module is disabled.
////////////////////////////////////////////////////////////////////////////////////////////////
always @(posedge m_axi_aclk) begin
   if(!m_axi_aresetn) begin
      double_frame_buffer_odd_addr_load      <= 0;
      double_frame_buffer_even_addr_load     <= 0;
      output_left_top_coord_x_load           <= 0;
      output_left_top_coord_y_load           <= 0;
   end else if(AXI_cs == ST_AXI_IDLE) begin
      double_frame_buffer_odd_addr_load      <= double_frame_buffer_odd_addr      ;
      double_frame_buffer_even_addr_load     <= double_frame_buffer_even_addr     ;
      output_left_top_coord_x_load           <= output_left_top_coord_x           ;
      output_left_top_coord_y_load           <= output_left_top_coord_y           ;
   end
end 


////////////////////////////////////////////////////////////////////////////////////////////////
//    block for AR_DONE 
////////////////////////////////////////////////////////////////////////////////////////////////
always @(posedge m_axi_aclk) begin
   if(!m_axi_aresetn) begin
      AR_DONE <= 0;
   end
   else begin
      if(AXI_cs == ST_AXI_AR_TR) begin
         if(m_axi_data_arready & m_axi_data_arvalid) begin
            AR_DONE <= 1;
         end
         else begin
            AR_DONE <= AR_DONE;  
         end
      end
      else begin
         AR_DONE <= 0;
      end
   end
end 


////////////////////////////////////////////////////////////////////////////////////////////////
//    block for R_DONE 
////////////////////////////////////////////////////////////////////////////////////////////////
always @(posedge m_axi_aclk) begin
   if(!m_axi_aresetn) begin
      R_DONE <= 0;
   end
   else begin
      if(AXI_cs == ST_AXI_R_TR) begin
         if(m_axi_data_rlast && m_axi_data_rvalid) begin
            R_DONE <= 1;
         end
         else begin
            R_DONE <= R_DONE;  
         end
      end
      else begin
         R_DONE <= 0;
      end
   end
end 



/***********************************************************************************************
//    block for end address of LCD frame
***********************************************************************************************/
always @(posedge m_axi_aclk) begin
   if(!m_axi_aresetn) begin
      output_frame_address_offset      <= 0;
   end 
   else begin
      output_frame_address_offset      <=   (IMG_HSIZE * (output_left_top_coord_y_load + OUTPUT_IMG_VSIZE - 1) + output_left_top_coord_x_load + OUTPUT_IMG_HSIZE) << 1;
   end
end 


/***********************************************************************************************
//    block for arlen.
//    To meet the AXI interface standard, this module MUST NOT cross the 4kb bondary.
//    Note 1 : If the next burst is crossing 4kb boundary, arlen is reduced to meet AXI interface standard.
//    Note 2 : If the nest burst is crossing the end of line of RoI, arlen is reduced to meet LCD frame size.
//    Note 3 : Default Burst size is 16
***********************************************************************************************/
always @(*) begin
   if(`upward_nearlest_4kb_boundary(m_axi_data_araddr) < (m_axi_data_araddr + ADDRESS_INC_PER_BURST)) begin
      m_axi_data_arlen <= ((`upward_nearlest_4kb_boundary(m_axi_data_araddr) - m_axi_data_araddr) / 4)-1; // Note 1
   end
   else if(m_axi_data_araddr > SOL_addr + OUTPUT_ROW_SIZE - ADDRESS_INC_PER_BURST*1)begin
      m_axi_data_arlen <= ((SOL_addr + OUTPUT_ROW_SIZE - m_axi_data_araddr)/4)-1; // Note 2
   end 
   else begin
      m_axi_data_arlen <= 4'd15; // Note 3
   end
end // combination logic for m_axi_data_arlen


/***********************************************************************************************
//    block for araddr
***********************************************************************************************/
always @(posedge m_axi_aclk) begin
   if(!m_axi_aresetn) begin
      m_axi_data_araddr <= 0;
      SOL_addr          <= 0;
   end
   else begin
      if(AXI_cs == ST_AXI_IDLE) begin
         // state가 IDLE이면 읽어 올 메모리의 주소를 odd frame adress로 초기화 시킨다.
         m_axi_data_araddr    <= double_frame_buffer_odd_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
         SOL_addr         <= double_frame_buffer_odd_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
      end else if(SYNC_FORCE_TO_CAM) begin
         // 만약 SYNC 기능이 활성화 되었다면
         if(m_axi_data_arvalid && m_axi_data_arready) begin
            // AR 채널로 address의 전송이 완료되고 나서
            if((m_axi_data_araddr >= double_frame_buffer_odd_addr_load + output_frame_address_offset - ADDRESS_INC_PER_BURST*1) & ((~odd_even_write)) & (m_axi_data_araddr < double_frame_buffer_even_addr_load )) begin
               // 만약 odd frame의 ROI 전체를 전송 완료 했으나, 아직 even frame이 기록 중이면 다시 odd frame의 ROI 시작 부분으로 넘어간다.
               m_axi_data_araddr <= double_frame_buffer_odd_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
               SOL_addr      <= double_frame_buffer_odd_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
            end 
            else if((m_axi_data_araddr >= double_frame_buffer_even_addr_load + output_frame_address_offset - ADDRESS_INC_PER_BURST*1) & (odd_even_write)) begin
               // 만약 even frame의 ROI 전체를 전송 완료 했으나, 아직 odd frame이 기록 중이면 다시 even frame의 ROI 시작 부분으로 넘어간다.
               m_axi_data_araddr <= double_frame_buffer_even_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
               SOL_addr      <= double_frame_buffer_even_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
            end 
            else if(((m_axi_data_araddr >= double_frame_buffer_odd_addr_load + output_frame_address_offset - ADDRESS_INC_PER_BURST*1) && (m_axi_data_araddr < double_frame_buffer_even_addr_load ))) begin
               // 만약 odd frame의 ROI 전체를 전송 완료 했다면, even frame의 ROI 시작 부분으로 넘어간다.
               m_axi_data_araddr <= double_frame_buffer_even_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
               SOL_addr      <= double_frame_buffer_even_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
            end 
            else if((m_axi_data_araddr >= double_frame_buffer_even_addr_load + output_frame_address_offset - ADDRESS_INC_PER_BURST*1)) begin
               // 만약 even frame의 ROI 전체를 전송 완료 했다면, odd frame의 ROI 시작 부분으로 넘어간다.
               m_axi_data_araddr <= double_frame_buffer_odd_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
               SOL_addr      <= double_frame_buffer_odd_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
            end 
            else if(m_axi_data_araddr >= SOL_addr + OUTPUT_ROW_SIZE - ADDRESS_INC_PER_BURST*1)begin
               // 만약 ROI의 한 line을 전송했다면, 다음 line으로 넘어간다.
               m_axi_data_araddr <= SOL_addr + NEXT_LINE;
               SOL_addr      <= SOL_addr + NEXT_LINE;
            end 
            else begin
               if(`upward_nearlest_4kb_boundary(m_axi_data_araddr) < (m_axi_data_araddr + ADDRESS_INC_PER_BURST)) begin
                  // 만약 burst를 진행할 경우, 4kb boundary crossing이 발생한다면, 4kb boundary까지만 burst 동작을 진행한다.
                  m_axi_data_araddr <=  `upward_nearlest_4kb_boundary(m_axi_data_araddr);
               end
               else begin
                  // 만약 한 번의 burst가 끝나면, 다음 burst로 넘어간다.
                  m_axi_data_araddr <=  m_axi_data_araddr + ADDRESS_INC_PER_BURST;
               end
            end
         end
      end else begin
         // 만약 SYNC 기능이 비활성화 되었다면
          if(m_axi_data_arvalid && m_axi_data_arready) begin
             // AR 채널로 address의 전송이 완료되고 나서
            if((m_axi_data_araddr == double_frame_buffer_odd_addr_load + output_frame_address_offset - ADDRESS_INC_PER_BURST*1) && (m_axi_data_araddr < double_frame_buffer_even_addr_load )) begin
               // 만약 odd frame의 ROI 전체를 전송 완료 했다면, even frame의 ROI 시작 부분으로 넘어간다.
               m_axi_data_araddr <= double_frame_buffer_even_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
               SOL_addr      <= double_frame_buffer_even_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
            end 
            else if(m_axi_data_araddr == double_frame_buffer_even_addr_load + output_frame_address_offset - ADDRESS_INC_PER_BURST*1) begin
               // 만약 even frame의 ROI 전체를 전송 완료 했다면, odd frame의 ROI 시작 부분으로 넘어간다.
               m_axi_data_araddr <= double_frame_buffer_odd_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
               SOL_addr      <= double_frame_buffer_odd_addr_load + ((output_left_top_coord_x_load + (output_left_top_coord_y_load)*NEXT_LINE/2)<<1);
            end 
            else if(m_axi_data_araddr >= SOL_addr + OUTPUT_ROW_SIZE - ADDRESS_INC_PER_BURST*1)begin
               // 만약 ROI의 한 line을 전송했다면, 다음 line으로 넘어간다.
               m_axi_data_araddr <= SOL_addr + NEXT_LINE;
               SOL_addr      <= SOL_addr + NEXT_LINE;
            end 
            else begin
               if(`upward_nearlest_4kb_boundary(m_axi_data_araddr) < (m_axi_data_araddr + ADDRESS_INC_PER_BURST)) begin
                  // 만약 burst를 진행할 경우, 4kb boundary crossing이 발생한다면, 4kb boundary까지만 burst 동작을 진행한다.
                  m_axi_data_araddr <=  `upward_nearlest_4kb_boundary(m_axi_data_araddr);
               end
               else begin
                  // 만약 한 번의 burst가 끝나면, 다음 burst로 넘어간다.
                  m_axi_data_araddr <=  m_axi_data_araddr + ADDRESS_INC_PER_BURST;
               end
            end
         end
      end
   end
end



////////////////////////////////////////////////////////////////////////////////////////////////
//    block for arvalid
////////////////////////////////////////////////////////////////////////////////////////////////
always @(*) begin
   if((AXI_cs == ST_AXI_AR_TR) && (!AR_DONE))
      m_axi_data_arvalid = 1;
   else
      m_axi_data_arvalid = 0;
end // combination logic for arvalid


/***********************************************************************************************
//    block for finding falling edge of module_enable
***********************************************************************************************/
always @(posedge m_axi_aclk) begin
   if(!m_axi_aresetn) begin
      module_enable_falling_d1 <= 1;
   end
   else begin
      module_enable_falling_d1 <= module_enable;
   end
end 



endmodule // AXI_to_FIFO end