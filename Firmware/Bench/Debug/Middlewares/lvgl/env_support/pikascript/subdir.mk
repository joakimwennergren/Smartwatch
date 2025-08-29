################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/env_support/pikascript/pika_lv_point_t.c \
../Middlewares/lvgl/env_support/pikascript/pika_lv_timer_t.c \
../Middlewares/lvgl/env_support/pikascript/pika_lv_wegit.c \
../Middlewares/lvgl/env_support/pikascript/pika_lvgl.c \
../Middlewares/lvgl/env_support/pikascript/pika_lvgl_indev_t.c \
../Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_event.c \
../Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_obj.c \
../Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_style_t.c 

OBJS += \
./Middlewares/lvgl/env_support/pikascript/pika_lv_point_t.o \
./Middlewares/lvgl/env_support/pikascript/pika_lv_timer_t.o \
./Middlewares/lvgl/env_support/pikascript/pika_lv_wegit.o \
./Middlewares/lvgl/env_support/pikascript/pika_lvgl.o \
./Middlewares/lvgl/env_support/pikascript/pika_lvgl_indev_t.o \
./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_event.o \
./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_obj.o \
./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_style_t.o 

C_DEPS += \
./Middlewares/lvgl/env_support/pikascript/pika_lv_point_t.d \
./Middlewares/lvgl/env_support/pikascript/pika_lv_timer_t.d \
./Middlewares/lvgl/env_support/pikascript/pika_lv_wegit.d \
./Middlewares/lvgl/env_support/pikascript/pika_lvgl.d \
./Middlewares/lvgl/env_support/pikascript/pika_lvgl_indev_t.d \
./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_event.d \
./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_obj.d \
./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_style_t.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/env_support/pikascript/%.o Middlewares/lvgl/env_support/pikascript/%.su Middlewares/lvgl/env_support/pikascript/%.cyclo: ../Middlewares/lvgl/env_support/pikascript/%.c Middlewares/lvgl/env_support/pikascript/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-env_support-2f-pikascript

clean-Middlewares-2f-lvgl-2f-env_support-2f-pikascript:
	-$(RM) ./Middlewares/lvgl/env_support/pikascript/pika_lv_point_t.cyclo ./Middlewares/lvgl/env_support/pikascript/pika_lv_point_t.d ./Middlewares/lvgl/env_support/pikascript/pika_lv_point_t.o ./Middlewares/lvgl/env_support/pikascript/pika_lv_point_t.su ./Middlewares/lvgl/env_support/pikascript/pika_lv_timer_t.cyclo ./Middlewares/lvgl/env_support/pikascript/pika_lv_timer_t.d ./Middlewares/lvgl/env_support/pikascript/pika_lv_timer_t.o ./Middlewares/lvgl/env_support/pikascript/pika_lv_timer_t.su ./Middlewares/lvgl/env_support/pikascript/pika_lv_wegit.cyclo ./Middlewares/lvgl/env_support/pikascript/pika_lv_wegit.d ./Middlewares/lvgl/env_support/pikascript/pika_lv_wegit.o ./Middlewares/lvgl/env_support/pikascript/pika_lv_wegit.su ./Middlewares/lvgl/env_support/pikascript/pika_lvgl.cyclo ./Middlewares/lvgl/env_support/pikascript/pika_lvgl.d ./Middlewares/lvgl/env_support/pikascript/pika_lvgl.o ./Middlewares/lvgl/env_support/pikascript/pika_lvgl.su ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_indev_t.cyclo ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_indev_t.d ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_indev_t.o ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_indev_t.su ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_event.cyclo ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_event.d ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_event.o ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_event.su ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_obj.cyclo ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_obj.d ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_obj.o ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_obj.su ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_style_t.cyclo ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_style_t.d ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_style_t.o ./Middlewares/lvgl/env_support/pikascript/pika_lvgl_lv_style_t.su

.PHONY: clean-Middlewares-2f-lvgl-2f-env_support-2f-pikascript

