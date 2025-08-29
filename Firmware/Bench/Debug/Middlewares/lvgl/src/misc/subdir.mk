################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/misc/lv_anim.c \
../Middlewares/lvgl/src/misc/lv_anim_timeline.c \
../Middlewares/lvgl/src/misc/lv_area.c \
../Middlewares/lvgl/src/misc/lv_array.c \
../Middlewares/lvgl/src/misc/lv_async.c \
../Middlewares/lvgl/src/misc/lv_bidi.c \
../Middlewares/lvgl/src/misc/lv_circle_buf.c \
../Middlewares/lvgl/src/misc/lv_color.c \
../Middlewares/lvgl/src/misc/lv_color_op.c \
../Middlewares/lvgl/src/misc/lv_event.c \
../Middlewares/lvgl/src/misc/lv_fs.c \
../Middlewares/lvgl/src/misc/lv_grad.c \
../Middlewares/lvgl/src/misc/lv_iter.c \
../Middlewares/lvgl/src/misc/lv_ll.c \
../Middlewares/lvgl/src/misc/lv_log.c \
../Middlewares/lvgl/src/misc/lv_lru.c \
../Middlewares/lvgl/src/misc/lv_math.c \
../Middlewares/lvgl/src/misc/lv_matrix.c \
../Middlewares/lvgl/src/misc/lv_palette.c \
../Middlewares/lvgl/src/misc/lv_profiler_builtin.c \
../Middlewares/lvgl/src/misc/lv_rb.c \
../Middlewares/lvgl/src/misc/lv_style.c \
../Middlewares/lvgl/src/misc/lv_style_gen.c \
../Middlewares/lvgl/src/misc/lv_templ.c \
../Middlewares/lvgl/src/misc/lv_text.c \
../Middlewares/lvgl/src/misc/lv_text_ap.c \
../Middlewares/lvgl/src/misc/lv_timer.c \
../Middlewares/lvgl/src/misc/lv_tree.c \
../Middlewares/lvgl/src/misc/lv_utils.c 

OBJS += \
./Middlewares/lvgl/src/misc/lv_anim.o \
./Middlewares/lvgl/src/misc/lv_anim_timeline.o \
./Middlewares/lvgl/src/misc/lv_area.o \
./Middlewares/lvgl/src/misc/lv_array.o \
./Middlewares/lvgl/src/misc/lv_async.o \
./Middlewares/lvgl/src/misc/lv_bidi.o \
./Middlewares/lvgl/src/misc/lv_circle_buf.o \
./Middlewares/lvgl/src/misc/lv_color.o \
./Middlewares/lvgl/src/misc/lv_color_op.o \
./Middlewares/lvgl/src/misc/lv_event.o \
./Middlewares/lvgl/src/misc/lv_fs.o \
./Middlewares/lvgl/src/misc/lv_grad.o \
./Middlewares/lvgl/src/misc/lv_iter.o \
./Middlewares/lvgl/src/misc/lv_ll.o \
./Middlewares/lvgl/src/misc/lv_log.o \
./Middlewares/lvgl/src/misc/lv_lru.o \
./Middlewares/lvgl/src/misc/lv_math.o \
./Middlewares/lvgl/src/misc/lv_matrix.o \
./Middlewares/lvgl/src/misc/lv_palette.o \
./Middlewares/lvgl/src/misc/lv_profiler_builtin.o \
./Middlewares/lvgl/src/misc/lv_rb.o \
./Middlewares/lvgl/src/misc/lv_style.o \
./Middlewares/lvgl/src/misc/lv_style_gen.o \
./Middlewares/lvgl/src/misc/lv_templ.o \
./Middlewares/lvgl/src/misc/lv_text.o \
./Middlewares/lvgl/src/misc/lv_text_ap.o \
./Middlewares/lvgl/src/misc/lv_timer.o \
./Middlewares/lvgl/src/misc/lv_tree.o \
./Middlewares/lvgl/src/misc/lv_utils.o 

C_DEPS += \
./Middlewares/lvgl/src/misc/lv_anim.d \
./Middlewares/lvgl/src/misc/lv_anim_timeline.d \
./Middlewares/lvgl/src/misc/lv_area.d \
./Middlewares/lvgl/src/misc/lv_array.d \
./Middlewares/lvgl/src/misc/lv_async.d \
./Middlewares/lvgl/src/misc/lv_bidi.d \
./Middlewares/lvgl/src/misc/lv_circle_buf.d \
./Middlewares/lvgl/src/misc/lv_color.d \
./Middlewares/lvgl/src/misc/lv_color_op.d \
./Middlewares/lvgl/src/misc/lv_event.d \
./Middlewares/lvgl/src/misc/lv_fs.d \
./Middlewares/lvgl/src/misc/lv_grad.d \
./Middlewares/lvgl/src/misc/lv_iter.d \
./Middlewares/lvgl/src/misc/lv_ll.d \
./Middlewares/lvgl/src/misc/lv_log.d \
./Middlewares/lvgl/src/misc/lv_lru.d \
./Middlewares/lvgl/src/misc/lv_math.d \
./Middlewares/lvgl/src/misc/lv_matrix.d \
./Middlewares/lvgl/src/misc/lv_palette.d \
./Middlewares/lvgl/src/misc/lv_profiler_builtin.d \
./Middlewares/lvgl/src/misc/lv_rb.d \
./Middlewares/lvgl/src/misc/lv_style.d \
./Middlewares/lvgl/src/misc/lv_style_gen.d \
./Middlewares/lvgl/src/misc/lv_templ.d \
./Middlewares/lvgl/src/misc/lv_text.d \
./Middlewares/lvgl/src/misc/lv_text_ap.d \
./Middlewares/lvgl/src/misc/lv_timer.d \
./Middlewares/lvgl/src/misc/lv_tree.d \
./Middlewares/lvgl/src/misc/lv_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/misc/%.o Middlewares/lvgl/src/misc/%.su Middlewares/lvgl/src/misc/%.cyclo: ../Middlewares/lvgl/src/misc/%.c Middlewares/lvgl/src/misc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-misc

clean-Middlewares-2f-lvgl-2f-src-2f-misc:
	-$(RM) ./Middlewares/lvgl/src/misc/lv_anim.cyclo ./Middlewares/lvgl/src/misc/lv_anim.d ./Middlewares/lvgl/src/misc/lv_anim.o ./Middlewares/lvgl/src/misc/lv_anim.su ./Middlewares/lvgl/src/misc/lv_anim_timeline.cyclo ./Middlewares/lvgl/src/misc/lv_anim_timeline.d ./Middlewares/lvgl/src/misc/lv_anim_timeline.o ./Middlewares/lvgl/src/misc/lv_anim_timeline.su ./Middlewares/lvgl/src/misc/lv_area.cyclo ./Middlewares/lvgl/src/misc/lv_area.d ./Middlewares/lvgl/src/misc/lv_area.o ./Middlewares/lvgl/src/misc/lv_area.su ./Middlewares/lvgl/src/misc/lv_array.cyclo ./Middlewares/lvgl/src/misc/lv_array.d ./Middlewares/lvgl/src/misc/lv_array.o ./Middlewares/lvgl/src/misc/lv_array.su ./Middlewares/lvgl/src/misc/lv_async.cyclo ./Middlewares/lvgl/src/misc/lv_async.d ./Middlewares/lvgl/src/misc/lv_async.o ./Middlewares/lvgl/src/misc/lv_async.su ./Middlewares/lvgl/src/misc/lv_bidi.cyclo ./Middlewares/lvgl/src/misc/lv_bidi.d ./Middlewares/lvgl/src/misc/lv_bidi.o ./Middlewares/lvgl/src/misc/lv_bidi.su ./Middlewares/lvgl/src/misc/lv_circle_buf.cyclo ./Middlewares/lvgl/src/misc/lv_circle_buf.d ./Middlewares/lvgl/src/misc/lv_circle_buf.o ./Middlewares/lvgl/src/misc/lv_circle_buf.su ./Middlewares/lvgl/src/misc/lv_color.cyclo ./Middlewares/lvgl/src/misc/lv_color.d ./Middlewares/lvgl/src/misc/lv_color.o ./Middlewares/lvgl/src/misc/lv_color.su ./Middlewares/lvgl/src/misc/lv_color_op.cyclo ./Middlewares/lvgl/src/misc/lv_color_op.d ./Middlewares/lvgl/src/misc/lv_color_op.o ./Middlewares/lvgl/src/misc/lv_color_op.su ./Middlewares/lvgl/src/misc/lv_event.cyclo ./Middlewares/lvgl/src/misc/lv_event.d ./Middlewares/lvgl/src/misc/lv_event.o ./Middlewares/lvgl/src/misc/lv_event.su ./Middlewares/lvgl/src/misc/lv_fs.cyclo ./Middlewares/lvgl/src/misc/lv_fs.d ./Middlewares/lvgl/src/misc/lv_fs.o ./Middlewares/lvgl/src/misc/lv_fs.su ./Middlewares/lvgl/src/misc/lv_grad.cyclo ./Middlewares/lvgl/src/misc/lv_grad.d ./Middlewares/lvgl/src/misc/lv_grad.o ./Middlewares/lvgl/src/misc/lv_grad.su ./Middlewares/lvgl/src/misc/lv_iter.cyclo ./Middlewares/lvgl/src/misc/lv_iter.d ./Middlewares/lvgl/src/misc/lv_iter.o ./Middlewares/lvgl/src/misc/lv_iter.su ./Middlewares/lvgl/src/misc/lv_ll.cyclo ./Middlewares/lvgl/src/misc/lv_ll.d ./Middlewares/lvgl/src/misc/lv_ll.o ./Middlewares/lvgl/src/misc/lv_ll.su ./Middlewares/lvgl/src/misc/lv_log.cyclo ./Middlewares/lvgl/src/misc/lv_log.d ./Middlewares/lvgl/src/misc/lv_log.o ./Middlewares/lvgl/src/misc/lv_log.su ./Middlewares/lvgl/src/misc/lv_lru.cyclo ./Middlewares/lvgl/src/misc/lv_lru.d ./Middlewares/lvgl/src/misc/lv_lru.o ./Middlewares/lvgl/src/misc/lv_lru.su ./Middlewares/lvgl/src/misc/lv_math.cyclo ./Middlewares/lvgl/src/misc/lv_math.d ./Middlewares/lvgl/src/misc/lv_math.o ./Middlewares/lvgl/src/misc/lv_math.su ./Middlewares/lvgl/src/misc/lv_matrix.cyclo ./Middlewares/lvgl/src/misc/lv_matrix.d ./Middlewares/lvgl/src/misc/lv_matrix.o ./Middlewares/lvgl/src/misc/lv_matrix.su ./Middlewares/lvgl/src/misc/lv_palette.cyclo ./Middlewares/lvgl/src/misc/lv_palette.d ./Middlewares/lvgl/src/misc/lv_palette.o ./Middlewares/lvgl/src/misc/lv_palette.su ./Middlewares/lvgl/src/misc/lv_profiler_builtin.cyclo ./Middlewares/lvgl/src/misc/lv_profiler_builtin.d ./Middlewares/lvgl/src/misc/lv_profiler_builtin.o ./Middlewares/lvgl/src/misc/lv_profiler_builtin.su ./Middlewares/lvgl/src/misc/lv_rb.cyclo ./Middlewares/lvgl/src/misc/lv_rb.d ./Middlewares/lvgl/src/misc/lv_rb.o ./Middlewares/lvgl/src/misc/lv_rb.su ./Middlewares/lvgl/src/misc/lv_style.cyclo ./Middlewares/lvgl/src/misc/lv_style.d ./Middlewares/lvgl/src/misc/lv_style.o ./Middlewares/lvgl/src/misc/lv_style.su ./Middlewares/lvgl/src/misc/lv_style_gen.cyclo ./Middlewares/lvgl/src/misc/lv_style_gen.d ./Middlewares/lvgl/src/misc/lv_style_gen.o ./Middlewares/lvgl/src/misc/lv_style_gen.su ./Middlewares/lvgl/src/misc/lv_templ.cyclo ./Middlewares/lvgl/src/misc/lv_templ.d ./Middlewares/lvgl/src/misc/lv_templ.o ./Middlewares/lvgl/src/misc/lv_templ.su ./Middlewares/lvgl/src/misc/lv_text.cyclo ./Middlewares/lvgl/src/misc/lv_text.d ./Middlewares/lvgl/src/misc/lv_text.o ./Middlewares/lvgl/src/misc/lv_text.su ./Middlewares/lvgl/src/misc/lv_text_ap.cyclo ./Middlewares/lvgl/src/misc/lv_text_ap.d ./Middlewares/lvgl/src/misc/lv_text_ap.o ./Middlewares/lvgl/src/misc/lv_text_ap.su ./Middlewares/lvgl/src/misc/lv_timer.cyclo ./Middlewares/lvgl/src/misc/lv_timer.d ./Middlewares/lvgl/src/misc/lv_timer.o ./Middlewares/lvgl/src/misc/lv_timer.su ./Middlewares/lvgl/src/misc/lv_tree.cyclo ./Middlewares/lvgl/src/misc/lv_tree.d ./Middlewares/lvgl/src/misc/lv_tree.o ./Middlewares/lvgl/src/misc/lv_tree.su ./Middlewares/lvgl/src/misc/lv_utils.cyclo ./Middlewares/lvgl/src/misc/lv_utils.d ./Middlewares/lvgl/src/misc/lv_utils.o ./Middlewares/lvgl/src/misc/lv_utils.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-misc

