################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/libs/expat/xmlparse.c \
../Middlewares/lvgl/src/libs/expat/xmlrole.c \
../Middlewares/lvgl/src/libs/expat/xmltok.c \
../Middlewares/lvgl/src/libs/expat/xmltok_impl.c \
../Middlewares/lvgl/src/libs/expat/xmltok_ns.c 

OBJS += \
./Middlewares/lvgl/src/libs/expat/xmlparse.o \
./Middlewares/lvgl/src/libs/expat/xmlrole.o \
./Middlewares/lvgl/src/libs/expat/xmltok.o \
./Middlewares/lvgl/src/libs/expat/xmltok_impl.o \
./Middlewares/lvgl/src/libs/expat/xmltok_ns.o 

C_DEPS += \
./Middlewares/lvgl/src/libs/expat/xmlparse.d \
./Middlewares/lvgl/src/libs/expat/xmlrole.d \
./Middlewares/lvgl/src/libs/expat/xmltok.d \
./Middlewares/lvgl/src/libs/expat/xmltok_impl.d \
./Middlewares/lvgl/src/libs/expat/xmltok_ns.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/libs/expat/%.o Middlewares/lvgl/src/libs/expat/%.su Middlewares/lvgl/src/libs/expat/%.cyclo: ../Middlewares/lvgl/src/libs/expat/%.c Middlewares/lvgl/src/libs/expat/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-libs-2f-expat

clean-Middlewares-2f-lvgl-2f-src-2f-libs-2f-expat:
	-$(RM) ./Middlewares/lvgl/src/libs/expat/xmlparse.cyclo ./Middlewares/lvgl/src/libs/expat/xmlparse.d ./Middlewares/lvgl/src/libs/expat/xmlparse.o ./Middlewares/lvgl/src/libs/expat/xmlparse.su ./Middlewares/lvgl/src/libs/expat/xmlrole.cyclo ./Middlewares/lvgl/src/libs/expat/xmlrole.d ./Middlewares/lvgl/src/libs/expat/xmlrole.o ./Middlewares/lvgl/src/libs/expat/xmlrole.su ./Middlewares/lvgl/src/libs/expat/xmltok.cyclo ./Middlewares/lvgl/src/libs/expat/xmltok.d ./Middlewares/lvgl/src/libs/expat/xmltok.o ./Middlewares/lvgl/src/libs/expat/xmltok.su ./Middlewares/lvgl/src/libs/expat/xmltok_impl.cyclo ./Middlewares/lvgl/src/libs/expat/xmltok_impl.d ./Middlewares/lvgl/src/libs/expat/xmltok_impl.o ./Middlewares/lvgl/src/libs/expat/xmltok_impl.su ./Middlewares/lvgl/src/libs/expat/xmltok_ns.cyclo ./Middlewares/lvgl/src/libs/expat/xmltok_ns.d ./Middlewares/lvgl/src/libs/expat/xmltok_ns.o ./Middlewares/lvgl/src/libs/expat/xmltok_ns.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-libs-2f-expat

