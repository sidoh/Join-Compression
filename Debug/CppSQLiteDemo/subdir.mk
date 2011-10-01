################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CppSQLiteDemo/CppSQLite3Demo.cpp 

OBJS += \
./CppSQLiteDemo/CppSQLite3Demo.o 

CPP_DEPS += \
./CppSQLiteDemo/CppSQLite3Demo.d 


# Each subdirectory must supply rules for building sources it contributes
CppSQLiteDemo/CppSQLite3Demo.o: ../CppSQLiteDemo/CppSQLite3Demo.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/Users/mullins/Documents/workspace/Join-Compression/lib/sparsehash-1.11/src" -I/usr/include -I"/Users/mullins/Documents/workspace/Join-Compression/compression" -I"/Users/mullins/Documents/workspace/Join-Compression/CppSQLiteDemo" -I"/Users/mullins/Documents/workspace/Join-Compression/datastructures" -I"/Users/mullins/Documents/workspace/Join-Compression/sqlite3" -I"/Users/mullins/Documents/workspace/Join-Compression/src/DataBindings" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"CppSQLiteDemo/CppSQLite3Demo.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


