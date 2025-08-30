################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/others/test/lv_test_display.c \
../Drivers/lvgl/src/others/test/lv_test_helpers.c \
../Drivers/lvgl/src/others/test/lv_test_indev.c \
../Drivers/lvgl/src/others/test/lv_test_indev_gesture.c \
../Drivers/lvgl/src/others/test/lv_test_screenshot_compare.c 

OBJS += \
./Drivers/lvgl/src/others/test/lv_test_display.o \
./Drivers/lvgl/src/others/test/lv_test_helpers.o \
./Drivers/lvgl/src/others/test/lv_test_indev.o \
./Drivers/lvgl/src/others/test/lv_test_indev_gesture.o \
./Drivers/lvgl/src/others/test/lv_test_screenshot_compare.o 

C_DEPS += \
./Drivers/lvgl/src/others/test/lv_test_display.d \
./Drivers/lvgl/src/others/test/lv_test_helpers.d \
./Drivers/lvgl/src/others/test/lv_test_indev.d \
./Drivers/lvgl/src/others/test/lv_test_indev_gesture.d \
./Drivers/lvgl/src/others/test/lv_test_screenshot_compare.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/others/test/%.o Drivers/lvgl/src/others/test/%.su Drivers/lvgl/src/others/test/%.cyclo: ../Drivers/lvgl/src/others/test/%.c Drivers/lvgl/src/others/test/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/home/joakim-wennergren/Desktop/Smartwatch/Firmware/Bench/Drivers/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-others-2f-test

clean-Drivers-2f-lvgl-2f-src-2f-others-2f-test:
	-$(RM) ./Drivers/lvgl/src/others/test/lv_test_display.cyclo ./Drivers/lvgl/src/others/test/lv_test_display.d ./Drivers/lvgl/src/others/test/lv_test_display.o ./Drivers/lvgl/src/others/test/lv_test_display.su ./Drivers/lvgl/src/others/test/lv_test_helpers.cyclo ./Drivers/lvgl/src/others/test/lv_test_helpers.d ./Drivers/lvgl/src/others/test/lv_test_helpers.o ./Drivers/lvgl/src/others/test/lv_test_helpers.su ./Drivers/lvgl/src/others/test/lv_test_indev.cyclo ./Drivers/lvgl/src/others/test/lv_test_indev.d ./Drivers/lvgl/src/others/test/lv_test_indev.o ./Drivers/lvgl/src/others/test/lv_test_indev.su ./Drivers/lvgl/src/others/test/lv_test_indev_gesture.cyclo ./Drivers/lvgl/src/others/test/lv_test_indev_gesture.d ./Drivers/lvgl/src/others/test/lv_test_indev_gesture.o ./Drivers/lvgl/src/others/test/lv_test_indev_gesture.su ./Drivers/lvgl/src/others/test/lv_test_screenshot_compare.cyclo ./Drivers/lvgl/src/others/test/lv_test_screenshot_compare.d ./Drivers/lvgl/src/others/test/lv_test_screenshot_compare.o ./Drivers/lvgl/src/others/test/lv_test_screenshot_compare.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-others-2f-test

