################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/others/xml/lv_xml.c \
../Middlewares/lvgl/src/others/xml/lv_xml_base_types.c \
../Middlewares/lvgl/src/others/xml/lv_xml_component.c \
../Middlewares/lvgl/src/others/xml/lv_xml_parser.c \
../Middlewares/lvgl/src/others/xml/lv_xml_style.c \
../Middlewares/lvgl/src/others/xml/lv_xml_update.c \
../Middlewares/lvgl/src/others/xml/lv_xml_utils.c \
../Middlewares/lvgl/src/others/xml/lv_xml_widget.c 

OBJS += \
./Middlewares/lvgl/src/others/xml/lv_xml.o \
./Middlewares/lvgl/src/others/xml/lv_xml_base_types.o \
./Middlewares/lvgl/src/others/xml/lv_xml_component.o \
./Middlewares/lvgl/src/others/xml/lv_xml_parser.o \
./Middlewares/lvgl/src/others/xml/lv_xml_style.o \
./Middlewares/lvgl/src/others/xml/lv_xml_update.o \
./Middlewares/lvgl/src/others/xml/lv_xml_utils.o \
./Middlewares/lvgl/src/others/xml/lv_xml_widget.o 

C_DEPS += \
./Middlewares/lvgl/src/others/xml/lv_xml.d \
./Middlewares/lvgl/src/others/xml/lv_xml_base_types.d \
./Middlewares/lvgl/src/others/xml/lv_xml_component.d \
./Middlewares/lvgl/src/others/xml/lv_xml_parser.d \
./Middlewares/lvgl/src/others/xml/lv_xml_style.d \
./Middlewares/lvgl/src/others/xml/lv_xml_update.d \
./Middlewares/lvgl/src/others/xml/lv_xml_utils.d \
./Middlewares/lvgl/src/others/xml/lv_xml_widget.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/others/xml/%.o Middlewares/lvgl/src/others/xml/%.su Middlewares/lvgl/src/others/xml/%.cyclo: ../Middlewares/lvgl/src/others/xml/%.c Middlewares/lvgl/src/others/xml/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-others-2f-xml

clean-Middlewares-2f-lvgl-2f-src-2f-others-2f-xml:
	-$(RM) ./Middlewares/lvgl/src/others/xml/lv_xml.cyclo ./Middlewares/lvgl/src/others/xml/lv_xml.d ./Middlewares/lvgl/src/others/xml/lv_xml.o ./Middlewares/lvgl/src/others/xml/lv_xml.su ./Middlewares/lvgl/src/others/xml/lv_xml_base_types.cyclo ./Middlewares/lvgl/src/others/xml/lv_xml_base_types.d ./Middlewares/lvgl/src/others/xml/lv_xml_base_types.o ./Middlewares/lvgl/src/others/xml/lv_xml_base_types.su ./Middlewares/lvgl/src/others/xml/lv_xml_component.cyclo ./Middlewares/lvgl/src/others/xml/lv_xml_component.d ./Middlewares/lvgl/src/others/xml/lv_xml_component.o ./Middlewares/lvgl/src/others/xml/lv_xml_component.su ./Middlewares/lvgl/src/others/xml/lv_xml_parser.cyclo ./Middlewares/lvgl/src/others/xml/lv_xml_parser.d ./Middlewares/lvgl/src/others/xml/lv_xml_parser.o ./Middlewares/lvgl/src/others/xml/lv_xml_parser.su ./Middlewares/lvgl/src/others/xml/lv_xml_style.cyclo ./Middlewares/lvgl/src/others/xml/lv_xml_style.d ./Middlewares/lvgl/src/others/xml/lv_xml_style.o ./Middlewares/lvgl/src/others/xml/lv_xml_style.su ./Middlewares/lvgl/src/others/xml/lv_xml_update.cyclo ./Middlewares/lvgl/src/others/xml/lv_xml_update.d ./Middlewares/lvgl/src/others/xml/lv_xml_update.o ./Middlewares/lvgl/src/others/xml/lv_xml_update.su ./Middlewares/lvgl/src/others/xml/lv_xml_utils.cyclo ./Middlewares/lvgl/src/others/xml/lv_xml_utils.d ./Middlewares/lvgl/src/others/xml/lv_xml_utils.o ./Middlewares/lvgl/src/others/xml/lv_xml_utils.su ./Middlewares/lvgl/src/others/xml/lv_xml_widget.cyclo ./Middlewares/lvgl/src/others/xml/lv_xml_widget.d ./Middlewares/lvgl/src/others/xml/lv_xml_widget.o ./Middlewares/lvgl/src/others/xml/lv_xml_widget.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-others-2f-xml

