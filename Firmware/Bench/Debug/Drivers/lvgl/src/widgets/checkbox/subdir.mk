################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/widgets/checkbox/lv_checkbox.c 

OBJS += \
./Drivers/lvgl/src/widgets/checkbox/lv_checkbox.o 

C_DEPS += \
./Drivers/lvgl/src/widgets/checkbox/lv_checkbox.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/widgets/checkbox/%.o Drivers/lvgl/src/widgets/checkbox/%.su Drivers/lvgl/src/widgets/checkbox/%.cyclo: ../Drivers/lvgl/src/widgets/checkbox/%.c Drivers/lvgl/src/widgets/checkbox/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/home/joakim-wennergren/Desktop/Smartwatch/Firmware/Bench/Drivers/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-widgets-2f-checkbox

clean-Drivers-2f-lvgl-2f-src-2f-widgets-2f-checkbox:
	-$(RM) ./Drivers/lvgl/src/widgets/checkbox/lv_checkbox.cyclo ./Drivers/lvgl/src/widgets/checkbox/lv_checkbox.d ./Drivers/lvgl/src/widgets/checkbox/lv_checkbox.o ./Drivers/lvgl/src/widgets/checkbox/lv_checkbox.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-widgets-2f-checkbox

