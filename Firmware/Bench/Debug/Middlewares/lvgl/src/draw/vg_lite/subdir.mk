################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_buf_vg_lite.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_arc.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_border.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_box_shadow.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_fill.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_img.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_label.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_layer.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_line.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_mask_rect.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_triangle.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_vector.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_decoder.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_grad.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_math.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_path.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_pending.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_stroke.c \
../Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_utils.c 

OBJS += \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_buf_vg_lite.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_arc.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_border.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_box_shadow.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_fill.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_img.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_label.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_layer.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_line.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_mask_rect.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_triangle.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_vector.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_decoder.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_grad.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_math.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_path.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_pending.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_stroke.o \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_utils.o 

C_DEPS += \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_buf_vg_lite.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_arc.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_border.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_box_shadow.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_fill.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_img.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_label.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_layer.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_line.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_mask_rect.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_triangle.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_vector.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_decoder.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_grad.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_math.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_path.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_pending.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_stroke.d \
./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/draw/vg_lite/%.o Middlewares/lvgl/src/draw/vg_lite/%.su Middlewares/lvgl/src/draw/vg_lite/%.cyclo: ../Middlewares/lvgl/src/draw/vg_lite/%.c Middlewares/lvgl/src/draw/vg_lite/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-draw-2f-vg_lite

clean-Middlewares-2f-lvgl-2f-src-2f-draw-2f-vg_lite:
	-$(RM) ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_buf_vg_lite.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_buf_vg_lite.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_buf_vg_lite.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_buf_vg_lite.su ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite.su ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_arc.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_arc.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_arc.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_arc.su ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_border.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_border.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_border.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_border.su ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_box_shadow.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_box_shadow.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_box_shadow.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_box_shadow.su ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_fill.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_fill.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_fill.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_fill.su ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_img.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_img.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_img.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_img.su ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_label.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_label.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_label.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_label.su ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_layer.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_layer.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_layer.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_layer.su ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_line.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_line.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_line.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_line.su ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_mask_rect.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_mask_rect.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_mask_rect.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_mask_rect.su ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_triangle.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_triangle.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_triangle.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_triangle.su ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_vector.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_vector.d ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_vector.o ./Middlewares/lvgl/src/draw/vg_lite/lv_draw_vg_lite_vector.su ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_decoder.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_decoder.d ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_decoder.o ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_decoder.su ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_grad.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_grad.d ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_grad.o ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_grad.su ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_math.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_math.d ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_math.o ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_math.su ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_path.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_path.d ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_path.o ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_path.su ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_pending.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_pending.d ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_pending.o ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_pending.su ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_stroke.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_stroke.d ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_stroke.o ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_stroke.su ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_utils.cyclo ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_utils.d ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_utils.o ./Middlewares/lvgl/src/draw/vg_lite/lv_vg_lite_utils.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-draw-2f-vg_lite

