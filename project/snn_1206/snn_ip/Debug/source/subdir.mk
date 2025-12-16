################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/snn_1206/snn_ip_core/snn_ip.cpp 

OBJS += \
./source/snn_ip.o 

CPP_DEPS += \
./source/snn_ip.d 


# Each subdirectory must supply rules for building sources it contributes
source/snn_ip.o: C:/snn_1206/snn_ip_core/snn_ip.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -IC:/snn_1206 -IC:/Xilinx/Vivado/2019.2/include -IC:/Xilinx/Vivado/2019.2/include/etc -IC:/Xilinx/Vivado/2019.2/win64/tools/systemc/include -IC:/Xilinx/Vivado/2019.2/include/ap_sysc -IC:/Xilinx/Vivado/2019.2/win64/tools/auto_cc/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


