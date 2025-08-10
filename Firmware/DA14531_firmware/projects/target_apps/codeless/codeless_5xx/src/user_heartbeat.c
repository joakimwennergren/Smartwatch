/**
 ****************************************************************************************
 *
 * @file user_heartbeat.c
 *
 * @brief Functions for handling the heartbeat command
 *
 * Copyright (C) 2020-2024 Renesas Electronics Corporation and/or its affiliates.
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


#include "user_heartbeat.h"
#include "user_codeless_env.h"
#include "user_at_commands.h"

#if defined (USE_AT_HRTBT)

#define HRTBT_PIN_TOGGLING_INTERVAL (uint32_t)100  // Toggling every 100*10 ms = 1 sec

struct heart_beat_configuration
{
    timer_hnd heart_beat_timer;
    bool is_heart_beat_enabled;
    GPIO_PORT heart_beat_port;
    GPIO_PIN heart_beat_pin;
};

static struct heart_beat_configuration heart_beat_cfg __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY

/****************************************************************************************
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************/

static void heart_beat_callback(void)
{
    static bool status = 0;
    if ( status )
    {
        GPIO_SetInactive(heart_beat_cfg.heart_beat_port, heart_beat_cfg.heart_beat_pin);
    }
    else
    {
        GPIO_SetActive(heart_beat_cfg.heart_beat_port, heart_beat_cfg.heart_beat_pin);
    }
    status = ! status;
    heart_beat_cfg.heart_beat_timer = app_easy_timer(HRTBT_PIN_TOGGLING_INTERVAL, heart_beat_callback);
}

/****************************************************************************************
 * EXPORTED FUNCTION DEFINITIONS
 ****************************************************************************************/

bool is_heart_beat_hardware_conf_valid(void)
{
    bool is_heart_beat_pin_found = false;

    // Run through all IO pins in the pin configuration array to find the heartbeat pin
    uint8_t num_of_pins_in_conf_array = sizeof(codeless_env.port_configuration) / sizeof(codeless_env.port_configuration[0]);
    for (uint8_t j = 0; j < num_of_pins_in_conf_array; j++)
    {
        // Check if heart beat is configured
        if (IO_FUNC_HRTBT == codeless_env.port_configuration[j])
        {
            is_heart_beat_pin_found = true;
            break;
        }
    }
    return is_heart_beat_pin_found;
}

void set_heart_beat_pin_port_cfg(GPIO_PORT port, GPIO_PIN pin)
{
    heart_beat_cfg.heart_beat_port = port;
    heart_beat_cfg.heart_beat_pin = pin;
}

void start_heart_beat(void)
{
    if (!heart_beat_cfg.is_heart_beat_enabled)
    {
        heart_beat_cfg.heart_beat_timer = app_easy_timer(HRTBT_PIN_TOGGLING_INTERVAL, heart_beat_callback);
        heart_beat_cfg.is_heart_beat_enabled = true;
    }
}

void stop_heart_beat(void)
{
    if (heart_beat_cfg.is_heart_beat_enabled)
    {
        app_easy_timer_cancel(heart_beat_cfg.heart_beat_timer);
        heart_beat_cfg.is_heart_beat_enabled = false;
    }
}

bool is_heart_beat_enabled(void)
{
    return heart_beat_cfg.is_heart_beat_enabled;
}

#endif // USE_AT_HRTBT

/// @} APP
