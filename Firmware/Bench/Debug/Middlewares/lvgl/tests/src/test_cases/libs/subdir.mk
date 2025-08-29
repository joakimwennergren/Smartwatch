################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/tests/src/test_cases/libs/test_barcode.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_bin_decoder.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_bmp.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_ffmpeg.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_font_stress.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_freetype.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_libpng.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_lodepng.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_memmove.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_qrcode.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_svg_decoder.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_tiny_ttf.c \
../Middlewares/lvgl/tests/src/test_cases/libs/test_tjpgd.c 

OBJS += \
./Middlewares/lvgl/tests/src/test_cases/libs/test_barcode.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_bin_decoder.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_bmp.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_ffmpeg.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_font_stress.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_freetype.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_libpng.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_lodepng.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_memmove.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_qrcode.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_svg_decoder.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_tiny_ttf.o \
./Middlewares/lvgl/tests/src/test_cases/libs/test_tjpgd.o 

C_DEPS += \
./Middlewares/lvgl/tests/src/test_cases/libs/test_barcode.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_bin_decoder.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_bmp.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_ffmpeg.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_font_stress.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_freetype.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_libpng.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_lodepng.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_memmove.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_qrcode.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_svg_decoder.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_tiny_ttf.d \
./Middlewares/lvgl/tests/src/test_cases/libs/test_tjpgd.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/tests/src/test_cases/libs/%.o Middlewares/lvgl/tests/src/test_cases/libs/%.su Middlewares/lvgl/tests/src/test_cases/libs/%.cyclo: ../Middlewares/lvgl/tests/src/test_cases/libs/%.c Middlewares/lvgl/tests/src/test_cases/libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-tests-2f-src-2f-test_cases-2f-libs

clean-Middlewares-2f-lvgl-2f-tests-2f-src-2f-test_cases-2f-libs:
	-$(RM) ./Middlewares/lvgl/tests/src/test_cases/libs/test_barcode.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_barcode.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_barcode.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_barcode.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_bin_decoder.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_bin_decoder.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_bin_decoder.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_bin_decoder.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_bmp.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_bmp.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_bmp.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_bmp.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_ffmpeg.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_ffmpeg.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_ffmpeg.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_ffmpeg.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_font_stress.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_font_stress.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_font_stress.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_font_stress.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_freetype.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_freetype.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_freetype.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_freetype.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_libpng.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_libpng.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_libpng.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_libpng.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_lodepng.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_lodepng.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_lodepng.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_lodepng.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_memmove.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_memmove.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_memmove.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_memmove.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_qrcode.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_qrcode.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_qrcode.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_qrcode.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_svg_decoder.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_svg_decoder.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_svg_decoder.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_svg_decoder.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_tiny_ttf.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_tiny_ttf.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_tiny_ttf.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_tiny_ttf.su ./Middlewares/lvgl/tests/src/test_cases/libs/test_tjpgd.cyclo ./Middlewares/lvgl/tests/src/test_cases/libs/test_tjpgd.d ./Middlewares/lvgl/tests/src/test_cases/libs/test_tjpgd.o ./Middlewares/lvgl/tests/src/test_cases/libs/test_tjpgd.su

.PHONY: clean-Middlewares-2f-lvgl-2f-tests-2f-src-2f-test_cases-2f-libs

