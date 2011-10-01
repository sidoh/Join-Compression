################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/sparsehash-1.11/experimental/example.c \
../lib/sparsehash-1.11/experimental/libchash.c 

OBJS += \
./lib/sparsehash-1.11/experimental/example.o \
./lib/sparsehash-1.11/experimental/libchash.o 

C_DEPS += \
./lib/sparsehash-1.11/experimental/example.d \
./lib/sparsehash-1.11/experimental/libchash.d 


# Each subdirectory must supply rules for building sources it contributes
lib/sparsehash-1.11/experimental/%.o: ../lib/sparsehash-1.11/experimental/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/usr/include -I"/Users/mullins/Documents/workspace/Join-Compression/sqlite3" -I"/Users/mullins/Documents/workspace/Join-Compression/lib/sparsehash-1.11/src" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


