/**
 ****************************************************************************************
 *
 * @file user_periph_setup.c
 *
 * @brief Peripherals setup and initialization.
 *
 * Copyright (C) 2012-2024 Renesas Electronics Corporation and/or its affiliates.
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
#include "rwip_config.h"             // SW configuration
#include "datasheet.h"
#include "user_periph_setup.h"       // peripheral configuration
#include "gpio.h"
#include "uart.h"                    // UART initialization
#include "system_library.h"          // patch func
#include "user_cmd_interpreter.h"
#include "user_codeless_env.h"
#include "syscntl.h"
#include "user_utility_functions.h"
#include "user_profiles_config.h"
#include "user_custs_sps.h"
#include "user_spi_command_interface.h"


#if defined (CFG_SPI_FLASH_ENABLE)
#include "spi.h"
#include "spi_flash.h"
#endif

/**
 ****************************************************************************************
 * @brief Each application reserves its own GPIOs here.
 *
 * @return void
 ****************************************************************************************
 */

#if DEVELOPMENT_DEBUG

void GPIO_reservations(void)
{
/*
 * Globally reserved GPIOs reservation
 */

/*
 * Application specific GPIOs reservation. Used only in Development mode (#if DEVELOPMENT_DEBUG)
 *
 * i.e.
 * RESERVE_GPIO(DESCRIPTIVE_NAME, GPIO_PORT_0, GPIO_PIN_1, PID_GPIO);    //Reserve P_01 as Generic Purpose I/O
 */
#ifdef CFG_PRINTF_UART2
    RESERVE_GPIO(UART2_TX, UART2_TX_GPIO_PORT, UART2_TX_GPIO_PIN, PID_UART2_TX);
    RESERVE_GPIO(UART2_RX, UART2_RX_GPIO_PORT, UART2_RX_GPIO_PIN, PID_UART2_RX);
#endif
}
#endif //DEVELOPMENT_DEBUG

/**
 ****************************************************************************************
 * @brief Initialize the command uart RX/TX Pins
 ****************************************************************************************
 */

void set_commmand_uart_pins(void)
{
    #ifdef CFG_PRINTF_UART2
    GPIO_ConfigurePin(UARTx_TX_GPIO_PORT, UARTx_TX_GPIO_PIN, OUTPUT, PID_UART2_TX, false);
    if(codeless_env.sleep_active==0)
        GPIO_ConfigurePin(UARTx_RX_GPIO_PORT, UARTx_RX_GPIO_PIN, INPUT, PID_UART2_RX, false);
    else
        GPIO_ConfigurePin(UARTx_RX_GPIO_PORT, UARTx_RX_GPIO_PIN, INPUT, PID_GPIO, true);
    #else
    GPIO_ConfigurePin(UARTx_TX_GPIO_PORT, UARTx_TX_GPIO_PIN, OUTPUT, PID_UART1_TX, false);
    if(codeless_env.sleep_active==0)
        GPIO_ConfigurePin(UARTx_RX_GPIO_PORT, UARTx_RX_GPIO_PIN, INPUT, PID_UART1_RX, false);
    else
        /*If we dont deactivate this during sleep a break condition may cause UART ERROR */
        GPIO_ConfigurePin(UARTx_RX_GPIO_PORT, UARTx_RX_GPIO_PIN, INPUT, PID_GPIO, true);
     #endif
}

/**
 ****************************************************************************************
 * @brief Map port pins. The UART and SPI port pins and GPIO ports are mapped.
 ****************************************************************************************
 */
#if defined(USE_AT_FLOWCONTROL) && !(UART_HW_FLOW_ENABLED)
#error "USE_AT_FLOWCONTROL needs HW Flow Control Enabled"
#endif
void set_pad_functions(void)        // set gpio port function mode
{
/*
 * Configure application ports.
 * i.e.
 * GPIO_ConfigurePin( GPIO_PORT_0, GPIO_PIN_1, OUTPUT, PID_GPIO, false ); // Set P_01 as Generic purpose Output
 */

#ifdef __DA14586__
    // disallow spontaneous flash wake-up
    GPIO_ConfigurePin(GPIO_PORT_2, GPIO_PIN_3, OUTPUT, PID_GPIO, true);
#endif

    set_commmand_uart_pins();

#if (UART_HW_FLOW_ENABLED) && !defined(USE_AT_FLOWCONTROL)

    #ifdef CODELESS_UART2
    #error "UART2 does not support HW Flow Control. Select UART1 or disable HW Flow Control"
    #else
    #if defined(USE_AT_BINARY_MODE)
        if ((codeless_env.sleep_active == 0) && (codeless_env.binary_mode == 0))
    #else
        if (codeless_env.sleep_active == 0) // codeless_env.binary mode field does not exist if not in binary mode
    #endif
        {
            GPIO_ConfigurePin( GPIO_UARTx_RTS_PORT, GPIO_UARTx_RTS_PIN, OUTPUT, PID_UART1_RTSN, true );
            uart_sps_flow_off(true);
        }
        else
        {
            GPIO_ConfigurePin( GPIO_UARTx_RTS_PORT, GPIO_UARTx_RTS_PIN, OUTPUT, PID_GPIO, true );
        }
        
        if(codeless_env.sleep_active==0)
            GPIO_ConfigurePin( GPIO_UARTx_CTS_PORT, GPIO_UARTx_CTS_PIN, INPUT, PID_UART1_CTSN, false );
        else
            GPIO_ConfigurePin(GPIO_UARTx_CTS_PORT, GPIO_UARTx_CTS_PIN, INPUT, PID_GPIO, true );
    #endif // CODELESS_UART2
#endif //(UART_HW_FLOW_ENABLED) && !defined(USE_AT_FLOWCONTROL)


  // Go through all the IOs
  for(uint8_t i=0; i<MAX_PIN_NUMBER; i++)
  {
    #if defined(__DA14585__) || defined(__DA14586__)
    GPIO_PORT port_number = (GPIO_PORT)(i / 10);
    GPIO_PIN pin_number = (GPIO_PIN)(i % 10);
    #else
    GPIO_PORT port_number = (GPIO_PORT)0;
    GPIO_PIN pin_number = (GPIO_PIN)(i);
    #endif
    io_func_t func = codeless_env.port_configuration[i];



    // Set port configuration accordingly
    if ((func == IO_FUNC_INPUT) || (func == IO_FUNC_INPUT_PULLUP) || (func == IO_FUNC_INPUT_PULLDOWN))
    {
        // Standard input port, input port with pull-up resistor, Input port with pull-down resistor
        GPIO_ConfigurePin(port_number, pin_number, (GPIO_PUPD)((func-1)*0x100), PID_GPIO, false );
    }
    else if(func == IO_FUNC_OUTPUT)
    {
        // Output port must be set according to the state it was in before sleep
        GPIO_ConfigurePin(port_number, pin_number, OUTPUT, PID_GPIO, codeless_env.port_io_state[i]);
    }

    else if((func == IO_FUNC_ANALOG_INPUT || func == IO_FUNC_ANALOG_INPUT_ATT3) && ((uint8_t)port_number == 0) && ((uint8_t)pin_number <= 3))
      // Analog input port
      GPIO_ConfigurePin(port_number, pin_number, INPUT, PID_ADC, false );

    else if(func == IO_FUNC_I2C_CLOCK)
    {
      // I2C clock output port
    #if defined(__DA14531__) && defined(__MIKROBUS2__)
        GPIO_ConfigurePin(GPIO_I2C_SCL_PORT, GPIO_I2C_SCL_PIN, OUTPUT, PID_I2C_SCL, false );
    #else
        GPIO_ConfigurePin(port_number, pin_number, OUTPUT, PID_I2C_SCL, false );
    #endif
    }

    else if(func == IO_FUNC_I2C_DATA)
    {
      // I2C data port
    #if defined(__DA14531__) && defined(__MIKROBUS2__)
        GPIO_ConfigurePin(GPIO_I2C_SDA_PORT, GPIO_I2C_SDA_PIN, OUTPUT, PID_I2C_SDA, false );
    #else
        GPIO_ConfigurePin(port_number, pin_number, OUTPUT, PID_I2C_SDA, false );
    #endif
    }
    #ifdef USE_AT_FLOWCONTROL
    else if(func == IO_FUNC_UART1_RTS)
    {
        if(codeless_env.flow_control_enabled)
        {
            #if defined(USE_AT_BINARY_MODE)
            if((codeless_env.sleep_active==0)&&(codeless_env.binary_mode==0))
            #else
            if(codeless_env.sleep_active==0) // codeless_env.binary mode field does not exist if not in binary mode
            #endif
            {
                GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT, PID_UART1_RTSN, true );
                uart_sps_flow_off(true);
            }
            else
            {
                GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, OUTPUT, PID_GPIO, true );
            }
        }
    }
    else if(func == IO_FUNC_UART1_CTS)
    {
        if(codeless_env.flow_control_enabled)
        {
            if(codeless_env.sleep_active==0)
                GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, INPUT, PID_UART1_CTSN, false );
            else
                GPIO_ConfigurePin((GPIO_PORT)port_number, (GPIO_PIN)pin_number, INPUT, PID_GPIO, true );
        }
    }
    #endif
  }
    #ifdef DBG_PIN1_PORT
    GPIO_ConfigurePin( DBG_PIN1_PORT, DBG_PIN1_PIN, OUTPUT, PID_GPIO, false );
    #warning "DBG PINS ARE ENABLED FLWO CONTROL WONT WORK"
    #endif
    #ifdef DBG_PIN2_PORT
    GPIO_ConfigurePin( DBG_PIN2_PORT, DBG_PIN2_PIN, OUTPUT, PID_GPIO, false );
    #warning "DBG PINS ARE ENABLED FLWO CONTROL WONT WORK"
    #endif

// This is the point where the flash SPI pins are configured.

#if (BLE_SUOTA_RECEIVER) || defined (CFG_SPI_FLASH_ENABLE)
    GPIO_ConfigurePin(SPI_EN_GPIO_PORT,  SPI_EN_GPIO_PIN,  OUTPUT, PID_SPI_EN,  true);
    GPIO_ConfigurePin(SPI_CLK_GPIO_PORT, SPI_CLK_GPIO_PIN, OUTPUT, PID_SPI_CLK, false);
    GPIO_ConfigurePin(SPI_DO_GPIO_PORT,  SPI_DO_GPIO_PIN,  OUTPUT, PID_SPI_DO,  false);
    GPIO_ConfigurePin(SPI_DI_GPIO_PORT,  SPI_DI_GPIO_PIN,  INPUT,  PID_SPI_DI,  false);


#endif

#if (CMD_LOCAL_SOURCE == CMD_SPI)
    setup_spi_command_interface_pins();
    setup_spihddr_gpios();
#endif
}



/**
 ****************************************************************************************
 * @brief Enable pad and peripheral clocks assuming that peripheral power domain
 *        is down. The UART and SPI clocks are set.
 * @return void
 ****************************************************************************************
 */
void periph_init(void)
{
#if defined (__DA14531__)
    // Disable HW Reset functionality of P0_0
    GPIO_Disable_HW_Reset();
    // In Boost mode enable the DCDC converter to supply VBAT_HIGH for the used GPIOs
    syscntl_dcdc_turn_on_in_boost(SYSCNTL_DCDC_LEVEL_3V0);
#else
    // Power up peripherals' power domain
    SetBits16(PMU_CTRL_REG, PERIPH_SLEEP, 0);
    while (!(GetWord16(SYS_STAT_REG) & PER_IS_UP));
    SetBits16(CLK_16M_REG, XTAL16_BIAS_SH_ENABLE, 1);
#endif

    //rom patch
    patch_func();

    // Set default baud rate
#if defined(USE_AT_BAUD)
    if (codeless_env.baud_rate == 0)
    {
        codeless_env.baud_rate = UART_SPS_BAUDRATE;
    }
#endif

    #ifdef USE_AT_BINARY_MODE
    if (codeless_env.sleep_active==0)
    {
        if (codeless_env.binary_mode==false)
        {

            user_set_uart_to_codeless_settings();

#if defined (__DA14585__) || defined(__DA14586__)
            while (uart_data_ready_getf(CODELESS_UART))
            {
                uart_read_byte(CODELESS_UART);
            }
            for (int i=0;i<2500;i++)
            {
                __asm("nop");
            }
#endif
            console_env.parser_flag = CHAR_PARSER_ACTIVE;
            console_env.input_cmd_char_index = 0;
            user_character_parser_start();
        }
        else
        {
            //Using SPS initialization is done inside on_ble_powered
        }
    }
    #else
    if (codeless_env.sleep_active==0)
    {
        user_set_uart_to_codeless_settings();
        console_env.parser_flag = CHAR_PARSER_ACTIVE;
        console_env.input_cmd_char_index = 0;
        user_character_parser_start();
    }
    #endif

#if defined(CFG_PRF_SUOTAR) || defined(CFG_SPI_FLASH_ENABLE)
#if defined(CFG_SPI_STATIC_CONFIGURATION)
    spi_initialize(NULL);
#else
    spi_cfg_t spi_flash_cfg = { .spi_ms = SPI_MS_MODE_MASTER,
                                .spi_cp = SPI_CP_MODE_0,
                                .spi_speed = SPI_SPEED_MODE_4MHz,
                                .spi_wsz = SPI_MODE_8BIT,
                                .spi_cs = SPI_CS_0,
                                .cs_pad.port = SPI_EN_GPIO_PORT,
                                .cs_pad.pin = SPI_EN_GPIO_PIN,
                        #if defined (__DA14531__)
                                .spi_capture = SPI_MASTER_EDGE_CAPTURE
                        #endif
                                };

    spi_initialize(&spi_flash_cfg);
#endif // CFG_SPI_STATIC_CONFIGURATION
#endif // CFG_PRF_SUOTAR || CFG_SPI_FLASH_ENABLE

    set_pad_functions();
    // Set pad functionality
    // Enable the pads
    GPIO_set_pad_latch_en(true);
}
