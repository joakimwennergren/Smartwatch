/**
 ****************************************************************************************
 *
 * @file user_gap.c
 *
 * @brief user_gap source file
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

#include "user_gap.h"
#include "custs1_task.h"
#include "user_custs_config.h"
#include "user_custs1_def.h"
#include "app.h"

#include "user_codeless_env.h"
#include "user_security.h"
/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void user_app_configuration_func(uint8_t role)
{
    struct gapm_set_dev_config_cmd* cmd = app_easy_gap_dev_config_get_active();
    #ifdef USE_AT_MAXMTU
    struct connection_configuration_t *p_conf=&codeless_env.conn_conf;
    #endif

    // Set device configuration
    cmd->operation = GAPM_SET_DEV_CONFIG;
    // Set role
    cmd->role = role;
    // Also retain the role in the environment
    codeless_env.bt_role = role;
#ifdef CODELESS_585 // no addr field for 580 message.
    extern struct bd_addr user_injected_bd_address;
    memcpy(&cmd->addr, &user_injected_bd_address, 6);

#ifndef USER_CFG_ADDRESS_MODE
    #error USER_CFG_ADDRESS_MODE should be always defined
#else
    #if (USER_CFG_ADDRESS_MODE==APP_CFG_ADDR_PUB)
    cmd->addr_type = GAPM_CFG_ADDR_PUBLIC;
    #elif (USER_CFG_ADDRESS_MODE==APP_CFG_ADDR_STATIC)
    cmd->addr_type = GAPM_CFG_ADDR_STATIC;
    #endif
#endif
    #ifdef USE_AT_MAXMTU
    cmd->max_mtu=p_conf->max_mtu;
    #else
    cmd->max_mtu=user_gapm_conf.max_mtu;
    #endif
#endif
    cmd->priv1_2= 0x00;
    memset(cmd->irk.key, 0, sizeof(struct gap_sec_key));

    app_gapm_configure_msg_send(cmd);
    app_easy_reset_config_cmd();
#if (BOND_CMD_SUPPORTED)
    // Update the security/pairing settings according to codeless_env.bt_role but keep the same mode
    extern security_and_pairing_t sec_pair_mode;
    set_security_and_pairing_mode(sec_pair_mode);
#endif
}

void user_connect_to_peripheral(uint8_t peer_addr_type, uint8_t* addr, uint16_t intv)
{
    // Construct and send a connect message
    struct gapm_start_connection_cmd* msg;
    msg = (struct gapm_start_connection_cmd*)KE_MSG_ALLOC_DYN(GAPM_START_CONNECTION_CMD, TASK_GAPM,
                                                              TASK_APP, gapm_start_connection_cmd,
                                                              sizeof(struct gap_bdaddr));
    msg->nb_peers = 1;
    memcpy((void*)&msg->peers[0].addr, (void*)addr, BD_ADDR_LEN);
    msg->peers[0].addr_type = peer_addr_type;
    msg->con_intv_max = intv;
    msg->con_intv_min = intv;
    msg->ce_len_min = 0x45;
    msg->ce_len_max = 0x45;
    msg->con_latency = 0;
    msg->op.addr_src = 0;
    msg->superv_to = 300; // 300 -> 3000 ms ;
    msg->scan_interval = 0x1800;
    msg->scan_window = 0x1700;
    msg->op.code = GAPM_CONNECTION_DIRECT;
    KE_MSG_SEND((void*)msg);
    ke_state_set(TASK_APP, APP_CONNECTABLE);
}

void user_scan_start(void)
{
    // Comstruct and send a command to start scanning
    struct gapm_start_scan_cmd* cmd
        = KE_MSG_ALLOC(GAPM_START_SCAN_CMD, TASK_GAPM, TASK_APP, gapm_start_scan_cmd);

    cmd->op.code = user_scan_conf.code;
    cmd->op.addr_src = user_scan_conf.addr_src;
    cmd->interval = user_scan_conf.interval;
    cmd->window = user_scan_conf.window;
    cmd->mode = user_scan_conf.mode;
    cmd->filt_policy = user_scan_conf.filt_policy;
    cmd->filter_duplic = user_scan_conf.filter_duplic;
    // Send the message
    KE_MSG_SEND(cmd);
}

/// @} APP
