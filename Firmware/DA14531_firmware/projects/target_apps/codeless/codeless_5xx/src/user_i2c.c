/**
 ****************************************************************************************
 *
 * @file user_i2c.c
 *
 * @brief CodeLess i2c source file.
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

#include "user_i2c.h"
#include "i2c.h"
#include "user_codeless_env.h"
#include "user_utility_functions.h"
#include "arch_console.h"

/****************************************************************************************
 * MACROS
 ****************************************************************************************/
struct i2c_cfg_env_t i2c_cfg_env;

/**
 ****************************************************************************************
 * @brief Send I2C slave memory address
 *
 * @param[in] address of the I2C slave memory
 ****************************************************************************************
 */
static void user_i2c_send_address(uint8_t address_to_send)
{
    i2c_write_byte(address_to_send & 0xFF); // Set address LSB, write access
}

/**
 ****************************************************************************************
 * @brief      Reads single byte from I2C slave.
 *
 * @param[in]  address, Memory address to read the byte from.
 *
 * @return     Read byte.
 ****************************************************************************************
 */
static bool user_i2c_read_byte(uint8_t address, uint8_t* read_data)
{
    user_i2c_send_address(address & 0x3FF);
    while (!i2c_is_tx_fifo_not_full()); // Wait if Tx FIFO is full
#if defined(__DA14531__)
    i2c_write_byte(I2C_STOP|(0x0100 & 0x3FF)); // Set R/W bit to 1 (read access)
#else
    i2c_write_byte(0x0100 & 0x3FF); // Set R/W bit to 1 (read access)
#endif
    while (!i2c_is_tx_fifo_empty()); // Wait until I2C Tx FIFO empty
    while (i2c_is_master_busy()); // Make sure master has finished
    // Did we receive any data?
    if (i2c_get_rx_fifo_level() != 0)
    {
        *read_data = i2c_read_byte(); // Get received byte
        return true;
    }
    else
    {
        return false;
    }
}

/**
 ****************************************************************************************
 * @brief      Reads 16bit word from I2C slave.
 *
 * @param[in]  address, Memory address to read the byte from.
 *
 * @return     Read word (16bit).
 ****************************************************************************************
 */
static bool user_i2c_read_word16(uint8_t address, uint16_t* read_data)
{
    user_i2c_send_address(address & 0x3FF);
    while (!i2c_is_tx_fifo_not_full()); // Wait if Tx FIFO is full
    i2c_write_byte(0x0100 & 0x3FF); // Set R/W bit to 1 (read access) MSB
#if defined(__DA14531__)
    i2c_write_byte(I2C_STOP|(0x0100 & 0x3FF)); // Set R/W bit to 1 (read access) LSB
#else
    i2c_write_byte(0x0100 & 0x3FF); // Set R/W bit to 1 (read access) LSB
#endif
    while (!i2c_is_tx_fifo_empty()); // Wait until I2C Tx FIFO empty
    while (i2c_is_master_busy());
    // Did we receive any data?
    if (i2c_get_rx_fifo_level() != 0)
    {
        uint16_t MSB = i2c_read_byte();
        uint16_t LSB = i2c_read_byte();
        *read_data = (MSB * 0x100 + LSB); // return received word
        return true;
    }
    else
    {
        return false;
    }
}

/**
 ****************************************************************************************
 * @brief      Writes single byte to I2C slave.
 *
 * @param[in]  address, Memory address to write the byte to.
 * @param[in]  wr_data, Data to write.
 *
 * @return     void.
 ****************************************************************************************
 */
static void user_i2c_write_byte(uint16_t address, uint8_t wr_data)
{
    user_i2c_send_address(address);
    while (!i2c_is_tx_fifo_not_full())
    {
        ; // Wait if I2C Tx FIFO is full
    }
#if defined(__DA14531__)
    i2c_write_byte(I2C_STOP|(wr_data & 0xFF)); // Send write data
#else
     i2c_write_byte(wr_data & 0xFF); // Send write data
#endif
    while (!i2c_is_tx_fifo_empty()); // Wait until Tx FIFO is empty
    while (i2c_is_master_busy()); // wait until no master activity
}

/**
 ****************************************************************************************
 * @brief      Writes 16bit word to I2C slave.
 *
 * @param[in]  address, Memory address to write the byte to.
 * @param[in]  wr_data, Data to write.
 *
 * @return     void.
 ****************************************************************************************
 */
static void user_i2c_write_16(uint16_t address, uint16_t wr_data)
{
    user_i2c_send_address(address);
    while (!i2c_is_tx_fifo_not_full()); // Wait if I2C Tx FIFO is full
    i2c_write_byte((uint8_t)((wr_data & 0xFF00) >> 8)); // Send write data
#if defined(__DA14531__)
    i2c_write_byte(I2C_STOP|((uint8_t)(wr_data & 0x00FF))); // Send write data
#else
    i2c_write_byte((uint8_t)(wr_data & 0x00FF)); // Send write data
#endif
    while (i2c_is_master_busy()); // wait until no master activity
}

void user_i2c_config(uint8_t address_width, uint8_t bit_rate, uint8_t register_width)
{
    i2c_cfg_env.address_width = address_width;
    i2c_cfg_env.bit_rate = bit_rate;
    i2c_cfg_env.register_width = register_width;
}

bool user_is_i2c_hw_valid(void)
{
    // Default to false
    bool status_scl = false;
    bool status_sda = false;

    // Run through all IO pins in the pin configuration array
    for (uint8_t i = 0; i < MAX_PIN_NUMBER; i++) {
        // Is there a pin configured for I2C Clock?
        if (codeless_env.port_configuration[i] == IO_FUNC_I2C_CLOCK) {
            status_scl = true;
        }
        // Is there a pin configured for I2C Data?
        if (codeless_env.port_configuration[i] == IO_FUNC_I2C_DATA) {
            status_sda = true;
        }
    }
    // Return true if a pin was defined as I2C Clock AND a pin is set to I2C Data
    return (status_scl & status_sda);
}

void user_i2c_init(uint16_t slave_address)
{
    // Initialize the I2C with the address provided as argument
    // TODO: Support 10bit addressing
    i2c_set_clock_status(I2C_CLOCK_ENABLE); // Enable  clock for I2C
    i2c_set_controller_status(I2C_CONTROLLER_DISABLE); // Disable the I2C controller
    i2c_set_mode(I2C_MODE_MASTER); // I2C Master mode, slave is disabled
    i2c_set_restart_status(I2C_RESTART_ENABLE); // Restart enabled

    i2c_speed_t speed = (i2c_cfg_env.bit_rate == 1) ? I2C_SPEED_STANDARD : I2C_SPEED_FAST;
    i2c_set_speed(speed);

    if (i2c_cfg_env.address_width == 7) {
        i2c_set_target_addressing_mode(I2C_ADDRESSING_7B);
    } else {
        i2c_set_target_addressing_mode(I2C_ADDRESSING_7B);
    }

    i2c_set_target_address(slave_address); // Set Slave device address
    i2c_set_controller_status(I2C_CONTROLLER_ENABLE); // Enable the I2C controller

    while (i2c_is_master_busy()); // Wait for I2C master FSM to be IDLE
}

void user_i2c_scan(char* resp_str)
{
    // Run through all I2C addresses (7bit addressing only!)
    for (uint16_t i = 0x01; i < 0x7F; i++) {
        // Set next slave address
        user_i2c_init(i);
        i2c_write_byte(0x00 & 0x3FF); // Transmit Address on bus
        while (!i2c_is_tx_fifo_not_full()); // Wait if I2C Tx FIFO is full
#if defined(__DA14531__)
        i2c_write_byte(I2C_STOP|(0x0100 & 0x3FF)); // Send read register 0x00
#else
        i2c_write_byte(0x0100 & 0x3FF); // Send read register 0x00
#endif
        while (!i2c_is_tx_fifo_empty()); // Wait until Tx FIFO is empty
        while (i2c_is_master_busy()); // Make sure Master has finished
        // Did we receive any data?
        if (i2c_get_rx_fifo_level() != 0) {
            // Read the received data (device_id)
            uint8_t device_id = i2c_read_byte();
            // Report address and register 0x00 (device_id)
            arch_sprintf(resp_str, "%s0x%02X:0x%02X,", resp_str, i, device_id);
        }
    }
    // Disable I2C
    i2c_set_controller_status(I2C_CONTROLLER_DISABLE); // Disable the I2C controller
    i2c_set_clock_status(I2C_CLOCK_DISABLE); // Disable clock for I2C
}

bool user_i2c_read(uint16_t hw_address, uint16_t reg_address, uint8_t num_bytes, char* resp_str)
{
    user_i2c_init(hw_address);
    for (uint8_t i = 0; i < num_bytes; i++) {
        if (i2c_cfg_env.register_width == 8) {
            uint8_t data;
            if (user_i2c_read_byte(reg_address + i, &data)) {
                if (i == 0) {
                    arch_sprintf(resp_str, "0x%02X", data);
                } else {
                    arch_sprintf(resp_str, "%s,0x%02X", resp_str, data);
                }
            } else {
                return false;
            }
        } else {
            uint16_t data;
            if (user_i2c_read_word16(reg_address + i, &data)) {
                if (i == 0) {
                    arch_sprintf(resp_str, "0x%02X", data);
                } else {
                    arch_sprintf(resp_str, "%s,0x%02X", resp_str, data);
                }
            } else {
                return false;
            }
        }
    }
    return true;
}

void user_i2c_write(uint16_t hw_address, uint16_t reg_address, uint16_t wr_data)
{
    user_i2c_init(hw_address);
    if (i2c_cfg_env.register_width == 8) {
        user_i2c_write_byte(reg_address, (uint8_t)wr_data);
    } else {
        user_i2c_write_16(reg_address, wr_data);
    }
}

/// @} APP
