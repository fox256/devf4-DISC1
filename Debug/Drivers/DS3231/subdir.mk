################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DS3231/ds3231.c 

OBJS += \
./Drivers/DS3231/ds3231.o 

C_DEPS += \
./Drivers/DS3231/ds3231.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DS3231/%.o Drivers/DS3231/%.su: ../Drivers/DS3231/%.c Drivers/DS3231/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/cubeide_workspace/devf4/Drivers/SHT20" -I"D:/cubeide_workspace/devf4/Drivers/LIS3DS" -I"D:/cubeide_workspace/devf4/Drivers/DS3231" -I"D:/cubeide_workspace/devf4/Drivers/ILI9341/inc" -I"D:/cubeide_workspace/devf4/Drivers/EmWin/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-DS3231

clean-Drivers-2f-DS3231:
	-$(RM) ./Drivers/DS3231/ds3231.d ./Drivers/DS3231/ds3231.o ./Drivers/DS3231/ds3231.su

.PHONY: clean-Drivers-2f-DS3231

