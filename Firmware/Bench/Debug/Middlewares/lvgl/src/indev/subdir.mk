################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/indev/lv_indev.c \
../Middlewares/lvgl/src/indev/lv_indev_gesture.c \
../Middlewares/lvgl/src/indev/lv_indev_scroll.c 

OBJS += \
./Middlewares/lvgl/src/indev/lv_indev.o \
./Middlewares/lvgl/src/indev/lv_indev_gesture.o \
./Middlewares/lvgl/src/indev/lv_indev_scroll.o 

C_DEPS += \
./Middlewares/lvgl/src/indev/lv_indev.d \
./Middlewares/lvgl/src/indev/lv_indev_gesture.d \
./Middlewares/lvgl/src/indev/lv_indev_scroll.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/indev/%.o Middlewares/lvgl/src/indev/%.su Middlewares/lvgl/src/indev/%.cyclo: ../Middlewares/lvgl/src/indev/%.c Middlewares/lvgl/src/indev/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-indev

clean-Middlewares-2f-lvgl-2f-src-2f-indev:
	-$(RM) ./Middlewares/lvgl/src/indev/lv_indev.cyclo ./Middlewares/lvgl/src/indev/lv_indev.d ./Middlewares/lvgl/src/indev/lv_indev.o ./Middlewares/lvgl/src/indev/lv_indev.su ./Middlewares/lvgl/src/indev/lv_indev_gesture.cyclo ./Middlewares/lvgl/src/indev/lv_indev_gesture.d ./Middlewares/lvgl/src/indev/lv_indev_gesture.o ./Middlewares/lvgl/src/indev/lv_indev_gesture.su ./Middlewares/lvgl/src/indev/lv_indev_scroll.cyclo ./Middlewares/lvgl/src/indev/lv_indev_scroll.d ./Middlewares/lvgl/src/indev/lv_indev_scroll.o ./Middlewares/lvgl/src/indev/lv_indev_scroll.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-indev

