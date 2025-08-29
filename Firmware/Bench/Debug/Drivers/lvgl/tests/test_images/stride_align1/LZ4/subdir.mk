################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A1_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A2_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A4_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A8_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_ARGB8888_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I1_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I2_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I4_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I8_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_L8_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565A8_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB888_LZ4_align1.c \
../Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_XRGB8888_LZ4_align1.c 

OBJS += \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A1_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A2_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A4_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A8_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_ARGB8888_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I1_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I2_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I4_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I8_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_L8_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565A8_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB888_LZ4_align1.o \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_XRGB8888_LZ4_align1.o 

C_DEPS += \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A1_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A2_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A4_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A8_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_ARGB8888_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I1_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I2_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I4_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I8_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_L8_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565A8_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB888_LZ4_align1.d \
./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_XRGB8888_LZ4_align1.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/tests/test_images/stride_align1/LZ4/%.o Drivers/lvgl/tests/test_images/stride_align1/LZ4/%.su Drivers/lvgl/tests/test_images/stride_align1/LZ4/%.cyclo: ../Drivers/lvgl/tests/test_images/stride_align1/LZ4/%.c Drivers/lvgl/tests/test_images/stride_align1/LZ4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Drivers/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-tests-2f-test_images-2f-stride_align1-2f-LZ4

clean-Drivers-2f-lvgl-2f-tests-2f-test_images-2f-stride_align1-2f-LZ4:
	-$(RM) ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A1_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A1_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A1_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A1_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A2_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A2_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A2_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A2_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A4_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A4_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A4_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A4_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A8_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A8_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A8_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_A8_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_ARGB8888_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_ARGB8888_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_ARGB8888_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_ARGB8888_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I1_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I1_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I1_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I1_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I2_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I2_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I2_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I2_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I4_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I4_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I4_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I4_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I8_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I8_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I8_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_I8_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_L8_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_L8_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_L8_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_L8_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565A8_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565A8_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565A8_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565A8_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB565_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB888_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB888_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB888_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_RGB888_LZ4_align1.su ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_XRGB8888_LZ4_align1.cyclo ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_XRGB8888_LZ4_align1.d ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_XRGB8888_LZ4_align1.o ./Drivers/lvgl/tests/test_images/stride_align1/LZ4/test_XRGB8888_LZ4_align1.su

.PHONY: clean-Drivers-2f-lvgl-2f-tests-2f-test_images-2f-stride_align1-2f-LZ4

