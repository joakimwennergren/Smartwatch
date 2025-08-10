/**
 ****************************************************************************************
 *
 * @file user_gatt.h
 *
 * @brief user_gatt header file.
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

#ifndef _USER_GATT_H_
#define _USER_GATT_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "app_api.h"
#include "prf.h"
/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
*/

/**
 ****************************************************************************************
 * @brief  Sends a string (command or response) to remote peer (BLE).
 *
 * @param[in]  str_to_send pointer to string that is to be send
 *****************************************************************************************
 */
void send_to_remote(char* str_to_send);

/**
 ****************************************************************************************
 * @brief  Performs a GATT characteristics discovery.
 *
 *****************************************************************************************
 */
void user_gatt_discover_chars(void);

/**
 ****************************************************************************************
 * @brief  Performs a GATT write operation
 *
 * @param[in] handle of the characteristic that data needs to be written
 *
 * @param[in] value pointer to data that will be written
 *
 * @param[in] length length of value data
 *
 * @param[in] operation GATT operation
 *
 * @param[in] seq_num the sequence number that marks the write operation
  *****************************************************************************************
 */
void user_prf_gatt_write(uint16_t handle, uint8_t* value, uint16_t length, uint8_t operation,  uint16_t seq_num);

/**
 ****************************************************************************************
 * @brief  Sends to peer ble device SPS flow on or off
 *
 * @param[in]  flow flow value
 *****************************************************************************************
 */
void user_send_sps_ble_flow(char flow);
#endif //_USER_GATT_H_
/// @} APP
