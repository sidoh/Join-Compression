################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataBindings/tpch/TpchHelper.cpp 

OBJS += \
./src/DataBindings/tpch/TpchHelper.o 

CPP_DEPS += \
./src/DataBindings/tpch/TpchHelper.d 


# Each subdirectory must supply rules for building sources it contributes
src/DataBindings/tpch/%.o: ../src/DataBindings/tpch/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include -I"/Users/mullins/Documents/workspace/Join-Compression/src/DataBindings/tpch" -I"/Users/mullins/Documents/workspace/Join-Compression/sqlite3" -I"/Users/mullins/Documents/workspace/Join-Compression/src/DataBindings" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


