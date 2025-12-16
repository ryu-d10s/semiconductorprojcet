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
-- IP Name        : FIFO_to_LCD_IF
-- IP Revision    :                                                         
-- File Name      : FIFO_to_LCD_IF.v
-- File Revision  : 1.0                                                     
-- Date           : 2020/05/06
-- Tool Version   : Xilinx Vivado 2019.2                                    
-- Authors        : Libertron R&D Center, THYoon                            
-- IP Revision History                                                     
-- 2020/05/06     : start
-- 2020/05/06     : HDMI와 LCD를 동시에 출력하기 위하여 동작하도록 개발 방향 선회
-- 2020/05/24     : 오버레이 기능 추가
-- 2020/07/06     : AXI ARADDR 4KB boundary 문제 수정
-- 2020/07/13     : 파일 분할
-------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////
//
//    본 IP는 buffer adderess / output size, sync signal 값을 받아 이에 맞게 데이터를 읽어와 출력하는 IP 이다.
//
////////////////////////////////////////////////////////////////////////////////////////////////
`timescale 1ns/ 100ps

module FIFO_to_LCD_IF
#(
   /***********************************************************************************************
   //    parameter for LCD
   ***********************************************************************************************/
   parameter OUTPUT_BIT_WIDTH                      =  24         ,
   parameter Tvw                                   =  12'd10     , // VSYNC Pulse Width
   parameter Tvbp                                  =  12'd23     , // VSYNC Back Porch
   parameter Tvfp                                  =  12'd22     , // Vertical Front Porch
   parameter Tvdw                                  =  12'd480    , // Vertical valid data width
   parameter Thw                                   =  12'd20     , // HSYNC Pulse Width        
   parameter Thbp                                  =  12'd46     , // HSYNC Back Porch         
   parameter Thfp                                  =  12'd210    , // Horizontal Front Porch     
   parameter Thdw                                  =  12'd800      // Horizontal valid data width 

) // parameter list end
( // IO port list start
   /***********************************************************************************************
   //    I/O block for clock, reset
   ***********************************************************************************************/
   input    wire                                   regi_clk                             ,
   input    wire                                   module_rst                           ,


   /***********************************************************************************************
   //    I/O block for module control
   //    color_key      : RGB 565
   //    overlay_enable : If asserted, this module use overlay data pixel
   ***********************************************************************************************/
   input    wire     [15 : 0]                      color_key                            ,
   input    wire                                   overlay_enable                       ,


   /***********************************************************************************************
   //    I/O block for LCD parallel interface
   ***********************************************************************************************/
   input    wire                                   LCD_IF_pclk_in                  ,
   output   wire     [OUTPUT_BIT_WIDTH - 1 : 0]    LCD_IF_pdata                    ,
   output   wire                                   LCD_IF_HSYNC                    ,
   output   wire                                   LCD_IF_VSYNC                    ,
   output   wire                                   LCD_IF_DE                       ,
   output   wire                                   LCD_IF_pclk_out                 ,


   /***********************************************************************************************
   //    I/O block for background image FIFO
   ***********************************************************************************************/
   input    wire     [15 : 0]                      origin_pixel_data                    ,
   output   wire                                   ori_buffer_rd_en                     ,
   output   wire                                   ori_buffer_rd_clk                    ,
   input    wire                                   ori_buffer_prog_empty                ,
   input    wire                                   ori_buffer_zero_empty                ,


   /***********************************************************************************************
   //    I/O block for foreground image FIFO
   ***********************************************************************************************/
   input    wire     [15 : 0]                      overlay_pixel_data                   ,
   output   wire                                   ovr_buffer_rd_en                     ,
   output   wire                                   ovr_buffer_rd_clk                    ,
   input    wire                                   ovr_buffer_prog_empty                ,
   input    wire                                   ovr_buffer_zero_empty                       

); // IO port list end
/***********************************************************************************************
//
//    block for Local Parameter, function, macro Declaration              
//                      
***********************************************************************************************/
/***********************************************************************************************
//    macro function for RGB565 to RGB24
***********************************************************************************************/
`define     RGB565_to_RGB24(in)                        {{{8'b0}|{in[15:11]} << 3}, {8'b0|{in[10:5]} << 2}, {8'b0|{in[4:0]} << 3}}


/***********************************************************************************************
//
//    block for Register / Wire Declaration            
//                                         
***********************************************************************************************/
/***********************************************************************************************
//    wire declaration block for reset
***********************************************************************************************/     
wire                                   rst_sync_to_pclk                    ;


/***********************************************************************************************
//    wire declaration block for module configuration
***********************************************************************************************/  
wire   [15 : 0]      synced_color_key                                      ;
wire                 overlay_enable_sync_load                              ;


/***********************************************************************************************
//    wire declaration block for FIFO control
***********************************************************************************************/  
wire                                   ALL_buffer_rd_en                    ;
wire                                   ALL_buffer_zero_empty               ;


/***********************************************************************************************
//    wire declaration block for LCD data, sync signal
***********************************************************************************************/  
wire  [7 : 0]                          RED                                 ;
wire  [7 : 0]                          BLUE                                ;
wire  [7 : 0]                          GREEN                               ;
wire                                   frame_init                          ;
wire                                   LCD_end                             ;       

/***********************************************************************************************
//    register declaration block for module configuration
***********************************************************************************************/  
reg                                    overlay_enable_load                ;


/***********************************************************************************************
//    register declaration block for LCD data, sync signal
***********************************************************************************************/  
reg                                    IF_GO                               ;
reg                                    LCD_IF_VSYNC_rising_d1              ;
reg                                    LCD_IF_VSYNC_falling_d1             ;   // one clock delayed signal of LCD_IF_VSYNC


/***********************************************************************************************
//    
//    block for Simple Wire Interconnect    
//                                                    
***********************************************************************************************/
/***********************************************************************************************
//    Wire Interconnect block for clock, reset, PLL/MMCM lock signal
***********************************************************************************************/
assign      LCD_IF_pclk_out             =  LCD_IF_pclk_in        ;

/***********************************************************************************************
//    Wire Interconnect block for LCD pixel data
***********************************************************************************************/
assign      LCD_IF_pdata                =  ((overlay_pixel_data  == synced_color_key) && overlay_enable_load) ? `RGB565_to_RGB24(origin_pixel_data) 
                                                                                            : (overlay_enable_load ? `RGB565_to_RGB24(overlay_pixel_data) 
                                                                                            : `RGB565_to_RGB24(origin_pixel_data));

/***********************************************************************************************
//    Wire Interconnect block for FIFO control
***********************************************************************************************/
assign      ori_buffer_rd_clk                = LCD_IF_pclk_in                                                              ;
assign      ovr_buffer_rd_clk                = LCD_IF_pclk_in                                                              ;
assign      ori_buffer_rd_en                 = ALL_buffer_rd_en                                                            ;
assign      ovr_buffer_rd_en                 = ALL_buffer_rd_en & overlay_enable_load                                     ;
assign      ALL_buffer_prog_empty            = ori_buffer_prog_empty | (ovr_buffer_prog_empty & overlay_enable_load)      ;
assign      ALL_buffer_zero_empty            = ori_buffer_zero_empty | (ovr_buffer_zero_empty & overlay_enable_load)      ;
assign      frame_init                       = (~LCD_IF_VSYNC_rising_d1) & (LCD_IF_VSYNC)                                  ;
assign      LCD_end                          = (LCD_IF_VSYNC_falling_d1) & (~LCD_IF_VSYNC);


/***********************************************************************************************
//                                                                                              
//    block for CDC                                                                             
//                                                                                              
***********************************************************************************************/        
/***********************************************************************************************
//    CDC block for reset
***********************************************************************************************/                     
xpm_cdc_async_rst #(
   .DEST_SYNC_FF              (4                         ),    
   .INIT_SYNC_FF              (0                         ),    
   .RST_ACTIVE_HIGH           (1                         )  
)  
CDC_reset_sync_2_IF_clk       (
   .dest_arst                 (rst_sync_to_pclk          ),
   .dest_clk                  (LCD_IF_pclk_in            ),
   .src_arst                  (module_rst                )
);


/***********************************************************************************************
//    CDC block for overlay_enable
***********************************************************************************************/
xpm_cdc_async_rst #(
 .DEST_SYNC_FF                (4),   
 .INIT_SYNC_FF                (0),   
 .RST_ACTIVE_HIGH             (0) 
)
CDC_reset_from_overlay_enable_to_overlay_enable_sync
(
 .src_arst                    (overlay_enable),   				
 .dest_clk                    (LCD_IF_pclk_in),       			
 .dest_arst                   (overlay_enable_sync)  			
);
/***********************************************************************************************
//    CDC block for color key
***********************************************************************************************/       
xpm_cdc_array_single #(
   .DEST_SYNC_FF              (4                         ),   				
   .INIT_SYNC_FF              (0                         ),   				
   .SIM_ASSERT_CHK            (0                         ), 				
   .SRC_INPUT_REG             (1                         ),  				
   .WIDTH                     (16                        )           				
)
CDC_data_from_color_key_to_synced_color_key
(
   .src_clk                   (regi_clk                  ),        		
   .src_in                    (color_key                 ),    			
   .dest_clk                  (LCD_IF_pclk_in            ), 
   .dest_out                  (synced_color_key          )  	
);


/***********************************************************************************************
//                                                                                              
//    block for IP Instance                                                                     
//                                                                                              
***********************************************************************************************/  
/***********************************************************************************************
//    block for LCD sync signal generator
***********************************************************************************************/ 
pattern_gen_LCD_IF #(
   .Tvw                       (Tvw                       ),
   .Tvbp                      (Tvbp                      ),
   .Tvfp                      (Tvfp                      ),
   .Tvdw                      (Tvdw                      ),
   .Thw                       (Thw                       ),
   .Thbp                      (Thbp                      ),
   .Thfp                      (Thfp                      ),
   .Thdw                      (Thdw                      )
)u_pattern_gen_lcd
(                            
   .clk                       (LCD_IF_pclk_in            ),
   .rstb                      (IF_GO                     ),                     
   .pat_vs                    (LCD_IF_VSYNC              ),
   .pat_hs                    (LCD_IF_HSYNC              ),
   .pat_de                    (LCD_IF_DE                 ),
   .pat_load_en               (ALL_buffer_rd_en          )
);


/***********************************************************************************************
//                                                                                              
//    block for excution                                                                        
//                                                                                              
***********************************************************************************************/
/***********************************************************************************************
//    block for finding rising edge of LCD_IF_VSYNC
***********************************************************************************************/
always @(posedge LCD_IF_pclk_in) begin
   if(rst_sync_to_pclk) begin
      LCD_IF_VSYNC_rising_d1 <= 0;
   end
   else begin
      LCD_IF_VSYNC_rising_d1 <= LCD_IF_VSYNC;
   end
end 

/***********************************************************************************************
//    block for finding falling edge of LCD_IF_VSYNC
***********************************************************************************************/

always @(posedge LCD_IF_pclk_in) begin
   if(rst_sync_to_pclk) begin
      LCD_IF_VSYNC_falling_d1 <= 1;
   end
   else begin
      LCD_IF_VSYNC_falling_d1 <= LCD_IF_VSYNC;
   end
end 

/***********************************************************************************************
//    block for overlay_enable register
***********************************************************************************************/
always @(posedge LCD_IF_pclk_in) begin
   if(rst_sync_to_pclk) begin
      overlay_enable_load <= 0;
   end
   else begin
      if(frame_init | LCD_end) begin
         if(overlay_enable_sync) begin
            overlay_enable_load <= 1;
         end
         else begin
            overlay_enable_load <= 0;
         end
      end
   end
end 


/***********************************************************************************************
//    block for LCD interface enable. 
//    If buffer has data enough, LCD IF is ON
***********************************************************************************************/
always @(posedge LCD_IF_pclk_in) begin
   if(rst_sync_to_pclk) begin
      IF_GO <= 0;
   end else if((!ALL_buffer_prog_empty))begin
      IF_GO <= 1;
   end
   else if(ALL_buffer_zero_empty & LCD_end) begin
      IF_GO <= 0;
   end
end 






endmodule // FIFO_to_LCD_IF end