/**
 ****************************************************************************************
 *
 * @file user_cmd_parser.h
 *
 * @brief Functions for parsing at commands from codeless interpreter.
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

#ifndef _USER_CMD_PARSER_H_
#define _USER_CMD_PARSER_H_
/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup APP_CODELESS
 *
 * @brief Codeless command parser.
 *
 * Functions for parsing at commands from codeless interpreter.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "app_api.h"
#include "user_at_console.h"
#include "user_at_commands.h"

/*
 * DEFINITIONS
 ****************************************************************************************
 */
 /**
  * \brief Bluetooth activity state
  *
  * This enumeration type is used to keep track of current device Bluetooth activity state
  */
 typedef enum AT_CMD_TYPE
 {
     AT_CMD_LOCAL,  //AT or AT+, a command issued from local source with local destination
     AT_CMD_REMOTE, //Ar or ATr+, a command either from remote peer or to remote peer
     AT_CMD_PIPE,   // | destination remote peer.
     AT_CMD_UNDEFINED,
 } AT_CMD_TYPE_t;
/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Start command input character parser.
 *
 * Start and keep active interrupt callback that is reading charachters from
 * character input source. (currently only UART is supported)
 *****************************************************************************************
 */
void user_character_parser_start(void);

/**
 ****************************************************************************************
 * @brief Character parser logic implementation.
 *
 * This function receives every character from command source and fills in the command buffer
 *  When a carriage return is detected or the comand buffer has overflown user_at_cmd_ready
 *  is called and string passed over uart is parsed.
 *
 * @param[in]  status Uart callback status - not in use - here to supres warnings.
 *****************************************************************************************
 */
void user_character_parser(uint16_t status);

/**
 ****************************************************************************************
 * @brief Message to task app that an at command has been issued.
 *
 * If a valid length input string has been detected a message is sent to task app
 * to be processed as a command.
 *
 * @param[in]  bytes Length of incoming command.
 *****************************************************************************************
 */
void user_at_cmd_ready(uint32_t bytes);

/**
 ****************************************************************************************
 * @brief Clean at command buffer content.
 *
 * Removes back-space and carriage return characters. Zero terminates command string
 *
 * @param[in]  cmd_buffer Pointer to input command buffer.
 * @param[in]  cmd_length Input string length in bytes.
 *****************************************************************************************
 */
void clean_at_command(char* cmd_buffer, size_t cmd_length);

/**
 ****************************************************************************************
 * @brief Extract arguments from at command.
 *
 * Parses a valid at command. Locates command tag index, command arguments index and length
 * and replaces with null = and comma in order to have null terminated strings addresable
 * with their index from the original command buffer.
 *****************************************************************************************
 */
bool parse_at_command(struct at_cmd_params_t *cmd_arguments);

/**
 ****************************************************************************************
 * @brief Validate at command buffer content.
 *
 * Validates the format of the AT command. Returns true if the format is valid.
 *****************************************************************************************
 */
AT_CMD_TYPE_t validate_at_command(char *cmd_buffer);


/**
 ****************************************************************************************
 * @brief Validate at command reply.
 *
 * validate if content in reply_buffer is a valid console respone or not.
 * checks if  ending is a valid OK_TERMINATION_STRING or error STRING
 ******************************************************************************************
 */
bool validate_at_reply(char* reply_buffer);

/**
 ****************************************************************************************
 * @brief Matches command tag and number of aguments and returns AT_COMMAND_ID
 *
 *****************************************************************************************
 */
AT_COMMAND_ID_t get_at_command_id(struct at_cmd_params_t *arguments);

#endif //_USER_CMD_PARSER_H_

/// @} APP
