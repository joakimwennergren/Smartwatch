/**
 ****************************************************************************************
 *
 * @file user_spi_command_interface.c
 *
 * @brief user_spi_command_interface source file.
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#ifndef _USER_SPI_COMMAND_INTERFACE_H_
#define _USER_SPI_COMMAND_INTERFACE_H_

#if defined(__DA14585__) || defined(__DA14586__)
    #define SPI_SLAVE_SUPPORT 1
#elif defined(__DA14531__)
    #define CFG_SPI_SLAVE
#endif

#include "user_periph_setup.h"
#include "user_at_console.h"
#include "gpio.h"
#include "spi.h"

#define SPIHDDR_MASTER_RX_OPCODE (uint8_t)0x61
#define SPIHDDR_MASTER_TX_OPCODE (uint8_t)0x9E

#define SPI_SLAVE_RX_BUFFER_SIZE (CMD_BUFFER_SIZE + 1)
#define SPI_SLAVE_TX_BUFFER_SIZE (RPLY_MAX_SIZE   + 2)    // Extra two bytes to communicate the bytes available


typedef void (*spi_rx_callback_t)(uint16_t);

struct spi_slave_rx_data_t
{
    uint8_t rx_buffer[SPI_SLAVE_RX_BUFFER_SIZE];
    int number_of_bytes_to_receive;
    int number_of_bytes_received;
};

struct spi_slave_tx_data_t
{
    uint8_t tx_buffer[SPI_SLAVE_TX_BUFFER_SIZE];
    int number_of_bytes_to_send;
    int number_of_bytes_sent;
};

struct spihddr_info_t
{
    struct spi_slave_rx_data_t slave_rx_data;
    struct spi_slave_tx_data_t slave_tx_data;
    bool waiting_for_master_opcode;
    bool is_busy;
};


/**
 *****************************************************************************************
 * @brief      Retrieves data received through spi command interface
 *
 * @return     spi_rx_data_t, a pointer to a structure containing the characters received
 *             through spi including the number of bytes received
 *****************************************************************************************
*/
void conf_spi_slave_cmd_interface(void);

/**
 *****************************************************************************************
 * @brief      Retrieves data received through spi command interface
 *
 * @return     spi_slave_rx_data_t, a pointer to a structure containing the data received
 *             and the number of data
 *****************************************************************************************
*/
volatile struct spi_slave_rx_data_t* get_spi_rx_data(void);

/**
 *****************************************************************************************
 * @brief      Registers an spi rx callback that will be executed when the spi transaction
 *             is over.
 *
 * @param[in]  cb, a pointer to the data that will be sent through spi
 * @param[in]  num, the number of bytes to send
 *
 * @return     void
 *****************************************************************************************
*/
void register_spi_rx_callback(spi_rx_callback_t cb);

/**
 *****************************************************************************************
 * @brief      Checks the status of the spihddr mechanism
 *
 * @return     void
 *****************************************************************************************
*/
bool spihddr_is_idle(void);

/**
 *****************************************************************************************
 * @brief      Configures the spi and data ready pins
 *
 * @return     void
 *****************************************************************************************
*/
void setup_spi_command_interface_pins(void);

/**
 *****************************************************************************************
 * @brief      Asserts the spi data ready pin
 *
 * @return     void
 *****************************************************************************************
*/
void assert_spi_drdy_pin(void);

/**
 *****************************************************************************************
 * @brief      Deasserts the spi data ready pin
 *
 * @return     void
 *****************************************************************************************
*/
void deassert_spi_drdy_pin(void);

/**
 *****************************************************************************************
 * @brief      Handles the echo of the initial at command received through spi
 *
 * @return     void
 *****************************************************************************************
*/
void send_initial_command_echo(void);

/**
 *****************************************************************************************
 * @brief      Set the necessary pins for the spihddr mechanism to work
 *
 * @return     void
 *****************************************************************************************
*/
void setup_spihddr_gpios(void);

/**
 *****************************************************************************************
 * @brief      Store a transmission message to an intermediate buffer
 *
 * @param[in]  data, a pointer to the data that will be stored
 * @param[in]  length, the number of bytes to store
 *
 * @return     void
 *****************************************************************************************
*/

void spihddr_store_slave_tx_msg(uint8_t* data, uint8_t length);

#endif // _USER_SPI_COMMAND_INTERFACE_H_


/// @} APP
