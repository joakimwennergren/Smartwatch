################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/battery.c \
../Core/Src/brightness.c \
../Core/Src/display.c \
../Core/Src/main.c \
../Core/Src/nunito_68.c \
../Core/Src/roboto_28.c \
../Core/Src/roboto_38.c \
../Core/Src/roboto_58.c \
../Core/Src/stm32u5xx_hal_msp.c \
../Core/Src/stm32u5xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32u5xx.c \
../Core/Src/tree.c \
../Core/Src/tree_and_grass.c 

OBJS += \
./Core/Src/battery.o \
./Core/Src/brightness.o \
./Core/Src/display.o \
./Core/Src/main.o \
./Core/Src/nunito_68.o \
./Core/Src/roboto_28.o \
./Core/Src/roboto_38.o \
./Core/Src/roboto_58.o \
./Core/Src/stm32u5xx_hal_msp.o \
./Core/Src/stm32u5xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32u5xx.o \
./Core/Src/tree.o \
./Core/Src/tree_and_grass.o 

C_DEPS += \
./Core/Src/battery.d \
./Core/Src/brightness.d \
./Core/Src/display.d \
./Core/Src/main.d \
./Core/Src/nunito_68.d \
./Core/Src/roboto_28.d \
./Core/Src/roboto_38.d \
./Core/Src/roboto_58.d \
./Core/Src/stm32u5xx_hal_msp.d \
./Core/Src/stm32u5xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32u5xx.d \
./Core/Src/tree.d \
./Core/Src/tree_and_grass.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Drivers/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/battery.cyclo ./Core/Src/battery.d ./Core/Src/battery.o ./Core/Src/battery.su ./Core/Src/brightness.cyclo ./Core/Src/brightness.d ./Core/Src/brightness.o ./Core/Src/brightness.su ./Core/Src/display.cyclo ./Core/Src/display.d ./Core/Src/display.o ./Core/Src/display.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/nunito_68.cyclo ./Core/Src/nunito_68.d ./Core/Src/nunito_68.o ./Core/Src/nunito_68.su ./Core/Src/roboto_28.cyclo ./Core/Src/roboto_28.d ./Core/Src/roboto_28.o ./Core/Src/roboto_28.su ./Core/Src/roboto_38.cyclo ./Core/Src/roboto_38.d ./Core/Src/roboto_38.o ./Core/Src/roboto_38.su ./Core/Src/roboto_58.cyclo ./Core/Src/roboto_58.d ./Core/Src/roboto_58.o ./Core/Src/roboto_58.su ./Core/Src/stm32u5xx_hal_msp.cyclo ./Core/Src/stm32u5xx_hal_msp.d ./Core/Src/stm32u5xx_hal_msp.o ./Core/Src/stm32u5xx_hal_msp.su ./Core/Src/stm32u5xx_it.cyclo ./Core/Src/stm32u5xx_it.d ./Core/Src/stm32u5xx_it.o ./Core/Src/stm32u5xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32u5xx.cyclo ./Core/Src/system_stm32u5xx.d ./Core/Src/system_stm32u5xx.o ./Core/Src/system_stm32u5xx.su ./Core/Src/tree.cyclo ./Core/Src/tree.d ./Core/Src/tree.o ./Core/Src/tree.su ./Core/Src/tree_and_grass.cyclo ./Core/Src/tree_and_grass.d ./Core/Src/tree_and_grass.o ./Core/Src/tree_and_grass.su

.PHONY: clean-Core-2f-Src

