################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/examples/widgets/label/lv_example_label_1.c \
../Middlewares/lvgl/examples/widgets/label/lv_example_label_2.c \
../Middlewares/lvgl/examples/widgets/label/lv_example_label_3.c \
../Middlewares/lvgl/examples/widgets/label/lv_example_label_4.c \
../Middlewares/lvgl/examples/widgets/label/lv_example_label_5.c \
../Middlewares/lvgl/examples/widgets/label/lv_example_label_6.c 

OBJS += \
./Middlewares/lvgl/examples/widgets/label/lv_example_label_1.o \
./Middlewares/lvgl/examples/widgets/label/lv_example_label_2.o \
./Middlewares/lvgl/examples/widgets/label/lv_example_label_3.o \
./Middlewares/lvgl/examples/widgets/label/lv_example_label_4.o \
./Middlewares/lvgl/examples/widgets/label/lv_example_label_5.o \
./Middlewares/lvgl/examples/widgets/label/lv_example_label_6.o 

C_DEPS += \
./Middlewares/lvgl/examples/widgets/label/lv_example_label_1.d \
./Middlewares/lvgl/examples/widgets/label/lv_example_label_2.d \
./Middlewares/lvgl/examples/widgets/label/lv_example_label_3.d \
./Middlewares/lvgl/examples/widgets/label/lv_example_label_4.d \
./Middlewares/lvgl/examples/widgets/label/lv_example_label_5.d \
./Middlewares/lvgl/examples/widgets/label/lv_example_label_6.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/examples/widgets/label/%.o Middlewares/lvgl/examples/widgets/label/%.su Middlewares/lvgl/examples/widgets/label/%.cyclo: ../Middlewares/lvgl/examples/widgets/label/%.c Middlewares/lvgl/examples/widgets/label/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-examples-2f-widgets-2f-label

clean-Middlewares-2f-lvgl-2f-examples-2f-widgets-2f-label:
	-$(RM) ./Middlewares/lvgl/examples/widgets/label/lv_example_label_1.cyclo ./Middlewares/lvgl/examples/widgets/label/lv_example_label_1.d ./Middlewares/lvgl/examples/widgets/label/lv_example_label_1.o ./Middlewares/lvgl/examples/widgets/label/lv_example_label_1.su ./Middlewares/lvgl/examples/widgets/label/lv_example_label_2.cyclo ./Middlewares/lvgl/examples/widgets/label/lv_example_label_2.d ./Middlewares/lvgl/examples/widgets/label/lv_example_label_2.o ./Middlewares/lvgl/examples/widgets/label/lv_example_label_2.su ./Middlewares/lvgl/examples/widgets/label/lv_example_label_3.cyclo ./Middlewares/lvgl/examples/widgets/label/lv_example_label_3.d ./Middlewares/lvgl/examples/widgets/label/lv_example_label_3.o ./Middlewares/lvgl/examples/widgets/label/lv_example_label_3.su ./Middlewares/lvgl/examples/widgets/label/lv_example_label_4.cyclo ./Middlewares/lvgl/examples/widgets/label/lv_example_label_4.d ./Middlewares/lvgl/examples/widgets/label/lv_example_label_4.o ./Middlewares/lvgl/examples/widgets/label/lv_example_label_4.su ./Middlewares/lvgl/examples/widgets/label/lv_example_label_5.cyclo ./Middlewares/lvgl/examples/widgets/label/lv_example_label_5.d ./Middlewares/lvgl/examples/widgets/label/lv_example_label_5.o ./Middlewares/lvgl/examples/widgets/label/lv_example_label_5.su ./Middlewares/lvgl/examples/widgets/label/lv_example_label_6.cyclo ./Middlewares/lvgl/examples/widgets/label/lv_example_label_6.d ./Middlewares/lvgl/examples/widgets/label/lv_example_label_6.o ./Middlewares/lvgl/examples/widgets/label/lv_example_label_6.su

.PHONY: clean-Middlewares-2f-lvgl-2f-examples-2f-widgets-2f-label

