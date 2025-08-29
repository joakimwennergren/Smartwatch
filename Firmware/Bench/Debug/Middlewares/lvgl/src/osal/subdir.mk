################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/osal/lv_cmsis_rtos2.c \
../Middlewares/lvgl/src/osal/lv_freertos.c \
../Middlewares/lvgl/src/osal/lv_linux.c \
../Middlewares/lvgl/src/osal/lv_mqx.c \
../Middlewares/lvgl/src/osal/lv_os.c \
../Middlewares/lvgl/src/osal/lv_os_none.c \
../Middlewares/lvgl/src/osal/lv_pthread.c \
../Middlewares/lvgl/src/osal/lv_rtthread.c \
../Middlewares/lvgl/src/osal/lv_sdl2.c \
../Middlewares/lvgl/src/osal/lv_windows.c 

OBJS += \
./Middlewares/lvgl/src/osal/lv_cmsis_rtos2.o \
./Middlewares/lvgl/src/osal/lv_freertos.o \
./Middlewares/lvgl/src/osal/lv_linux.o \
./Middlewares/lvgl/src/osal/lv_mqx.o \
./Middlewares/lvgl/src/osal/lv_os.o \
./Middlewares/lvgl/src/osal/lv_os_none.o \
./Middlewares/lvgl/src/osal/lv_pthread.o \
./Middlewares/lvgl/src/osal/lv_rtthread.o \
./Middlewares/lvgl/src/osal/lv_sdl2.o \
./Middlewares/lvgl/src/osal/lv_windows.o 

C_DEPS += \
./Middlewares/lvgl/src/osal/lv_cmsis_rtos2.d \
./Middlewares/lvgl/src/osal/lv_freertos.d \
./Middlewares/lvgl/src/osal/lv_linux.d \
./Middlewares/lvgl/src/osal/lv_mqx.d \
./Middlewares/lvgl/src/osal/lv_os.d \
./Middlewares/lvgl/src/osal/lv_os_none.d \
./Middlewares/lvgl/src/osal/lv_pthread.d \
./Middlewares/lvgl/src/osal/lv_rtthread.d \
./Middlewares/lvgl/src/osal/lv_sdl2.d \
./Middlewares/lvgl/src/osal/lv_windows.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/osal/%.o Middlewares/lvgl/src/osal/%.su Middlewares/lvgl/src/osal/%.cyclo: ../Middlewares/lvgl/src/osal/%.c Middlewares/lvgl/src/osal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-osal

clean-Middlewares-2f-lvgl-2f-src-2f-osal:
	-$(RM) ./Middlewares/lvgl/src/osal/lv_cmsis_rtos2.cyclo ./Middlewares/lvgl/src/osal/lv_cmsis_rtos2.d ./Middlewares/lvgl/src/osal/lv_cmsis_rtos2.o ./Middlewares/lvgl/src/osal/lv_cmsis_rtos2.su ./Middlewares/lvgl/src/osal/lv_freertos.cyclo ./Middlewares/lvgl/src/osal/lv_freertos.d ./Middlewares/lvgl/src/osal/lv_freertos.o ./Middlewares/lvgl/src/osal/lv_freertos.su ./Middlewares/lvgl/src/osal/lv_linux.cyclo ./Middlewares/lvgl/src/osal/lv_linux.d ./Middlewares/lvgl/src/osal/lv_linux.o ./Middlewares/lvgl/src/osal/lv_linux.su ./Middlewares/lvgl/src/osal/lv_mqx.cyclo ./Middlewares/lvgl/src/osal/lv_mqx.d ./Middlewares/lvgl/src/osal/lv_mqx.o ./Middlewares/lvgl/src/osal/lv_mqx.su ./Middlewares/lvgl/src/osal/lv_os.cyclo ./Middlewares/lvgl/src/osal/lv_os.d ./Middlewares/lvgl/src/osal/lv_os.o ./Middlewares/lvgl/src/osal/lv_os.su ./Middlewares/lvgl/src/osal/lv_os_none.cyclo ./Middlewares/lvgl/src/osal/lv_os_none.d ./Middlewares/lvgl/src/osal/lv_os_none.o ./Middlewares/lvgl/src/osal/lv_os_none.su ./Middlewares/lvgl/src/osal/lv_pthread.cyclo ./Middlewares/lvgl/src/osal/lv_pthread.d ./Middlewares/lvgl/src/osal/lv_pthread.o ./Middlewares/lvgl/src/osal/lv_pthread.su ./Middlewares/lvgl/src/osal/lv_rtthread.cyclo ./Middlewares/lvgl/src/osal/lv_rtthread.d ./Middlewares/lvgl/src/osal/lv_rtthread.o ./Middlewares/lvgl/src/osal/lv_rtthread.su ./Middlewares/lvgl/src/osal/lv_sdl2.cyclo ./Middlewares/lvgl/src/osal/lv_sdl2.d ./Middlewares/lvgl/src/osal/lv_sdl2.o ./Middlewares/lvgl/src/osal/lv_sdl2.su ./Middlewares/lvgl/src/osal/lv_windows.cyclo ./Middlewares/lvgl/src/osal/lv_windows.d ./Middlewares/lvgl/src/osal/lv_windows.o ./Middlewares/lvgl/src/osal/lv_windows.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-osal

