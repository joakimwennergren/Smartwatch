/**
 ****************************************************************************************
 *
 * @file user_spi.h
 *
 * @brief user_spi header file.
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

#ifndef _USER_SPI_H_
#define _USER_SPI_H_

#include "spi.h"
#include "app_api.h"
#include "user_at_console.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define CONSOLE_MAX_SPI_STRING_LENGTH 64 // 64 hex chars -> 32 bytes
#define CONSOLE_MIN_SPI_STRING_LENGTH  2 //  2 hex chars ->  1 byte
/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief      Performs a preliminary check on the string argument specified for the
 *             spi write and spi transfer commands
 * @return     an error depending on the verification
 ****************************************************************************************
 */
AT_CONSOLE_ERROR_TYPE_t validate_spi_wr_and_tr_arguments(const char * cmd_line_str);

/**
 ****************************************************************************************
 * @brief      Checks if spi pin configuration is valid
 *
 * @return     true if configuration is valid false otherwise
 ****************************************************************************************
 */
bool user_is_spi_hw_valid(void);

/**
 ****************************************************************************************
 * @brief      Configure the spi interface
 *
 * @param[in]  speed_cfg, the spi speed configuration
 * @param[in]  pol_phase_cfg, spi polarity and phase configuration
 * @param[in]  word_size_cfg, spi word size configuration
 *
 * @return     void
 ****************************************************************************************
 */
void user_spi_config(SPI_SPEED_MODE_CFG speed_cfg,SPI_CP_MODE_CFG pol_phase_cfg,SPI_WSZ_MODE_CFG word_size_cfg);

/**
 ****************************************************************************************
 * @brief      Write data to the spi interface
 *
 * @param[in]  data, the data to send
 * @param[in]  num, number of bytes to send
 *
 * @return     void
 *****************************************************************************************
*/

void user_spi_wr(const uint8_t *data,uint8_t number_of_bytes);

/**
 ****************************************************************************************
 * @brief      Read data from the spi interface
 *
 * @param[in]  data, the data to read
 * @param[in]  num, number of bytes to read
 *
 * @return     void
 *****************************************************************************************
*/

void user_spi_rd(uint8_t * data,uint8_t number_of_bytes);

/**
 ****************************************************************************************
 * @brief      Transfer data through the spi interface - write/read
 *
 * @param[out] data_out, the data send to the spi interface
 * @param[in]  data_in, the data to read back through the spi interface
 * @param[in]  number_of_bytes, number of bytes to write/read
 *
 * @return     void
 *****************************************************************************************
*/

void user_spi_tr(const uint8_t *data_out, uint8_t *data_in, uint8_t number_of_bytes);

#endif //_USER_I2C_H_
/// @} APP
