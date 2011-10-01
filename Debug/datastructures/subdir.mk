################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../datastructures/IndexDictionary.cpp \
../datastructures/StringDictionary.cpp 

OBJS += \
./datastructures/IndexDictionary.o \
./datastructures/StringDictionary.o 

CPP_DEPS += \
./datastructures/IndexDictionary.d \
./datastructures/StringDictionary.d 


# Each subdirectory must supply rules for building sources it contributes
datastructures/%.o: ../datastructures/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"../lib/sparsehash-1.11/src" -I/usr/include -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


