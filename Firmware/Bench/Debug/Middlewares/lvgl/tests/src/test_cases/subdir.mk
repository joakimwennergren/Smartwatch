################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/tests/src/test_cases/_test_template.c \
../Middlewares/lvgl/tests/src/test_cases/test_align_flex.c \
../Middlewares/lvgl/tests/src/test_cases/test_anim.c \
../Middlewares/lvgl/tests/src/test_cases/test_anim_timeline.c \
../Middlewares/lvgl/tests/src/test_cases/test_area.c \
../Middlewares/lvgl/tests/src/test_cases/test_array.c \
../Middlewares/lvgl/tests/src/test_cases/test_bindings.c \
../Middlewares/lvgl/tests/src/test_cases/test_circle_buf.c \
../Middlewares/lvgl/tests/src/test_cases/test_click.c \
../Middlewares/lvgl/tests/src/test_cases/test_config.c \
../Middlewares/lvgl/tests/src/test_cases/test_demo_stress.c \
../Middlewares/lvgl/tests/src/test_cases/test_demo_widgets.c \
../Middlewares/lvgl/tests/src/test_cases/test_display.c \
../Middlewares/lvgl/tests/src/test_cases/test_draw_buf_stride.c \
../Middlewares/lvgl/tests/src/test_cases/test_event.c \
../Middlewares/lvgl/tests/src/test_cases/test_file_explorer.c \
../Middlewares/lvgl/tests/src/test_cases/test_font_loader.c \
../Middlewares/lvgl/tests/src/test_cases/test_font_manager.c \
../Middlewares/lvgl/tests/src/test_cases/test_fs.c \
../Middlewares/lvgl/tests/src/test_cases/test_gesture_pinch.c \
../Middlewares/lvgl/tests/src/test_cases/test_grid.c \
../Middlewares/lvgl/tests/src/test_cases/test_grid_fr.c \
../Middlewares/lvgl/tests/src/test_cases/test_gridnav.c \
../Middlewares/lvgl/tests/src/test_cases/test_group.c \
../Middlewares/lvgl/tests/src/test_cases/test_hover.c \
../Middlewares/lvgl/tests/src/test_cases/test_indev_reset.c \
../Middlewares/lvgl/tests/src/test_cases/test_indev_wait_release.c \
../Middlewares/lvgl/tests/src/test_cases/test_margin_align.c \
../Middlewares/lvgl/tests/src/test_cases/test_margin_flex.c \
../Middlewares/lvgl/tests/src/test_cases/test_margin_grid.c \
../Middlewares/lvgl/tests/src/test_cases/test_math.c \
../Middlewares/lvgl/tests/src/test_cases/test_mem.c \
../Middlewares/lvgl/tests/src/test_cases/test_observer.c \
../Middlewares/lvgl/tests/src/test_cases/test_profiler.c \
../Middlewares/lvgl/tests/src/test_cases/test_recolor.c \
../Middlewares/lvgl/tests/src/test_cases/test_screen_load.c \
../Middlewares/lvgl/tests/src/test_cases/test_snapshot.c \
../Middlewares/lvgl/tests/src/test_cases/test_style.c \
../Middlewares/lvgl/tests/src/test_cases/test_svg.c \
../Middlewares/lvgl/tests/src/test_cases/test_svg_anim.c \
../Middlewares/lvgl/tests/src/test_cases/test_tree.c \
../Middlewares/lvgl/tests/src/test_cases/test_txt.c 

OBJS += \
./Middlewares/lvgl/tests/src/test_cases/_test_template.o \
./Middlewares/lvgl/tests/src/test_cases/test_align_flex.o \
./Middlewares/lvgl/tests/src/test_cases/test_anim.o \
./Middlewares/lvgl/tests/src/test_cases/test_anim_timeline.o \
./Middlewares/lvgl/tests/src/test_cases/test_area.o \
./Middlewares/lvgl/tests/src/test_cases/test_array.o \
./Middlewares/lvgl/tests/src/test_cases/test_bindings.o \
./Middlewares/lvgl/tests/src/test_cases/test_circle_buf.o \
./Middlewares/lvgl/tests/src/test_cases/test_click.o \
./Middlewares/lvgl/tests/src/test_cases/test_config.o \
./Middlewares/lvgl/tests/src/test_cases/test_demo_stress.o \
./Middlewares/lvgl/tests/src/test_cases/test_demo_widgets.o \
./Middlewares/lvgl/tests/src/test_cases/test_display.o \
./Middlewares/lvgl/tests/src/test_cases/test_draw_buf_stride.o \
./Middlewares/lvgl/tests/src/test_cases/test_event.o \
./Middlewares/lvgl/tests/src/test_cases/test_file_explorer.o \
./Middlewares/lvgl/tests/src/test_cases/test_font_loader.o \
./Middlewares/lvgl/tests/src/test_cases/test_font_manager.o \
./Middlewares/lvgl/tests/src/test_cases/test_fs.o \
./Middlewares/lvgl/tests/src/test_cases/test_gesture_pinch.o \
./Middlewares/lvgl/tests/src/test_cases/test_grid.o \
./Middlewares/lvgl/tests/src/test_cases/test_grid_fr.o \
./Middlewares/lvgl/tests/src/test_cases/test_gridnav.o \
./Middlewares/lvgl/tests/src/test_cases/test_group.o \
./Middlewares/lvgl/tests/src/test_cases/test_hover.o \
./Middlewares/lvgl/tests/src/test_cases/test_indev_reset.o \
./Middlewares/lvgl/tests/src/test_cases/test_indev_wait_release.o \
./Middlewares/lvgl/tests/src/test_cases/test_margin_align.o \
./Middlewares/lvgl/tests/src/test_cases/test_margin_flex.o \
./Middlewares/lvgl/tests/src/test_cases/test_margin_grid.o \
./Middlewares/lvgl/tests/src/test_cases/test_math.o \
./Middlewares/lvgl/tests/src/test_cases/test_mem.o \
./Middlewares/lvgl/tests/src/test_cases/test_observer.o \
./Middlewares/lvgl/tests/src/test_cases/test_profiler.o \
./Middlewares/lvgl/tests/src/test_cases/test_recolor.o \
./Middlewares/lvgl/tests/src/test_cases/test_screen_load.o \
./Middlewares/lvgl/tests/src/test_cases/test_snapshot.o \
./Middlewares/lvgl/tests/src/test_cases/test_style.o \
./Middlewares/lvgl/tests/src/test_cases/test_svg.o \
./Middlewares/lvgl/tests/src/test_cases/test_svg_anim.o \
./Middlewares/lvgl/tests/src/test_cases/test_tree.o \
./Middlewares/lvgl/tests/src/test_cases/test_txt.o 

C_DEPS += \
./Middlewares/lvgl/tests/src/test_cases/_test_template.d \
./Middlewares/lvgl/tests/src/test_cases/test_align_flex.d \
./Middlewares/lvgl/tests/src/test_cases/test_anim.d \
./Middlewares/lvgl/tests/src/test_cases/test_anim_timeline.d \
./Middlewares/lvgl/tests/src/test_cases/test_area.d \
./Middlewares/lvgl/tests/src/test_cases/test_array.d \
./Middlewares/lvgl/tests/src/test_cases/test_bindings.d \
./Middlewares/lvgl/tests/src/test_cases/test_circle_buf.d \
./Middlewares/lvgl/tests/src/test_cases/test_click.d \
./Middlewares/lvgl/tests/src/test_cases/test_config.d \
./Middlewares/lvgl/tests/src/test_cases/test_demo_stress.d \
./Middlewares/lvgl/tests/src/test_cases/test_demo_widgets.d \
./Middlewares/lvgl/tests/src/test_cases/test_display.d \
./Middlewares/lvgl/tests/src/test_cases/test_draw_buf_stride.d \
./Middlewares/lvgl/tests/src/test_cases/test_event.d \
./Middlewares/lvgl/tests/src/test_cases/test_file_explorer.d \
./Middlewares/lvgl/tests/src/test_cases/test_font_loader.d \
./Middlewares/lvgl/tests/src/test_cases/test_font_manager.d \
./Middlewares/lvgl/tests/src/test_cases/test_fs.d \
./Middlewares/lvgl/tests/src/test_cases/test_gesture_pinch.d \
./Middlewares/lvgl/tests/src/test_cases/test_grid.d \
./Middlewares/lvgl/tests/src/test_cases/test_grid_fr.d \
./Middlewares/lvgl/tests/src/test_cases/test_gridnav.d \
./Middlewares/lvgl/tests/src/test_cases/test_group.d \
./Middlewares/lvgl/tests/src/test_cases/test_hover.d \
./Middlewares/lvgl/tests/src/test_cases/test_indev_reset.d \
./Middlewares/lvgl/tests/src/test_cases/test_indev_wait_release.d \
./Middlewares/lvgl/tests/src/test_cases/test_margin_align.d \
./Middlewares/lvgl/tests/src/test_cases/test_margin_flex.d \
./Middlewares/lvgl/tests/src/test_cases/test_margin_grid.d \
./Middlewares/lvgl/tests/src/test_cases/test_math.d \
./Middlewares/lvgl/tests/src/test_cases/test_mem.d \
./Middlewares/lvgl/tests/src/test_cases/test_observer.d \
./Middlewares/lvgl/tests/src/test_cases/test_profiler.d \
./Middlewares/lvgl/tests/src/test_cases/test_recolor.d \
./Middlewares/lvgl/tests/src/test_cases/test_screen_load.d \
./Middlewares/lvgl/tests/src/test_cases/test_snapshot.d \
./Middlewares/lvgl/tests/src/test_cases/test_style.d \
./Middlewares/lvgl/tests/src/test_cases/test_svg.d \
./Middlewares/lvgl/tests/src/test_cases/test_svg_anim.d \
./Middlewares/lvgl/tests/src/test_cases/test_tree.d \
./Middlewares/lvgl/tests/src/test_cases/test_txt.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/tests/src/test_cases/%.o Middlewares/lvgl/tests/src/test_cases/%.su Middlewares/lvgl/tests/src/test_cases/%.cyclo: ../Middlewares/lvgl/tests/src/test_cases/%.c Middlewares/lvgl/tests/src/test_cases/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-tests-2f-src-2f-test_cases

clean-Middlewares-2f-lvgl-2f-tests-2f-src-2f-test_cases:
	-$(RM) ./Middlewares/lvgl/tests/src/test_cases/_test_template.cyclo ./Middlewares/lvgl/tests/src/test_cases/_test_template.d ./Middlewares/lvgl/tests/src/test_cases/_test_template.o ./Middlewares/lvgl/tests/src/test_cases/_test_template.su ./Middlewares/lvgl/tests/src/test_cases/test_align_flex.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_align_flex.d ./Middlewares/lvgl/tests/src/test_cases/test_align_flex.o ./Middlewares/lvgl/tests/src/test_cases/test_align_flex.su ./Middlewares/lvgl/tests/src/test_cases/test_anim.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_anim.d ./Middlewares/lvgl/tests/src/test_cases/test_anim.o ./Middlewares/lvgl/tests/src/test_cases/test_anim.su ./Middlewares/lvgl/tests/src/test_cases/test_anim_timeline.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_anim_timeline.d ./Middlewares/lvgl/tests/src/test_cases/test_anim_timeline.o ./Middlewares/lvgl/tests/src/test_cases/test_anim_timeline.su ./Middlewares/lvgl/tests/src/test_cases/test_area.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_area.d ./Middlewares/lvgl/tests/src/test_cases/test_area.o ./Middlewares/lvgl/tests/src/test_cases/test_area.su ./Middlewares/lvgl/tests/src/test_cases/test_array.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_array.d ./Middlewares/lvgl/tests/src/test_cases/test_array.o ./Middlewares/lvgl/tests/src/test_cases/test_array.su ./Middlewares/lvgl/tests/src/test_cases/test_bindings.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_bindings.d ./Middlewares/lvgl/tests/src/test_cases/test_bindings.o ./Middlewares/lvgl/tests/src/test_cases/test_bindings.su ./Middlewares/lvgl/tests/src/test_cases/test_circle_buf.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_circle_buf.d ./Middlewares/lvgl/tests/src/test_cases/test_circle_buf.o ./Middlewares/lvgl/tests/src/test_cases/test_circle_buf.su ./Middlewares/lvgl/tests/src/test_cases/test_click.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_click.d ./Middlewares/lvgl/tests/src/test_cases/test_click.o ./Middlewares/lvgl/tests/src/test_cases/test_click.su ./Middlewares/lvgl/tests/src/test_cases/test_config.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_config.d ./Middlewares/lvgl/tests/src/test_cases/test_config.o ./Middlewares/lvgl/tests/src/test_cases/test_config.su ./Middlewares/lvgl/tests/src/test_cases/test_demo_stress.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_demo_stress.d ./Middlewares/lvgl/tests/src/test_cases/test_demo_stress.o ./Middlewares/lvgl/tests/src/test_cases/test_demo_stress.su ./Middlewares/lvgl/tests/src/test_cases/test_demo_widgets.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_demo_widgets.d ./Middlewares/lvgl/tests/src/test_cases/test_demo_widgets.o ./Middlewares/lvgl/tests/src/test_cases/test_demo_widgets.su ./Middlewares/lvgl/tests/src/test_cases/test_display.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_display.d ./Middlewares/lvgl/tests/src/test_cases/test_display.o ./Middlewares/lvgl/tests/src/test_cases/test_display.su ./Middlewares/lvgl/tests/src/test_cases/test_draw_buf_stride.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_draw_buf_stride.d ./Middlewares/lvgl/tests/src/test_cases/test_draw_buf_stride.o ./Middlewares/lvgl/tests/src/test_cases/test_draw_buf_stride.su ./Middlewares/lvgl/tests/src/test_cases/test_event.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_event.d ./Middlewares/lvgl/tests/src/test_cases/test_event.o ./Middlewares/lvgl/tests/src/test_cases/test_event.su ./Middlewares/lvgl/tests/src/test_cases/test_file_explorer.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_file_explorer.d ./Middlewares/lvgl/tests/src/test_cases/test_file_explorer.o ./Middlewares/lvgl/tests/src/test_cases/test_file_explorer.su ./Middlewares/lvgl/tests/src/test_cases/test_font_loader.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_font_loader.d ./Middlewares/lvgl/tests/src/test_cases/test_font_loader.o ./Middlewares/lvgl/tests/src/test_cases/test_font_loader.su ./Middlewares/lvgl/tests/src/test_cases/test_font_manager.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_font_manager.d ./Middlewares/lvgl/tests/src/test_cases/test_font_manager.o ./Middlewares/lvgl/tests/src/test_cases/test_font_manager.su ./Middlewares/lvgl/tests/src/test_cases/test_fs.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_fs.d ./Middlewares/lvgl/tests/src/test_cases/test_fs.o ./Middlewares/lvgl/tests/src/test_cases/test_fs.su ./Middlewares/lvgl/tests/src/test_cases/test_gesture_pinch.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_gesture_pinch.d ./Middlewares/lvgl/tests/src/test_cases/test_gesture_pinch.o ./Middlewares/lvgl/tests/src/test_cases/test_gesture_pinch.su ./Middlewares/lvgl/tests/src/test_cases/test_grid.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_grid.d ./Middlewares/lvgl/tests/src/test_cases/test_grid.o ./Middlewares/lvgl/tests/src/test_cases/test_grid.su ./Middlewares/lvgl/tests/src/test_cases/test_grid_fr.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_grid_fr.d ./Middlewares/lvgl/tests/src/test_cases/test_grid_fr.o ./Middlewares/lvgl/tests/src/test_cases/test_grid_fr.su ./Middlewares/lvgl/tests/src/test_cases/test_gridnav.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_gridnav.d ./Middlewares/lvgl/tests/src/test_cases/test_gridnav.o ./Middlewares/lvgl/tests/src/test_cases/test_gridnav.su ./Middlewares/lvgl/tests/src/test_cases/test_group.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_group.d ./Middlewares/lvgl/tests/src/test_cases/test_group.o ./Middlewares/lvgl/tests/src/test_cases/test_group.su ./Middlewares/lvgl/tests/src/test_cases/test_hover.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_hover.d ./Middlewares/lvgl/tests/src/test_cases/test_hover.o ./Middlewares/lvgl/tests/src/test_cases/test_hover.su ./Middlewares/lvgl/tests/src/test_cases/test_indev_reset.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_indev_reset.d ./Middlewares/lvgl/tests/src/test_cases/test_indev_reset.o ./Middlewares/lvgl/tests/src/test_cases/test_indev_reset.su
	-$(RM) ./Middlewares/lvgl/tests/src/test_cases/test_indev_wait_release.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_indev_wait_release.d ./Middlewares/lvgl/tests/src/test_cases/test_indev_wait_release.o ./Middlewares/lvgl/tests/src/test_cases/test_indev_wait_release.su ./Middlewares/lvgl/tests/src/test_cases/test_margin_align.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_margin_align.d ./Middlewares/lvgl/tests/src/test_cases/test_margin_align.o ./Middlewares/lvgl/tests/src/test_cases/test_margin_align.su ./Middlewares/lvgl/tests/src/test_cases/test_margin_flex.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_margin_flex.d ./Middlewares/lvgl/tests/src/test_cases/test_margin_flex.o ./Middlewares/lvgl/tests/src/test_cases/test_margin_flex.su ./Middlewares/lvgl/tests/src/test_cases/test_margin_grid.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_margin_grid.d ./Middlewares/lvgl/tests/src/test_cases/test_margin_grid.o ./Middlewares/lvgl/tests/src/test_cases/test_margin_grid.su ./Middlewares/lvgl/tests/src/test_cases/test_math.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_math.d ./Middlewares/lvgl/tests/src/test_cases/test_math.o ./Middlewares/lvgl/tests/src/test_cases/test_math.su ./Middlewares/lvgl/tests/src/test_cases/test_mem.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_mem.d ./Middlewares/lvgl/tests/src/test_cases/test_mem.o ./Middlewares/lvgl/tests/src/test_cases/test_mem.su ./Middlewares/lvgl/tests/src/test_cases/test_observer.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_observer.d ./Middlewares/lvgl/tests/src/test_cases/test_observer.o ./Middlewares/lvgl/tests/src/test_cases/test_observer.su ./Middlewares/lvgl/tests/src/test_cases/test_profiler.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_profiler.d ./Middlewares/lvgl/tests/src/test_cases/test_profiler.o ./Middlewares/lvgl/tests/src/test_cases/test_profiler.su ./Middlewares/lvgl/tests/src/test_cases/test_recolor.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_recolor.d ./Middlewares/lvgl/tests/src/test_cases/test_recolor.o ./Middlewares/lvgl/tests/src/test_cases/test_recolor.su ./Middlewares/lvgl/tests/src/test_cases/test_screen_load.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_screen_load.d ./Middlewares/lvgl/tests/src/test_cases/test_screen_load.o ./Middlewares/lvgl/tests/src/test_cases/test_screen_load.su ./Middlewares/lvgl/tests/src/test_cases/test_snapshot.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_snapshot.d ./Middlewares/lvgl/tests/src/test_cases/test_snapshot.o ./Middlewares/lvgl/tests/src/test_cases/test_snapshot.su ./Middlewares/lvgl/tests/src/test_cases/test_style.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_style.d ./Middlewares/lvgl/tests/src/test_cases/test_style.o ./Middlewares/lvgl/tests/src/test_cases/test_style.su ./Middlewares/lvgl/tests/src/test_cases/test_svg.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_svg.d ./Middlewares/lvgl/tests/src/test_cases/test_svg.o ./Middlewares/lvgl/tests/src/test_cases/test_svg.su ./Middlewares/lvgl/tests/src/test_cases/test_svg_anim.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_svg_anim.d ./Middlewares/lvgl/tests/src/test_cases/test_svg_anim.o ./Middlewares/lvgl/tests/src/test_cases/test_svg_anim.su ./Middlewares/lvgl/tests/src/test_cases/test_tree.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_tree.d ./Middlewares/lvgl/tests/src/test_cases/test_tree.o ./Middlewares/lvgl/tests/src/test_cases/test_tree.su ./Middlewares/lvgl/tests/src/test_cases/test_txt.cyclo ./Middlewares/lvgl/tests/src/test_cases/test_txt.d ./Middlewares/lvgl/tests/src/test_cases/test_txt.o ./Middlewares/lvgl/tests/src/test_cases/test_txt.su

.PHONY: clean-Middlewares-2f-lvgl-2f-tests-2f-src-2f-test_cases

