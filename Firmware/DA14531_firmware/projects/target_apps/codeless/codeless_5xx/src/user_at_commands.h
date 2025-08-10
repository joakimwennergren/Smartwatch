/**
 ****************************************************************************************
 *
 * @file user_at_commands.h
 *
 * @brief  Codeless AT commands header file
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

#ifndef _USER_AT_COMMANDS_H_
#define _USER_AT_COMMANDS_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup APP_CODELESS
 *
 * @brief Codeless AT commands implementation.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "user_at_console.h"
#include "rwip.h"
#include "da1458x_config_basic.h"
/*
 * DEFINES
 ****************************************************************************************
 */

/// If the following symbols are defined the respective at commands and their components
/// will be available, otherwise they will be compiled out for a leaner codesize and and
/// invalid command message will be returned every time they are issued by the user.

//#if defined(USE_AT_BINARY_MODE)&&defined(__DA14531__)
#if defined(__DA14531__) && !defined(__DA14535__)
#define USE_AT_BDADDR
#define USE_AT_IO
#define USE_AT_GAPSTATUS
#define nUSE_AT_ADVDATA
#define nUSE_AT_ADVRESP
#define USE_AT_ADVSTOP
#define USE_AT_ADVSTART
#if !defined(__DA14531_01__)
#define USE_AT_CENTRAL
#define USE_AT_GAPSCAN
#endif
#define USE_AT_GAPCONNECT
#define USE_AT_SLEEP
#define USE_AT_PIN
#define USE_AT_FLOWCONTROL
#if !defined( __IS_SDK6_COMPILER_GCC__) || !defined(__DA14531_01__)
#define USE_AT_CONPAR
#endif
#define USE_AT_BND
#define USE_AT_SEC
#if !defined(__DA14531_01__)
#define USE_AT_PERIPHERAL
#endif



#if !defined(USE_AT_BINARY_MODE)
    #if !defined (USE_SET_TWO)
        #define USE_AT_PRINT
        #define USE_AT_HNDL
        #define USE_AT_EVENT
        #define USE_AT_BROADCASTER
        #define USE_AT_RANDOM
        #define USE_AT_MAXMTU
        #define USE_AT_PWM
        #if CMD_LOCAL_SOURCE==CMD_UART
            #define USE_AT_BAUD
        #endif
        #if (CMD_LOCAL_SOURCE != CMD_SPI)
            #if !defined (CFG_SPI_FLASH_ENABLE)
                #define USE_AT_SPI
            #endif
        #endif
    #elif defined (USE_SET_TWO)
        #if (CMD_LOCAL_SOURCE != CMD_SPI)
            #if !defined (CFG_SPI_FLASH_ENABLE)
                #define USE_AT_SPI
            #endif
        #endif
        #define USE_AT_DLEEN
        #define USE_AT_MEM
        #define USE_AT_BATT
        #define USE_AT_HOSTSLP
        #define USE_AT_ADC
        #define USE_AT_I2C
        #define USE_AT_PWRLVL
        #define USE_AT_RSSI
        #define USE_AT_HRTBT
        #define USE_AT_CMD
    #endif // !USE_SET_TWO
#endif //!USE_AT_BINARY_MODE

#else
#define USE_AT_BDADDR
#define USE_AT_MEM
#define USE_AT_CMD
#define USE_AT_SLEEP
#define USE_AT_IO
#define USE_AT_ADC
#define USE_AT_BATT
#define USE_AT_I2C
#define USE_AT_PRINT
#define USE_AT_GAPSTATUS
#define USE_AT_ADVDATA
#define USE_AT_ADVRESP
#define USE_AT_ADVSTOP
#define USE_AT_ADVSTART
#define USE_AT_CENTRAL
#define USE_AT_GAPSCAN
#define USE_AT_GAPCONNECT
#define USE_AT_RANDOM
#define USE_AT_PIN
#define USE_AT_HNDL
#define USE_AT_EVENT
#define USE_AT_BROADCASTER
#define USE_AT_CONPAR
#define USE_AT_DLEEN
#define USE_AT_MAXMTU
#define USE_AT_BND
#define USE_AT_FLOWCONTROL
#define USE_AT_HOSTSLP
#define USE_AT_PWRLVL
#define USE_AT_PWM
#define USE_AT_PERIPHERAL

#if (CMD_LOCAL_SOURCE != CMD_SPI)
    #if !defined (CFG_SPI_FLASH_ENABLE)
    #define USE_AT_SPI
    #endif // CFG_SPI_FLASH_ENABLE
#endif

#define USE_AT_RSSI
#define USE_AT_SEC
#define USE_AT_HRTBT
#if CMD_LOCAL_SOURCE==CMD_UART
    #define USE_AT_BAUD
#endif
#endif

#undef USE_AT_CURSOR  //TODO, define 531 pins


/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */


/**
 * \brief  AT command parameters structure.
 */
struct at_cmd_params_t
{
    char* cmd_buffer;                      /**< Pointer to command buffer */
    size_t cmd_length;                     /**< Command string length in bytes */
    uint8_t command_tag_length;            /**< Command tag number of characters */
    uint8_t cmd_tag_index;                 /**< Command tag index - (|, AT, ATr, AT+, ATr+) */
    CMD_SRC_t cmd_source;                  /**< Command route. */
    uint8_t arg_count;                     /**< Number of arguments */
    uint8_t arg_index[CMD_MAX_ARG_COUNT];  /**< Index of command buffer argument n is located */
    uint8_t arg_length[CMD_MAX_ARG_COUNT]; /**< Argument n length */
    bool reply_flag;                       /**< RESET: at command reply is suppressed. true on init */
    bool success_flag;                     /**< SET: at command is considered succesful. false on init */
    AT_CONSOLE_ERROR_TYPE_t error_status;  /**< current AT command error code */
};

/**
 * \brief AT command set.
 *
 * Set of supported codeless at command set.
 */
typedef enum {
    AT=0, /**< Returns OK */
    ATI, /**< Lists SW release and HW information */
    ATE, /**< Turns echo on or off */
    ATZ, /**< Set gpio configuration to default */
    ATR, /**< Platform reset */
    ATF, /**< Turn error report on or off */
#ifdef USE_AT_CURSOR
    AT_CURSOR, /**< Places a time stamp cursor in SmartSnippets power profiler */
#endif
#ifdef USE_AT_BDADDR
    AT_BDADDR, /**< Displays the Bluetooth device address */
#endif
#ifdef USE_AT_MEM
    AT_MEM, /**< Stores/Displays a single or multiple commands (semicolon separated) */
#endif
#ifdef USE_AT_CMD
    AT_CMDSTORE, /**< Stores one or multiple commands (semicolon separated)  */
    AT_CMDPLAY, /**<  Executes a stored command string */
    AT_CMD, /**<  Displays a stored command string*/
    AT_TMRSTART, /**< Starts a timer */
    AT_TMRSTOP, /**<  Stops a timer */
#endif
#ifdef USE_AT_SLEEP
    AT_SLEEP, /**< Controls sleep mode (0:awake / 1:extended sleep */
#endif
#ifdef USE_AT_IO
    AT_IOCFG, /**< Sets the functionality of a specified IO pin. */
    AT_IO, /**< Sets Output pin (2 arguments) or read pin state (single argument)*/
#endif
#ifdef USE_AT_ADC
    AT_ADC, /**< Read an analog input (Only pin P0_0 - P0_3!)*/
#endif
#ifdef USE_AT_BATT
    AT_BATT, /**< Query the battery capacity in percentage */
#endif
#ifdef USE_AT_I2C
    AT_I2CSCAN, /**< Scan for I2C slaves */
    AT_I2CCFG, /**< Configure I2C */
    AT_I2CREAD, /**< Read one or more I2C slave registers */
    AT_I2CWRITE, /**< Write to a single I2C slave register */
#endif
#ifdef USE_AT_PRINT
    AT_PRINT, /**< Print a string to local UART */
#endif
#ifdef USE_AT_GAPSTATUS
    AT_GAPSTATUS, /**< Report the Bluetooth GAP role and conection status */
#endif
#ifdef USE_AT_ADVDATA
    AT_ADVDATA_SET, /**< Set Bluetooth advertising data */
    AT_ADVDATA_GET, /**< Get Bluetooth advertising data */
#endif
#ifdef USE_AT_ADVRESP
    AT_ADVRESP_SET, /**< Set Bluetooth advertising response data */
    AT_ADVRESP_GET, /**< Get Bluetooth advertising response data */
#endif
#ifdef USE_AT_ADVSTOP
    AT_ADVSTOP, /**< Stop Bluetooth advertising */
#endif
#ifdef USE_AT_ADVSTART
    AT_ADVSTART, /**< Start Bluetooth advertising */
#endif
#ifdef USE_AT_CENTRAL
    AT_CENTRAL, /**< Put the device in central Bluetooth role*/
#endif
#ifdef USE_AT_PERIPHERAL
    AT_PERIPHERAL, /**< Put the device in peripheral Bluetooth role */
#endif
#ifdef USE_AT_BROADCASTER
    AT_BROADCASTER, /**< Put the device in broadcaster Bluetooth role */
#endif
#ifdef USE_AT_GAPSCAN
    AT_GAPSCAN, /**< Start a Bluetooth scan */
#endif
#ifdef USE_AT_GAPCONNECT
#if !defined(__DA14531_01__)
    AT_GAPCONNECT, /**< Initiate a Bluetooth connection */
#endif
    AT_GAPDISCONNECT, /**< Disconnect from a Bluetooth peer */
#endif
#ifdef USE_AT_RANDOM
    AT_RANDOM, /**< Produce a random 32bit number */
#endif
#ifdef USE_AT_PIN
    AT_PIN, /**< Set or request the current pin code */
#endif
#ifdef USE_AT_BND
    #if (BLE_APP_SEC)
    AT_CLRBNDE,
    AT_CHGBNDP,
    AT_IEBNDE,
    #endif
#endif
#ifdef USE_AT_HNDL
    AT_HNDL,        /**< Set event handlers */
#endif
#ifdef USE_AT_EVENT
    AT_EVENT,       /**< Set events */
#endif
#ifdef USE_AT_BINARY_MODE
    AT_BINREQ,
    AT_BINREQACK,
    AT_BINREQEXIT,
    AT_BINESC,
    AT_BINRESUME,
    AT_BINREQEXITACK,
#endif
#ifdef USE_AT_CONPAR
    AT_CONPAR,
#endif
#ifdef USE_AT_DLEEN
    AT_DLEEN,
#endif
#ifdef USE_AT_MAXMTU
    AT_MAXMTU,
#endif
#ifdef USE_AT_FLOWCONTROL
    AT_FLOWCONTROL,
#endif
#ifdef USE_AT_HOSTSLP
    AT_HOSTSLP,
#endif
#ifdef USE_AT_PWRLVL
    AT_PWRLVL,
#endif
#ifdef USE_AT_PWM
    AT_PWM,
#endif
#ifdef USE_AT_SPI
    AT_SPICFG,
    AT_SPIWR,
    AT_SPIRD,
    AT_SPITR,
#endif
#ifdef USE_AT_RSSI
    AT_RSSI,
#endif
#ifdef USE_AT_SEC
    AT_SEC,
#endif
#ifdef USE_AT_HRTBT
    AT_HRTBT,
#endif
#ifdef USE_AT_BAUD
    AT_BAUD,
#endif
    AT_INVALID, /**< Command to execute in case of an invalid command. */
    AT_LAST_VALUE /**< Enumeration length. */
} AT_COMMAND_ID_t;

/**
 * \brief AT command callback type.
 */
typedef void (*at_cmd_callback)(struct at_cmd_params_t*, char*);

/**
 * \brief At command characteristics.
 *
 *  All at command attributes required in at command jump table.
 */

struct at_command_characteristics_t
{
    uint8_t command_min_arg_count:4; /**< Minimum number of arguments */
    uint8_t command_max_arg_count:4; /**< Maximum number of arguments */
    const char* command_tag_string;  /**< at command tag string */
    at_cmd_callback callback;        /**< at command callback that implements functionality. */
}__attribute__((__packed__));

#define AT_CMD_ENTRY(id, min_args, max_args, tag, cb)   [id] = { min_args, max_args, tag, cb}

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Executes event handlers at commands
 ****************************************************************************************
 */
void user_execute_event_handler_commands(char * cmd);

/**
 ****************************************************************************************
 * @brief Returns OK.
 ****************************************************************************************
 */
void user_at(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Lists SW release and HW information.
 ****************************************************************************************
 */
void user_ati(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Turns echo on or off.
 ****************************************************************************************
 */
void user_ate(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Set system gpio configuration to default.
 ****************************************************************************************
 */
void user_atz(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Trigger a platform reset.
 ****************************************************************************************
 */
void user_atr(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Turns error report on or off.
 ****************************************************************************************
 */
void user_atf(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Places a time stamp cursor in SmartSnippets' power profiler.
 ****************************************************************************************
 */
void user_at_cursor(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Displays the Bluetooth device addres.
 ****************************************************************************************
 */
void user_at_bdaddr(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Stores/Displays a user string from/to the requested slot.
 ****************************************************************************************
 */
void user_at_mem(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Stores one or multiple commands (semicolon separated) to the requested slot.
 ****************************************************************************************
 */
void user_at_cmdstore(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Executes a stored command string from the specified slot.
 ****************************************************************************************
 */
void user_at_cmdplay(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief  Displays stored command string in the specified slot.
 ****************************************************************************************
 */
void user_at_cmd(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Start a timer.
 ****************************************************************************************
 */
void user_at_tmrstart(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief  Stop a timer.
 ****************************************************************************************
 */
void user_at_tmrstop(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Controls sleep mode (0:awake / 1:extended sleep).
 ****************************************************************************************
 */
void user_at_sleep(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief ts the functionality of a specified IO pin..
 ****************************************************************************************
 */
void user_at_iocfg(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Sets Output pin (2 arguments) or read pin state (single argument.
 ****************************************************************************************
 */
void user_at_io(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Read an analog input (Only pin P0_0 - P0_3!.
 ****************************************************************************************
 */
void user_at_adc(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Query the battery capacity in percentage.
 ****************************************************************************************
 */
void user_at_batt(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Scan for I2C slaves.
 ****************************************************************************************
 */
void user_at_i2cscan(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Configure I2C.
 ****************************************************************************************
 */
void user_at_i2ccfg(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Read one or more I2C slave registers.
 ****************************************************************************************
 */
void user_at_i2cread(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Write to a single I2C slave register.
 ****************************************************************************************
 */
void user_at_i2cwrite(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Print a string to local UART.
 ****************************************************************************************
 */
void user_at_print(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Report the Bluetooth GAP role and conection status.
 ****************************************************************************************
 */
void user_at_gapstatus(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Set Bluetooth advertising data.
 ****************************************************************************************
 */
void user_at_advdata_set(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Get Bluetooth advertising data.
 ****************************************************************************************
 */
void user_at_advdata_get(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Set Bluetooth advertising response data.
 ****************************************************************************************
 */
void user_at_advresp_set(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Get Bluetooth advertising response data.
 ****************************************************************************************
 */
void user_at_advresp_get(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Stop Bluetooth advertising.
 ****************************************************************************************
 */
void user_at_advstop(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Start Bluetooth advertising.
 ****************************************************************************************
 */
void user_at_advstart(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Put the device in central Bluetooth rol.
 ****************************************************************************************
 */
void user_at_central(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Put the device in peripheral Bluetooth role.
 ****************************************************************************************
 */
void user_at_peripheral(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Put the device in broadcaster Bluetooth role.
 ****************************************************************************************
 */
void user_at_broadcaster(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Start a Bluetooth scan.
 ****************************************************************************************
 */
void user_at_gapscan(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Initiate a Bluetooth connection.
 ****************************************************************************************
 */
void user_at_gapconnect(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Disconnect from a Bluetooth peer.
 ****************************************************************************************
 */
void user_at_gapdisconnect(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Produce a random 32bit number.
 ****************************************************************************************
 */
void user_at_random(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Set or request the current pin code.
 ****************************************************************************************
 */
void user_at_pin(struct at_cmd_params_t* arg, char* reply_string);

/**
 **************************************************************************************** ****************************************************************************************
 */
void user_at_clrbnde(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Change the persistency status of a bonding database entry
 ****************************************************************************************
 */
void user_at_chgbndp(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Import/export a bonding database entry
 ****************************************************************************************
 */
void user_at_iebnde(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Configure event handlers
 ****************************************************************************************
 */
void user_at_hndl(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Configure events
 ****************************************************************************************
 */

void user_at_event(struct at_cmd_params_t* arg, char* reply_string);


/**
 ****************************************************************************************
 * @brief Invalid or unused at command handler.
 ****************************************************************************************
 */
void user_at_invalid(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief binary request command handler
 ****************************************************************************************
 */
void user_at_binreq(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief binary request acknowledge command handler
 ****************************************************************************************
 */
void user_at_binreqack(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief binary request exit command handler
 ****************************************************************************************
 */
void user_at_binreqexit(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief binary request exit acknowledge command handler
 ****************************************************************************************
 */
void user_at_binreqexitack(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief binary mode resume command handler
 ****************************************************************************************
 */
void user_at_binresume(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief set binary mode escape conditions handler
 ****************************************************************************************
 */
void user_at_binesc(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief set binary mode escape conditions handler
 ****************************************************************************************
 */
void user_at_conpar(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief set ble data length handler (DLE)
 ****************************************************************************************
 */
void user_at_dleen(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief set ble MTU handler
 ****************************************************************************************
 */
void user_at_maxmtu(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief set flow control handler
 ****************************************************************************************
 */
void user_at_flowcontrol(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief set host sleep mode handler
 ****************************************************************************************
 */
void user_at_hostslp(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief set power level handler
 ****************************************************************************************
 */
void user_at_pwrlvl(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief set pwm handler
 ****************************************************************************************
 */
void user_at_pwm(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Configure and initialize spi interface
 ****************************************************************************************
 */
void user_at_spi_conf(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Write a specific number of items to the spi interface.
 *        Data read is discarded
 ****************************************************************************************
 */
void user_at_spi_wr(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief read a specific number of items from the spi interface
 ****************************************************************************************
 */
void user_at_spi_rd(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Write a specific number of items to the spi interface and read the response
          keeping the CS low during the entire operation
 ****************************************************************************************
 */
void user_at_spi_transfer(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Get the received signal strength indication as reported by the device
 ****************************************************************************************
 */
void user_at_rssi(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Output a heartbeat signal on one of the IO pins
 ****************************************************************************************
 */
void user_at_hrtbt(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Configure security
 ****************************************************************************************
 */
void user_at_sec(struct at_cmd_params_t* arg, char* reply_string);

/**
 ****************************************************************************************
 * @brief Configure and retrieve serial port baud rate
 ****************************************************************************************
 */
void user_at_baud(struct at_cmd_params_t* arg, char* reply_string);


/**
 ****************************************************************************************
 * @brief Execute an AT command
 ****************************************************************************************
 */
#if defined(CFG_DATAPMP) && defined(CFG_ENTER_BINARY_MODE_ON_CONNECTION)
void user_execute_commands(char* cmd, enum CMD_SRC src);
#endif


#endif //_USER_AT_COMMANDS_H_

/// @} APP
