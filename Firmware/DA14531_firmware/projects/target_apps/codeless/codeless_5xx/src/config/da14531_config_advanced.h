/**
 ****************************************************************************************
 *
 * @file da14531_config_advanced.h
 *
 * @brief Advanced compile configuration file.
 *
 * Copyright (C) 2017-2024 Renesas Electronics Corporation and/or its affiliates.
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

#ifndef _DA14531_CONFIG_ADVANCED_H_
#define _DA14531_CONFIG_ADVANCED_H_

#include "da14531_config_basic.h"
#include "da1458x_stack_config.h"

/****************************************************************************************************************/
/* Low Power clock selection.                                                                                   */
/*      -LP_CLK_XTAL32      External XTAL32K oscillator                                                         */
/*      -LP_CLK_RCX20       Internal RCX clock                                                                  */
/*      -LP_CLK_FROM_OTP    Use the selection in the corresponding field of OTP Header                          */
/****************************************************************************************************************/
#define CFG_LP_CLK              LP_CLK_RCX20

/****************************************************************************************************************/
/* Periodic wakeup period to poll GTL iface. Time in msec.                                                      */
/****************************************************************************************************************/
#define CFG_MAX_SLEEP_DURATION_PERIODIC_WAKEUP_MS                  500  // 0.5s

/****************************************************************************************************************/
/* Periodic wakeup period if GTL iface is not enabled. Time in msec.                                            */
/****************************************************************************************************************/
#define CFG_MAX_SLEEP_DURATION_EXTERNAL_WAKEUP_MS                  10000  // 10s

/****************************************************************************************************************/
/* Wakeup from external processor running host application.                                                     */
/****************************************************************************************************************/
#undef CFG_EXTERNAL_WAKEUP

/****************************************************************************************************************/
/* Wakeup external processor when a message is sent to GTL                                                      */
/****************************************************************************************************************/
#undef CFG_WAKEUP_EXT_PROCESSOR

/****************************************************************************************************************/
/* Enables True Random Number Generator. A true random number, generated at system initialization, is used to   */
/* seed any random number generator (C standard library, ChaCha20, etc.).                                       */
/****************************************************************************************************************/
#define CFG_TRNG

/****************************************************************************************************************/
/* Secure connections support.                                                                                  */
/* If the secure connections mode is to be used the macro must be defined. The secure connections mode uses     */
/* private/public keys which have been created based on the Elliptic-curve Diffie-Hellman (ECDH) protocol.      */
/* Note for DA14585/586/531:                                                                                    */
/* If the macro is defined, the ECDH keys will be created only once after the system start-up. If the legacy    */
/* pairing is to be used, it is recommended to undefine the macro in order to gain faster start-up time and     */
/* reduce the RAM footprint.                                                                                    */
/* Note for DA14531-01:                                                                                         */
/* The ECDH keys are always created after a pairing request. If the legacy pairing is to be used, it is         */
/* recommended to undefine the macro in order to reduce the RAM footprint.                                      */
/****************************************************************************************************************/
#define CFG_ENABLE_SMP_SECURE

/****************************************************************************************************************/
/* Uses ChaCha20 random number generator instead of the C standard library random number generator.             */
/****************************************************************************************************************/
#undef CFG_USE_CHACHA20_RAND

/****************************************************************************************************************/
/* Custom heap sizes                                                                                            */
/****************************************************************************************************************/
#define DB_HEAP_SZ              (1020)
#define MSG_HEAP_SZ             (2048)
#if defined(OUTBOUND_CHAR_QUEUE)
#define ENV_HEAP_SZ              (832)
#endif

/****************************************************************************************************************/
/* NVDS configuration                                                                                           */
/* - CFG_NVDS_TAG_BD_ADDRESS            Default bdaddress. If bdaddress is written in OTP header this value is  */
/*                                      ignored                                                                 */
/* - CFG_NVDS_TAG_LPCLK_DRIFT           Low power clock drift. Permitted values in ppm are:                     */
/*      + DRIFT_20PPM                                                                                           */
/*      + DRIFT_30PPM                                                                                           */
/*      + DRIFT_50PPM                                                                                           */
/*      + DRIFT_75PPM                                                                                           */
/*      + DRIFT_100PPM                                                                                          */
/*      + DRIFT_150PPM                                                                                          */
/*      + DRIFT_250PPM                                                                                          */
/*      + DRIFT_500PPM                  Default value (500 ppm)                                                 */
/* - CFG_NVDS_TAG_BLE_CA_TIMER_DUR      Channel Assessment Timer duration (Multiple of 10ms)                    */
/* - CFG_NVDS_TAG_BLE_CRA_TIMER_DUR     Channel Reassessment Timer duration (Multiple of CA timer duration)     */
/* - CFG_NVDS_TAG_BLE_CA_MIN_RSSI       Minimum RSSI Threshold                                                  */
/* - CFG_NVDS_TAG_BLE_CA_NB_PKT         Number of packets to receive for statistics                             */
/* - CFG_NVDS_TAG_BLE_CA_NB_BAD_PKT     Number  of bad packets needed to remove a channel                       */
/****************************************************************************************************************/
#define CFG_NVDS_TAG_BD_ADDRESS             {0x05, 0x00, 0xF4, 0x35, 0x23, 0x48}

#define CFG_NVDS_TAG_LPCLK_DRIFT            DRIFT_500PPM
#define CFG_NVDS_TAG_BLE_CA_TIMER_DUR       2000
#define CFG_NVDS_TAG_BLE_CRA_TIMER_DUR      6
#define CFG_NVDS_TAG_BLE_CA_MIN_RSSI        0x40
#define CFG_NVDS_TAG_BLE_CA_NB_PKT          100
#define CFG_NVDS_TAG_BLE_CA_NB_BAD_PKT      50

/****************************************************************************************************************/
/* Enables the logging of heap memories usage. The feature can be used in development/debug mode.               */
/* Application must be executed in Keil debugger environment and "da14531.lib" must be replaced with            */
/* "da14531_with_heap_logging.lib" in project structure under sdk_arch. Developer must stop execution           */
/* and type disp_heaplog in debugger's command window. Heap memory statistics will be displayed on window       */
/****************************************************************************************************************/
#undef CFG_LOG_HEAP_USAGE

/****************************************************************************************************************/
/* Enables the BLE statistics measurement feature.                                                              */
/****************************************************************************************************************/
#undef CFG_BLE_METRICS

/****************************************************************************************************************/
/* Output the Hardfault arguments to serial/UART interface.                                                     */
/****************************************************************************************************************/
#undef CFG_PRODUCTION_DEBUG_OUTPUT

/****************************************************************************************************************/
/* Maximum supported TX data packet length (supportedMaxTxOctets value, as defined in 4.2 Specification).       */
/* Range: 27 - 251 octets.                                                                                      */
/* NOTE 1: Even number of octets are not supported. A selected even number will be automatically converted to   */
/*         the next odd one.                                                                                    */
/* NOTE 2: The supportedMaxTxTime value is automatically calculated by the ROM code, according to the following */
/*         equation:                                                                                            */
/*             supportedMaxTxTime = (supportedMaxTxOctets + 11 + 3 ) * 8                                        */
/*         Range: 328 - 2120 usec.                                                                              */
/****************************************************************************************************************/
#define CFG_MAX_TX_PACKET_LENGTH        (69)

/****************************************************************************************************************/
/* Maximum supported RX data packet length (supportedMaxRxOctets value, as defined in 4.2 Specification).       */
/* Range: 27 - 251 octets.                                                                                      */
/* NOTE 1: Even number of octets are not supported. A selected even number will be automatically converted to   */
/*         the next odd one.                                                                                    */
/* NOTE 2: The supportedMaxRxTime value is automatically calculated by the ROM code, according to the following */
/*         equation:                                                                                            */
/*             supportedMaxRxTime = (supportedMaxRxOctets + 11 + 3 ) * 8                                        */
/*         Range: 328 - 2120 usec.                                                                              */
/****************************************************************************************************************/
#define CFG_MAX_RX_PACKET_LENGTH        (69)

/****************************************************************************************************************/
/* Select external application/host transport layer:                                                            */
/*     - 0 = GTL (auto)                                                                                         */
/*     - 1 = HCI (auto)                                                                                         */
/*     - 8 = GTL (fixed)                                                                                        */
/*     - 9 = HCI (fixed)                                                                                        */
/****************************************************************************************************************/
#define CFG_USE_H4TL                    (0)

/****************************************************************************************************************/
/* Duplicate filter max value for the scan report list. The maximum value shall be 100.                         */
/****************************************************************************************************************/
#define CFG_BLE_DUPLICATE_FILTER_MAX    (10)

/****************************************************************************************************************/
/* Duplicate filter flag for the scan report list. This flag controls what will be reported if the              */
/* CFG_BLE_DUPLICATE_FILTER_MAX number is exceeded.                                                             */
/*     - If the flag is defined, the extra devices are considered to be in the list and will not be reported.   */
/****************************************************************************************************************/
#undef CFG_BLE_DUPLICATE_FILTER_FOUND

/****************************************************************************************************************/
/* Resolving list maximum size.                                                                                 */
/****************************************************************************************************************/
#define CFG_LLM_RESOLVING_LIST_MAX      LLM_RESOLVING_LIST_MAX

/****************************************************************************************************************/
/* Enables automatic data packet length negotiation.                                                            */
/* NOTE: Enable only if peer device supports data length extension!!                                            */
/****************************************************************************************************************/
#undef AUTO_DATA_LENGTH_NEGOTIATION_UPON_NEW_CONNECTION

/****************************************************************************************************************/
/* Maximum retention memory in bytes. The base address of the retention data is calculated from the selected    */
/* size.                                                                                                        */
/****************************************************************************************************************/
#define CFG_RET_DATA_SIZE    (1636)

/****************************************************************************************************************/
/* Maximum uninitialized retained data required by the application.                                             */
/****************************************************************************************************************/
#define CFG_RET_DATA_UNINIT_SIZE (12)

/****************************************************************************************************************/
/* RAM cell(s) retention mode handling. The user has to select which RAM cells must be retained during the      */
/* extended sleep, based on his/her application RAM layout. The last RAM block is always retained, since it     */
/* contains the BLE state and ROM data.                                                                         */
/*     - CFG_RETAIN_RAM_1_BLOCK: if defined, the 1st RAM block must be retained.                                */
/*     - CFG_RETAIN_RAM_2_BLOCK: if defined, the 2nd RAM block must be retained.                                */
/* By default, the SDK keeps all RAM cells retained.                                                            */
/****************************************************************************************************************/
#define CFG_CUSTOM_SCATTER_FILE
#ifdef CFG_CUSTOM_SCATTER_FILE
    #define CFG_RETAIN_RAM_1_BLOCK
    #define CFG_RETAIN_RAM_2_BLOCK
    #define CFG_RETAIN_RAM_3_BLOCK
#endif

/****************************************************************************************************************/
/* Code location selection.                                                                                     */
/*     - CFG_CODE_LOCATION_EXT: Code is loaded from SPI flash / I2C EEPROM / UART                               */
/*     - CFG_CODE_LOCATION_OTP: Code is burned in the OTP                                                       */
/* The above options are mutually exclusive and exactly one of them must be enabled.                            */
/****************************************************************************************************************/
#define CFG_CODE_LOCATION_EXT
#undef CFG_CODE_LOCATION_OTP

/****************************************************************************************************************/
/* Uses long range extender (e.g. SKY66111).                                                                    */
/****************************************************************************************************************/
#undef CFG_RANGE_EXT

/****************************************************************************************************************/
/* Temperature range selection (it applies to hibernation mode only).                                           */
/* - CFG_HIGH_TEMPERATURE:         Device is configured to operate at high temperature range (-40C to +105C).   */
/* - CFG_AMB_TEMPERATURE:          Device is configured to operate at ambient temperature range (-40C to +40C). */
/* - CFG_MID_TEMPERATURE:          Device is configured to operate at mid temperature range (-40C to +60C).     */
/* - CFG_EXT_TEMPERATURE:          Device is configured to operate at ext temperature range (-40C to +85C).     */
/* NOTE 1: High temperature support is not compatible with power optimizations. User shall undefine the         */
/*         CFG_POWER_OPTIMIZATIONS flag, if device is to support the high temperature range feature.            */
/****************************************************************************************************************/
#define CFG_AMB_TEMPERATURE
#define CFG_ADC_DISABLE_CALIBRATION
#undef GPIO_DRV_IRQ_HANDLING_DISABLED
//#define __EXCLUDE_ROM_ARCH_CONSOLE__

#if !defined(__DA14531_01__)
#define CFG_REUSE_STARTUP_CODE_RAM
#endif

#if defined(CFG_REUSE_STARTUP_CODE_RAM)
#define SYS_INIT_PRE_RUN_ONCE_CODE      __attribute__((noinline)) __SECTION("system_init_pre_run_once")
#define SYS_INIT_INTERIM_RUN_ONCE_CODE  __attribute__((noinline)) __SECTION("system_init_interim_run_once")
#endif

#define GPIO_DRV_PIN_ALLOC_MON_DISABLED

#define __EXCLUDE_UART2_HANDLER__
#define CFG_UART2_DISABLE

#define __EXCLUDE_SWTIM1_HANDLER__
#define __EXCLUDE_RTC_HANDLER__
#define __EXCLUDE_I2C_HANDLER__

#undef CFG_BOND_CMD_SUPPORTED

/****************************************************************************************************************/
/* Define to force pairing when a value (AT command) is written to the inbound characteristic when no pin is set*/
/****************************************************************************************************************/
#undef CFG_FORCE_PAIR_ON_INBOUND_VALUE_WRITTEN

/****************************************************************************************************************/
/* Include the unused calibration_res variable.Excluding it saves about 40 bytes                                */
/****************************************************************************************************************/
#undef CFG_INCLUDE_CAL_RES


/****************************************************************************************************************/
/* Additional memory optimizations for DA14531                                                                  */
/****************************************************************************************************************/

/****************************************************************************************************************/
/* The systick handler is not used in CodeLess and therefore it can be removed.                                 */
/****************************************************************************************************************/
#define __EXCLUDE_SYSTICK_HANDLER__


/****************************************************************************************************************/
/* If this macro is defined the SUOTA buffer is reduced from 512 bytes to 128 bytes                             */
/****************************************************************************************************************/
#define USE_SMALLER_SUOTA_BUFFER_SIZE

// If this macro is defined the gpio is optimized based one the fact that
// gpio port is always zero
#if defined(__DA14531_01__)
#undef GPIO_OPT
#else
#define GPIO_OPT
#endif

/****************************************************************************************************************/
/* This macro will enable code optimizations in the rf driver for 531 allowing for smaller code size            */
/****************************************************************************************************************/
#define RF_OPT

/****************************************************************************************************************/
/* This macro will enable code optimizations in the adc driver for 531 allowing for slightly smaller code size  */
/****************************************************************************************************************/
#define ADC_OPT

/****************************************************************************************************************/
/* Define to add security support for CodeLess central                                                          */
/****************************************************************************************************************/
#undef CFG_BOND_CMD_SUPPORTED

#ifdef CFG_BOND_CMD_SUPPORTED
    #if defined(__DA14531_01__)
        #error Central is not supported in 531_01
    #else
        #define BOND_CMD_SUPPORTED (1)
        #if defined(__DA14531__)
            #warning Security in 531 central requires a lot of additional ram.Please remove some features (e.g. SUOTA) if the feature does not fit
        #endif
    #endif
#else
    #define BOND_CMD_SUPPORTED (0)
#endif

/****************************************************************************************************************/
/* Disable quadrature decoder on start up. The quadrature decoder is by default enabled on system power up and  */
/* it may count events. This leads to WKUP_QUADEC_IRQn pending interrupts.                                      */
/****************************************************************************************************************/
#define CFG_DISABLE_QUADEC_ON_START_UP

#ifdef USE_AT_BINARY_MODE
    #define CFG_PERIPHERAL_CE_LEN_LIMITING_ENABLED
#endif

#ifdef CFG_PERIPHERAL_CE_LEN_LIMITING_ENABLED
    #define PERIPHERAL_CE_LEN_LIMIT (1)
#endif

/****************************************************************************************************************/
/* When an incoming command is received it is printed immediately.However when a message is already being       */
/* printed the incoming command may corrupt the message. This macro ensures that the command is added on a list */
/* to be printed later.                                                                                         */
/****************************************************************************************************************/
#define USE_DELAYED_PRINTING_ON_BUSY_UART

/****************************************************************************************************************/
/* This macro will disable adc calibration in the adc driver for 531 allowing for slightly smaller code size    */
/****************************************************************************************************************/
#if !defined(__DA14531_01__)
#define CFG_ADC_DISABLE_CALIBRATION
#endif

/****************************************************************************************************************/
/* This macro will use a static configuration in the spi driver to save up some space                           */
/****************************************************************************************************************/
#undef CFG_SPI_STATIC_CONFIGURATION

/****************************************************************************************************************/
/* If this macro is defined, CodeLess will enter binary mode when a connection occurs automatically provided    */
/* that the remote peer supports binary mode as well                                                            */
/****************************************************************************************************************/
#if defined(CFG_DATAPMP)
#undef CFG_ENTER_BINARY_MODE_ON_CONNECTION
#if defined(CFG_ENTER_BINARY_MODE_ON_CONNECTION) && !defined(__DA14531_01__)
#warning This feature will probably not fit in DA14531 DATAPUMP.Please remove some other feature to include this in
#endif
#endif

/****************************************************************************************************************/
/* If this macro is defined, CodeLess will change the permissions to access the custom profile database         */
/* dynamically depending on the AT+SEC selection.This macro and CFG_BOND_CMD_SUPPORTED are mutually exclusive   */
/****************************************************************************************************************/
#if defined(__DA14531_01__)
#define CFG_USE_DYNAMIC_PRF_PERMS
#else // DA14531
#if defined(CFG_BOND_CMD_SUPPORTED)
#undef CFG_USE_DYNAMIC_PRF_PERMS
#else
#undef CFG_USE_DYNAMIC_PRF_PERMS // #define this macro here if you need dynamic profile permissions
#endif
#if defined(CFG_USE_DYNAMIC_PRF_PERMS)
#warning This feature will probably not fit in DA14531.Please remove some other feature to include this in
#endif
#endif

#endif // _DA14531_CONFIG_ADVANCED_H_
