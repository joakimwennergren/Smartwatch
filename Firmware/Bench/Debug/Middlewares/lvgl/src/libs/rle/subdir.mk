################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/libs/rle/lv_rle.c 

OBJS += \
./Middlewares/lvgl/src/libs/rle/lv_rle.o 

C_DEPS += \
./Middlewares/lvgl/src/libs/rle/lv_rle.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/libs/rle/%.o Middlewares/lvgl/src/libs/rle/%.su Middlewares/lvgl/src/libs/rle/%.cyclo: ../Middlewares/lvgl/src/libs/rle/%.c Middlewares/lvgl/src/libs/rle/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-libs-2f-rle

clean-Middlewares-2f-lvgl-2f-src-2f-libs-2f-rle:
	-$(RM) ./Middlewares/lvgl/src/libs/rle/lv_rle.cyclo ./Middlewares/lvgl/src/libs/rle/lv_rle.d ./Middlewares/lvgl/src/libs/rle/lv_rle.o ./Middlewares/lvgl/src/libs/rle/lv_rle.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-libs-2f-rle

