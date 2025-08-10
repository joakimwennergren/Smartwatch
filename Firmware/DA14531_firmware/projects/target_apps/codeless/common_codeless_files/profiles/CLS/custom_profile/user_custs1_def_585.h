/**
 ****************************************************************************************
 *
 * @file user_custs1_def_585.h
 *
 * @brief Custom1 Server (CUSTS1) profile database declarations.This file was auto
 * generated 2/4/2017 9:13:54 AM by DA1458x Custom GATT Service Constructor (v1.1b)
 *
 * Copyright (C) 2017-2023 Renesas Electronics Corporation and/or its affiliates.
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

#ifndef _USER_CUSTS1_DEF_585_H_
#define _USER_CUSTS1_DEF_585_H_

/**
 ****************************************************************************************
 * @defgroup USER_CONFIG
 * @ingroup USER
 * @brief Custom1 Server (CUSTS1) profile database declarations.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "attm_db_128.h"
#include "user_at_console.h"
/*
 * DEFINES
 ****************************************************************************************
 */

#define DEF_CUST1_SVC_UUID_128   {0x83, 0x6E, 0xEC, 0x1B, 0xF9, 0xB7, 0x05, 0x9C, 0xDC, 0x40, 0x74, 0xE6, 0x04, 0x3B, 0x6D, 0x86}

#define DEF_CUST1_INBOUND_UUID_128  {0x25, 0x54, 0xE4, 0x4D, 0x59, 0x14, 0xD1, 0xB7, 0x1D, 0x41, 0xCD, 0xE8, 0xB9, 0x8F, 0x4F, 0x91}
#define DEF_CUST1_OUTBOUND_UUID_128  {0x04, 0xA4, 0x59, 0xDC, 0x06, 0x6B, 0x09, 0xAA, 0xBE, 0x4F, 0xB2, 0x50, 0xAA, 0x35, 0xB5, 0x3B}
#define DEF_CUST1_FLOW_CONTROL_UUID_128  {0x39, 0x56, 0x0D, 0xC1, 0x56, 0x18, 0x25, 0x9F, 0x45, 0x4A, 0xF9, 0xD4, 0x39, 0x8B, 0x04, 0xE2}

#define SPS_SERVICE_UUID    {0xb7, 0x5c, 0x49, 0xd2, 0x04, 0xa3, 0x40, 0x71, 0xa0, 0xb5, 0x35, 0x85, 0x3e, 0xb0, 0x83, 0x07}

#define SPS_SERVER_TX_UUID  {0xb8, 0x5c, 0x49, 0xd2, 0x04, 0xa3, 0x40, 0x71, 0xa0, 0xb5, 0x35, 0x85, 0x3e, 0xb0, 0x83, 0x07}
#define SPS_SERVER_RX_UUID  {0xba, 0x5c, 0x49, 0xd2, 0x04, 0xa3, 0x40, 0x71, 0xa0, 0xb5, 0x35, 0x85, 0x3e, 0xb0, 0x83, 0x07}
#define SPS_FLOW_CTRL_UUID  {0xb9, 0x5c, 0x49, 0xd2, 0x04, 0xa3, 0x40, 0x71, 0xa0, 0xb5, 0x35, 0x85, 0x3e, 0xb0, 0x83, 0x07}


#define DEF_CUST1_INBOUND_LEN  CMD_BUFFER_SIZE
#define DEF_CUST1_OUTBOUND_LEN  CMD_BUFFER_SIZE
#define DEF_CUST1_FLOW_CONTROL_LEN  1

#define SPS_SERVER_TX_CHAR_LEN      250
#define SPS_SERVER_RX_CHAR_LEN      250
#define SPS_FLOW_CTRL_CHAR_LEN      1

///Attribute Database Index Enumeration
enum
{
    CUST1_IDX_SVC = 0,

    CUST1_IDX_INBOUND_CHAR,
    CUST1_IDX_INBOUND_VAL,

    CUST1_IDX_OUTBOUND_CHAR,
    CUST1_IDX_OUTBOUND_VAL,

    CUST1_IDX_FLOW_CONTROL_CHAR,
    CUST1_IDX_FLOW_CONTROL_VAL,
    CUST1_IDX_FLOW_CONTROL_CFG,

    #ifdef CUSTS_SPSS
    CUST1_SPSS_IDX_SVC,

    CUST1_SPSS_IDX_TX_CHAR,
    CUST1_SPSS_IDX_TX_VAL,
    CUST1_SPSS_IDX_TX_CFG,


    CUST1_SPSS_IDX_RX_CHAR,
    CUST1_SPSS_IDX_RX_VAL,
//    CUST1_SPSS_IDX_RX_CFG,


    CUST1_SPSS_IDX_FLOW_CONTROL_CHAR,
    CUST1_SPSS_IDX_FLOW_CONTROL_VAL,
    CUST1_SPSS_IDX_FLOW_CONTROL_CFG,

    #endif

    CUST1_IDX_NB
};

/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */

extern const struct attm_desc_128 custs1_att_db[CUST1_IDX_NB];

extern const att_svc_desc128_t custs1_svc;

extern const uint8_t CUST1_INBOUND_UUID_128[ATT_UUID_128_LEN];
extern const uint8_t CUST1_OUTBOUND_UUID_128[ATT_UUID_128_LEN];
extern const uint8_t CUST1_FLOW_CONTROL_UUID_128[ATT_UUID_128_LEN];

extern const att_svc_desc128_t custs1_sps_svc;
#ifdef CUSTS_SPSS
extern const uint8_t CUST1_SPS_RX_UUID_128[ATT_UUID_128_LEN];
extern const uint8_t CUST1_SPS_TX_UUID_128[ATT_UUID_128_LEN];
extern const uint8_t CUST1_SPS_FLOW_CONTROL_UUID_128[ATT_UUID_128_LEN];
#endif

/// @} USER_CONFIG

#endif // _USER_CUSTS1_DEF_H_
