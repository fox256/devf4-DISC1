################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ILI9341/src/ILI9341.c \
../Drivers/ILI9341/src/ILI9341_GFX.c \
../Drivers/ILI9341/src/fonts.c 

OBJS += \
./Drivers/ILI9341/src/ILI9341.o \
./Drivers/ILI9341/src/ILI9341_GFX.o \
./Drivers/ILI9341/src/fonts.o 

C_DEPS += \
./Drivers/ILI9341/src/ILI9341.d \
./Drivers/ILI9341/src/ILI9341_GFX.d \
./Drivers/ILI9341/src/fonts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ILI9341/src/%.o Drivers/ILI9341/src/%.su: ../Drivers/ILI9341/src/%.c Drivers/ILI9341/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/cubeide_workspace/devf4/Drivers/SHT20" -I"D:/cubeide_workspace/devf4/Drivers/LIS3DS" -I"D:/cubeide_workspace/devf4/Drivers/DS3231" -I"D:/cubeide_workspace/devf4/Drivers/ILI9341/inc" -I"D:/cubeide_workspace/devf4/Drivers/EmWin/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ILI9341-2f-src

clean-Drivers-2f-ILI9341-2f-src:
	-$(RM) ./Drivers/ILI9341/src/ILI9341.d ./Drivers/ILI9341/src/ILI9341.o ./Drivers/ILI9341/src/ILI9341.su ./Drivers/ILI9341/src/ILI9341_GFX.d ./Drivers/ILI9341/src/ILI9341_GFX.o ./Drivers/ILI9341/src/ILI9341_GFX.su ./Drivers/ILI9341/src/fonts.d ./Drivers/ILI9341/src/fonts.o ./Drivers/ILI9341/src/fonts.su

.PHONY: clean-Drivers-2f-ILI9341-2f-src

