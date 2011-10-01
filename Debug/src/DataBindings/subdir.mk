################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataBindings/JoinTable.cpp \
../src/DataBindings/Row.cpp \
../src/DataBindings/SQLite3RowBuilder.cpp \
../src/DataBindings/SQLite3Table.cpp 

OBJS += \
./src/DataBindings/JoinTable.o \
./src/DataBindings/Row.o \
./src/DataBindings/SQLite3RowBuilder.o \
./src/DataBindings/SQLite3Table.o 

CPP_DEPS += \
./src/DataBindings/JoinTable.d \
./src/DataBindings/Row.d \
./src/DataBindings/SQLite3RowBuilder.d \
./src/DataBindings/SQLite3Table.d 


# Each subdirectory must supply rules for building sources it contributes
src/DataBindings/%.o: ../src/DataBindings/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include -I"../sqlite3" -I"../src/DataBindings" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/DataBindings/Row.o: ../src/DataBindings/Row.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include -I"../src/DataBindings" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/DataBindings/Row.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/DataBindings/SQLite3RowBuilder.o: ../src/DataBindings/SQLite3RowBuilder.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include -I"../sqlite3" -I"../src/DataBindings" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/DataBindings/SQLite3RowBuilder.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


