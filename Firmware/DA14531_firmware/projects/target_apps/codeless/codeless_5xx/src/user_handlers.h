/**
 ****************************************************************************************
 *
 * @file user_handlers.h
 *
 * @brief Declaration of the functions used for CodeLess handlers
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

#ifndef _USER_HANDLERS_H_
#define _USER_HANDLERS_H_

#include "app_handlers_db.h"
#include "stdbool.h"

/**
 * \brief  event handlers enumeration
 */


/**
 ****************************************************************************************
 * @brief      enables the selected handler
 *
 * @param[in]  handler, the specified handler
 * @param[in]  commands, a string of AT Commands that will be executed
 * @param[in]  length of the string of AT commands
 *
 * @return     zero if successful, a negative number if an error occurs
 *****************************************************************************************
 */
int user_enable_handler(EVENT_HANDLERS_ENUM handler, char * commands, int size);

/**
 ****************************************************************************************
 * @brief      Checks that ports have been configured so that there is support for I2C.
 *             There must be one I2C SCL and one I2C SDA port defined
 *
 * @return     True if both I2C SCL and I2C SDA has been configured
 *****************************************************************************************
 */
void user_disable_handler(EVENT_HANDLERS_ENUM handler);

/**
 ****************************************************************************************
 * @brief      Checks if the specified handler is enabled or not
 *
 * @param[in]  handler the specified handler
 *
 * @return     true if specified handler is enabled, false otherwise
 *****************************************************************************************
 */

bool user_is_handler_enabled(EVENT_HANDLERS_ENUM handler);

/**
 ****************************************************************************************
 * @brief      returns the command string of the specified handler
 *
 * @param[in]  handler the specified handler
 *
 * @return     the command string if available,NULL otherwise
 *****************************************************************************************
 */

const char * user_get_handler_command_string(EVENT_HANDLERS_ENUM handler);

/**
 ****************************************************************************************
 * @brief      checks if argument specifies a valid USER_EVENT_HANDLERS_ENUM
 *
 * @param[in]  argument the argument provided in the command line
 * @param[out] handler a pointer to a valid handler if the argument is correct and the
 *             handler is not NULL
 *
 * @return     true if the argument is correct, false otherwise
 *****************************************************************************************
 */
bool user_is_handler_argument_valid(const char * const argument, EVENT_HANDLERS_ENUM * handler);

#endif //_USER_HANDLERS_H_
/// @} APP
