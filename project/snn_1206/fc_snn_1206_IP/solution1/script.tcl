############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project fc_snn_1206_IP
set_top fc_snn_top
add_files weights.h
add_files fc_snn_top.cpp
add_files -tb tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xc7z020-clg484-1}
create_clock -period 10ns -name default
config_export -format ip_catalog -rtl verilog
#source "./fc_snn_1206_IP/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
