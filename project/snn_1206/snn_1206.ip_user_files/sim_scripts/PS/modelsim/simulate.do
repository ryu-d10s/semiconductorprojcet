onbreak {quit -f}
onerror {quit -f}

vsim -voptargs="+acc" -t 1ps -L xilinx_vip -L xpm -L xil_defaultlib -L fifo_generator_v13_2_5 -L xilinx_vip -L unisims_ver -L unimacro_ver -L secureip -lib xil_defaultlib xil_defaultlib.PS xil_defaultlib.glbl

do {wave.do}

view wave
view structure
view signals

do {PS.udo}

run -all

quit -force
