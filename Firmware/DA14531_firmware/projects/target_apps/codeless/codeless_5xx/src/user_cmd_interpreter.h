/**
 ****************************************************************************************
 *
 * @file user_cmd_interpreter.h
 *
 * @brief Function declarations for the interpretation of CodeLess AT commands
 *
 * Copyright (C) 2018-2023 Renesas Electronics Corporation and/or its affiliates.
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

#ifndef _USER_CMD_INTERPRETER_H_
#define _USER_CMD_INTERPRETER_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup APP_CODELESS
 *
 * @brief Codeless command interpreter.
 *
 * Provides function user_cmd_interpeter and helper functions, that are used to parse and execute
 * incoming commands.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "app_api.h"
#include "user_cmd_parser.h"
#include "user_at_console.h"
//#include "user_codeless_env.h"
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Replies back to the originator of a command.
 *
 * @param[in]  reply_string Pointer to the reply string. In case of an empty string for an
 *                          error report in case of failure, it should have at least
 *                          ERROR_REPORT_STRING length.
 * @param[in]  cmd_arguments Pointer to the command arguments structure.

 *****************************************************************************************
 */
void user_at_cmd_reply(struct at_cmd_params_t* cmd_arguments, char* reply_string);

/**
 ****************************************************************************************
 * @brief Interprets and handles individual AT commands.
 *
 * @param[in]  cmd_rx_buffer Pointer to command buffer.
 * @param[in]  cmd_length    Length of incoming command.
 * @param[in]  cmd_source    Source of incoming command (Local or remote peer).
 *****************************************************************************************
 */
void user_cmd_interpreter( char* cmd_rx_buffer, uint32_t cmd_length, CMD_SRC_t cmd_source);

#endif //_USER_CMD_INTERPRETER_H_

/// @} APP
