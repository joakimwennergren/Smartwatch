/**
 ****************************************************************************************
 *
 * @file da14585_config_basic.h
 *
 * @brief Basic compile configuration file.
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

#ifndef _DA14585_CONFIG_BASIC_H_
#define _DA14585_CONFIG_BASIC_H_

#include "da1458x_stack_config.h"
#ifdef CODELESS_585
#include "user_profiles_config.h"
#endif

/***************************************************************************************************************/
/* Integrated or external processor configuration                                                              */
/*    -defined      Integrated processor mode. Host application runs in DA14585 processor. Host application    */
/*                  is the TASK_APP kernel task.                                                               */
/*    -undefined    External processor mode. Host application runs on an external processor. Communicates with */
/*                  BLE application through GTL protocol over a signalling iface (UART, SPI etc)               */
/***************************************************************************************************************/
#define CFG_APP

/****************************************************************************************************************/
/* Enables the BLE security functionality in TASK_APP. If not defined BLE security related code is compiled out.*/
/****************************************************************************************************************/
#define CFG_APP_SECURITY

/****************************************************************************************************************/
/* Enables WatchDog timer.                                                                                      */
/****************************************************************************************************************/
#define CFG_WDOG

/****************************************************************************************************************/
/* Determines maximum concurrent connections supported by application. It configures the heap memory allocated  */
/* to service multiple connections. It is used for GAP central role applications. For GAP peripheral role it    */
/* should be set to 1 for optimizing memory utilization.                                                        */
/*      - MAX value for DA14585: 8                                                                              */
/****************************************************************************************************************/
#define CFG_MAX_CONNECTIONS     (1)

/****************************************************************************************************************/
/* Enables development/debug mode. For production mode builds it must be disabled.                              */
/* When enabled the following debugging features are enabled                                                    */
/*      -   Allows the emulation of the OTP mirroring to System RAM. No actual writing to RAM is done, but the  */
/*          exact same amount of time is spend as if the mirroring would take place. This is to mimic the       */
/*          behavior as if the System Code is already in OTP, and the mirroring takes place after waking up,    */
/*          but the (development) code still resides in an external source.                                     */
/*      -   Validation of GPIO reservations.                                                                    */
/*      -   Enables Debug module and sets code execution in breakpoint in Hardfault and NMI (Watchdog) handlers.*/
/*          It allows developer to hot attach debugger and get debug information                                */
/****************************************************************************************************************/
#undef CFG_DEVELOPMENT_DEBUG
#define GPIO_DRV_PIN_ALLOC_MON_DISABLED

/****************************************************************************************************************/
/* UART Console Print. If CFG_PRINTF is defined, serial interface logging mechanism will be enabled.            */
/* If CFG_PRINTF_UART2 is defined, then serial interface logging mechanism is implented using UART2, else UART1 */
/* will be used.                                                                                                */
/****************************************************************************************************************/
#define CFG_PRINTF //Mandatory for Codeless
#ifdef CFG_PRINTF
    /* This determines the UART Used for Codeless, if not defined UART1 will be used, note that in DA14531 UART2
       does not support RTS/CTS (HW) flow control */
    #undef CFG_PRINTF_UART2
#endif

/****************************************************************************************************************/
/* UART1 Driver Implementation. If CFG_UART1_SDK is defined, UART1 ROM driver will be overriden and UART SDK    */
/* driver will be used, else ROM driver will be used for UART1 module.                                          */
/****************************************************************************************************************/
#define CFG_UART1_SDK

#define GPIO_DRV_PIN_ALLOC_MON_DISABLED

#define USE_AT_BINARY_MODE

//#define CUSTS_SPSC 1
#if !defined(CFG_PRF_SPSS) && defined(USE_AT_BINARY_MODE)
#define CUSTS_SPSS 1
#endif
// #define __EXCLUDE_ROM_ARCH_CONSOLE__

/****************************************************************************************************************/
/* CodeLess outbound characteristic queue mode                                                                  */
/* In the CodeLess peripheral case all outgoing responses that are to be transferred to the central             */
/* will be written to the CodeLess outbound characteristic.As soon as this happens a notification will be sent  */
/* to the central to read the outbound characteristic.If commands are sent by multiple interfaces to the        */
/* codeless peripheral (e.g. both uart and bluetooth) in close proximity one response may overwrite             */
/* the previous one before it can be read by the central.When this macro is defined a queue is used so that     */
/* responses are not overwritten                                                                                */
/****************************************************************************************************************/
#define OUTBOUND_CHAR_QUEUE

/****************************************************************************************************************/
/* CodeLess pin debug feature                                                                                   */
/* When this macro is defined an external pin will change status on next reboot if a nmi or hardfault occurs    */
/****************************************************************************************************************/
#undef CFG_PIN_CHANGE_ON_NMI_OR_HARDFAULT


#endif // _DA14585_CONFIG_BASIC_H_
