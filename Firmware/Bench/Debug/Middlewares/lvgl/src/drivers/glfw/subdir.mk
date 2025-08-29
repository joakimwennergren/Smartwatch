################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/drivers/glfw/lv_glfw_window.c \
../Middlewares/lvgl/src/drivers/glfw/lv_opengles_debug.c \
../Middlewares/lvgl/src/drivers/glfw/lv_opengles_driver.c \
../Middlewares/lvgl/src/drivers/glfw/lv_opengles_texture.c 

OBJS += \
./Middlewares/lvgl/src/drivers/glfw/lv_glfw_window.o \
./Middlewares/lvgl/src/drivers/glfw/lv_opengles_debug.o \
./Middlewares/lvgl/src/drivers/glfw/lv_opengles_driver.o \
./Middlewares/lvgl/src/drivers/glfw/lv_opengles_texture.o 

C_DEPS += \
./Middlewares/lvgl/src/drivers/glfw/lv_glfw_window.d \
./Middlewares/lvgl/src/drivers/glfw/lv_opengles_debug.d \
./Middlewares/lvgl/src/drivers/glfw/lv_opengles_driver.d \
./Middlewares/lvgl/src/drivers/glfw/lv_opengles_texture.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/drivers/glfw/%.o Middlewares/lvgl/src/drivers/glfw/%.su Middlewares/lvgl/src/drivers/glfw/%.cyclo: ../Middlewares/lvgl/src/drivers/glfw/%.c Middlewares/lvgl/src/drivers/glfw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-drivers-2f-glfw

clean-Middlewares-2f-lvgl-2f-src-2f-drivers-2f-glfw:
	-$(RM) ./Middlewares/lvgl/src/drivers/glfw/lv_glfw_window.cyclo ./Middlewares/lvgl/src/drivers/glfw/lv_glfw_window.d ./Middlewares/lvgl/src/drivers/glfw/lv_glfw_window.o ./Middlewares/lvgl/src/drivers/glfw/lv_glfw_window.su ./Middlewares/lvgl/src/drivers/glfw/lv_opengles_debug.cyclo ./Middlewares/lvgl/src/drivers/glfw/lv_opengles_debug.d ./Middlewares/lvgl/src/drivers/glfw/lv_opengles_debug.o ./Middlewares/lvgl/src/drivers/glfw/lv_opengles_debug.su ./Middlewares/lvgl/src/drivers/glfw/lv_opengles_driver.cyclo ./Middlewares/lvgl/src/drivers/glfw/lv_opengles_driver.d ./Middlewares/lvgl/src/drivers/glfw/lv_opengles_driver.o ./Middlewares/lvgl/src/drivers/glfw/lv_opengles_driver.su ./Middlewares/lvgl/src/drivers/glfw/lv_opengles_texture.cyclo ./Middlewares/lvgl/src/drivers/glfw/lv_opengles_texture.d ./Middlewares/lvgl/src/drivers/glfw/lv_opengles_texture.o ./Middlewares/lvgl/src/drivers/glfw/lv_opengles_texture.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-drivers-2f-glfw

