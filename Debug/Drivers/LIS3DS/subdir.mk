################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LIS3DS/lis3dsh.c 

OBJS += \
./Drivers/LIS3DS/lis3dsh.o 

C_DEPS += \
./Drivers/LIS3DS/lis3dsh.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LIS3DS/%.o Drivers/LIS3DS/%.su: ../Drivers/LIS3DS/%.c Drivers/LIS3DS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/cubeide_workspace/devf4/Drivers/SHT20" -I"D:/cubeide_workspace/devf4/Drivers/LIS3DS" -I"D:/cubeide_workspace/devf4/Drivers/DS3231" -I"D:/cubeide_workspace/devf4/Drivers/ILI9341/inc" -I"D:/cubeide_workspace/devf4/Drivers/EmWin/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-LIS3DS

clean-Drivers-2f-LIS3DS:
	-$(RM) ./Drivers/LIS3DS/lis3dsh.d ./Drivers/LIS3DS/lis3dsh.o ./Drivers/LIS3DS/lis3dsh.su

.PHONY: clean-Drivers-2f-LIS3DS

