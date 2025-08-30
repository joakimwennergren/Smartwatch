################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/lv_init.c 

OBJS += \
./Drivers/lvgl/src/lv_init.o 

C_DEPS += \
./Drivers/lvgl/src/lv_init.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/%.o Drivers/lvgl/src/%.su Drivers/lvgl/src/%.cyclo: ../Drivers/lvgl/src/%.c Drivers/lvgl/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I"/Users/joakimwennergren/Desktop/Smartwatch/Firmware/Bench/Drivers/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src

clean-Drivers-2f-lvgl-2f-src:
	-$(RM) ./Drivers/lvgl/src/lv_init.cyclo ./Drivers/lvgl/src/lv_init.d ./Drivers/lvgl/src/lv_init.o ./Drivers/lvgl/src/lv_init.su

.PHONY: clean-Drivers-2f-lvgl-2f-src

