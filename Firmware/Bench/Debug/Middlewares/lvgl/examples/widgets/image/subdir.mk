################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/examples/widgets/image/lv_example_image_1.c \
../Middlewares/lvgl/examples/widgets/image/lv_example_image_2.c \
../Middlewares/lvgl/examples/widgets/image/lv_example_image_3.c \
../Middlewares/lvgl/examples/widgets/image/lv_example_image_4.c \
../Middlewares/lvgl/examples/widgets/image/lv_example_image_5.c 

OBJS += \
./Middlewares/lvgl/examples/widgets/image/lv_example_image_1.o \
./Middlewares/lvgl/examples/widgets/image/lv_example_image_2.o \
./Middlewares/lvgl/examples/widgets/image/lv_example_image_3.o \
./Middlewares/lvgl/examples/widgets/image/lv_example_image_4.o \
./Middlewares/lvgl/examples/widgets/image/lv_example_image_5.o 

C_DEPS += \
./Middlewares/lvgl/examples/widgets/image/lv_example_image_1.d \
./Middlewares/lvgl/examples/widgets/image/lv_example_image_2.d \
./Middlewares/lvgl/examples/widgets/image/lv_example_image_3.d \
./Middlewares/lvgl/examples/widgets/image/lv_example_image_4.d \
./Middlewares/lvgl/examples/widgets/image/lv_example_image_5.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/examples/widgets/image/%.o Middlewares/lvgl/examples/widgets/image/%.su Middlewares/lvgl/examples/widgets/image/%.cyclo: ../Middlewares/lvgl/examples/widgets/image/%.c Middlewares/lvgl/examples/widgets/image/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-examples-2f-widgets-2f-image

clean-Middlewares-2f-lvgl-2f-examples-2f-widgets-2f-image:
	-$(RM) ./Middlewares/lvgl/examples/widgets/image/lv_example_image_1.cyclo ./Middlewares/lvgl/examples/widgets/image/lv_example_image_1.d ./Middlewares/lvgl/examples/widgets/image/lv_example_image_1.o ./Middlewares/lvgl/examples/widgets/image/lv_example_image_1.su ./Middlewares/lvgl/examples/widgets/image/lv_example_image_2.cyclo ./Middlewares/lvgl/examples/widgets/image/lv_example_image_2.d ./Middlewares/lvgl/examples/widgets/image/lv_example_image_2.o ./Middlewares/lvgl/examples/widgets/image/lv_example_image_2.su ./Middlewares/lvgl/examples/widgets/image/lv_example_image_3.cyclo ./Middlewares/lvgl/examples/widgets/image/lv_example_image_3.d ./Middlewares/lvgl/examples/widgets/image/lv_example_image_3.o ./Middlewares/lvgl/examples/widgets/image/lv_example_image_3.su ./Middlewares/lvgl/examples/widgets/image/lv_example_image_4.cyclo ./Middlewares/lvgl/examples/widgets/image/lv_example_image_4.d ./Middlewares/lvgl/examples/widgets/image/lv_example_image_4.o ./Middlewares/lvgl/examples/widgets/image/lv_example_image_4.su ./Middlewares/lvgl/examples/widgets/image/lv_example_image_5.cyclo ./Middlewares/lvgl/examples/widgets/image/lv_example_image_5.d ./Middlewares/lvgl/examples/widgets/image/lv_example_image_5.o ./Middlewares/lvgl/examples/widgets/image/lv_example_image_5.su

.PHONY: clean-Middlewares-2f-lvgl-2f-examples-2f-widgets-2f-image

