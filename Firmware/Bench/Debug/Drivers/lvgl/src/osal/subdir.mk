################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/osal/lv_cmsis_rtos2.c \
../Drivers/lvgl/src/osal/lv_freertos.c \
../Drivers/lvgl/src/osal/lv_linux.c \
../Drivers/lvgl/src/osal/lv_mqx.c \
../Drivers/lvgl/src/osal/lv_os.c \
../Drivers/lvgl/src/osal/lv_os_none.c \
../Drivers/lvgl/src/osal/lv_pthread.c \
../Drivers/lvgl/src/osal/lv_rtthread.c \
../Drivers/lvgl/src/osal/lv_sdl2.c \
../Drivers/lvgl/src/osal/lv_windows.c 

OBJS += \
./Drivers/lvgl/src/osal/lv_cmsis_rtos2.o \
./Drivers/lvgl/src/osal/lv_freertos.o \
./Drivers/lvgl/src/osal/lv_linux.o \
./Drivers/lvgl/src/osal/lv_mqx.o \
./Drivers/lvgl/src/osal/lv_os.o \
./Drivers/lvgl/src/osal/lv_os_none.o \
./Drivers/lvgl/src/osal/lv_pthread.o \
./Drivers/lvgl/src/osal/lv_rtthread.o \
./Drivers/lvgl/src/osal/lv_sdl2.o \
./Drivers/lvgl/src/osal/lv_windows.o 

C_DEPS += \
./Drivers/lvgl/src/osal/lv_cmsis_rtos2.d \
./Drivers/lvgl/src/osal/lv_freertos.d \
./Drivers/lvgl/src/osal/lv_linux.d \
./Drivers/lvgl/src/osal/lv_mqx.d \
./Drivers/lvgl/src/osal/lv_os.d \
./Drivers/lvgl/src/osal/lv_os_none.d \
./Drivers/lvgl/src/osal/lv_pthread.d \
./Drivers/lvgl/src/osal/lv_rtthread.d \
./Drivers/lvgl/src/osal/lv_sdl2.d \
./Drivers/lvgl/src/osal/lv_windows.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/osal/%.o Drivers/lvgl/src/osal/%.su Drivers/lvgl/src/osal/%.cyclo: ../Drivers/lvgl/src/osal/%.c Drivers/lvgl/src/osal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/home/joakim-wennergren/Desktop/Smartwatch/Firmware/Bench/Middlewares" -I"/home/joakim-wennergren/Desktop/Smartwatch/Firmware/Bench/Drivers/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-osal

clean-Drivers-2f-lvgl-2f-src-2f-osal:
	-$(RM) ./Drivers/lvgl/src/osal/lv_cmsis_rtos2.cyclo ./Drivers/lvgl/src/osal/lv_cmsis_rtos2.d ./Drivers/lvgl/src/osal/lv_cmsis_rtos2.o ./Drivers/lvgl/src/osal/lv_cmsis_rtos2.su ./Drivers/lvgl/src/osal/lv_freertos.cyclo ./Drivers/lvgl/src/osal/lv_freertos.d ./Drivers/lvgl/src/osal/lv_freertos.o ./Drivers/lvgl/src/osal/lv_freertos.su ./Drivers/lvgl/src/osal/lv_linux.cyclo ./Drivers/lvgl/src/osal/lv_linux.d ./Drivers/lvgl/src/osal/lv_linux.o ./Drivers/lvgl/src/osal/lv_linux.su ./Drivers/lvgl/src/osal/lv_mqx.cyclo ./Drivers/lvgl/src/osal/lv_mqx.d ./Drivers/lvgl/src/osal/lv_mqx.o ./Drivers/lvgl/src/osal/lv_mqx.su ./Drivers/lvgl/src/osal/lv_os.cyclo ./Drivers/lvgl/src/osal/lv_os.d ./Drivers/lvgl/src/osal/lv_os.o ./Drivers/lvgl/src/osal/lv_os.su ./Drivers/lvgl/src/osal/lv_os_none.cyclo ./Drivers/lvgl/src/osal/lv_os_none.d ./Drivers/lvgl/src/osal/lv_os_none.o ./Drivers/lvgl/src/osal/lv_os_none.su ./Drivers/lvgl/src/osal/lv_pthread.cyclo ./Drivers/lvgl/src/osal/lv_pthread.d ./Drivers/lvgl/src/osal/lv_pthread.o ./Drivers/lvgl/src/osal/lv_pthread.su ./Drivers/lvgl/src/osal/lv_rtthread.cyclo ./Drivers/lvgl/src/osal/lv_rtthread.d ./Drivers/lvgl/src/osal/lv_rtthread.o ./Drivers/lvgl/src/osal/lv_rtthread.su ./Drivers/lvgl/src/osal/lv_sdl2.cyclo ./Drivers/lvgl/src/osal/lv_sdl2.d ./Drivers/lvgl/src/osal/lv_sdl2.o ./Drivers/lvgl/src/osal/lv_sdl2.su ./Drivers/lvgl/src/osal/lv_windows.cyclo ./Drivers/lvgl/src/osal/lv_windows.d ./Drivers/lvgl/src/osal/lv_windows.o ./Drivers/lvgl/src/osal/lv_windows.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-osal

