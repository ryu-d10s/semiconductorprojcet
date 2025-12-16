//Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
//Date        : Thu Dec 11 00:10:50 2025
//Host        : IT23-JS running 64-bit major release  (build 9200)
//Command     : generate_target PS_wrapper.bd
//Design      : PS_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module PS_wrapper
   (reset_rtl,
    reset_rtl_0,
    sys_clock);
  input reset_rtl;
  input reset_rtl_0;
  input sys_clock;

  wire reset_rtl;
  wire reset_rtl_0;
  wire sys_clock;

  PS PS_i
       (.reset_rtl(reset_rtl),
        .reset_rtl_0(reset_rtl_0),
        .sys_clock(sys_clock));
endmodule
