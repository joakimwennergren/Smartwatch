################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/demos/render/assets/img_render_arc_bg.c \
../Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.c \
../Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.c \
../Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_i1.c \
../Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_l8.c \
../Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.c \
../Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.c \
../Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.c \
../Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.c \
../Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.c 

OBJS += \
./Middlewares/lvgl/demos/render/assets/img_render_arc_bg.o \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.o \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.o \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_i1.o \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_l8.o \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.o \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.o \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.o \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.o \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.o 

C_DEPS += \
./Middlewares/lvgl/demos/render/assets/img_render_arc_bg.d \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.d \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.d \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_i1.d \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_l8.d \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.d \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.d \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.d \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.d \
./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/demos/render/assets/%.o Middlewares/lvgl/demos/render/assets/%.su Middlewares/lvgl/demos/render/assets/%.cyclo: ../Middlewares/lvgl/demos/render/assets/%.c Middlewares/lvgl/demos/render/assets/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-demos-2f-render-2f-assets

clean-Middlewares-2f-lvgl-2f-demos-2f-render-2f-assets:
	-$(RM) ./Middlewares/lvgl/demos/render/assets/img_render_arc_bg.cyclo ./Middlewares/lvgl/demos/render/assets/img_render_arc_bg.d ./Middlewares/lvgl/demos/render/assets/img_render_arc_bg.o ./Middlewares/lvgl/demos/render/assets/img_render_arc_bg.su ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.cyclo ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.d ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.o ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.su ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.cyclo ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.d ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.o ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.su ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_i1.cyclo ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_i1.d ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_i1.o ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_i1.su ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_l8.cyclo ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_l8.d ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_l8.o ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_l8.su ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.cyclo ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.d ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.o ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.su ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.cyclo ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.d ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.o ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.su ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.cyclo ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.d ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.o ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.su ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.cyclo ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.d ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.o ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.su ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.cyclo ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.d ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.o ./Middlewares/lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.su

.PHONY: clean-Middlewares-2f-lvgl-2f-demos-2f-render-2f-assets

