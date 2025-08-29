################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A1_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A2_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A4_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A8_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_ARGB8888_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I1_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I2_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I4_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I8_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_L8_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565A8_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB888_RLE_align1.c \
../Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_XRGB8888_RLE_align1.c 

OBJS += \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A1_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A2_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A4_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A8_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_ARGB8888_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I1_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I2_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I4_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I8_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_L8_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565A8_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB888_RLE_align1.o \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_XRGB8888_RLE_align1.o 

C_DEPS += \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A1_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A2_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A4_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A8_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_ARGB8888_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I1_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I2_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I4_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I8_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_L8_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565A8_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB888_RLE_align1.d \
./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_XRGB8888_RLE_align1.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/tests/test_images/stride_align1/RLE/%.o Middlewares/lvgl/tests/test_images/stride_align1/RLE/%.su Middlewares/lvgl/tests/test_images/stride_align1/RLE/%.cyclo: ../Middlewares/lvgl/tests/test_images/stride_align1/RLE/%.c Middlewares/lvgl/tests/test_images/stride_align1/RLE/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-tests-2f-test_images-2f-stride_align1-2f-RLE

clean-Middlewares-2f-lvgl-2f-tests-2f-test_images-2f-stride_align1-2f-RLE:
	-$(RM) ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A1_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A1_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A1_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A1_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A2_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A2_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A2_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A2_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A4_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A4_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A4_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A4_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A8_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A8_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A8_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_A8_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_ARGB8888_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_ARGB8888_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_ARGB8888_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_ARGB8888_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I1_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I1_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I1_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I1_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I2_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I2_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I2_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I2_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I4_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I4_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I4_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I4_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I8_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I8_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I8_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_I8_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_L8_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_L8_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_L8_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_L8_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565A8_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565A8_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565A8_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565A8_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB565_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB888_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB888_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB888_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_RGB888_RLE_align1.su ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_XRGB8888_RLE_align1.cyclo ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_XRGB8888_RLE_align1.d ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_XRGB8888_RLE_align1.o ./Middlewares/lvgl/tests/test_images/stride_align1/RLE/test_XRGB8888_RLE_align1.su

.PHONY: clean-Middlewares-2f-lvgl-2f-tests-2f-test_images-2f-stride_align1-2f-RLE

