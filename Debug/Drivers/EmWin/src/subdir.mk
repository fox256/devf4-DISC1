################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/EmWin/src/GUIConf.c \
../Drivers/EmWin/src/GUI_X.c \
../Drivers/EmWin/src/LCDConf_FlexColor.c 

OBJS += \
./Drivers/EmWin/src/GUIConf.o \
./Drivers/EmWin/src/GUI_X.o \
./Drivers/EmWin/src/LCDConf_FlexColor.o 

C_DEPS += \
./Drivers/EmWin/src/GUIConf.d \
./Drivers/EmWin/src/GUI_X.d \
./Drivers/EmWin/src/LCDConf_FlexColor.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/EmWin/src/%.o Drivers/EmWin/src/%.su: ../Drivers/EmWin/src/%.c Drivers/EmWin/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/cubeide_workspace/devf4/Drivers/SHT20" -I"D:/cubeide_workspace/devf4/Drivers/LIS3DS" -I"D:/cubeide_workspace/devf4/Drivers/DS3231" -I"D:/cubeide_workspace/devf4/Drivers/ILI9341/inc" -I"D:/cubeide_workspace/devf4/Drivers/EmWin/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-EmWin-2f-src

clean-Drivers-2f-EmWin-2f-src:
	-$(RM) ./Drivers/EmWin/src/GUIConf.d ./Drivers/EmWin/src/GUIConf.o ./Drivers/EmWin/src/GUIConf.su ./Drivers/EmWin/src/GUI_X.d ./Drivers/EmWin/src/GUI_X.o ./Drivers/EmWin/src/GUI_X.su ./Drivers/EmWin/src/LCDConf_FlexColor.d ./Drivers/EmWin/src/LCDConf_FlexColor.o ./Drivers/EmWin/src/LCDConf_FlexColor.su

.PHONY: clean-Drivers-2f-EmWin-2f-src

