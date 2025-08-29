################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_buf_pxp.c \
../Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp.c \
../Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_fill.c \
../Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_img.c \
../Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_layer.c \
../Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_cfg.c \
../Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_osa.c \
../Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_utils.c 

OBJS += \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_buf_pxp.o \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp.o \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_fill.o \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_img.o \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_layer.o \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_cfg.o \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_osa.o \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_utils.o 

C_DEPS += \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_buf_pxp.d \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp.d \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_fill.d \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_img.d \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_layer.d \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_cfg.d \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_osa.d \
./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/lvgl/src/draw/nxp/pxp/%.o Middlewares/lvgl/src/draw/nxp/pxp/%.su Middlewares/lvgl/src/draw/nxp/pxp/%.cyclo: ../Middlewares/lvgl/src/draw/nxp/pxp/%.c Middlewares/lvgl/src/draw/nxp/pxp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares" -I"/Users/joakimwennergren/STM32CubeIDE/workspace_1.19.0/Smartwatch_bench/Middlewares/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp

clean-Middlewares-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp:
	-$(RM) ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_buf_pxp.cyclo ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_buf_pxp.d ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_buf_pxp.o ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_buf_pxp.su ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp.cyclo ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp.d ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp.o ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp.su ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_fill.cyclo ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_fill.d ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_fill.o ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_fill.su ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_img.cyclo ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_img.d ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_img.o ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_img.su ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_layer.cyclo ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_layer.d ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_layer.o ./Middlewares/lvgl/src/draw/nxp/pxp/lv_draw_pxp_layer.su ./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_cfg.cyclo ./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_cfg.d ./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_cfg.o ./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_cfg.su ./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_osa.cyclo ./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_osa.d ./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_osa.o ./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_osa.su ./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_utils.cyclo ./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_utils.d ./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_utils.o ./Middlewares/lvgl/src/draw/nxp/pxp/lv_pxp_utils.su

.PHONY: clean-Middlewares-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp

