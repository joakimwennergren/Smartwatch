################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/demos/music/lv_demo_music.c \
../Middlewares/lvgl/demos/music/lv_demo_music_list.c \
../Middlewares/lvgl/demos/music/lv_demo_music_main.c 

OBJS += \
./Middlewares/lvgl/demos/music/lv_demo_music.o \
./Middlewares/lvgl/demos/music/lv_demo_music_list.o \
./Middlewares/lvgl/demos/music/lv_demo_music_main.o 

C_DEPS += \
./Middlewares/lvgl/demos/music/lv_demo_music.d \
./Middlewares/lvgl/demos/music/lv_demo_music_list.d \
./Middlewares/lvgl/demos/music/lv_demo_music_main.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/demos/music/%.o Middlewares/lvgl/demos/music/%.su Middlewares/lvgl/demos/music/%.cyclo: ../Middlewares/lvgl/demos/music/%.c Middlewares/lvgl/demos/music/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-demos-2f-music

clean-Middlewares-2f-lvgl-2f-demos-2f-music:
	-$(RM) ./Middlewares/lvgl/demos/music/lv_demo_music.cyclo ./Middlewares/lvgl/demos/music/lv_demo_music.d ./Middlewares/lvgl/demos/music/lv_demo_music.o ./Middlewares/lvgl/demos/music/lv_demo_music.su ./Middlewares/lvgl/demos/music/lv_demo_music_list.cyclo ./Middlewares/lvgl/demos/music/lv_demo_music_list.d ./Middlewares/lvgl/demos/music/lv_demo_music_list.o ./Middlewares/lvgl/demos/music/lv_demo_music_list.su ./Middlewares/lvgl/demos/music/lv_demo_music_main.cyclo ./Middlewares/lvgl/demos/music/lv_demo_music_main.d ./Middlewares/lvgl/demos/music/lv_demo_music_main.o ./Middlewares/lvgl/demos/music/lv_demo_music_main.su

.PHONY: clean-Middlewares-2f-lvgl-2f-demos-2f-music

