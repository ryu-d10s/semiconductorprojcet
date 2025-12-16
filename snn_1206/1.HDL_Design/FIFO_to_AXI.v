/*-------------------------------------------------------------------------
--                                                                         
--   Copyright (c) Libertron Co., LTD. 2020                           
--   ALL RIGHTS RESERVED                                                   
--                                                                         
--   THIS PROGRAM IS THE PROPERTY OF Libertron Co., LTD. AND IS            
--   BEING PROVIDED TO YOU PURSUANT TO A LICENSE AGREEMENT THAT            
--   SETS FORTH CERTAIN TERMS AND CONDITIONS FOR USE OF THIS PROGRAM.      
--   YOU MAY NOT COPY, DISTRIBUTE, USE OR OTHERWISE CREATE DERIVATIVES     
--   OF THIS CAM_SOFTWARE EXCEPT AS PROVIDED IN THE LICENSE AGREEMENT.         
-- IP Name       : FIFO_to_AXI
-- IP Revision   :                                                         
-- File Name     : FIFO_to_AXI.v
-- File Revision : 2.0                                                     
-- Date          : 2020/04/21
-- Tool Version  : Xilinx Vivado 2019.2                                    
-- Authors       : Libertron R&D Center, THYoon                            
-- IP Revision History                                                     
-- 2020/04/21 : start
-- 2020/05/12 : 내부 Sync 동작 변경
-- 2020/05/22 : 동작 전면 재수정
-- 2020/05/27 : 파일 분할 및 이름 변경
-- 2020/09/17 : WLAST 오류 수정
-- 2020/09/23 : module rst에 따른 counter 동작 변경
-- 2020/09/25 : state에 따른 reset 동작 수정
-------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////////////////////
//
//    This IP transfer the data from camera module to RAM using AXI bus.
//    camera setting : RGB565, window size : 2200X1125, active area : 1920X1080 (FHD), pclk = 148.5MHz
//    NOTE : ZSK (Zynq 7serise) PS-HP use "AXI 3"
//
////////////////////////////////////////////////////////////////////////////////////////////////

`timescale 1ns/ 100ps

module FIFO_to_AXI
#(
   /***********************************************************************************************
   //    parameter for camera configuration
   ***********************************************************************************************/
   parameter IMG_HSIZE                    =  1920  ,
   parameter IMG_VSIZE                    =  1080  ,
   parameter MAXIMUM_BURST_LEN            =  16    ,


   /***********************************************************************************************
   //    parameter for AXI BUS
   ***********************************************************************************************/
   parameter M_AXI_ADDR_WIDTH	            =  32    ,
   parameter M_AXI_DATA_WIDTH	            =  32                                                                            

) // parameter list end
( // IO port list start
   /***********************************************************************************************
   //    I/O block for clock, reset
   ***********************************************************************************************/
   input    wire                                   regi_clk                   ,
   input    wire                                   module_rst_in              ,   
   input    wire                                   m_axi_data_aclk            ,
   input    wire                                   m_axi_data_aresetn         ,


   /***********************************************************************************************
   //    I/O block for module control
   ***********************************************************************************************/
   input    wire     [M_AXI_ADDR_WIDTH - 1 : 0]    odd_frame_addr_in          , 
   input    wire     [M_AXI_ADDR_WIDTH - 1 : 0]    even_frame_addr_in         , 
   output   reg                                    odd_even_write             , // 0 : odd frame, 1 : even frame


   /***********************************************************************************************
   //    I/O block for AXI BUS
   ***********************************************************************************************/
   output   reg      [M_AXI_ADDR_WIDTH - 1 : 0]    m_axi_data_awaddr          , 
   output   wire     [1 : 0]                       m_axi_data_awburst         , 
   output   wire     [3 : 0]                       m_axi_data_awcache         , 
   output   wire     [5 : 0]                       m_axi_data_awid            , 
   output   reg      [3 : 0]                       m_axi_data_awlen           , 
   output   wire     [1 : 0]                       m_axi_data_awlock          , 
   output   wire     [2 : 0]                       m_axi_data_awprot          , 
   output   wire     [3 : 0]                       m_axi_data_awqos           , 
   input    wire                                   m_axi_data_awready         , 
   output   wire     [2 : 0]                       m_axi_data_awsize          , 
   output   wire                                   m_axi_data_awvalid         , 
   output   wire     [M_AXI_DATA_WIDTH - 1 : 0]    m_axi_data_wdata           , 
   output   wire     [5 : 0]                       m_axi_data_wid             , 
   output   wire                                   m_axi_data_wlast           , 
   input    wire                                   m_axi_data_wready          , 
   output   wire     [3 : 0]                       m_axi_data_wstrb           , 
   output   wire                                   m_axi_data_wvalid          , 
   output   wire                                   m_axi_data_bready          , 
   input    wire                                   m_axi_data_bvalid          , 



   /***********************************************************************************************
   //    I/O block for FIFO ctrl
   ***********************************************************************************************/
   input    wire     [15 : 0]                      FIFO_wr_data               ,
   input    wire                                   FIFO_wr_en                 ,
   input    wire                                   FIFO_wr_clk                
); // IO port list end



/***********************************************************************************************
//
//    block for Local Parameter, function, macro Declaration              
//                      
***********************************************************************************************/
/***********************************************************************************************
//    localparameter for state machine
***********************************************************************************************/
localparam ST_AXI_WR_IDLE                    = 11'b000_0000_0001  ;  // 1
localparam ST_AXI_WR_FIFO_rst                = 11'b000_0000_0010  ;  // 2
localparam ST_AXI_WR_FIFO_WAIT               = 11'b000_0000_0100  ;  // 4
localparam ST_AXI_WR_AW                      = 11'b000_0000_1000  ;  // 8
localparam ST_AXI_WR_FIFO_COUNT_LOCK_WAIT    = 11'b000_0001_0000  ;  // 16
localparam ST_AXI_WR_BURST                   = 11'b000_0010_0000  ;  // 32
localparam ST_AXI_WR_RES_COUNT_CHK           = 11'b000_0100_0000  ;  // 64
localparam ST_AXI_WR_RES_AW                  = 11'b000_1000_0000  ;  // 128
localparam ST_AXI_WR_RES_WRITE               = 11'b001_0000_0000  ;  // 256
localparam ST_AXI_WR_FIRST_STAGE             = 11'b010_0000_0000  ;  // 512
localparam ST_AXI_WR_ADDR_LOAD               = 11'b100_0000_0000  ;  // 1024
localparam WR_STOP_LIMIT                     = 500                ;  // 100MHz 기준, 5us이상 데이터가 들어오지 않으면 stop로 간주  
localparam FIFO_LOCK_CLK                     = 10                 ;  // 


/***********************************************************************************************
//    localparameter for AXI interface
***********************************************************************************************/
localparam PIXEL_PER_BURST                   = MAXIMUM_BURST_LEN * M_AXI_DATA_WIDTH / 8 / 2           ;
localparam BUFFER_SIZE                       = IMG_HSIZE * IMG_VSIZE * (M_AXI_DATA_WIDTH / 8) / 2     ; 



/***********************************************************************************************
//
//    block for Register / Wire Declaration            
//                                         
***********************************************************************************************/
/***********************************************************************************************
//    Wire declaration block for clock, reset, PLL/MMCM lock signal
***********************************************************************************************/        
wire                FIFO_wr_rst_busy         ;
wire                FIFO_rd_rst_busy         ;
wire                FIFO_rst_busy            ;
wire                FIFO_rst                 ;
wire                module_rst               ;  // regi_clk에 동기되어 들어온 module_rst_in을 rst에 동기화 한 신호
wire                clk                      ;  // module 내부 전체 clock, = m_axi_data_aclk
wire                reset_ok                 ;  // 현재 state에서 reset 되어도 AXI 버스에 문제가 없을 때 High


/***********************************************************************************************
//    Wire declaration block for FIFO control
***********************************************************************************************/
wire                FIFO_rd_en               ;
wire [31 : 0]       FIFO_rd_data             ;
wire                FIFO_zero_empty          ;
wire                FIFO_read_ready          ;
wire                FIFO_is_not_read_ready   ;
wire [9 : 0]        FIFO_rd_data_cnt         ;
wire                FIFO_rd_data_valid       ;

/***********************************************************************************************
//    Wire declaration block for state machine
***********************************************************************************************/
wire                FIFO_cnt_lock            ;


/***********************************************************************************************
//    Register declaration block for clock, reset, PLL/MMCM lock signal
***********************************************************************************************/        
reg                 rst                      ;  // module 내부 전체 reset,  Active High


/***********************************************************************************************
//    Register declaration block for FIFO control
***********************************************************************************************/
reg                 FIFO_wr_stop             ;  // 일정 CLK 이상 FIFO_rd_data_cnt가 변하지 않으면 FIFO_wr_stop로 간주한다.
reg  [9 : 0]        FIFO_rd_data_cnt_d1      ;
reg  [11 : 0]       FIFO_wr_stop_cnt         ;


/***********************************************************************************************
//    Register declaration block for state machine
***********************************************************************************************/
reg   [10 : 0]      AXI_WR_cs                ;
reg   [10 : 0]      AXI_WR_ns                ;
reg   [20 : 0]      first_stage_timer        ;
reg   [7 : 0]       AXI_wr_counter           ;
reg   [7 : 0]       last_burst_len           ;
reg   [8 : 0]       FIFO_lock_timer          ;


/***********************************************************************************************
//    Register declaration block for buffer address load
***********************************************************************************************/
reg   [31 : 0]      odd_addr_load            ;
reg   [31 : 0]      even_addr_load           ;


/***********************************************************************************************
//    
//    block for Simple Wire Interconnect    
//                                                    
***********************************************************************************************/
/***********************************************************************************************
//    Wire Interconnect block for clock, reset, PLL/MMCM lock signal
***********************************************************************************************/
assign         clk                  =  m_axi_data_aclk                                 ;
assign         reset_ok             =  (AXI_WR_cs ==  ST_AXI_WR_IDLE     ) ||
                                       (AXI_WR_cs ==  ST_AXI_WR_FIFO_rst ) ||
                                       (AXI_WR_cs ==  ST_AXI_WR_FIFO_COUNT_LOCK_WAIT) ||
                                       (AXI_WR_cs ==  ST_AXI_WR_FIRST_STAGE);


/***********************************************************************************************
//    Wire Interconnect block for FIFO control
***********************************************************************************************/
assign         FIFO_rst             =  rst                                             ;
assign         FIFO_rst_busy        =  FIFO_wr_rst_busy | FIFO_rd_rst_busy             ;
assign         FIFO_read_ready      =  ~FIFO_is_not_read_ready                         ;
assign         FIFO_rd_en           =  m_axi_data_wvalid && m_axi_data_wready          ;


/***********************************************************************************************
//    Wire Interconnect block for AXI interconnect
***********************************************************************************************/
assign         m_axi_data_awprot    =  3'b000                                                                                                      ;
assign         m_axi_data_bready    =  1                                                                                                           ;
assign         m_axi_data_wdata     =  {FIFO_rd_data[15:0], FIFO_rd_data[31:16]}                                                                   ;
assign         m_axi_data_awsize    =  3'b010                                                                                                      ; 
assign         m_axi_data_awburst   =  2'b01                                                                                                       ; 
assign         m_axi_data_awvalid   =  ((AXI_WR_cs == ST_AXI_WR_AW) || (AXI_WR_cs == ST_AXI_WR_RES_AW)) ? 1 : 0                                    ;    
assign         m_axi_data_wvalid    =  ((AXI_WR_cs == ST_AXI_WR_BURST)||(AXI_WR_cs == ST_AXI_WR_RES_WRITE))&& (FIFO_rd_data_valid == 1)            ;
assign         m_axi_data_wlast     =  (AXI_wr_counter == last_burst_len) && ((AXI_WR_cs == ST_AXI_WR_BURST)||(AXI_WR_cs == ST_AXI_WR_RES_WRITE))  ;
assign         m_axi_data_awcache   =  4'b0011                                                                                                     ; // 4'b0011 
assign         m_axi_data_awid      =  0                                                                                                           ;
assign         m_axi_data_awlock    =  0                                                                                                           ;
assign         m_axi_data_awqos     =  0                                                                                                           ;
assign         m_axi_data_wid       =  0                                                                                                           ;
assign         m_axi_data_wstrb     =  4'b1111                                                                                                     ;


/***********************************************************************************************
//    Wire Interconnect block for state machine
***********************************************************************************************/
assign         FIFO_cnt_lock      =  (FIFO_lock_timer == FIFO_LOCK_CLK)                         ;


/***********************************************************************************************
//                                                                                              
//    block for CDC                                                                             
//                                                                                              
***********************************************************************************************/                    
xpm_cdc_async_rst #(
 .DEST_SYNC_FF          (4                      ),    
 .INIT_SYNC_FF          (0                      ),    
 .RST_ACTIVE_HIGH       (1                      )  
)
CDC_reset_from_module_rst_in_to_module_rst
(
 .src_arst              (module_rst_in          ),   		
 .dest_clk              (m_axi_data_aclk        ),    
 .dest_arst             (module_rst             )  			
);


/***********************************************************************************************
//                                                                                              
//    block for IP Instance                                                                     
//                                                                                              
***********************************************************************************************/                 
CAM_pdata_sync_FIFO cam_data_fifo
(
 .rst                   (FIFO_rst               ),  
 .wr_clk                (FIFO_wr_clk            ),  
 .rd_clk                (clk                    ),  
 .din                   (FIFO_wr_data           ),  
 .wr_en                 (FIFO_wr_en             ),  
 .rd_en                 (FIFO_rd_en             ),  
 .dout                  (FIFO_rd_data           ),  
 .empty                 (FIFO_zero_empty        ),  
 .valid                 (FIFO_rd_data_valid     ),  
 .rd_data_count         (FIFO_rd_data_cnt       ),  
 .prog_empty            (FIFO_is_not_read_ready ),  
 .wr_rst_busy           (FIFO_wr_rst_busy       ),  
 .rd_rst_busy           (FIFO_rd_rst_busy       )    
);


/***********************************************************************************************
//                                                                                              
//    block for excution                                                                        
//                                                                                              
***********************************************************************************************/
/***********************************************************************************************
//    block for registerd reset signal. 참고 : https://forums.xilinx.com/t5/Blog-Archive/Demystifying-Resets-Synchronous-Asynchronous-and-other-Design/td-p/887366
//    m_axi_data_aresetn 이외에 reset 신호가 발생하면, 해당 신호를 사용하여 rst신호를 assert함.
//    특히 AXI 버스 관련된 동작을 하는 스테이트가 아닐때만 reset 신호를 발생함.
***********************************************************************************************/
always @(posedge clk) begin
   if(!m_axi_data_aresetn) begin
      rst <= 1;         // m_axi_data_aresetn가 assert 되면 다른 block을 초기화 하기 위해 rst신호를 assert 한다.
   end
   else begin
      rst   <= module_rst & (m_axi_data_wlast | reset_ok); 
   end
end 


/***********************************************************************************************
//    block for state machine
***********************************************************************************************/
////////////////////// state macnine for AXI_WR ////////////////////////
always @(posedge clk) begin
   if(!m_axi_data_aresetn) begin
      AXI_WR_cs <= ST_AXI_WR_FIRST_STAGE;
   end
   else begin
      AXI_WR_cs <= AXI_WR_ns;
   end
end // AXI_WR state machine 
////////////////////// state macnine for AXI_WR ////////////////////////

always @(*) begin
   case (AXI_WR_cs)
      ST_AXI_WR_FIRST_STAGE            :  if(first_stage_timer > 10000) begin
                                             AXI_WR_ns = ST_AXI_WR_ADDR_LOAD                          ;
                                          end
                                          else begin
                                             AXI_WR_ns = ST_AXI_WR_FIRST_STAGE                        ;
                                          end
      ST_AXI_WR_ADDR_LOAD             :  AXI_WR_ns = ST_AXI_WR_IDLE                                   ;
      /****************************************************************/
      ST_AXI_WR_IDLE                   :  AXI_WR_ns = ST_AXI_WR_FIFO_rst                              ;
      /****************************************************************/
      ST_AXI_WR_FIFO_rst               :  if(rst) begin
                                             AXI_WR_ns = ST_AXI_WR_FIRST_STAGE                        ;
                                          end
                                          else if(~FIFO_rst_busy) begin // fifo reset이 완료 되면
                                             AXI_WR_ns = ST_AXI_WR_FIFO_WAIT                          ;
                                          end
                                          else begin
                                             AXI_WR_ns = ST_AXI_WR_FIFO_rst                           ;
                                          end
      /****************************************************************/
      ST_AXI_WR_FIFO_WAIT              :  if(rst) begin
                                             AXI_WR_ns = ST_AXI_WR_FIRST_STAGE                        ;
                                          end
                                          else if(FIFO_read_ready) begin
                                             AXI_WR_ns = ST_AXI_WR_AW                                 ;
                                          end
                                          else if(FIFO_wr_stop & (!FIFO_zero_empty)) begin // FIFO 데이터 기록이 더 이상 발생하지 않으면   
                                             AXI_WR_ns = ST_AXI_WR_FIFO_COUNT_LOCK_WAIT               ; 
                                          end
                                          else begin
                                             AXI_WR_ns = ST_AXI_WR_FIFO_WAIT                          ;
                                          end
      /****************************************************************/
      ST_AXI_WR_AW                     :  if(m_axi_data_awready && m_axi_data_awvalid) begin 
                                             AXI_WR_ns = ST_AXI_WR_BURST                              ;
                                          end
                                          else begin
                                             AXI_WR_ns = ST_AXI_WR_AW                                 ;
                                          end
      /****************************************************************/
      ST_AXI_WR_BURST                  :  if(m_axi_data_wlast) begin
                                             AXI_WR_ns = ST_AXI_WR_FIFO_WAIT                          ;   
                                          end
                                          else begin
                                             AXI_WR_ns = ST_AXI_WR_BURST                              ;
                                          end
      /****************************************************************/
      ST_AXI_WR_FIFO_COUNT_LOCK_WAIT   :  if(rst) begin
                                             AXI_WR_ns = ST_AXI_WR_FIRST_STAGE                        ;
                                          end
                                          else if(FIFO_cnt_lock) begin
                                             AXI_WR_ns = ST_AXI_WR_RES_COUNT_CHK                      ;
                                          end
                                          else begin
                                             AXI_WR_ns = ST_AXI_WR_FIFO_COUNT_LOCK_WAIT               ;
                                          end
      /****************************************************************/
      ST_AXI_WR_RES_COUNT_CHK          :   if(!FIFO_zero_empty) begin
                                             AXI_WR_ns = ST_AXI_WR_RES_AW                             ;
                                          end
                                          else begin
                                             AXI_WR_ns = ST_AXI_WR_ADDR_LOAD                         ;
                                          end
      /****************************************************************/
      ST_AXI_WR_RES_AW                 :  if(m_axi_data_awready && m_axi_data_awvalid) begin
                                             AXI_WR_ns = ST_AXI_WR_RES_WRITE                          ;
                                          end
                                          else begin
                                             AXI_WR_ns = ST_AXI_WR_RES_AW                             ;
                                          end
      /****************************************************************/
      ST_AXI_WR_RES_WRITE              :  if(m_axi_data_wlast) begin
                                             AXI_WR_ns = ST_AXI_WR_FIFO_COUNT_LOCK_WAIT               ;   
                                          end
                                          else begin
                                             AXI_WR_ns = ST_AXI_WR_RES_WRITE                          ;
                                          end
      /****************************************************************/
      default                       :  AXI_WR_ns = ST_AXI_WR_IDLE;
   endcase
end // combination logic for AXI_WR_ns


/***********************************************************************************************
//    block for FIFO_lock_timer
***********************************************************************************************/
always @(posedge m_axi_data_aclk) begin
   if(rst) begin
      FIFO_lock_timer <= 0;
   end
   else if(AXI_WR_cs == ST_AXI_WR_FIFO_COUNT_LOCK_WAIT)begin
      FIFO_lock_timer <= FIFO_lock_timer +1;
   end
   else begin
      FIFO_lock_timer <= 0;
   end
end 


/***********************************************************************************************
//    block for FIFO_rd_data_cnt_d1
***********************************************************************************************/
always @(posedge clk) begin
   if(rst) begin
      FIFO_rd_data_cnt_d1 <= 0;
   end
   else begin
      FIFO_rd_data_cnt_d1 <= FIFO_rd_data_cnt;
   end
end 

/***********************************************************************************************
//    block for FIFO_wr_stop_cnt
//    FIFO가 비어 있지 않은데, 그 데이터의 갯수가 증가하지 않으면, 그 시간을 카운트 한다.
//    이는 camara에서 data가 입력되지 않는 시간을 (=VSYNC신호의 assertion) 의미한다.
***********************************************************************************************/
always @(posedge clk) begin
   if(rst) begin
      FIFO_wr_stop_cnt <= 0;
   end
   else begin
      if((FIFO_rd_data_cnt_d1 == FIFO_rd_data_cnt) && (!FIFO_zero_empty)) begin
         FIFO_wr_stop_cnt <= FIFO_wr_stop_cnt + 1;
      end
      else begin
         FIFO_wr_stop_cnt <= 0;
      end
   end
end 

/***********************************************************************************************
//    block for FIFO_wr_stop
//    FIFO에 데이터가 있는 상태에서 그 갯수의 증가가 WR_STOP_LIMIT 클럭이 지나도록 증가하지 않으면 stop로 간주한다.
//    HSYNC가 끝나는 순간부터 VSYNC가 끝나는 순간은 30FPS 기준 1.2us = 120clk 이므로 이를 참고하여 FIFO의 prog_empty의 쓰래쉬 홀드를 결정한다.
//    한번 stop 신호가 뜨면 FIFO가 빌 때까지 stop 신호를 띄어놓는다. 이는 stop 신호가 assertion되면 state machine의 동작에 의해 FIFO 내부의 data가 출력되면서
//    FIFO내부의 DATA 갯수가 변하기 때문이다.
***********************************************************************************************/
always @(posedge clk) begin
   if(rst) begin
      FIFO_wr_stop <= 0;
   end
   else begin
      if(FIFO_wr_stop_cnt > WR_STOP_LIMIT) begin
         FIFO_wr_stop <= 1;
      end
      else if(FIFO_zero_empty)begin
         FIFO_wr_stop <= 0;
      end
      else begin
         FIFO_wr_stop <= FIFO_wr_stop;
      end
   end
end 

/***********************************************************************************************
//    block for first_stage_timer
***********************************************************************************************/
always @(posedge clk) begin
   if(rst) begin
      first_stage_timer <= 0;
   end
   else begin
      if((AXI_WR_cs == ST_AXI_WR_FIRST_STAGE) && (!module_rst)) begin
         first_stage_timer <= first_stage_timer + 1;
      end
   end
end 

/***********************************************************************************************
//    block for awadddr
***********************************************************************************************/
always @(posedge clk) begin
   if(rst) begin
      m_axi_data_awaddr <= 0;
   end
   else begin
      case (AXI_WR_cs)
         ST_AXI_WR_IDLE :     if(odd_even_write) begin // 0 : odd frame, 1 : even frame
                                 m_axi_data_awaddr <= even_addr_load;
                              end
                              else begin
                                 m_axi_data_awaddr <= odd_addr_load;
                              end
         /****************************************************************/
         ST_AXI_WR_AW   :     if(m_axi_data_awvalid && m_axi_data_awready)begin
                                 m_axi_data_awaddr <= m_axi_data_awaddr + (m_axi_data_awlen+1)*(M_AXI_DATA_WIDTH / 8);
                              end
         /****************************************************************/
         ST_AXI_WR_RES_AW :   if(m_axi_data_awvalid && m_axi_data_awready)begin
                                 m_axi_data_awaddr <= m_axi_data_awaddr + (m_axi_data_awlen+1)*(M_AXI_DATA_WIDTH / 8);
                              end
         /****************************************************************/
         default: m_axi_data_awaddr <= m_axi_data_awaddr;
      endcase
   end
end 

/***********************************************************************************************
//    block for odd_even_write (0 : odd frame, 1 : even frame)
***********************************************************************************************/
always @(posedge clk) begin
   if(rst) begin
      odd_even_write <= 0; // 시작 0 : odd frame, 1 : even frame
   end
   else begin
      if((m_axi_data_awaddr == even_addr_load + (BUFFER_SIZE) - (last_burst_len+1) * (M_AXI_ADDR_WIDTH / 8)) & m_axi_data_awvalid & m_axi_data_awready) begin // 짝수 끝 도달 -> 홀수로 변경
         odd_even_write <= 0;
      end
      else if((m_axi_data_awaddr == odd_addr_load + (BUFFER_SIZE) - (last_burst_len+1) * (M_AXI_ADDR_WIDTH / 8)) & m_axi_data_awvalid & m_axi_data_awready) begin // 홀수 끝 도달 -> 짝수로 변경
         odd_even_write <= 1;
      end
   end
end 

/***********************************************************************************************
//    block for m_axi_data_awlen
***********************************************************************************************/
always @(posedge clk) begin
   if(rst) begin
      m_axi_data_awlen <= 0;
   end
   else if(FIFO_rd_data_cnt >= 16) begin
      m_axi_data_awlen = 15;
   end
   else if (FIFO_rd_data_cnt == 0) begin
      m_axi_data_awlen = 0;
   end
   else begin 
      m_axi_data_awlen = FIFO_rd_data_cnt - 1;
   end
end 

/***********************************************************************************************
//    block for burst len counter
***********************************************************************************************/
always @(posedge clk) begin
   if(rst) begin
      AXI_wr_counter <= 0;
   end
   else if((AXI_WR_cs == ST_AXI_WR_BURST)||(AXI_WR_cs == ST_AXI_WR_RES_WRITE)) begin
      if(m_axi_data_wvalid && m_axi_data_wready)begin
         AXI_wr_counter <= AXI_wr_counter + 1;
      end
   end else begin
      AXI_wr_counter <= 0;
   end
end 

/***********************************************************************************************
//    block for last burst len
***********************************************************************************************/
always @(posedge m_axi_data_aclk) begin
   if(!m_axi_data_aresetn) begin
      last_burst_len <= 0;
   end
   else begin
      if((AXI_WR_cs == ST_AXI_WR_AW) || (AXI_WR_cs == ST_AXI_WR_RES_AW)) begin
         last_burst_len <= m_axi_data_awlen;
      end
   end
end 


/***********************************************************************************************
//    block for address load
***********************************************************************************************/
always @(posedge regi_clk) begin
   if(rst) begin
      odd_addr_load    <= 0;
      even_addr_load   <= 0;
   end
   else begin
      if(AXI_WR_cs == ST_AXI_WR_ADDR_LOAD) begin
         odd_addr_load    <= odd_frame_addr_in ;
         even_addr_load   <= even_frame_addr_in;
      end
   end
end 


////////////////////////////////////////// simulation only
`ifdef XILINX_SIMULATOR
reg [ 1:8*27 ] AXI_WR_state_string;
always @(*) begin
   case (AXI_WR_cs)
      ST_AXI_WR_IDLE                : AXI_WR_state_string <= "ST_AXI_WR_IDLE                ";
      ST_AXI_WR_FIFO_rst            : AXI_WR_state_string <= "ST_AXI_WR_FIFO_rst            ";
      ST_AXI_WR_FIFO_WAIT           : AXI_WR_state_string <= "ST_AXI_WR_FIFO_WAIT           ";
      ST_AXI_WR_AW                  : AXI_WR_state_string <= "ST_AXI_WR_AW                  ";
      ST_AXI_WR_FIFO_COUNT_LOCK_WAIT: AXI_WR_state_string <= "ST_AXI_WR_FIFO_COUNT_LOCK_WAIT";
      ST_AXI_WR_BURST               : AXI_WR_state_string <= "ST_AXI_WR_BURST               ";
      ST_AXI_WR_RES_COUNT_CHK       : AXI_WR_state_string <= "ST_AXI_WR_RES_COUNT_CHK       ";
      ST_AXI_WR_RES_AW              : AXI_WR_state_string <= "ST_AXI_WR_RES_AW              ";
      ST_AXI_WR_RES_WRITE           : AXI_WR_state_string <= "ST_AXI_WR_RES_WRITE           ";
      ST_AXI_WR_FIRST_STAGE         : AXI_WR_state_string <= "ST_AXI_WR_FIRST_STAGE         ";
      ST_AXI_WR_ADDR_LOAD           : AXI_WR_state_string <= "ST_AXI_WR_ADDR_LOAD           ";
   endcase
end
`endif
////////////////////////////////////////// simulation only


endmodule // FIFO_to_AXI end