/**
 ****************************************************************************************
 *
 * @file user_codeless_strings.h
 *
 * @brief contains all strings used for interfacing with the user as command replys or
 *        event notifications.
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

#ifndef _USER_CODELESS_STRINGS_H_
#define _USER_CODELESS_STRINGS_H_

#include "codeless_sw_version.h"

#ifdef CODELESS_585
    #if defined( __DA14585__)
        #define CODELESS_INFO_STRING "CodeLess DA14585 " SW_VERSION " "
    #elif defined (__DA14586__)
        #define CODELESS_INFO_STRING "CodeLess DA14586 " SW_VERSION " "
    #elif defined(__DA14531_01__)
        #define CODELESS_INFO_STRING "CodeLess DA14531-01 " SW_VERSION " "
    #elif defined(__DA14535__)
        #define CODELESS_INFO_STRING "CodeLess DA14535 " SW_VERSION " "
    #elif defined (__DA14531__) // The __DA14531__ must be the last in the sequence
        #define CODELESS_INFO_STRING "CodeLess DA14531 " SW_VERSION " "
    #else
        #error No device has been defined for CodeLess
    #endif
#endif


#define INIT_STRING "\r\n+READY\r\n"
#define WAKEUP_STRING "\r\n+AWAKE\r\n"
#define OK_TERMINATION_STRING "\r\nOK\r\n"
#define OK_TERMINATION_STRING_LEN 6
#define ERROR_TERMINATION_STRING "\r\nERROR\r\n"
#define ERROR_TERMINATION_STRING_LEN 9
#define CODELESS_CMD_INVALID_STRING "INVALID COMMAND."
#define NEWLINE_STRING "\r\n"
#define CONNECTING_STRING "CONNECTING\r\n"
#define DISCONNECTING_STRING "DISCONNECTING\r\n"
#define CONNECTION_SUCCESSFUL_STRING "\r\n+CONNECTED\r\n"
#define CONNECTION_FAIL_STRING "CONNECTION FAILED\r\nERROR\r\n"
#define SCANNING_STRING "SCANNING\r\n"
#define BONDING_FAIL_STRING "+BONDING FAILED\r\n"
#define BONDING_SUCCEED_STRING "+BONDING SUCCESS\r\n"
#define DISCONNECTION_STRING "\r\n+DISCONNECTED\r\n"
#define SCAN_COMPLETE_STRING "SCAN COMPLETE\r\nOK\r\n"
#define PASS_REQ_STRING "+PASSCODE REQ RECEIVED\r\n"
#define SEC_REQ_STRING "SECURITY REQ. AUTH LEVEL: "
#define DSPS_PEER "+BINARY MODE SUPPORTED\r\n"
#define CODELESS_PEER "+COMMAND MODE SUPPORTED\r\n"
#define ECHO_ON_STRING "+ECHO ON\r\n"
#define ECHO_OFF_STRING "+ECHO OFF\r\n"
#define BINESC_SEQ_CHANGED_STRING "+ESC SEQ\r\n"

#if (BOND_CMD_SUPPORTED)
#define SECURITY_REQUEST_RECV_STRING "+RECV SEC REQ\r\n"
#define ENCRYPTED_LINK_STRING "+ENC LINK\r\n"
#define BOND_INFO_STRING "+BOND INFO\r\n"
#define PERIPH_KEY_MISSING_STRING "+PERIPH ENC KEY MISSING\r\n"
#define BOND_REQ_STRING "+BOND REQ\r\n"
#endif

#endif //_USER_CODELESS_STRINGS_H_
