############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project snn_ip
set_top snn_ip
add_files snn_ip_core/snn_weights.h
add_files snn_ip_core/snn_ip.h
add_files snn_ip_core/snn_ip.cpp
add_files -tb snn_ip_core/testbench.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xc7z020-clg484-1}
create_clock -period 10ns -name default
config_export -format ip_catalog -rtl verilog
#source "./snn_ip/solution1/directives.tcl"
csim_design -setup
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
