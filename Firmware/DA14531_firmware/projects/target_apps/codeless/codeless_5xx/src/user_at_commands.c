/**
 ****************************************************************************************
 *
 * @file user_at_commands.c
 *
 * @brief AT commands source file
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
#include <stdlib.h>
#include <ctype.h>

#include "user_at_commands.h"
#include "user_handlers.h"
#include "user_i2c.h"
#include "gpio.h"
#include "user_periph_setup.h"
#include "user_bonding_database.h"
#include "app_bond_db.h"
#include "adc.h"
#include "battery.h"
#include "arch_console.h"
#include "user_gap.h"
#include "user_utility_functions.h"
#include "user_cmd_parser.h"
#include "custs1_task.h"
#include "user_codeless_env.h"
#include "ke_mem.h"
#include "arch.h"
#include "arch_system.h"
#include "app_bond_db.h"
#include "user_gatt.h"
#include "uart.h"
#include "user_codeless.h"
#include "rwip.h"
#include "app_events_db.h"
#include "app_conpar_db.h"
#if defined(__DA14531__)
#include "rf_531.h"
#endif
#include "user_pwm.h"
#include "user_spi.h"
#include "user_security.h"
#include "user_heartbeat.h"
#include "user_baud.h"
#include "user_at_console.h"

/*
 * DEFINES
 ****************************************************************************************
 */
/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */
extern void user_advertise(void);
extern void user_codeless_set_default_gpio(void);
extern void user_prepare_sleep(void);

/// at commands jumptable.
const struct at_command_characteristics_t at_commands_chars[] = {
    AT_CMD_ENTRY( AT              ,  0,  0, ""             , user_at              ),
    AT_CMD_ENTRY( ATI             ,  0,  0, "I"            , user_ati             ),
    AT_CMD_ENTRY( ATE             ,  0,  1, "E"            , user_ate             ),
    AT_CMD_ENTRY( ATZ             ,  0,  0, "Z"            , user_atz             ),
    AT_CMD_ENTRY( ATR             ,  0,  0, "R"            , user_atr             ),
    AT_CMD_ENTRY( ATF             ,  1,  1, "F"            , user_atf             ),
#ifdef USE_AT_CURSOR
    AT_CMD_ENTRY( AT_CURSOR       ,  0,  0, "CURSOR"       , user_at_cursor       ),
#endif
#ifdef USE_AT_BDADDR
    AT_CMD_ENTRY( AT_BDADDR       ,  0,  0, "BDADDR"       , user_at_bdaddr       ),
#endif
#ifdef USE_AT_MEM
    AT_CMD_ENTRY( AT_MEM          ,  1,  2, "MEM"          , user_at_mem          ),
#endif
#ifdef USE_AT_CMD
    AT_CMD_ENTRY( AT_CMDSTORE     ,  2,  2, "CMDSTORE"     , user_at_cmdstore     ),
    AT_CMD_ENTRY( AT_CMDPLAY      ,  1,  1, "CMDPLAY"      , user_at_cmdplay      ),
    AT_CMD_ENTRY( AT_CMD          ,  1,  1, "CMD"          , user_at_cmd          ),
    AT_CMD_ENTRY( AT_TMRSTART     ,  3,  3, "TMRSTART"     , user_at_tmrstart     ),
    AT_CMD_ENTRY( AT_TMRSTOP      ,  1,  1, "TMRSTOP"      , user_at_tmrstop      ),
#endif
#ifdef USE_AT_SLEEP
    AT_CMD_ENTRY( AT_SLEEP        ,  1,  1, "SLEEP"        , user_at_sleep        ),
#endif
#ifdef USE_AT_IO
    AT_CMD_ENTRY( AT_IOCFG        ,  0,  3, "IOCFG"        , user_at_iocfg        ),
    AT_CMD_ENTRY( AT_IO           ,  1,  2, "IO"           , user_at_io           ),
#endif
#ifdef USE_AT_ADC
    AT_CMD_ENTRY( AT_ADC          ,  1,  1, "ADC"          , user_at_adc          ),
#endif
#ifdef USE_AT_BATT
    AT_CMD_ENTRY( AT_BATT         ,  0,  0, "BATT"         , user_at_batt         ),
#endif
#ifdef USE_AT_I2C
    AT_CMD_ENTRY( AT_I2CSCAN      ,  0,  0, "I2CSCAN"      , user_at_i2cscan      ),
    AT_CMD_ENTRY( AT_I2CCFG       ,  3,  3, "I2CCFG"       , user_at_i2ccfg       ),
    AT_CMD_ENTRY( AT_I2CREAD      ,  2,  3, "I2CREAD"      , user_at_i2cread      ),
    AT_CMD_ENTRY( AT_I2CWRITE     ,  3,  3, "I2CWRITE"     , user_at_i2cwrite     ),
#endif
#ifdef USE_AT_PRINT
    AT_CMD_ENTRY( AT_PRINT        ,  1,  1, "PRINT"        , user_at_print        ),
#endif
#ifdef USE_AT_GAPSTATUS
    AT_CMD_ENTRY( AT_GAPSTATUS    ,  0,  0, "GAPSTATUS"    , user_at_gapstatus    ),
#endif
#ifdef USE_AT_ADVDATA
    AT_CMD_ENTRY( AT_ADVDATA_SET  ,  1,  1, "ADVDATA"      , user_at_advdata_set  ),
    AT_CMD_ENTRY( AT_ADVDATA_GET  ,  0,  0, "ADVDATA"      , user_at_advdata_get  ),
#endif
#ifdef USE_AT_ADVRESP
    AT_CMD_ENTRY( AT_ADVRESP_SET  ,  1,  1, "ADVRESP"      , user_at_advresp_set  ),
    AT_CMD_ENTRY( AT_ADVRESP_GET  ,  0,  0, "ADVRESP"      , user_at_advresp_get  ),
#endif
#ifdef USE_AT_ADVSTOP
    AT_CMD_ENTRY( AT_ADVSTOP      ,  0,  0, "ADVSTOP"      , user_at_advstop      ),
#endif
#ifdef USE_AT_ADVSTART
    AT_CMD_ENTRY( AT_ADVSTART     ,  0,  1, "ADVSTART"     , user_at_advstart     ),
#endif
#ifdef USE_AT_CENTRAL
    AT_CMD_ENTRY( AT_CENTRAL      ,  0,  0, "CENTRAL"      , user_at_central      ),
#endif
#ifdef USE_AT_PERIPHERAL
    AT_CMD_ENTRY( AT_PERIPHERAL   ,  0,  0, "PERIPHERAL"   , user_at_peripheral   ),
#endif
#ifdef USE_AT_BROADCASTER
    AT_CMD_ENTRY( AT_BROADCASTER  ,  0,  0, "BROADCASTER"  , user_at_broadcaster  ),
#endif
#ifdef USE_AT_GAPSCAN
    AT_CMD_ENTRY( AT_GAPSCAN      ,  0,  0, "GAPSCAN"      , user_at_gapscan      ),
#endif
#ifdef USE_AT_GAPCONNECT
#if !defined(__DA14531_01__)
    AT_CMD_ENTRY( AT_GAPCONNECT   ,  2,  2, "GAPCONNECT"   , user_at_gapconnect   ),
#endif
    AT_CMD_ENTRY( AT_GAPDISCONNECT,  0,  0, "GAPDISCONNECT", user_at_gapdisconnect),
#endif
#ifdef USE_AT_RANDOM
    AT_CMD_ENTRY( AT_RANDOM       ,  0,  0, "RANDOM"       , user_at_random       ),
#endif
#ifdef USE_AT_PIN
    AT_CMD_ENTRY( AT_PIN          ,  1,  1, "PIN"          , user_at_pin          ),
#endif
#ifdef USE_AT_BND
    #if (BLE_APP_SEC)
    AT_CMD_ENTRY( AT_CLRBNDE      ,  1,  1, "CLRBNDE"      , user_at_clrbnde      ),
    AT_CMD_ENTRY( AT_CHGBNDP      ,  0,  2, "CHGBNDP"      , user_at_chgbndp      ),
    AT_CMD_ENTRY( AT_IEBNDE       ,  1,  2, "IEBNDE"       , user_at_iebnde       ),
    #endif
#endif
#ifdef USE_AT_HNDL
    AT_CMD_ENTRY( AT_HNDL         ,  0,  2, "HNDL"         , user_at_hndl         ),
#endif
#ifdef USE_AT_EVENT
    AT_CMD_ENTRY( AT_EVENT        ,  0,  2, "EVENT"        , user_at_event        ),
#endif
#ifdef USE_AT_BINARY_MODE
    AT_CMD_ENTRY( AT_BINREQ       ,  0,  0, "BINREQ"       , user_at_binreq       ),
    AT_CMD_ENTRY( AT_BINREQACK    ,  0,  0, "BINREQACK"    , user_at_binreqack    ),
    AT_CMD_ENTRY( AT_BINREQEXIT   ,  0,  0, "BINREQEXIT"   , user_at_binreqexit   ),
    AT_CMD_ENTRY( AT_BINESC       ,  0,  3, "BINESC"       , user_at_binesc       ),
    AT_CMD_ENTRY( AT_BINRESUME    ,  0,  0, "BINRESUME"    , user_at_binresume    ),
    AT_CMD_ENTRY( AT_BINREQEXITACK,  0,  0, "BINREQEXITACK", user_at_binreq       ),

#endif
#ifdef USE_AT_CONPAR
     AT_CMD_ENTRY( AT_CONPAR      ,  0,  4, "CONPAR"       , user_at_conpar       ),
#endif
#ifdef USE_AT_DLEEN
     AT_CMD_ENTRY( AT_DLEEN       ,  0,  3, "DLEEN"        , user_at_dleen        ),
#endif
#ifdef USE_AT_MAXMTU
     AT_CMD_ENTRY( AT_MAXMTU      ,  0,  1, "MAXMTU"       , user_at_maxmtu       ),
#endif
#ifdef USE_AT_FLOWCONTROL
     AT_CMD_ENTRY( AT_FLOWCONTROL ,  0,  3, "FLOWCONTROL"  , user_at_flowcontrol  ),
#endif
#ifdef USE_AT_HOSTSLP
    AT_CMD_ENTRY( AT_HOSTSLP      ,  0,  4, "HOSTSLP"      , user_at_hostslp      ),
#endif
#ifdef USE_AT_PWRLVL
    AT_CMD_ENTRY( AT_PWRLVL       ,  0,  1, "PWRLVL"       , user_at_pwrlvl       ),
#endif
#ifdef USE_AT_PWM
    AT_CMD_ENTRY( AT_PWM          ,  3,  3, "PWM"          , user_at_pwm          ),
#endif
#ifdef USE_AT_SPI
    AT_CMD_ENTRY( AT_SPICFG       ,  3,  3, "SPICFG"       , user_at_spi_conf     ),
    AT_CMD_ENTRY( AT_SPIWR        ,  1,  1, "SPIWR"        , user_at_spi_wr       ),
    AT_CMD_ENTRY( AT_SPIRD        ,  1,  1, "SPIRD"        , user_at_spi_rd       ),
    AT_CMD_ENTRY( AT_SPITR        ,  1,  1, "SPITR"        , user_at_spi_transfer ),
#endif
#ifdef USE_AT_RSSI
    AT_CMD_ENTRY( AT_RSSI         ,  0,  0, "RSSI"         , user_at_rssi         ),
#endif
#ifdef USE_AT_SEC
    AT_CMD_ENTRY( AT_SEC          ,  0,  1, "SEC"          ,  user_at_sec         ),
#endif
#ifdef USE_AT_HRTBT
    AT_CMD_ENTRY( AT_HRTBT        ,  0,  1, "HRTBT"        , user_at_hrtbt        ),
#endif
#ifdef USE_AT_BAUD
    AT_CMD_ENTRY( AT_BAUD         ,  0,  1, "BAUD"         , user_at_baud         ),
#endif
    AT_CMD_ENTRY( AT_INVALID      ,  0,  1, "XXX"          , user_at_invalid      )
};

#if defined(USE_AT_CMD) || defined(USE_AT_HNDL) || (defined(CFG_DATAPMP) && defined(CFG_ENTER_BINARY_MODE_ON_CONNECTION))

bool is_string_null_or_empty(const char* const string)
{
    if (string==NULL)
    {
        return true;
    }
    // Ensure that the string does not contain only spaces
    for (int i=0;i<strlen(string);i++)
    {
        if (!isspace(string[i]))
        {
            return false;
        }
    }
    return true;
}

/// command sequencer
#if defined(CFG_DATAPMP) && defined(CFG_ENTER_BINARY_MODE_ON_CONNECTION)
void user_execute_commands(char* cmd, enum CMD_SRC src)
#else
static void user_execute_commands(char* cmd, enum CMD_SRC src)
#endif
{
    // Iterate through the command string,
    // Every time a command separator is found,
    // Replace with null character and send APP message
    uint8_t prev_command_index = 0;
    size_t len = strlen(cmd) + 1;
    for (size_t i = 0; i < len; i++)
    {
        /* code */
        if ((cmd[i] == ';') || (cmd[i] == 0x00))
        {
            /*
            A command has been found. Any leading or trailing spaces will result in an error.
            Therefore they must be removed.
            */
            uint8_t actual_cmd_start_pos = prev_command_index;
            while (isspace(cmd[actual_cmd_start_pos]))
            {
                actual_cmd_start_pos++;
            }
            uint8_t actual_cmd_end_pos = i-1; // This is the position of the last character of the command
            while (isspace(cmd[actual_cmd_end_pos]))
            {
                actual_cmd_end_pos--;
            }

            uint8_t current_cmd_length = actual_cmd_end_pos - actual_cmd_start_pos + 1 + 1; //+1 for null termination
            //end of command
            //send message to task app
            struct user_app_cmd_received* at_cmd_msg = KE_MSG_ALLOC_DYN(USER_APP_CMD_RECEIVED,
                                                                        TASK_APP, TASK_APP,
                                                                        user_app_cmd_received,
                                                                        current_cmd_length);
            at_cmd_msg->bytes = current_cmd_length;
            at_cmd_msg->cmd_source = src;
            // zero out allocated memory
            memset(at_cmd_msg->cmd_buffer, 0, current_cmd_length);
            //copy current command to message data payload. -1 in order to not copy the ; character
            memcpy(at_cmd_msg->cmd_buffer, cmd + actual_cmd_start_pos, current_cmd_length - 1);
            KE_MSG_SEND(at_cmd_msg);
            // store current command index as previous.
            prev_command_index = i + 1;
        }
    }
}
#endif

#ifdef USE_AT_HNDL
void user_execute_event_handler_commands(char * cmd)
{
    user_execute_commands(cmd,CMD_SRC_HNDL);
}
#endif

#ifdef USE_AT_CMD

static uint8_t slot __SECTION_ZERO("retention_mem_area0");
static void set_slot(uint8_t i)
{
    slot = i;
}
// Following throw commands are callback functions to the 4 user timers and execute command strings
// saved to the respective user_at_memcmd buffer.
static void throw_command(void)
{
    if (codeless_env.command_slot[slot] != NULL) {
        user_execute_commands(codeless_env.command_slot[slot], CMD_SRC_SEQ);
    }
    codeless_env.tmr[0] = EASY_TIMER_INVALID_TIMER;
}
#endif//USE_AT_CMD

void user_at(struct at_cmd_params_t* arg, char* reply_string)
{
    #ifdef USE_AT_BINARY_MODE
    /* Is this an AT as an acknowledge to exit sequence? */
    if(codeless_env.wait_esc_ack_from_host==true)
    {
        /*In case that we wait an AT to exit binary mode */
        codeless_env.wait_esc_ack_from_host=false;
        app_easy_timer_cancel(codeless_env.host_guard_time_timer1);

        /* if the exit from binary mode is due to disconnection print this */
        if(codeless_env.disconnection_event)
        {
            codeless_env.disconnection_event=false;
            user_print_disconnection_string();
            codeless_env.gap_activity = IDLE;
        }
    }
    #endif
    #ifdef USE_AT_HOSTSLP
    if(codeless_env.hst_sleep_mode==1)
    {
        app_easy_timer_cancel(codeless_env.host_wakeup_attemt_timer);
        codeless_env.hst_sleep_mode=0;
    }
    #endif
    arg->success_flag = true;
}
#include "user_custs1_def_585.h"
#include "user_custs_sps.h"
void user_ati(struct at_cmd_params_t* arg, char* reply_string)
{
    //user_send_remote_notification(CUST1_SPSS_IDX_FLOW_CONTROL_VAL, FLOW_OFF, 0, 1);
    arch_sprintf(reply_string, CODELESS_INFO_STRING);
    arg->success_flag = true;
}

static char *user_get_argument(struct at_cmd_params_t* arg, uint8_t index)
{
    return &arg->cmd_buffer[arg->arg_index[index]];
}

static uint32_t user_get_argument_value(struct at_cmd_params_t* arg, uint8_t index)
{
    return (uint32_t)((uint16_t)ahtoi(user_get_argument(arg, index)));
}

void user_ate(struct at_cmd_params_t* arg, char* reply_string)
{
    const char *string = NULL;
    if (arg->arg_count == 0)
    {
        arch_sprintf(reply_string,"%d",console_env.echo);
    }
    else
    {
        uint8_t index = user_get_argument_value(arg, 0);
        if (index == 0)
        {
            console_env.echo = false;
            string = ECHO_OFF_STRING;

        }
        else
        {
            console_env.echo = true;
            string = ECHO_ON_STRING;
        }
        if(arg->cmd_source==CMD_SRC_REMOTE)
        {
            send_to_local(string);
        }
    }
    arg->success_flag = true;
}

void user_atz(struct at_cmd_params_t* arg, char* reply_string)
{
    user_codeless_set_default_gpio();
    #ifdef USE_AT_HRTBT
        stop_heart_beat();
    #endif
    arg->success_flag = true;
}

void user_atr(struct at_cmd_params_t* arg, char* reply_string)
{
#ifdef CODELESS_585
    platform_reset(RESET_AFTER_SUOTA_UPDATE);
#endif
}

void user_atf(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t index = user_get_argument_value(arg, 0);
    if (index == 0) {
        console_env.error_report_flag = false;
    } else {
        console_env.error_report_flag = true;
    }
    arg->success_flag = true;
}

#ifdef USE_AT_CURSOR
void user_at_cursor(struct at_cmd_params_t* arg, char* reply_string)
{
    if (DEVELOPMENT_DEBUG) {
        // During debugging we can use this function
        arch_set_pxact_gpio();
    } else {
        // When debugging is disabled, we can set the cursor as follows:
        uint32_t i;
        SetWord16(P13_MODE_REG, PID_GPIO | OUTPUT);
        SetWord16(P1_SET_DATA_REG, 0x8);
        for (i = 0; i < 150; i++) {
            ;
        }
        SetWord16(P1_RESET_DATA_REG, 0x8);
    }
    arg->success_flag = true;
}
#endif

#ifdef USE_AT_BDADDR
void user_at_bdaddr(struct at_cmd_params_t* arg, char* reply_string)
{

    uint32_t bdaddr_msb = (GetWord32(BLE_BDADDRU_REG))&0x1FFFF;
    uint32_t bdaddr_lsb = (GetWord32(BLE_BDADDRL_REG));
    uint8_t addr[6];
    memcpy(&addr, &bdaddr_lsb, 4);
    memcpy(&addr[4], &bdaddr_msb, 2);

    uint8_t n=0;
    for (int i = 5;i >= 0;i--)
    {
        arch_sprintf(reply_string+n,"%02X:",addr[i]);
        n=strlen(reply_string);
    }
    n--; // The last : is not needed
    // Public or Random adress
    if ((bdaddr_msb >> 16) > 0)
    {
        strcpy(reply_string+n,",R");
    }
    else
    {
        strcpy(reply_string+n,",P");
    }
    arg->success_flag = true;
}
#endif

#ifdef USE_AT_MEM
void user_at_mem(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t index = user_get_argument_value(arg, 0);
    // check for valid slot number
    if (index < USER_MEMORY_SLOT_NUMBER) {
        if (arg->arg_count == 1) {
            // Display string saved to requested memory slot.
            if (codeless_env.memory_slot[index] != NULL) {
                arch_sprintf(reply_string, "%s", codeless_env.memory_slot[index]);
            }
            arg->success_flag = true;
        } else {
            // check for valid requested mem length
            if (arg->arg_length[1] <= USER_MEMORY_LENGTH) {

                // if memory slot has been previously allocated, should be freed first.
                if (codeless_env.memory_slot[index] != NULL) {
                    ke_free(codeless_env.memory_slot[index]);
                }
                if (user_malloc(&codeless_env.memory_slot[index], arg->arg_length[1] + 1, KE_MEM_ENV)) {
                    memset(codeless_env.memory_slot[index], 0, arg->arg_length[1] + 1);
                    memcpy(codeless_env.memory_slot[index], user_get_argument(arg, 1),
                           arg->arg_length[1]);
                    arg->success_flag = true;
                } else {
                    codeless_env.memory_slot[index] = NULL;
                    arg->error_status = AT_CONSOLE_ERROR_8; // Could not allocate memory
                }
            } else {
                arg->error_status = AT_CONSOLE_ERROR_9; // mem length longer than max
            }
        }
    } else {
        arg->error_status = AT_CONSOLE_ERROR_10; // mem slot invalid
    }
}
#endif

#ifdef USE_AT_CMD
void user_at_cmdstore(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t index = user_get_argument_value(arg, 0);

    // check that a valid slot number is requested
    if (index < USER_MEMCMD_SLOT_NUMBER) {
        // check that memcmd size is not larger than allowed
        if (arg->arg_length[1] <= USER_MEMCMD_LENGTH) {

            // if memory slot has been previously allocated, should be freed first.
            if (codeless_env.command_slot[index] != NULL) {
                ke_free(codeless_env.command_slot[index]);
            }
            if (user_malloc(&codeless_env.command_slot[index], arg->arg_length[1] + 1, KE_MEM_ENV)){
                memset(codeless_env.command_slot[index], 0, arg->arg_length[1] + 1);
                memcpy(codeless_env.command_slot[index], user_get_argument(arg, 1),
                       arg->arg_length[1]);
                arg->success_flag = true;
            } else {
                codeless_env.command_slot[index] = NULL;
                arg->error_status = AT_CONSOLE_ERROR_8; // Could not allocate memory
            }
        }
        else{
            arg->error_status = AT_CONSOLE_ERROR_9;//memcmd length longer than max
        }
    }
    else {
        arg->error_status = AT_CONSOLE_ERROR_10;//memcmd slot invalid
    }
}

void user_at_cmdplay(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t index = user_get_argument_value(arg, 0);

    if (index < USER_MEMCMD_SLOT_NUMBER) {
        if (codeless_env.command_slot[index] != NULL) {
            user_execute_commands(codeless_env.command_slot[index],CMD_SRC_SEQ);
            arg->success_flag = true;
        }
    }
    else {
        arg->error_status = AT_CONSOLE_ERROR_10;//memcmd slot invalid
    }
}

void user_at_cmd(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t index = user_get_argument_value(arg, 0);
    if (index < USER_MEMCMD_SLOT_NUMBER) {
        if (codeless_env.command_slot[index] != NULL) {
            arch_sprintf(reply_string, "%s", codeless_env.command_slot[index]);
        }
        arg->success_flag = true;
    }
    else{
        arg->error_status = AT_CONSOLE_ERROR_10;//memcmd slot invalid
    }
}

void user_at_tmrstart(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t timer_id = user_get_argument_value(arg, 0);
    uint8_t cmd_slot = user_get_argument_value(arg, 1);
    uint32_t delay = user_get_argument_value(arg, 2);

    if ((delay > 0) && (delay < KE_TIMER_DELAY_MAX)) {
        if (timer_id < 4) {
            if (cmd_slot < USER_MEMCMD_SLOT_NUMBER)
            {
                arg->success_flag = true;
                set_slot(cmd_slot);
                codeless_env.tmr[timer_id] = app_easy_timer(delay, throw_command);
            } else {
                arg->error_status = AT_CONSOLE_ERROR_10; // Invalid command slot
            }
        } else{
            arg->error_status = AT_CONSOLE_ERROR_11; // Invalid timer id
        }
    }
    else{
        arg->error_status = AT_CONSOLE_ERROR_13; // at command argument out of range
    }
}

void user_at_tmrstop(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t timer_id = user_get_argument_value(arg, 0);
    if (timer_id < 4) {
        // check if valid timer handle
        if (codeless_env.tmr[timer_id] != EASY_TIMER_INVALID_TIMER) {
            app_easy_timer_cancel(codeless_env.tmr[timer_id]);
            codeless_env.tmr[timer_id] = EASY_TIMER_INVALID_TIMER;
        }
        arg->success_flag = true;
    } else {
        arg->error_status = AT_CONSOLE_ERROR_11; // Invalid timer id
    }
}
#endif

#ifdef USE_AT_SLEEP
void user_at_sleep(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t index = user_get_argument_value(arg, 0);
    if (index == 0) {
       // arch_disable_sleep();
        //user_wakeup();
        codeless_env.sleep_active=0;
        codeless_env.user_allow_to_go_to_sleep_flag = false;
    } else {
        codeless_env.user_allow_to_go_to_sleep_flag = true;
        codeless_env.sleep_active=1;
        user_prepare_sleep();
    }
    arg->success_flag = true;
}
#endif

#ifdef USE_AT_IO

bool is_spi_flash_port(uint8_t port)
{
    #if defined (CFG_SPI_FLASH_ENABLE)
        // For DA14531 pin assignment is direct - port is always zero
        if ((port==SPI_EN_GPIO_PORT * 10 + SPI_EN_GPIO_PIN)  ||
            (port==SPI_CLK_GPIO_PORT * 10 +SPI_CLK_GPIO_PIN) ||
            (port==SPI_DO_GPIO_PORT * 10 + SPI_DO_GPIO_PIN)  ||
            (port==SPI_DI_GPIO_PORT * 10 +SPI_DI_GPIO_PIN))
        {
            return true;
        }
        else
        {
            return false;
        }
    #else
        return false;
    #endif
}

bool is_debugger_port(uint8_t port)
{
    // If the debugger is enabled,the pins used for the debugger cannot be used for other purposes
#if defined(__DA14531__)
    bool is_swclk = false;
    bool is_swd = false;
    do
    {
        uint16_t dbg_conf = GetBits16(SYS_CTRL_REG, DEBUGGER_ENABLE);
        if (dbg_conf == NO_SWD)
        {
            break;
        }
        else
        {
            if ((GPIO_PIN)port == GPIO_PIN_2)
            {
                is_swclk = true;
                break;
            }
            else
            {
                switch (dbg_conf)
                {
                    case SWD_DATA_AT_P0_5:
                        is_swd = ((GPIO_PIN)port == GPIO_PIN_5) ? true:false;
                    break;
                    case SWD_DATA_AT_P0_1:
                        is_swd = ((GPIO_PIN)port == GPIO_PIN_1) ? true:false;
                    break;
                    case SWD_DATA_AT_P0_10:
                        is_swd = ((GPIO_PIN)port == GPIO_PIN_10) ? true:false;
                    break;
                }
            }
        }
    }
    while (0);
    return (is_swclk||is_swd);
#else
    bool return_value = false;
    uint16_t dbg_conf = GetBits16(SYS_CTRL_REG, DEBUGGER_ENABLE);
    if (dbg_conf != 0)
    {
        // Debugger is enabled.If the debugger pins are requested return true
        if ((port == GPIO_PORT_1 * 10 + GPIO_PIN_4) ||
            (port == GPIO_PORT_1 * 10 + GPIO_PIN_5))
        {
            return_value = true;
        }
    }
    return return_value;
#endif
}

void user_at_iocfg(struct at_cmd_params_t* arg, char* reply_string) // TODO: This function is too large. Certain parts must be removed
{
    bool port_cfg_failed = false;

    if (arg->arg_count != 1) {
        if (arg->arg_count == 0) {
            // List all IO configuration settings
            for (uint8_t i = 0; i < MAX_PIN_NUMBER; i++) {
                if (codeless_env.port_configuration[i] != IO_FUNC_NOT_AVAILABLE) {
                    arch_sprintf(reply_string, "%s%02d ", reply_string,
                                 (uint8_t)codeless_env.port_configuration[i]);
                }
            }
            arg->success_flag = true;
        } else // arg_count > 2
        {
            uint8_t port = user_get_argument_value(arg, 0);
            uint8_t func = user_get_argument_value(arg, 1);

            if (!((arg->arg_count == 3) && (func != IO_FUNC_OUTPUT))) {

                // Validate port and functionality
                if ((codeless_env.port_configuration[port] != IO_FUNC_NOT_AVAILABLE) && (port < MAX_PIN_NUMBER)
                    && ((io_func_t)func < IO_FUNC_NOT_AVAILABLE)
                    && (port != UARTx_TX_GPIO_PORT * 10 + UARTx_TX_GPIO_PIN)
                    && (port != UARTx_RX_GPIO_PORT * 10 + UARTx_RX_GPIO_PIN)
                    && (! is_spi_flash_port(port)) && (! is_debugger_port(port))) {

                    // Resolve port and pin numbers from argument
                    #if  defined(__DA14585__) || defined(__DA14586__)
                    uint8_t port_number = port / 10;
                    uint8_t pin_number = port % 10;
                    #elif   defined(__DA14531__)
                    uint8_t port_number = 0;
                    uint8_t pin_number = port;
                    #endif
                    // Set port configuration accordingly
                    if ((func == IO_FUNC_INPUT) || (func == IO_FUNC_INPUT_PULLUP) || (func == IO_FUNC_INPUT_PULLDOWN)) {
                        // Standard input port
                        // Input port with pull-up resistor
                        // Input port with pull-down resistor
                        GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, (GPIO_PUPD)((func-1)*0x100),
                                          PID_GPIO, false);


                    } else if (func == IO_FUNC_OUTPUT) {
                        // Output port
                        bool pin_value = false;
                        if (arg->arg_count == 3) {
                            uint8_t data = user_get_argument_value(arg, 2);
                            if (data == 1) {
                                pin_value = true;
                            }
                        }
                        GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT,
                                          PID_GPIO, pin_value);
#if defined (USE_AT_ADC)
    #if defined (__DA14585__) || defined(__DA14585__)
                    } else if ((func == IO_FUNC_ANALOG_INPUT || func == IO_FUNC_ANALOG_INPUT_ATT3)
                               && (port_number == 0) && (pin_number <= 3)) {
                        // Analog input port
                        GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, INPUT,
                                          PID_ADC, false);
    #elif defined(__DA14531__)
                    } else if ((func == IO_FUNC_ANALOG_INPUT || func == IO_FUNC_ANALOG_INPUT_ATT3) &&
                               (port_number == 0) &&
                               (pin_number == 1 || pin_number == 2 || pin_number==6 || pin_number==7))  {
                        // Analog input port
                        GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, INPUT,
                                          PID_ADC, false);
    #endif
#endif
#if defined (USE_AT_I2C)
                    } else if (func == IO_FUNC_I2C_CLOCK) {
                        // Remove any existing I2C clock pins
                        /*
                        for (uint8_t i = 0; i < MAX_PIN_NUMBER; i++) {
                            if (codeless_env.port_configuration[i] == IO_FUNC_I2C_CLOCK) {
                                codeless_env.port_configuration[i] = IO_FUNC_UNDEFINED;
                            }
                        }
                        */
                        user_assign_pin(port, IO_FUNC_I2C_CLOCK);
                        // I2C clock output port
                        GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT,
                                          PID_I2C_SCL, false);
                    } else if (func == IO_FUNC_I2C_DATA) {
                        // Remove any existing I2C data pins
                        /*
                        for (uint8_t i = 0; i < MAX_PIN_NUMBER; i++) {
                            if (codeless_env.port_configuration[i] == IO_FUNC_I2C_DATA) {
                                codeless_env.port_configuration[i] = IO_FUNC_UNDEFINED;
                            }
                        }*/
                        user_assign_pin(port, IO_FUNC_I2C_DATA);
                        // I2C data port
                        GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT,
                                          PID_I2C_SDA, false);
#endif
                    } else if ((func == IO_FUNC_CONN_IND_HI) || (func == IO_FUNC_CONN_IND_LO)) {
                        // Connection indicator, high during a connection
                        // The assinment is not needed here because it will take place at the end
                        // codeless_env.port_configuration[port] = func;

                        bool is_high = (func == IO_FUNC_CONN_IND_HI);
                        if (is_connected()) {
                            GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT,
                                              PID_GPIO, is_high);
                        } else {
                            GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT,
                                              PID_GPIO, !is_high);
                        }
/*
                    } else if (func == IO_FUNC_CONN_IND_LO) {
                        // Connection indicator, low during a connection
                        codeless_env.port_configuration[port] = IO_FUNC_CONN_IND_LO;
                        if (is_connected()) {
                            GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT,
                                              PID_GPIO, false);
                        } else {
                            GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT,
                                              PID_GPIO, true);
                        }
*/
#if defined (USE_AT_PWM)
                    } else if (func == IO_FUNC_PWM2) {
                        // PWM port
                        codeless_env.port_configuration[port] = IO_FUNC_PWM2;
                        GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT, PID_PWM2, true);
#endif
#if defined (USE_AT_SPI)
                    } else if (func == IO_FUNC_SPI_CLK) {
                        // Remove any existing SPI Clock  pins
                        user_assign_pin(port, IO_FUNC_SPI_CLK);
                        // Configure SPI clock pin
                        GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT,
                                          PID_SPI_CLK, false);
                    } else if (func == IO_FUNC_SPI_CS) {
                        // Remove any existing SPI CS  pins
                        user_assign_pin(port, IO_FUNC_SPI_CS);
                        // Condigure SPI CS/EN pin
                        GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT,
                                          PID_SPI_EN, true);
                    } else if (func == IO_FUNC_SPI_MOSI) {
                        // Remove any existing SPI MOSI pins
                        user_assign_pin(port,IO_FUNC_SPI_MOSI);

                        // Configure SPI MOSI pin
                        GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT,
                                          PID_SPI_DO, false);

                    } else if (func == IO_FUNC_SPI_MISO) {
                        // Remove any existing SPI MISO pins
                        user_assign_pin(port, IO_FUNC_SPI_MISO);
                        // Configure SPI MISO pin
                        GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, INPUT,
                                          PID_SPI_DI, false);
#endif
#if defined (USE_AT_HRTBT)
                    }
                    else if (func == IO_FUNC_HRTBT)
                    {
                        user_assign_pin(port,IO_FUNC_HRTBT);
                        set_heart_beat_pin_port_cfg((GPIO_PORT)port_number, (GPIO_PIN)pin_number);
                        GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT, PID_GPIO, true);
#endif
                    } else {
                        port_cfg_failed = true;
                    }

                    if (!port_cfg_failed) {
                        codeless_env.port_configuration[port] = (io_func_t)func;
                        arg->success_flag = true;
                    }

                } else {
                    arg->error_status = AT_CONSOLE_ERROR_12; // Invalid gpio function requested
                }
            } // arg count ==3 && func != output
        } // arg count ==2
    } // arg count !=1
}

void user_at_io(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t port = user_get_argument_value(arg, 0);

    #if   defined(__DA14585__) || defined(__DA14586__)
    uint8_t port_number = port / 10;
    uint8_t pin_number = port % 10;
    #elif   defined(__DA14531__)
    uint8_t port_number = 0;
    uint8_t pin_number = port;
    #endif

    if(port > MAX_PIN_NUMBER)
    {
         arg->success_flag = false;
         return;
    }

    if (arg->arg_count == 1) {
        // Read (one argument means 'read')

        // Pin must be configured as input or output for read operation to work
        if ((codeless_env.port_configuration[port] == IO_FUNC_INPUT)
            || (codeless_env.port_configuration[port] == IO_FUNC_INPUT_PULLUP)
            || (codeless_env.port_configuration[port] == IO_FUNC_INPUT_PULLDOWN)
            || (codeless_env.port_configuration[port] == IO_FUNC_OUTPUT)

        ) {

            arch_sprintf(reply_string, "%d", (int)GPIO_GetPinStatus((GPIO_PORT)port_number, (GPIO_PIN)pin_number));
            arg->success_flag = true;
        }
    }

    else //  arg_count = 2
    {
        uint8_t data = user_get_argument_value(arg, 1);
        // Pin must be configured as output and data must be 0 or 1
        if ((codeless_env.port_configuration[port] == IO_FUNC_OUTPUT) && (data == 0 || data == 1)) {
            if (data == 0) {
                GPIO_SetInactive((GPIO_PORT)port_number, (GPIO_PIN)pin_number);
                codeless_env.port_io_state[port] = false;
            } else {
                GPIO_SetActive((GPIO_PORT)port_number, (GPIO_PIN)pin_number);
                codeless_env.port_io_state[port] = true;
            }
            arg->success_flag = true;
        }
    }
}
#endif

#ifdef USE_AT_ADC

#if defined(__DA14531__)
adc_input_se_t get_adc_input_se_t_from_531_pin(uint8_t pin)
{
    adc_input_se_t input=ADC_INPUT_SE_P0_2; //default value
    switch(pin)
    {
        case 1:
            input=ADC_INPUT_SE_P0_1;
        break;
        case 2:
            input=ADC_INPUT_SE_P0_2;
        break;
        case 6:
            input=ADC_INPUT_SE_P0_6;
        break;
        case 7:
            input=ADC_INPUT_SE_P0_7;
        break;
    }
    return input;
}
#endif

void user_at_adc(struct at_cmd_params_t *arg, char *reply_string)
{
    uint8_t port = user_get_argument_value(arg, 0);

#if defined (__DA14585__) || defined(__DA14586__)
    if ((port < 4) && ((codeless_env.port_configuration[port] == IO_FUNC_ANALOG_INPUT_ATT3) ||
                       (codeless_env.port_configuration[port] == IO_FUNC_ANALOG_INPUT)))
#elif defined(__DA14531__)
    if ((port == 1||port==2 || port==6 || port==7) &&
        ((codeless_env.port_configuration[port] == IO_FUNC_ANALOG_INPUT_ATT3) ||
         (codeless_env.port_configuration[port] == IO_FUNC_ANALOG_INPUT)))
#else
    #error No configuration defined
#endif
    {
        // Use 1:3 attenuation if applicable
        if (codeless_env.port_configuration[port] == IO_FUNC_ANALOG_INPUT)
        {
            #if  defined(__DA14531__)
            #if !defined(ADC_OPT)
            const adc_config_t cfg=
            {
                .input_mode=ADC_INPUT_MODE_SINGLE_ENDED,
                .input=get_adc_input_se_t_from_531_pin(port),
                .smpl_time_mult=0,
                .continuous=0,
                .interval_mult=0,
                .input_attenuator=ADC_INPUT_ATTN_NO,
                .chopping=0,
                .oversampling=0
            };
            #else
            const adc_config_t cfg =
            {
                .adc_cfg.b.input_mode=ADC_INPUT_MODE_SINGLE_ENDED,
                .adc_cfg.b.input=get_adc_input_se_t_from_531_pin(port),
                .adc_cfg.b.smpl_time_mult=0,
                .adc_cfg.b.continuous=0,
                .adc_cfg.b.interval_mult=0,
                .adc_cfg.b.input_attenuator=ADC_INPUT_ATTN_NO,
                .adc_cfg.b.chopping=0,
                .adc_cfg.b.oversampling=0
            };
            #endif
            #else
            const adc_config_t cfg=
            {
                .mode=ADC_INPUT_MODE_SINGLE_ENDED,
                .input=port,
                .sign=false,
                .attn=false
            };
            #endif
            adc_init(&cfg);
        }
        else
        {
            #if  defined(__DA14531__)
            #if !defined(ADC_OPT)
            const adc_config_t cfg_with_attn=
            {
                .input_mode=ADC_INPUT_MODE_SINGLE_ENDED,
                .input=get_adc_input_se_t_from_531_pin(port),
                .smpl_time_mult=2,
                .continuous=false,
                .interval_mult=0,
                .input_attenuator=ADC_INPUT_ATTN_4X,
                .chopping=false,
                .oversampling=0
            };
            #else
            const adc_config_t cfg_with_attn=
            {
                .adc_cfg.b.input_mode=ADC_INPUT_MODE_SINGLE_ENDED,
                .adc_cfg.b.input=get_adc_input_se_t_from_531_pin(port),
                .adc_cfg.b.smpl_time_mult=2,
                .adc_cfg.b.continuous=false,
                .adc_cfg.b.interval_mult=0,
                .adc_cfg.b.input_attenuator=(adc_input_attn_t)ADC_INPUT_ATTN_4X,
                .adc_cfg.b.chopping=false,
                .adc_cfg.b.oversampling=0
            };
            #endif
             adc_offset_calibrate(ADC_INPUT_MODE_SINGLE_ENDED);
            #else
                const adc_config_t cfg_with_attn=
                {
                    .mode=ADC_INPUT_MODE_SINGLE_ENDED,
                    .input=port,
                    .sign=false,
                    .attn=true
                };
            #endif
            adc_init(&cfg_with_attn);
        }
        uint16_t adc_sample=0;
        adc_enable();
        #if defined(__DA14585__) || defined(__DA14586__)
            // Open channel and take a dummy sample
            adc_sample=adc_get_sample();
        #elif defined(__DA14531__)
            adc_sample = adc_correct_sample(adc_get_sample());
        #else
            #error No configuration defined
        #endif
        // return the sample
        arch_sprintf(reply_string, "%d", adc_sample);
        // Disable the ADC
        adc_disable();
        arg->success_flag = true;
    }
    else
    {
        arg->error_status = AT_CONSOLE_ERROR_1;//ADC pins not properly set
    }
}
#endif

#ifdef USE_AT_BATT
void user_at_batt(struct at_cmd_params_t* arg, char* reply_string)
{
    // Read the battery capacity
    arch_sprintf(reply_string, "%d", battery_get_lvl(CODELESS_BATTERY_TYPE));
    arg->success_flag = true;
}
#endif

#ifdef USE_AT_I2C
void user_at_i2cscan(struct at_cmd_params_t* arg, char* reply_string)
{
    // Scan for I2C slaves only if hardware has been configured to support I2C
    if (user_is_i2c_hw_valid()) {
        user_i2c_scan(reply_string);
        arg->success_flag = true;
    } else {
        arg->error_status = AT_CONSOLE_ERROR_2;//I2C hw not properly set
    }
}

void user_at_i2ccfg(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t arg1 = user_get_argument_value(arg, 0);
    uint16_t arg2 = user_get_argument_value(arg, 1); // arg2 can take values up to 400 so
                                                                // it will not fit into a uint8
    uint8_t arg3 = user_get_argument_value(arg, 2);

    if (((arg1 == 7) || (arg1 == 10)) && ((arg2 == 100) || (arg2 == 400))
        && ((arg3 == 8) || (arg3 == 16))) {
        if (arg2 == 100) {
            user_i2c_config(arg1, 1, arg3);
        } else {
            user_i2c_config(arg1, 2, arg3);
        }
        arg->success_flag = true;
    } else {
        arg->error_status = AT_CONSOLE_ERROR_3;// I2C parameters specified are not valid.
    }
}

void user_at_i2cread(struct at_cmd_params_t* arg, char* reply_string)
{
    // If no third argument is provided, read 1 byte only
    uint8_t num_bytes = 1;

    if (arg->arg_count == 3) {
        num_bytes = user_get_argument_value(arg, 2);
    }
    // Check for valid hardware configuration
    if (user_is_i2c_hw_valid()) {
        uint8_t arg1 = user_get_argument_value(arg, 0);
        uint8_t arg2 = user_get_argument_value(arg, 1);

        if (user_i2c_read(arg1, arg2, num_bytes, reply_string)) {
            arg->success_flag = true;
        }
    } else {
        arg->error_status = AT_CONSOLE_ERROR_2; // I2C hw not properly set
    }
}

void user_at_i2cwrite(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t arg1 = user_get_argument_value(arg, 0);
    uint8_t arg2 = user_get_argument_value(arg, 1);
    uint8_t arg3 = user_get_argument_value(arg, 2);

    // Check for valid hardware configuration
    if (user_is_i2c_hw_valid()) {
        user_i2c_write(arg1, arg2, arg3);
        arg->success_flag = true;
    }
    else{
        arg->error_status = AT_CONSOLE_ERROR_2;//I2C hw not properly set
    }
}
#endif

#ifdef USE_AT_PRINT
void user_at_print(struct at_cmd_params_t* arg, char* reply_string)
{
    if(arg->cmd_source==CMD_SRC_REMOTE)
    {
        codeless_env.event_trigger=true;
        send_to_local("+PRINT:");
        send_to_local_no_CRLF(user_get_argument(arg, 0));
        send_to_local("");
    }
    else
    {
        send_to_local(user_get_argument(arg, 0));
    }
    arg->success_flag = true;
}
#endif

#ifdef USE_AT_GAPSTATUS
void user_at_gapstatus(struct at_cmd_params_t* arg, char* reply_string)
{
#ifdef CODELESS_585
#if !defined(__DA14531_01__)
    arch_sprintf(reply_string, "%d,%d", (codeless_env.bt_role == GAP_ROLE_CENTRAL),
                 is_connected());
#else
    // DA14531_01 cannot be central
    arch_sprintf(reply_string, "%d,%d", 0, is_connected());
#endif //__DA14531_01__
#endif
    arg->success_flag = true;
}
#endif

#ifdef USE_AT_ADVDATA
void user_at_advdata_set(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t byte_array[32];
    uint8_t len;
    bool arg_val = validate_adv_data(user_get_argument(arg, 0), byte_array, &len);

    if ((arg_val) && (len <= 28)) {
        memcpy(&codeless_env.adv_data, &byte_array, len);
        codeless_env.adv_data_len = len;
        arg->success_flag = true;
    }
    else{
        arg->error_status = AT_CONSOLE_ERROR_4;//Invalid advertise data
    }
}

void user_at_advdata_get(struct at_cmd_params_t* arg, char* reply_string)
{
    for (uint8_t i = 0; i < codeless_env.adv_data_len - 1; i++) {
        arch_sprintf(reply_string, "%s%02X:", reply_string, codeless_env.adv_data[i]);
    }
    arch_sprintf(reply_string, "%s%02X", reply_string,
                 codeless_env.adv_data[codeless_env.adv_data_len - 1]);

    arg->success_flag = true;
}
#endif

#ifdef USE_AT_ADVRESP
void user_at_advresp_set(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t byte_array[32];
    uint8_t len;
    bool arg_val = validate_adv_data(user_get_argument(arg, 0), byte_array, &len);

    if ((arg_val) && (len <= 31)) {
        memcpy(&codeless_env.resp_data, &byte_array, len);
        codeless_env.resp_data_len = len;
        arg->success_flag = true;
    }
    else{
        arg->error_status = AT_CONSOLE_ERROR_4;//Invalid advertise data
    }
}

void user_at_advresp_get(struct at_cmd_params_t* arg, char* reply_string)
{
    if (codeless_env.resp_data_len > 0)
    {
        uint8_t n=0;
        for (uint8_t i = 0; i < codeless_env.resp_data_len; i++)
        {
            arch_sprintf(reply_string+n,"%02X:",codeless_env.resp_data[i]);
            n=strlen(reply_string);
        }
        n--; // The last : is not needed
        reply_string[n]='\0'; // terminate string
    }
    arg->success_flag = true;
}
#endif

#ifdef USE_AT_ADVSTOP
void user_at_advstop(struct at_cmd_params_t* arg, char* reply_string)
{
#ifdef CODELESS_585
    if ((codeless_env.bt_role == GAP_ROLE_PERIPHERAL
         || codeless_env.bt_role == GAP_ROLE_BROADCASTER)
        && (codeless_env.gap_activity == ADVERTISING) && ((arg->cmd_source == CMD_SRC_LOCAL) || (arg->cmd_source == CMD_SRC_SEQ))
        && (!is_connected()))
#endif
    {
        app_easy_gap_advertise_stop();
        codeless_env.gap_activity = IDLE;
        // command succesfull but dont send reply for this command.
        arg->success_flag = true;
        arg->reply_flag = false;
    }
}
#endif

#ifdef USE_AT_ADVSTART
void user_at_advstart(struct at_cmd_params_t* arg, char* reply_string)
{
#ifdef CODELESS_585
    if ((codeless_env.bt_role == GAP_ROLE_PERIPHERAL || codeless_env.bt_role == GAP_ROLE_BROADCASTER)
        && (codeless_env.gap_activity == IDLE)
        && ((arg->cmd_source == CMD_SRC_LOCAL) || (arg->cmd_source == CMD_SRC_SEQ))
        && (!is_connected()) )
#endif
    {
        if (arg->arg_count == 1) {
            uint16_t intv = user_get_argument_value(arg, 0);
            if (intv >= 100 && intv <= 3000) {
                // Set the advertising interval
                codeless_env.adv_intv = intv * 16/10;
            }
            else
            {
                arg->success_flag = false;
                return;
            }
        } else {
            codeless_env.adv_intv = user_adv_conf.intv_min;
        }
        // Try to start advertising
        user_advertise();
        // command succesfull but dont send reply for this command.
        arg->success_flag = true;
        //arg->reply_flag = false;
    }
}
#endif

#ifdef USE_AT_CENTRAL
void user_at_central(struct at_cmd_params_t* arg, char* reply_string)
{
#ifdef CODELESS_585
    if ((codeless_env.bt_role == GAP_ROLE_PERIPHERAL || codeless_env.bt_role == GAP_ROLE_BROADCASTER)
        && (codeless_env.gap_activity == IDLE) && (arg->cmd_source == CMD_SRC_LOCAL)
        && (!is_connected()))
#endif
    {
        codeless_env.is_connectable = false;
#ifdef CODELESS_585
        // Set central role
        user_app_configuration_func(GAP_ROLE_CENTRAL);
#endif
        // command succesfull but don't send reply for this command.
        arg->success_flag = true;
        arg->reply_flag = false;
    }
}
#endif

#ifdef USE_AT_PERIPHERAL
void user_at_peripheral(struct at_cmd_params_t* arg, char* reply_string)
{

#ifdef CODELESS_585
#if !defined(__DA14531_01__)
    if ((codeless_env.bt_role == GAP_ROLE_CENTRAL || codeless_env.bt_role == GAP_ROLE_BROADCASTER)
#else
    if ((codeless_env.bt_role == GAP_ROLE_BROADCASTER)
#endif
        && (codeless_env.gap_activity == IDLE) && (arg->cmd_source == CMD_SRC_LOCAL)
        && (!is_connected()))
#endif
    {
        codeless_env.is_connectable = true;
#ifdef CODELESS_585
        user_app_configuration_func(GAP_ROLE_PERIPHERAL);
#if defined(CFG_PRF_SUOTAR)
        extern void app_suotar_create_db(void);
        app_suotar_create_db();
#endif
        extern void app_custs1_create_db(void);
        app_custs1_create_db();
#endif
        // command succesfull but dont send reply for this command.
        arg->success_flag = true;
        arg->reply_flag = false;
    }
}
#endif

#ifdef USE_AT_BROADCASTER
void user_at_broadcaster(struct at_cmd_params_t* arg, char* reply_string)
{

#ifdef CODELESS_585
    if ((codeless_env.bt_role == GAP_ROLE_CENTRAL || codeless_env.bt_role == GAP_ROLE_PERIPHERAL)
        && (codeless_env.gap_activity == IDLE) && (arg->cmd_source == CMD_SRC_LOCAL)
        && (ke_state_get(TASK_APP) != APP_CONNECTED))
#endif
    {
        // Set broadcaster role
        codeless_env.is_connectable = false;
        user_app_configuration_func(GAP_ROLE_BROADCASTER);
        // command successful but dont send reply for this command
        arg->success_flag = true;
        arg->reply_flag = false;
    }
}
#endif

#ifdef USE_AT_GAPSCAN
void user_at_gapscan(struct at_cmd_params_t* arg, char* reply_string)
{

#ifdef CODELESS_585
    if ((codeless_env.bt_role == GAP_ROLE_CENTRAL) && (codeless_env.gap_activity == IDLE)
        && (arg->cmd_source == CMD_SRC_LOCAL) && (!is_connected()))
#endif
    {
        send_to_local(SCANNING_STRING);
        codeless_env.gap_activity = SCANNING;
        user_scan_start();
        // command successful but do not send reply for this command.
        arg->success_flag = true;
        arg->reply_flag = false;
    }
}
#endif

#ifdef USE_AT_GAPCONNECT
#if !defined(__DA14531_01__)
void gapconnect_timeout_callback(void)
{
    if (codeless_env.gap_activity == INITIATING_CONNECTION)
    {
        // Create a GAP activity cancel message
        struct gapm_cancel_cmd* cmd = app_gapm_cancel_msg_create();
        // Send the message
        app_gapm_cancel_msg_send(cmd);
    }
}


void user_at_gapconnect(struct at_cmd_params_t* arg, char* reply_string)
{
#if defined(CODELESS_585)
    if ((codeless_env.bt_role == GAP_ROLE_CENTRAL) && (codeless_env.gap_activity == IDLE)
        && (arg->cmd_source == CMD_SRC_LOCAL) && (!is_connected())
        && ((*user_get_argument(arg, 1) == 'R')
            || (*user_get_argument(arg, 1) == 'P'))
        && (arg->arg_length[0] == 17) // BD Address must be 17 character string XX:XX:XX:XX:XX:XX
    )
#endif
    {
        uint8_t connect_bdaddr_type;
        send_to_local(CONNECTING_STRING);
        if (*user_get_argument(arg, 1) == 'R') {
            connect_bdaddr_type = ADDR_RAND; // Peer is random address type
        } else {
            connect_bdaddr_type = ADDR_PUBLIC; // Peer is public address type
        }
        struct bd_addr address = strtobdaddr(user_get_argument(arg, 0));
        uint8_t addr[6];
        memcpy(&addr, &address, 6);
        user_connect_to_peripheral(connect_bdaddr_type, addr, 10);
        codeless_env.gap_activity = INITIATING_CONNECTION;

        const uint16_t timeout = 800; // Timeout in 800 slots x 10ms = 8 seconds
        app_easy_timer(timeout, gapconnect_timeout_callback);

        // command successful but do not send reply for this command.
        arg->success_flag = true;
        arg->reply_flag = false;
    }
}
#endif // __DA14531_01__

void user_at_gapdisconnect(struct at_cmd_params_t* arg, char* reply_string)
{
    if (is_connected()) {
        send_to_local(DISCONNECTING_STRING);
        codeless_env.gap_activity = DISCONNECTING;
        app_disconnect_op(0, CO_ERROR_REMOTE_USER_TERM_CON);
        // command successful but don't send reply for this command.
        arg->success_flag = true;
        arg->reply_flag = false;
    }
}
#endif // USE_AT_GAPCONNECT

#ifdef USE_AT_RANDOM
void user_at_random(struct at_cmd_params_t* arg, char* reply_string)
{
    arch_sprintf(reply_string, "0x%08X", rand());
    arg->success_flag = true;
}
#endif

#ifdef USE_AT_PIN
void user_at_pin(struct at_cmd_params_t* arg, char* reply_string)
{
    if (!codeless_env.is_tk_entry_pending) {
        arg->success_flag = false;
        return;
    }

    uint32_t arg1 = ahtoi(user_get_argument(arg, 0));
    codeless_env.is_tk_entry_pending = false;
    app_easy_security_tk_exch(codeless_env.connection_index, (uint8_t *) &arg1, sizeof(arg1), true);

    arg->success_flag = true;
}
#endif


#if defined(USE_AT_BND)
    #if (BLE_APP_SEC)
    // If security is not enabled, this set of commands does not
    // make sense.

void user_at_clrbnde(struct at_cmd_params_t* arg, char* reply_string)
{
    uint8_t conv_result = 0;
    do
    {
        // This commands needs exactly one argument
        if (arg->arg_count != 1)
        {
            arg->success_flag = false;
            break;
        }
        // Exactly one argument
        char* argument=user_get_argument(arg, 0);
        // We expect numbers 1 - MAX_APP_BOND_DB_MAX_BONDED_PEERS and 0xFF

        uint32_t number=0;
        int conversion_error=0;
        conversion_error=atoui32_with_error_checking((char*)argument, 0, &number);
        if (conversion_error==0)
        {
            if ((number >= 1 && number <= APP_BOND_DB_MAX_BONDED_PEERS) || number==0xFF)
            {
                conv_result = (uint8_t)number;
            }
            else
            {
                arg->success_flag = false;
                break;
            }
        }
        else
        {
            arg->success_flag = false;
            break;
        }
        if (conv_result == 0xFF)
        {  // remove all entries
            default_app_bdb_remove_entry( NO_SEARCH_TYPE, REMOVE_ALL, NULL, 0);
        }
        else
        {
              // remove specific entry
            // the slot specified in the command line is 1 indexed
            uint8_t slot=(uint8_t)(conv_result-1);
            default_app_bdb_remove_entry(SEARCH_BY_SLOT_TYPE, REMOVE_THIS_ENTRY, &slot, 0);

        }
        arg->success_flag = true;
    }
    while (0);
}

void user_at_chgbndp(struct at_cmd_params_t* arg, char* reply_string)
{
    do
    {
        if (arg->arg_count == 0) // No arguments - print the database persistence status
        {
            default_app_bdb_get_persistence_status(reply_string);
            arg->success_flag = true;
            break;
        }
        else if (arg->arg_count == 2)
        {
            char* arg1 = user_get_argument(arg, 0);
            char* arg2 = user_get_argument(arg, 1);

            uint8_t arg1_num=0;
            uint8_t arg2_num=0;

            bool are_args_valid=user_verify_persistence_args(arg1, arg2, &arg1_num, &arg2_num);
            if (! are_args_valid)
            {
                arg->success_flag = false;
                break;
            }
            if (arg1_num == 0xFF)
            {
                // change the persistence of all valid entries
                default_app_bdb_change_persistence_status_for_all_entries((uint8_t)arg2_num);
                arg->success_flag = true;
            }
            else
            {
                // change the persistence of all valid entries
                // the slot specified in the command line is 1 indexed
                uint8_t slot=(uint8_t)(arg1_num-1);
                default_app_bdb_change_persistence_status(slot, (uint8_t)arg2_num);
                arg->success_flag = true;
                break;
            }
        }
        else //invalid number of arguments
        {
            arch_sprintf(reply_string,"%s",CODELESS_CMD_INVALID_STRING);
            arg->success_flag=false;
            break;
        }
    }
    while (0);
}

void user_at_iebnde(struct at_cmd_params_t* arg, char* reply_string)
{
    char temp_str[75]={0};
    // We need 27 + 25 + 16 + 1 + 4 bytes = 73 bytes * 2  = 146 chars + 4
    // delimiters + 1 for null termination = 151 chars
    //reply string is large enough and already zeroed when passed as argument

    size_t length = 0;
    const char delimiter=';';
    extern struct bond_db bdb;
    // Only one argument found. Export the entry in the specified slot
    if (arg->arg_count == 1)
    {
        //This number will be used for the slot to read. It should be valid.
        uint8_t bonding_idx = 0;
        char* argument = user_get_argument(arg, 0);
        if (user_is_iebnde_command_argument_valid(argument, &bonding_idx))
        {
            const struct app_sec_bond_data_env_tag* bdb_at_idx_ptr;
            bdb_at_idx_ptr = &bdb.data[bonding_idx];

            // LTK(16) + EDIV(2) + Random Number(8) + Key size(1) = 27 bytes
            memcpy(temp_str, &bdb_at_idx_ptr->ltk, 27);
            for(uint8_t i=0; i<27; i++)
            {
                arch_sprintf(reply_string+2*i,"%02X",temp_str[i]);
            } // 54 chars so far

            // Place a comma here to make the output more readable = 1 byte
            length = strlen(reply_string);
            reply_string[length] = delimiter; // 55 chars so far

            // RCSRK + Peer BD Address + Addr type + Auth + bdb slot  = 25 bytes
            memcpy(temp_str,&bdb_at_idx_ptr->rcsrk,25);
            length=strlen(reply_string);
            for(uint8_t i=0; i<25; i++)
            {
                arch_sprintf(&reply_string[length]+2*i,"%02X",temp_str[i]);
            } // 55 chars + 50 chars = 105 chars so far

            // Place a comma here to make the output more readable
            length=strlen(reply_string);
            reply_string[length] =delimiter; // 105 + 1 = 106 chars so far

            //Export the IRK(16) = 16 bytes
            memcpy(temp_str,&bdb_at_idx_ptr->rirk.irk.key[0],16);
            length=strlen(reply_string);
            for(uint8_t i=0; i<16; i++)
            {
                arch_sprintf(&reply_string[length]+2*i, "%02X",temp_str[i]);
            } // 106 chars + 32 chars =138 chars so far

            // Place a comma here to make the output more readable
            length=strlen(reply_string);
            reply_string[length] = delimiter; // 139 chars so far

            // Persistence(1)+timestamp(4) = 5 bytes
            uint8_t persistence = bdb.persistence[bonding_idx];
            uint32_t timestamp = bdb.timestamp[bonding_idx];
            length=strlen(reply_string);
            arch_sprintf(&reply_string[length], "%02X%c%08X", persistence, delimiter, timestamp );
            // 139 chars + 2 chars + 8 chars +1 char = 150 chars

            arg->success_flag = true;
        }
        else // argument not valid
        {
            arg->error_status = AT_CONSOLE_ERROR_13;
            arg->success_flag = false;
        }
    }
    else if (arg->arg_count == 2)
    {
        struct app_sec_bond_data_env_tag bdb_at_idx;

        // Get the bonding data from the input string
        arch_sprintf(reply_string, "%s", user_get_argument(arg, 1));
        if (is_at_iebnde_string_arg_valid(reply_string, (uint8_t*)temp_str))
        {
            // Initialize the bonding data struct
            memset(&bdb_at_idx, 0, sizeof(bdb_at_idx));

            // LTK(16) + EDIV(2) + Random Number(8) + Key size(1) = 27 bytes
            //memcpy(bdb_at_idx.ltk[0],&temp_str[0],27);
            void* ptr = &bdb_at_idx.ltk;
            memcpy(ptr,&temp_str[0],27);

            //Update the valid_keys field which is currently NOKEY_PRESENT because of the initialization
            bdb_at_idx.valid_keys |=LTK_PRESENT;

            // The 27th byte is the comma
            // RCSRK + Peer BD Address + Addr type + Auth + bdb slot
            ptr = &bdb_at_idx.rcsrk;
            memcpy(ptr, &temp_str[27], 25);

            // Update the valid_keys field keeping the previous keys
            bdb_at_idx.valid_keys |= RCSRK_PRESENT;

            // IRK
            ptr = &bdb_at_idx.rirk.irk.key[0];
            memcpy(ptr, &temp_str[52], 16);

            //Update the valid_keys field keeping the previous keys
            bdb_at_idx.valid_keys |= RIRK_PRESENT;

            uint32_t persistence=(uint32_t)temp_str[68];
            uint32_t timestamp = 0;

            //Convert the byte array to uint32_t - little endian
            timestamp |= (((uint32_t)temp_str[69])<<24 & ((uint32_t)0xFF000000));
            timestamp |= (((uint32_t)temp_str[70])<<16 & ((uint32_t)0x00FF0000));
            timestamp |= (((uint32_t)temp_str[71])<<8  & ((uint32_t)0x0000FF00));
            timestamp |= (((uint32_t)temp_str[72])<<0  & ((uint32_t)0x000000FF));

            //Add the entry to the db including the persistence and the timestamp
            app_bdb_add_entry_with_persistence_and_timestamp(&bdb_at_idx, persistence, timestamp);
            arg->success_flag = true;
        }
        else
        {
            // Invalid argument length
            arg->success_flag = false;
        }
    }
    else
    { // Invalid number of arguments
        arg->success_flag = false;
    }
}
    #endif // (BLE_APP_SEC)
#endif // (USE_AT_BND)

#ifdef USE_AT_HNDL

void user_at_hndl(struct at_cmd_params_t* arg, char* reply_string)
{
    if (arg->arg_count == 0)
    {
        // print existing configuration
        const char* con_at_commands=user_get_handler_command_string(CONNECTION_EVENT_HANDLER);
        const char* discon_at_commands=user_get_handler_command_string(DISCONNECTION_EVENT_HANDLER);
        const char* wakeup_at_commands=user_get_handler_command_string(WAKEUP_EVENT_HANDLER);

        int n=0;
        const char * empty_str="<empty>";
        arch_sprintf(reply_string+n, "%d,%s\r\n",1, (con_at_commands==NULL)? empty_str:con_at_commands);
        n=strlen(reply_string);
        arch_sprintf(reply_string+n, "%d,%s\r\n",2, (discon_at_commands==NULL)? empty_str:discon_at_commands);
        n=strlen(reply_string);
        arch_sprintf(reply_string+n, "%d,%s\r\n",3, (wakeup_at_commands==NULL)? empty_str:wakeup_at_commands);
        arg->success_flag=true;

    }
    else if (arg->arg_count == 1)
    {
        // No second argument - deactivate the event
        char * first_arg = user_get_argument(arg, 0);
        EVENT_HANDLERS_ENUM handler;

        bool is_valid=user_is_handler_argument_valid(first_arg, &handler);
        if (is_valid)
        {
            user_disable_handler(handler);
            arg->success_flag=true;
        }
        else
        {
            arg->error_status=AT_CONSOLE_ERROR_13; //AT Command argument out of range
        }
    }
    else if (arg->arg_count == 2)
    {
        // activate the event. The specified set of commands
        // will be executed if this event activates
        char * first_arg = user_get_argument(arg, 0);
        char * second_arg = user_get_argument(arg, 1);
        EVENT_HANDLERS_ENUM handler;

        bool is_first_arg_valid=user_is_handler_argument_valid(first_arg, &handler);
        if (is_first_arg_valid)
        {
            if (!is_string_null_or_empty(second_arg))
            {
                int result=user_enable_handler(handler,second_arg,strlen(second_arg));
                if (result == 0)
                {
                    arg->success_flag=true;
                }
            }
        }
        else
        {
            // At least one of the arguments was invalid
            arg->error_status=AT_CONSOLE_ERROR_13; //AT command argument out of range
        }
    }
    else
    {
        // Invalid number of arguments - we do not need to do anything here
    }
}
#endif

#ifdef USE_AT_EVENT
void user_at_event(struct at_cmd_params_t* arg, char* reply_string)
{
    arg->success_flag = false;
    do
    {
        if (arg->arg_count == 0)
        {
            // The current event status should be printed to the console
            app_get_printable_event_table(reply_string);
            arg->success_flag = true;
            break;
        }
        if (arg->arg_count == 2)
        {
            char* first_arg = user_get_argument(arg, 0);
            char* second_arg = user_get_argument(arg, 1);

            uint32_t event = 0;
            uint32_t status = 0;
            struct argument_info info={first_arg, 1, NUMBER_OF_EVENTS, 0};

            if (validate_argument(&info, &event) < 0)
            {
                break;
            }
            event--; // The database is zero indexed

            info =(struct argument_info){second_arg, 0, 1 ,0};
            if (validate_argument(&info, &status) < 0)
            {
                break;
            }
            app_set_event_status((EVENTS_ENUM)event, (bool)status);
            arg->success_flag = true;
        }
    }
    while (0);
}
#endif

#ifdef USE_AT_BINARY_MODE

void user_at_binreq(struct at_cmd_params_t* arg, char* reply_string)
{
    //send_to_local(&arg->cmd_buffer[0]);
    if(arg->cmd_source==CMD_SRC_LOCAL)
    {
        send_to_remote(&arg->cmd_buffer[0]);
        codeless_env.disable_local_reply=true;
    }
    else
    {
        send_to_local(&arg->cmd_buffer[2]);
        send_to_local("\r\n");
    }
    arg->success_flag = true;

}

void user_at_binresume(struct at_cmd_params_t* arg, char* reply_string)
{
    if (is_connected())
    {
        codeless_env.req_binary_mode=true;
        arg->success_flag = true;
    }
    else
    {
        arg->success_flag = false;
    }
}

void user_at_binreqack(struct at_cmd_params_t* arg, char* reply_string)
{
#if !defined(__DA14531_01__)
    if (codeless_env.bt_role == GAP_ROLE_CENTRAL)
    {
        //control for central
    }
    else
#endif
    {
        if (!custs1_flow_Control_ccc_notifications_enabled())
        {
            arg->success_flag = false;
            return;
        }
    }

    bool connected=false;
    if (is_connected())
        connected=true;

    if(arg->cmd_source==CMD_SRC_LOCAL)
    {
        send_to_remote(&arg->cmd_buffer[0]);
        codeless_env.disable_local_reply=true;
    }
    else
    {
        send_to_local(&arg->cmd_buffer[2]);
        send_to_local("\r\n");
    }
    /* Actual switch is happenning inside uart_callback() when print queue is empty */
    if (connected==true)
    {

        user_disable_sleep();

        uart_wait_tx_finish(CODELESS_UART);

        while (uart_data_ready_getf(CODELESS_UART))
        {
            uart_read_byte(CODELESS_UART);
        }
        codeless_env.req_binary_mode=true;
        codeless_env.binary_mode=false;
        /* if command originator is remote dont wait for the OK string */

        if((arg->cmd_source==CMD_SRC_REMOTE) || (peer_supports_codeless() != true) )
        {
            activate_binary_mode(false);
        }
        else
        {
            codeless_env.disable_local_reply=true;
        }
    }


    arg->success_flag = true;
}

void user_at_binreqexit(struct at_cmd_params_t* arg, char* reply_string)
{
    if(arg->cmd_source==CMD_SRC_LOCAL)
    {
        send_to_remote(&arg->cmd_buffer[0]);
        codeless_env.disable_local_reply=true;
    }
    else
    {
        /*If the device is in binary mode then send the exit sequence to host */
        /*Else if the device has already left binary bode just sent the uncolicited message AT+BINREQEXIT*/
        if(codeless_env.binary_mode==true)
        {
            user_initiate_binary_exit();
            user_on_sps_disconnect();

        }
        else
        {
             send_to_local(&arg->cmd_buffer[2]);
             send_to_local("\r\n");
        }
    }
    arg->success_flag = true;
}

void user_at_binesc(struct at_cmd_params_t* arg, char* reply_string)
{

     if (arg->arg_count == 0)
     {
         arch_sprintf(reply_string, "%i %x %i\r\n", (int)ESC_TIMER1_TO_MSEC(codeless_env.escape_time1), (int)codeless_env.escape_chars_command_input, (int)ESC_TIMER2_TO_MSEC(codeless_env.escape_time2));
         arg->success_flag = true;
     }
     else if (arg->arg_count == 3)
     {
         codeless_env.escape_time1 = MSEC_TO_ESC_TIMER1(user_get_argument_value(arg, 0));
         codeless_env.escape_time2 = MSEC_TO_ESC_TIMER2(user_get_argument_value(arg, 2));

         int32_t escape_characters = ahtoi(user_get_argument(arg, 1));
         codeless_env.escape_chars_command_input=escape_characters;

         codeless_env.escape_chars[0]=escape_characters&0xFF;
         codeless_env.escape_chars[1]=(escape_characters>>8)&0xFF;
         codeless_env.escape_chars[2]=(escape_characters>>16)&0xFF;
         if(arg->cmd_source==CMD_SRC_REMOTE)
         {
            send_to_local(BINESC_SEQ_CHANGED_STRING);
         }
         arg->success_flag = true;
     }
     else
     {
         arg->success_flag = false;
     }
}
#endif
/*
  0x00 = bin 00 = disble param update
  0x01 = bin 01 = param update on every connection
  0x02 = bin 10 = param update now
  0x03 = bin 11 = param update now and on every connection
*/
#ifdef USE_AT_CONPAR

void user_at_conpar(struct at_cmd_params_t* arg, char* reply_string)
{
    struct connection_configuration_t *p_conf=&codeless_env.conn_conf;

    bool connected=false;

    if (is_connected())
        connected=true;

    arg->success_flag = true;

    if (arg->arg_count == 0)
    {
        arch_sprintf(reply_string, "%i %i %i %i\r\n", (int) p_conf->connection_interval, (int)p_conf->latency, (int)p_conf->time_out, (int)p_conf->param_update_enable);
    }
    else if (arg->arg_count == 4)
    {

        uint16_t connection_interval=user_get_argument_value(arg, 0);
        /* In order to be able to handle decimal, the connection interval is in multiple of 1.25s */
        /* Connection interval should be in the range of 7.5 msec */
        if(connection_interval<6 || connection_interval>3200)
             arg->success_flag=false;

        uint16_t latency=user_get_argument_value(arg, 1);
        /* Slave latency should be less than 500 */
        if(latency>499)
            arg->success_flag=false;

        /* Timeout should be in the range 100ms to 32sec  and should be a multiple of 10 msec*/
        uint16_t time_out=user_get_argument_value(arg, 2);
        if((time_out<100) || (time_out>32000))
             arg->success_flag=false;

        if((time_out%10)!=0)
            arg->success_flag=false;


        uint32_t slave_latency_high_limit= ((10*time_out/(25*connection_interval)))-1;
        if (latency>slave_latency_high_limit)
            arg->success_flag=false;

        uint16_t pu_action=user_get_argument_value(arg, 3);
        if (pu_action>3)
            arg->success_flag=false;

        if (((pu_action&0x2)==0x2) && (!connected))
        {
            //Attempted immediate param update without connection
            arg->error_status = AT_CONSOLE_ERROR_16;
            return;
        }

        uint16_t param_update_enable= pu_action&0x1;

        /*If all check are correct we move temporary values to sticky values */
        if(arg->success_flag==true)
        {
            p_conf->connection_interval=connection_interval;
            p_conf->latency=latency;
            p_conf->time_out=time_out;
            p_conf->param_update_enable=param_update_enable;
            if ((pu_action&0x2)==0x2)
            {
                // Restore params on disconnection if  pu_action is 2
                p_conf->restore_params = true;
                user_param_update_start(0);
            }
            if ((pu_action & 0x1) == 0x1)
            {
                // Before saving to flash ensure that restore params is set to false
                p_conf->restore_params = false;
                app_store_cpdb_conf_to_flash(p_conf);
            }
        }
        else
        {
             arg->error_status = AT_CONSOLE_ERROR_14;
        }
    }
    else
    {
        //Invalid number of arguments
        arg->success_flag = false;
    }
}
#endif
#ifdef USE_AT_DLEEN
void user_at_dleen(struct at_cmd_params_t* arg, char* reply_string)
{
    struct connection_configuration_t *p_conf=&codeless_env.conn_conf;
    arg->success_flag = false;
    bool connected=false;
    if (ke_state_get(TASK_APP) == APP_CONNECTED)
        connected=true;

    if (arg->arg_count == 0)
    {
        arch_sprintf(reply_string, "%i %i %i\r\n", (int) p_conf->dle_en, (int)p_conf->dle_tx_pkt_len, (int) p_conf->dle_rx_pkt_len);
        arg->success_flag = true;
    }
    else if (arg->arg_count == 3)
    {
        if(connected)
        {
            arg->error_status = AT_CONSOLE_ERROR_15;
            return;
        }
        arg->success_flag = true;

        uint16_t dle_en=user_get_argument_value(arg, 0);
        if(dle_en>1)
            arg->success_flag = false;

        uint16_t dle_tx_pkt_len=user_get_argument_value(arg, 1);
        if((dle_tx_pkt_len<27)||(dle_tx_pkt_len>251))
            arg->success_flag = false;

        uint16_t dle_rx_pkt_len=user_get_argument_value(arg, 2);
        if((dle_rx_pkt_len<27)||(dle_rx_pkt_len>251))
            arg->success_flag = false;

        if(arg->success_flag==true)
        {
            p_conf->dle_en=dle_en;
            p_conf->dle_tx_pkt_len=dle_tx_pkt_len;
            p_conf->dle_rx_pkt_len=dle_rx_pkt_len;

            user_activate_dle( p_conf->dle_en,  p_conf->dle_tx_pkt_len, p_conf->dle_rx_pkt_len);
            app_store_cpdb_conf_to_flash(p_conf);
        }
        else
        {
            arg->error_status = AT_CONSOLE_ERROR_14;
        }
    }
}
#endif
#ifdef USE_AT_MAXMTU
/* Applied on restart, can we reconfig */
void user_at_maxmtu(struct at_cmd_params_t* arg, char* reply_string)
{
    struct connection_configuration_t *p_conf=&codeless_env.conn_conf;

    arg->success_flag = false;
    if (arg->arg_count == 0)
    {
        arch_sprintf(reply_string, "%i\r\n", (int) gattm_get_max_mtu());
        arg->success_flag = true;
    }
    else if (arg->arg_count == 1)
    {
        int mtu=user_get_argument_value(arg, 0);
        if( (mtu<23)||(mtu>512))
        {
            arg->error_status = AT_CONSOLE_ERROR_14;
        }
        else
        {
              if (   (codeless_env.gap_activity == IDLE)
                    && (arg->cmd_source == CMD_SRC_LOCAL)
                    && (ke_state_get(TASK_APP) != APP_CONNECTED))
              {
                    p_conf->max_mtu=mtu;
                    gattm_set_max_mtu(mtu);
                    app_store_cpdb_conf_to_flash(p_conf);
                    arg->success_flag = true;
              }
        }
    }
}

#endif

#ifdef USE_AT_FLOWCONTROL
void user_at_flowcontrol(struct at_cmd_params_t* arg, char* reply_string)
{
    if (arg->arg_count == 0)
    {
        arch_sprintf(reply_string, "%i %i %i\r\n", (int)codeless_env.flow_control_enabled, (int)codeless_env.rts_port_pin_input, (int)codeless_env.cts_port_pin_input);
        arg->success_flag = true;
    }
    else if(arg->arg_count==3)
    {
        uint8_t flow_control = user_get_argument_value(arg, 0);
        //Range Check
        if(flow_control>1)
        {
            arg->success_flag = false;
            arg->error_status = AT_CONSOLE_ERROR_14;
            return;
        }
        codeless_env.flow_control_enabled=flow_control;

        if (codeless_env.flow_control_enabled)
        {

            uint8_t port_rts=user_get_argument_value(arg, 1);
            uint8_t port_cts=user_get_argument_value(arg, 2);
            //Range Check
            if((port_rts>MAX_PIN_NUMBER) || (port_cts>MAX_PIN_NUMBER))
            {
                 arg->success_flag = false;
                 arg->error_status = AT_CONSOLE_ERROR_14;
                 return;
            }

            codeless_env.rts_port_pin_input=port_rts;
            codeless_env.cts_port_pin_input=port_cts;

            // Resolve port and pin numbers from argument
            #if   defined(__DA14585__) || defined(__DA14586__)
            codeless_env.rts_port = port_rts/10;
            codeless_env.rts_pin  = port_rts%10;

            codeless_env.cts_port = port_cts/10;
            codeless_env.cts_pin  = port_cts%10;
            #elif   defined(__DA14531__)
            codeless_env.rts_pin  = port_rts;
            codeless_env.cts_pin  = port_cts;
            #endif

            user_assign_pin(port_rts, IO_FUNC_UART1_RTS);
            user_assign_pin(port_cts, IO_FUNC_UART1_CTS);
            #if defined(__DA14531__)
            GPIO_ConfigurePin((GPIO_PORT)0, (GPIO_PIN)codeless_env.rts_pin, OUTPUT, PID_UART1_RTSN, false );
            GPIO_ConfigurePin((GPIO_PORT)0, (GPIO_PIN)codeless_env.cts_pin, INPUT, PID_UART1_CTSN, false );
            #else
            GPIO_ConfigurePin((GPIO_PORT)codeless_env.rts_port, (GPIO_PIN)codeless_env.rts_pin, OUTPUT, PID_UART1_RTSN, false );
            GPIO_ConfigurePin((GPIO_PORT)codeless_env.cts_port, (GPIO_PIN)codeless_env.cts_pin, INPUT, PID_UART1_CTSN, false );
            #endif
            arg->success_flag = true;

        }
        else
        {
            user_assign_pin(codeless_env.rts_port_pin_input, IO_FUNC_UNDEFINED);
            user_assign_pin(codeless_env.cts_port_pin_input, IO_FUNC_UNDEFINED);

#if !defined(__DA14531__)
            codeless_env.rts_port = 0;
#endif
            codeless_env.rts_pin  = 0;

#if !defined(__DA14531__)
            codeless_env.cts_port = 0;
#endif
            codeless_env.cts_pin  = 0;

            arg->success_flag = true;
        }

    }
    else
    {
         arg->success_flag = false;
    }
}
#endif

#ifdef USE_AT_HOSTSLP
#ifndef USE_AT_FLOWCONTROL
#warning "AT+FLOWCONTROL is disabled"
#endif
void user_at_hostslp(struct at_cmd_params_t* arg, char* reply_string)
{

    if (arg->arg_count==0)
    {
        arch_sprintf(reply_string, "%i %i %i %i\r\n", (int)codeless_env.hst_sleep_mode, (int)codeless_env.hst_sleep_wakeup_byte,
                                                      (int)codeless_env.hst_sleep_wakeup_retry_interval, (int)codeless_env.hst_sleep_wakeup_retry_times);
        arg->success_flag = true;
    }
    else if(arg->arg_count==4)
    {
        uint16_t hst_sleep_mode = user_get_argument_value(arg, 0);
        if( hst_sleep_mode>1 )
        {
            arg->success_flag = false;
            arg->error_status = AT_CONSOLE_ERROR_14;
            return;
        }
        codeless_env.hst_sleep_mode = hst_sleep_mode;
        codeless_env.hst_sleep_wakeup_byte = user_get_argument_value(arg, 1);
        codeless_env.hst_sleep_wakeup_retry_interval = user_get_argument_value(arg, 2);
        codeless_env.hst_sleep_wakeup_retry_times = user_get_argument_value(arg, 3);
        codeless_env.hst_sleep_wakeup_retry_times_cnt = 0;
        /*user_wkup_init will handle the wakup process */
        arg->success_flag = true;
    }
    else
    {
        arg->success_flag = false;
    }

}
#endif

#ifdef USE_AT_PWRLVL
void user_at_pwrlvl(struct at_cmd_params_t* arg, char* reply_string)
{
#if ! defined(__DA14531__)
    const char * not_supported_string="\r\nNOT SUPPORTED\r\n";
#endif
    if (arg->arg_count == 0)
    {
        // We need to print the current power level
#if defined(__DA14531__)
        rf_tx_pwr_lvl_t result=rf_pa_pwr_get();
        arch_sprintf(reply_string, "%d", (int)result);
#else
        arch_sprintf(reply_string, "%s", not_supported_string);
#endif
        arg->success_flag = true;
    }
    else if (arg->arg_count == 1)
    {
        char *arg_1 = user_get_argument(arg, 0);
        const struct argument_info info = {arg_1, 1, 12, 0};
        uint32_t result = 0;
        if (validate_argument(&info, &result) == 0)
        {
        #ifdef __DA14531__
            rf_pa_pwr_set((rf_tx_pwr_lvl_t)result);
        #else
            arch_sprintf(reply_string, "%s", not_supported_string);
        #endif
            arg->success_flag = true;
        }
        else
        {
            arg->error_status = AT_CONSOLE_ERROR_13;
            arg->success_flag = false;
        }
    }
    else
    {
        // Invalid number of arguments.
        arch_sprintf(reply_string,"%s",CODELESS_CMD_INVALID_STRING);
        arg->success_flag = false;
    }
}
#endif

#ifdef USE_AT_PWM
void user_at_pwm(struct at_cmd_params_t* arg, char* reply_string)
{
    do
    {

        if (! is_pwm_hardware_configuration_valid())
        {
            arg->error_status = AT_CONSOLE_ERROR_2; // HW not properly set
            arg->success_flag = false;
            break;
        }
        // Three arguments,frequency, duty cycle, duration in ms
        if (arg->arg_count != 3)
        {
            arg->success_flag = false;
            arch_sprintf(reply_string,"%s",CODELESS_CMD_INVALID_STRING);
            break;
        }
        char *arg1_frequency = user_get_argument(arg, 0);
        char *arg2_duty_cycle = user_get_argument(arg, 1);
        char *arg3_duration_in_ms = user_get_argument(arg, 2);

        uint32_t frequency      = 0;
        uint32_t duty_cycle     = 0;
        uint32_t duration_in_ms = 0;

        // Checking that arguments are actually valid numbers
        if (atoui32_with_error_checking(arg1_frequency,10,&frequency) !=0
            || atoui32_with_error_checking(arg2_duty_cycle,10,&duty_cycle) !=0
            || atoui32_with_error_checking(arg3_duration_in_ms,10,&duration_in_ms) !=0)
        {
            arch_sprintf(reply_string,"%s",CODELESS_CMD_INVALID_STRING);
            arg->success_flag = false;
            break;
        }

        // Checking that numbers are within certain limits
        // Frequency can be between 2Hz and 8MHz
        if ((frequency < MINIMUM_PWM_FREQUENCY) || (frequency > MAXIMUM_PWM_FREQUENCY)) {
            arg->error_status = AT_CONSOLE_ERROR_13; // Argument out of range
            arg->success_flag = false;
            break;
        }

        // Duration can be between 0.1 and 10 sec
        if ((duration_in_ms < MINIMUM_PWM_DURATION_IN_MS) || (duration_in_ms > MAXIMUM_PWM_DURATION_IN_MS))
        {
            arg->error_status = AT_CONSOLE_ERROR_13; // Argument out of range
            arg->success_flag = false;
            break;
        }

        // Duty cycle can be between 0 and 100
        if (duty_cycle > 100)
        {
            arg->error_status = AT_CONSOLE_ERROR_13; // Argument out of range
            arg->success_flag = false;
            break;
        }
        int result=pwm(frequency, duty_cycle, duration_in_ms);
        if (result == 0)
        {
            arg->success_flag = true;
            break;
        }
    }
    while (0);
    return;
}
#endif

#ifdef USE_AT_SPI

void user_at_spi_conf(struct at_cmd_params_t* arg, char* reply_string)
{
    uint32_t result;
    SPI_SPEED_MODE_CFG spi_speed_cfg;
    SPI_CP_MODE_CFG phase_pol_cfg;
    SPI_WSZ_MODE_CFG word_size_cfg;
    do
    {
        if (! user_is_spi_hw_valid())
        {
            arg->error_status = AT_CONSOLE_ERROR_2; // SPI hw not properly set
            arg->success_flag = false;
            break;
        }

        // Speed configuration. Accepted values are 2,4 and 8 - common between 585,586 and 531.
        char *arg_1 = user_get_argument(arg, 0);

        // Phase and polarity configuration.Accepted values 0,1,2,3
        char *arg_2 = user_get_argument(arg, 1);

        // Word size. Currently this can be 8 (bits) only
        char *arg_3 = user_get_argument(arg, 2);

        const struct argument_info speed_info = { arg_1, 0, 2, 0};
        if (validate_argument(&speed_info, &result) == 0)
        {
            #if defined(__DA14585__) || defined(__DA14586__)
            spi_speed_cfg =(SPI_SPEED_MODE_CFG)result;
            #elif defined (__DA14531__)
            spi_speed_cfg = (SPI_SPEED_MODE_CFG)((SPI_SPEED_MODE_2MHz>>1)*(2<<result));
            #else
                #error No configuration defined
            #endif
        }
        else
        {
            arg->error_status = AT_CONSOLE_ERROR_13; // Argument out of range
            arg->success_flag = false;
            break;
        }

        const struct argument_info phase_and_pol_info={ arg_2, 0, 3, 0};
        if (validate_argument(&phase_and_pol_info, &result) == 0)
        {
           phase_pol_cfg = (SPI_CP_MODE_CFG)result;
        }
        else
        {
            arg->error_status = AT_CONSOLE_ERROR_13; // Argument out of range
            arg->success_flag = false;
            break;
        }

        if (arg_3 !=NULL && strcmp(arg_3,"8") == 0)
        {
            word_size_cfg = SPI_MODE_8BIT;
        }
        else
        {
            arg->error_status = AT_CONSOLE_ERROR_13; // Argument out of range
            arg->success_flag = false;
            break;
        }
        user_spi_config(spi_speed_cfg, phase_pol_cfg, word_size_cfg);
        arg->success_flag = true;
        break;
    }
    while (0);
}

void user_at_spi_wr(struct at_cmd_params_t* arg, char* reply_string)
{
    AT_CONSOLE_ERROR_TYPE_t error_status=AT_CONSOLE_NO_ERROR;
    do
    {
        //Check for valid spi configuration and arguments
        char *hex_string_arg = user_get_argument(arg, 0);
        error_status=validate_spi_wr_and_tr_arguments(hex_string_arg);
        if (error_status != AT_CONSOLE_NO_ERROR)
        {
            arg->error_status=error_status;
            break;
        }

        //The argument is always treated as a hex string. However it shall be checked
        //if there is a hex "0x" or "0X" prefix.The string is valid (at least two characters)
        //or the code would not have reached this point.
        if (strncmp(hex_string_arg,"0x",2)==0 || strncmp(hex_string_arg,"0X",2)==0)
        {
            hex_string_arg=hex_string_arg+2;
        }

        bool is_hex_string_valid=true;
        uint8_t spi_send_buffer[strlen(hex_string_arg)>>1];
        memset(spi_send_buffer,(int)0,sizeof(spi_send_buffer));

        //Convert the hex string to a byte array.Check that the hex string is valid
        uint32_t result=0;
        for (uint16_t k=0; k < sizeof(spi_send_buffer) ; k++)
        {
            char c[3]={0};
            c[0]=hex_string_arg[2*k];
            c[1]=hex_string_arg[2*k + 1];
            c[2]=0;
            if (atoui32_with_error_checking(c, 16, &result) == 0)
            {
                spi_send_buffer[k]=(uint8_t)result;
            }
            else
            {
                is_hex_string_valid=false;
                break;
            }
        }
        if (!is_hex_string_valid)
        {
            arg->error_status=AT_CONSOLE_ERROR_14; // invalid hex string - return invalid parameter range
            break;
        }
        else
        {
            user_spi_wr(spi_send_buffer,sizeof(spi_send_buffer));
            arg->success_flag = true;
            break;
        }
    }
    while (0);
    return;
}

void user_at_spi_rd(struct at_cmd_params_t* arg, char* reply_string)
{
    do
    {
        // Check for valid hardware configuration
        if (!user_is_spi_hw_valid())
        {
            arg->error_status = AT_CONSOLE_ERROR_2;// HW not properly set
            break;
        }
        uint8_t arg1 = user_get_argument_value(arg, 0); //Number of bytes to read
        if (arg1>CONSOLE_MAX_SPI_STRING_LENGTH)
        {
            arg->error_status=AT_CONSOLE_ERROR_13; // At command argument out of range - string too long
            break;
        }
        uint8_t data[arg1];
        user_spi_rd(data,arg1);
        arch_sprintf(reply_string,"%s","0x");
        for (uint8_t jj=0; jj < arg1 ; jj++)
        {
            arch_sprintf(reply_string+2+2*jj, "%02X",data[jj]);
        }
        arg->success_flag = true;
        break;
    }
    while (0);
    return;
}

void user_at_spi_transfer(struct at_cmd_params_t* arg, char* reply_string)
{
    AT_CONSOLE_ERROR_TYPE_t error_status=AT_CONSOLE_NO_ERROR;
    do
    {
        char *hex_string_arg = user_get_argument(arg, 0);
        error_status=validate_spi_wr_and_tr_arguments(hex_string_arg);
        if (error_status != AT_CONSOLE_NO_ERROR)
        {
            arg->error_status=error_status;
            break;
        }

        //The argument is always treated as a hex string. However it shall be checked
        //if there is a hex "0x" or "0X" prefix.The string is valid (at least two characters)
        //or the code would not have reached this point.
        if (strncmp(hex_string_arg,"0x",2)==0 || strncmp(hex_string_arg,"0X",2)==0)
        {
            hex_string_arg=hex_string_arg+2;
        }

        bool is_hex_string_valid=true;

        uint8_t spi_send_buffer[strlen(hex_string_arg)>>1];
        uint8_t spi_receive_buffer[strlen(hex_string_arg)>>1];

        memset(spi_send_buffer,(int)0,sizeof(spi_send_buffer));
        memset(spi_receive_buffer,(int)0,sizeof(spi_receive_buffer));

        //Convert the hex string to a byte array.Check that the hex string is valid
        uint32_t result=0;
        for (uint16_t k=0; k < sizeof(spi_send_buffer) ; k++)
        {
            char c[3]={0};
            c[0]=hex_string_arg[2*k];
            c[1]=hex_string_arg[2*k + 1];
            c[2]=0;
            if (atoui32_with_error_checking(c, 16, &result) == 0)
            {
                spi_send_buffer[k]=(uint8_t)result;
            }
            else
            {
                is_hex_string_valid=false;
                break;
            }
        }
        if (!is_hex_string_valid)
        {
            arg->error_status=AT_CONSOLE_ERROR_14; // invalid hex string - return invalid parameter range
            break;
        }
        else
        {
            user_spi_tr(spi_send_buffer,spi_receive_buffer,sizeof(spi_send_buffer));
            arch_sprintf(reply_string,"%s","0x");
            for (uint8_t jj=0; jj < sizeof(spi_send_buffer) ; jj++)
            {
                arch_sprintf(reply_string+2+2*jj, "%02X",spi_receive_buffer[jj]);
            }
            arg->success_flag = true;
            break;
        }
    }
    while (0);
    return;
}

#endif

#ifdef USE_AT_RSSI

void user_at_rssi(struct at_cmd_params_t* arg, char* reply_string)
{
    if (ke_state_get(TASK_APP) != APP_CONNECTED)
    {
        arg->error_status = AT_CONSOLE_ERROR_16; // Device is not connected
        arg->success_flag = false;
    }
    else
    {
        /*
        The codeless_env.rssi contains the 2s complement of the
        rssi value in dBm. An intermediate response will be sent
        to the console.
        */
        if (codeless_env.rssi==0)
        {
            const char *sampling_string = "Sampling...";
            arch_sprintf(reply_string, "%s", sampling_string);
        }
        else
        {
            arch_sprintf(reply_string, "%d dBm",codeless_env.rssi-256);
        }
        arg->success_flag = true;
    }
}
#endif

#ifdef USE_AT_SEC

void user_at_sec(struct at_cmd_params_t* arg, char* reply_string)
{
    extern bool restore_sec_pair_mode_on_discon_if_legacy;
    do
    {
        if (arg->arg_count == 0)
        {
            arch_sprintf(reply_string, "%d",get_security_and_pairing_mode());
            arg->success_flag = true;
            break;
        }
        else if (arg->arg_count == 1)
        {
            uint32_t arg_as_number = 0;
            char *cmd_arg = user_get_argument(arg, 0);

            // Check arguments
            if (atoui32_with_error_checking((char*)cmd_arg, 0, &arg_as_number) == 0)
            {
                if (arg_as_number > 4) // valid values are 0,1,2,3,4
                {
                    arg->error_status=AT_CONSOLE_ERROR_14; // Invalid parameter range
                    arg->success_flag = false;
                    break;
                }
            }
            else
            {
                arg->error_status=AT_CONSOLE_ERROR_14; // Invalid parameter range
                arg->success_flag = false;
                break;
            }
            // Check for an active connection
            if (is_connected())
            {
                arg->error_status=AT_CONSOLE_ERROR_15; // Device is connected
                arg->success_flag = false;
                break;
            }

#if defined(CFG_USE_DYNAMIC_PRF_PERMS)
            // Execute the actual call to the set_security_and_pairing_mode function
            // only if the security level specified is different than the current level
            if (get_security_and_pairing_mode() != (security_and_pairing_t)arg_as_number)
            {
                set_security_and_pairing_mode((security_and_pairing_t)arg_as_number);

                //If dynamic profile permissions macro is defined a reply for the command
                //will not be sent.The reply will be handled by the callbacks.
                arg->reply_flag = false;
            }
#else
            set_security_and_pairing_mode((security_and_pairing_t)arg_as_number);
#endif
            restore_sec_pair_mode_on_discon_if_legacy = false;
            arg->success_flag = true;
            break;
        }
        else
        {
            arg->success_flag = false;
        }
    }
    while (0);
    return;
}

#endif


#ifdef USE_AT_HRTBT

void user_at_hrtbt(struct at_cmd_params_t* arg, char* reply_string)
{
    do
    {
        if (arg->arg_count == 0)
        {
            arch_sprintf(reply_string, "%d",is_heart_beat_enabled());
            arg->success_flag = true;
            break;
        }
        else if (arg->arg_count == 1)
        {
            uint32_t arg_as_number = 0;
            char *cmd_arg = user_get_argument(arg, 0);

            // Check arguments
            struct argument_info info={cmd_arg, 0, 1, 0};
            if (validate_argument(&info, &arg_as_number) < 0)
            {
                arg->error_status=AT_CONSOLE_ERROR_14; // Invalid parameter range
                arg->success_flag = false;
                break;
            }
            if (!is_heart_beat_hardware_conf_valid())
            {
                arg->error_status = AT_CONSOLE_ERROR_2; // HW not properly set
                arg->success_flag = false;
                break;
            }
            switch (arg_as_number)
            {
                case 0:
                {
                    stop_heart_beat();
                    break;
                }
                case 1:
                {
                    start_heart_beat();
                    break;
                }
            }
            arg->success_flag = true;
            break;
        }
        else
        {
            arg->success_flag = false;
        }
    }
    while (0);
    return;
}
#endif

#ifdef USE_AT_BAUD
void user_at_baud(struct at_cmd_params_t* arg, char* reply_string)
{
    do
    {
        // No arguments.Retrieve and print the current baud rate
        if (arg->arg_count == 0)
        {
            int32_t result = user_uart_baudrate_getf(CODELESS_UART);
            if (result==-1)
            {
                arch_sprintf(reply_string, "%s", "Error determining baud rate");
                break;
            }
            else
            {
                arch_sprintf(reply_string, "%d",  result);
            }
        }
        else if (arg->arg_count == 1)
        {
            char *arg1 = user_get_argument(arg, 0);
            uint32_t baud_rate=0;
            if (atoui32_with_error_checking(arg1,10,&baud_rate) !=0)
            {
                arg->error_status = AT_CONSOLE_ERROR_13; // AT command argument out of range
                break;
            }
            else
            {
                UART_BAUDRATE uart_baud_rate;
                //The argument is a valid number.Is it a valid baudrate?
                if (is_baud_rate_valid((int32_t)baud_rate,&uart_baud_rate))
                {
                    // Everything is ok. The baud rate will change

                    // Do not send a response
                    arg->reply_flag = false;

                    // Store the codeless information to the environment
                    codeless_env.baud_rate = uart_baud_rate;

                    if(arg->cmd_source !=CMD_SRC_REMOTE)
                    {
                        /*
                        Send the ok termination string with the old baudrate now. If command is local and echo
                        is enabled the command has been printed already. This command does not make sense if another
                        interface is used therefore the whole AT+BAUD Command is excluded.
                        */
                        uart_write_buffer(CODELESS_UART, (const uint8_t*)OK_TERMINATION_STRING, strlen(OK_TERMINATION_STRING));
                        uart_wait_tx_finish(CODELESS_UART);
                    }
                    else
                    {
                        send_to_remote(OK_TERMINATION_STRING);
                    }
                    // Change the actual baud rate
                    uart_baudrate_setf(CODELESS_UART, uart_baud_rate);
                    // From this point onwards the baud rate has changed.
                }
                else
                {
                    arg->error_status = AT_CONSOLE_ERROR_13; // AT command argument out of range
                    break;
                }
            }
        }
        else
        {
            //Invalid number of arguments
            arg->success_flag = false;
            break;
        }
        arg->success_flag = true;
        break;
    }
    while (0);
    return;
}
#endif // USE_AT_BAUD


void user_at_invalid(struct at_cmd_params_t* arg, char* reply_string)
{
    arch_sprintf(reply_string, CODELESS_CMD_INVALID_STRING);
    arg->success_flag = false;
}

/// @} APP


