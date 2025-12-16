onbreak {quit -force}
onerror {quit -force}

asim -t 1ps +access +r +m+PS -L xilinx_vip -L xpm -L xil_defaultlib -L fifo_generator_v13_2_5 -L xilinx_vip -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.PS xil_defaultlib.glbl

do {wave.do}

view wave
view structure

do {PS.udo}

run -all

endsim

quit -force
