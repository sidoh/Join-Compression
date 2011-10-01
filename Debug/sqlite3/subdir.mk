################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../sqlite3/CppSQLite3.cpp 

OBJS += \
./sqlite3/CppSQLite3.o 

CPP_DEPS += \
./sqlite3/CppSQLite3.d 


# Each subdirectory must supply rules for building sources it contributes
sqlite3/CppSQLite3.o: ../sqlite3/CppSQLite3.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include -I"/Users/mullins/Documents/workspace/Join-Compression/sqlite3" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"sqlite3/CppSQLite3.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


