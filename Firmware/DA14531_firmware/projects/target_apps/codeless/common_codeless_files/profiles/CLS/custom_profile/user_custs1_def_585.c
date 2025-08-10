/**
 ****************************************************************************************
 *
 * @file user_custs1_def_585.c
 *
 * @brief Custom1 Server (CUSTS1) profile database definitions.
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
 * This file was auto generated 2/4/2017 9:13:54 AM
 * by DA1458x Custom GATT Service Constructor (v1.1b)
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @defgroup USER_CONFIG
 * @ingroup USER
 * @brief Custom1 Server (CUSTS1) profile database definitions.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include <stdint.h>
#include "prf_types.h"
#include "attm_db_128.h"
#include "user_custs1_def_585.h"

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Full CUSTOM1 Database Description - Used to add attributes into the database

const att_svc_desc128_t custs1_svc                               = DEF_CUST1_SVC_UUID_128;

const uint8_t CUST1_INBOUND_UUID_128[ATT_UUID_128_LEN]           = DEF_CUST1_INBOUND_UUID_128;
const uint8_t CUST1_OUTBOUND_UUID_128[ATT_UUID_128_LEN]          = DEF_CUST1_OUTBOUND_UUID_128;
const uint8_t CUST1_FLOW_CONTROL_UUID_128[ATT_UUID_128_LEN]      = DEF_CUST1_FLOW_CONTROL_UUID_128;

const att_svc_desc128_t custs1_sps_svc                           = SPS_SERVICE_UUID;

#ifdef CUSTS_SPSS
const uint8_t CUST1_SPS_RX_UUID_128[ATT_UUID_128_LEN]            = SPS_SERVER_RX_UUID;
const uint8_t CUST1_SPS_TX_UUID_128[ATT_UUID_128_LEN]            = SPS_SERVER_TX_UUID;
const uint8_t CUST1_SPS_FLOW_CONTROL_UUID_128[ATT_UUID_128_LEN]  = SPS_FLOW_CTRL_UUID;
#endif
/*
 * CUSTS1 ATTRIBUTES
 ****************************************************************************************
 */

static const uint16_t att_decl_svc       = ATT_DECL_PRIMARY_SERVICE;
static const uint16_t att_decl_char      = ATT_DECL_CHARACTERISTIC;
static const uint16_t att_decl_cfg       = ATT_DESC_CLIENT_CHAR_CFG;

#ifdef CUSTS_SPSS
const uint8_t custs1_services[]  = {CUST1_IDX_SVC, CUST1_SPSS_IDX_SVC, CUST1_IDX_NB};
#else
const uint8_t custs1_services[]  = {CUST1_IDX_SVC, CUST1_IDX_NB};
#endif
const uint8_t custs1_services_size = ARRAY_LEN(custs1_services) - 1;
const uint16_t custs1_att_max_nb = CUST1_IDX_NB;

/// Full CUSTOM1 Database Description - Used to add attributes into the database
const struct attm_desc_128 custs1_att_db[CUST1_IDX_NB] =
{

  // -----------  Attributes of Custom Service #1 -----------//
  [CUST1_IDX_SVC] =
  {
    (uint8_t*)&att_decl_svc,
    ATT_UUID_128_LEN,
    PERM(RD, ENABLE),
    sizeof(custs1_svc),
    sizeof(custs1_svc),
    (uint8_t*)&custs1_svc
  },

  // Inbound Characteristic Attribute
  [CUST1_IDX_INBOUND_CHAR] =
  {
    (uint8_t*)&att_decl_char,
    ATT_UUID_16_LEN,
    PERM(RD, ENABLE),
    0,
    0,
    NULL
  },

  // Inbound Characteristic Value Attribute
  [CUST1_IDX_INBOUND_VAL] =
  {
    CUST1_INBOUND_UUID_128,
    ATT_UUID_128_LEN,
#if defined(CFG_FORCE_PAIR_ON_INBOUND_VALUE_WRITTEN)
    PERM(WR,AUTH) | PERM(RD,AUTH) | PERM(WRITE_REQ, AUTH),
#else
    PERM(WR,ENABLE) | PERM(RD,ENABLE) | PERM(WRITE_REQ, ENABLE),
#endif
    DEF_CUST1_INBOUND_LEN,
    0,
    NULL
  },

  // Outbound Characteristic Attribute
  [CUST1_IDX_OUTBOUND_CHAR] =
  {
    (uint8_t*)&att_decl_char,
    ATT_UUID_16_LEN,
    PERM(RD, ENABLE),
    0,
    0,
    NULL
  },

  // Outbound Characteristic Value Attribute
  [CUST1_IDX_OUTBOUND_VAL] =
  {
    CUST1_OUTBOUND_UUID_128,
    ATT_UUID_128_LEN,
    PERM(WR,ENABLE) | PERM(RD,ENABLE) | PERM(WRITE_REQ, ENABLE),
#if defined(OUTBOUND_CHAR_QUEUE)
    PERM(RI,ENABLE)|DEF_CUST1_OUTBOUND_LEN,
#else
    DEF_CUST1_OUTBOUND_LEN,
#endif
    0,
    NULL
  },

  // Flow Control Characteristic Attribute
  [CUST1_IDX_FLOW_CONTROL_CHAR] =
  {
    (uint8_t*)&att_decl_char,
    ATT_UUID_16_LEN,
    PERM(RD, ENABLE),
    0,
    0,
    NULL
  },

  // Flow Control Characteristic Value Attribute
  [CUST1_IDX_FLOW_CONTROL_VAL] =
  {
    CUST1_FLOW_CONTROL_UUID_128,
    ATT_UUID_128_LEN,
    PERM(WR,ENABLE) | PERM(RD,ENABLE) | PERM(NTF, ENABLE) | PERM(WRITE_REQ, ENABLE),
    DEF_CUST1_FLOW_CONTROL_LEN,
    0,
    NULL
  },

  // Flow Control Characteristic Client Configuration Attribute
  [CUST1_IDX_FLOW_CONTROL_CFG] =
  {
    (uint8_t*)&att_decl_cfg,
    ATT_UUID_16_LEN,
    PERM(RD, ENABLE) | PERM(WR, ENABLE) | PERM(WRITE_REQ, ENABLE),
    sizeof(uint16_t),
    0,
    NULL
  },
#ifdef CUSTS_SPSS
  [CUST1_SPSS_IDX_SVC] =
  {
    (uint8_t*)&att_decl_svc,
    ATT_UUID_128_LEN,
    PERM(RD, ENABLE),
    sizeof(custs1_sps_svc),
    sizeof(custs1_sps_svc),
    (uint8_t*)&custs1_sps_svc
  },

   // TX Characteristic
  [CUST1_SPSS_IDX_TX_CHAR] =
  {
    (uint8_t*)&att_decl_char,
    ATT_UUID_16_LEN,
    PERM(RD, ENABLE),
    0,
    0,
    NULL
  },

  // TX Characteristic Value
  [CUST1_SPSS_IDX_TX_VAL] =
  {
    CUST1_SPS_TX_UUID_128,
    ATT_UUID_128_LEN,
    PERM(NTF, ENABLE),
    SPS_SERVER_TX_CHAR_LEN,
    0,
    NULL
  },

  // TX Characteristic Configuration
  [CUST1_SPSS_IDX_TX_CFG] =
  {
    (uint8_t*)&att_decl_cfg,
    ATT_UUID_16_LEN,
    PERM(RD, ENABLE) | PERM(WR, ENABLE) | PERM(WRITE_REQ, ENABLE),
    sizeof(uint16_t),
    0,
    NULL
  },

   // RX Characteristic
  [CUST1_SPSS_IDX_RX_CHAR] =
  {
    (uint8_t*)&att_decl_char,
    ATT_UUID_16_LEN,
    PERM(RD, ENABLE),
    0,
    0,
    NULL
  },

  //RX Characteristic Value
  [CUST1_SPSS_IDX_RX_VAL] =
  {
    CUST1_SPS_RX_UUID_128,
    ATT_UUID_128_LEN,
    PERM(WR, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
    SPS_SERVER_RX_CHAR_LEN,
    0,
    NULL
  },

  // RX Characteristic Configuration
  /*
  [CUST1_SPSS_IDX_RX_CFG] =
  {
    (uint8_t*)&att_decl_cfg,
    ATT_UUID_16_LEN,
    PERM(RD, ENABLE) | PERM(WR, ENABLE)  | PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
    sizeof(uint16_t),
    0,
    NULL
  },
  */
   // Flow Control Characteristic
  [CUST1_SPSS_IDX_FLOW_CONTROL_CHAR] =
  {
    (uint8_t*)&att_decl_char,
    ATT_UUID_16_LEN,
    PERM(RD, ENABLE),
    0,
    0,
    NULL
  },

  // Flow Control Characteristic Value
  [CUST1_SPSS_IDX_FLOW_CONTROL_VAL] =
  {
    CUST1_SPS_FLOW_CONTROL_UUID_128,
    ATT_UUID_128_LEN,
    PERM(RD, ENABLE) | PERM(WR, ENABLE) | PERM(NTF, ENABLE)  | PERM(WRITE_COMMAND, ENABLE),
    SPS_FLOW_CTRL_CHAR_LEN,
    0,
    NULL
  },

  // Flow Control Characteristic Configuration
  [CUST1_SPSS_IDX_FLOW_CONTROL_CFG] =
  {
    (uint8_t*)&att_decl_cfg,
    ATT_UUID_16_LEN,
    PERM(RD, ENABLE) | PERM(WR, ENABLE)  | PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
    sizeof(uint16_t),
    0,
    NULL
  },




#endif


};

/// @} USER_CONFIG
