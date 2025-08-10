/**
 ****************************************************************************************
 *
 * @file user_gatt.c
 *
 * @brief user_gatt source file
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "user_gatt.h"
#include "custs1_task.h"
#include "user_custs_config.h"
#include "user_custs1_def.h"
#include "user_at_console.h"
#include "prf_utils.h"

#include "custs1.h"
#ifdef CODELESS_585
#include "prf.h"
#endif
#include "user_codeless_env.h"
#include "user_codeless_strings.h"

#if defined (OUTBOUND_CHAR_QUEUE)
#include "user_utility_functions.h"
#endif

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void user_prf_gatt_write(uint16_t handle, uint8_t* value, uint16_t length, uint8_t operation, uint16_t seq_num)
{
    if(handle != ATT_INVALID_HANDLE)
    {
        struct gattc_write_cmd *wr_char = KE_MSG_ALLOC_DYN(GATTC_WRITE_CMD,
                KE_BUILD_ID(TASK_GATTC, codeless_env.connection_index), TASK_APP ,
                gattc_write_cmd, length);

        // Offset
        wr_char->offset         = 0x0000;
        // cursor always 0
        wr_char->cursor         = 0x0000;
        // Write Type
        wr_char->operation       = operation;
        // Characteristic Value attribute handle
        wr_char->handle         = handle;
        // Value Length
        wr_char->length         = length;
        // Auto Execute
        wr_char->auto_execute   = true;

        wr_char->seq_num =seq_num;
        // Value
        memcpy(&wr_char->value[0], value, length);

        // Send the message
        KE_MSG_SEND(wr_char);
    }
}

#ifdef CUSTS_SPSS
void user_send_sps_ble_flow(char flow)
{
    struct sps_env_t *sps_env = &codeless_env.sps_env;
#if !defined(__DA14531_01__)
    if (codeless_env.bt_role == GAP_ROLE_CENTRAL)
    {
        user_prf_gatt_write(codeless_env.hdl_dsps_flow_ctrl, (uint8_t *)&flow, 1,  GATTC_WRITE_NO_RESPONSE, 0);
    }
    else
#endif
    {
        struct custs1_val_ntf_ind_req* req2 = KE_MSG_ALLOC_DYN(CUSTS1_VAL_NTF_REQ,
                                                               prf_get_task_from_id(TASK_ID_CUSTS1),
                                                               TASK_APP,
                                                               custs1_val_ntf_ind_req,
                                                               1);
        req2->notification = true;
        req2->conidx = app_env->conhdl;
        req2->handle = CUST1_SPSS_IDX_FLOW_CONTROL_VAL;


        req2->value[0] = flow;
        req2->length = 1;


        KE_MSG_SEND(req2);
    }
    #ifdef CUSTS_SPSS
    sps_env->ble_flow_ntf_tx++;
    #endif


}
#endif

void send_to_remote(char* str_to_send)
{
    extern bool is_connected(void);
    if (is_connected())
    {

        // Write response string to Bluetooth peer
#if !defined(__DA14531_01__)
        if (codeless_env.bt_role == GAP_ROLE_CENTRAL)
        {


            // Codeless device is central/client
            user_prf_gatt_write(codeless_env.hdl_inbound_val, (uint8_t *)str_to_send, strlen(str_to_send)+1,  GATTC_WRITE, 0);

        }
        else
#endif
        {
#if !defined(OUTBOUND_CHAR_QUEUE)
             // Codeless device is peripheral/server
            struct custs1_val_set_req* req
                = KE_MSG_ALLOC_DYN(CUSTS1_VAL_SET_REQ, prf_get_task_from_id(TASK_ID_CUSTS1),
                                   TASK_APP, custs1_val_set_req, strlen(str_to_send) + 1);
            req->conidx = app_env->conhdl;
            req->handle = CUST1_IDX_OUTBOUND_VAL;

            req->length = strlen(str_to_send) + 1;
            memcpy(req->value, str_to_send, strlen(str_to_send) + 1);
            KE_MSG_SEND(req);
#else
            outbound_char_enqueue(str_to_send);
#endif
#if !defined(__DA14531_01__)
            if (codeless_env.bt_role != GAP_ROLE_CENTRAL)
#endif
            {
                // Notify Bluetooth peer

                struct custs1_val_ntf_ind_req* req2
                        = KE_MSG_ALLOC_DYN(CUSTS1_VAL_NTF_REQ, prf_get_task_from_id(TASK_ID_CUSTS1),
                                       TASK_APP, custs1_val_ntf_ind_req, 1);
                req2->notification = true;
                req2->conidx = app_env->conhdl;
                req2->handle = CUST1_IDX_FLOW_CONTROL_VAL;
                req2->length = 1;
                req2->value[0] = 0x01;
                KE_MSG_SEND(req2);

                //user_send_remote_notification(CUST1_IDX_FLOW_CONTROL_VAL, 0x01, 0, 1);
            }

        }

    } else {
        at_console_error_report(AT_CONSOLE_ERROR_7); // Tried to send to peer but no connection
        send_to_local(OK_TERMINATION_STRING);
    }
}

void user_gatt_discover_chars()
{
    struct gattc_disc_cmd* req
        = KE_MSG_ALLOC_DYN(GATTC_DISC_CMD, KE_BUILD_ID(TASK_GATTC, 0), TASK_APP, gattc_disc_cmd, 2);



#ifdef CODELESS_585
    req->operation = GATTC_DISC_ALL_CHAR;
#endif
    memset(&req->uuid, 0, 2);

    req->uuid_len = 2;
    req->start_hdl = 0x0001;
    req->end_hdl = 0x1FFF;
    KE_MSG_SEND(req);
}

/// @} APP
