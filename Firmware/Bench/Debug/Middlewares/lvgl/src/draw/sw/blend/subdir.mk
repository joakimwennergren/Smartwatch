################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend.c \
../Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_al88.c \
../Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888.c \
../Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888_premultiplied.c \
../Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_i1.c \
../Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_l8.c \
../Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565.c \
../Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565_swapped.c \
../Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb888.c 

OBJS += \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend.o \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_al88.o \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888.o \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888_premultiplied.o \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_i1.o \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_l8.o \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565.o \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565_swapped.o \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb888.o 

C_DEPS += \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend.d \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_al88.d \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888.d \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888_premultiplied.d \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_i1.d \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_l8.d \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565.d \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565_swapped.d \
./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb888.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/draw/sw/blend/%.o Middlewares/lvgl/src/draw/sw/blend/%.su Middlewares/lvgl/src/draw/sw/blend/%.cyclo: ../Middlewares/lvgl/src/draw/sw/blend/%.c Middlewares/lvgl/src/draw/sw/blend/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-draw-2f-sw-2f-blend

clean-Middlewares-2f-lvgl-2f-src-2f-draw-2f-sw-2f-blend:
	-$(RM) ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend.cyclo ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend.d ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend.o ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend.su ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_al88.cyclo ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_al88.d ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_al88.o ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_al88.su ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888.cyclo ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888.d ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888.o ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888.su ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888_premultiplied.cyclo ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888_premultiplied.d ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888_premultiplied.o ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_argb8888_premultiplied.su ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_i1.cyclo ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_i1.d ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_i1.o ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_i1.su ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_l8.cyclo ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_l8.d ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_l8.o ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_l8.su ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565.cyclo ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565.d ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565.o ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565.su ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565_swapped.cyclo ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565_swapped.d ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565_swapped.o ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb565_swapped.su ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb888.cyclo ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb888.d ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb888.o ./Middlewares/lvgl/src/draw/sw/blend/lv_draw_sw_blend_to_rgb888.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-draw-2f-sw-2f-blend

