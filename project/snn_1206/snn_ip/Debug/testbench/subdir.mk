################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/snn_1206/snn_ip_core/testbench.cpp 

OBJS += \
./testbench/testbench.o 

CPP_DEPS += \
./testbench/testbench.d 


# Each subdirectory must supply rules for building sources it contributes
testbench/testbench.o: C:/snn_1206/snn_ip_core/testbench.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -IC:/snn_1206 -IC:/Xilinx/Vivado/2019.2/include -IC:/Xilinx/Vivado/2019.2/include/etc -IC:/Xilinx/Vivado/2019.2/win64/tools/systemc/include -IC:/Xilinx/Vivado/2019.2/include/ap_sysc -IC:/Xilinx/Vivado/2019.2/win64/tools/auto_cc/include -O0 -g3 -Wall -Wno-unknown-pragmas -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"testbench/testbench.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


