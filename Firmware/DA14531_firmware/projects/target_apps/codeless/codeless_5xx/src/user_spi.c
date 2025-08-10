/**
 ****************************************************************************************
 *
 * @file user_spi.c
 *
 * @brief Functions for handling the spi commands
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
#include "user_spi.h"
#include "user_codeless_env.h"
#include "user_utility_functions.h"
#include "arch_console.h"

#if defined (USE_AT_SPI)
/****************************************************************************************
 * FUNCTIONS
 ****************************************************************************************/


AT_CONSOLE_ERROR_TYPE_t validate_spi_wr_and_tr_arguments(const char * cmd_line_str)
{
    AT_CONSOLE_ERROR_TYPE_t error_status=AT_CONSOLE_NO_ERROR;
    do
    {
        //Check for valid hardware configuration
        if (! user_is_spi_hw_valid())
        {
            // HW not properly set
            error_status = AT_CONSOLE_ERROR_2;
            break;
        }
        const char * hex_string=cmd_line_str;

        //Check that the input string is not too long
        if ( strlen(hex_string) > CONSOLE_MAX_SPI_STRING_LENGTH || strlen(hex_string) < CONSOLE_MIN_SPI_STRING_LENGTH)
        {
            // String either too long or too short
            error_status = AT_CONSOLE_ERROR_13; // AT command argument out of range
            break;
        }
        // if it has a prefix 0x or 0X check that there are at least
        // two additional characters as well
        if (strncmp(hex_string,"0x",2) == 0 || strncmp(hex_string,"0X",2) == 0)
        {
            if (strlen(hex_string) < 4)
            {
                error_status = AT_CONSOLE_ERROR_13; // AT command argument out of range
                break;
            }
        }
        // Check that an even number of hex characters is given.
        if (strlen(hex_string) % 2 !=0)
        {

            error_status = AT_CONSOLE_ERROR_13; // AT command argument out of range
            break;
        }
    }
    while (0);
    return error_status;
}

bool user_is_spi_hw_valid(void)
{
    // Default to false
    bool is_mosi_found = false;
    bool is_miso_found = false;
    bool is_clk_found = false;
    bool is_cs_found = false;

    // Run through all IO pins in the pin configuration array
    uint8_t num_of_pins_in_conf_array=sizeof(codeless_env.port_configuration)/sizeof(codeless_env.port_configuration[0]);
    for (uint8_t j = 0; j < num_of_pins_in_conf_array; j++)
    {
        // Check if mosi is configured
        if (IO_FUNC_SPI_MOSI == codeless_env.port_configuration[j])
        {
            is_mosi_found = true;
        }

        // Check if miso is configured
        if (IO_FUNC_SPI_MISO == codeless_env.port_configuration[j])
        {
            is_miso_found = true;
        }

        // Check if clock is configured
        if (IO_FUNC_SPI_CLK == codeless_env.port_configuration[j])
        {
            is_clk_found = true;
        }

        // Check if cs is configured
        if (IO_FUNC_SPI_CS == codeless_env.port_configuration[j])
        {
            is_cs_found = true;
        }
    }
    // We do not perform a check for multiple pins per category

    bool is_spi_ok = is_mosi_found && is_miso_found && is_clk_found && is_cs_found;
    return is_spi_ok;
}


void user_spi_config(SPI_SPEED_MODE_CFG speed_cfg,SPI_CP_MODE_CFG pol_phase_cfg,SPI_WSZ_MODE_CFG word_size_cfg)
{
    // Run through all IO pins in the pin configuration array to find the CS pin
    uint8_t num_of_pins_in_conf_array=sizeof(codeless_env.port_configuration)/sizeof(codeless_env.port_configuration[0]);

    // TODO: Create a dedicated array to hold SPI information

    uint8_t port=0;
    for (uint8_t j=0; j < num_of_pins_in_conf_array ; j++)
    {
        if (IO_FUNC_SPI_CS==codeless_env.port_configuration[j])
        {
            port=j;
            break;
        }
    }
    // Resolve port and pin numbers from codeless_env.port_configuration
    #if   defined(__DA14585__) || defined(__DA14586__)
    uint8_t port_number = port / 10;
    uint8_t pin_number = port % 10;
    #elif   defined(__DA14531__)
    uint8_t port_number = 0;
    uint8_t pin_number = port;
    #endif

    spi_cfg_t spi_cfg;

    memset(&spi_cfg,(int)0,sizeof(spi_cfg));
    spi_cfg.spi_ms      = SPI_MS_MODE_MASTER;
    spi_cfg.spi_cp      = pol_phase_cfg;
    spi_cfg.spi_speed   = speed_cfg;
    spi_cfg.spi_wsz     = word_size_cfg;
    spi_cfg.spi_cs      = SPI_CS_0;
    spi_cfg.spi_irq     = SPI_IRQ_DISABLED;
    spi_cfg.cs_pad.port = (GPIO_PORT)port_number;
    spi_cfg.cs_pad.pin  = (GPIO_PIN)pin_number;

    spi_initialize(&spi_cfg);
}

void user_spi_wr(const uint8_t * data, uint8_t number_of_bytes)
{
    if ((data !=NULL) && (number_of_bytes>0))
    {
        spi_cs_low();
        spi_send(data, number_of_bytes, SPI_OP_BLOCKING);
        spi_cs_high();
    }
}

void user_spi_rd(uint8_t * data, uint8_t number_of_bytes)
{
    if ((data !=NULL) && (number_of_bytes>0))
    {
        spi_cs_low();
        spi_receive(data, number_of_bytes, SPI_OP_BLOCKING);
        spi_cs_high();
    }
}

void user_spi_tr(const uint8_t *data_out, uint8_t *data_in, uint8_t number_of_bytes)
{
    if ((data_in !=NULL) && (data_out !=NULL) && (number_of_bytes>0))
    {
        spi_cs_low();
        spi_transfer(data_out, data_in, number_of_bytes, SPI_OP_BLOCKING);
        spi_cs_high();
    }
}

#endif // USE_AT_SPI

/// @} APP
