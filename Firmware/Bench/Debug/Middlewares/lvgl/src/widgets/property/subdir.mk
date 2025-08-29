################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/widgets/property/lv_animimage_properties.c \
../Middlewares/lvgl/src/widgets/property/lv_dropdown_properties.c \
../Middlewares/lvgl/src/widgets/property/lv_image_properties.c \
../Middlewares/lvgl/src/widgets/property/lv_keyboard_properties.c \
../Middlewares/lvgl/src/widgets/property/lv_label_properties.c \
../Middlewares/lvgl/src/widgets/property/lv_obj_properties.c \
../Middlewares/lvgl/src/widgets/property/lv_roller_properties.c \
../Middlewares/lvgl/src/widgets/property/lv_slider_properties.c \
../Middlewares/lvgl/src/widgets/property/lv_style_properties.c \
../Middlewares/lvgl/src/widgets/property/lv_textarea_properties.c 

OBJS += \
./Middlewares/lvgl/src/widgets/property/lv_animimage_properties.o \
./Middlewares/lvgl/src/widgets/property/lv_dropdown_properties.o \
./Middlewares/lvgl/src/widgets/property/lv_image_properties.o \
./Middlewares/lvgl/src/widgets/property/lv_keyboard_properties.o \
./Middlewares/lvgl/src/widgets/property/lv_label_properties.o \
./Middlewares/lvgl/src/widgets/property/lv_obj_properties.o \
./Middlewares/lvgl/src/widgets/property/lv_roller_properties.o \
./Middlewares/lvgl/src/widgets/property/lv_slider_properties.o \
./Middlewares/lvgl/src/widgets/property/lv_style_properties.o \
./Middlewares/lvgl/src/widgets/property/lv_textarea_properties.o 

C_DEPS += \
./Middlewares/lvgl/src/widgets/property/lv_animimage_properties.d \
./Middlewares/lvgl/src/widgets/property/lv_dropdown_properties.d \
./Middlewares/lvgl/src/widgets/property/lv_image_properties.d \
./Middlewares/lvgl/src/widgets/property/lv_keyboard_properties.d \
./Middlewares/lvgl/src/widgets/property/lv_label_properties.d \
./Middlewares/lvgl/src/widgets/property/lv_obj_properties.d \
./Middlewares/lvgl/src/widgets/property/lv_roller_properties.d \
./Middlewares/lvgl/src/widgets/property/lv_slider_properties.d \
./Middlewares/lvgl/src/widgets/property/lv_style_properties.d \
./Middlewares/lvgl/src/widgets/property/lv_textarea_properties.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/widgets/property/%.o Middlewares/lvgl/src/widgets/property/%.su Middlewares/lvgl/src/widgets/property/%.cyclo: ../Middlewares/lvgl/src/widgets/property/%.c Middlewares/lvgl/src/widgets/property/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-widgets-2f-property

clean-Middlewares-2f-lvgl-2f-src-2f-widgets-2f-property:
	-$(RM) ./Middlewares/lvgl/src/widgets/property/lv_animimage_properties.cyclo ./Middlewares/lvgl/src/widgets/property/lv_animimage_properties.d ./Middlewares/lvgl/src/widgets/property/lv_animimage_properties.o ./Middlewares/lvgl/src/widgets/property/lv_animimage_properties.su ./Middlewares/lvgl/src/widgets/property/lv_dropdown_properties.cyclo ./Middlewares/lvgl/src/widgets/property/lv_dropdown_properties.d ./Middlewares/lvgl/src/widgets/property/lv_dropdown_properties.o ./Middlewares/lvgl/src/widgets/property/lv_dropdown_properties.su ./Middlewares/lvgl/src/widgets/property/lv_image_properties.cyclo ./Middlewares/lvgl/src/widgets/property/lv_image_properties.d ./Middlewares/lvgl/src/widgets/property/lv_image_properties.o ./Middlewares/lvgl/src/widgets/property/lv_image_properties.su ./Middlewares/lvgl/src/widgets/property/lv_keyboard_properties.cyclo ./Middlewares/lvgl/src/widgets/property/lv_keyboard_properties.d ./Middlewares/lvgl/src/widgets/property/lv_keyboard_properties.o ./Middlewares/lvgl/src/widgets/property/lv_keyboard_properties.su ./Middlewares/lvgl/src/widgets/property/lv_label_properties.cyclo ./Middlewares/lvgl/src/widgets/property/lv_label_properties.d ./Middlewares/lvgl/src/widgets/property/lv_label_properties.o ./Middlewares/lvgl/src/widgets/property/lv_label_properties.su ./Middlewares/lvgl/src/widgets/property/lv_obj_properties.cyclo ./Middlewares/lvgl/src/widgets/property/lv_obj_properties.d ./Middlewares/lvgl/src/widgets/property/lv_obj_properties.o ./Middlewares/lvgl/src/widgets/property/lv_obj_properties.su ./Middlewares/lvgl/src/widgets/property/lv_roller_properties.cyclo ./Middlewares/lvgl/src/widgets/property/lv_roller_properties.d ./Middlewares/lvgl/src/widgets/property/lv_roller_properties.o ./Middlewares/lvgl/src/widgets/property/lv_roller_properties.su ./Middlewares/lvgl/src/widgets/property/lv_slider_properties.cyclo ./Middlewares/lvgl/src/widgets/property/lv_slider_properties.d ./Middlewares/lvgl/src/widgets/property/lv_slider_properties.o ./Middlewares/lvgl/src/widgets/property/lv_slider_properties.su ./Middlewares/lvgl/src/widgets/property/lv_style_properties.cyclo ./Middlewares/lvgl/src/widgets/property/lv_style_properties.d ./Middlewares/lvgl/src/widgets/property/lv_style_properties.o ./Middlewares/lvgl/src/widgets/property/lv_style_properties.su ./Middlewares/lvgl/src/widgets/property/lv_textarea_properties.cyclo ./Middlewares/lvgl/src/widgets/property/lv_textarea_properties.d ./Middlewares/lvgl/src/widgets/property/lv_textarea_properties.o ./Middlewares/lvgl/src/widgets/property/lv_textarea_properties.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-widgets-2f-property

