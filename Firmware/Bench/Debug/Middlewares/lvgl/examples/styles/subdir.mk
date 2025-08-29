################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/examples/styles/lv_example_style_1.c \
../Middlewares/lvgl/examples/styles/lv_example_style_10.c \
../Middlewares/lvgl/examples/styles/lv_example_style_11.c \
../Middlewares/lvgl/examples/styles/lv_example_style_12.c \
../Middlewares/lvgl/examples/styles/lv_example_style_13.c \
../Middlewares/lvgl/examples/styles/lv_example_style_14.c \
../Middlewares/lvgl/examples/styles/lv_example_style_15.c \
../Middlewares/lvgl/examples/styles/lv_example_style_16.c \
../Middlewares/lvgl/examples/styles/lv_example_style_17.c \
../Middlewares/lvgl/examples/styles/lv_example_style_18.c \
../Middlewares/lvgl/examples/styles/lv_example_style_19.c \
../Middlewares/lvgl/examples/styles/lv_example_style_2.c \
../Middlewares/lvgl/examples/styles/lv_example_style_3.c \
../Middlewares/lvgl/examples/styles/lv_example_style_4.c \
../Middlewares/lvgl/examples/styles/lv_example_style_5.c \
../Middlewares/lvgl/examples/styles/lv_example_style_6.c \
../Middlewares/lvgl/examples/styles/lv_example_style_7.c \
../Middlewares/lvgl/examples/styles/lv_example_style_8.c \
../Middlewares/lvgl/examples/styles/lv_example_style_9.c 

OBJS += \
./Middlewares/lvgl/examples/styles/lv_example_style_1.o \
./Middlewares/lvgl/examples/styles/lv_example_style_10.o \
./Middlewares/lvgl/examples/styles/lv_example_style_11.o \
./Middlewares/lvgl/examples/styles/lv_example_style_12.o \
./Middlewares/lvgl/examples/styles/lv_example_style_13.o \
./Middlewares/lvgl/examples/styles/lv_example_style_14.o \
./Middlewares/lvgl/examples/styles/lv_example_style_15.o \
./Middlewares/lvgl/examples/styles/lv_example_style_16.o \
./Middlewares/lvgl/examples/styles/lv_example_style_17.o \
./Middlewares/lvgl/examples/styles/lv_example_style_18.o \
./Middlewares/lvgl/examples/styles/lv_example_style_19.o \
./Middlewares/lvgl/examples/styles/lv_example_style_2.o \
./Middlewares/lvgl/examples/styles/lv_example_style_3.o \
./Middlewares/lvgl/examples/styles/lv_example_style_4.o \
./Middlewares/lvgl/examples/styles/lv_example_style_5.o \
./Middlewares/lvgl/examples/styles/lv_example_style_6.o \
./Middlewares/lvgl/examples/styles/lv_example_style_7.o \
./Middlewares/lvgl/examples/styles/lv_example_style_8.o \
./Middlewares/lvgl/examples/styles/lv_example_style_9.o 

C_DEPS += \
./Middlewares/lvgl/examples/styles/lv_example_style_1.d \
./Middlewares/lvgl/examples/styles/lv_example_style_10.d \
./Middlewares/lvgl/examples/styles/lv_example_style_11.d \
./Middlewares/lvgl/examples/styles/lv_example_style_12.d \
./Middlewares/lvgl/examples/styles/lv_example_style_13.d \
./Middlewares/lvgl/examples/styles/lv_example_style_14.d \
./Middlewares/lvgl/examples/styles/lv_example_style_15.d \
./Middlewares/lvgl/examples/styles/lv_example_style_16.d \
./Middlewares/lvgl/examples/styles/lv_example_style_17.d \
./Middlewares/lvgl/examples/styles/lv_example_style_18.d \
./Middlewares/lvgl/examples/styles/lv_example_style_19.d \
./Middlewares/lvgl/examples/styles/lv_example_style_2.d \
./Middlewares/lvgl/examples/styles/lv_example_style_3.d \
./Middlewares/lvgl/examples/styles/lv_example_style_4.d \
./Middlewares/lvgl/examples/styles/lv_example_style_5.d \
./Middlewares/lvgl/examples/styles/lv_example_style_6.d \
./Middlewares/lvgl/examples/styles/lv_example_style_7.d \
./Middlewares/lvgl/examples/styles/lv_example_style_8.d \
./Middlewares/lvgl/examples/styles/lv_example_style_9.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/examples/styles/%.o Middlewares/lvgl/examples/styles/%.su Middlewares/lvgl/examples/styles/%.cyclo: ../Middlewares/lvgl/examples/styles/%.c Middlewares/lvgl/examples/styles/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-examples-2f-styles

clean-Middlewares-2f-lvgl-2f-examples-2f-styles:
	-$(RM) ./Middlewares/lvgl/examples/styles/lv_example_style_1.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_1.d ./Middlewares/lvgl/examples/styles/lv_example_style_1.o ./Middlewares/lvgl/examples/styles/lv_example_style_1.su ./Middlewares/lvgl/examples/styles/lv_example_style_10.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_10.d ./Middlewares/lvgl/examples/styles/lv_example_style_10.o ./Middlewares/lvgl/examples/styles/lv_example_style_10.su ./Middlewares/lvgl/examples/styles/lv_example_style_11.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_11.d ./Middlewares/lvgl/examples/styles/lv_example_style_11.o ./Middlewares/lvgl/examples/styles/lv_example_style_11.su ./Middlewares/lvgl/examples/styles/lv_example_style_12.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_12.d ./Middlewares/lvgl/examples/styles/lv_example_style_12.o ./Middlewares/lvgl/examples/styles/lv_example_style_12.su ./Middlewares/lvgl/examples/styles/lv_example_style_13.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_13.d ./Middlewares/lvgl/examples/styles/lv_example_style_13.o ./Middlewares/lvgl/examples/styles/lv_example_style_13.su ./Middlewares/lvgl/examples/styles/lv_example_style_14.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_14.d ./Middlewares/lvgl/examples/styles/lv_example_style_14.o ./Middlewares/lvgl/examples/styles/lv_example_style_14.su ./Middlewares/lvgl/examples/styles/lv_example_style_15.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_15.d ./Middlewares/lvgl/examples/styles/lv_example_style_15.o ./Middlewares/lvgl/examples/styles/lv_example_style_15.su ./Middlewares/lvgl/examples/styles/lv_example_style_16.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_16.d ./Middlewares/lvgl/examples/styles/lv_example_style_16.o ./Middlewares/lvgl/examples/styles/lv_example_style_16.su ./Middlewares/lvgl/examples/styles/lv_example_style_17.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_17.d ./Middlewares/lvgl/examples/styles/lv_example_style_17.o ./Middlewares/lvgl/examples/styles/lv_example_style_17.su ./Middlewares/lvgl/examples/styles/lv_example_style_18.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_18.d ./Middlewares/lvgl/examples/styles/lv_example_style_18.o ./Middlewares/lvgl/examples/styles/lv_example_style_18.su ./Middlewares/lvgl/examples/styles/lv_example_style_19.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_19.d ./Middlewares/lvgl/examples/styles/lv_example_style_19.o ./Middlewares/lvgl/examples/styles/lv_example_style_19.su ./Middlewares/lvgl/examples/styles/lv_example_style_2.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_2.d ./Middlewares/lvgl/examples/styles/lv_example_style_2.o ./Middlewares/lvgl/examples/styles/lv_example_style_2.su ./Middlewares/lvgl/examples/styles/lv_example_style_3.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_3.d ./Middlewares/lvgl/examples/styles/lv_example_style_3.o ./Middlewares/lvgl/examples/styles/lv_example_style_3.su ./Middlewares/lvgl/examples/styles/lv_example_style_4.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_4.d ./Middlewares/lvgl/examples/styles/lv_example_style_4.o ./Middlewares/lvgl/examples/styles/lv_example_style_4.su ./Middlewares/lvgl/examples/styles/lv_example_style_5.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_5.d ./Middlewares/lvgl/examples/styles/lv_example_style_5.o ./Middlewares/lvgl/examples/styles/lv_example_style_5.su ./Middlewares/lvgl/examples/styles/lv_example_style_6.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_6.d ./Middlewares/lvgl/examples/styles/lv_example_style_6.o ./Middlewares/lvgl/examples/styles/lv_example_style_6.su ./Middlewares/lvgl/examples/styles/lv_example_style_7.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_7.d ./Middlewares/lvgl/examples/styles/lv_example_style_7.o ./Middlewares/lvgl/examples/styles/lv_example_style_7.su ./Middlewares/lvgl/examples/styles/lv_example_style_8.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_8.d ./Middlewares/lvgl/examples/styles/lv_example_style_8.o ./Middlewares/lvgl/examples/styles/lv_example_style_8.su ./Middlewares/lvgl/examples/styles/lv_example_style_9.cyclo ./Middlewares/lvgl/examples/styles/lv_example_style_9.d ./Middlewares/lvgl/examples/styles/lv_example_style_9.o ./Middlewares/lvgl/examples/styles/lv_example_style_9.su

.PHONY: clean-Middlewares-2f-lvgl-2f-examples-2f-styles

