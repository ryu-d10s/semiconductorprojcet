vlib work
vlib activehdl

vlib activehdl/xilinx_vip
vlib activehdl/xpm
vlib activehdl/xil_defaultlib
vlib activehdl/fifo_generator_v13_2_5

vmap xilinx_vip activehdl/xilinx_vip
vmap xpm activehdl/xpm
vmap xil_defaultlib activehdl/xil_defaultlib
vmap fifo_generator_v13_2_5 activehdl/fifo_generator_v13_2_5

vlog -work xilinx_vip  -sv2k12 "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -sv2k12 "+incdir+../../../../snn_1206.srcs/sources_1/bd/PS/ipshared/4fba" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \

vcom -work xpm -93 \
"C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../snn_1206.srcs/sources_1/bd/PS/ipshared/4fba" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/PS/ip/PS_clk_wiz_0_0/PS_clk_wiz_0_0_clk_wiz.v" \
"../../../bd/PS/ip/PS_clk_wiz_0_0/PS_clk_wiz_0_0.v" \
"../../../bd/PS/ip/PS_clk_wiz_0_1/PS_clk_wiz_0_1_clk_wiz.v" \
"../../../bd/PS/ip/PS_clk_wiz_0_1/PS_clk_wiz_0_1.v" \

vlog -work fifo_generator_v13_2_5  -v2k5 "+incdir+../../../../snn_1206.srcs/sources_1/bd/PS/ipshared/4fba" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../snn_1206.srcs/sources_1/bd/PS/ipshared/276e/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_5 -93 \
"../../../../snn_1206.srcs/sources_1/bd/PS/ipshared/276e/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_5  -v2k5 "+incdir+../../../../snn_1206.srcs/sources_1/bd/PS/ipshared/4fba" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../snn_1206.srcs/sources_1/bd/PS/ipshared/276e/hdl/fifo_generator_v13_2_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../snn_1206.srcs/sources_1/bd/PS/ipshared/4fba" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/PS/ip/PS_fifo_generator_0_0/sim/PS_fifo_generator_0_0.v" \
"../../../bd/PS/ip/PS_fifo_generator_0_1/sim/PS_fifo_generator_0_1.v" \
"../../../bd/PS/sim/PS.v" \

vlog -work xil_defaultlib \
"glbl.v"

