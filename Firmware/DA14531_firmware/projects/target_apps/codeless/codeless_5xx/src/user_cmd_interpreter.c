/**
 ****************************************************************************************
 *
 * @file user_cmd_interpreter.c
 *
 * @brief AT commands interpreter source file.
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
#include "user_cmd_interpreter.h"
#include "arch_console.h"
#include "uart.h"
#include "gpio.h"
#include "adc.h"
#include "battery.h"
#include "custs1_task.h"
#include "user_custs_config.h"
#include "user_custs1_def.h"
#include "stdlib.h"
#include "user_cmd_parser.h"
#include "user_i2c.h"
#include "user_gap.h"
#include "user_gatt.h"
#include "user_periph_setup.h"
#include "user_at_commands.h"
#include "user_utility_functions.h"
#include "ke_mem.h"
#include "user_codeless_env.h"


/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
extern struct codeless_env_t codeless_env;
extern const struct at_command_characteristics_t at_commands_chars[];
/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void user_at_cmd_reply(struct at_cmd_params_t* cmd_arguments, char* reply_string)
{
    if (cmd_arguments->reply_flag)
    { //some commands suppress answers explicitly.
        if (cmd_arguments->success_flag)
        {
            // Append 'OK' to response
            arch_sprintf(reply_string, "%s%s", reply_string, OK_TERMINATION_STRING);
        }
        else
        {
            // Append 'ERROR' to response
            arch_sprintf(reply_string, "%s%s", reply_string, ERROR_TERMINATION_STRING);
        }
        // Reply to BT Peer if the command originated there (only if connected)
        if (cmd_arguments->cmd_source == CMD_SRC_REMOTE)
        {
            send_to_remote(reply_string);
        }
        else if (cmd_arguments->cmd_source == CMD_SRC_LOCAL)
        {
            // Reply locally
            send_to_local(reply_string);
        }
        else if (cmd_arguments->cmd_source == CMD_SRC_SEQ)
        {
            // Reply locally if command originates from command sequencer
            send_to_local(reply_string);
        }
#ifdef USE_AT_HNDL
        else if (cmd_arguments->cmd_source == CMD_SRC_HNDL)
        {
            // Reply locally if command originates from event handler
            send_to_local(reply_string);
        }
#endif
        else
        {
            at_console_error_report(AT_CONSOLE_ERROR_5); // Undefined reply destination
        }
    }
}

static void user_cmd_arguments_init(struct at_cmd_params_t* cmd_args, char* cmd_rx_buffer,
                                    uint32_t cmd_length, CMD_SRC_t cmd_source)
{
    cmd_rx_buffer[cmd_length - 1] = 0x00; // Explicitly null terminate input string.
    cmd_args->cmd_buffer = cmd_rx_buffer;
    cmd_args->cmd_length = cmd_length;
    cmd_args->cmd_source = cmd_source;
    cmd_args->cmd_tag_index = 0;
    cmd_args->command_tag_length = 0;
    cmd_args->arg_count = 0;
    for (uint8_t i = 0; i < CMD_MAX_ARG_COUNT; i++) {
        cmd_args->arg_index[i] = 0;
        cmd_args->arg_length[i] = 0;
    }
    cmd_args->success_flag = false;
    cmd_args->reply_flag = true;
    cmd_args->error_status = AT_CONSOLE_NO_ERROR;
}

void user_cmd_interpreter(char* cmd_rx_buffer, uint32_t cmd_length, CMD_SRC_t cmd_source)
{
    /* Initialize command arguments */
    struct at_cmd_params_t cmd_arguments;
    user_cmd_arguments_init(&cmd_arguments, cmd_rx_buffer, cmd_length, cmd_source);

    /* Start parsing */
    // Check if this is a valid reply
    if (validate_at_reply(cmd_arguments.cmd_buffer)) {
        // Print response
        send_to_local(cmd_arguments.cmd_buffer);
    } else {
        AT_COMMAND_ID_t at_cmd_index;
        // Pre-processing of command - remove backspaces and carriage return.
        clean_at_command(cmd_arguments.cmd_buffer, cmd_arguments.cmd_length);
        // Verify at command validity
        AT_CMD_TYPE_t input_cmd_type = validate_at_command(cmd_arguments.cmd_buffer);
        // Route command
        if ((input_cmd_type == AT_CMD_LOCAL) ||
           ((input_cmd_type == AT_CMD_REMOTE) && (cmd_source == CMD_SRC_REMOTE)) ||
           ((input_cmd_type == AT_CMD_LOCAL) && (cmd_source == CMD_SRC_SEQ)))
        {
            // Local AT command or remote AT command from peer -> interpret locally.
            // Parse at command components: tag and arguments.
            parse_at_command(&cmd_arguments);
            // Get at command id based on tag.
            at_cmd_index = get_at_command_id(&cmd_arguments);

            // Allocate memory for reply string.
            {
                char* at_cmd_reply_string;
                size_t reply_str_len = RPLY_MAX_SIZE;

                if (user_malloc(&at_cmd_reply_string, reply_str_len, KE_MEM_NON_RETENTION))
                {
                    // Perform AT command functionality via callback and form a reply message.
                    at_commands_chars[at_cmd_index].callback(&cmd_arguments, at_cmd_reply_string);
                    if(codeless_env.disable_local_reply==true)
                    {
                         /* This is a passthrough command that affects both ends, we keep only the remote reply */
                        ke_free(at_cmd_reply_string);
                        codeless_env.disable_local_reply=false;
                        return;
                    }
                    // Report last error status that has been reported by  if any.
    #ifdef AT_CONSOLE_PRINT_ERROR_MESSAGES
                    if ((cmd_arguments.error_status != AT_CONSOLE_NO_ERROR)
                        && (cmd_arguments.error_status < AT_CONSOLE_ERROR_MAX_VAL)
                        && (console_env.error_report_flag)) {
                        arch_sprintf(at_cmd_reply_string,
                                     user_error_message[cmd_arguments.error_status]);
    #endif
                    }
                    // Return at command reply depending on reply destination
                    user_at_cmd_reply(&cmd_arguments, at_cmd_reply_string);
                    // free allocated memory for reply string
                    ke_free(at_cmd_reply_string);
                } else {
                    // Could not allocate max memory requireed for reply response.
                    at_console_error_report(AT_CONSOLE_ERROR_8);
                }
            }


        } else if (((input_cmd_type == AT_CMD_PIPE) || (input_cmd_type == AT_CMD_REMOTE))
                   && (cmd_source == CMD_SRC_LOCAL)) {
            // Pipe command or a remote at command from local source, send to peer.
            send_to_remote(cmd_arguments.cmd_buffer);
        } else if ((input_cmd_type == AT_CMD_PIPE) && (cmd_source == CMD_SRC_REMOTE)) {
            // Pipe command from remote peer, print to local terminal.
            send_to_local(cmd_arguments.cmd_buffer);
        } else {
            at_console_error_report(AT_CONSOLE_ERROR_6);
            send_to_local(ERROR_TERMINATION_STRING);
        }
    }
}

/// @} APP
