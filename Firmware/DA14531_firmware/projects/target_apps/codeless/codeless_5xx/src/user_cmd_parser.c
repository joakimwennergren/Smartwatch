/**
 ****************************************************************************************
 *
 * @file user_cmd_parser.c
 *
 * @brief AT commands parser source file.
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
#include "user_cmd_parser.h"
#include "arch_console.h"
#include "uart.h"
#include "stdlib.h"
#include "custs1_task.h"
#include "user_codeless_strings.h"
#include "user_codeless_env.h"
#include "user_spi_command_interface.h"
#include "user_at_console.h"
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
#if CMD_LOCAL_SOURCE == CMD_UART
void uart2_tx_dummy_callback(uint8_t nothing)
{
    // do nothing - callback for echo uart2write implementing echo functionality.
}
#endif

void user_codeless_uart_start(void)
{
    #ifdef USE_AT_BINARY_MODE
    if ( codeless_env.binary_mode==false)
    {
        user_character_parser_start();
    }
    #else
    user_character_parser_start();
    #endif
}

void user_codeless_spi_start(void)
{
    user_character_parser_start();
}


void user_character_parser_start(void)
{
#if CMD_LOCAL_SOURCE == CMD_UART
    //uart2_read(&console_env.cmd_buffer_single_char, 1, user_character_parser);
    uart_register_rx_cb(CODELESS_UART,user_character_parser);
    uart_receive(CODELESS_UART,&console_env.cmd_buffer_single_char,1,UART_OP_INTR);

#elif CMD_LOCAL_SOURCE == CMD_SPI
    register_spi_rx_callback(&user_character_parser);
    conf_spi_slave_cmd_interface();

#elif CMD_LOCAL_SOURCE == CMD_I2C

#else
#error undefined CMD_LOCAL_SOURCE
#endif
}

/**
 ****************************************************************************************
 * @brief Write one character to uart.If uart is busy add the character to a list for
          later printing
 * @param[in] uart_id Identifies which UART to use
 * @return void
 ****************************************************************************************
**/

#if defined(USE_DELAYED_PRINTING_ON_BUSY_UART)
static void print_character(uart_t *uart_id, uint8_t data)
{
    extern printf_msg *printf_msg_list;
    if (printf_msg_list !=NULL)
    {
        arch_printf("%c",data);
    }
    else
    {
        uart_write_byte(CODELESS_UART, data);
    }
}
#endif

void user_character_parser(uint16_t status)
{
    volatile uint8_t input_data;

    // Echo implementation - uart specific.
#if CMD_LOCAL_SOURCE == CMD_UART
    input_data = console_env.cmd_buffer_single_char;
    console_env.at_cmd_rx_buffer[console_env.input_cmd_char_index] = input_data;
    console_env.input_cmd_char_index++;
    if (console_env.echo)
    {
        // Print incoming character.
#if defined(USE_DELAYED_PRINTING_ON_BUSY_UART)
        print_character(CODELESS_UART, input_data);
#else
        uart_write_byte(CODELESS_UART, input_data);
#endif

        //uart2_write(&input_data, 1, uart2_tx_dummy_callback);
        // If incoming character is backspace, then go back and print a space to the character
        // position to be deleted.
        if (input_data == 0x08)
        {
            uint8_t s[2] = { 0x20, 0x08 };
#if defined(USE_DELAYED_PRINTING_ON_BUSY_UART)
            print_character(CODELESS_UART,s[0]);
            print_character(CODELESS_UART,s[1]);
#else
            uart_write_byte(CODELESS_UART,s[0]);
            uart_write_byte(CODELESS_UART,s[1]);
#endif
        }
    }
#elif CMD_LOCAL_SOURCE == CMD_SPI

    /*
    This whole part is executed within the spi_rx_callback which is in turn
    executed within the cs deassertion isr.
    */
    volatile struct spi_slave_rx_data_t* data=get_spi_rx_data();
    if (console_env.echo)
    {
        // If echo is enabled the initial request must be sent back.
    }
    console_env.cmd_buffer_single_char=data->rx_buffer[data->number_of_bytes_received-1];
    input_data = console_env.cmd_buffer_single_char;
    console_env.at_cmd_rx_buffer[console_env.input_cmd_char_index] = input_data;
    console_env.input_cmd_char_index = data->number_of_bytes_received;
    console_env.input_cmd_char_index++;
    memcpy(console_env.at_cmd_rx_buffer,(uint8_t*)data->rx_buffer, data->number_of_bytes_received);


#elif CMD_LOCAL_SOURCE == CMD_I2C

    //to be completed

#endif
    // Was this a Carriage-Return char? or a command buffer overflow?
    if (input_data == 0x0D || console_env.input_cmd_char_index > CMD_BUFFER_SIZE) {
        console_env.at_cmd_rx_buffer[console_env.input_cmd_char_index]
            = 0; // null terminate command string
        user_at_cmd_ready( console_env.input_cmd_char_index);
        // reset command buffer index to start
        console_env.input_cmd_char_index = 0;
    }
#if CMD_LOCAL_SOURCE == CMD_UART
    user_codeless_uart_start();
#elif CMD_LOCAL_SOURCE == CMD_SPI
    /*
    At this point the command has been sent.Waiting for the reply.
    No action is necessary
    */

    //user_codeless_spi_start();

#elif CMD_LOCAL_SOURCE == CMD_I2C

#else
#error undefined CMD_LOCAL_SOURCE
#endif
}

void user_at_cmd_ready( uint32_t bytes)
{
    // Do not interpret commands longer than allowed length.
    if (bytes <= CMD_BUFFER_SIZE) {
        struct user_app_cmd_received* at_cmd_msg = KE_MSG_ALLOC_DYN(
            USER_APP_CMD_RECEIVED, TASK_APP, TASK_APP, user_app_cmd_received, bytes);
        at_cmd_msg->bytes = bytes;
        at_cmd_msg->cmd_source = CMD_SRC_LOCAL;
        memcpy(at_cmd_msg->cmd_buffer, console_env.at_cmd_rx_buffer, bytes);
        KE_MSG_SEND(at_cmd_msg);

        // Reset console_env.at_cmd_rx_buffer content
        memset(console_env.at_cmd_rx_buffer, 0, CMD_BUFFER_SIZE);
    }
}

void clean_at_command(char* cmd_buffer, size_t cmd_length)
{
    // Removes backspace characters and carriage return. Null terminates the command string.
    uint8_t index = 0;
    for (uint8_t i = 0; i < cmd_length; i++)
    {
        if (cmd_buffer[i] == 0x08)
        {
            index--;
        }
        else
        {
            //if a carriage return is returned make it a null termination
            if (cmd_buffer[i] == 0x0D)
            {
                cmd_buffer[index++] = 0x00;
            }
            else
            {
                cmd_buffer[index++] = cmd_buffer[i];
            }
        }
    }
}

bool parse_at_command(struct at_cmd_params_t* cmd_arguments)
{
    // Locate command tag start index
    if ((cmd_arguments->cmd_buffer[2] == 'r') || (cmd_arguments->cmd_buffer[2] == '+')) {
        if (cmd_arguments->cmd_buffer[3] == '+') {
            /* ATr+ */
            cmd_arguments->cmd_tag_index = 4;
        } else {
            /* ATr or AT+ */
            cmd_arguments->cmd_tag_index = 3;
        }
    } else {
        if ((cmd_arguments->cmd_buffer[0] == 0x00) && (cmd_arguments->cmd_buffer[1] == 0x00)) {
            /* plain carriage return */
            cmd_arguments->cmd_tag_index = 0;
        } else {
            /* AT*/
            cmd_arguments->cmd_tag_index = 2;
        }

    }

    cmd_arguments->arg_count = 0;

    uint8_t next_index = 0;
    // Record and process command tag.
    for (uint8_t i = 0; i < cmd_arguments->cmd_length; i++) {
        // Locate command tag ending and null terminate string. Locate first argument index.
        if (cmd_arguments->cmd_buffer[i] == 0x00) {
            // This is the case for non = commands such as AT ATI ATE ATZ or commands issued
            // without arguments ie AT+ADVSTART
            // command_tag_state = false;
            cmd_arguments->command_tag_length = i - cmd_arguments->cmd_tag_index;
            next_index = i + 1;
            break;
        }
        if (cmd_arguments->cmd_buffer[i] == '=') {
            cmd_arguments->cmd_buffer[i]
                = 0x00; // null terminate command tag so it can be identified as a separate string
            cmd_arguments->arg_index[0] = i + 1;
            cmd_arguments->arg_count++;
            cmd_arguments->command_tag_length = i - cmd_arguments->cmd_tag_index;
            next_index = i + 1;
            break;
        }
    }

    // In case of CMDSTORE, there might be comma inside the second arguments, thus
    // special handling is required.
#ifdef USE_AT_CMD
    if (cmd_arguments->command_tag_length == 8) {
        bool cmdstore_flag = true;
        for (size_t i = 0; i < cmd_arguments->command_tag_length; i++) {
            char ith_tag_char = cmd_arguments->cmd_buffer[cmd_arguments->cmd_tag_index+i];
            if(ith_tag_char != at_commands_chars[AT_CMDSTORE].command_tag_string[i]){
                cmdstore_flag = false;
                break;
            }
        }
        //Check for = and , and if not a valid cmdstore command explicitly zero num of arguments
        //in order to fail.
        uint8_t arg_offset;
        if (cmd_arguments->cmd_buffer[cmd_arguments->cmd_tag_index+10]==',') {
            arg_offset = 11;
        }
        else if (cmd_arguments->cmd_buffer[cmd_arguments->cmd_tag_index+10]==',') {
            arg_offset = 12;
        }
        else{
            //not a valid cmdstore command - either not enough arguments or more than 99 command
            //slots have been referenced
            //cmd_arguments->arg_count = 0;
            cmdstore_flag = false;
        }
        if (cmdstore_flag) {
            // this is a cmdstore command.
            cmd_arguments->arg_count = 2;
            cmd_arguments->arg_index[0] = 9 + cmd_arguments->cmd_tag_index;
            cmd_arguments->arg_length[0] = 1;
            cmd_arguments->arg_index[1] = arg_offset + cmd_arguments->cmd_tag_index;
            cmd_arguments->arg_length[1] = cmd_arguments->cmd_length - cmd_arguments->arg_index[1];
            return true;
        }
    }
#endif

    /*
    In addition to the AT+CMDSTORE command, the AT+HNDL works in the same way.
    The second argument may have one or more commas and special handling is necessary
    */
#ifdef USE_AT_HNDL
    if (cmd_arguments->command_tag_length == strlen(at_commands_chars[AT_HNDL].command_tag_string))
    {
        // This may be an AT_HNDL command - the command length is correct.
        do
        {
            char * cmd_tag = &cmd_arguments->cmd_buffer[cmd_arguments->cmd_tag_index];
            // Check if the command tag is equal to the AT_HNDL one
            if (strncmp(cmd_tag, at_commands_chars[AT_HNDL].command_tag_string, cmd_arguments->command_tag_length) != 0)
            {
                // This is not an AT_HNDL command - the tags do not much
                break;
            }
            /*
            This is an AT_HNDL command.It may have no arguments.In that case there is no multiple commas issue.
            If there are arguments the cmd_arguments->arg_count will have a value greater than zero
            */
            if (cmd_arguments->arg_count == 0)
            {
                break;
            }
            /*
            This is an AT_HNDL command with arguments. There may be either one or two arguments.If a comma character
            is found after the '=' then there are two arguments.
            */
            char* first_comma_ptr = strchr(&cmd_arguments->cmd_buffer[cmd_arguments->arg_index[0]],',');
            if (first_comma_ptr == NULL ) // No commas found
            {
                // cmd_arguments->arg_count is already set
                // cmd_arguments->arg_index[0] is already set
                cmd_arguments->arg_length[0] = cmd_arguments->cmd_length - cmd_arguments->arg_index[0];
            }
            else
            {
                // At this point a comma character has been found and there are two arguments.
                cmd_arguments->arg_count = 2; // The number of arguments is 2
                // Replace comma with null character so it can be referenced as a null terminated string
                *first_comma_ptr = '\0';
                //Set the first argument length.The index for the first argument has been set already
                cmd_arguments->arg_length[0] = first_comma_ptr - &cmd_arguments->cmd_buffer[cmd_arguments->arg_index[0]];
                //Set the necessary information for the second argument
                cmd_arguments->arg_index[1] = cmd_arguments->arg_index[0]+cmd_arguments->arg_length[0]+1;
                cmd_arguments->arg_length[1] = cmd_arguments->cmd_length - cmd_arguments->arg_index[1];
                return true;
            }
        }
        while (0);
    }
#endif

    // The AT+PRINT command also needs special handling.The comma character may be part of the argument
#ifdef USE_AT_PRINT
    if (cmd_arguments->command_tag_length == strlen(at_commands_chars[AT_PRINT].command_tag_string))
    {
        // This may be an AT_PRINT command - the command length is correct.
        do
        {
            char* cmd_tag = &cmd_arguments->cmd_buffer[cmd_arguments->cmd_tag_index];
            // Check if the command tag is equal to the AT_PRINT one
            if (strncmp(cmd_tag, at_commands_chars[AT_PRINT].command_tag_string, cmd_arguments->command_tag_length) != 0)
            {
                // This is not an AT_PRINT command - the tags do not much
                break;
            }
            // This is indeed an AT_PRINT command.
            cmd_arguments->arg_count = 1;
            /*
            The cmd_arguments->arg_index[0] has been already set when the '=' was found.
            Only the length will be set
            */
            cmd_arguments->arg_length[0] = cmd_arguments->cmd_length - cmd_arguments->arg_index[0];
            return true;
        }
        while (0);
    }
#endif

    // Record and process command arguments
    for (uint8_t i = next_index; i < cmd_arguments->cmd_length; i++) {
        // record comma separated arguments if any and replace comma with null in order to
        // have null terminated strings for arguments referenced with argument index.
        if (cmd_arguments->cmd_buffer[i] == 0x00) {
            if (cmd_arguments->arg_count <= CMD_MAX_ARG_COUNT) {
                cmd_arguments->arg_length[cmd_arguments->arg_count - 1]
                    = i - cmd_arguments->arg_index[cmd_arguments->arg_count - 1];
            }
            break;
        } else if (cmd_arguments->cmd_buffer[i] == ',') {
            // replace comma with null character so it can be referenced as a null terminated
            // string from argument index.
            cmd_arguments->cmd_buffer[i] = 0x00;
            if (cmd_arguments->arg_count <= CMD_MAX_ARG_COUNT) {
                cmd_arguments->arg_index[cmd_arguments->arg_count] = i + 1;
                cmd_arguments->arg_length[cmd_arguments->arg_count - 1]
                    = i - cmd_arguments->arg_index[cmd_arguments->arg_count - 1];
            } else {
                // number of arguments in command larger than max defined
                // Only the first MAX_ARG_COUNT are considered.
                break;
            }
            cmd_arguments->arg_count++;
        }
    }
    return true;
}

AT_CMD_TYPE_t validate_at_command(char* cmd_buffer)
{
    AT_CMD_TYPE_t result;
    if (((cmd_buffer[0] == 'A') && (cmd_buffer[1] == 'T'))
        || ((cmd_buffer[0] == 0x00) && (cmd_buffer[1] == 0x00))) {
        //either a valid AT command or a plain carriage return character
        result = AT_CMD_LOCAL;
        if (cmd_buffer[2] == 'r') {
            // AT command follow by r specifier
            result = AT_CMD_REMOTE;
        }
    } else if (cmd_buffer[0] == '|') {
        result = AT_CMD_PIPE;
    } else {
        result = AT_CMD_UNDEFINED;
    }
    return result;
}


static bool str_ends_to(char* str_buff, char* str_ending)
{
    //detect if cmd_buffer ends in proper CMD_OK_TERMINATION_STRING
    size_t start_index = strlen(str_buff) - strlen(str_ending);

    return !strcmp(str_buff + start_index, str_ending);
}

bool validate_at_reply(char* reply_buffer)
{
    // Check this is not an at command.
    if (((reply_buffer[0] == 'A') && (reply_buffer[1] == 'T')) || (reply_buffer[0] == '|')) {
        return false;
    }

    if (str_ends_to(reply_buffer, OK_TERMINATION_STRING)) {
        return true;
    } else if (str_ends_to(reply_buffer, ERROR_TERMINATION_STRING)) {
        return true;
    } else {
        return false;
    }
}

/// Returns true if the received command matches cmd_tag and if the number of
/// arguments cmd_arg_count is between min_args and max_args
static bool user_verify_at_cmd(const char* cmd_tag, uint8_t min_args, uint8_t max_args, char* cmd_rx_tag,
                               uint8_t cmd_arg_count, uint8_t cmd_tag_length,
                               uint8_t cmd_rx_tag_length)
{
    bool result = false;
    if ((cmd_arg_count >= min_args) && (cmd_arg_count <= max_args)) {
        if (cmd_tag_length == cmd_rx_tag_length) {
            // check character by character if command tag received is the same with command tag id
            result = !memcmp(cmd_rx_tag, cmd_tag, cmd_tag_length);
        }
    }
    return (result);
}

AT_COMMAND_ID_t get_at_command_id(struct at_cmd_params_t* arguments)
{
    char* cmd_tag_buffer = arguments->cmd_buffer + arguments->cmd_tag_index;
    AT_COMMAND_ID_t at_command_index = AT_INVALID;

    for (size_t cmd_index = 0; cmd_index < AT_LAST_VALUE - 1; cmd_index++) {
        if (user_verify_at_cmd(at_commands_chars[cmd_index].command_tag_string,
                               at_commands_chars[cmd_index].command_min_arg_count,
                               at_commands_chars[cmd_index].command_max_arg_count, cmd_tag_buffer,
                               arguments->arg_count, strlen(at_commands_chars[cmd_index].command_tag_string),
                               arguments->command_tag_length)) {
            at_command_index = (AT_COMMAND_ID_t)cmd_index;
            break;
        }
    }
    return (at_command_index);
}

/// @} APP
