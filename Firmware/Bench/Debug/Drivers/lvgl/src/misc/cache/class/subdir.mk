################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/misc/cache/class/lv_cache_lru_ll.c \
../Drivers/lvgl/src/misc/cache/class/lv_cache_lru_rb.c 

OBJS += \
./Drivers/lvgl/src/misc/cache/class/lv_cache_lru_ll.o \
./Drivers/lvgl/src/misc/cache/class/lv_cache_lru_rb.o 

C_DEPS += \
./Drivers/lvgl/src/misc/cache/class/lv_cache_lru_ll.d \
./Drivers/lvgl/src/misc/cache/class/lv_cache_lru_rb.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/misc/cache/class/%.o Drivers/lvgl/src/misc/cache/class/%.su Drivers/lvgl/src/misc/cache/class/%.cyclo: ../Drivers/lvgl/src/misc/cache/class/%.c Drivers/lvgl/src/misc/cache/class/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/home/joakim-wennergren/Desktop/Smartwatch/Firmware/Bench/Middlewares" -I"/home/joakim-wennergren/Desktop/Smartwatch/Firmware/Bench/Drivers/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-misc-2f-cache-2f-class

clean-Drivers-2f-lvgl-2f-src-2f-misc-2f-cache-2f-class:
	-$(RM) ./Drivers/lvgl/src/misc/cache/class/lv_cache_lru_ll.cyclo ./Drivers/lvgl/src/misc/cache/class/lv_cache_lru_ll.d ./Drivers/lvgl/src/misc/cache/class/lv_cache_lru_ll.o ./Drivers/lvgl/src/misc/cache/class/lv_cache_lru_ll.su ./Drivers/lvgl/src/misc/cache/class/lv_cache_lru_rb.cyclo ./Drivers/lvgl/src/misc/cache/class/lv_cache_lru_rb.d ./Drivers/lvgl/src/misc/cache/class/lv_cache_lru_rb.o ./Drivers/lvgl/src/misc/cache/class/lv_cache_lru_rb.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-misc-2f-cache-2f-class

