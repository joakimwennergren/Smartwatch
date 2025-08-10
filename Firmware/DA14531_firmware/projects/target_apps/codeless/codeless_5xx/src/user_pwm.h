/**
 ****************************************************************************************
 *
 * @file user_pwm.h
 *
 * @brief user_pwm header file.
 *
 * Copyright (C) 2018-2024 Renesas Electronics Corporation and/or its affiliates.
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

#ifndef _USER_PWM_H_
#define _USER_PWM_H_

#include "app_api.h"
#include "user_codeless_env.h"

#define MINIMUM_PWM_FREQUENCY          1000  // 1000 Hz
#define MAXIMUM_PWM_FREQUENCY        500000  // 500 KHz
#define MAXIMUM_PWM_DURATION_IN_MS    10000  // 10 sec
#define MINIMUM_PWM_DURATION_IN_MS      100  // 0.1 sec


/**
 ****************************************************************************************
 * @brief    Checks if pwm hardware configuration is valid
 *
 * @return   true if the configuration is valid, false otherwise
 *****************************************************************************************
 */
bool is_pwm_hardware_configuration_valid(void);

/**
 ****************************************************************************************
 * @brief      Configures pwm output
 *
 * @param[in]  pwm_frequency, the frequency of the pwm pulse (1000 Hz to 8MHz)
 * @param[in]  duty_cycle, the duty cycle ranging from 0 to 100
 * @param[in]  duration, the duration of pwm in milliseconds (1ms to 1000ms)
 *
 * @return   0 on success,a negative number on error
 *****************************************************************************************
 */
int pwm(uint32_t pwm_frequency, uint8_t duty_cycle, uint16_t duration_in_ms);

#endif //_USER_PWM_H_
/// @} APP
