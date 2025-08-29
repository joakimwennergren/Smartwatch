################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/widgets/canvas/lv_canvas.c 

OBJS += \
./Middlewares/lvgl/src/widgets/canvas/lv_canvas.o 

C_DEPS += \
./Middlewares/lvgl/src/widgets/canvas/lv_canvas.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/widgets/canvas/%.o Middlewares/lvgl/src/widgets/canvas/%.su Middlewares/lvgl/src/widgets/canvas/%.cyclo: ../Middlewares/lvgl/src/widgets/canvas/%.c Middlewares/lvgl/src/widgets/canvas/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-widgets-2f-canvas

clean-Middlewares-2f-lvgl-2f-src-2f-widgets-2f-canvas:
	-$(RM) ./Middlewares/lvgl/src/widgets/canvas/lv_canvas.cyclo ./Middlewares/lvgl/src/widgets/canvas/lv_canvas.d ./Middlewares/lvgl/src/widgets/canvas/lv_canvas.o ./Middlewares/lvgl/src/widgets/canvas/lv_canvas.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-widgets-2f-canvas

