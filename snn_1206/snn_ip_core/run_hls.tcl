############################################################
# Vitis HLS TCL Script for SNN IP Core
# Target: Zynq-7000 (xc7z020clg400-1)
# Clock: 100MHz (10ns)
############################################################

# Create new project
open_project -reset snn_ip_project

# Set top function
set_top snn_ip

# Add design files
add_files snn_ip.cpp
add_files snn_ip.h
add_files snn_weights.h

# Add testbench files
add_files -tb testbench.cpp

# Create solution
open_solution -reset "solution1"

# Set target device (Zynq-7020)
set_part {xc7z020clg400-1}

# Set clock period (10ns = 100MHz)
create_clock -period 10 -name default

# Configuration settings
config_compile -name_max_length 256
config_compile -pipeline_loops 64

# RTL configuration
config_rtl -reset all -reset_async

# Interface configuration
config_interface -m_axi_latency 64
config_interface -m_axi_alignment_byte_size 64
config_interface -m_axi_max_widen_bitwidth 512

############################################################
# Run C Simulation
############################################################
puts "=========================================="
puts "Running C Simulation..."
puts "=========================================="
csim_design -clean

############################################################
# Run C Synthesis
############################################################
puts "=========================================="
puts "Running C Synthesis..."
puts "=========================================="
csynth_design

############################################################
# Run C/RTL Co-simulation (Optional - commented out for faster build)
############################################################
# puts "=========================================="
# puts "Running C/RTL Co-simulation..."
# puts "=========================================="
# cosim_design -rtl verilog -trace_level all

############################################################
# Export RTL Design (IP Packaging)
############################################################
puts "=========================================="
puts "Exporting RTL as IP..."
puts "=========================================="
export_design -rtl verilog -format ip_catalog -description "Lightweight SNN IP Core" -vendor "user" -library "snn" -version "1.0" -display_name "SNN_IP"

############################################################
# Generate Reports
############################################################
puts "=========================================="
puts "HLS Synthesis Complete!"
puts "=========================================="
puts ""
puts "Reports generated in:"
puts "  - snn_ip_project/solution1/syn/report/"
puts ""
puts "IP package exported to:"
puts "  - snn_ip_project/solution1/impl/ip/"
puts ""
puts "Key metrics to check:"
puts "  1. Latency (cycles)"
puts "  2. Resource utilization (BRAM, DSP, FF, LUT)"
puts "  3. Clock frequency achieved"
puts ""

# Exit Vitis HLS
exit
