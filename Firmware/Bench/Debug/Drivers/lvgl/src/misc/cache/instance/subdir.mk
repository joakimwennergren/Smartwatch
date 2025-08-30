################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/misc/cache/instance/lv_image_cache.c \
../Drivers/lvgl/src/misc/cache/instance/lv_image_header_cache.c 

OBJS += \
./Drivers/lvgl/src/misc/cache/instance/lv_image_cache.o \
./Drivers/lvgl/src/misc/cache/instance/lv_image_header_cache.o 

C_DEPS += \
./Drivers/lvgl/src/misc/cache/instance/lv_image_cache.d \
./Drivers/lvgl/src/misc/cache/instance/lv_image_header_cache.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/misc/cache/instance/%.o Drivers/lvgl/src/misc/cache/instance/%.su Drivers/lvgl/src/misc/cache/instance/%.cyclo: ../Drivers/lvgl/src/misc/cache/instance/%.c Drivers/lvgl/src/misc/cache/instance/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I"/Users/joakimwennergren/Desktop/Smartwatch/Firmware/Bench/Drivers/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-misc-2f-cache-2f-instance

clean-Drivers-2f-lvgl-2f-src-2f-misc-2f-cache-2f-instance:
	-$(RM) ./Drivers/lvgl/src/misc/cache/instance/lv_image_cache.cyclo ./Drivers/lvgl/src/misc/cache/instance/lv_image_cache.d ./Drivers/lvgl/src/misc/cache/instance/lv_image_cache.o ./Drivers/lvgl/src/misc/cache/instance/lv_image_cache.su ./Drivers/lvgl/src/misc/cache/instance/lv_image_header_cache.cyclo ./Drivers/lvgl/src/misc/cache/instance/lv_image_header_cache.d ./Drivers/lvgl/src/misc/cache/instance/lv_image_header_cache.o ./Drivers/lvgl/src/misc/cache/instance/lv_image_header_cache.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-misc-2f-cache-2f-instance

