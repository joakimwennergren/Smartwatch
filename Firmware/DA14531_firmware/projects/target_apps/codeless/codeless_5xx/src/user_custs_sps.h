/**
 ****************************************************************************************
 *
 * @file user_custs_sps.h
 *
 * @brief Declaration of user functions to support custom service sps server and client
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

#ifndef _USER_CUSTS_SPS_H_
#define _USER_CUSTS_SPS_H_
/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup APP_CODELESS
 *
 * @brief Codeless AT commands implementation.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "co_bt.h"
#include "user_codeless_strings.h"
#include "user_at_commands.h"
#include "user_codeless_env.h"
#include "custs1_task.h"
/*
 * DEFINES
 ****************************************************************************************
 */
/// Enumeration of flow on or off
typedef enum flow_ctrl_states
{
    FLOW_ON     = (uint8_t)0x01,
    FLOW_OFF    = (uint8_t)0x02,
}flow_ctrl_state_t;



/* These RX TX LVL's are relative to UART */
#define RX_FLOW_ON_LVL (1)
#define RX_FLOW_OFF_LVL (2)

#ifdef __DA14531__
#define TX_FLOW_ON_LVL (2)
#define TX_FLOW_OFF_LVL (4)
#else
#define TX_FLOW_ON_LVL (4)
#define TX_FLOW_OFF_LVL (8)
#endif


#define DMA_UART_RX_TO_ROUNDS 20

#define PON_STATE_IDLE          0
#define PON_STATE_INIT          1
#define PON_STATE_WAIT_RTS      2

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief  CUSTS1_VAL_WRITE_IND handler for SPS Server characteristic values (binary mode)
 *
 * @param[in]  msg_param Pointer to incoming message
 *
 * @return void
 ****************************************************************************************
 */

void user_spss_val_write_ind(struct custs1_val_write_ind* msg_param);

/**
 ****************************************************************************************
 * @brief  Initialize SPS message queues (binary mode)
 *
 * @return void
 ****************************************************************************************
 */
void user_init_queues(void);

/**
 ****************************************************************************************
 * @brief Activate UART RX for binary mode operations
 *
 * @return   true if a buffer has successfully been allocated gor RX, false otherwise
 ****************************************************************************************
 */
bool uart_rx_activate(void);

/**
 ****************************************************************************************
 * @brief Asynchronsously checks if there are buffers ready to be placed in uart tx queue.
 *        Used in BLE-> UART path
 * @return void
 ****************************************************************************************
 */
void sps_uart_tx_async(void);

/**
 ****************************************************************************************
 * @brief Asynchronsously checks if there are buffers ready to be send over BLE
 *        Used in UART->BLE path
 *
 * @return true if a buffer has successfully been pushed to BLE, false otherwise
 ****************************************************************************************
 */
bool sps_uart_to_ble (void);

/**
 ****************************************************************************************
 * @brief Called on BLE TX confirmation to resume sending
 *
 * @param[in]  success Successfully tx'd (true), or unsuccesfully (false)
 *
 * @return void
 ****************************************************************************************
 */
void uart_to_ble_confirm(bool success);

/**
 ****************************************************************************************
 * @brief  Called on ble data reception to put the new data in UART TX queue
 *
 * @param[in]  msg_param_value Pointer to incoming binary data
 *
 * @param[in]  length Length of incoming binary data
 *
 * @return void
 ****************************************************************************************
 */
void user_sps_ble_rx_buffer(void *msg_param_value, uint16_t length);

/**
 ****************************************************************************************
 * @brief Checks if the receive list queue has exceeded the limit RX_FLOW_OFF_LVL in order
 *        to deassert RTS
 *
 * @return true if flow is disabled, false otherwise
 ****************************************************************************************
 */
bool user_check_set_flow_off(void);

/**
 ****************************************************************************************
 * @brief Checks if the receive list queue is bellow limit RX_FLOW_ON_LVL in order
 *        to assert RTS
 *
 * @return true if flow is enabled, false otherwise
 ****************************************************************************************
 */
bool user_check_set_flow_on(void);

/**
 ****************************************************************************************
 * @brief Checks if UART and UART SPS should be re-asserted if uart is in  flow off
 *
 * @return void
 ****************************************************************************************
 */
void uart_rx_reactivate(void);


/**
 ****************************************************************************************
 * @brief  Checks if the UART Tx can be reactivated by comparing tx_list_ready.cnt
 *               with TX_FLOW_ON_LVL
 *
 * @return true if the Rx of data from the BLE peer can be continued, false otherwise
 ****************************************************************************************
 */
bool uart_test_tx_queue_for_flow_on(void);

/**
 ****************************************************************************************
 * @brief  Checks if the UART Tx should be deactivated by comparing tx_list_ready.cnt
 *               with TX_FLOW_OFF_LVL
 *
 * @return true if the Rx of data from the BLE peer should be blocked, false otherwise
 ****************************************************************************************
 */
bool uart_test_tx_queue_for_flow_off(void);

/**
 ****************************************************************************************
 * @brief On disconnection event places p_rx_ready_active back to rx_list_ready list
 *
 * @return void
 ****************************************************************************************
 */
void user_on_sps_disconnect(void);

/**
 ****************************************************************************************
 * @brief Initialization of local and remote flow enable flags when entering binary mode
 *
 * @return void
 ****************************************************************************************
 */
void user_init_sps(void);

/**
 ****************************************************************************************
 * @brief Checks the UART DMA Rx timeout
 *
 * @return void
 ****************************************************************************************
 */
void user_check_uart_rx_to(void);

/**
 ****************************************************************************************
 * @brief  Free all RX/TX buffers of SPS lists, called when exiting binary mode
 *
 * @return void
 ****************************************************************************************
 */
void user_free_sps_buffers(void);

/**
 ****************************************************************************************
 * @brief Forces ble flow off
 *
 * @return void
 ****************************************************************************************
 */
void user_ble_force_tx_flow_off(void);

/**
 ****************************************************************************************
 * @brief Asserts RTS signal
 *
 * @return void
 ****************************************************************************************
 */
void uart_sps_flow_on(void);

/**
 ****************************************************************************************
 * @brief  de-asserts RTS signal if uart conditions are valid
 *
 * @param[in] force Force RTS deassertion if true, or if false check first of UART is free
 *
 * @return true if RTS is deasserted, false otherwise
 ****************************************************************************************
 */
bool uart_sps_flow_off(bool force);

/**
 ****************************************************************************************
 * @brief Initialization of flow control in binary mode
 *
 * @return void
 ****************************************************************************************
 */
void uart_fc_init(void);

/**
 ****************************************************************************************
 * @brief Check if device can go to sleep
 *
 * @return void
 ****************************************************************************************
 */
void user_sps_sleep_check(void);

/**
 ****************************************************************************************
 * @brief Initialize binary mode exit
 *
 * @return void
 ****************************************************************************************
 */
void user_initiate_binary_exit(void);

/**
 ****************************************************************************************
 * @brief Activation of binary mode
 *
 * @param[in] print_ok Prints "OK\r\n" if true
 *
 * @return void
 ****************************************************************************************
 */
bool activate_binary_mode(bool print_ok);

/**
 ****************************************************************************************
 * @brief Initialize UART for codeless operation (command mode)
 *
 * @return void
 ****************************************************************************************
 */
void user_codeless_uart_start(void);

/**
 ****************************************************************************************
 * @brief Initialize SPI for codeless operation in command mode
 *
 * @return void
 ****************************************************************************************
 */
void user_codeless_spi_start(void);

/**
 ****************************************************************************************
 * @brief Disables sleep timer when entering binary mode
 *
 * @return void
 ****************************************************************************************
 */
void user_disable_sleep(void);

/**
 ****************************************************************************************
 * @brief Initializes parameters of various notifications of the SPS service
 *
 * @return void
 ****************************************************************************************
 */
void user_reset_peer_status_vars(void);

/**
 ****************************************************************************************
 * @brief Returns whether the peer device supports CODELESS
 *
 * @return true if the peer device supports CODELESS
 ****************************************************************************************
 */
bool peer_supports_codeless(void);

/**
 ****************************************************************************************
 * @brief Returns whether the peer device supports DSPS
 *
 * @return true if the peer device supports DSPS
 ****************************************************************************************
 */
bool peer_supports_dsps(void);

/**
 ****************************************************************************************
 * @brief Informs the local if the remote peers supports CODELESS
 *
 * @return void
 ****************************************************************************************
 */
void remote_codeless_support_prompt_send_to_local(void);

/**
 ****************************************************************************************
 * @brief Informs the local if the remote peers supports DSPS
 *
 * @return void
 ****************************************************************************************
 */
void remote_dsps_support_prompt_send_to_local(void);

 #endif //_USER_CUSTS_SPS_H_

/// @} APP
