################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/libs/barcode/code128.c \
../Drivers/lvgl/src/libs/barcode/lv_barcode.c 

OBJS += \
./Drivers/lvgl/src/libs/barcode/code128.o \
./Drivers/lvgl/src/libs/barcode/lv_barcode.o 

C_DEPS += \
./Drivers/lvgl/src/libs/barcode/code128.d \
./Drivers/lvgl/src/libs/barcode/lv_barcode.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/libs/barcode/%.o Drivers/lvgl/src/libs/barcode/%.su Drivers/lvgl/src/libs/barcode/%.cyclo: ../Drivers/lvgl/src/libs/barcode/%.c Drivers/lvgl/src/libs/barcode/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/home/joakim-wennergren/Desktop/Smartwatch/Firmware/Bench/Middlewares" -I"/home/joakim-wennergren/Desktop/Smartwatch/Firmware/Bench/Drivers/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-barcode

clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-barcode:
	-$(RM) ./Drivers/lvgl/src/libs/barcode/code128.cyclo ./Drivers/lvgl/src/libs/barcode/code128.d ./Drivers/lvgl/src/libs/barcode/code128.o ./Drivers/lvgl/src/libs/barcode/code128.su ./Drivers/lvgl/src/libs/barcode/lv_barcode.cyclo ./Drivers/lvgl/src/libs/barcode/lv_barcode.d ./Drivers/lvgl/src/libs/barcode/lv_barcode.o ./Drivers/lvgl/src/libs/barcode/lv_barcode.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-libs-2f-barcode

