################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/drivers/wayland/lv_wayland.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wayland_smm.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wl_cache.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wl_dmabuf.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wl_keyboard.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer_axis.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wl_seat.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wl_shell.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wl_shm.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wl_touch.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wl_window.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wl_window_decorations.c \
../Middlewares/lvgl/src/drivers/wayland/lv_wl_xdg_shell.c 

OBJS += \
./Middlewares/lvgl/src/drivers/wayland/lv_wayland.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wayland_smm.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_cache.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_dmabuf.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_keyboard.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer_axis.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_seat.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_shell.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_shm.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_touch.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_window.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_window_decorations.o \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_xdg_shell.o 

C_DEPS += \
./Middlewares/lvgl/src/drivers/wayland/lv_wayland.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wayland_smm.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_cache.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_dmabuf.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_keyboard.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer_axis.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_seat.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_shell.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_shm.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_touch.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_window.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_window_decorations.d \
./Middlewares/lvgl/src/drivers/wayland/lv_wl_xdg_shell.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/drivers/wayland/%.o Middlewares/lvgl/src/drivers/wayland/%.su Middlewares/lvgl/src/drivers/wayland/%.cyclo: ../Middlewares/lvgl/src/drivers/wayland/%.c Middlewares/lvgl/src/drivers/wayland/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-drivers-2f-wayland

clean-Middlewares-2f-lvgl-2f-src-2f-drivers-2f-wayland:
	-$(RM) ./Middlewares/lvgl/src/drivers/wayland/lv_wayland.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wayland.d ./Middlewares/lvgl/src/drivers/wayland/lv_wayland.o ./Middlewares/lvgl/src/drivers/wayland/lv_wayland.su ./Middlewares/lvgl/src/drivers/wayland/lv_wayland_smm.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wayland_smm.d ./Middlewares/lvgl/src/drivers/wayland/lv_wayland_smm.o ./Middlewares/lvgl/src/drivers/wayland/lv_wayland_smm.su ./Middlewares/lvgl/src/drivers/wayland/lv_wl_cache.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wl_cache.d ./Middlewares/lvgl/src/drivers/wayland/lv_wl_cache.o ./Middlewares/lvgl/src/drivers/wayland/lv_wl_cache.su ./Middlewares/lvgl/src/drivers/wayland/lv_wl_dmabuf.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wl_dmabuf.d ./Middlewares/lvgl/src/drivers/wayland/lv_wl_dmabuf.o ./Middlewares/lvgl/src/drivers/wayland/lv_wl_dmabuf.su ./Middlewares/lvgl/src/drivers/wayland/lv_wl_keyboard.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wl_keyboard.d ./Middlewares/lvgl/src/drivers/wayland/lv_wl_keyboard.o ./Middlewares/lvgl/src/drivers/wayland/lv_wl_keyboard.su ./Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer.d ./Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer.o ./Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer.su ./Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer_axis.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer_axis.d ./Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer_axis.o ./Middlewares/lvgl/src/drivers/wayland/lv_wl_pointer_axis.su ./Middlewares/lvgl/src/drivers/wayland/lv_wl_seat.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wl_seat.d ./Middlewares/lvgl/src/drivers/wayland/lv_wl_seat.o ./Middlewares/lvgl/src/drivers/wayland/lv_wl_seat.su ./Middlewares/lvgl/src/drivers/wayland/lv_wl_shell.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wl_shell.d ./Middlewares/lvgl/src/drivers/wayland/lv_wl_shell.o ./Middlewares/lvgl/src/drivers/wayland/lv_wl_shell.su ./Middlewares/lvgl/src/drivers/wayland/lv_wl_shm.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wl_shm.d ./Middlewares/lvgl/src/drivers/wayland/lv_wl_shm.o ./Middlewares/lvgl/src/drivers/wayland/lv_wl_shm.su ./Middlewares/lvgl/src/drivers/wayland/lv_wl_touch.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wl_touch.d ./Middlewares/lvgl/src/drivers/wayland/lv_wl_touch.o ./Middlewares/lvgl/src/drivers/wayland/lv_wl_touch.su ./Middlewares/lvgl/src/drivers/wayland/lv_wl_window.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wl_window.d ./Middlewares/lvgl/src/drivers/wayland/lv_wl_window.o ./Middlewares/lvgl/src/drivers/wayland/lv_wl_window.su ./Middlewares/lvgl/src/drivers/wayland/lv_wl_window_decorations.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wl_window_decorations.d ./Middlewares/lvgl/src/drivers/wayland/lv_wl_window_decorations.o ./Middlewares/lvgl/src/drivers/wayland/lv_wl_window_decorations.su ./Middlewares/lvgl/src/drivers/wayland/lv_wl_xdg_shell.cyclo ./Middlewares/lvgl/src/drivers/wayland/lv_wl_xdg_shell.d ./Middlewares/lvgl/src/drivers/wayland/lv_wl_xdg_shell.o ./Middlewares/lvgl/src/drivers/wayland/lv_wl_xdg_shell.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-drivers-2f-wayland

