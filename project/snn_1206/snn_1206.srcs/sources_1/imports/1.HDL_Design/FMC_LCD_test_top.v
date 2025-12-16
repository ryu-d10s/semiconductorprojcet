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
-- IP Name       : FMC_LCD_test_top
-- IP Revision   :                                                         
-- File Name     : FMC_LCD_test_top.v
-- File Revision : 1.0                                                     
-- Date          : 2020/04/27
-- Tool Version  : Xilinx Vivado 2019.2                                    
-- Authors       : Libertron R&D Center, THYoon                            
-- IP Revision History                                                     
-- 2020/04/27 : start            
-- 2020/05/06 : 전체 design 재설계
-- 2020/07/13 : refine                                  
-------------------------------------------------------------------------*/
`timescale 1ns/ 100ps

module FMC_LCD_test_top
#(
   /***********************************************************************************************
   //    parameter for camera configuration
   ***********************************************************************************************/
   parameter IMG_HSIZE                       =  1920        ,
   parameter IMG_VSIZE                       =  1080        ,
   parameter CAM_BIT_WIDTH                   =  10          ,


   /***********************************************************************************************
   //    parameter for LCD configuration
   ***********************************************************************************************/
   parameter LCD_IMG_HSIZE                   =  800         ,
   parameter LCD_IMG_VSIZE                   =  480         ,
   parameter LCD_BPP                         =  16          ,
   parameter LCD_Tvw                         =  12'd10      , // VSYNC Pulse Width
   parameter LCD_Tvbp                        =  12'd23      , // VSYNC Back Porch
   parameter LCD_Tvfp                        =  12'd22      , // Vertical Front Porch
   parameter LCD_Tvdw                        =  12'd480     , // Vertical valid data width
   parameter LCD_Thw                         =  12'd20      , // HSYNC Pulse Width        
   parameter LCD_Thbp                        =  12'd46      , // HSYNC Back Porch         
   parameter LCD_Thfp                        =  12'd210     , // Horizontal Front Porch     
   parameter LCD_Thdw                        =  12'd800     , // Horizontal valid data width
   parameter LCD_BIT_WIDTH                   =  24          ,


   /***********************************************************************************************
   //    parameter for AXI interface configuration
   ***********************************************************************************************/
   parameter M_AXI_ADDR_WIDTH	               =  32          ,
   parameter M_AXI_DATA_WIDTH	               =  32          ,
   parameter MAXIMUM_BURST_LEN               =  16          

) // parameter list end
( // IO port list start

   /***********************************************************************************************
   //    input block for clock, reset
   ***********************************************************************************************/
   // input    wire                                   CLK_125_P               ,  // use for ULTRON or differential clock
   // input    wire                                   CLK_125_N               ,  // use for ULTRON or differential clock
   input    wire                                   clk_from_pad            , // clock from device pad, single end.
   input    wire                                   rst_btn                 , // entire PL logic reset signal from device pad, Active High.


   /***********************************************************************************************
   //    I/O block for camera data and control 
   ***********************************************************************************************/
   input    wire     [CAM_BIT_WIDTH - 1 : 0]       CAM_data_in             ,
   input    wire                                   CAM_pclk_in             ,
   input    wire                                   CAM_HSYNC_in            ,
   input    wire                                   CAM_VSYNC_in            ,
   //input    wire                                   CAM_de_in               ,     // CAM_de_in is replaced by {CAM_HSYNC_in && CAM_VSYNC_in}
   output   wire                                   CAM_rstb                ,
   output   wire                                   CAM_stdby               ,
   output   wire                                   CAM_mclk                ,
   inout    wire                                   CAM_I2C_scl             ,
   inout    wire                                   CAM_I2C_sda             ,


   /***********************************************************************************************
   //    I/O block for LCD interface and LCD control
   ***********************************************************************************************/
   output   wire     [LCD_BIT_WIDTH  - 1 : 0]      LCD_IF_pdata_out        ,
   output   wire                                   LCD_IF_HSYNC_out        ,
   output   wire                                   LCD_IF_VSYNC_out        ,
   output   wire                                   LCD_IF_DE_out           ,
   output   wire                                   LCD_IF_pclk_out         ,
   output   wire                                   LCD_rstb                ,
   output   wire                                   LCD_mode                ,
   output   wire                                   LCD_shlr                ,
   output   wire                                   LCD_updn                ,
   output   wire                                   LCD_dith                ,
   output   wire                                   LCD_W_LED_en            ,
   output   wire                                   LCD_W_LED_ctrl          ,
   output   wire                                   LCD_DRV_ctrl            ,


   /***********************************************************************************************
   //    I/O block for touch sensor control
   ***********************************************************************************************/
   output   wire                                   Touch_rstb              ,
   inout    wire                                   Touch_Intr              ,
   inout    wire                                   Touch_I2C_scl           ,
   inout    wire                                   Touch_I2C_sda           ,

   /***********************************************************************************************
   //    I/O block for PMOD 
   ***********************************************************************************************/
   inout    wire  [7:0]                            PMOD_A_tri_io           ,
   inout    wire  [7:0]                            PMOD_B_tri_io              
); // IO port list end


/***********************************************************************************************
//
//    block for Local Parameter, function, macro Declaration              
//                      
***********************************************************************************************/


/***********************************************************************************************
//
//    block for Register / Wire Declaration            
//                                         
***********************************************************************************************/
/***********************************************************************************************
//    Declaration block for clock, reset, PLL/MMCM lock signal
***********************************************************************************************/
wire                    PS_GEN_rstb                                     ;           // Reset signal from PS instance. Active low
wire                    PS_GEN_rst                                      ;           // Reset signal from PS instance. Active high
wire                    clk_buffered                                    ;           // Clock buffer(BUFG) output.
wire                    PL_clk                                          ;           // PL logic clock.
wire                    LCD_clk                                         ;           // LCD pixel clock, 33.3333 MHz
wire                    CAM_mclk_lock                                   ;           // PLL for camera mclk is locked
wire                    SYS_clk_lock                                    ;           // PLL for PL clk and LCD clk is locked
wire                    clk_lock                                        ;           // = CAM_mclk_lock & SYS_clk_lock
wire                    DCM_lock                                        ;           // = clk_lock
wire                    CAM_rst_req                                     ;           // Camera rst signal generate enable signal. This signal is NOT connected to camera sensor's rstb, but connected to reset signal generator(Cam_Rst_Gen).
                                                                                    // If this signal is asserted then Cam_Rst_Gen generate 3ms rstb signal for camera sensor. Active High 


/***********************************************************************************************
//    Declaration block for camera input data FIFO connection
***********************************************************************************************/
wire  [15:0]            CAM_FIFO_wr_data                                ;
wire                    CAM_FIFO_wr_en                                  ;
wire                    CAM_FIFO_wr_clk                                 ;


/***********************************************************************************************
//    Declaration block for module control, Status signal
***********************************************************************************************/
wire                    odd_even_write                                  ;           // 0 : Odd frame buffer is in writting, 1 : Even frame buffer is in writting.
wire                    overlay_enable                                  ;           // Active High
wire                    LCD_en                                          ;           // Active High
wire                    CAM_en                                          ;           // Active High
wire     [23:0]         output_left_top_coord                           ;           // output_left_top_coord[23 : 12] : X coord, output_left_top_coord[11 : 0] : Y coord
wire     [31:0]         origin_even_frame_addr                          ;           // Double frame buffer address for camera image. Fix this value before assert LCD_en / CAM_en
wire     [31:0]         origin_odd_frame_addr                           ;           // Double frame buffer address for camera image. Fix this value before assert LCD_en / CAM_en
wire     [31:0]         overlay_even_frame_addr                         ;           // Double frame buffer address for overlay image. Fix this value before assert LCD_en / CAM_en
wire     [31:0]         overlay_odd_frame_addr                          ;           // Double frame buffer address for overlay image. Fix this value before assert LCD_en / CAM_en
wire     [31:0]         Setting                                         ;           // Setting value of submodule.
wire     [31:0]         Status                                          ;           // Status of submodule.
wire                    CAM_rst_seq_done                                ;           // If camera reset sequence is done, this signal is asserted.
wire     [15:0]         Color_key                                       ;           // RGB565 overlay color key
wire                    HSYNC_lock                                      ;           // HSYNC lock
wire                    Frame_lock                                      ;           // Frame lock

/***********************************************************************************************
//    Declaration block for LCD pixel data FIFO connection
***********************************************************************************************/
wire  [31:0]            LCD_camera_image_FIFO_data                      ;
wire                    LCD_camera_image_FIFO_wr_clk                    ;
wire                    LCD_camera_image_FIFO_wr_en                     ;
wire                    LCD_camera_image_FIFO_prog_full                 ;
wire                    LCD_camera_image_FIFO_rst                       ;
wire                    LCD_camera_image_FIFO_rst_synced                ;
wire  [15 : 0]          origin_pixel_data                               ;
wire                    ori_buffer_rd_en                                ;
wire                    ori_buffer_rd_clk                               ;
wire                    ori_buffer_prog_empty                           ;
wire                    ori_buffer_zero_empty                           ;
wire  [31:0]            LCD_overlay_image_FIFO_data                     ;
wire                    LCD_overlay_image_FIFO_wr_clk                   ;
wire                    LCD_overlay_image_FIFO_wr_en                    ;
wire                    LCD_overlay_image_FIFO_prog_full                ;
wire                    LCD_overlay_image_FIFO_rst                      ;
wire                    LCD_overlay_image_FIFO_rst_synced               ;
wire  [15 : 0]          overlay_pixel_data                              ;
wire                    ovr_buffer_rd_en                                ;
wire                    ovr_buffer_rd_clk                               ;
wire                    ovr_buffer_prog_empty                           ;
wire                    ovr_buffer_zero_empty                           ;


/***********************************************************************************************
//    Declaration block for AXI interface.
//    AXI_RAM_PORT_1 : Transmit the camera pixel data from camera FIFO to DDR in the PS, and transmit the LCD original data from DDR in the PS to LCD FIFO.
***********************************************************************************************/
wire     [31:0]         AXI_RAM_PORT_1_araddr                           ;
wire     [1:0]          AXI_RAM_PORT_1_arburst                          ;
wire     [3:0]          AXI_RAM_PORT_1_arcache                          ;
wire     [5:0]          AXI_RAM_PORT_1_arid                             ;
wire     [3:0]          AXI_RAM_PORT_1_arlen                            ;
wire                    AXI_RAM_PORT_1_arlock                           ;
wire     [2:0]          AXI_RAM_PORT_1_arprot                           ;
wire     [3:0]          AXI_RAM_PORT_1_arqos                            ;
wire                    AXI_RAM_PORT_1_arready                          ;
wire     [2:0]          AXI_RAM_PORT_1_arsize                           ;
wire                    AXI_RAM_PORT_1_arvalid                          ;
wire     [31:0]         AXI_RAM_PORT_1_awaddr                           ;
wire     [1:0]          AXI_RAM_PORT_1_awburst                          ;
wire     [3:0]          AXI_RAM_PORT_1_awcache                          ;
wire     [5:0]          AXI_RAM_PORT_1_awid                             ;
wire     [3:0]          AXI_RAM_PORT_1_awlen                            ;
wire     [1:0]          AXI_RAM_PORT_1_awlock                           ;
wire     [2:0]          AXI_RAM_PORT_1_awprot                           ;
wire     [3:0]          AXI_RAM_PORT_1_awqos                            ;
wire                    AXI_RAM_PORT_1_awready                          ;
wire     [2:0]          AXI_RAM_PORT_1_awsize                           ;
wire                    AXI_RAM_PORT_1_awvalid                          ;
wire     [5:0]          AXI_RAM_PORT_1_bid                              ;
wire                    AXI_RAM_PORT_1_bready                           ;
wire     [1:0]          AXI_RAM_PORT_1_bresp                            ;
wire                    AXI_RAM_PORT_1_bvalid                           ;
wire     [31:0]         AXI_RAM_PORT_1_rdata                            ;
wire     [5:0]          AXI_RAM_PORT_1_rid                              ;
wire                    AXI_RAM_PORT_1_rlast                            ;
wire                    AXI_RAM_PORT_1_rready                           ;
wire     [1:0]          AXI_RAM_PORT_1_rresp                            ;
wire                    AXI_RAM_PORT_1_rvalid                           ;
wire     [31:0]         AXI_RAM_PORT_1_wdata                            ;
wire     [5:0]          AXI_RAM_PORT_1_wid                              ;
wire                    AXI_RAM_PORT_1_wlast                            ;
wire                    AXI_RAM_PORT_1_wready                           ;
wire     [3:0]          AXI_RAM_PORT_1_wstrb                            ;
wire                    AXI_RAM_PORT_1_wvalid                           ;


/***********************************************************************************************
//    Declaration block for AXI interface.
//    AXI_RAM_PORT_2 : Transmit LCD overlay data from DDR in PS to LCD FIFO.
***********************************************************************************************/
wire     [31:0]         AXI_RAM_PORT_2_araddr                           ;
wire     [1:0]          AXI_RAM_PORT_2_arburst                          ;
wire     [3:0]          AXI_RAM_PORT_2_arcache                          ;
wire     [5:0]          AXI_RAM_PORT_2_arid                             ;
wire     [3:0]          AXI_RAM_PORT_2_arlen                            ;
wire                    AXI_RAM_PORT_2_arlock                           ;
wire     [2:0]          AXI_RAM_PORT_2_arprot                           ;
wire     [3:0]          AXI_RAM_PORT_2_arqos                            ;
wire                    AXI_RAM_PORT_2_arready                          ;
wire     [2:0]          AXI_RAM_PORT_2_arsize                           ;
wire                    AXI_RAM_PORT_2_arvalid                          ;
wire     [31:0]         AXI_RAM_PORT_2_awaddr                           ;
wire     [1:0]          AXI_RAM_PORT_2_awburst                          ;
wire     [3:0]          AXI_RAM_PORT_2_awcache                          ;
wire     [5:0]          AXI_RAM_PORT_2_awid                             ;
wire     [3:0]          AXI_RAM_PORT_2_awlen                            ;
wire     [1:0]          AXI_RAM_PORT_2_awlock                           ;
wire     [2:0]          AXI_RAM_PORT_2_awprot                           ;
wire     [3:0]          AXI_RAM_PORT_2_awqos                            ;
wire                    AXI_RAM_PORT_2_awready                          ;
wire     [2:0]          AXI_RAM_PORT_2_awsize                           ;
wire                    AXI_RAM_PORT_2_awvalid                          ;
wire     [5:0]          AXI_RAM_PORT_2_bid                              ;
wire                    AXI_RAM_PORT_2_bready                           ;
wire     [1:0]          AXI_RAM_PORT_2_bresp                            ;
wire                    AXI_RAM_PORT_2_bvalid                           ;
wire     [31:0]         AXI_RAM_PORT_2_rdata                            ;
wire     [5:0]          AXI_RAM_PORT_2_rid                              ;
wire                    AXI_RAM_PORT_2_rlast                            ;
wire                    AXI_RAM_PORT_2_rready                           ;
wire     [1:0]          AXI_RAM_PORT_2_rresp                            ;
wire                    AXI_RAM_PORT_2_rvalid                           ;
wire     [31:0]         AXI_RAM_PORT_2_wdata                            ;
wire     [5:0]          AXI_RAM_PORT_2_wid                              ;
wire                    AXI_RAM_PORT_2_wlast                            ;
wire                    AXI_RAM_PORT_2_wready                           ;
wire     [3:0]          AXI_RAM_PORT_2_wstrb                            ;
wire                    AXI_RAM_PORT_2_wvalid                           ;


/***********************************************************************************************
//    Declaration block for AXI interface.
//    AXI_CAM_PORT_1 : Transmit camera data. Directly connected to AXI_RAM_PORT_1.
***********************************************************************************************/
wire     [31:0]         AXI_CAM_PORT_1_awaddr                           ;
wire     [1:0]          AXI_CAM_PORT_1_awburst                          ;
wire     [3:0]          AXI_CAM_PORT_1_awcache                          ;
wire     [5:0]          AXI_CAM_PORT_1_awid                             ;
wire     [3:0]          AXI_CAM_PORT_1_awlen                            ;
wire     [1:0]          AXI_CAM_PORT_1_awlock                           ;
wire     [2:0]          AXI_CAM_PORT_1_awprot                           ;
wire     [3:0]          AXI_CAM_PORT_1_awqos                            ;
wire                    AXI_CAM_PORT_1_awready                          ;
wire     [2:0]          AXI_CAM_PORT_1_awsize                           ;
wire                    AXI_CAM_PORT_1_awvalid                          ;
wire     [5:0]          AXI_CAM_PORT_1_bid                              ;
wire                    AXI_CAM_PORT_1_bready                           ;
wire     [1:0]          AXI_CAM_PORT_1_bresp                            ;
wire                    AXI_CAM_PORT_1_bvalid                           ;
wire     [31:0]         AXI_CAM_PORT_1_wdata                            ;
wire     [5:0]          AXI_CAM_PORT_1_wid                              ;
wire                    AXI_CAM_PORT_1_wlast                            ;
wire                    AXI_CAM_PORT_1_wready                           ;
wire     [3:0]          AXI_CAM_PORT_1_wstrb                            ;
wire                    AXI_CAM_PORT_1_wvalid                           ;


/***********************************************************************************************
//    Declaration block for AXI interface.
//    AXI_LCD_ORI_PORT_1 : Transmit LCD original data. Directly connected to AXI_RAM_PORT_1.
***********************************************************************************************/
wire     [31:0]         AXI_LCD_ORI_PORT_1_araddr                       ;
wire     [1:0]          AXI_LCD_ORI_PORT_1_arburst                      ;
wire     [3:0]          AXI_LCD_ORI_PORT_1_arcache                      ;
wire     [5:0]          AXI_LCD_ORI_PORT_1_arid                         ;
wire     [3:0]          AXI_LCD_ORI_PORT_1_arlen                        ;
wire                    AXI_LCD_ORI_PORT_1_arlock                       ;
wire     [2:0]          AXI_LCD_ORI_PORT_1_arprot                       ;
wire     [3:0]          AXI_LCD_ORI_PORT_1_arqos                        ;
wire                    AXI_LCD_ORI_PORT_1_arready                      ;
wire     [2:0]          AXI_LCD_ORI_PORT_1_arsize                       ;
wire                    AXI_LCD_ORI_PORT_1_arvalid                      ;
wire     [31:0]         AXI_LCD_ORI_PORT_1_rdata                        ;
wire     [5:0]          AXI_LCD_ORI_PORT_1_rid                          ;
wire                    AXI_LCD_ORI_PORT_1_rlast                        ;
wire                    AXI_LCD_ORI_PORT_1_rready                       ;
wire     [1:0]          AXI_LCD_ORI_PORT_1_rresp                        ;
wire                    AXI_LCD_ORI_PORT_1_rvalid                       ;


/***********************************************************************************************
//    Declaration block for AXI interface.
//    AXI_LCD_OVR_PORT_2 : Transmit LCD overlay data. Directly connected to AXI_RAM_PORT_2.
***********************************************************************************************/
wire     [31:0]         AXI_LCD_OVR_PORT_2_araddr                       ;
wire     [1:0]          AXI_LCD_OVR_PORT_2_arburst                      ;
wire     [3:0]          AXI_LCD_OVR_PORT_2_arcache                      ;
wire     [5:0]          AXI_LCD_OVR_PORT_2_arid                         ;
wire     [3:0]          AXI_LCD_OVR_PORT_2_arlen                        ;
wire                    AXI_LCD_OVR_PORT_2_arlock                       ;
wire     [2:0]          AXI_LCD_OVR_PORT_2_arprot                       ;
wire     [3:0]          AXI_LCD_OVR_PORT_2_arqos                        ;
wire                    AXI_LCD_OVR_PORT_2_arready                      ;
wire     [2:0]          AXI_LCD_OVR_PORT_2_arsize                       ;
wire                    AXI_LCD_OVR_PORT_2_arvalid                      ;
wire     [31:0]         AXI_LCD_OVR_PORT_2_rdata                        ;
wire     [5:0]          AXI_LCD_OVR_PORT_2_rid                          ;
wire                    AXI_LCD_OVR_PORT_2_rlast                        ;
wire                    AXI_LCD_OVR_PORT_2_rready                       ;
wire     [1:0]          AXI_LCD_OVR_PORT_2_rresp                        ;
wire                    AXI_LCD_OVR_PORT_2_rvalid                       ;



/***********************************************************************************************
//    
//    block for Simple Wire Interconnect    
//                                                    
***********************************************************************************************/
/***********************************************************************************************
//    Wire Interconnect block for clock, reset, PLL/MMCM lock signal
***********************************************************************************************/
assign      clk_lock                   = CAM_mclk_lock & SYS_clk_lock   ;
assign      DCM_lock                   = clk_lock                       ;


/***********************************************************************************************
//    Wire Interconnect block for submodule control and Status signal
***********************************************************************************************/
assign      Status[0 : 0]              =  CAM_rst_seq_done              ;
assign      Status[1 : 1]              =  odd_even_write                ;
assign      Status[2 : 2]              =  HSYNC_lock                    ;           
assign      Status[3 : 3]              =  Frame_lock                    ; 

assign      CAM_rst_req                =  Setting[14 : 14]              ;

assign      overlay_enable             =  Setting[13 : 13]              ;
assign      LCD_en                     =  Setting[11 : 11]              ;
assign      CAM_en                     =  Setting[9  :  9]              ;
assign      Touch_rstb                 =  Setting[8  :  8]              ;

assign      LCD_rstb                   =  Setting[7  :  7]              ;
assign      LCD_mode                   =  Setting[6  :  6]              ;
assign      LCD_shlr                   =  Setting[5  :  5]              ;
assign      LCD_updn                   =  Setting[4  :  4]              ;

assign      LCD_dith                   =  Setting[3  :  3]              ;
assign      LCD_W_LED_en               =  Setting[2  :  2]              ;
assign      LCD_W_LED_ctrl             =  Setting[1  :  1]              ;
assign      LCD_DRV_ctrl               =  Setting[0  :  0]              ;


/***********************************************************************************************
//    Wire Interconnect block for AXI_RAM_PORT_1
***********************************************************************************************/
assign      AXI_RAM_PORT_1_awaddr      =  AXI_CAM_PORT_1_awaddr         ;
assign      AXI_RAM_PORT_1_awburst     =  AXI_CAM_PORT_1_awburst        ;
assign      AXI_RAM_PORT_1_awcache     =  AXI_CAM_PORT_1_awcache        ;
assign      AXI_RAM_PORT_1_awid        =  AXI_CAM_PORT_1_awid           ;
assign      AXI_RAM_PORT_1_awlen       =  AXI_CAM_PORT_1_awlen          ;
assign      AXI_RAM_PORT_1_awlock      =  AXI_CAM_PORT_1_awlock         ;
assign      AXI_RAM_PORT_1_awprot      =  AXI_CAM_PORT_1_awprot         ;
assign      AXI_RAM_PORT_1_awqos       =  AXI_CAM_PORT_1_awqos          ;
assign      AXI_RAM_PORT_1_awsize      =  AXI_CAM_PORT_1_awsize         ;
assign      AXI_RAM_PORT_1_awvalid     =  AXI_CAM_PORT_1_awvalid        ;
assign      AXI_RAM_PORT_1_bid         =  AXI_CAM_PORT_1_bid            ;
assign      AXI_RAM_PORT_1_bready      =  AXI_CAM_PORT_1_bready         ;
assign      AXI_RAM_PORT_1_bresp       =  AXI_CAM_PORT_1_bresp          ;
assign      AXI_RAM_PORT_1_wdata       =  AXI_CAM_PORT_1_wdata          ;
assign      AXI_RAM_PORT_1_wid         =  AXI_CAM_PORT_1_wid            ;
assign      AXI_RAM_PORT_1_wlast       =  AXI_CAM_PORT_1_wlast          ;
assign      AXI_RAM_PORT_1_wstrb       =  AXI_CAM_PORT_1_wstrb          ;
assign      AXI_RAM_PORT_1_wvalid      =  AXI_CAM_PORT_1_wvalid         ;
assign      AXI_CAM_PORT_1_awready     =  AXI_RAM_PORT_1_awready        ;
assign      AXI_CAM_PORT_1_bvalid      =  AXI_RAM_PORT_1_bvalid         ;
assign      AXI_CAM_PORT_1_wready      =  AXI_RAM_PORT_1_wready         ;
assign      AXI_RAM_PORT_1_araddr      =  AXI_LCD_ORI_PORT_1_araddr     ;
assign      AXI_RAM_PORT_1_arburst     =  AXI_LCD_ORI_PORT_1_arburst    ;
assign      AXI_RAM_PORT_1_arcache     =  AXI_LCD_ORI_PORT_1_arcache    ;
assign      AXI_RAM_PORT_1_arid        =  AXI_LCD_ORI_PORT_1_arid       ;
assign      AXI_RAM_PORT_1_arlen       =  AXI_LCD_ORI_PORT_1_arlen      ;
assign      AXI_RAM_PORT_1_arlock      =  AXI_LCD_ORI_PORT_1_arlock     ;
assign      AXI_RAM_PORT_1_arprot      =  AXI_LCD_ORI_PORT_1_arprot     ;
assign      AXI_RAM_PORT_1_arqos       =  AXI_LCD_ORI_PORT_1_arqos      ;
assign      AXI_RAM_PORT_1_arsize      =  AXI_LCD_ORI_PORT_1_arsize     ;
assign      AXI_RAM_PORT_1_arvalid     =  AXI_LCD_ORI_PORT_1_arvalid    ;
assign      AXI_RAM_PORT_1_rready      =  AXI_LCD_ORI_PORT_1_rready     ;
assign      AXI_LCD_ORI_PORT_1_arready =  AXI_RAM_PORT_1_arready        ;
assign      AXI_LCD_ORI_PORT_1_rdata   =  AXI_RAM_PORT_1_rdata          ;
assign      AXI_LCD_ORI_PORT_1_rid     =  AXI_RAM_PORT_1_rid            ;
assign      AXI_LCD_ORI_PORT_1_rlast   =  AXI_RAM_PORT_1_rlast          ;
assign      AXI_LCD_ORI_PORT_1_rresp   =  AXI_RAM_PORT_1_rresp          ;
assign      AXI_LCD_ORI_PORT_1_rvalid  =  AXI_RAM_PORT_1_rvalid         ;



/***********************************************************************************************
//    Wire Interconnect block for AXI_RAM_PORT_2
***********************************************************************************************/
assign      AXI_RAM_PORT_2_araddr      =  AXI_LCD_OVR_PORT_2_araddr     ;
assign      AXI_RAM_PORT_2_arburst     =  AXI_LCD_OVR_PORT_2_arburst    ;
assign      AXI_RAM_PORT_2_arcache     =  AXI_LCD_OVR_PORT_2_arcache    ;
assign      AXI_RAM_PORT_2_arid        =  AXI_LCD_OVR_PORT_2_arid       ;
assign      AXI_RAM_PORT_2_arlen       =  AXI_LCD_OVR_PORT_2_arlen      ;
assign      AXI_RAM_PORT_2_arlock      =  AXI_LCD_OVR_PORT_2_arlock     ;
assign      AXI_RAM_PORT_2_arprot      =  AXI_LCD_OVR_PORT_2_arprot     ;
assign      AXI_RAM_PORT_2_arqos       =  AXI_LCD_OVR_PORT_2_arqos      ;
assign      AXI_RAM_PORT_2_arsize      =  AXI_LCD_OVR_PORT_2_arsize     ;
assign      AXI_RAM_PORT_2_arvalid     =  AXI_LCD_OVR_PORT_2_arvalid    ;
assign      AXI_RAM_PORT_2_rready      =  AXI_LCD_OVR_PORT_2_rready     ;
assign      AXI_LCD_OVR_PORT_2_arready =  AXI_RAM_PORT_2_arready        ;
assign      AXI_LCD_OVR_PORT_2_rdata   =  AXI_RAM_PORT_2_rdata          ;
assign      AXI_LCD_OVR_PORT_2_rid     =  AXI_RAM_PORT_2_rid            ;
assign      AXI_LCD_OVR_PORT_2_rlast   =  AXI_RAM_PORT_2_rlast          ;
assign      AXI_LCD_OVR_PORT_2_rresp   =  AXI_RAM_PORT_2_rresp          ;
assign      AXI_LCD_OVR_PORT_2_rvalid  =  AXI_RAM_PORT_2_rvalid         ;


/***********************************************************************************************
//                                                                                              
//    block for CDC                                                                             
//                                                                                              
***********************************************************************************************/
/***********************************************************************************************
//    block for FIFO reset
***********************************************************************************************/
xpm_cdc_async_rst #  (
 .DEST_SYNC_FF       (4                                     ),    			
 .INIT_SYNC_FF       (0                                     ),    			
 .RST_ACTIVE_HIGH    (1                                     )  			
)
CDC_reset_from_LCD_camera_image_FIFO_rst_to_LCD_camera_image_FIFO_rst_synced
(
 .src_arst           (LCD_camera_image_FIFO_rst             ),   	
 .dest_clk           (ori_buffer_rd_clk                     ),       			
 .dest_arst          (LCD_camera_image_FIFO_rst_synced      )
);

xpm_cdc_async_rst #  (
 .DEST_SYNC_FF       (4                                     ),    			
 .INIT_SYNC_FF       (0                                     ),    			
 .RST_ACTIVE_HIGH    (1                                     )  			
)
CDC_reset_from_LCD_overlay_image_FIFO_rst_to_LCD_overlay_image_FIFO_rst_synced
(
 .src_arst           (LCD_overlay_image_FIFO_rst            ),   	
 .dest_clk           (ovr_buffer_rd_clk                     ),       			
 .dest_arst          (LCD_overlay_image_FIFO_rst_synced     )
);


/***********************************************************************************************
//
//    block for IP Instance                                                                     
//
***********************************************************************************************/
/***********************************************************************************************
//    block for clock tree
//    for ULTRON  :  125 P/N -> IBUFDS -> BUFG -> PLLs
//    for ZSK     :  clk_from_pad -> BUFG -> PLLs
***********************************************************************************************/
// wire single_end_clk;
// IBUFDS IBUFDS_inst
// (
//    .O             (single_end_clk   ),
//    .I             (CLK_125_P        ),
//    .IB            (CLK_125_N        )
// );
// BUFG clk_input_buffer 
// (
//    .I             (single_end_clk   ),
//    .O             (clk_buffered     )
// );

BUFG clk_input_buffer 
(
   .I             (clk_from_pad     ),
   .O             (clk_buffered     )
);

CAM_mclk_GEN CAM_mclk_generator
(
   .clk_in        (clk_buffered     ),
   .reset         (rst_btn          ), 
   .CAM_mclk      (CAM_mclk         ),     
   .locked        (CAM_mclk_lock    ) 
); 

SYS_clk_GEN SYS_clk_generator
(
   .clk_in        (clk_buffered     ),
   .reset         (rst_btn          ),
   .PL_clk        (PL_clk           ),
   .LCD_clk       (LCD_clk          ),
   .locked        (SYS_clk_lock     )
);   


/***********************************************************************************************
//    Transfer the camera data to AXI interface.
***********************************************************************************************/
CAM_IF_to_FIFO#(
   .IMG_HSIZE                    (1920                               ),
   .IMG_VSIZE                    (1080                               ),
   .CAM_BIT_WIDTH                (10                                 )                                                      
) // parameter list end
CAM_FIFO_writer
( // IO port list start
   .regi_clk                     (PL_clk                             ),
   .rst_in                       (PS_GEN_rst                         ),
   .CAM_data_in                  (CAM_data_in                        ),
   .CAM_pclk_in                  (CAM_pclk_in                        ),
   .CAM_HSYNC_in                 (CAM_HSYNC_in                       ),
   .CAM_VSYNC_in                 (CAM_VSYNC_in                       ),
   .CAM_DE_in                    (CAM_HSYNC_in & CAM_VSYNC_in        ),
   .CAM_en                       (CAM_en                             ),
   .frame_lock                   (Frame_lock                         ),
   .HSYNC_lock                   (HSYNC_lock                         ),
   .FIFO_wr_data                 (CAM_FIFO_wr_data                   ),
   .FIFO_wr_en                   (CAM_FIFO_wr_en                     ),
   .FIFO_wr_clk                  (CAM_FIFO_wr_clk                    )
); // IO port list end


FIFO_to_AXI#(
   .IMG_HSIZE                    (1920                               ),
   .IMG_VSIZE                    (1080                               ),
   .MAXIMUM_BURST_LEN            (16                                 ),
   .M_AXI_ADDR_WIDTH	            (32                                 ),
   .M_AXI_DATA_WIDTH	            (32                                 )
) // parameter list end
CAM_FIFO_reader
( // IO port list start
   .regi_clk                     (PL_clk                             ),
   .module_rst_in                (~CAM_en                            ),
   .odd_frame_addr_in            (origin_odd_frame_addr              ),
   .even_frame_addr_in           (origin_even_frame_addr             ),
   .odd_even_write               (odd_even_write                     ),
   .m_axi_data_aclk              (PL_clk                             ),
   .m_axi_data_aresetn           (PS_GEN_rstb                        ),
   .m_axi_data_awaddr            (AXI_CAM_PORT_1_awaddr              ), 
   .m_axi_data_awburst           (AXI_CAM_PORT_1_awburst             ), 
   .m_axi_data_awcache           (AXI_CAM_PORT_1_awcache             ), 
   .m_axi_data_awid              (AXI_CAM_PORT_1_awid                ), 
   .m_axi_data_awlen             (AXI_CAM_PORT_1_awlen               ), 
   .m_axi_data_awlock            (AXI_CAM_PORT_1_awlock              ), 
   .m_axi_data_awprot            (AXI_CAM_PORT_1_awprot              ), 
   .m_axi_data_awqos             (AXI_CAM_PORT_1_awqos               ), 
   .m_axi_data_awready           (AXI_CAM_PORT_1_awready             ), 
   .m_axi_data_awsize            (AXI_CAM_PORT_1_awsize              ), 
   .m_axi_data_awvalid           (AXI_CAM_PORT_1_awvalid             ), 
   .m_axi_data_wdata             (AXI_CAM_PORT_1_wdata               ), 
   .m_axi_data_wid               (AXI_CAM_PORT_1_wid                 ), 
   .m_axi_data_wlast             (AXI_CAM_PORT_1_wlast               ), 
   .m_axi_data_wready            (AXI_CAM_PORT_1_wready              ), 
   .m_axi_data_wstrb             (AXI_CAM_PORT_1_wstrb               ), 
   .m_axi_data_wvalid            (AXI_CAM_PORT_1_wvalid              ), 
   .m_axi_data_bready            (AXI_CAM_PORT_1_bready              ), 
   .m_axi_data_bvalid            (AXI_CAM_PORT_1_bvalid              ), 
   .FIFO_wr_data                 (CAM_FIFO_wr_data                   ),
   .FIFO_wr_en                   (CAM_FIFO_wr_en                     ),
   .FIFO_wr_clk                  (CAM_FIFO_wr_clk                    )
); // IO port list end


/***********************************************************************************************
//    block for read LCD pixel data from DDR RAM, write to FIFO
***********************************************************************************************/
AXI_to_FIFO#(
   .IMG_HSIZE                    (1920                               ),
   .IMG_VSIZE                    (1080                               ),
   .OUTPUT_IMG_HSIZE             (800                                ),
   .OUTPUT_IMG_VSIZE             (480                                ),
   .SYNC_FORCE_TO_CAM            (1                                  ),                
   .M_AXI_ADDR_WIDTH	            (32                                 ),
   .M_AXI_DATA_WIDTH	            (32                                 ),
   .MAXIMUM_BURST_LEN            (16                                 )

) // parameter list end
CAM_IMAGE_READER
( // IO port list start
   .m_axi_aclk                   (PL_clk                             ),
   .m_axi_aresetn                (PS_GEN_rstb                        ),
   .odd_even_write               (!odd_even_write                     ),
   .double_frame_buffer_odd_addr (origin_odd_frame_addr              ),
   .double_frame_buffer_even_addr(origin_even_frame_addr             ),
   .output_left_top_coord_x      (output_left_top_coord[23 : 12]     ),
   .output_left_top_coord_y      (output_left_top_coord[11 : 0]      ),
   .module_enable                (LCD_en                             ),
   .m_axi_data_araddr            (AXI_LCD_ORI_PORT_1_araddr          ),
   .m_axi_data_arburst           (AXI_LCD_ORI_PORT_1_arburst         ),
   .m_axi_data_arcache           (AXI_LCD_ORI_PORT_1_arcache         ),
   .m_axi_data_arid              (AXI_LCD_ORI_PORT_1_arid            ),
   .m_axi_data_arlen             (AXI_LCD_ORI_PORT_1_arlen           ),
   .m_axi_data_arlock            (AXI_LCD_ORI_PORT_1_arlock          ),
   .m_axi_data_arprot            (AXI_LCD_ORI_PORT_1_arprot          ),
   .m_axi_data_arqos             (AXI_LCD_ORI_PORT_1_arqos           ),
   .m_axi_data_arready           (AXI_LCD_ORI_PORT_1_arready         ),
   .m_axi_data_arsize            (AXI_LCD_ORI_PORT_1_arsize          ),
   .m_axi_data_arvalid           (AXI_LCD_ORI_PORT_1_arvalid         ),
   .m_axi_data_rid               (AXI_LCD_ORI_PORT_1_rid             ),
   .m_axi_data_rlast             (AXI_LCD_ORI_PORT_1_rlast           ),
   .m_axi_data_rready            (AXI_LCD_ORI_PORT_1_rready          ),
   .m_axi_data_rdata             (AXI_LCD_ORI_PORT_1_rdata           ),
   .m_axi_data_rvalid            (AXI_LCD_ORI_PORT_1_rvalid          ),
   .m_axi_data_rresp             (AXI_LCD_ORI_PORT_1_rresp           ),
   .FIFO_data                    (LCD_camera_image_FIFO_data         ),
   .FIFO_wr_clk                  (LCD_camera_image_FIFO_wr_clk       ),
   .FIFO_wr_en                   (LCD_camera_image_FIFO_wr_en        ),
   .FIFO_prog_full               (LCD_camera_image_FIFO_prog_full    ),
   .module_rst_out               (LCD_camera_image_FIFO_rst          )
); // IO port list end

AXI_to_FIFO#(
   .IMG_HSIZE                    (1920                               ),
   .IMG_VSIZE                    (1080                               ),
   .OUTPUT_IMG_HSIZE             (800                                ),
   .OUTPUT_IMG_VSIZE             (480                                ),
   .SYNC_FORCE_TO_CAM            (1                                  ),                
   .M_AXI_ADDR_WIDTH	            (32                                 ),
   .M_AXI_DATA_WIDTH	            (32                                 ),
   .MAXIMUM_BURST_LEN            (16                                 )

) // parameter list end
OVR_IMAGE_READER
( // IO port list start
   .m_axi_aclk                   (PL_clk                             ),
   .m_axi_aresetn                (PS_GEN_rstb                        ),
   .odd_even_write               (!odd_even_write                     ),
   .double_frame_buffer_odd_addr (overlay_odd_frame_addr             ),
   .double_frame_buffer_even_addr(overlay_even_frame_addr            ),
   .output_left_top_coord_x      (output_left_top_coord[23 : 12]     ),
   .output_left_top_coord_y      (output_left_top_coord[11 : 0]      ),
   .module_enable                (overlay_enable & LCD_en            ),
   .m_axi_data_araddr            (AXI_LCD_OVR_PORT_2_araddr          ),
   .m_axi_data_arburst           (AXI_LCD_OVR_PORT_2_arburst         ),
   .m_axi_data_arcache           (AXI_LCD_OVR_PORT_2_arcache         ),
   .m_axi_data_arid              (AXI_LCD_OVR_PORT_2_arid            ),
   .m_axi_data_arlen             (AXI_LCD_OVR_PORT_2_arlen           ),
   .m_axi_data_arlock            (AXI_LCD_OVR_PORT_2_arlock          ),
   .m_axi_data_arprot            (AXI_LCD_OVR_PORT_2_arprot          ),
   .m_axi_data_arqos             (AXI_LCD_OVR_PORT_2_arqos           ),
   .m_axi_data_arready           (AXI_LCD_OVR_PORT_2_arready         ),
   .m_axi_data_arsize            (AXI_LCD_OVR_PORT_2_arsize          ),
   .m_axi_data_arvalid           (AXI_LCD_OVR_PORT_2_arvalid         ),
   .m_axi_data_rid               (AXI_LCD_OVR_PORT_2_rid             ),
   .m_axi_data_rlast             (AXI_LCD_OVR_PORT_2_rlast           ),
   .m_axi_data_rready            (AXI_LCD_OVR_PORT_2_rready          ),
   .m_axi_data_rdata             (AXI_LCD_OVR_PORT_2_rdata           ),
   .m_axi_data_rvalid            (AXI_LCD_OVR_PORT_2_rvalid          ),
   .m_axi_data_rresp             (AXI_LCD_OVR_PORT_2_rresp           ),
   .FIFO_data                    (LCD_overlay_image_FIFO_data        ),
   .FIFO_wr_clk                  (LCD_overlay_image_FIFO_wr_clk      ),
   .FIFO_wr_en                   (LCD_overlay_image_FIFO_wr_en       ),
   .FIFO_prog_full               (LCD_overlay_image_FIFO_prog_full   ),
   .module_rst_out               (LCD_overlay_image_FIFO_rst         )
); // IO port list end


/***********************************************************************************************
//    block for LCD pixel data FIFO
***********************************************************************************************/
LCD_pdata_FIFO CAM_frame_buffer  (
  .rst                           (LCD_camera_image_FIFO_rst_synced   ),
  .wr_clk                        (LCD_camera_image_FIFO_wr_clk       ),
  .rd_clk                        (ori_buffer_rd_clk                  ),
  .din                           (LCD_camera_image_FIFO_data         ),
  .wr_en                         (LCD_camera_image_FIFO_wr_en        ),
  .rd_en                         (ori_buffer_rd_en                   ),
  .dout                          (origin_pixel_data                  ),
  .empty                         (ori_buffer_zero_empty              ),
  .prog_full                     (LCD_camera_image_FIFO_prog_full    ),
  .prog_empty                    (ori_buffer_prog_empty              )
);

LCD_pdata_FIFO OVR_frame_buffer  (
  .rst                           (LCD_overlay_image_FIFO_rst_synced  ),
  .wr_clk                        (LCD_overlay_image_FIFO_wr_clk      ),
  .rd_clk                        (ovr_buffer_rd_clk                  ),
  .din                           (LCD_overlay_image_FIFO_data        ),
  .wr_en                         (LCD_overlay_image_FIFO_wr_en       ),
  .rd_en                         (ovr_buffer_rd_en                   ),
  .dout                          (overlay_pixel_data                 ),
  .empty                         (ovr_buffer_zero_empty              ),
  .prog_full                     (LCD_overlay_image_FIFO_prog_full   ),
  .prog_empty                    (ovr_buffer_prog_empty              )
);


/***********************************************************************************************
//    block for LCD interface control
***********************************************************************************************/
FIFO_to_LCD_IF#(
   .OUTPUT_BIT_WIDTH             (24                                 ),
   .Tvw                          (LCD_Tvw                            ), // VSYNC Pulse Width
   .Tvbp                         (LCD_Tvbp - LCD_Tvw                 ), // VSYNC Back Porch
   .Tvfp                         (LCD_Tvfp                           ), // Vertical Front Porch
   .Tvdw                         (LCD_Tvdw                           ), // Vertical valid data width
   .Thw                          (LCD_Thw                            ), // HSYNC Pulse Width        
   .Thbp                         (LCD_Thbp - LCD_Thw                 ), // HSYNC Back Porch         
   .Thfp                         (LCD_Thfp                           ), // Horizontal Front Porch     
   .Thdw                         (LCD_Thdw                           )  // Horizontal valid data width 
) // parameter list end
LCDC
( // IO port list start
   .regi_clk                     (PL_clk                             ),
   .module_rst                   (PS_GEN_rst                         ),
   .color_key                    (Color_key                          ),
   .overlay_enable               (overlay_enable & LCD_en            ),
   .LCD_IF_pclk_in               (LCD_clk                            ),
   .LCD_IF_pdata                 (LCD_IF_pdata_out                   ),
   .LCD_IF_HSYNC                 (LCD_IF_HSYNC_out                   ),
   .LCD_IF_VSYNC                 (LCD_IF_VSYNC_out                   ),
   .LCD_IF_DE                    (LCD_IF_DE_out                      ),
   .LCD_IF_pclk_out              (LCD_IF_pclk_out                    ),
   .origin_pixel_data            (origin_pixel_data                  ),
   .ori_buffer_rd_en             (ori_buffer_rd_en                   ),
   .ori_buffer_rd_clk            (ori_buffer_rd_clk                  ),
   .ori_buffer_prog_empty        (ori_buffer_prog_empty              ),
   .ori_buffer_zero_empty        (ori_buffer_zero_empty              ),
   .overlay_pixel_data           (overlay_pixel_data                 ),
   .ovr_buffer_rd_en             (ovr_buffer_rd_en                   ),
   .ovr_buffer_rd_clk            (ovr_buffer_rd_clk                  ),
   .ovr_buffer_prog_empty        (ovr_buffer_prog_empty              ),
   .ovr_buffer_zero_empty        (ovr_buffer_zero_empty              )

); // IO port list end


/***********************************************************************************************
//    block for camera reset signal generator
***********************************************************************************************/
CAM_rst_GEN #(
   .CAM_MCLK_SPEED_MHz(27)
) // parameter list end
camera_reset
( // IO port list start
   .clk                          (CAM_mclk                           ),
   .rst                          (CAM_rst_req | PS_GEN_rst           ),
   .m_axi_aclk                   (PL_clk                             ),
   .CAM_rst_seq_done             (CAM_rst_seq_done                   ),
   .CAM_rstb                     (CAM_rstb                           ),
   .CAM_stdby                    (CAM_stdby                          ),
   .PLL_lock                     (clk_lock                           )
); // IO port list end


/***********************************************************************************************
//    block for ULTRON_PS
//    vivado 2019.2 autogenerated
***********************************************************************************************/
PS_wrapper PS
(
   /****************************************************************/
   .CAM_I2C_scl_io               (CAM_I2C_scl                        ),
   .CAM_I2C_sda_io               (CAM_I2C_sda                        ),
   .CROP_COORD                   (output_left_top_coord              ),
   .DCM_lock                     (DCM_lock                           ),
   .ORI_BUFFER_ADDR_EVEN         (origin_even_frame_addr             ),
   .ORI_BUFFER_ADDR_ODD          (origin_odd_frame_addr              ),
   .OVR_BUFFER_ADDR_EVEN         (overlay_even_frame_addr            ),
   .OVR_BUFFER_ADDR_ODD          (overlay_odd_frame_addr             ),
   .Color_key                    (Color_key                          ),
   .PL_clk                       (PL_clk                             ),
   .PMOD_A_tri_io                (PMOD_A_tri_io                      ),
   .PMOD_B_tri_io                (PMOD_B_tri_io                      ),
   .PS_GEN_rst                   (PS_GEN_rst                         ),
   .PS_GEN_rstb                  (PS_GEN_rstb                        ),
   .Setting                      (Setting                            ),
   .Status                       (Status                             ),
   .Touch_I2C_scl_io             (Touch_I2C_scl                      ),
   .Touch_I2C_sda_io             (Touch_I2C_sda                      ),
   .Touch_Intr                   (Touch_Intr                         ),
   .rst                          (rst_btn                            ),
   /****************************************************************/
   // port for AXI interface
   .AXI_RAM_PORT_1_araddr        (AXI_RAM_PORT_1_araddr              ),
   .AXI_RAM_PORT_1_arburst       (AXI_RAM_PORT_1_arburst             ),
   .AXI_RAM_PORT_1_arcache       (AXI_RAM_PORT_1_arcache             ),
   .AXI_RAM_PORT_1_arid          (AXI_RAM_PORT_1_arid                ),
   .AXI_RAM_PORT_1_arlen         (AXI_RAM_PORT_1_arlen               ),
   .AXI_RAM_PORT_1_arlock        (AXI_RAM_PORT_1_arlock              ),
   .AXI_RAM_PORT_1_arprot        (AXI_RAM_PORT_1_arprot              ),
   .AXI_RAM_PORT_1_arqos         (AXI_RAM_PORT_1_arqos               ),
   .AXI_RAM_PORT_1_arready       (AXI_RAM_PORT_1_arready             ),
   .AXI_RAM_PORT_1_arsize        (AXI_RAM_PORT_1_arsize              ),
   .AXI_RAM_PORT_1_arvalid       (AXI_RAM_PORT_1_arvalid             ),
   .AXI_RAM_PORT_1_awaddr        (AXI_RAM_PORT_1_awaddr              ),
   .AXI_RAM_PORT_1_awburst       (AXI_RAM_PORT_1_awburst             ),
   .AXI_RAM_PORT_1_awcache       (AXI_RAM_PORT_1_awcache             ),
   .AXI_RAM_PORT_1_awid          (AXI_RAM_PORT_1_awid                ),
   .AXI_RAM_PORT_1_awlen         (AXI_RAM_PORT_1_awlen               ),
   .AXI_RAM_PORT_1_awlock        (AXI_RAM_PORT_1_awlock              ),
   .AXI_RAM_PORT_1_awprot        (AXI_RAM_PORT_1_awprot              ),
   .AXI_RAM_PORT_1_awqos         (AXI_RAM_PORT_1_awqos               ),
   .AXI_RAM_PORT_1_awready       (AXI_RAM_PORT_1_awready             ),
   .AXI_RAM_PORT_1_awsize        (AXI_RAM_PORT_1_awsize              ),
   .AXI_RAM_PORT_1_awvalid       (AXI_RAM_PORT_1_awvalid             ),
   .AXI_RAM_PORT_1_bid           (AXI_RAM_PORT_1_bid                 ),
   .AXI_RAM_PORT_1_bready        (AXI_RAM_PORT_1_bready              ),
   .AXI_RAM_PORT_1_bresp         (AXI_RAM_PORT_1_bresp               ),
   .AXI_RAM_PORT_1_bvalid        (AXI_RAM_PORT_1_bvalid              ),
   .AXI_RAM_PORT_1_rdata         (AXI_RAM_PORT_1_rdata               ),
   .AXI_RAM_PORT_1_rid           (AXI_RAM_PORT_1_rid                 ),
   .AXI_RAM_PORT_1_rlast         (AXI_RAM_PORT_1_rlast               ),
   .AXI_RAM_PORT_1_rready        (AXI_RAM_PORT_1_rready              ),
   .AXI_RAM_PORT_1_rresp         (AXI_RAM_PORT_1_rresp               ),
   .AXI_RAM_PORT_1_rvalid        (AXI_RAM_PORT_1_rvalid              ),
   .AXI_RAM_PORT_1_wdata         (AXI_RAM_PORT_1_wdata               ),
   .AXI_RAM_PORT_1_wid           (AXI_RAM_PORT_1_wid                 ),
   .AXI_RAM_PORT_1_wlast         (AXI_RAM_PORT_1_wlast               ),
   .AXI_RAM_PORT_1_wready        (AXI_RAM_PORT_1_wready              ),
   .AXI_RAM_PORT_1_wstrb         (AXI_RAM_PORT_1_wstrb               ),
   .AXI_RAM_PORT_1_wvalid        (AXI_RAM_PORT_1_wvalid              ),
   .AXI_RAM_PORT_2_araddr        (AXI_RAM_PORT_2_araddr              ),
   .AXI_RAM_PORT_2_arburst       (AXI_RAM_PORT_2_arburst             ),
   .AXI_RAM_PORT_2_arcache       (AXI_RAM_PORT_2_arcache             ),
   .AXI_RAM_PORT_2_arid          (AXI_RAM_PORT_2_arid                ),
   .AXI_RAM_PORT_2_arlen         (AXI_RAM_PORT_2_arlen               ),
   .AXI_RAM_PORT_2_arlock        (AXI_RAM_PORT_2_arlock              ),
   .AXI_RAM_PORT_2_arprot        (AXI_RAM_PORT_2_arprot              ),
   .AXI_RAM_PORT_2_arqos         (AXI_RAM_PORT_2_arqos               ),
   .AXI_RAM_PORT_2_arready       (AXI_RAM_PORT_2_arready             ),
   .AXI_RAM_PORT_2_arsize        (AXI_RAM_PORT_2_arsize              ),
   .AXI_RAM_PORT_2_arvalid       (AXI_RAM_PORT_2_arvalid             ),
   .AXI_RAM_PORT_2_awaddr        (AXI_RAM_PORT_2_awaddr              ),
   .AXI_RAM_PORT_2_awburst       (AXI_RAM_PORT_2_awburst             ),
   .AXI_RAM_PORT_2_awcache       (AXI_RAM_PORT_2_awcache             ),
   .AXI_RAM_PORT_2_awid          (AXI_RAM_PORT_2_awid                ),
   .AXI_RAM_PORT_2_awlen         (AXI_RAM_PORT_2_awlen               ),
   .AXI_RAM_PORT_2_awlock        (AXI_RAM_PORT_2_awlock              ),
   .AXI_RAM_PORT_2_awprot        (AXI_RAM_PORT_2_awprot              ),
   .AXI_RAM_PORT_2_awqos         (AXI_RAM_PORT_2_awqos               ),
   .AXI_RAM_PORT_2_awready       (AXI_RAM_PORT_2_awready             ),
   .AXI_RAM_PORT_2_awsize        (AXI_RAM_PORT_2_awsize              ),
   .AXI_RAM_PORT_2_awvalid       (AXI_RAM_PORT_2_awvalid             ),
   .AXI_RAM_PORT_2_bid           (AXI_RAM_PORT_2_bid                 ),
   .AXI_RAM_PORT_2_bready        (AXI_RAM_PORT_2_bready              ),
   .AXI_RAM_PORT_2_bresp         (AXI_RAM_PORT_2_bresp               ),
   .AXI_RAM_PORT_2_bvalid        (AXI_RAM_PORT_2_bvalid              ),
   .AXI_RAM_PORT_2_rdata         (AXI_RAM_PORT_2_rdata               ),
   .AXI_RAM_PORT_2_rid           (AXI_RAM_PORT_2_rid                 ),
   .AXI_RAM_PORT_2_rlast         (AXI_RAM_PORT_2_rlast               ),
   .AXI_RAM_PORT_2_rready        (AXI_RAM_PORT_2_rready              ),
   .AXI_RAM_PORT_2_rresp         (AXI_RAM_PORT_2_rresp               ),
   .AXI_RAM_PORT_2_rvalid        (AXI_RAM_PORT_2_rvalid              ),
   .AXI_RAM_PORT_2_wdata         (AXI_RAM_PORT_2_wdata               ),
   .AXI_RAM_PORT_2_wid           (AXI_RAM_PORT_2_wid                 ),
   .AXI_RAM_PORT_2_wlast         (AXI_RAM_PORT_2_wlast               ),
   .AXI_RAM_PORT_2_wready        (AXI_RAM_PORT_2_wready              ),
   .AXI_RAM_PORT_2_wstrb         (AXI_RAM_PORT_2_wstrb               ),
   .AXI_RAM_PORT_2_wvalid        (AXI_RAM_PORT_2_wvalid              ),
   /****************************************************************/
   // port for DDR, Fixed IO interface
   .DDR_addr                     (DDR_addr                           ),
   .DDR_ba                       (DDR_ba                             ),
   .DDR_cas_n                    (DDR_cas_n                          ),
   .DDR_ck_n                     (DDR_ck_n                           ),
   .DDR_ck_p                     (DDR_ck_p                           ),
   .DDR_cke                      (DDR_cke                            ),
   .DDR_cs_n                     (DDR_cs_n                           ),
   .DDR_dm                       (DDR_dm                             ),
   .DDR_dq                       (DDR_dq                             ),
   .DDR_dqs_n                    (DDR_dqs_n                          ),
   .DDR_dqs_p                    (DDR_dqs_p                          ),
   .DDR_odt                      (DDR_odt                            ),
   .DDR_ras_n                    (DDR_ras_n                          ),
   .DDR_reset_n                  (DDR_reset_n                        ),
   .DDR_we_n                     (DDR_we_n                           ),
   .FIXED_IO_ddr_vrn             (FIXED_IO_ddr_vrn                   ),
   .FIXED_IO_ddr_vrp             (FIXED_IO_ddr_vrp                   ),
   .FIXED_IO_mio                 (FIXED_IO_mio                       ),
   .FIXED_IO_ps_clk              (FIXED_IO_ps_clk                    ),
   .FIXED_IO_ps_porb             (FIXED_IO_ps_porb                   ),
   .FIXED_IO_ps_srstb            (FIXED_IO_ps_srstb                  )
);




endmodule // FMC_LCD_test_top end