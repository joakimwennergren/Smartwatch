/**
 ****************************************************************************************
 *
 * @file user_i2c.h
 *
 * @brief Declaration of the functions used for CodeLess I2C
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

#ifndef _USER_I2C_H_
#define _USER_I2C_H_

#include "app_api.h"

/**
 * \brief  I2C struct
 */
struct i2c_cfg_env_t
{
    uint8_t bit_rate;       /**<  1 for 100kBit/s, 2 for 400kBit/s */
    uint8_t register_width; /**< slave register width 8 or 16 bit */
    uint8_t address_width;  /**<  slave addressing width 10 or 7 bit */
};

/**
 ****************************************************************************************
 * @brief      Sets the i2c slave configuration
 *
 * @param[in]  address_width, The I2C slave address width (7 or 10 bits)
 * @param[in]  bit rate, The I2C slave bit rate (1:100kbit/s, 2:400kbit/s)
 * @param[in]  register_width, The I2C slave register width (8 or 16 bit)
 *
 *****************************************************************************************
 */
void user_i2c_config(uint8_t address_width, uint8_t bit_rate, uint8_t register_width);

/**
 ****************************************************************************************
 * @brief      Checks that ports have been configured so that there is support for I2C.
 *             There must be one I2C SCL and one I2C SDA port defined
 *
 * @return     True if both I2C SCL and I2C SDA has been configured
 *****************************************************************************************
 */
bool user_is_i2c_hw_valid(void);

/**
 ****************************************************************************************
 * @brief      Initializes the I2C interface with the provide slave address
 *
 * @param[in]  slave_address, The I2C slave address to communicate with
 *
 * @return     void
 *****************************************************************************************
 */
void user_i2c_init(uint16_t slave_address);

/**
 ****************************************************************************************
 * @brief      Scans the I2C bus for slave devices
 *
 * @param[in]  extended, if true: Response will include potential I2C slave device IDs
 * @param[in]  remote, originator of the scan command
 *
 * @return     void
 *****************************************************************************************
 */
void user_i2c_scan(char *resp_str);

/**
 ****************************************************************************************
 * @brief      Reads data from an I2C slave
 *
 * @param[in]  hw_address, HW address of I2C slave device
 * @param[in]  reg_address, Register address to be read
 * @param[in]  num_bytes, Number of bytes to read
 * @param[in]  remote, originator of the read command
 *
 * @return     bool, True if read operation was succesfull false otherwise.
 *****************************************************************************************
 */
bool user_i2c_read(uint16_t hw_address, uint16_t reg_address, uint8_t num_bytes, char *resp_str);

/**
 ****************************************************************************************
 * @brief      Writes data to a register address of an I2C slave
 *
 * @param[in]  hw_address, HW address of I2C slave device
 * @param[in]  reg_address, Register address to write to
 * @param[in]  data, Data to write
 * @param[in]  remote, originator of the read command
 *
 * @return     void
 *****************************************************************************************
 */
void user_i2c_write(uint16_t hw_address, uint16_t reg_address, uint16_t wr_data);

#endif //_USER_I2C_H_
/// @} APP
