/**
 ****************************************************************************************
 *
 * @file user_at_console.h
 *
 * @brief  Codeless console error codes and enumerations
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

#ifndef _USER_AT_CONSOLE_H_
#define _USER_AT_CONSOLE_H_
/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup APP_CODELESS
 *
 * @brief Codeless environment.
 *
 * Declares global codeless environment to be used throughout the application.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "user_command_interface.h"


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */


#if (CMD_LOCAL_SOURCE == CMD_SPI || CMD_LOCAL_SOURCE == CMD_I2C) && defined(CFG_DATAPMP)
    #warning "Binary commands do not work through spi or i2c command interfaces"
#endif

#define CMD_BUFFER_SIZE 165               /**< Size of at receive buffer */
#define CMD_MAX_ARG_COUNT 5               /**< Max number of at command arguments */
#define RPLY_MAX_SIZE 255                 /**< Max length of at command reply string */
#define AT_CONSOLE_PRINT_ERROR_MESSAGES   /**< Define this if detailed messages are to be printed.*/

/**
 * \brief AT console error status enumeration
 */
typedef enum
{
    AT_CONSOLE_NO_ERROR=0,    /**< No error detected */
    AT_CONSOLE_ERROR_1,       /**< ADC pins not properly set */
    AT_CONSOLE_ERROR_2,       /**< HW not properly set generic message*/
    AT_CONSOLE_ERROR_3,       /**< I2C parameters specified are not valid */
    AT_CONSOLE_ERROR_4,       /**< Invalid advertise data */
    AT_CONSOLE_ERROR_5,       /**< Undefined  reply destination*/
    AT_CONSOLE_ERROR_6,       /**< Non AT command.*/
    AT_CONSOLE_ERROR_7,       /**< Tried to send to peer but no connection .*/
    AT_CONSOLE_ERROR_8,       /**< Could not allocate memory */
    AT_CONSOLE_ERROR_9,       /**< mem or memcmd length longer than max */
    AT_CONSOLE_ERROR_10,      /**< Invalid mem or memcmd slot */
    AT_CONSOLE_ERROR_11,      /**< Invalid timer id */
    AT_CONSOLE_ERROR_12,      /**< Invalid gpio function requested */
    AT_CONSOLE_ERROR_13,      /**< AT command argument out of range */
    AT_CONSOLE_ERROR_14,      /**< Invalid parameter range */
    AT_CONSOLE_ERROR_15,      /**< Device is connected */
    AT_CONSOLE_ERROR_16,      /**< Device is not connected */
    AT_CONSOLE_ERROR_MAX_VAL,
} AT_CONSOLE_ERROR_TYPE_t;

/**
 * \brief AT command source
 *
 * This enumeration type is used to keep track of where an AT command originated
 */
typedef enum CMD_SRC
{
    CMD_SRC_UNDEFINED,      /**<  */
    CMD_SRC_LOCAL,          /**< Command from local uart  */
    CMD_SRC_REMOTE,         /**< Command from peer */
    CMD_SRC_SEQ,            /**< Command from command sequencer */
    CMD_SRC_HNDL,           /**< Command from event handler */
} CMD_SRC_t;

/**
 * \brief AT command reply destination
 *
 * This enumeration type is used to keep track of where the
 * response is to be generated
 */
typedef enum CMD_DEST
{
    CMD_DEST_UNDEFINED,      /**<  */
    CMD_DEST_LOCAL,          /**< Reply tolocal uart  */
    CMD_DEST_REMOTE,         /**< Reply to peer */
} CMD_DEST_t;

/**
 * \brief character parser status
 */
typedef enum CHAR_PARSER_STATUS
{
    CHAR_PARSER_ACTIVE,     /**< Characther parser is active and is scanning for characters*/
    CHAR_PARSER_NOT_ACTIVE, /**< Characther parser is not active. */
} CHAR_PARSER_STATUS_t;

/**
 * \brief  at console environment
 */
struct at_console_env_t
{
    CHAR_PARSER_STATUS_t parser_flag;         /**< Flag to denote that character parser is active */
    uint8_t cmd_buffer_single_char;           /**< Character buffer from character source */
    size_t input_cmd_char_index;              /**< Characther index of incomming commmand */
    char at_cmd_rx_buffer[CMD_BUFFER_SIZE];   /**< Command buffer from character buffer */
    bool echo;                                /**< Local command source Echo function flag */
    bool error_report_flag;                   /**< Error report flag */
};

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

extern struct at_console_env_t console_env;
#ifdef AT_CONSOLE_PRINT_ERROR_MESSAGES
extern const char* user_error_message[AT_CONSOLE_ERROR_MAX_VAL];
#endif
/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 * \brief  Send reply_string to local peer.
 */
void send_to_local(const char* reply_string);

/**
 * \brief  Send reply_string to local peer without printing CRLF
 */
void send_to_local_no_CRLF(const char* reply_string);

/**
 * \brief  Report error id
 *
 * If AT_CONSOLE_PRINT_ERROR_MESSAGES is defined then explicit messages are printed to the local
 * peer console. Oterwise the error id is printed. If required a custom error reporting scheme
 * can be implemeneted under this function.
 */
void at_console_error_report(AT_CONSOLE_ERROR_TYPE_t error_id);
#endif //_USER_AT_CONSOLE_H_

/// @} APP
