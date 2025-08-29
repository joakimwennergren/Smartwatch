################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_1.c \
../Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_10.c \
../Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_11.c \
../Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_2.c \
../Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_3.c \
../Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_4.c \
../Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_5.c \
../Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_6.c \
../Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_7.c \
../Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_8.c \
../Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_9.c 

OBJS += \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_1.o \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_10.o \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_11.o \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_2.o \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_3.o \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_4.o \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_5.o \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_6.o \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_7.o \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_8.o \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_9.o 

C_DEPS += \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_1.d \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_10.d \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_11.d \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_2.d \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_3.d \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_4.d \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_5.d \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_6.d \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_7.d \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_8.d \
./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_9.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/examples/widgets/canvas/%.o Middlewares/lvgl/examples/widgets/canvas/%.su Middlewares/lvgl/examples/widgets/canvas/%.cyclo: ../Middlewares/lvgl/examples/widgets/canvas/%.c Middlewares/lvgl/examples/widgets/canvas/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-examples-2f-widgets-2f-canvas

clean-Middlewares-2f-lvgl-2f-examples-2f-widgets-2f-canvas:
	-$(RM) ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_1.cyclo ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_1.d ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_1.o ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_1.su ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_10.cyclo ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_10.d ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_10.o ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_10.su ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_11.cyclo ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_11.d ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_11.o ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_11.su ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_2.cyclo ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_2.d ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_2.o ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_2.su ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_3.cyclo ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_3.d ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_3.o ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_3.su ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_4.cyclo ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_4.d ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_4.o ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_4.su ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_5.cyclo ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_5.d ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_5.o ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_5.su ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_6.cyclo ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_6.d ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_6.o ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_6.su ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_7.cyclo ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_7.d ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_7.o ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_7.su ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_8.cyclo ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_8.d ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_8.o ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_8.su ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_9.cyclo ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_9.d ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_9.o ./Middlewares/lvgl/examples/widgets/canvas/lv_example_canvas_9.su

.PHONY: clean-Middlewares-2f-lvgl-2f-examples-2f-widgets-2f-canvas

