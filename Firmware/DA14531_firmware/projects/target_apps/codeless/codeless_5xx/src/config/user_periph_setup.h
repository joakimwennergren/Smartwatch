/**
 ****************************************************************************************
 *
 * @file user_periph_setup.h
 *
 * @brief Peripherals setup header file.
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

#ifndef _USER_PERIPH_SETUP_H_
#define _USER_PERIPH_SETUP_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"
#include "arch.h"
#include "da1458x_periph_setup.h"
#include "i2c_eeprom.h"
#include "uart.h"
/*
 * DEFINES
 ****************************************************************************************
 */

//*** <<< Use Configuration Wizard in Context Menu >>> ***

// <o> DK selection <0=> As in da1458x_periph_setup.h <1=> Basic <2=> Pro
// The expert configuration is not supported
#define HW_CONFIG                           (2)

#define HW_CONFIG_BASIC_DK                  ((HW_CONFIG==0 && SDK_CONFIG==1) || HW_CONFIG==1)
#define HW_CONFIG_PRO_DK                    ((HW_CONFIG==0 && SDK_CONFIG==2) || HW_CONFIG==2)



// <o> Flow Control selection <0=> HW RTS/CTS  <1=> NONE
#define FLOW_CONTROL_CONFIG                 (0)

#define CFG_UART_HW_FLOW_CTRL               (FLOW_CONTROL_CONFIG==0)
#define CFG_UART_NO_FLOW_CTRL               (FLOW_CONTROL_CONFIG==1)

#if CFG_UART_HW_FLOW_CTRL
#define UART_HW_FLOW_ENABLED                (1)
#else
#define UART_HW_FLOW_ENABLED                (0)
#endif

// <o> Baud Rate selection <1=> 9600 <2=> 19200 <3=> 38400 <4=> 57600 <5=> 115200  <6=> 230400 <7=> 460800 <8=> 921600
#if defined(__MIKROBUS2__)
    #define BAUDRATE_CONFIG                 (5)
#else
    #define BAUDRATE_CONFIG                 (4)
#endif

#define BAUDRATE_9K6                        (BAUDRATE_CONFIG==1)
#define BAUDRATE_19K2                       (BAUDRATE_CONFIG==2)
#define BAUDRATE_38K4                       (BAUDRATE_CONFIG==3)
#define BAUDRATE_57K6                       (BAUDRATE_CONFIG==4)
#define BAUDRATE_115K2                      (BAUDRATE_CONFIG==5)
#define BAUDRATE_230K4                      (BAUDRATE_CONFIG==6)
#define BAUDRATE_460K8                      (BAUDRATE_CONFIG==7)
#define BAUDRATE_921K6                      (BAUDRATE_CONFIG==8)

//*** <<< end of configuration section >>>    ***
#if BAUDRATE_9K6
    #define UART_SPS_BAUDRATE                UART_BAUDRATE_9600
    #define CFG_UART_SPS_BAUDRATE            104
    #define CFG_UART_SPS_FRAC_BAUDRATE       3
#endif

#if BAUDRATE_19K2
    #define UART_SPS_BAUDRATE                UART_BAUDRATE_19200
    #define CFG_UART_SPS_BAUDRATE            52
    #define CFG_UART_SPS_FRAC_BAUDRATE       1
#endif

#if BAUDRATE_38K4
    #define UART_SPS_BAUDRATE                UART_BAUDRATE_38400
    #define CFG_UART_SPS_BAUDRATE            26
    #define CFG_UART_SPS_FRAC_BAUDRATE       1
#endif

#if BAUDRATE_57K6
    #define UART_SPS_BAUDRATE                UART_BAUDRATE_57600
    #define CFG_UART_SPS_BAUDRATE            17
    #define CFG_UART_SPS_FRAC_BAUDRATE       6
#endif

#if BAUDRATE_115K2
    #define UART_SPS_BAUDRATE                UART_BAUDRATE_115200
    #define CFG_UART_SPS_BAUDRATE            8
    #define CFG_UART_SPS_FRAC_BAUDRATE       11
#endif

#if BAUDRATE_230K4
    #define UART_SPS_BAUDRATE                UART_BAUDRATE_230400
    #define CFG_UART_SPS_BAUDRATE            4
    #define CFG_UART_SPS_FRAC_BAUDRATE       5
#endif

#if BAUDRATE_460K8
    #define UART_SPS_BAUDRATE                UART_BAUDRATE_460800
    #define CFG_UART_SPS_BAUDRATE            2
    #define CFG_UART_SPS_FRAC_BAUDRATE       3
#endif

#if BAUDRATE_921K6
    #define UART_SPS_BAUDRATE                UART_BAUDRATE_921600
    #define CFG_UART_SPS_BAUDRATE            1
    #define CFG_UART_SPS_FRAC_BAUDRATE       1
#endif


#define UART_WAIT_BYTE_TIME                  (CFG_UART_SPS_BAUDRATE * 10)        // time in uSec
#if UART_SW_FLOW_ENABLED
    #define UART_WAIT_BYTE_COUNTER           (UART_WAIT_BYTE_TIME * 8) + 30      //convert in for loop counter
#else
    #define UART_WAIT_BYTE_COUNTER           (UART_WAIT_BYTE_TIME * 4) + 30      //convert in for loop counter
#endif

/****************************************************************************************/
/* UART2 configuration                                                                  */
/****************************************************************************************/
#ifdef CFG_PRINTF_UART2
    #define CODELESS_UART                    UART2
    #define CODELESS_UART2
#else
    #define CODELESS_UART                    UART1
    #define CODELESS_UART1
#endif


#define CODELESS_UARTx_BAUDRATE              UART_SPS_BAUDRATE
#define CODELESS_UARTx_DATABITS              UART_DATABITS_8
#define CODELESS_UARTx_PARITY                UART_PARITY_NONE
#define CODELESS_UARTx_STOPBITS              UART_STOPBITS_1


#if UART_HW_FLOW_ENABLED
    #define CODELESS_UARTx_AFCE              UART_AFCE_EN
#else
    #define CODELESS_UARTx_AFCE              UART_AFCE_DIS
#endif

#ifndef __DA14531__
    #define CODELESS_UARTx_FIFO              UART_FIFO_DIS
    #define CODELESS_UARTx_TX_FIFO_LEVEL     UART_TX_FIFO_LEVEL_0
    #define CODELESS_UARTx_RX_FIFO_LEVEL     UART_RX_FIFO_LEVEL_0
#else
    #define CODELESS_UARTx_FIFO              UART_FIFO_EN
    #define CODELESS_UARTx_TX_FIFO_LEVEL     UART_TX_FIFO_LEVEL_3
    #define CODELESS_UARTx_RX_FIFO_LEVEL     UART_RX_FIFO_LEVEL_0
#endif

#define DSPS_BAUD_RATE                       UART_SPS_BAUDRATE
#define DSPS_DATABITS                        UART_DATABITS_8
#define DSPS_PARITY                          UART_PARITY_NONE
#define DSPS_STOPBITS                        UART_STOPBITS_1
#define DSPS_AFCE                            UART_AFCE_DIS
#define DSPS_FIFO                            UART_FIFO_EN
#define DSPS_TX_FIFO_LEVEL                   UART_TX_FIFO_LEVEL_3
#define DSPS_RX_FIFO_LEVEL                   UART_RX_FIFO_LEVEL_3

#if !defined (__DA14531__)
    #define MAX_PIN_NUMBER                   (37)
#else
    #define MAX_PIN_NUMBER                   (12)
#endif

#if (UART_HW_FLOW_ENABLED) && !defined(USE_AT_FLOWCONTROL)
#if !defined (__DA14531__)
    #define GPIO_UARTx_RTS_PORT              GPIO_PORT_2
    #define GPIO_UARTx_RTS_PIN               GPIO_PIN_7
    #define GPIO_UARTx_CTS_PORT              GPIO_PORT_2
    #define GPIO_UARTx_CTS_PIN               GPIO_PIN_8

#else
    #define GPIO_UARTx_RTS_PORT              GPIO_PORT_0
    #if defined(__MIKROBUS2__)
        #define GPIO_UARTx_RTS_PIN           GPIO_PIN_4
    #else
        #define GPIO_UARTx_RTS_PIN           GPIO_PIN_7
    #endif
    #define GPIO_UARTx_CTS_PORT              GPIO_PORT_0
    #if defined(__MIKROBUS2__)
        #define GPIO_UARTx_CTS_PIN           GPIO_PIN_3
    #else
        #define GPIO_UARTx_CTS_PIN           GPIO_PIN_8
    #endif // __MIKROBUS2__
#endif
#endif

/****************************************************************************************/
/* Debugging configuration                                                              */
/****************************************************************************************/
/*Enable Disable Debug Pins */
#define DBG_PINS                            (0)
#if DBG_PINS

#if !defined (__DA14531__)
    #define DBG_PIN1_PORT                   GPIO_PORT_1
    #define DBG_PIN1_PIN                    GPIO_PIN_0

    #define DBG_PIN2_PORT                   GPIO_PORT_0
    #define DBG_PIN2_PIN                    GPIO_PIN_1
#else
    #define DBG_PIN1_PORT                   GPIO_PORT_0
    #define DBG_PIN1_PIN                    GPIO_PIN_8

    #define DBG_PIN2_PORT                   GPIO_PORT_0
    #define DBG_PIN2_PIN                    GPIO_PIN_9

#endif

#define DBG1_ON                             GPIO_SetActive(DBG_PIN1_PORT,DBG_PIN1_PIN)
#define DBG1_OFF                            GPIO_SetInactive(DBG_PIN1_PORT,DBG_PIN1_PIN)

#define DBG2_ON                             GPIO_SetActive(DBG_PIN2_PORT,DBG_PIN2_PIN)
#define DBG2_OFF                            GPIO_SetInactive(DBG_PIN2_PORT,DBG_PIN2_PIN)

#else

#define DBG1_ON
#define DBG1_OFF

#define DBG2_ON
#define DBG2_OFF

#endif

/****************************************************************************************/
/* I2C EEPROM configuration                                                             */
/****************************************************************************************/

#define I2C_EEPROM_SIZE                      0x20000         // EEPROM size in bytes
#define I2C_EEPROM_PAGE                      256             // EEPROM page size in bytes
#define I2C_SPEED_MODE                       I2C_FAST        // 1: standard mode (100 kbits/s), 2: fast mode (400 kbits/s)
#define I2C_ADDRESS_MODE                     I2C_7BIT_ADDR   // 0: 7-bit addressing, 1: 10-bit addressing
#define I2C_ADDRESS_SIZE                     I2C_2BYTES_ADDR // 0: 8-bit memory address, 1: 16-bit memory address, 3: 24-bit memory address

/****************************************************************************************/
/* SPI FLASH configuration                                                              */
/****************************************************************************************/

#ifdef CODELESS_585
    #define SPI_FLASH_DEFAULT_SIZE           (256 * 1024)    // SPI Flash memory size in bytes
#else
    #error "No configuration defined"
#endif
#define SPI_FLASH_DEFAULT_PAGE               256
#define SPI_SECTOR_SIZE                      4096

#if defined(__DA14586__)

    #define SPI_EN_GPIO_PORT                 GPIO_PORT_2
    #define SPI_EN_GPIO_PIN                  GPIO_PIN_3

    #define SPI_CLK_GPIO_PORT                GPIO_PORT_2
    #define SPI_CLK_GPIO_PIN                 GPIO_PIN_0

    #define SPI_DO_GPIO_PORT                 GPIO_PORT_2
    #define SPI_DO_GPIO_PIN                  GPIO_PIN_9

    #define SPI_DI_GPIO_PORT                 GPIO_PORT_2
    #define SPI_DI_GPIO_PIN                  GPIO_PIN_4

#elif defined(__DA14585__)

    #define SPI_EN_GPIO_PORT                 GPIO_PORT_0
    #define SPI_EN_GPIO_PIN                  GPIO_PIN_3

    #define SPI_CLK_GPIO_PORT                GPIO_PORT_0
    #define SPI_CLK_GPIO_PIN                 GPIO_PIN_0

    #define SPI_DO_GPIO_PORT                 GPIO_PORT_0
    #define SPI_DO_GPIO_PIN                  GPIO_PIN_6

    #define SPI_DI_GPIO_PORT                 GPIO_PORT_0
    #define SPI_DI_GPIO_PIN                  GPIO_PIN_5

#elif defined(__DA14531__)

    #define SPI_EN_GPIO_PORT                 GPIO_PORT_0
    #define SPI_EN_GPIO_PIN                  GPIO_PIN_1

    #define SPI_CLK_GPIO_PORT                GPIO_PORT_0
    #define SPI_CLK_GPIO_PIN                 GPIO_PIN_4

    #define SPI_DO_GPIO_PORT                 GPIO_PORT_0
    #define SPI_DO_GPIO_PIN                  GPIO_PIN_0

    #define SPI_DI_GPIO_PORT                 GPIO_PORT_0
    #define SPI_DI_GPIO_PIN                  GPIO_PIN_3
#else
    #error No configuration defined
#endif

/****************************************************************************************/
/* UART2 pin configuration (debug print console)                                        */
/****************************************************************************************/

#ifdef CODELESS_UART1
    #define IO_FUNC_UART_TX                  IO_FUNC_UART1_TX
    #define IO_FUNC_UART_RX                  IO_FUNC_UART1_RX
#endif

#ifdef CODELESS_UART2
    #define IO_FUNC_UART_TX                  IO_FUNC_UART2_TX
    #define IO_FUNC_UART_RX                  IO_FUNC_UART2_RX
#endif

#if !defined (__DA14531__)
    #define UARTx_TX_GPIO_PORT               GPIO_PORT_2
    #define UARTx_TX_GPIO_PIN                GPIO_PIN_6
    #define UARTx_RX_GPIO_PORT               GPIO_PORT_2
    #define UARTx_RX_GPIO_PIN                GPIO_PIN_5
#else
    #define UARTx_TX_GPIO_PORT               GPIO_PORT_0
#if defined(__MIKROBUS2__)
    #define UARTx_TX_GPIO_PIN                GPIO_PIN_0
#else
    #define UARTx_TX_GPIO_PIN                GPIO_PIN_6
#endif

#define UARTx_RX_GPIO_PORT                   GPIO_PORT_0
#if defined(__MIKROBUS2__)
    #define UARTx_RX_GPIO_PIN                GPIO_PIN_1
#else
    #define UARTx_RX_GPIO_PIN                GPIO_PIN_5
#endif // __MIKROBUS2__
#endif // !defined(__DA14531__)

#if UART_HW_FLOW_ENABLED
    #define SLEEP_WKUP_PORT                  GPIO_UARTx_CTS_PORT
    #define SLEEP_WKUP_PIN                   GPIO_UARTx_CTS_PIN
#else
    #define SLEEP_WKUP_PORT                  UARTx_RX_GPIO_PORT
    #define SLEEP_WKUP_PIN                   UARTx_RX_GPIO_PIN
#endif

//I2C PINS
#if defined(__DA14531__) && defined(__MIKROBUS2__)
    #define GPIO_I2C_SCL_PORT                GPIO_PORT_0
    #define GPIO_I2C_SCL_PIN                 GPIO_PIN_2
    #define GPIO_I2C_SDA_PORT                GPIO_PORT_0
    #define GPIO_I2C_SDA_PIN                 GPIO_PIN_8
#endif

/****************************************************************************************/
/* LED and button configuration                                                         */
/****************************************************************************************/

#if HW_CONFIG_BASIC_DK
    #warning "UNTESTED CONFIG"
    #define GPIO_ALERT_LED_PORT              GPIO_PORT_1
    #define GPIO_ALERT_LED_PIN               GPIO_PIN_0

    #define USE_PUSH_BUTTON                  0
    #define GPIO_BUTTON_PORT                 GPIO_PORT_0
    #define GPIO_BUTTON_PIN                  GPIO_PIN_6

    #define USE_BAT_LEVEL_ALERT              0
    #define GPIO_BAT_LED_PORT                GPIO_PORT_1
    #define GPIO_BAT_LED_PIN                 GPIO_PIN_2

#elif HW_CONFIG_PRO_DK
    #define GPIO_ALERT_LED_PORT              GPIO_PORT_1
    #define GPIO_ALERT_LED_PIN               GPIO_PIN_0

    #define USE_PUSH_BUTTON                  1
    #define GPIO_BUTTON_PORT                 GPIO_PORT_0 // TODO: fix
    #define GPIO_BUTTON_PIN                  GPIO_PIN_0  // TODO: fix

    #define USE_BAT_LEVEL_ALERT              0
    #define GPIO_BAT_LED_PORT                GPIO_PORT_1
    #define GPIO_BAT_LED_PIN                 GPIO_PIN_2

#else // (other configuration)
#endif

/***************************************************************************************/
/* Production debug output configuration                                               */
/***************************************************************************************/
#if PRODUCTION_DEBUG_OUTPUT
    #define PRODUCTION_DEBUG_PORT            GPIO_PORT_2
    #define PRODUCTION_DEBUG_PIN             GPIO_PIN_5
#endif
/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Enable pad and peripheral clocks assuming that peripheral power domain
 *        is down. The UART and SPI clocks are set.
 ****************************************************************************************
 */
void periph_init(void);

/**
 ****************************************************************************************
 * @brief Each application reserves its own GPIOs here.
 ****************************************************************************************
 */
void GPIO_reservations(void);

/**
 ****************************************************************************************
 * @brief Set gpio port function mode
 ****************************************************************************************
 */
void set_pad_functions(void);
void set_commmand_uart_pins(void);

#endif // _USER_PERIPH_SETUP_H_
