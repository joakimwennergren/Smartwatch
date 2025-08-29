################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/demos/benchmark/assets/img_benchmark_avatar.c \
../Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_argb.c \
../Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_rgb.c \
../Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_12_aligned.c \
../Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_14_aligned.c \
../Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_16_aligned.c \
../Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_18_aligned.c \
../Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_20_aligned.c \
../Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_24_aligned.c \
../Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_26_aligned.c 

OBJS += \
./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_avatar.o \
./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_argb.o \
./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_rgb.o \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_12_aligned.o \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_14_aligned.o \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_16_aligned.o \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_18_aligned.o \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_20_aligned.o \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_24_aligned.o \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_26_aligned.o 

C_DEPS += \
./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_avatar.d \
./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_argb.d \
./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_rgb.d \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_12_aligned.d \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_14_aligned.d \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_16_aligned.d \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_18_aligned.d \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_20_aligned.d \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_24_aligned.d \
./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_26_aligned.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/demos/benchmark/assets/%.o Middlewares/lvgl/demos/benchmark/assets/%.su Middlewares/lvgl/demos/benchmark/assets/%.cyclo: ../Middlewares/lvgl/demos/benchmark/assets/%.c Middlewares/lvgl/demos/benchmark/assets/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-demos-2f-benchmark-2f-assets

clean-Middlewares-2f-lvgl-2f-demos-2f-benchmark-2f-assets:
	-$(RM) ./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_avatar.cyclo ./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_avatar.d ./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_avatar.o ./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_avatar.su ./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_argb.cyclo ./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_argb.d ./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_argb.o ./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_argb.su ./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_rgb.cyclo ./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_rgb.d ./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_rgb.o ./Middlewares/lvgl/demos/benchmark/assets/img_benchmark_lvgl_logo_rgb.su ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_12_aligned.cyclo ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_12_aligned.d ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_12_aligned.o ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_12_aligned.su ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_14_aligned.cyclo ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_14_aligned.d ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_14_aligned.o ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_14_aligned.su ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_16_aligned.cyclo ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_16_aligned.d ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_16_aligned.o ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_16_aligned.su ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_18_aligned.cyclo ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_18_aligned.d ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_18_aligned.o ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_18_aligned.su ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_20_aligned.cyclo ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_20_aligned.d ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_20_aligned.o ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_20_aligned.su ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_24_aligned.cyclo ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_24_aligned.d ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_24_aligned.o ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_24_aligned.su ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_26_aligned.cyclo ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_26_aligned.d ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_26_aligned.o ./Middlewares/lvgl/demos/benchmark/assets/lv_font_benchmark_montserrat_26_aligned.su

.PHONY: clean-Middlewares-2f-lvgl-2f-demos-2f-benchmark-2f-assets

