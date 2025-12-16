onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib PS_opt

do {wave.do}

view wave
view structure
view signals

do {PS.udo}

run -all

quit -force
