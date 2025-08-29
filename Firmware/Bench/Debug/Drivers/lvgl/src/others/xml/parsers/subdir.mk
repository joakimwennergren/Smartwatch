################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_arc_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_bar_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_button_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_buttonmatrix_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_calendar_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_canvas_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_chart_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_checkbox_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_dropdown_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_event_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_image_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_keyboard_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_label_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_obj_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_roller_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_scale_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_slider_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_spangroup_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_table_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_tabview_parser.c \
../Drivers/lvgl/src/others/xml/parsers/lv_xml_textarea_parser.c 

OBJS += \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_arc_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_bar_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_button_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_buttonmatrix_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_calendar_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_canvas_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_chart_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_checkbox_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_dropdown_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_event_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_image_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_keyboard_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_label_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_obj_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_roller_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_scale_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_slider_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_spangroup_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_table_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_tabview_parser.o \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_textarea_parser.o 

C_DEPS += \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_arc_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_bar_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_button_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_buttonmatrix_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_calendar_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_canvas_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_chart_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_checkbox_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_dropdown_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_event_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_image_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_keyboard_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_label_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_obj_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_roller_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_scale_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_slider_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_spangroup_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_table_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_tabview_parser.d \
./Drivers/lvgl/src/others/xml/parsers/lv_xml_textarea_parser.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/others/xml/parsers/%.o Drivers/lvgl/src/others/xml/parsers/%.su Drivers/lvgl/src/others/xml/parsers/%.cyclo: ../Drivers/lvgl/src/others/xml/parsers/%.c Drivers/lvgl/src/others/xml/parsers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Drivers/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-others-2f-xml-2f-parsers

clean-Drivers-2f-lvgl-2f-src-2f-others-2f-xml-2f-parsers:
	-$(RM) ./Drivers/lvgl/src/others/xml/parsers/lv_xml_arc_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_arc_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_arc_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_arc_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_bar_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_bar_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_bar_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_bar_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_button_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_button_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_button_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_button_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_buttonmatrix_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_buttonmatrix_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_buttonmatrix_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_buttonmatrix_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_calendar_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_calendar_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_calendar_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_calendar_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_canvas_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_canvas_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_canvas_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_canvas_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_chart_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_chart_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_chart_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_chart_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_checkbox_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_checkbox_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_checkbox_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_checkbox_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_dropdown_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_dropdown_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_dropdown_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_dropdown_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_event_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_event_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_event_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_event_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_image_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_image_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_image_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_image_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_keyboard_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_keyboard_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_keyboard_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_keyboard_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_label_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_label_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_label_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_label_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_obj_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_obj_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_obj_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_obj_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_roller_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_roller_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_roller_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_roller_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_scale_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_scale_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_scale_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_scale_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_slider_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_slider_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_slider_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_slider_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_spangroup_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_spangroup_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_spangroup_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_spangroup_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_table_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_table_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_table_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_table_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_tabview_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_tabview_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_tabview_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_tabview_parser.su ./Drivers/lvgl/src/others/xml/parsers/lv_xml_textarea_parser.cyclo ./Drivers/lvgl/src/others/xml/parsers/lv_xml_textarea_parser.d ./Drivers/lvgl/src/others/xml/parsers/lv_xml_textarea_parser.o ./Drivers/lvgl/src/others/xml/parsers/lv_xml_textarea_parser.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-others-2f-xml-2f-parsers

