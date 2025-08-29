################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/examples/assets/animimg001.c \
../Middlewares/lvgl/examples/assets/animimg002.c \
../Middlewares/lvgl/examples/assets/animimg003.c \
../Middlewares/lvgl/examples/assets/img_caret_down.c \
../Middlewares/lvgl/examples/assets/img_cogwheel_argb.c \
../Middlewares/lvgl/examples/assets/img_cogwheel_indexed16.c \
../Middlewares/lvgl/examples/assets/img_cogwheel_rgb.c \
../Middlewares/lvgl/examples/assets/img_hand.c \
../Middlewares/lvgl/examples/assets/img_skew_strip.c \
../Middlewares/lvgl/examples/assets/img_star.c \
../Middlewares/lvgl/examples/assets/img_svg_img.c \
../Middlewares/lvgl/examples/assets/imgbtn_left.c \
../Middlewares/lvgl/examples/assets/imgbtn_mid.c \
../Middlewares/lvgl/examples/assets/imgbtn_right.c 

OBJS += \
./Middlewares/lvgl/examples/assets/animimg001.o \
./Middlewares/lvgl/examples/assets/animimg002.o \
./Middlewares/lvgl/examples/assets/animimg003.o \
./Middlewares/lvgl/examples/assets/img_caret_down.o \
./Middlewares/lvgl/examples/assets/img_cogwheel_argb.o \
./Middlewares/lvgl/examples/assets/img_cogwheel_indexed16.o \
./Middlewares/lvgl/examples/assets/img_cogwheel_rgb.o \
./Middlewares/lvgl/examples/assets/img_hand.o \
./Middlewares/lvgl/examples/assets/img_skew_strip.o \
./Middlewares/lvgl/examples/assets/img_star.o \
./Middlewares/lvgl/examples/assets/img_svg_img.o \
./Middlewares/lvgl/examples/assets/imgbtn_left.o \
./Middlewares/lvgl/examples/assets/imgbtn_mid.o \
./Middlewares/lvgl/examples/assets/imgbtn_right.o 

C_DEPS += \
./Middlewares/lvgl/examples/assets/animimg001.d \
./Middlewares/lvgl/examples/assets/animimg002.d \
./Middlewares/lvgl/examples/assets/animimg003.d \
./Middlewares/lvgl/examples/assets/img_caret_down.d \
./Middlewares/lvgl/examples/assets/img_cogwheel_argb.d \
./Middlewares/lvgl/examples/assets/img_cogwheel_indexed16.d \
./Middlewares/lvgl/examples/assets/img_cogwheel_rgb.d \
./Middlewares/lvgl/examples/assets/img_hand.d \
./Middlewares/lvgl/examples/assets/img_skew_strip.d \
./Middlewares/lvgl/examples/assets/img_star.d \
./Middlewares/lvgl/examples/assets/img_svg_img.d \
./Middlewares/lvgl/examples/assets/imgbtn_left.d \
./Middlewares/lvgl/examples/assets/imgbtn_mid.d \
./Middlewares/lvgl/examples/assets/imgbtn_right.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/examples/assets/%.o Middlewares/lvgl/examples/assets/%.su Middlewares/lvgl/examples/assets/%.cyclo: ../Middlewares/lvgl/examples/assets/%.c Middlewares/lvgl/examples/assets/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-examples-2f-assets

clean-Middlewares-2f-lvgl-2f-examples-2f-assets:
	-$(RM) ./Middlewares/lvgl/examples/assets/animimg001.cyclo ./Middlewares/lvgl/examples/assets/animimg001.d ./Middlewares/lvgl/examples/assets/animimg001.o ./Middlewares/lvgl/examples/assets/animimg001.su ./Middlewares/lvgl/examples/assets/animimg002.cyclo ./Middlewares/lvgl/examples/assets/animimg002.d ./Middlewares/lvgl/examples/assets/animimg002.o ./Middlewares/lvgl/examples/assets/animimg002.su ./Middlewares/lvgl/examples/assets/animimg003.cyclo ./Middlewares/lvgl/examples/assets/animimg003.d ./Middlewares/lvgl/examples/assets/animimg003.o ./Middlewares/lvgl/examples/assets/animimg003.su ./Middlewares/lvgl/examples/assets/img_caret_down.cyclo ./Middlewares/lvgl/examples/assets/img_caret_down.d ./Middlewares/lvgl/examples/assets/img_caret_down.o ./Middlewares/lvgl/examples/assets/img_caret_down.su ./Middlewares/lvgl/examples/assets/img_cogwheel_argb.cyclo ./Middlewares/lvgl/examples/assets/img_cogwheel_argb.d ./Middlewares/lvgl/examples/assets/img_cogwheel_argb.o ./Middlewares/lvgl/examples/assets/img_cogwheel_argb.su ./Middlewares/lvgl/examples/assets/img_cogwheel_indexed16.cyclo ./Middlewares/lvgl/examples/assets/img_cogwheel_indexed16.d ./Middlewares/lvgl/examples/assets/img_cogwheel_indexed16.o ./Middlewares/lvgl/examples/assets/img_cogwheel_indexed16.su ./Middlewares/lvgl/examples/assets/img_cogwheel_rgb.cyclo ./Middlewares/lvgl/examples/assets/img_cogwheel_rgb.d ./Middlewares/lvgl/examples/assets/img_cogwheel_rgb.o ./Middlewares/lvgl/examples/assets/img_cogwheel_rgb.su ./Middlewares/lvgl/examples/assets/img_hand.cyclo ./Middlewares/lvgl/examples/assets/img_hand.d ./Middlewares/lvgl/examples/assets/img_hand.o ./Middlewares/lvgl/examples/assets/img_hand.su ./Middlewares/lvgl/examples/assets/img_skew_strip.cyclo ./Middlewares/lvgl/examples/assets/img_skew_strip.d ./Middlewares/lvgl/examples/assets/img_skew_strip.o ./Middlewares/lvgl/examples/assets/img_skew_strip.su ./Middlewares/lvgl/examples/assets/img_star.cyclo ./Middlewares/lvgl/examples/assets/img_star.d ./Middlewares/lvgl/examples/assets/img_star.o ./Middlewares/lvgl/examples/assets/img_star.su ./Middlewares/lvgl/examples/assets/img_svg_img.cyclo ./Middlewares/lvgl/examples/assets/img_svg_img.d ./Middlewares/lvgl/examples/assets/img_svg_img.o ./Middlewares/lvgl/examples/assets/img_svg_img.su ./Middlewares/lvgl/examples/assets/imgbtn_left.cyclo ./Middlewares/lvgl/examples/assets/imgbtn_left.d ./Middlewares/lvgl/examples/assets/imgbtn_left.o ./Middlewares/lvgl/examples/assets/imgbtn_left.su ./Middlewares/lvgl/examples/assets/imgbtn_mid.cyclo ./Middlewares/lvgl/examples/assets/imgbtn_mid.d ./Middlewares/lvgl/examples/assets/imgbtn_mid.o ./Middlewares/lvgl/examples/assets/imgbtn_mid.su ./Middlewares/lvgl/examples/assets/imgbtn_right.cyclo ./Middlewares/lvgl/examples/assets/imgbtn_right.d ./Middlewares/lvgl/examples/assets/imgbtn_right.o ./Middlewares/lvgl/examples/assets/imgbtn_right.su

.PHONY: clean-Middlewares-2f-lvgl-2f-examples-2f-assets

