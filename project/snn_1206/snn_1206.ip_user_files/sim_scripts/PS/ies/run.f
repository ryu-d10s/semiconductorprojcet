-makelib ies_lib/xilinx_vip -sv \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/rst_vip_if.sv" \
-endlib
-makelib ies_lib/xpm -sv \
  "C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
-endlib
-makelib ies_lib/xpm \
  "C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/PS/ip/PS_clk_wiz_0_0/PS_clk_wiz_0_0_clk_wiz.v" \
  "../../../bd/PS/ip/PS_clk_wiz_0_0/PS_clk_wiz_0_0.v" \
  "../../../bd/PS/ip/PS_clk_wiz_0_1/PS_clk_wiz_0_1_clk_wiz.v" \
  "../../../bd/PS/ip/PS_clk_wiz_0_1/PS_clk_wiz_0_1.v" \
-endlib
-makelib ies_lib/fifo_generator_v13_2_5 \
  "../../../../snn_1206.srcs/sources_1/bd/PS/ipshared/276e/simulation/fifo_generator_vlog_beh.v" \
-endlib
-makelib ies_lib/fifo_generator_v13_2_5 \
  "../../../../snn_1206.srcs/sources_1/bd/PS/ipshared/276e/hdl/fifo_generator_v13_2_rfs.vhd" \
-endlib
-makelib ies_lib/fifo_generator_v13_2_5 \
  "../../../../snn_1206.srcs/sources_1/bd/PS/ipshared/276e/hdl/fifo_generator_v13_2_rfs.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/PS/ip/PS_fifo_generator_0_0/sim/PS_fifo_generator_0_0.v" \
  "../../../bd/PS/ip/PS_fifo_generator_0_1/sim/PS_fifo_generator_0_1.v" \
  "../../../bd/PS/sim/PS.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  glbl.v
-endlib

