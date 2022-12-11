################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../inc/sken_lib/Enc.cpp \
../inc/sken_lib/Motor.cpp \
../inc/sken_lib/PS3.cpp 

OBJS += \
./inc/sken_lib/Enc.o \
./inc/sken_lib/Motor.o \
./inc/sken_lib/PS3.o 

CPP_DEPS += \
./inc/sken_lib/Enc.d \
./inc/sken_lib/Motor.d \
./inc/sken_lib/PS3.d 


# Each subdirectory must supply rules for building sources it contributes
inc/sken_lib/%.o: ../inc/sken_lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_HAL_DRIVER -I"C:/Users/Owner/asobi/HAL_Driver/Inc/Legacy" -I"C:/Users/Owner/asobi/Utilities/STM32F4xx-Nucleo" -I"C:/Users/Owner/asobi/inc" -I"C:/Users/Owner/asobi/CMSIS/device" -I"C:/Users/Owner/asobi/CMSIS/core" -I"C:/Users/Owner/asobi/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


