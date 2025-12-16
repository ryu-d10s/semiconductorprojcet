connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-SMT2NC 210308BA4DDE" && level==0} -index 1
fpga -file C:/snn_1206/snn_dma_app_1208/_ide/bitstream/design_1_wrapper_1208.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/snn_1206/design_1_wrapper_1208/export/design_1_wrapper_1208/hw/design_1_wrapper_1208.xsa -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/snn_1206/snn_dma_app_1208/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/snn_1206/snn_dma_app_1208/Debug/snn_dma_app_1208.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
