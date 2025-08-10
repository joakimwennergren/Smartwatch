/**
 ****************************************************************************************
 *
 * @file user_pwm.c
 *
 * @brief Functions for handling the pwm command
 *
 * Copyright (C) 2019-2024 Renesas Electronics Corporation and/or its affiliates.
 * All rights reserved. Confidential Information.
 *
 * This software ("Software") is supplied by Renesas Electronics Corporation and/or its
 * affiliates ("Renesas"). Renesas grants you a personal, non-exclusive, non-transferable,
 * revocable, non-sub-licensable right and license to use the Software, solely if used in
 * or together with Renesas products. You may make copies of this Software, provided this
 * copyright notice and disclaimer ("Notice") is included in all such copies. Renesas
 * reserves the right to change or discontinue the Software at any time without notice.
 *
 * THE SOFTWARE IS PROVIDED "AS IS". RENESAS DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. TO THE
 * MAXIMUM EXTENT PERMITTED UNDER LAW, IN NO EVENT SHALL RENESAS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE, EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES. USE OF THIS SOFTWARE MAY BE SUBJECT TO TERMS AND CONDITIONS CONTAINED IN
 * AN ADDITIONAL AGREEMENT BETWEEN YOU AND RENESAS. IN CASE OF CONFLICT BETWEEN THE TERMS
 * OF THIS NOTICE AND ANY SUCH ADDITIONAL LICENSE AGREEMENT, THE TERMS OF THE AGREEMENT
 * SHALL TAKE PRECEDENCE. BY CONTINUING TO USE THIS SOFTWARE, YOU AGREE TO THE TERMS OF
 * THIS NOTICE.IF YOU DO NOT AGREE TO THESE TERMS, YOU ARE NOT PERMITTED TO USE THIS
 * SOFTWARE.
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */


#include "user_at_commands.h"
#include "user_pwm.h"
#include "user_codeless_env.h"
#include "user_utility_functions.h"
#include "arch_console.h"
#include "timer2.h"
#include "timer0_2.h"
#include "math.h"

#if defined(USE_AT_PWM)

static bool is_pwm_in_use = false;

bool is_pwm_hardware_configuration_valid(void)
{
    bool is_found = false;

    // Run through all IO pins in the pin configuration array to find the pwm pin
    uint8_t num_of_pins_in_conf_array=sizeof(codeless_env.port_configuration)/sizeof(codeless_env.port_configuration[0]);
    for (uint8_t j=0; j < num_of_pins_in_conf_array ; j++)
    {
        if (IO_FUNC_PWM2==codeless_env.port_configuration[j]) {
            is_found = true;
            break;
        }
    }
    return is_found;
}

void user_pwm_stop_handler(void)
{
     // Stop the timer
    timer2_stop();

    // Disable the Timer0/Timer2 input clock
    timer0_2_clk_disable();
    is_pwm_in_use = false;
}

int pwm(uint32_t pwm_frequency, uint8_t duty_cycle, uint16_t duration_in_ms)
{
    int return_value=0;
    do
    {
        if (is_pwm_in_use)
        {
            return_value=-1;
            break;
        }

        // Enable the Timer0/Timer2 input clock
        timer0_2_clk_enable();

        // Set the Timer0/Timer2 input clock division factor
        tim0_2_clk_div_config_t clk_div_config = { .clk_div = TIM0_2_CLK_DIV_8 };
        uint32_t divider=8;

        timer0_2_clk_div_set(&clk_div_config);

        // Configure hardware pause
        #if defined (__DA14531__)
        tim2_config_t config = {.clk_source = TIM2_CLK_SYS, .hw_pause = TIM2_HW_PAUSE_OFF};
        #else
        tim2_config_t config = {.hw_pause = TIM2_HW_PAUSE_OFF};
        #endif
        timer2_config(&config);

        // System clock, divided by 8, is the Timer2 input clock source (according
        // to the clk_div_config struct above).
        timer2_pwm_freq_set(pwm_frequency, 16000000 / divider);

        timer2_start();

        // Set PWM2 duty cycle
        tim2_pwm_config_t pwm_config;
        memset(&pwm_config, (int)0, sizeof(pwm_config));
        pwm_config.pwm_signal = TIM2_PWM_2;
        pwm_config.pwm_dc     = duty_cycle;
        timer2_pwm_signal_config(&pwm_config);

        // Release sw pause to let PWM2 run
        timer2_resume();
#if defined(__IS_SDK6_COMPILER_GCC__)
        uint32_t timer_delay_in_10ms_slots=(uint32_t)(duration_in_ms / 10);
#else
        uint32_t timer_delay_in_10ms_slots=(uint32_t)round((double)duration_in_ms / 10.0);
#endif

        timer_hnd stop_pwm_timer_hnd = app_easy_timer(timer_delay_in_10ms_slots, user_pwm_stop_handler);
        if (stop_pwm_timer_hnd == EASY_TIMER_INVALID_TIMER) //timer is invalid
        {
             // No chance to stop the pwm later.It should be stopped now.
             timer2_stop();

            // Disable the Timer0/Timer2 input clock
            timer0_2_clk_disable();
            return_value=-2;
            break;
        }
        is_pwm_in_use=true;
    }
    while (0);
    return return_value;
}

#endif // USE_AT_PWM

/// @} APP
