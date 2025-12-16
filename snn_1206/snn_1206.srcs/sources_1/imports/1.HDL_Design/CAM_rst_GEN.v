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
-- IP Name        : CAM_rst_GEN
-- IP Revision    :                                                         
-- File Name      : CAM_rst_GEN.v
-- File Revision  : 1.0                                                     
-- Date           : 2020/04/29 
-- Tool Version   : Xilinx Vivado 2019.2                                    
-- Authors        : Libertron R&D Center, THYoon                            
-- IP Revision History                                                     
-- 2020/04/29     : start                                                    
-------------------------------------------------------------------------*/

`timescale 1ns/ 100ps

module CAM_rst_GEN
#(
   parameter CAM_MCLK_SPEED_MHz   =  27
) // parameter list end
( // IO port list start
   input    wire        clk                  ,  // clock, sync with sysclk
   input    wire        rst                  ,  // IP reset signal, active high


   input    wire        m_axi_aclk           ,

   output   wire        CAM_rst_seq_done     ,  // power on sequence done signal, active high
   output   reg         CAM_rstb             ,  // camera reset signal, active low
   output   reg         CAM_stdby            ,  // camera standby signal, active high

   input    wire        PLL_lock       
); // IO port list end


// Local Parameter Declaration 
localparam ms_1  = CAM_MCLK_SPEED_MHz * 1000; // clock for 1ms 
localparam ms_2  = CAM_MCLK_SPEED_MHz * 1000; // clock for 1ms       
localparam ms_3  = CAM_MCLK_SPEED_MHz * 3000; // clock for 3ms
localparam ms_01 = CAM_MCLK_SPEED_MHz * 100; // clock for 0.1 ms


function integer clogb2 (input integer size);
begin
size = size - 1;
// increment clogb2 from 1 for each bit in size
for (clogb2 = 1; size > 1; clogb2 = clogb2 + 1)
   size = size >> 1;
end
endfunction // clogb2


// Register / Wire Declaration            
reg [clogb2(ms_3) - 1 : 0]       timer             ;
reg                              CAM_rst_seq_done_i    ;


// Simple Wire Interconnect


// CDC Block        


xpm_cdc_async_rst #        (
   .DEST_SYNC_FF           (4    ),   
   .INIT_SYNC_FF           (0    ),   
   .RST_ACTIVE_HIGH        (1    ) 
)
xpm_cdc_async_rst_inst     (
   .dest_arst              (i_rst            ), 
   .dest_clk               (clk              ),
   .src_arst               (rst              ) 
);


xpm_cdc_array_single #     (
   .DEST_SYNC_FF           (4                ),
   .INIT_SYNC_FF           (0                ),
   .SIM_ASSERT_CHK         (0                ),
   .SRC_INPUT_REG          (1                ),
   .WIDTH                  (1                ) 
)
CDC_CAM_rst_seq_done           (
   .dest_out               (CAM_rst_seq_done     ),
   .dest_clk               (m_axi_aclk       ),
   .src_clk                (clk              ),
   .src_in                 (CAM_rst_seq_done_i   )
);

// IP Instance                     


// excution Block              

////////////////////////////////////////////////////////////////////////////////////////////////
//
//    block for timer
//
////////////////////////////////////////////////////////////////////////////////////////////////
always @(posedge clk) begin
   if(i_rst) begin
      timer <= 0;
   end else if ((timer == (ms_3-1)) &&(PLL_lock)) begin
      timer <= timer;
   end else if(PLL_lock)  begin
      timer <= timer + 1;
   end
end 

////////////////////////////////////////////////////////////////////////////////////////////////
//
//    block for CAM_rstb. CAM_rstb assert 0.1 ms after cam_rst_latch is asserted
//
////////////////////////////////////////////////////////////////////////////////////////////////
always @(posedge clk) begin
   if(i_rst) begin
      CAM_rstb <= 0; // Note : CAM_rstb is active low signal
   end else if ((timer < ms_01) && (PLL_lock))begin
      CAM_rstb <= 0;
   end else if ((timer > ms_01) && (PLL_lock))begin
      CAM_rstb <= 1;
   end
end 

////////////////////////////////////////////////////////////////////////////////////////////////
//
//    block for standby signal
//
////////////////////////////////////////////////////////////////////////////////////////////////
always @(posedge clk) begin
   if(i_rst) begin
      CAM_stdby <= 0;
   end
end 

////////////////////////////////////////////////////////////////////////////////////////////////
//
//    block for pwr seq done signal
//
////////////////////////////////////////////////////////////////////////////////////////////////
always @(posedge clk) begin
   if(i_rst) begin
      CAM_rst_seq_done_i <= 0;
   end else if ((timer >= (ms_3-1)) && PLL_lock)begin
      CAM_rst_seq_done_i <= 1;
   end
end 


endmodule // CAM_rst_GEN end   