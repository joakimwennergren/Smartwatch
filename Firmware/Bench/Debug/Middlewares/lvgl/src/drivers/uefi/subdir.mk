################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/drivers/uefi/lv_uefi_context.c \
../Middlewares/lvgl/src/drivers/uefi/lv_uefi_display.c \
../Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_keyboard.c \
../Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_pointer.c \
../Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_touch.c \
../Middlewares/lvgl/src/drivers/uefi/lv_uefi_private.c 

OBJS += \
./Middlewares/lvgl/src/drivers/uefi/lv_uefi_context.o \
./Middlewares/lvgl/src/drivers/uefi/lv_uefi_display.o \
./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_keyboard.o \
./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_pointer.o \
./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_touch.o \
./Middlewares/lvgl/src/drivers/uefi/lv_uefi_private.o 

C_DEPS += \
./Middlewares/lvgl/src/drivers/uefi/lv_uefi_context.d \
./Middlewares/lvgl/src/drivers/uefi/lv_uefi_display.d \
./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_keyboard.d \
./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_pointer.d \
./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_touch.d \
./Middlewares/lvgl/src/drivers/uefi/lv_uefi_private.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/drivers/uefi/%.o Middlewares/lvgl/src/drivers/uefi/%.su Middlewares/lvgl/src/drivers/uefi/%.cyclo: ../Middlewares/lvgl/src/drivers/uefi/%.c Middlewares/lvgl/src/drivers/uefi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-drivers-2f-uefi

clean-Middlewares-2f-lvgl-2f-src-2f-drivers-2f-uefi:
	-$(RM) ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_context.cyclo ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_context.d ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_context.o ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_context.su ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_display.cyclo ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_display.d ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_display.o ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_display.su ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_keyboard.cyclo ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_keyboard.d ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_keyboard.o ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_keyboard.su ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_pointer.cyclo ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_pointer.d ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_pointer.o ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_pointer.su ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_touch.cyclo ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_touch.d ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_touch.o ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_indev_touch.su ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_private.cyclo ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_private.d ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_private.o ./Middlewares/lvgl/src/drivers/uefi/lv_uefi_private.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-drivers-2f-uefi

