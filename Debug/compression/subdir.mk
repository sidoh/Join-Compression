################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../compression/BigInt.cpp \
../compression/ColumnDictionaryEntry.cpp \
../compression/CompressedRowIterator.cpp \
../compression/Compressor.cpp \
../compression/DictionaryDefinition.cpp \
../compression/EncodedFileHeader.cpp \
../compression/IndexEntry.cpp \
../compression/InnerDictionaryEntry.cpp \
../compression/LeafDictionaryEntry.cpp 

OBJS += \
./compression/BigInt.o \
./compression/ColumnDictionaryEntry.o \
./compression/CompressedRowIterator.o \
./compression/Compressor.o \
./compression/DictionaryDefinition.o \
./compression/EncodedFileHeader.o \
./compression/IndexEntry.o \
./compression/InnerDictionaryEntry.o \
./compression/LeafDictionaryEntry.o 

CPP_DEPS += \
./compression/BigInt.d \
./compression/ColumnDictionaryEntry.d \
./compression/CompressedRowIterator.d \
./compression/Compressor.d \
./compression/DictionaryDefinition.d \
./compression/EncodedFileHeader.d \
./compression/IndexEntry.d \
./compression/InnerDictionaryEntry.d \
./compression/LeafDictionaryEntry.d 


# Each subdirectory must supply rules for building sources it contributes
compression/%.o: ../compression/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include -I"/Users/mullins/Documents/workspace/Join-Compression/datastructures" -I"/Users/mullins/Documents/workspace/Join-Compression/src/DataBindings" -I"/Users/mullins/Documents/workspace/Join-Compression/compression" -I"/Users/mullins/Documents/workspace/Join-Compression/lib/sparsehash-1.11/src" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


