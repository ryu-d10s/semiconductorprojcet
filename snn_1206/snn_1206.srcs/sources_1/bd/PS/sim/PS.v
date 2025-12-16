//Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
//Date        : Thu Dec 11 00:10:50 2025
//Host        : IT23-JS running 64-bit major release  (build 9200)
//Command     : generate_target PS.bd
//Design      : PS
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "PS,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=PS,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=4,numReposBlks=4,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,da_board_cnt=4,da_clkrst_cnt=4,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "PS.hwdef" *) 
module PS
   (reset_rtl,
    reset_rtl_0,
    sys_clock);
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.RESET_RTL RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.RESET_RTL, INSERT_VIP 0, POLARITY ACTIVE_HIGH" *) input reset_rtl;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.RESET_RTL_0 RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.RESET_RTL_0, INSERT_VIP 0, POLARITY ACTIVE_HIGH" *) input reset_rtl_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.SYS_CLOCK CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.SYS_CLOCK, CLK_DOMAIN PS_sys_clock, FREQ_HZ 100000000, INSERT_VIP 0, PHASE 0.000" *) input sys_clock;

  wire CAM_mclk_GEN_CAM_mclk;
  wire reset_rtl_0_1;
  wire reset_rtl_1;
  wire sys_clock_1;

  assign reset_rtl_0_1 = reset_rtl_0;
  assign reset_rtl_1 = reset_rtl;
  assign sys_clock_1 = sys_clock;
  PS_clk_wiz_0_0 CAM_mclk_GEN
       (.CAM_mclk(CAM_mclk_GEN_CAM_mclk),
        .clk_in1(sys_clock_1),
        .reset(reset_rtl_1));
  PS_fifo_generator_0_1 CAM_pdata_sync_FIFO
       (.din({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .rd_clk(CAM_mclk_GEN_CAM_mclk),
        .rd_en(1'b0),
        .rst(1'b0),
        .wr_clk(CAM_mclk_GEN_CAM_mclk),
        .wr_en(1'b0));
  PS_fifo_generator_0_0 LCD_pdata_FIFO
       (.din({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .rd_clk(CAM_mclk_GEN_CAM_mclk),
        .rd_en(1'b0),
        .rst(1'b0),
        .wr_clk(CAM_mclk_GEN_CAM_mclk),
        .wr_en(1'b0));
  PS_clk_wiz_0_1 SYS_clk_GEN
       (.clk_in1(sys_clock_1),
        .reset(reset_rtl_0_1));
endmodule
