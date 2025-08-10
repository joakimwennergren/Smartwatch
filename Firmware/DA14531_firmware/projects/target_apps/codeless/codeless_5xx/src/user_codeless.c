/**
 ****************************************************************************************
 *
 * @file user_codeless.c
 *
 * @brief codeless project source code.
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

/**
 ****************************************************************************************
 * @addtogroup APP
 * @{

 ****************************************************************************************
 */
#include "rwip_config.h" // SW configuration

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "user_codeless.h"
#include "user_at_commands.h"
#include "user_at_console.h"
#include "app_api.h"
#include "arch_console.h"
#include "uart.h"
#include "wkupct_quadec.h"
#include "gpio.h"
#include "custs1.h"
#include "custs1_task.h"
#include "user_cmd_parser.h"
#include "user_cmd_interpreter.h"
#include "user_custs_config.h"
#include "user_custs1_def.h"
#include "user_periph_setup.h"
#include "user_gap.h"
#include "user_gatt.h"
#include "user_utility_functions.h"
#include "user_codeless_env.h"
#include "user_i2c.h"
#include "user_handlers.h"
#include "ke_mem.h"
#include "app_bond_db.h"
#include "prf_utils.h"
#include "gattc.h"
#include "user_periph_setup.h"
#include "app_events_db.h"
#include "user_custs_sps.h"
#include "app_conpar_db.h"
#include "user_security.h"
#include "user_callback_config.h"
#if defined(CFG_USE_DYNAMIC_PRF_PERMS)
#include "user_security.h"
#include "app_suotar.h"
#endif


/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
/*
 * Provided static random address
 */
struct bd_addr user_injected_bd_address;
extern timer_hnd sleep_timer;
extern bool restore_sec_pair_mode_on_discon_if_legacy;
/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

uint8_t requester_connidx __SECTION_ZERO("retention_mem_area0"); // @RETENTION MEMORY

timer_hnd features_timer __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY;

#ifdef USE_AT_RSSI
timer_hnd rssi_timer __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY;
#endif

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

static void user_gattc_exc_mtu_cmd(uint8_t conidx)
{
    struct gattc_exc_mtu_cmd *cmd =  KE_MSG_ALLOC(GATTC_EXC_MTU_CMD,
                                                  KE_BUILD_ID(TASK_GATTC, conidx),
                                                  TASK_APP,
                                                  gattc_exc_mtu_cmd);

    cmd->operation=GATTC_MTU_EXCH;
    cmd->seq_num = 0;
    KE_MSG_SEND(cmd);
}

void check_features(struct gapc_peer_features_ind *param )
{
    #ifdef USE_AT_BINARY_MODE
    volatile uint8_t features1 =   *(uint8_t *)&param->features[0];
    //volatile uint8_t features2 =   *(uint8_t *)&param->features[1];
    struct sps_env_t *sps_env = &codeless_env.sps_env;

    user_gattc_exc_mtu_cmd(0);

    if( features1 & 0x20 )
    {
        //arch_printf("DLE ON\r\n");
        sps_env->peer_supports_dle = 1;
    }
    else
    {
        //arch_printf("DLE OFF\r\n");
        sps_env->peer_supports_dle = 0;
    }

    #endif

}

#ifdef USE_AT_BINARY_MODE
void user_set_default_tx_size(void)
{
    //We need to set them in advance in case that length os not set
    struct sps_env_t *sps_env = &codeless_env.sps_env;
    uint8_t conidx=0;
    uint16_t mtu = gattc_get_mtu(conidx);

    sps_env->mtu = mtu;
    sps_env->tx_size =  mtu-3;
}
#endif

void user_on_update_params_complete (void)
{
    #ifdef USE_AT_BINARY_MODE
    struct sps_env_t *sps_env = &codeless_env.sps_env;
    uint8_t conidx=0;

    if( sps_env->peer_supports_dle )
    {
        //arch_printf("SEND LEN REQ\r\n");
        int supportedMaxRxTime = (CFG_MAX_TX_PACKET_LENGTH + 11 + 3 ) * 8;
        app_easy_gap_set_data_packet_length(conidx, CFG_MAX_TX_PACKET_LENGTH, supportedMaxRxTime);
        user_set_default_tx_size();
        user_gattc_exc_mtu_cmd(conidx);
    }

    #endif
}

void user_on_update_params_rejected(const uint8_t reason)
{
    user_on_update_params_complete();
}

void user_on_gapc_peer_features_ind(const uint8_t conidx, struct gapc_peer_features_ind const *param)
{
    #ifdef USE_AT_BINARY_MODE
    #ifdef USE_AT_CONPAR
    struct connection_configuration_t *p_conf=&codeless_env.conn_conf;
    #endif

    check_features( (struct gapc_peer_features_ind *)param);

    #ifdef USE_AT_CONPAR
    if(p_conf->param_update_enable)
        user_param_update_start(conidx);
    #endif
    #endif
}

void get_features(void)
{
    #ifdef USE_AT_BINARY_MODE
    struct sps_env_t *sps_env = &codeless_env.sps_env;
    sps_env->peer_supports_dle = 0;

    struct gapc_get_info_cmd* info_cmd = KE_MSG_ALLOC(GAPC_GET_INFO_CMD,
                                                      KE_BUILD_ID(TASK_GAPC,0),
                                                      TASK_APP,
                                                      gapc_get_info_cmd);
    // request peer device name.
    info_cmd->operation = GAPC_GET_PEER_FEATURES;

    // send command
    KE_MSG_SEND(info_cmd);
    #endif
}

#ifdef USE_AT_RSSI
void get_rssi(void)
{
    app_gap_get_con_rssi(codeless_env.connection_index); // send rssi message
    rssi_timer=app_easy_timer(200,get_rssi); // Start the timer again with 2000 msec interval
}
#endif

static void set_connection_indicator_output(bool value)
{
   for (uint8_t i = 0; i < MAX_PIN_NUMBER; i++)
   {
        if (codeless_env.port_configuration[i] == IO_FUNC_CONN_IND_HI)
        {
            GPIO_ConfigurePin((GPIO_PORT)(i / 10), (GPIO_PIN)(i % 10), OUTPUT, PID_GPIO, value);
        }
        if (codeless_env.port_configuration[i] == IO_FUNC_CONN_IND_LO)
        {
            GPIO_ConfigurePin((GPIO_PORT)(i / 10), (GPIO_PIN)(i % 10), OUTPUT, PID_GPIO, !value);
        }
    }
}

#if defined(CFG_DATAPMP) && defined(CFG_ENTER_BINARY_MODE_ON_CONNECTION)

#define TIME_TO_ENTER_BIN_MODE_AFTER_CONN_IN_10MS (220)

void enter_binary_mode_on_connection(void)
{
    if( peer_supports_dsps())
    {
        user_execute_commands("AT+BINREQACK\r\n",CMD_SRC_LOCAL);
    }
}
#endif

void user_on_connection(uint8_t conidx, struct gapc_connection_req_ind const* param)
{
#if defined(USE_AT_BINARY_MODE)
    user_reset_peer_status_vars();
#endif

#ifdef USE_AT_HNDL
    if (user_is_handler_enabled(CONNECTION_EVENT_HANDLER))
    {
        user_execute_event_handler_commands((char*)user_get_handler_command_string(CONNECTION_EVENT_HANDLER));
    }
#endif
#if defined(USE_AT_CONPAR) && !defined(USE_AT_BINARY_MODE)
    struct connection_configuration_t *p_conf=&codeless_env.conn_conf;
#endif
    static int i=0;
    codeless_env.event_trigger=true;
    //Call the default handler for this event
#if !defined(__DA14531_01__)
    if (codeless_env.bt_role != GAP_ROLE_CENTRAL)
#endif
    {
        if (app_env[conidx].conidx != GAP_INVALID_CONIDX)
        {
             codeless_env.connection_index = conidx;

             user_exit_sleep();
             if(sleep_timer != 0)
                app_easy_timer_cancel(sleep_timer);
             sleep_timer=0;
             features_timer = app_easy_timer(60, get_features);
            // Enable the created profiles/services
            if(!i)
            {
                i=1;
                app_prf_enable(conidx);
            }
            #if BLE_APP_SEC
            if ((user_default_hnd_conf.security_request_scenario == DEF_SEC_REQ_ON_CONNECT)
                && (BLE_APP_SEC)) {
                if (get_security_and_pairing_mode() !=USER_NO_SECURITY )
                {
                    app_easy_security_request(conidx);
                }
            }
            #endif
            #ifdef USE_AT_RSSI
            // Send a message to retrieve the rssi value and start
            // a timer to retrieve the rssi value regularly
            get_rssi();
            #endif


            #if  !defined(USE_AT_BINARY_MODE)
            /* If sps is enabled, param update is performed at later stage */
            #ifdef USE_AT_CONPAR
            if(p_conf->param_update_enable)
                user_param_update_start(conidx);
            #else
            user_param_update_start(conidx);
            #endif //USE_AT_CONPAR

            user_gattc_exc_mtu_cmd(conidx);
            #endif //!USE_AT_BINARY_MODE

            #ifdef USE_AT_EVENT
            if (app_is_event_enabled(CONNECTION_EVENT))
            #endif //USE_AT_EVENT
            {
                send_to_local(CONNECTION_SUCCESSFUL_STRING);
            }
#if defined(OUTBOUND_CHAR_QUEUE)
            outbound_char_init_queue();
#endif
#if defined(CFG_DATAPMP) && defined(CFG_ENTER_BINARY_MODE_ON_CONNECTION)
            app_easy_timer(TIME_TO_ENTER_BIN_MODE_AFTER_CONN_IN_10MS, enter_binary_mode_on_connection);
#endif
        } else {
            // No connection has been established, restart advertising
            user_advertise();
        }

    }
#if !defined(__DA14531_01__)
    else // if(codeless_env.bt_role == GAP_ROLE_CENTRAL_CODELESS)
    {
        codeless_env.connection_index = conidx;
        if(sleep_timer != 0)
            app_easy_timer_cancel(sleep_timer);
        sleep_timer=0;
        //user_gattc_exc_mtu_cmd(conidx);
#ifdef USE_AT_EVENT
        if (app_is_event_enabled(CONNECTION_EVENT))
#endif
        {
            send_to_local(CONNECTION_SUCCESSFUL_STRING);
        }

        #ifdef USE_AT_RSSI
        // Send a message to retrieve the rssi value and start
        // a timer to retrieve the rssi value regularly
        get_rssi();
        #endif

        // Make a GATT characteristic discovery to identify the 16bit attribute handles of the three
        // CodeLess characteristics
        codeless_env.gap_activity = DISCOVERING;
        user_gatt_discover_chars();
    }
#endif // __DA14531_01__

    // Set the connection indication if any
    set_connection_indicator_output(true);

    // A connection parameter request must comply with certain rules for apple phones.
    // TODO:check is the following line is necessary for iphones
    // app_param_update_op(0,24,48,0, 200,12,12);

}

void user_on_connect_failed(void)
{
#if BOND_CMD_SUPPORTED
    if (codeless_env.gap_activity != BONDING) {
#else
    {
#endif
        send_to_local(CONNECTION_FAIL_STRING);
        codeless_env.gap_activity = IDLE;
    }

#ifdef CODELESS_585
    if (codeless_env.bt_role == GAP_ROLE_PERIPHERAL)
#endif
    {
        app_easy_gap_disconnect(0);
    }
}

void user_print_disconnection_string(void)
{
#if BOND_CMD_SUPPORTED
    if (codeless_env.gap_activity == BONDING) {
        send_to_local(BONDING_FAIL_STRING);
    } else if (codeless_env.gap_activity == DISCONNECTING) {
#else
    if (codeless_env.gap_activity == DISCONNECTING) {
#endif
        #ifdef USE_AT_EVENT
        if (app_is_event_enabled(DISCONNECTION_EVENT))
        #endif
        {
            send_to_local(DISCONNECTION_STRING);
        }
        send_to_local(OK_TERMINATION_STRING);
    } else {
        #ifdef USE_AT_EVENT
        if (app_is_event_enabled(DISCONNECTION_EVENT))
        #endif
        {
            send_to_local(DISCONNECTION_STRING);
        }
    }
}
void user_on_disconnect(struct gapc_disconnect_ind const* param)
{
    #ifdef USE_AT_RSSI
    // Cancel the rssi timer if valid. The function will check for invalid
    // timer handle.
    app_easy_timer_cancel(rssi_timer);
    codeless_env.rssi = 0;
    #endif
    #ifdef CFG_PRF_SUOTAR
    if (suota_state.reboot_requested)
    {
        // Reboot request will be served
        suota_state.reboot_requested = 0;
        // Platform reset
        platform_reset(RESET_AFTER_SUOTA_UPDATE);
    }
    #endif
    ke_state_set(TASK_APP, APP_CONNECTABLE);
    codeless_env.event_trigger=true;
    #ifdef USE_AT_BINARY_MODE
    if (codeless_env.binary_mode==false)
    #endif
    {
        user_exit_sleep();
        user_print_disconnection_string();
        codeless_env.gap_activity = IDLE;
    }
    #ifdef USE_AT_BINARY_MODE
    else
    {
      /*Binary mode supported but not active right now */
      user_initiate_binary_exit();
      codeless_env.disconnection_event=true;
      #ifdef CUSTS_SPSS
      user_on_sps_disconnect();
      #endif
    }
    #endif

#ifdef USE_AT_HNDL
    if (user_is_handler_enabled(DISCONNECTION_EVENT_HANDLER))
    {
        user_execute_event_handler_commands((char*)user_get_handler_command_string(DISCONNECTION_EVENT_HANDLER));
    }
#endif
#ifdef USE_AT_CONPAR
    if (codeless_env.conn_conf.restore_params)
    {
        set_default_connection_parameters(&codeless_env.conn_conf);
        codeless_env.conn_conf.restore_params = false;
    }
#endif
    // Restore the connection indicator if any
    set_connection_indicator_output(false);

    // If it had been necessary to change the pairing mode to connect restore it back
    if (restore_sec_pair_mode_on_discon_if_legacy)
    {

        restore_sec_pair_mode_on_discon_if_legacy = false;
        set_security_and_pairing_mode(USER_SECURE_CONNECTIONS_WITH_LEGACY_FALLBACK);
    }
    if ( (codeless_env.bt_role == GAP_ROLE_BROADCASTER) || (codeless_env.bt_role == GAP_ROLE_PERIPHERAL) )
    {
        user_advertise();
    }
#if defined(OUTBOUND_CHAR_QUEUE)
    outbound_char_flush_queue();
#endif
}

#if !defined (CFG_PRINTF_UART2)
void user_codeless_set_default_gpio(void)
{
    // Initially, set All IOs to undefined:
    for (uint8_t i = 0; i < MAX_PIN_NUMBER; i++) {
        codeless_env.port_configuration[i] = IO_FUNC_UNDEFINED;
    }

    codeless_env.port_configuration[UARTx_TX_GPIO_PORT * 10 + UARTx_TX_GPIO_PIN] = IO_FUNC_UART_TX;
    codeless_env.port_configuration[UARTx_RX_GPIO_PORT * 10 + UARTx_RX_GPIO_PIN] = IO_FUNC_UART_RX;

    #ifdef CFG_SPI_FLASH_ENABLE
        // For DA14531 pin assignment is direct - port is always zero
        codeless_env.port_configuration[SPI_EN_GPIO_PORT * 10 + SPI_EN_GPIO_PIN] = IO_FUNC_SPI_CS;
        codeless_env.port_configuration[SPI_CLK_GPIO_PORT * 10 +SPI_CLK_GPIO_PIN]= IO_FUNC_SPI_CLK;
        codeless_env.port_configuration[SPI_DO_GPIO_PORT * 10 + SPI_DO_GPIO_PIN] = IO_FUNC_SPI_MOSI;
        codeless_env.port_configuration[SPI_DI_GPIO_PORT * 10 +SPI_DI_GPIO_PIN]  = IO_FUNC_SPI_MISO;
    #endif

    // Set default I2C slave configuration
    #ifdef USE_AT_I2C
    user_i2c_config(CODELESS_DEFAULT_I2C_ADDR_BITS, CODELESS_DEFAULT_I2C_BITRATE,
                    CODELESS_DEFAULT_I2C_REG_BITS);
    #endif
}
#else
void user_codeless_set_default_gpio(void)
{
    // Initially, set All IOs to undefined:
    for (uint8_t i = 0; i < MAX_PIN_NUMBER; i++) {
        codeless_env.port_configuration[i] = IO_FUNC_UNDEFINED;
        if ((i % 10 == 8) || (i % 10 == 9)) {
            codeless_env.port_configuration[i] = IO_FUNC_NOT_AVAILABLE;
        }
    }
    #ifndef __DA14531__ //DA14585
    // Set P0_4 to UART1 TX
    codeless_env.port_configuration[4] = IO_FUNC_UART2_TX;
    // Set P0_5 to UART1 RX
    codeless_env.port_configuration[5] = IO_FUNC_UART2_RX;
    #else
    // Set P0_6 to UART1 TX
    codeless_env.port_configuration[6] = IO_FUNC_UART2_TX;
    // Set P0_7 to UART1 RX
    codeless_env.port_configuration[7] = IO_FUNC_UART2_RX;

    #endif
    // Set default I2C slave configuration
    user_i2c_config(CODELESS_DEFAULT_I2C_ADDR_BITS, CODELESS_DEFAULT_I2C_BITRATE,
                    CODELESS_DEFAULT_I2C_REG_BITS);
}
#endif

void user_advertise(void)
{
    struct gapm_start_advertise_cmd* cmd;

    if (codeless_env.is_connectable) {
        cmd = app_easy_gap_undirected_advertise_get_active();
    } else {
        cmd = app_easy_gap_non_connectable_advertise_get_active();
    }

    // Specify the advertise data
    cmd->info.host.adv_data_len = codeless_env.adv_data_len;
    memcpy(&cmd->info.host.adv_data, &codeless_env.adv_data, codeless_env.adv_data_len);
    // Specify scan response data (if any)
    if (codeless_env.resp_data_len > 0 && codeless_env.is_connectable) {
        cmd->info.host.scan_rsp_data_len = codeless_env.resp_data_len;
        memcpy(&cmd->info.host.scan_rsp_data, &codeless_env.resp_data, codeless_env.resp_data_len);
    } else {
        cmd->info.host.scan_rsp_data_len = 0;
    }
    // Set advertising interval
    cmd->intv_min = codeless_env.adv_intv;
    cmd->intv_max = codeless_env.adv_intv;
    // Set the advertise mode
    if (codeless_env.is_connectable)
    {
        cmd->info.host.mode = GAP_GEN_DISCOVERABLE;
        app_easy_gap_undirected_advertise_start();
    }
    else
    {
        cmd->info.host.mode = GAP_BROADCASTER_MODE;
        app_easy_gap_non_connectable_advertise_start();
    }

    // Retain the current activity state
    codeless_env.gap_activity = ADVERTISING;
}

bool is_connected(void)
{
    return (ke_state_get(TASK_APP) == APP_CONNECTED);
}

void user_on_adv_stop(const uint8_t status)
{
#if defined(CFG_USE_DYNAMIC_PRF_PERMS)
    if (get_prf_db_perms_info()->is_prf_db_perm_chg_req_received)
    {
        user_app_configuration_func(GAP_ROLE_BROADCASTER);
        get_prf_db_perms_info()->state = PRF_DB_EXEC_STATE_CHANGE_ROLE;
    }
    else
#endif
    {
        codeless_env.gap_activity = IDLE;
        if (!is_connected()) {
            send_to_local(OK_TERMINATION_STRING);
        }
    }
}
void user_on_data_length_change(ke_msg_id_t msgid,
                                        struct gapc_le_pkt_size_ind *param,
                                        ke_task_id_t const src_id)
{
    arch_printf("LE PKT SIZE TX %i %i RX %i %i\r\n", (int)param->max_tx_octets, (int)param->max_tx_time, (int)param->max_rx_octets, (int)param->max_rx_time);
}

#if defined(OUTBOUND_CHAR_QUEUE)

void user_codeless_service_read_non_db_val_handler(ke_msg_id_t const msgid,
                                           struct custs1_value_req_ind const *param,
                                           ke_task_id_t const dest_id,
                                           ke_task_id_t const src_id)
{

    struct custs1_value_req_rsp *rsp = KE_MSG_ALLOC_DYN(CUSTS1_VALUE_REQ_RSP,
                                                        prf_get_task_from_id(TASK_ID_CUSTS1),
                                                        TASK_APP,
                                                        custs1_value_req_rsp,
                                                        165);

    char* data=outbound_char_dequeue();
    ASSERT_WARNING(data!=NULL);
    // Provide the connection index.
    rsp->conidx  = app_env[param->conidx].conidx;
    // Provide the attribute index.
    rsp->att_idx = param->att_idx;
    // Set current length to the string length plus one more byte
    rsp->length  = strlen(data)+1;
    // Provide the ATT error code.
    rsp->status  = ATT_ERR_NO_ERROR;
    // Copy value
    memcpy(&rsp->value, data, rsp->length);
    // Explicitly add zero termination to the string since this is expected
    // in the air by the codeless central.The SmartConsole application does not need it.
    rsp->value[rsp->length-1]=0;

    if (data !=NULL)
    {
        ke_free(data);
    }
    // Send message
    KE_MSG_SEND(rsp);
}
#endif


void user_catch_rest_hndl(ke_msg_id_t const msgid, void const* param, ke_task_id_t const dest_id,
                          ke_task_id_t const src_id)
{
    #ifdef USE_AT_BINARY_MODE
    struct sps_env_t *sps_env = &codeless_env.sps_env;
    #endif

    switch (msgid) {
    case GAPC_PARAM_UPDATED_IND:
            __NOP();
            break;
    case CUSTS1_VAL_WRITE_IND: {
        // Peer has written to codeless (peripheral) database inbound characteristic and a write
        // notification arrived from stack.
        struct custs1_val_write_ind* msg_param = (struct custs1_val_write_ind*)(param);
        if (msg_param->handle == CUST1_IDX_INBOUND_VAL)
        {
            // When CodeLess is connected the AT+SLEEP=1 command may be issued.CodeLess will enter
            // sleep mode while connected.If a command is written to the inbound characteristic and CodeLess
            // is sleeping it has to wakeup correctly and notify the Codeless env as well.

            if (codeless_env.sleep_active)
            {
                user_exit_sleep();
            }
            user_cmd_interpreter((char*)msg_param->value, msg_param->length, CMD_SRC_REMOTE);
        }
        else if(msg_param->handle == CUST1_IDX_FLOW_CONTROL_CFG)
        {
            codeless_env.codeless_notif_enabled = ((msg_param->value[0] & 0x01) && (msg_param->value[1] == 0x00));
#if defined(USE_AT_BINARY_MODE)
            remote_codeless_support_prompt_send_to_local();
#endif //defined(USE_AT_BINARY_MODE)
        }
        #ifdef CUSTS_SPSS
        else
        {
            user_spss_val_write_ind(msg_param);
        }
        #endif
    } break;

    #ifdef CUSTS_SPSS
    case CUSTS1_VAL_NTF_CFM: {
        struct custs1_val_ntf_cfm *msg_param=(struct custs1_val_ntf_cfm*)(param);
        if (msg_param->handle==CUST1_SPSS_IDX_TX_VAL)
        {
            //Process only completion events from notifications
            if(msg_param->status == ATT_ERR_NO_ERROR)
            {
                uart_to_ble_confirm(true);
            }
            else
            {
                uart_to_ble_confirm(false);
            }
        }
        else if (msg_param->handle==CUST1_SPSS_IDX_FLOW_CONTROL_VAL)
        {
            sps_env->ble_flow_ntf_tx_cmp++;

        }
    } break;
    #endif
#ifdef CODELESS_585
    case CUSTS1_ATT_INFO_REQ: {
        struct custs1_att_info_req const* msg_param = (struct custs1_att_info_req const*)param;
        switch (msg_param->att_idx) {
        case CUST1_IDX_INBOUND_VAL:
            svc1_long_val_att_info_rsp(msgid, msg_param, dest_id, src_id);
            break;

        default:
            svc1_rest_att_info_rsp(msgid, msg_param, dest_id, src_id);
            break;
        }
    } break;
#endif

    case GATTC_DISC_CHAR_IND: {
        struct gattc_disc_char_ind const* msg_param = (struct gattc_disc_char_ind const*)param;

        // Store CodeLess characteristics' 16bit handles in CodeLess environment
        if (memcmp(&msg_param->uuid, codeless_const_env.char_uuid_inbound, 16) == 0) {
            codeless_env.hdl_inbound_val = msg_param->pointer_hdl;
#if defined(USE_AT_BINARY_MODE)
            remote_codeless_support_prompt_send_to_local();
#endif //defined(USE_AT_BINARY_MODE)
        }
        if (memcmp(&msg_param->uuid, codeless_const_env.char_uuid_outbound, 16) == 0) {
            codeless_env.hdl_outbound_val = msg_param->pointer_hdl;
        }
        if (memcmp(&msg_param->uuid, codeless_const_env.char_uuid_flow_ctrl, 16) == 0) {
            // Store handle to client configuration of flow control characteristic
            codeless_env.hdl_flow_ctrl = msg_param->pointer_hdl; // Client configuration attribute
            // Set client configuration notification flag
            uint16_t data = 0x0001;
            user_prf_gatt_write(codeless_env.hdl_flow_ctrl+1, (uint8_t *)&data, sizeof(uint16_t),  GATTC_WRITE, 0);
        }

        #ifdef USE_AT_BINARY_MODE

        if (memcmp(&msg_param->uuid, codeless_const_env.dsps_char_uuid_tx, 16) == 0) {
            codeless_env.hdl_dsps_tx_val = msg_param->pointer_hdl;
            uint16_t data = 0x0001;
            // Set client configuration notification flag
            user_prf_gatt_write(codeless_env.hdl_dsps_tx_val+1, (uint8_t *)&data, sizeof(uint16_t),  GATTC_WRITE, 0);
            sps_env->tx_flow_en = true;
            sps_env->rx_flow_en = true;
#if defined(USE_AT_BINARY_MODE)
            remote_dsps_support_prompt_send_to_local();
#endif //defined(USE_AT_BINARY_MODE)
        }
        if (memcmp(&msg_param->uuid, codeless_const_env.dsps_char_uuid_rx, 16) == 0) {
            codeless_env.hdl_dsps_rx_val = msg_param->pointer_hdl;
        }
        if (memcmp(&msg_param->uuid, codeless_const_env.dsps_char_uuid_flow_ctrl, 16) == 0) {
            // Store handle to client configuration of flow control characteristic
            codeless_env.hdl_dsps_flow_ctrl = msg_param->pointer_hdl; // Client configuration attribute
            // Set client configuration notification flag
            uint16_t data = 0x0001;
            user_prf_gatt_write(codeless_env.hdl_dsps_flow_ctrl+1, (uint8_t *)&data, sizeof(uint16_t),  GATTC_WRITE, 0);

            sps_env->tx_flow_en = true;
            sps_env->rx_flow_en = true;
        }
        #endif
    } break;

    case GATTC_CMP_EVT: {
        if (codeless_env.gap_activity == DISCOVERING) {
            codeless_env.gap_activity = IDLE;
            send_to_local(OK_TERMINATION_STRING);
        }
        #ifdef USE_AT_BINARY_MODE
        struct gattc_cmp_evt *param_2 =  (struct gattc_cmp_evt  *) param;
        if(param_2->operation == GATTC_WRITE_NO_RESPONSE)
        {
            /* Filter only data tx */
            if( param_2->seq_num!= 0xFE32)
                return;
            if(param_2->status== ATT_ERR_NO_ERROR)
            {
                uart_to_ble_confirm(true);
            }
            else
            {
                uart_to_ble_confirm(false);
            }

        }
        #endif
    } break;

    case GAPC_CMP_EVT: {
#if BOND_CMD_SUPPORTED
        struct gapc_cmp_evt const * msg_param = (struct gapc_cmp_evt const*)param;
        if (msg_param->operation == GAPC_GET_CON_RSSI) {
            // do nothing
        }
        else if (msg_param->operation == GAPC_ENCRYPT)
        {
            if(((struct gapc_cmp_evt const*)param)->status==SMP_ERROR_ENC_KEY_MISSING)
            {
                CALLBACK_ARGS_0(user_app_bond_db_callbacks.app_on_encrypt_key_missing)
            }
        }
        else if (codeless_env.gap_activity != BONDING) {
            /*
            Do not send an OK. If events are enabled an unsolicited message
            will be printed. Otherwise do not print anything.
            */
            // send_to_local(OK_TERMINATION_STRING);
        } else {
            codeless_env.gap_activity = DISCOVERING;
            user_gatt_discover_chars();
        }
#endif //BOND_CMD_SUPPORTED
    } break;

    case GATTC_EVENT_IND: {
        struct gattc_event_ind const* msg_param = (struct gattc_event_ind const*)param;
        // Only notifications from the flow-control handle are accepted
        if ((msg_param->handle == codeless_env.hdl_flow_ctrl)
            && (msg_param->type == GATTC_NOTIFY)) {
            struct gattc_read_cmd* req = KE_MSG_ALLOC_DYN(
            GATTC_READ_CMD, KE_BUILD_ID(TASK_GATTC, 0), TASK_APP, gattc_read_cmd, 2);
            req->nb = 1;
            req->operation = GATTC_READ;
            req->req.simple.offset = 0;
            req->req.simple.length = 0;
            req->req.simple.handle = codeless_env.hdl_outbound_val;
            KE_MSG_SEND(req);

        }
        #ifdef USE_AT_BINARY_MODE
        if (msg_param->handle == codeless_env.hdl_dsps_tx_val)
        {
            if(codeless_env.binary_mode==true)
            {
                user_sps_ble_rx_buffer((void *)msg_param->value, msg_param->length);
            }
        }
        else if (msg_param->handle == codeless_env.hdl_dsps_flow_ctrl)
        {
            if(msg_param->value[0] == FLOW_ON)
            {
                codeless_env.sps_env.tx_flow_en = true;
            }
            else if (msg_param->value[0] == FLOW_OFF)
            {
                codeless_env.sps_env.tx_flow_en = false;
            }
        }
        #endif

    } break;

    case GATTC_READ_IND: {
        // codeless (central)got notified that peers outbound characteristic has been written and
        // gatt-read it.
        struct gattc_read_ind* msg_param = (struct gattc_read_ind*)param;
        user_cmd_interpreter((char*)msg_param->value, msg_param->length, CMD_SRC_REMOTE);
    } break;

    case USER_APP_CMD_RECEIVED: { // Command arrived from local source or command sequencer
        // Explicitly dont allow going to sleep (done for X10msec timer on startup)
        codeless_env.user_allow_to_go_to_sleep_flag = false;
        // Before interpreting any local command,
        // Stop any ongoing GAP central activity
        // and handled when the command message is parsed
        if (codeless_env.gap_activity == INITIATING_CONNECTION
            || codeless_env.gap_activity == SCANNING || codeless_env.gap_activity == DISCOVERING) {
            // Create a GAP activity cancel message
            struct gapm_cancel_cmd* cmd = app_gapm_cancel_msg_create();
            // Send the message
            app_gapm_cancel_msg_send(cmd);
        } else // Regular command
        {
            // if cmd dest is remote, send command to remote peer - otherwise interpret locally
            struct user_app_cmd_received* msg_param = (struct user_app_cmd_received*)(param);
            user_cmd_interpreter((char*)msg_param->cmd_buffer, msg_param->bytes,
                                 (CMD_SRC_t)msg_param->cmd_source);
        }
    } break;

    case GATTC_MTU_CHANGED_IND: {
        #ifdef USE_AT_BINARY_MODE
        struct gattc_mtu_changed_ind const* msg_param = (struct gattc_mtu_changed_ind const*)param;
        codeless_env.sps_env.mtu = msg_param->mtu;
        codeless_env.sps_env.tx_size = msg_param->mtu-3;
        #endif
    } break;
#if defined(OUTBOUND_CHAR_QUEUE)
    // When the remote peer reads the codeless outbound characteristic this case will be executed
    case CUSTS1_VALUE_REQ_IND:
    {
        user_codeless_service_read_non_db_val_handler(msgid,param,dest_id,src_id);
    }
    break;
#endif
    }
}


void user_on_adv_report_ind(struct gapm_adv_report_ind const* param)
{
    // Dump Scan report to UART
    char address_type = 'R';
    if (param->report.adv_addr_type == 0) {
        address_type = 'P';
    }
    char codeless_service = ' ';
    if (param->report.data_len > 20) // Must have at least 21 bytes to be a CodeLess device
    {
#if defined (LEGACY_SERVICE_REPORT)
        if (memcmp(&param->report.data[5], codeless_const_env.service_uuid, 16) == 0)
        {
            codeless_service = '*';
        }
        #ifdef USE_AT_BINARY_MODE
        if (memcmp(&param->report.data[5], codeless_const_env.dsps_service_uuid, 16) == 0)
        {
            codeless_service = '*';
        }
        #endif
#else
      if ((memcmp(&param->report.data[5], codeless_const_env.service_uuid, 16) == 0) || (memcmp(&param->report.data[5], codeless_const_env.dsps_service_uuid, 16) == 0))
      {
         codeless_service = '*';
      }
#endif
    }
    if (param->report.evt_type == 0x00 || param->report.evt_type == 0x04) // Only ADV_IND and SCAN_RESPONSE
    {
        // Was it a normal advertising or a scan response?
        char* type_str = "ADV\0";
        if (param->report.evt_type == 0x04) {
            type_str = "RSP\0";
        }
        char adv_rep_str[120]={0};
        char scan_rsp_str[65]={0};
        arch_sprintf(adv_rep_str, "(%c) %02X:%02X:%02X:%02X:%02X:%02X,%c, Type: %s, RSSI:%d\r\n",
                     codeless_service, param->report.adv_addr.addr[5],
                     param->report.adv_addr.addr[4], param->report.adv_addr.addr[3],
                     param->report.adv_addr.addr[2], param->report.adv_addr.addr[1],
                     param->report.adv_addr.addr[0], address_type, type_str,
                     param->report.rssi - 255);

        if ((param->report.evt_type == 0x04) && (param->report.data_len > 0) && param->report.data[0]>=2)
        {
            // param->report.data[0]:length of the data.The length itself is not counted.The param->report.data[0]
            // must be at least equal to 2 for a scan response to be available
            // param->report.data[1]:type of data
            // param->report.data[2]:First character of the scan response
            // If there is one non-printable character in scan response print all character in
            // hex format

            const uint8_t scan_rsp_data_len = param->report.data[0]-1;
            const uint8_t *scan_rsp_data = &param->report.data[2];

            bool is_scan_rsp_printable = true;
            for (uint8_t i=0;i < scan_rsp_data_len;i++)
            {
                if ((scan_rsp_data[i] < ' ') || (scan_rsp_data[i] > '~'))
                {
                    is_scan_rsp_printable = false;
                    break;
                }
            }
            if (is_scan_rsp_printable)
            {
                memcpy(scan_rsp_str,scan_rsp_data, scan_rsp_data_len);
                // The two \r\n characters in adv_rep_str must be erased
                arch_sprintf(adv_rep_str+strlen(adv_rep_str)-2,", RSP:%s\r\n",scan_rsp_str);
            }
            else
            {
                for (uint8_t j=0;j< scan_rsp_data_len;j++)
                {
                    arch_sprintf(scan_rsp_str+2*j,"%02X", scan_rsp_data[j]);
                }
                arch_sprintf(adv_rep_str+strlen(adv_rep_str)-2,", RSP:0x%s\r\n",scan_rsp_str);
            }
        }
        send_to_local(adv_rep_str);
    }
}

void user_scan_completed(uint8_t status)
{
    send_to_local(SCAN_COMPLETE_STRING);
    codeless_env.gap_activity = IDLE;
}

void user_on_dev_config_complete(void)
{
    // Disable sleep - Device will go to sleep only if explicitly asked with AT+SLEEP=1 command
    arch_disable_sleep();

    // Freeze the watchdog
    // wdg_freeze();

    // Perform initialization only for startup - not due to ble role change.


    if (codeless_env.bt_role == GAP_ROLE_NONE)
    {
        // Sets IO configuration to codeless initial default.
        user_codeless_set_default_gpio();
        // Indicate the status via serial port
#ifdef USE_AT_EVENT
        if (app_is_event_enabled(INITIALIZATION_EVENT))
#endif
        {
            send_to_local(INIT_STRING);
        }
        // Call the default handler for this event
        default_app_on_set_dev_config_complete();
        // Explicitly set sleep flag to true.
        codeless_env.user_allow_to_go_to_sleep_flag = true;
        // Start a timer to enter sleep 10 seconds after bootup,
        // unless a '@' or <CR> character is received via UART
        //sleep_timer = app_easy_timer(CODELESS_SLEEP_AFTER_X10MSEC, user_prepare_sleep);

        codeless_env.bt_role = GAP_ROLE_PERIPHERAL;

       // Advertise on init.
        codeless_env.is_connectable = true;
        codeless_env.adv_intv = user_adv_conf.intv_min;
       //Try to start advertising
        //user_advertise(); //Fails to complete DB init

    }
    else
    {
#if defined(CFG_USE_DYNAMIC_PRF_PERMS)
        prf_db_perms_info_t *info = get_prf_db_perms_info();
        if (info->is_prf_db_perm_chg_req_received)
        {
            if (PRF_DB_EXEC_STATE_CHANGE_ROLE == info->state)
            {
                // app_easy_timer(10, conf_timer_callback);
                user_app_configuration_func(info->conf.original_bt_role);
                info->state = PRF_DB_EXEC_STATE_RESTORE_ROLE;
            }
            else if (PRF_DB_EXEC_STATE_RESTORE_ROLE == info->state)
            {
#if defined(CFG_PRF_SUOTAR)
                extern void app_suotar_create_db(void);
                app_suotar_create_db();
#endif
                extern void app_custs1_create_db(void);
                app_custs1_create_db();

                if (info->conf.original_gap_activity == ADVERTISING)
                {
                    user_advertise();
                }
                info->is_prf_db_perm_chg_req_received = false;
                // This is the OK termination string for the AT+SEC command
                send_to_local(OK_TERMINATION_STRING);
            }
        }
        else
#endif
        {
            // report the following in case of ble role change.
            codeless_env.gap_activity = IDLE;
            send_to_local(OK_TERMINATION_STRING);
        }
    }

    // Load generated static random address into registers
    uint32_t bdaddr_lsb = 0x00000000;
    uint32_t bdaddr_msb = 0x00000000;
    uint8_t addr[6];
    memcpy(&addr, &user_injected_bd_address, 6);
    memcpy(&bdaddr_lsb, &addr[0], 4);
    memcpy(&bdaddr_msb, &addr[4], 2);
    SetWord32(BLE_BDADDRL_REG, bdaddr_lsb);

#ifndef USER_CFG_ADDRESS_MODE
    #error USER_CFG_ADDRESS_MODE should be always defined
#else
    #if (USER_CFG_ADDRESS_MODE==APP_CFG_ADDR_PUB)
    SetWord32(BLE_BDADDRU_REG, bdaddr_msb + 0x00000); // Public address
    #elif (USER_CFG_ADDRESS_MODE==APP_CFG_ADDR_STATIC)
    SetWord32(BLE_BDADDRU_REG, bdaddr_msb + 0x10000); // Random static address so add 0x10000
    #endif
#endif


    if (console_env.parser_flag == CHAR_PARSER_NOT_ACTIVE) {
        // set charachter parser flag to active.
        console_env.parser_flag = CHAR_PARSER_ACTIVE;
        console_env.input_cmd_char_index = 0;
        user_codeless_uart_start();
        uart_sps_flow_on();
    }
    #ifdef CUSTS_SPSS
    user_init_queues();
    #endif
}

void user_app_on_init(void)
{
    // Create a static, random, Bluetooth Device Address
#if defined(CFG_USE_GENERATED_BLUETOOTH_ADDRESS)
    user_injected_bd_address = generate_random_bd_addr();
#else
    user_injected_bd_address = get_bd_addr_from_otp_or_nvds();
#endif
    default_app_on_init();
    // Set initial Bluetooth role
#ifdef CODELESS_585
    codeless_env.bt_role = GAP_ROLE_NONE;
#endif

    // Set the application state
    codeless_env.gap_activity = IDLE;
    codeless_env.adv_intv = user_adv_conf.intv_min;
    console_env.echo = true;
    console_env.error_report_flag = true;

    #ifdef USE_AT_BINARY_MODE
    codeless_env.binary_mode=false;
    codeless_env.escape_time1=MSEC_TO_ESC_TIMER1(CODELESS_DEFAULT_ESC_TIME1); //1sec
    codeless_env.escape_time2=MSEC_TO_ESC_TIMER2(CODELESS_DEFAULT_ESC_TIME2); //1sec
    codeless_env.escape_chars[0]='+';
    codeless_env.escape_chars[1]='+';
    codeless_env.escape_chars[2]='+';
    codeless_env.escape_chars_command_input=0x2B2B2B;
    #endif

    codeless_env.is_tk_entry_pending = false;

    // Specify the advertise data

    #ifdef USE_AT_FLOWCONTROL
    codeless_env.flow_control_enabled=false;
    #endif

    #ifdef USE_AT_CONPAR
    struct connection_configuration_t *p_conf=&codeless_env.conn_conf;
    p_conf->dle_en=true;
    p_conf->dle_tx_pkt_len=CFG_MAX_TX_PACKET_LENGTH;
    p_conf->dle_rx_pkt_len=CFG_MAX_RX_PACKET_LENGTH;
    p_conf->max_mtu=user_gapm_conf.max_mtu;
    #endif

    #ifdef USE_AT_HOSTSLP
    codeless_env.hst_sleep_mode=HOSTSL_DEFAULT_SLP_MODE;
    codeless_env.hst_sleep_wakeup_byte=HOSTSL_DEFAULT_WKUP_BYTE;
    codeless_env.hst_sleep_wakeup_retry_interval=HOSTSL_DEFAULT_WKUP_INTERVAL;
    codeless_env.hst_sleep_wakeup_retry_times=HOSTSL_DEFAULT_WKUP_TRIES;
    #endif

    #ifdef USE_AT_BINARY_MODE
    const uint8_t advertisement_data[] =
    #else
    uint8_t advertisement_data[] =
    #endif
    { // Complete list of 128bit service UUIDs
    #ifdef USE_AT_BINARY_MODE
        17, GAP_AD_TYPE_COMPLETE_LIST_128_BIT_UUID, SPS_SERV_ADV_UUID_REV_BYTES,
    #else
        17, GAP_AD_TYPE_COMPLETE_LIST_128_BIT_UUID, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    #endif
         3, GAP_AD_TYPE_MORE_16_BIT_UUID, 0xF5, 0xFE, //SUOTA Service
      // Bluetooth Device Name
         5, GAP_AD_TYPE_SHORTENED_NAME,
         USER_DEVICE_NAME[0],
         USER_DEVICE_NAME[1],
         USER_DEVICE_NAME[2],
         USER_DEVICE_NAME[3]
    };
    #ifndef USE_AT_BINARY_MODE
    for (uint8_t i = 0; i < 16; i++) {
            advertisement_data[2 + i] = codeless_const_env.adv_service_uuid[i];
    }
    #endif


    memcpy(&codeless_env.adv_data, &advertisement_data, sizeof(advertisement_data));

    codeless_env.adv_data_len = sizeof(advertisement_data);

    // Set scan response data where the full CodeLess name is shown
    codeless_env.resp_data[0] = USER_DEVICE_NAME_LEN + 1;
    codeless_env.resp_data[1] = GAP_AD_TYPE_COMPLETE_NAME;

    memcpy(&codeless_env.resp_data[2], USER_DEVICE_NAME, USER_DEVICE_NAME_LEN);
    codeless_env.resp_data_len = USER_DEVICE_NAME_LEN + 2;

    // set codeless to connectable.
    codeless_env.is_connectable = true;
    // Initialize input command index to zero.
    console_env.input_cmd_char_index = 0;
    // Initialize parser flag
    console_env.parser_flag = CHAR_PARSER_NOT_ACTIVE;
#if defined(USE_AT_BND)
    #if (BLE_APP_SEC)
        // The bdb should be initialized once if the bonding commands are
        // included. The security should be enabled as well otherwise the
        // bond commands do not make sense.
        default_app_bdb_init();
    #else
        #warning "Bonding commands are included but security is disabled;No bonding commands will be available"
    #endif
#endif
#if defined(USE_AT_HNDL)
    // The hdb should be initialized once if the handler commands are
    // included
    app_hdb_init();
#endif

#if defined(USE_AT_CONPAR) || defined(USE_AT_MAXMTU) || defined(USE_AT_DLEEN)
    app_cpdb_init();
    app_load_cpdb_conf_from_flash(&codeless_env.conn_conf);
#endif

#if defined (USE_AT_EVENT)
    // The events database should be initialized once if the event command
    // is included
    app_evdb_init();
#endif

}

void user_app_resume_from_sleep(void)
{
    // set parser flag to not active.
    console_env.parser_flag = CHAR_PARSER_NOT_ACTIVE;
}

#if BLE_APP_SEC

void user_app_on_tk_exch(uint8_t conidx, struct gapc_bond_req_ind const *param)
{
    bool accept = false;
    uint32_t passkey;
    uint8_t key_length = 0;

    if (param->data.tk_type == GAP_TK_OOB)
    {
        /* Do nothing - OOB data not present */
    }
    else if (param->data.tk_type == GAP_TK_DISPLAY)
    {
#if defined (CFG_PRINTF)
        passkey = app_sec_gen_tk();

        char buffer[20];
        arch_sprintf(buffer, "\r\n+PIN:%06u\r\n", passkey);
        send_to_local(buffer);

        accept = true;
        key_length = sizeof(passkey);
#endif
    }
    else if (param->data.tk_type == GAP_TK_KEY_ENTRY)
    {
        /* Do not reply and wait for user input */
        codeless_env.is_tk_entry_pending = true;
        return;
    }
#if (ENABLE_SMP_SECURE)
    else if (param->data.tk_type == GAP_TK_KEY_CONFIRM)
    {
        // Numeric Comparison - Auto-Confirm
        accept = true;

#if defined (CFG_PRINTF) && (BOND_CMD_SUPPORTED)
        uint32_t passkey;
        // Print the 6 Least Significant Digits of Passkey
        char buf[6];
        passkey = (param->tk.key[0] <<  0) | (param->tk.key[1] <<  8) |
                  (param->tk.key[2] << 16) | (param->tk.key[3] << 24);
        arch_printf("\r\nConfirmation Value: ");
        for (uint8_t i = 0; i < 6; i++)
        {
            buf[5 - i] = passkey % 10;
            passkey /= 10;
        }
        for (uint8_t i = 0; i < 6; i++)
        {
            arch_printf("%u", buf[i]);
        }
#endif
    }
#endif // ENABLE_SMP_SECURE

    app_easy_security_tk_exch(conidx, (uint8_t *)&passkey, key_length, accept);
}
#endif

#if BOND_CMD_SUPPORTED
void user_on_security_req_ind(uint8_t auth)
{
    send_to_local(SECURITY_REQUEST_RECV_STRING);
    user_security_send_encrypt_cmd(0);
}
#endif //BOND_CMD_SUPPORTED

void user_on_pairing_succeeded(uint8_t conidx)
{
#if defined(CODELESS_585)
#if !defined(__DA14531_01__)
    if (codeless_env.bt_role == GAP_ROLE_CENTRAL)

    {
        send_to_local(BONDING_SUCCEED_STRING);
    }
#endif
#else
    send_to_local(BONDING_SUCCEED_STRING);
#endif
}

void user_on_pairing_failed(uint8_t conidx)
{
    send_to_local(BONDING_FAIL_STRING);
    app_easy_gap_disconnect(0);
}

void user_app_generate_static_random_addr(struct bd_addr* addr)
{
    memcpy(&addr->addr, &user_injected_bd_address, sizeof(user_injected_bd_address));
}

#if (BLE_APP_SEC)
void user_app_on_addr_solved_ind(const uint8_t conidx, struct gapm_addr_solved_ind const * param)
{
    /*
    We received a bluetooth address on connection and we requested from the controller to resolve it.
    Apparently the result was successful,meaning that a previously bonded device has been connected.
    Therefore amongst other things we need to update the timestamp of this connection so that it is the most
    recent connection in the list. We replicate the code from the default_app_on_addr_solved_ind with a small
    modification which handles the slot update.
    */

    const struct app_sec_bond_data_env_tag *pbd = NULL;


    // Search DB by peer's IRK
    pbd = app_easy_security_bdb_search_entry(SEARCH_BY_IRK_TYPE, (void *) &param->irk, sizeof(struct gap_sec_key));

    // If peer has been found in DB
    if(pbd)
    {
        // Store device bond data to security environment
        app_sec_env[conidx] = *pbd;
        // Accept encryption
        app_easy_security_accept_encryption(conidx);
        //The slot with the param->irk is pbd->bdb_slot
        update_db_slot_timestamp_on_connection(pbd->bdb_slot);
    }
    // If peer has not been found in DB
    else
    {
        // Reject encryption, disconnect
        app_easy_security_reject_encryption(conidx);
    }
}

void user_app_on_addr_resolve_failed(uint8_t conidx)
{
    //For the time being this is the only action here
    app_easy_security_reject_encryption(conidx);
}
#endif //(BLE_APP_SEC)

void user_on_db_init_complete(void)
{

    default_app_on_db_init_complete();
}

arch_main_loop_callback_ret_t user_on_system_powered(void)
{

    #if defined(CFG_BLE_METRICS) && defined(CFG_PRINTF)
    user_statistics();
    #endif

    return GOTO_SLEEP;
}

arch_main_loop_callback_ret_t user_on_ble_powered(void)
{
#ifdef CUSTS_SPSS
    struct sps_env_t *p_env = &codeless_env.sps_env;

    if ( codeless_env.binary_mode==false )
        return GOTO_SLEEP;

    switch( p_env->power_on_state )
    {
        case PON_STATE_IDLE:
            if( !is_connected() )
                break;

            /* controlled by remote host but will lock in binary mode*/
            /*
            if(p_env->tx_flow_en==0)
                break;
            */
            if (app_default_sleep_mode == ARCH_EXT_SLEEP_ON)
            {
                bool check=ke_check_msg_alloc(ELEMENT_SIZE_RX);
                if((p_env->lists_initialized == true) && check)
                {
                    user_set_uart_to_dsps_settings();
                    uart_rx_activate();
                    #if (UART_HW_FLOW_ENABLED)
                    #if defined(USE_AT_FLOWCONTROL)
                    #if defined(__DA14531__)
                    GPIO_ConfigurePin((GPIO_PORT)0, (GPIO_PIN) codeless_env.rts_pin, OUTPUT, PID_UART1_RTSN, true );
                    #else
                    GPIO_ConfigurePin((GPIO_PORT) codeless_env.rts_port, (GPIO_PIN) codeless_env.rts_pin, OUTPUT, PID_UART1_RTSN, true );
                    #endif
                    #else
                    GPIO_ConfigurePin(GPIO_UARTx_RTS_PORT, GPIO_UARTx_RTS_PIN, OUTPUT, PID_UART1_RTSN, true );
                    #endif // USE_AT_FLOWCONTROL
                    #endif // UART_HW_FLOW_ENABLED
                    uart_sps_flow_on();
                    p_env->power_on_state = PON_STATE_WAIT_RTS;
                }
            }
            else
            {
                p_env->power_on_state = PON_STATE_WAIT_RTS;
            }
            /* Falls through - No break */
        case PON_STATE_WAIT_RTS:
           sps_uart_tx_async();
           user_check_uart_rx_to();
           sps_uart_to_ble();
           uart_rx_reactivate();
           uart_test_tx_queue_for_flow_on();

        break;
        default:
        break;
    }
#endif
    return GOTO_SLEEP;

}

void user_before_sleep(void)
{
    #ifdef USE_AT_BINARY_MODE
    if ( codeless_env.binary_mode==true )
    {
        user_sps_sleep_check();
    }
    #endif
}

void user_app_on_pairing_request(uint8_t conidx, struct gapc_bond_req_ind const *param)
{
    #if defined(USE_AT_SEC)
    if ((param->request == GAPC_PAIRING_REQ) && (param->data.auth_req & GAP_AUTH_SEC)==0)
    {
        // The remote party has requested pairing but does not support secure connections
        // Therefore the authorization mode should be adjusted if legacy fallback is supported
        if (get_security_and_pairing_mode() == USER_SECURE_CONNECTIONS_WITH_LEGACY_FALLBACK)
        {
            // Revert to legacy mode
            if ((param->data.auth_req & GAP_AUTH_MITM)==GAP_AUTH_MITM)
            {
                set_security_and_pairing_mode(USER_LEGACY_PAIRING_WITH_PASSKEY);
                restore_sec_pair_mode_on_discon_if_legacy = true;
            }
            else // Lower authorization requirements even more
            {
                set_security_and_pairing_mode(USER_JUST_WORKS_WITH_ENCRYPTION);
                restore_sec_pair_mode_on_discon_if_legacy = true;
            }
        }
    }
    #endif
    app_easy_security_send_pairing_rsp(conidx, param);
}

#if BOND_CMD_SUPPORTED
// Security for the central case

 /**
 ****************************************************************************************
 * @brief Initial pairing->bonding process. to connected device
 *
 ****************************************************************************************
 */

void user_security_send_bond_req(uint8_t conidx)
{
    send_to_local(BOND_REQ_STRING);
    struct gapc_bond_cmd * cmd = KE_MSG_ALLOC(GAPC_BOND_CMD, KE_BUILD_ID(TASK_GAPC, conidx), TASK_APP, gapc_bond_cmd);
    cmd->operation = GAPC_BOND;
    cmd->pairing.iocap = user_security_conf.iocap;
    cmd->pairing.oob = user_security_conf.oob;
    cmd->pairing.auth = user_security_conf.auth;
    cmd->pairing.key_size = user_security_conf.key_size;
    cmd->pairing.ikey_dist = user_security_conf.ikey_dist;
    cmd->pairing.rkey_dist = user_security_conf.rkey_dist;
    cmd->pairing.sec_req = user_security_conf.sec_req;
    KE_MSG_SEND(cmd);
}

void user_security_send_encrypt_cmd(uint8_t conidx)
{
    //Check if the device is already bonded
    const struct app_sec_bond_data_env_tag *pbd = NULL;
    pbd = app_easy_security_bdb_search_entry(SEARCH_BY_BDA_TYPE, (void *)app_env[conidx].peer_addr.addr, BD_ADDR_LEN);
    if(pbd)
    {
        send_to_local(BOND_INFO_STRING);
        struct gapc_encrypt_cmd * cmd = KE_MSG_ALLOC(GAPC_ENCRYPT_CMD,KE_BUILD_ID(TASK_GAPC, conidx), TASK_APP, gapc_encrypt_cmd);
        cmd->operation = GAPC_ENCRYPT;
        cmd->ltk = pbd->ltk;
        KE_MSG_SEND(cmd);
    }
    else
    {
        //Device not bonded, run pairing procedule
        user_security_send_bond_req(conidx);
    }
}

void user_on_enc_key_missing(void)
{
    send_to_local(PERIPH_KEY_MISSING_STRING);
    default_app_bdb_remove_entry(SEARCH_BY_BDA_TYPE, REMOVE_THIS_ENTRY,
                                 (void *)app_env[0].peer_addr.addr, BD_ADDR_LEN);
    //try to pair up again if peripheral device does not disconnect immediately
    user_security_send_bond_req(0);
}

void user_on_encrypt_ind(const uint8_t conidx, const uint8_t auth)
{
    send_to_local(ENCRYPTED_LINK_STRING);
}

#endif // BOND_CMD_SUPPORTED


/// @} APP
