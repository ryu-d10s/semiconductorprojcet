// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
// Date        : Mon Dec  8 17:49:52 2025
// Host        : IT23-JS running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/snn_1206/snn_1206.srcs/sources_1/bd/design_1/ip/design_1_snn_ip_0_4/design_1_snn_ip_0_4_stub.v
// Design      : design_1_snn_ip_0_4
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg484-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "snn_ip,Vivado 2019.2" *)
module design_1_snn_ip_0_4(s_axi_CTRL_AWADDR, s_axi_CTRL_AWVALID, 
  s_axi_CTRL_AWREADY, s_axi_CTRL_WDATA, s_axi_CTRL_WSTRB, s_axi_CTRL_WVALID, 
  s_axi_CTRL_WREADY, s_axi_CTRL_BRESP, s_axi_CTRL_BVALID, s_axi_CTRL_BREADY, 
  s_axi_CTRL_ARADDR, s_axi_CTRL_ARVALID, s_axi_CTRL_ARREADY, s_axi_CTRL_RDATA, 
  s_axi_CTRL_RRESP, s_axi_CTRL_RVALID, s_axi_CTRL_RREADY, ap_clk, ap_rst_n, interrupt, 
  in_stream_TVALID, in_stream_TREADY, in_stream_TDATA, in_stream_TDEST, in_stream_TKEEP, 
  in_stream_TSTRB, in_stream_TUSER, in_stream_TLAST, in_stream_TID, out_stream_TVALID, 
  out_stream_TREADY, out_stream_TDATA, out_stream_TDEST, out_stream_TKEEP, 
  out_stream_TSTRB, out_stream_TUSER, out_stream_TLAST, out_stream_TID)
/* synthesis syn_black_box black_box_pad_pin="s_axi_CTRL_AWADDR[3:0],s_axi_CTRL_AWVALID,s_axi_CTRL_AWREADY,s_axi_CTRL_WDATA[31:0],s_axi_CTRL_WSTRB[3:0],s_axi_CTRL_WVALID,s_axi_CTRL_WREADY,s_axi_CTRL_BRESP[1:0],s_axi_CTRL_BVALID,s_axi_CTRL_BREADY,s_axi_CTRL_ARADDR[3:0],s_axi_CTRL_ARVALID,s_axi_CTRL_ARREADY,s_axi_CTRL_RDATA[31:0],s_axi_CTRL_RRESP[1:0],s_axi_CTRL_RVALID,s_axi_CTRL_RREADY,ap_clk,ap_rst_n,interrupt,in_stream_TVALID,in_stream_TREADY,in_stream_TDATA[31:0],in_stream_TDEST[0:0],in_stream_TKEEP[3:0],in_stream_TSTRB[3:0],in_stream_TUSER[0:0],in_stream_TLAST[0:0],in_stream_TID[0:0],out_stream_TVALID,out_stream_TREADY,out_stream_TDATA[31:0],out_stream_TDEST[0:0],out_stream_TKEEP[3:0],out_stream_TSTRB[3:0],out_stream_TUSER[0:0],out_stream_TLAST[0:0],out_stream_TID[0:0]" */;
  input [3:0]s_axi_CTRL_AWADDR;
  input s_axi_CTRL_AWVALID;
  output s_axi_CTRL_AWREADY;
  input [31:0]s_axi_CTRL_WDATA;
  input [3:0]s_axi_CTRL_WSTRB;
  input s_axi_CTRL_WVALID;
  output s_axi_CTRL_WREADY;
  output [1:0]s_axi_CTRL_BRESP;
  output s_axi_CTRL_BVALID;
  input s_axi_CTRL_BREADY;
  input [3:0]s_axi_CTRL_ARADDR;
  input s_axi_CTRL_ARVALID;
  output s_axi_CTRL_ARREADY;
  output [31:0]s_axi_CTRL_RDATA;
  output [1:0]s_axi_CTRL_RRESP;
  output s_axi_CTRL_RVALID;
  input s_axi_CTRL_RREADY;
  input ap_clk;
  input ap_rst_n;
  output interrupt;
  input in_stream_TVALID;
  output in_stream_TREADY;
  input [31:0]in_stream_TDATA;
  input [0:0]in_stream_TDEST;
  input [3:0]in_stream_TKEEP;
  input [3:0]in_stream_TSTRB;
  input [0:0]in_stream_TUSER;
  input [0:0]in_stream_TLAST;
  input [0:0]in_stream_TID;
  output out_stream_TVALID;
  input out_stream_TREADY;
  output [31:0]out_stream_TDATA;
  output [0:0]out_stream_TDEST;
  output [3:0]out_stream_TKEEP;
  output [3:0]out_stream_TSTRB;
  output [0:0]out_stream_TUSER;
  output [0:0]out_stream_TLAST;
  output [0:0]out_stream_TID;
endmodule
