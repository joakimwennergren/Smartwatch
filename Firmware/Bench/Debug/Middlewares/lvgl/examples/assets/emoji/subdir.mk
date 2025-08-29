################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/examples/assets/emoji/img_emoji_F617.c 

OBJS += \
./Middlewares/lvgl/examples/assets/emoji/img_emoji_F617.o 

C_DEPS += \
./Middlewares/lvgl/examples/assets/emoji/img_emoji_F617.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/examples/assets/emoji/%.o Middlewares/lvgl/examples/assets/emoji/%.su Middlewares/lvgl/examples/assets/emoji/%.cyclo: ../Middlewares/lvgl/examples/assets/emoji/%.c Middlewares/lvgl/examples/assets/emoji/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-examples-2f-assets-2f-emoji

clean-Middlewares-2f-lvgl-2f-examples-2f-assets-2f-emoji:
	-$(RM) ./Middlewares/lvgl/examples/assets/emoji/img_emoji_F617.cyclo ./Middlewares/lvgl/examples/assets/emoji/img_emoji_F617.d ./Middlewares/lvgl/examples/assets/emoji/img_emoji_F617.o ./Middlewares/lvgl/examples/assets/emoji/img_emoji_F617.su

.PHONY: clean-Middlewares-2f-lvgl-2f-examples-2f-assets-2f-emoji

