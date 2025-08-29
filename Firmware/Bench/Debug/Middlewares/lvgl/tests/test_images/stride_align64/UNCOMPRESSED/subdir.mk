################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A1_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A2_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A4_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A8_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_ARGB8888_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I1_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I2_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I4_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I8_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_L8_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565A8_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB888_NONE_align64.c \
../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_XRGB8888_NONE_align64.c 

OBJS += \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A1_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A2_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A4_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A8_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_ARGB8888_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I1_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I2_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I4_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I8_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_L8_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565A8_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB888_NONE_align64.o \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_XRGB8888_NONE_align64.o 

C_DEPS += \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A1_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A2_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A4_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A8_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_ARGB8888_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I1_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I2_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I4_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I8_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_L8_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565A8_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB888_NONE_align64.d \
./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_XRGB8888_NONE_align64.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/%.o Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/%.su Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/%.cyclo: ../Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/%.c Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-tests-2f-test_images-2f-stride_align64-2f-UNCOMPRESSED

clean-Middlewares-2f-lvgl-2f-tests-2f-test_images-2f-stride_align64-2f-UNCOMPRESSED:
	-$(RM) ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A1_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A1_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A1_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A1_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A2_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A2_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A2_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A2_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A4_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A4_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A4_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A4_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A8_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A8_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A8_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_A8_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_ARGB8888_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_ARGB8888_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_ARGB8888_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_ARGB8888_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I1_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I1_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I1_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I1_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I2_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I2_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I2_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I2_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I4_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I4_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I4_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I4_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I8_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I8_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I8_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_I8_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_L8_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_L8_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_L8_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_L8_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565A8_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565A8_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565A8_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565A8_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB565_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB888_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB888_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB888_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_RGB888_NONE_align64.su ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_XRGB8888_NONE_align64.cyclo ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_XRGB8888_NONE_align64.d ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_XRGB8888_NONE_align64.o ./Middlewares/lvgl/tests/test_images/stride_align64/UNCOMPRESSED/test_XRGB8888_NONE_align64.su

.PHONY: clean-Middlewares-2f-lvgl-2f-tests-2f-test_images-2f-stride_align64-2f-UNCOMPRESSED

