/**
 ****************************************************************************************
 *
 * @file  user_at_console.c
 *
 * @brief Console functions and errors messages source file
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "user_at_console.h"
#include "arch_console.h"
#include "user_codeless_strings.h"
#include "user_utility_functions.h"
#include "user_custs_sps.h"
#include "user_spi_command_interface.h"
/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/// The global environment for at console - @RETENTION MEMORY
struct at_console_env_t console_env __SECTION_ZERO("retention_mem_area0");

#ifdef AT_CONSOLE_PRINT_ERROR_MESSAGES
const char* user_error_message[AT_CONSOLE_ERROR_MAX_VAL] = {
    "EC00: NO ERROR",
    "EC01: ADC pins error",
    "EC02: HW not properly set", // This was I2C specific but now it is generic
    "EC03: Invalid I2C parameters",
    "EC04: Invalid advertising data",
    "EC05: Undefined reply destination",
    "EC06: Non AT command",
    "EC07: Tried to send to peer - no connection",
    "EC08: Memory allocation error",
    "EC09: Mem/memcmd length exceeded",
    "EC10: Invalid memcmd slot",
    "EC11: Invalid timer id",
    "EC12: Invalid gpio function requested",
    "EC13: Argument out of range",
    "EC14: Invalid parameters",
    "EC15: Device connected",
    "EC16: Device not connected",
};
#endif

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void send_to_local_no_CRLF(const char* reply_string)
{
#if CMD_LOCAL_SOURCE == CMD_UART
     #ifdef USE_AT_BINARY_MODE
    if (activate_binary_mode(true)==true)
    {
        return;
    }
    #endif
    arch_printf("%s", reply_string);
    user_host_wakeup_process();
#elif CMD_LOCAL_SOURCE == CMD_SPI

    user_host_wakeup_process();

    int length = strlen(reply_string);
    spihddr_store_slave_tx_msg((uint8_t*)reply_string, strlen(reply_string));
        //user_codeless_spi_start();


#elif CMD_LOCAL_SOURCE == CMD_I2C
    // TODO: Implement for drop 2
#else
#error undefined CMD_LOCAL_SOURCE
#endif
}

void send_to_local(const char* reply_string)
{
#if CMD_LOCAL_SOURCE == CMD_UART
     #ifdef USE_AT_BINARY_MODE
    if (activate_binary_mode(true)==true)
    {
        return;
    }
    #endif
    arch_printf("\r\n%s", reply_string);
    user_host_wakeup_process();
#elif CMD_LOCAL_SOURCE == CMD_SPI

    user_host_wakeup_process();

    int length = strlen(reply_string);
    spihddr_store_slave_tx_msg((uint8_t*)reply_string, strlen(reply_string));
        //user_codeless_spi_start();


#elif CMD_LOCAL_SOURCE == CMD_I2C
    // TODO: Implement for drop 2
#else
#error undefined CMD_LOCAL_SOURCE
#endif
}

void at_console_error_report(AT_CONSOLE_ERROR_TYPE_t error_id)
{
    if (console_env.error_report_flag) {
        if (error_id < AT_CONSOLE_ERROR_MAX_VAL) {
#ifdef AT_CONSOLE_PRINT_ERROR_MESSAGES
            send_to_local(user_error_message[error_id]);
#else
            // print error code to local terminal.
            char error_code_string[15];
            arch_sprintf(error_code_string, "\r\n error id: %d ", (uint8_t)error_id);
            arch_sprintf(error_code_string, "%s%s", error_code_string, ERROR_TERMINATION_STRING);
            send_to_local(error_code_string);
            // or implement a custom error code mechanism i.e num of pulses to a gpio.
#endif
        }
    }
}

/// @} APP
