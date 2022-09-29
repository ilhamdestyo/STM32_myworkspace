################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/GPIO.c \
../Src/i2c.c \
../Src/main.c \
../Src/myclock.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/GPIO.o \
./Src/i2c.o \
./Src/main.o \
./Src/myclock.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/GPIO.d \
./Src/i2c.d \
./Src/main.d \
./Src/myclock.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DSTM32F103x6 -c -I../Inc -I"/home/lime/Documents/STM32CubeIDE/myWorkspace/Proj_STM32F103C6_I2C_cobaregister/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/home/lime/Documents/STM32CubeIDE/myWorkspace/Proj_STM32F103C6_I2C_cobaregister/Drivers/CMSIS/Core/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/GPIO.d ./Src/GPIO.o ./Src/GPIO.su ./Src/i2c.d ./Src/i2c.o ./Src/i2c.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/myclock.d ./Src/myclock.o ./Src/myclock.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

