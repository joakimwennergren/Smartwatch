################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/drivers/evdev/lv_evdev.c 

OBJS += \
./Drivers/lvgl/src/drivers/evdev/lv_evdev.o 

C_DEPS += \
./Drivers/lvgl/src/drivers/evdev/lv_evdev.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/drivers/evdev/%.o Drivers/lvgl/src/drivers/evdev/%.su Drivers/lvgl/src/drivers/evdev/%.cyclo: ../Drivers/lvgl/src/drivers/evdev/%.c Drivers/lvgl/src/drivers/evdev/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Drivers/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-evdev

clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-evdev:
	-$(RM) ./Drivers/lvgl/src/drivers/evdev/lv_evdev.cyclo ./Drivers/lvgl/src/drivers/evdev/lv_evdev.d ./Drivers/lvgl/src/drivers/evdev/lv_evdev.o ./Drivers/lvgl/src/drivers/evdev/lv_evdev.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-evdev

