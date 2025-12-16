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
-- IP Name        : CAM_IF_to_FIFO
-- IP Revision    :                                                         
-- File Name      : CAM_IF_to_FIFO.v
-- File Revision  : 1.0                                                     
-- Date           : 2020/05/27
-- Tool Version   : Xilinx Vivado 2019.2                                    
-- Authors        : Libertron R&D Center, THYoon                            
-- IP Revision History                                                     
-- 2020/05/27     : 파일 분할                                                                        
-- 2020/07/25     : 리비젼
-------------------------------------------------------------------------*/

`timescale 1ns/ 100ps

module CAM_IF_to_FIFO
#(
   /***********************************************************************************************
   //    parameter for camera configuration.
   ***********************************************************************************************/
   parameter IMG_HSIZE                             =  1920                    ,
   parameter IMG_VSIZE                             =  1080                    ,
   parameter CAM_BIT_WIDTH                         =  10                                                                            
) // parameter list end
( // IO port list start
   /***********************************************************************************************
   //    input block for clock, reset.
   //    Note : regi_clk : module control register clock and also work as slow clock of FIFO.
   //    Note : rst_in : regi_clk domain
   ***********************************************************************************************/
   input    wire                                   regi_clk                   ,
   input    wire                                   rst_in                     ,
   

   /***********************************************************************************************
   //    I/O block for camera data and control.
   ***********************************************************************************************/
   input    wire     [CAM_BIT_WIDTH - 1 : 0]       CAM_data_in                ,
   input    wire                                   CAM_pclk_in                ,
   input    wire                                   CAM_HSYNC_in               ,
   input    wire                                   CAM_VSYNC_in               ,
   input    wire                                   CAM_DE_in                  ,


   /***********************************************************************************************
   //    I/O block for module control
   ***********************************************************************************************/
   input    wire                                   CAM_en                     ,


   /***********************************************************************************************
   //    Register declaration block for camera signal is lock or not
   ***********************************************************************************************/
   output   reg                                    frame_lock                 ,
   output   reg                                    HSYNC_lock                 ,

   /***********************************************************************************************
   //    I/O block for FIFO ctrl and FIFO write data.
   ***********************************************************************************************/
   output   reg      [15 : 0]                      FIFO_wr_data               , 
   output   wire                                   FIFO_wr_en                 ,
   output   wire                                   FIFO_wr_clk                
); // IO port list end

/***********************************************************************************************
//
//    block for Local Parameter, function, macro Declaration              
//                      
***********************************************************************************************/          
/***********************************************************************************************
//    There is No Local Parameter, function, macro Declaration          
***********************************************************************************************/


/***********************************************************************************************
//
//    block for Register / Wire Declaration            
//                                  
***********************************************************************************************/      
/***********************************************************************************************
//    Wire declaration block for clock, reset, PLL/MMCM lock signal
***********************************************************************************************/
wire                                      rst                           ;  // reset signal synchronized to cam_pclk.


/***********************************************************************************************
//    Wire declaration block for camera signal is lock or not
***********************************************************************************************/
wire                                      data_EOL                      ;
wire                                      data_SOF                      ;
wire                                      HSYNC_end                     ;
wire                                      VSYNC_end                     ;
wire                                      DE_end                        ;


/***********************************************************************************************
//    Wire declaration block for pixel coordinate
***********************************************************************************************/
wire  [12 : 0]                            x_coord                       ;


/***********************************************************************************************
//    Register declaration block for etc.
***********************************************************************************************/
wire                                      data_odd_even_sel             ; // subpixel data odd/even select.
wire                                      CAM_en_sync                   ;


/***********************************************************************************************
//    Register declaration block for detect rising / falling edge
***********************************************************************************************/
reg                                       CAM_HSYNC_falling_d1          ;
reg                                       CAM_VSYNC_falling_d1          ;
reg                                       CAM_DE_falling_d1             ;


/***********************************************************************************************
//    Register declaration block for camera input register
***********************************************************************************************/
reg  [CAM_BIT_WIDTH - 1 : 0]              CAM_data                      ;
reg                                       CAM_HSYNC                     ;
reg                                       CAM_VSYNC                     ;
reg                                       CAM_DE                        ;


/***********************************************************************************************
//    Register declaration block for camera signal is lock or not
***********************************************************************************************/
reg   [12 : 0]                            de_counter                    ;


/***********************************************************************************************
//    Register declaration block for pixel coordinate
***********************************************************************************************/
reg   [12 : 0]                            y_coord                       ;



/***********************************************************************************************
//    Register declaration block for etc.
***********************************************************************************************/
reg                                       pixel_data_valid              ;


/***********************************************************************************************
//    
//    block for Simple Wire Interconnect    
//                                                    
***********************************************************************************************/
/***********************************************************************************************
//    Wire Interconnect block for camera signal is locked or not
***********************************************************************************************/
assign            HSYNC_end         =  (CAM_HSYNC_falling_d1) & (~CAM_HSYNC)                 ;
assign            VSYNC_end         =  (CAM_VSYNC_falling_d1) & (~CAM_VSYNC)                 ;
assign            DE_end            =  (CAM_DE_falling_d1) & (~CAM_DE)                       ;


/***********************************************************************************************
//    Wire Interconnect block for FIFO ctrl
***********************************************************************************************/
assign            FIFO_wr_en        =  pixel_data_valid & frame_lock & CAM_en_sync           ;
assign            FIFO_wr_clk       =  CAM_pclk_in                                           ;


/***********************************************************************************************
//    Wire Interconnect block for etc
//    Note : ZN220 use 2 plck per 1 pixel.
***********************************************************************************************/
assign            data_odd_even_sel =  de_counter[0]                                         ;
assign            x_coord           =  de_counter >> 1                                       ;  


/***********************************************************************************************
//
//    block for CDC                                                                             
//
***********************************************************************************************/
/***********************************************************************************************
//    make synchronized reset signal.
***********************************************************************************************/
xpm_cdc_async_rst#      (
   .DEST_SYNC_FF        (4             ),    			
   .INIT_SYNC_FF        (0             ),    			
   .RST_ACTIVE_HIGH     (1             )  			
)
CDC_reset_from_module_rst_rst
(
   .src_arst            (rst_in        ),   
   .dest_clk            (CAM_pclk_in   ),   
   .dest_arst           (rst           )  				
);

xpm_cdc_array_single #  (
 .DEST_SYNC_FF          (4             ),
 .INIT_SYNC_FF          (0             ),
 .SIM_ASSERT_CHK        (0             ),
 .SRC_INPUT_REG         (1             ),
 .WIDTH                 (1             )
)
CDC_data_from_CAM_en_to_CAM_en_sync
(
 .src_clk               (regi_clk      ),
 .src_in                (CAM_en        ),
 .dest_clk              (CAM_pclk_in   ),
 .dest_out              (CAM_en_sync   )
);


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
//    block for camera data register
***********************************************************************************************/
always @(posedge CAM_pclk_in) begin
   if(rst) begin
      CAM_data  <= 0;
      CAM_HSYNC <= 0;
      CAM_VSYNC <= 0;
      CAM_DE    <= 0;
   end
   else begin
      CAM_data  <= CAM_data_in      ;
      CAM_HSYNC <= CAM_HSYNC_in     ;
      CAM_VSYNC <= CAM_VSYNC_in     ;
      CAM_DE    <= CAM_DE_in        ;
   end
end 



/***********************************************************************************************
//    block for de signal count
//    'End of HSYNC' means that one horizontal line is end and this block have to ready to get next 'de and pixel signal train'. 
***********************************************************************************************/
always @(posedge CAM_pclk_in) begin
   if(rst) begin
      de_counter <= 0;
   end
   else begin
      if (CAM_VSYNC & CAM_DE) begin
         de_counter <= de_counter + 1;
      end
      else if (HSYNC_end) begin
         de_counter <= 0;
      end
   end
end 


/***********************************************************************************************
//    block for y coordination 
//    'No VSYNC' means that one frame is end and this block have to ready to get next frame. 
***********************************************************************************************/
always @(posedge CAM_pclk_in) begin
   if(rst) begin
      y_coord <= 0;
   end
   else begin
      if(DE_end & CAM_VSYNC) begin
         y_coord <= y_coord + 1;
      end
      else if(!CAM_VSYNC) begin  
         y_coord <= 0;
      end
   end
end 


/***********************************************************************************************
//    block for pixel data concatnation
//    Note : data_odd_even_sel =  de_counter[0];
//    Note : 0 is even. And count of de is start from 0.
//    Note : In other word, the first subpixel which is this module receive is even pixel.
//    If this module receive odd subpixel, than store it to LSB side of 'one full pixel'(= CAM_data).
//    one full pixel = {[15]<---MSB side of one full pixel--->[8]}, {[7]<---LSB side of one full pixel--->[1]}
***********************************************************************************************/
always @(posedge CAM_pclk_in) begin
   if(rst) begin
      FIFO_wr_data[7:0]          <= 0                  ;
      FIFO_wr_data[15:8]         <= 0                  ;
   end
   else begin
      if(data_odd_even_sel)begin
         FIFO_wr_data[7:0]       <= CAM_data[9:2]      ;
      end else begin
         FIFO_wr_data[15:8]      <= CAM_data[9:2]      ;
      end 
   end
end 


/***********************************************************************************************
//    block for pixel_data_valid
//    Note : data_odd_even_sel =  de_counter[0];
//    Note : 0 is even. And count of de is start from 0.
//    Note : In other word, the first subpixel which is this module receive is even pixel.
//    To make 'one full pixel'(= CAM_data), this module have to receive 2 subpixels(= even and odd subpixel).
//    That means if this module receive odd pixel, than the CAM_data is valid.
***********************************************************************************************/
always @(posedge CAM_pclk_in) begin
   if(rst) begin
      pixel_data_valid <= 0;
   end
   else begin
      pixel_data_valid <= data_odd_even_sel; 
   end
end 


/***********************************************************************************************
//    block for HSYNC lock detect
//    default value of HSYNC_lock is High (= HSYNC is locked)
//    When HSYNC is end but de count is not a value to HSYNC lock than lock is deassert.
***********************************************************************************************/
always @(posedge CAM_pclk_in) begin
   if(rst) begin
      HSYNC_lock <= 0;
   end
   else begin
      if(VSYNC_end) begin
         HSYNC_lock <= 1;
      end
      else if(!CAM_en_sync) begin
         HSYNC_lock <= 0;
      end
      else if((de_counter != (IMG_HSIZE*2)) && HSYNC_end && CAM_VSYNC) begin
         HSYNC_lock <= 0;
      end
   end
end 


/***********************************************************************************************
//    block for frame lock detect
//    default value of frame_lock is Low (= frame is NOT locked)
//    When VSYNC is end HSYNC is locked and module receive IMG_VSIZE line during VSYNC, frame lock is assert.
***********************************************************************************************/
always @(posedge CAM_pclk_in) begin
   if(rst) begin
      frame_lock  <= 0;
   end
   else begin
      if(VSYNC_end) begin
         if((HSYNC_lock == 1) &&(y_coord == (IMG_VSIZE))) begin
            frame_lock <= 1; 
         end
         else begin
            frame_lock <= 0;
         end
      end
   end
end 


/***********************************************************************************************
//    block for finding falling edge of CAM_HSYNC, CAM_VSYNC, CAM_DE
***********************************************************************************************/
always @(posedge CAM_pclk_in) begin
   if(rst) begin
      CAM_HSYNC_falling_d1 <= 1;
      CAM_VSYNC_falling_d1 <= 1;
      CAM_DE_falling_d1    <= 1;
   end
   else begin
      CAM_HSYNC_falling_d1 <= CAM_HSYNC;
      CAM_VSYNC_falling_d1 <= CAM_VSYNC;
      CAM_DE_falling_d1    <= CAM_DE   ;
   end
end 


endmodule // CAM_IF_to_FIFO end