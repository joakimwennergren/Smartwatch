################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/examples/event/lv_example_event_bubble.c \
../Middlewares/lvgl/examples/event/lv_example_event_button.c \
../Middlewares/lvgl/examples/event/lv_example_event_click.c \
../Middlewares/lvgl/examples/event/lv_example_event_draw.c \
../Middlewares/lvgl/examples/event/lv_example_event_streak.c 

OBJS += \
./Middlewares/lvgl/examples/event/lv_example_event_bubble.o \
./Middlewares/lvgl/examples/event/lv_example_event_button.o \
./Middlewares/lvgl/examples/event/lv_example_event_click.o \
./Middlewares/lvgl/examples/event/lv_example_event_draw.o \
./Middlewares/lvgl/examples/event/lv_example_event_streak.o 

C_DEPS += \
./Middlewares/lvgl/examples/event/lv_example_event_bubble.d \
./Middlewares/lvgl/examples/event/lv_example_event_button.d \
./Middlewares/lvgl/examples/event/lv_example_event_click.d \
./Middlewares/lvgl/examples/event/lv_example_event_draw.d \
./Middlewares/lvgl/examples/event/lv_example_event_streak.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/examples/event/%.o Middlewares/lvgl/examples/event/%.su Middlewares/lvgl/examples/event/%.cyclo: ../Middlewares/lvgl/examples/event/%.c Middlewares/lvgl/examples/event/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-examples-2f-event

clean-Middlewares-2f-lvgl-2f-examples-2f-event:
	-$(RM) ./Middlewares/lvgl/examples/event/lv_example_event_bubble.cyclo ./Middlewares/lvgl/examples/event/lv_example_event_bubble.d ./Middlewares/lvgl/examples/event/lv_example_event_bubble.o ./Middlewares/lvgl/examples/event/lv_example_event_bubble.su ./Middlewares/lvgl/examples/event/lv_example_event_button.cyclo ./Middlewares/lvgl/examples/event/lv_example_event_button.d ./Middlewares/lvgl/examples/event/lv_example_event_button.o ./Middlewares/lvgl/examples/event/lv_example_event_button.su ./Middlewares/lvgl/examples/event/lv_example_event_click.cyclo ./Middlewares/lvgl/examples/event/lv_example_event_click.d ./Middlewares/lvgl/examples/event/lv_example_event_click.o ./Middlewares/lvgl/examples/event/lv_example_event_click.su ./Middlewares/lvgl/examples/event/lv_example_event_draw.cyclo ./Middlewares/lvgl/examples/event/lv_example_event_draw.d ./Middlewares/lvgl/examples/event/lv_example_event_draw.o ./Middlewares/lvgl/examples/event/lv_example_event_draw.su ./Middlewares/lvgl/examples/event/lv_example_event_streak.cyclo ./Middlewares/lvgl/examples/event/lv_example_event_streak.d ./Middlewares/lvgl/examples/event/lv_example_event_streak.o ./Middlewares/lvgl/examples/event/lv_example_event_streak.su

.PHONY: clean-Middlewares-2f-lvgl-2f-examples-2f-event

