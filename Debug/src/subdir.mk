################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EasyDriver.cpp \
../src/LockCamera.cpp \
../src/LockState.cpp \
../src/SimpleGPIO.cpp \
../src/TestApplication.cpp 

OBJS += \
./src/EasyDriver.o \
./src/LockCamera.o \
./src/LockState.o \
./src/SimpleGPIO.o \
./src/TestApplication.o 

CPP_DEPS += \
./src/EasyDriver.d \
./src/LockCamera.d \
./src/LockState.d \
./src/SimpleGPIO.d \
./src/TestApplication.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-gnueabihf-g++ -I/usr/arm-linux-gnueabihf/include/c++/4.8.2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


