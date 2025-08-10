/**
 ****************************************************************************************
 *
 * @file user_utility_functions.c
 *
 * @brief Utility functions used in the CodeLess project
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


#include "hash.h"
#include "user_utility_functions.h"
#include "user_codeless_env.h"
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "ke_mem.h"
#include "uart.h"
#include "user_periph_setup.h"
#include "user_codeless_env.h"
#include "user_at_commands.h"
#include "user_gap.h"
#include "arch_console.h"
#include "wkupct_quadec.h"
#include "user_custs_sps.h"
#include "app_handlers_db.h"
#include "app_events_db.h"
#include "user_handlers.h"
#if defined(__DA14531__)
#include "hw_otpc_531.h"
#endif
/*
 * This timer is used in order to activate sleepmode 10 seconds after bootup.
 */
timer_hnd sleep_timer __SECTION_ZERO("retention_mem_area0");
#ifdef USE_AT_HOSTSLP
static void user_wkup_init(void);
#endif

struct bd_addr generate_random_bd_addr(void)
{
    uint32_t siteID, timestamp, trim;


#ifdef CODELESS_585
    #if defined (__DA14585__) || defined(__DA14586__)
        #define TIME_STAMP_ADDRESS 0x07F8FEC8
        #define SITE_ID_ADDRESS    0x07F8FED0
        #define BAND_GAP_ADDRESS   0x07F8FF08
        #define LNA_TRIM_ADDRESS   0x07F8FEF8
    #else
        #define TIME_STAMP_ADDRESS 0x07F87FE8
        #define SITE_ID_ADDRESS    0x07F87FE4
        #define BAND_GAP_ADDRESS   0x07F87ED8
        #define LNA_TRIM_ADDRESS   0x07F87EE0
    #endif

    #if defined (__DA14585__) || defined (__DA14586__)
    // Enable OTP clock
    SetBits16(CLK_AMBA_REG, OTP_ENABLE, 1);
    // Set OTP in read mode
    SetWord32(OTPC_MODE_REG, 0x1);
    #else
    hw_otpc_init();
    hw_otpc_enter_mode(HW_OTPC_MODE_READ);
    #endif

#endif

    // Read OTP values
    timestamp = GetWord32(TIME_STAMP_ADDRESS); // Device time stamp
    siteID = GetWord8(SITE_ID_ADDRESS) & 0x7; // Get the Site ID (3-bits)
    timestamp ^= (siteID << 30); // Add test site to MSB
    trim = siteID >> 2; // MSb of Site ID
    trim |= (GetWord8(BAND_GAP_ADDRESS) & 0x3F) << 1; // Bandgap trim (6-bits)
    trim |= (GetWord8(LNA_TRIM_ADDRESS) & 0x7F) << 7; // LNA trim (7-bits)

    // Shuffle the bits to 'look' more random
    timestamp = hash(timestamp);
    trim = (hash(trim) & 0x3FFF) | 0xC000;
    struct bd_addr bdaddr;
    uint8_t bd_temp[6];
    // Assign unique address
    bd_temp[0] = timestamp & 0xFF;
    #if (USER_CFG_ADDRESS_MODE == APP_CFG_ADDR_STATIC)
        //Ensure that the two most significant bits are 1
        bd_temp[0]|=0xC0;
    #endif
    bd_temp[1] = (timestamp >> 8) & 0xFF;
    bd_temp[2] = (timestamp >> 16) & 0xFF;
    bd_temp[3] = (timestamp >> 24) & 0xFF;
    bd_temp[4] = trim & 0xFF;
    bd_temp[5] = trim >> 8;
    memcpy(&bdaddr, &bd_temp, 6);
    #if defined(__DA14585__) || defined(__DA14586__)
    SetBits16(CLK_AMBA_REG, OTP_ENABLE, 0); // disable OTP clock
    #else
    hw_otpc_disable();
    #endif
    return (bdaddr);
}

struct bd_addr get_bd_addr_from_otp_or_nvds(void)
{
    struct bd_addr codeless_bd_addr;
    extern struct bd_addr dev_bdaddr;

#if defined (__DA14531__)
    //check if dev_bdaddr is not blank (ones)
    extern const uint8_t blank_otp_bdaddr[6];
    if(memcmp(&dev_bdaddr, &blank_otp_bdaddr, NVDS_LEN_BD_ADDRESS))
#else
     //check if dev_bdaddr is not blank (zeros)
    if(memcmp(&dev_bdaddr, &co_null_bdaddr, NVDS_LEN_BD_ADDRESS))
#endif
    {
        memcpy(&codeless_bd_addr, &dev_bdaddr, NVDS_LEN_BD_ADDRESS);
    }
    else
    {
        uint8_t bd_temp[6] = CFG_NVDS_TAG_BD_ADDRESS;
        memcpy(&codeless_bd_addr, bd_temp , NVDS_LEN_BD_ADDRESS);
    }
    return codeless_bd_addr;
}

#if (BLE_SUOTA_RECEIVER)
void on_suotar_status_change(const uint8_t suotar_event)
{
#if (!SUOTAR_SPI_DISABLE)
    uint8_t dev_id;

    // Release Flash from power down
    spi_flash_release_from_power_down();

    // Try to auto-detect the device
    spi_flash_auto_detect(&dev_id);

    if (suotar_event == SUOTAR_END)
    {
        // Power down SPI Flash
        spi_flash_power_down();
    }
#endif
}
#endif


uint32_t ahtoi(char* str)
{
    // Function can handle both hexadecimal and decimal numbers
    return (uint32_t)strtol(str, NULL, 0);
}

int atoui32_with_error_checking(char * str, uint8_t base, uint32_t * result)
{
    int return_value = 0;
    char * endptr;

    do
    {
        //Ensure that arguments are correct
        if ((str == NULL) || (strlen(str) == 0) || (result == NULL))
        {
            return_value = -1;
            break;
        }
        //Begin conversion
        errno=0; //On success(valid conversion) errno should not be changed
        long int conv_result=strtol(str, &endptr, base);
        if (*endptr != '\0')
        { //An invalid number was specified
            return_value = -1;
            break;
        }
        else if (endptr == str)
        { //Empty string
            return_value = -1;
            break;
        }
        else
        {
            //If errno is not set the conversion is valid
            if (errno == ERANGE)
            {
                return_value = -1;
                break;
            }
            else
            {
                if (conv_result < 0)
                {
                    // Negative numbers are not used in CodeLess.This is an error.
                    return_value = -1;
                    break;
                }
                else
                {
                    *result = (uint32_t)conv_result;
                    return_value = 0;
                }
                break;
            }
        }
    }
    while(0);
    return return_value;
}

int validate_argument(const struct argument_info* info,uint32_t* result, ...)
{
    int value;
    uint32_t number;
    do
    {
        if (info == NULL)
        {
            value = -1;
            break;
        }
        // Obviously the argument cannot be null or an empty string
        // However apart from decimal numbers arguments may be specified as hexadecimal
        // numbers as well (e.g. 0x01 or 0xFF). For the numbers of interest the maximum
        // length of an argument is four.
        if (info->argument == NULL || strlen(info->argument) == 0 || strlen(info->argument) > 4)
        {
            value = -1; // invalid arguments
            break;
        }
        int conversion_error = atoui32_with_error_checking((char*)info->argument, 0, &number);
        if (conversion_error != 0)
        {
            value = -1; // invalid number or conversion error
            break;
        }
        // Check if the argument number is within limits
        if (number >= info->min_range_inclusive && number <= info->max_range_inclusive)
        {
            // The number belongs to [min_range_inclusive, max_range_inclusive].
            // No need to test the list.
            value = 0;
            break;
        }
        // If we reach this point the number was not within limits
        // Check if an argument list exists
        bool is_argument_part_of_the_list = false;
        if (info->additional_arg_count == 0)
        {
            // An argument list does not exist
            value = -1;
            break;
        }
        else
        {
            va_list list;
            va_start(list, result);
            for (size_t i = 0 ; i < info->additional_arg_count ; i++)
            {
                if (number == va_arg(list,uint32_t))
                {
                    is_argument_part_of_the_list = true;
                    break;
                }
            }
            va_end(list);
        }
        // At this point an argument list exists. If the argument is part
        // of the list it is valid else it is invalid.
        value = (is_argument_part_of_the_list ? 0 : (-1));
    }
    while(0);
    if (value == 0 && result !=NULL)
    {
        *result = number;
    }
    return value;
}


struct bd_addr strtobdaddr(char* str)
{
    struct bd_addr bdaddr;
    char c[6];
    char temp_str[3] = { 0 };
    for (uint8_t i = 0; i < 6; i++) {
        temp_str[0] = str[15 - i * 3];
        temp_str[1] = str[16 - i * 3];
        c[i] = (uint8_t)strtol(temp_str, NULL, 16);
    }
    memcpy(&bdaddr, &c, 6);
    return (bdaddr);
}

bool validate_adv_data(char* str, uint8_t* result, uint8_t* length)
{
    uint8_t len = strlen((char*)str) / 3 + 1;
    memcpy(length, &len, 1);
    // Convert from Ascii hex to bytes
    char temp_str[3] = { 0 };
    for (uint8_t i = 0; i < len; i++) {
        temp_str[0] = str[i * 3];
        temp_str[1] = str[i * 3 + 1];
        result[i] = (uint8_t)strtol(temp_str, NULL, 16);
    }
    // Validate that string adheres to |Length|Type|Data| format
    uint8_t ptr = 0;
    uint8_t lc = 0;
    while (ptr < len) {
        lc = result[ptr];
        ptr = ptr + lc + 1;
    }
    if (ptr == len) {
        return (true);
    } else {
        return (false);
    }
}

bool user_malloc(char** str, size_t str_size, uint8_t type)
{
    bool status = false;
    //TODO: Implement mem check for 580.
#if defined(CODELESS_585) && defined(USER_MALLOC_CHECK)
    if (ke_check_malloc(str_size, type))
#endif
    {
        *str = ke_malloc(str_size, type);
        // Initialize to zero, allocated memory
        memset(*str, 0, str_size);
        status = true;
    }
    return status;
}


uart_err_cb_t user_uart_error_cb(uart_t *uart, uint8_t uart_err_status)
{
    return 0;
}

#if !defined(USE_AT_BAUD)
static const uart_cfg_t codeless_uart_cfg =
{
    .baud_rate = CODELESS_UARTx_BAUDRATE,
    .data_bits = CODELESS_UARTx_DATABITS,
    .parity = CODELESS_UARTx_PARITY,
    .stop_bits = CODELESS_UARTx_STOPBITS,
    .auto_flow_control = CODELESS_UARTx_AFCE,
    .use_fifo = CODELESS_UARTx_FIFO,
    .tx_fifo_tr_lvl = CODELESS_UARTx_TX_FIFO_LEVEL,
    .rx_fifo_tr_lvl = CODELESS_UARTx_RX_FIFO_LEVEL,
    .intr_priority = 0
};
#endif

void user_set_uart_to_codeless_settings(void)
{
#if defined(USE_AT_BAUD)
    uart_cfg_t codeless_uart_cfg =
    {

    .baud_rate = codeless_env.baud_rate,
    .data_bits = CODELESS_UARTx_DATABITS,
    .parity = CODELESS_UARTx_PARITY,
    .stop_bits = CODELESS_UARTx_STOPBITS,
    .auto_flow_control = CODELESS_UARTx_AFCE,
    .use_fifo = CODELESS_UARTx_FIFO,
    .tx_fifo_tr_lvl = CODELESS_UARTx_TX_FIFO_LEVEL,
    .rx_fifo_tr_lvl = CODELESS_UARTx_RX_FIFO_LEVEL,
    .intr_priority = 0
};
#endif
    uart_initialize(CODELESS_UART, &codeless_uart_cfg);
    uart_register_err_cb(CODELESS_UART, (uart_err_cb_t)user_uart_error_cb);
    uart_sps_flow_on();

}
#ifdef USE_AT_BINARY_MODE

#if !defined(USE_AT_BAUD)
static const uart_cfg_t dsps_uart_cfg =
{
    .baud_rate = UART_SPS_BAUDRATE,
    .data_bits = UART_DATABITS_8,
    .parity = UART_PARITY_NONE,
    .stop_bits = UART_STOPBITS_1,
    .auto_flow_control = DSPS_AFCE,
    .use_fifo = DSPS_FIFO,
    .tx_fifo_tr_lvl = DSPS_TX_FIFO_LEVEL,
    .rx_fifo_tr_lvl = DSPS_RX_FIFO_LEVEL,
    .intr_priority = 0
};
#endif

void user_set_uart_to_dsps_settings(void)
{
#if defined(USE_AT_BAUD)
    uart_cfg_t dsps_uart_cfg =
    {
        .baud_rate = codeless_env.baud_rate,
        .data_bits = UART_DATABITS_8,
        .parity = UART_PARITY_NONE,
        .stop_bits = UART_STOPBITS_1,
        .auto_flow_control = DSPS_AFCE,
        .use_fifo = DSPS_FIFO,
        .tx_fifo_tr_lvl = DSPS_TX_FIFO_LEVEL,
        .rx_fifo_tr_lvl = DSPS_RX_FIFO_LEVEL,
        .intr_priority = 0
};
#endif
    uart_fc_init();

    uart_initialize(CODELESS_UART, &dsps_uart_cfg);
    uart_register_err_cb(CODELESS_UART,  (uart_err_cb_t)user_uart_error_cb);
}
#endif
#ifdef USE_AT_DLEEN
static void dle_on_off( bool dle_on, uint16_t tx_pkt_len, uint16_t rx_pkt_len )
{
    struct llm_le_env_tag *llm = &llm_le_env;

    if( dle_on==false )
    {
        llm->supportedMaxRxOctets = 27;
        llm->supportedMaxTxOctets = 27;
        llm->connInitialMaxTxOctets = 27;
    }
    else
    {
        llm->supportedMaxRxOctets = rx_pkt_len;
        llm->supportedMaxTxOctets = tx_pkt_len;
        llm->connInitialMaxTxOctets = tx_pkt_len;
    }
}

/* With DA14585 we cannot remove DLE support from LL_FEATURE_REQ/RSP
   but we may emulate this by reducing RX/TX sizes */
void user_activate_dle(bool dle_en, uint16_t tx_pkt_len, uint16_t rx_pkt_len)
{

    if(dle_en)
    {
         #ifdef __DA14531__
         struct le_features  my_llm_local_le_feats = {{ BLE_FEATURES_DLE, 0, 0, 0, 0, 0, 0, 0 }};
         memcpy(&llm_local_le_feats, &my_llm_local_le_feats, FEATS_LEN);
         #endif
         dle_on_off(true,  tx_pkt_len, rx_pkt_len);
    }
    else
    {
         #ifdef __DA14531__
         struct le_features  my_llm_local_le_feats = {{ BLE_FEATURES_NO_DLE, 0, 0, 0, 0, 0, 0, 0 }};
         memcpy(&llm_local_le_feats, &my_llm_local_le_feats, FEATS_LEN);
         #endif
         dle_on_off(false, tx_pkt_len, rx_pkt_len);
    }
}
#endif

void user_param_update_start(uint8_t conidx)
{
    #ifdef USE_AT_CONPAR
    struct connection_configuration_t *p_conf=&codeless_env.conn_conf;
    #endif
    struct gapc_param_update_cmd* cmd;
    cmd = app_easy_gap_param_update_get_active(conidx);

    #ifdef USE_AT_CONPAR
    cmd->intv_max=p_conf->connection_interval;
    cmd->intv_min= cmd->intv_max;
    cmd->latency=p_conf->latency;
    cmd->time_out=MS_TO_TIMERUNITS(p_conf->time_out);
    #endif

    app_param_update_msg_send(cmd);

    app_easy_gap_param_update_set_active(0);
}

void user_assign_pin(uint8_t port_pin, io_func_t func)
{
    for (uint8_t i = 0; i < MAX_PIN_NUMBER; i++)
    {
        if (codeless_env.port_configuration[i] == func)
        {
            codeless_env.port_configuration[i] = IO_FUNC_UNDEFINED;
            #if defined(__DA14585__) || defined(__DA14586__)
            GPIO_PORT port_number = (GPIO_PORT)(i / 10);
            GPIO_PIN pin_number = (GPIO_PIN)(i % 10);
            #elif   defined(__DA14531__)
            GPIO_PORT port_number = (GPIO_PORT)0;
            GPIO_PIN pin_number = (GPIO_PIN)(i);
            #endif
            GPIO_ConfigurePin(port_number, pin_number, INPUT, PID_GPIO, true );
        }
    }
    codeless_env.port_configuration[port_pin] = (io_func_t)func;
}

#ifndef USE_AT_HOSTSLP
void user_host_wakeup_process(void)
{
    arch_printf_process();
}

#else
#ifdef USE_AT_FLOWCONTROL
static void user_set_rts_high(void)
{
    uart_sps_flow_off(true);  //Forced set RTS to high

    codeless_env.host_wakeup_attemt_timer=app_easy_timer(codeless_env.hst_sleep_wakeup_retry_interval/20, user_wkup_init);
}
#endif


static void user_wkup_init(void)
{
    if (codeless_env.hst_sleep_wakeup_retry_times_cnt<codeless_env.hst_sleep_wakeup_retry_times)
    {

        codeless_env.hst_sleep_wakeup_retry_times_cnt++;
        #ifdef USE_AT_FLOWCONTROL
        if(codeless_env.flow_control_enabled)
        {
            uart_sps_flow_on();
            codeless_env.host_wakeup_attemt_timer=app_easy_timer(codeless_env.hst_sleep_wakeup_retry_interval/20, user_set_rts_high);
        }
        else
        #endif
        {
            uart_send(CODELESS_UART,(uint8_t *)&codeless_env.hst_sleep_wakeup_byte, 1, UART_OP_INTR);
            codeless_env.host_wakeup_attemt_timer=app_easy_timer(codeless_env.hst_sleep_wakeup_retry_interval/10, user_wkup_init);
        }

    }
    else
    {
        //DO WHAT??
    }

}
void user_host_wakeup_process(void)
{
    static int wakeup_process_init_cnt=0;

    if (codeless_env.hst_sleep_mode==0)
    {
         codeless_env.event_trigger=0;
         wakeup_process_init_cnt=0;
         arch_printf_process();
    }
    else
    {
        if(wakeup_process_init_cnt==0)
        {
            //We need to send the OK to host
            wakeup_process_init_cnt=1;
            arch_printf_process();
            return;
        }
        /* If msg buffer is overflown arch_printf_msg_active() will fail */
        else if ( codeless_env.event_trigger && (wakeup_process_init_cnt==1))
        {
            codeless_env.event_trigger=false;
            //The host is in sleep mode and there is a message pending, initialize host wkup procedure
            wakeup_process_init_cnt=2;
            user_wkup_init();

        }
        else
        {
            //Do nothing
        }
    }
}
#endif

void user_prepare_wkup_controller(uint32_t polarity)
{
    #if !defined(USE_AT_FLOWCONTROL)
    wkupct_enable_irq(WKUPCT_PIN_SELECT(SLEEP_WKUP_PORT, SLEEP_WKUP_PIN), // UART RX
                        WKUPCT_PIN_POLARITY(SLEEP_WKUP_PORT, SLEEP_WKUP_PIN,
                        polarity), // polarity low
                        1, // Number of events
                        0); // debouncing time = 0ms
    #else

    GPIO_PORT wkup_port=UARTx_RX_GPIO_PORT;
    GPIO_PIN wkup_pin=UARTx_RX_GPIO_PIN;
    if( codeless_env.flow_control_enabled==true)
    {
#if defined(__DA14531__)
        wkup_port=(GPIO_PORT)0;
#else
        wkup_port=(GPIO_PORT)codeless_env.cts_port;
#endif

        wkup_pin=(GPIO_PIN)codeless_env.cts_pin;
    }
    wkupct_enable_irq(WKUPCT_PIN_SELECT(wkup_port, wkup_pin), // UART RX
                    WKUPCT_PIN_POLARITY(wkup_port, wkup_pin,
                    polarity), // polarity low
                    1, // Number of events
                    0); // debouncing time = 0ms
    #endif
}

bool ke_check_msg_alloc(uint16_t const param_len)
{
    uint16_t size=sizeof(struct ke_msg) + param_len - sizeof (uint32_t);
    bool ret=  ke_check_malloc(size, KE_MEM_KE_MSG);
    return ret;
}


void delayed_wakeup(void)
{

    /*
       Check that parser is not already set by another event.
       For 585 if the device is already woken up the periph init won't run
       if the device is already woken up due to eg connection event. Here we
       make sure that the system will be initialized.
    */
    #if defined(__DA14531__)
        GPIO_ConfigurePin(UARTx_TX_GPIO_PORT, UARTx_TX_GPIO_PIN, OUTPUT, PID_UART1_TX, true);
    #endif
    #if defined(__DA14585__) || defined (__DA14586__)
    if (console_env.parser_flag == CHAR_PARSER_NOT_ACTIVE)
    #endif
    {
        // flush uart fifo - read until no data is left in uart rx fifo.
        user_set_uart_to_codeless_settings();
        while (uart_data_ready_getf(CODELESS_UART))
        {
            uart_read_byte(CODELESS_UART);
        }

        // set character parser flag to active.
        console_env.parser_flag = CHAR_PARSER_ACTIVE;
        // Prepare for first AT command via UART
        console_env.input_cmd_char_index = 0;

        user_codeless_uart_start();
        set_commmand_uart_pins();
        #if (UART_HW_FLOW_ENABLED)
        #if defined(USE_AT_FLOWCONTROL)
        if (codeless_env.flow_control_enabled)
        {
#if defined(__DA14531__)
            GPIO_ConfigurePin((GPIO_PORT)0, (GPIO_PIN) codeless_env.rts_pin, OUTPUT, PID_UART1_RTSN, true );
            GPIO_ConfigurePin((GPIO_PORT)0, (GPIO_PIN) codeless_env.cts_pin, INPUT, PID_UART1_CTSN, true );
#else
            GPIO_ConfigurePin((GPIO_PORT) codeless_env.rts_port, (GPIO_PIN) codeless_env.rts_pin, OUTPUT, PID_UART1_RTSN, true );
            GPIO_ConfigurePin((GPIO_PORT) codeless_env.cts_port, (GPIO_PIN) codeless_env.cts_pin, INPUT, PID_UART1_CTSN, true );
#endif
        }
        #else
        GPIO_ConfigurePin( GPIO_UARTx_RTS_PORT, GPIO_UARTx_RTS_PIN, OUTPUT, PID_UART1_RTSN, false );
        GPIO_ConfigurePin( GPIO_UARTx_CTS_PORT, GPIO_UARTx_CTS_PIN, INPUT, PID_UART1_CTSN, false );
        #endif // USE_AT_FLOWCONTROL
        #endif // UART_HW_FLOW_ENABLED
        uart_sps_flow_on();
    }

#ifdef USE_AT_EVENT
    if (app_is_event_enabled(WAKEUP_EVENT))
#endif
    {
        send_to_local(WAKEUP_STRING);
    }
#ifdef USE_AT_HNDL
   if (user_is_handler_enabled(WAKEUP_EVENT_HANDLER))
   {
        user_execute_event_handler_commands((char*)user_get_handler_command_string(WAKEUP_EVENT_HANDLER));
   }
#endif
}

/// Called when device wakes up from Sleep
void user_wakeup()
{
     // Disable interrupt
    wkupct_disable_irq();

    // Disable sleep
    arch_disable_sleep();

    // Freeze the watchdog
    // wdg_freeze();

    // Send a message to delay wakeup procedure.
    // delayed_wakeup is called once uart clock has settled (rwip_schedule is alreay called)
    codeless_env.sleep_active=0;
    #if defined(__DA14531__)
    /* This is needed in order to properly initialize rts/cts */
    periph_init();
    GPIO_ConfigurePin(UARTx_TX_GPIO_PORT, UARTx_TX_GPIO_PIN, OUTPUT, PID_GPIO, true);
    #endif
    ke_msg_id_t delayed_wakeup_msg = app_easy_msg_set(delayed_wakeup);
    if (delayed_wakeup_msg != 0)
    {
        if (!(app_check_BLE_active())) {
            arch_ble_force_wakeup(); // wake_up BLE
        }
        KE_MSG_SEND_BASIC(delayed_wakeup_msg, TASK_APP, 0);
    }
}

// Exit sleep immediately, connection or disconnection
void user_exit_sleep(void)
{
    #ifdef USE_AT_SLEEP
    wkupct_disable_irq();
    arch_disable_sleep();
    // wdg_freeze();
    codeless_env.sleep_active=0;
    codeless_env.user_allow_to_go_to_sleep_flag = false;
    delayed_wakeup();
    #endif
}

// Prepare to sleep. Set wakeup on UART RX activity (low transition)
void user_low_to_high_function(void)
{
    // Disable interrupt
    wkupct_disable_irq();
    wkupct_register_callback(user_wakeup);
    user_prepare_wkup_controller(WKUPCT_PIN_POLARITY_LOW);

}

void user_prepare_sleep()
{
    int polarity=0;


    if (codeless_env.user_allow_to_go_to_sleep_flag == true) {

        #if defined(__DA14531__)
        set_pad_functions();
        #endif


        #if (UART_HW_FLOW_ENABLED) && !defined(USE_AT_FLOWCONTROL)
        if(GPIO_GetPinStatus(GPIO_UARTx_CTS_PORT, GPIO_UARTx_CTS_PIN) == false)
        {
            //If the CTS pin is used, if it low then we need a toggle low-high-low
            //to wakeup
            polarity = WKUPCT_PIN_POLARITY_HIGH;
            wkupct_register_callback(user_low_to_high_function);
        }
        else
        {
             polarity = WKUPCT_PIN_POLARITY_LOW;
             wkupct_register_callback(user_wakeup);
        }
        #endif

        #if (UART_HW_FLOW_ENABLED) && defined(USE_AT_FLOWCONTROL)
        #if defined(__DA14531__)
        if((GPIO_GetPinStatus((GPIO_PORT)0, (GPIO_PIN)codeless_env.cts_pin) == false) && (codeless_env.flow_control_enabled==true))
        #else
        if((GPIO_GetPinStatus((GPIO_PORT)codeless_env.cts_port, (GPIO_PIN)codeless_env.cts_pin) == false) && (codeless_env.flow_control_enabled==true))
        #endif
        {
            //If the CTS pin is used, if it low then we need a toggle low-high-low
            //to wakeup
            polarity = WKUPCT_PIN_POLARITY_HIGH;
            wkupct_register_callback(user_low_to_high_function);
        }
        else
        {
            polarity = WKUPCT_PIN_POLARITY_LOW;
            wkupct_register_callback(user_wakeup);
        }
        #endif

        // Specify the IO pin, the polarity, the event count and the debouncing time for the counter
        // IRQ. If HW Flow Control is enabled the wakeup pin is the incoming CTS pin, otherwise the RX pin.
        user_prepare_wkup_controller(polarity);
        uart_sps_flow_off(true);
        arch_set_extended_sleep(false);
    }
}

void user_disable_sleep(void)
{
    wkupct_disable_irq();
    if(sleep_timer != 0)
        app_easy_timer_cancel(sleep_timer);
    sleep_timer = 0;
}

#if defined(OUTBOUND_CHAR_QUEUE)

typedef struct
{
    struct co_list queue;
}
outbound_char_queue_t;

typedef struct
{
    struct co_list_hdr hdr;
    char *data;
}
outbound_char_data_t;

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

static outbound_char_queue_t outbound_char_queue __SECTION_ZERO("retention_mem_area0");

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void outbound_char_init_queue(void)
{
    co_list_init(&outbound_char_queue.queue);
}

void outbound_char_flush_queue(void)
{
    // If we flush apart from the list we need to free the data members as well
    struct co_list_hdr *tmp_list_hdr = outbound_char_queue.queue.first;
    while (tmp_list_hdr !=NULL)
    {
        ke_free(((outbound_char_data_t*)tmp_list_hdr)->data);
        tmp_list_hdr = tmp_list_hdr->next;
    }
    // Free the list itself
    co_list_flush(&outbound_char_queue.queue);
}

void outbound_char_enqueue(const char* string_ptr)
{
    char *new_elmt_ptr=NULL;
    do
    {
        if (string_ptr ==NULL || strlen(string_ptr)==0)
        {
            break;
        }

        new_elmt_ptr=ke_malloc(strlen(string_ptr)+1,KE_MEM_ENV);
        if (new_elmt_ptr==NULL)
        {
            break;
        }
        strcpy(new_elmt_ptr,string_ptr);
        //Now the new item has to be placed in the queue
        outbound_char_data_t *outbound_char_data_ptr = ke_malloc(sizeof(outbound_char_data_t),KE_MEM_ENV);
        outbound_char_data_ptr->data=new_elmt_ptr;
        co_list_push_back(&outbound_char_queue.queue,(struct co_list_hdr*)outbound_char_data_ptr);
    }
    while (0);
    return;
}

char* outbound_char_dequeue(void)
{
    char *item_ptr=NULL;
    do
    {
        struct co_list_hdr *elmt = co_list_pop_front(&outbound_char_queue.queue);
        if (elmt==NULL)
        {
            // Nothing to return, NULL will be returned eventually
            break;
        }
        outbound_char_data_t *outbound_char_data_ptr = (outbound_char_data_t*)elmt;
        item_ptr=outbound_char_data_ptr->data;
        ke_free(outbound_char_data_ptr);
    }
    while (0);
    return item_ptr;
}
#endif // OUTBOUND_CHAR_QUEUE

#if defined(CFG_PIN_CHANGE_ON_NMI_OR_HARDFAULT)

/* Magic number definition */
#define MAGIC_NUM_1                         0x1234A5A5
#define MAGIC_NUM_2                         0xA5A51234
#define FAULT_INDEX                         4
#define MAGIC_NUM_1_INDEX                   0
#define MAGIC_NUM_2_INDEX                   5

#define INVALID_FAULT                       0x00
#define HARDFAULT_OCCURED                   (1<<0)
#define NMI_OCCURED                         (1<<1)

#if defined(__DA14531__)
    #define DEBUG_GPIO_PORT            GPIO_PORT_0
    #define DEBUG_GPIO_PIN             GPIO_PIN_9
#elif defined(__DA14585__) || defined (__DA14586__)
    #define DEBUG_GPIO_PORT            GPIO_PORT_1
    #define DEBUG_GPIO_PIN             GPIO_PIN_1
#else
#error Error configuring gpio pin for debugging
#endif

volatile uint8_t latest_fault_status[9]   __SECTION_ZERO("retention_mem_area_uninit");

uint8_t check_for_nmi_or_hardfault(void)
{
    uint8_t fault_status = 0;
    // Read the magic values from the un-initialized area
    uint32_t magic_num_1 = co_read32p((const void*)&latest_fault_status[MAGIC_NUM_1_INDEX]);
    uint32_t magic_num_2 = co_read32p((const void*)&latest_fault_status[MAGIC_NUM_2_INDEX]);

    // Check if the magic values are valid
    if (magic_num_1 == MAGIC_NUM_1 && magic_num_2 == MAGIC_NUM_2)
    {
        fault_status = latest_fault_status[FAULT_INDEX];
        if ((fault_status & HARDFAULT_OCCURED) || (fault_status & NMI_OCCURED))
        {
            GPIO_ConfigurePin(DEBUG_GPIO_PORT, DEBUG_GPIO_PIN, OUTPUT, PID_GPIO, true );
        }
    }
    else
    {
        co_write32p((const void*)&latest_fault_status[MAGIC_NUM_1_INDEX], MAGIC_NUM_1);
        co_write32p((const void*)&latest_fault_status[MAGIC_NUM_2_INDEX], MAGIC_NUM_2);
    }
   /*
    * The latest status is kept in the fault status variable,
    * re-initialize the value changed in the hardfault or NMI
    */
    latest_fault_status[FAULT_INDEX] = INVALID_FAULT;

    return fault_status;
}

void user_set_hardfault_flag(void)
{
    latest_fault_status[FAULT_INDEX] |= HARDFAULT_OCCURED;
}

void user_set_watchdog_flag(void)
{
    latest_fault_status[FAULT_INDEX] |= NMI_OCCURED;
}

#endif // CFG_PIN_CHANGE_ON_NMI_OR_HARDFAULT


