/**
 ****************************************************************************************
 *
 * @file user_heartbeat.h
 *
 * @brief user_heartbeat header file.
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

#ifndef _USER_HEART_BEAT_H_
#define _USER_HEART_BEAT_H_

#include "stdbool.h"
#include "stdint.h"
#include "gpio.h"

/**
 ****************************************************************************************
 * @brief      Sets the new security and pairing mode
 *
 * @return     bool, true if heart beat configuration is valid, false otherwise
 *****************************************************************************************
 */
bool is_heart_beat_hardware_conf_valid(void);

/**
 ****************************************************************************************
 * @brief      Sets the heartbeat port and pin configuration
 *
 * @param[in]  port, the heartbeat gpio port
 * @param[in]  pin , the heartbeat gpio pin
 *
 * @return     bool, true if heart beat configuration is valid, false otherwise
 *****************************************************************************************
 */
void set_heart_beat_pin_port_cfg(GPIO_PORT port, GPIO_PIN pin);

/**
 ****************************************************************************************
 * @brief      Stops the heartbeat operation
 *
 * @return     void
 *****************************************************************************************
 */
void stop_heart_beat(void);

/**
 ****************************************************************************************
 * @brief      Start the heartbeat operation
 *
 * @return     void
 *****************************************************************************************
 */
void start_heart_beat(void);

/**
 ****************************************************************************************
 * @brief      Retrieves the current heartbeat status
 *
 * @return     bool, true if heart beat is enabled, false otherwise
 *****************************************************************************************
 */
 bool is_heart_beat_enabled(void);


#endif //_USER_HEART_BEAT_H_
/// @} APP
