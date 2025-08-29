################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/demos/widgets/assets/img_clothes.c \
../Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_avatar.c \
../Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_needle.c \
../Middlewares/lvgl/demos/widgets/assets/img_lvgl_logo.c 

OBJS += \
./Middlewares/lvgl/demos/widgets/assets/img_clothes.o \
./Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_avatar.o \
./Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_needle.o \
./Middlewares/lvgl/demos/widgets/assets/img_lvgl_logo.o 

C_DEPS += \
./Middlewares/lvgl/demos/widgets/assets/img_clothes.d \
./Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_avatar.d \
./Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_needle.d \
./Middlewares/lvgl/demos/widgets/assets/img_lvgl_logo.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/demos/widgets/assets/%.o Middlewares/lvgl/demos/widgets/assets/%.su Middlewares/lvgl/demos/widgets/assets/%.cyclo: ../Middlewares/lvgl/demos/widgets/assets/%.c Middlewares/lvgl/demos/widgets/assets/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-demos-2f-widgets-2f-assets

clean-Middlewares-2f-lvgl-2f-demos-2f-widgets-2f-assets:
	-$(RM) ./Middlewares/lvgl/demos/widgets/assets/img_clothes.cyclo ./Middlewares/lvgl/demos/widgets/assets/img_clothes.d ./Middlewares/lvgl/demos/widgets/assets/img_clothes.o ./Middlewares/lvgl/demos/widgets/assets/img_clothes.su ./Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_avatar.cyclo ./Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_avatar.d ./Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_avatar.o ./Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_avatar.su ./Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_needle.cyclo ./Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_needle.d ./Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_needle.o ./Middlewares/lvgl/demos/widgets/assets/img_demo_widgets_needle.su ./Middlewares/lvgl/demos/widgets/assets/img_lvgl_logo.cyclo ./Middlewares/lvgl/demos/widgets/assets/img_lvgl_logo.d ./Middlewares/lvgl/demos/widgets/assets/img_lvgl_logo.o ./Middlewares/lvgl/demos/widgets/assets/img_lvgl_logo.su

.PHONY: clean-Middlewares-2f-lvgl-2f-demos-2f-widgets-2f-assets

