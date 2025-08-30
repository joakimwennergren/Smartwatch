################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/libs/svg/lv_svg.c \
../Drivers/lvgl/src/libs/svg/lv_svg_decoder.c \
../Drivers/lvgl/src/libs/svg/lv_svg_parser.c \
../Drivers/lvgl/src/libs/svg/lv_svg_render.c \
../Drivers/lvgl/src/libs/svg/lv_svg_token.c 

OBJS += \
./Drivers/lvgl/src/libs/svg/lv_svg.o \
./Drivers/lvgl/src/libs/svg/lv_svg_decoder.o \
./Drivers/lvgl/src/libs/svg/lv_svg_parser.o \
./Drivers/lvgl/src/libs/svg/lv_svg_render.o \
./Drivers/lvgl/src/libs/svg/lv_svg_token.o 

C_DEPS += \
./Drivers/lvgl/src/libs/svg/lv_svg.d \
./Drivers/lvgl/src/libs/svg/lv_svg_decoder.d \
./Drivers/lvgl/src/libs/svg/lv_svg_parser.d \
./Drivers/lvgl/src/libs/svg/lv_svg_render.d \
./Drivers/lvgl/src/libs/svg/lv_svg_token.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/libs/svg/%.o Drivers/lvgl/src/libs/svg/%.su Drivers/lvgl/src/libs/svg/%.cyclo: ../Drivers/lvgl/src/libs/svg/%.c Drivers/lvgl/src/libs/svg/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I"/Users/joakimwennergren/Desktop/Smartwatch/Firmware/Bench/Drivers/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-svg

clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-svg:
	-$(RM) ./Drivers/lvgl/src/libs/svg/lv_svg.cyclo ./Drivers/lvgl/src/libs/svg/lv_svg.d ./Drivers/lvgl/src/libs/svg/lv_svg.o ./Drivers/lvgl/src/libs/svg/lv_svg.su ./Drivers/lvgl/src/libs/svg/lv_svg_decoder.cyclo ./Drivers/lvgl/src/libs/svg/lv_svg_decoder.d ./Drivers/lvgl/src/libs/svg/lv_svg_decoder.o ./Drivers/lvgl/src/libs/svg/lv_svg_decoder.su ./Drivers/lvgl/src/libs/svg/lv_svg_parser.cyclo ./Drivers/lvgl/src/libs/svg/lv_svg_parser.d ./Drivers/lvgl/src/libs/svg/lv_svg_parser.o ./Drivers/lvgl/src/libs/svg/lv_svg_parser.su ./Drivers/lvgl/src/libs/svg/lv_svg_render.cyclo ./Drivers/lvgl/src/libs/svg/lv_svg_render.d ./Drivers/lvgl/src/libs/svg/lv_svg_render.o ./Drivers/lvgl/src/libs/svg/lv_svg_render.su ./Drivers/lvgl/src/libs/svg/lv_svg_token.cyclo ./Drivers/lvgl/src/libs/svg/lv_svg_token.d ./Drivers/lvgl/src/libs/svg/lv_svg_token.o ./Drivers/lvgl/src/libs/svg/lv_svg_token.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-svg

