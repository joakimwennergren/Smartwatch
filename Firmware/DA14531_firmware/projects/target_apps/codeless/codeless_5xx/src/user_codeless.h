/**
 ****************************************************************************************
 *
 * @file user_codeless.h
 *
 * @brief codeless project header file.
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

#ifndef _USER_CODELESS_H_
#define _USER_CODELESS_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup APP_CODELESS
 *
 * @brief Codeless application callback functions.
 *
 * Callback functions that define behavior of codeless app are implemented here. Codeless
 * receives characters over uart 576008N1 and will call user_at_cmd_ready
 * everytime a return charachter is typed or the typed command has exceded maximum command length.
 * This will triger a message to at command parser callback. Messages ariving from remote (over BLE)
 * codeless device are served in user_catch_rest_hndl. Incoming messages can either be peer commands
 * or peer reply to commands that codeless device has issued to connected peer.
 * If no action is requested 10 seconds after booting, then the device will sleep.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwble_config.h"
#include "app_task.h"  // application task
#include "gapc_task.h" // gap functions and messages
#include "gapm_task.h" // gap functions and messages
#include "app.h"       // application definitions
#include "co_error.h"  // error code definitions
#include "arch_api.h"
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Event called when a Bluetooth connection is established.
 *
 * @param[in]  conidx .
 * @param[in]  gapc_connection_req_ind .
 * @param[in]  param .
 *****************************************************************************************
 */
void user_on_connection(uint8_t conidx, struct gapc_connection_req_ind const *param);

/**
 ****************************************************************************************
 * @brief Connection attempt failed or was cancelled by user.
 *****************************************************************************************
 */
void user_on_connect_failed(void);

/**
 ****************************************************************************************
 * @brief  Event triggered when an existing Bluetooth connection is terminated.
 *
 * @param[in]  gapc_disconnect_ind .
 * @param[in]  param .
 *****************************************************************************************
 */
void user_on_disconnect(struct gapc_disconnect_ind const *param);

/**
 ****************************************************************************************
 * @brief Event triggered after the stack has been successfully initialized
 *
 * This callback is trigerred once on init and every time a role change is done.
 *****************************************************************************************
 */
void user_on_dev_config_complete(void);

/**
 ****************************************************************************************
 * @brief Handles Bluetooth GATT events.
 *
 * @param[in]  msgid .
 * @param[in]  param .
 * @param[in]  dest_id .
 * @param[in]  src_id .
 *****************************************************************************************
 */
void user_catch_rest_hndl(ke_msg_id_t const msgid, void const *param, ke_task_id_t const dest_id,
                          ke_task_id_t const src_id);

/**
 ****************************************************************************************
 * @brief Codeless device starts adevrtising.
 *
 *****************************************************************************************
 */
void user_advertise(void);

/**
 ****************************************************************************************
 * @brief Called when advertising stops.
 *
 * @param[in]  status
 *****************************************************************************************
 */
void user_on_adv_stop(const uint8_t status);

/**
 ****************************************************************************************
 * @brief Display advertising reports.
 *
 * @param[in]  param  .
 *****************************************************************************************
 */
void user_on_adv_report_ind(struct gapm_adv_report_ind const *param);

/**
 ****************************************************************************************
 * @brief Event triggered after application has been successfully initialized.
 *****************************************************************************************
 */
void user_app_on_init(void);

/**
 ****************************************************************************************
 * @brief Event triggered after waking from sleep.
 *****************************************************************************************
 */
void user_app_resume_from_sleep(void);

/**
 ****************************************************************************************
 * @brief Bluetooth scan has completed.
 *
 * @param[in]  status  .
 *****************************************************************************************
 */
void user_scan_completed(uint8_t status);

/**
 ****************************************************************************************
 * @brief Event triggered after temporary key request.
 *
 * @param[in]  conidx .
 * @param[in]  param .
 *****************************************************************************************
 */
void user_app_on_tk_exch(uint8_t conidx, struct gapc_bond_req_ind const *param);

/**
 ****************************************************************************************
 * @brief Event triggered after pairing failed.
 *
 * @param[in]  conidx .
 *****************************************************************************************
 */
void user_on_pairing_failed(uint8_t conidx);

#if BOND_CMD_SUPPORTED

/**
 ****************************************************************************************
 * @brief Indication of a successful encryption on the connection
 *
 ****************************************************************************************
 */
void user_on_encrypt_ind(const uint8_t conidx, const uint8_t auth);

/**
 ****************************************************************************************
 * @brief Initial security encryption to the connection
 * if the connected device is not paired, go to the pairing process.
 ****************************************************************************************
 */
void user_security_send_encrypt_cmd(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Call back when peripheral missing previously stored bonding info and refused the encryption
 *
 ****************************************************************************************
 */
void user_on_enc_key_missing(void);

/**
 ****************************************************************************************
 * @brief Event triggered after security request from peripheral.
 *
 * @param[in]  auth_lvl .
 *****************************************************************************************
 */
void user_on_security_req_ind(const uint8_t auth_lvl);
#endif //BOND_CMD_SUPPORTED

/**
 ****************************************************************************************
 * @brief Event triggered after succesfull pairing.
 *
 * @param[in]  conidx .
 *****************************************************************************************
 */
void user_on_pairing_succeeded(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Event triggered when a static random address is assigned by the user app.
 *
 * @param[in]  addr .
 *****************************************************************************************
 */
void user_app_generate_static_random_addr(struct bd_addr *addr);

/**
 ****************************************************************************************
 * @brief User function called on address resolved indication.
 *
 * @param[in] conidx         Connection Id number
 *
 * @param[in] param          Pointer to GAPM_ADDR_SOLVED_IND message
 *
 * @return void
 *
 ****************************************************************************************
 */
void user_app_on_addr_solved_ind(const uint8_t conidx, struct gapm_addr_solved_ind const * param);

/**
 ****************************************************************************************
 * @brief Default function called on GAPM_CMP_EVT (GAPM_RESOLV_ADDR) event with
 *        status = GAP_ERR_NOT_FOUND.
 *
 * @param[in] conidx         Connection Id number
 *
 * @return void
 ****************************************************************************************
 */
 void user_app_on_addr_resolve_failed(uint8_t conidx);

/**
****************************************************************************************
* @brief User function called on database init complete
*
* @return void
****************************************************************************************
*/
void user_app_on_db_init_complete(void);

/**
****************************************************************************************
* @brief User called just before sleep
*
* @return void
****************************************************************************************
*/
void user_before_sleep(void);

/**
****************************************************************************************
* @brief Prints disconnection string
*
* @return void
****************************************************************************************
*/
void user_print_disconnection_string(void);

/**
****************************************************************************************
* @brief Parameter update aaccepted callback function
*
* @return void
****************************************************************************************
*/
void user_on_update_params_complete(void);

/**
****************************************************************************************
* @brief Parameter update rejected callback function
*
* @return void
****************************************************************************************
*/
void user_on_update_params_rejected(const uint8_t reason);

/**
****************************************************************************************
* @brief Called while system is powered
*
* @return desired sleep mode, has no effect
****************************************************************************************
*/
arch_main_loop_callback_ret_t user_on_system_powered(void);

/**
****************************************************************************************
* @brief Called while BLE is powered
*
* @return desired sleep mode, has no effect
****************************************************************************************
*/
arch_main_loop_callback_ret_t user_on_ble_powered(void);

/**
****************************************************************************************
* @brief Called when a pairing request is initiated from the remote peer
*
* @return void
****************************************************************************************
*/
void user_app_on_pairing_request(uint8_t conidx, struct gapc_bond_req_ind const *param);

/**
****************************************************************************************
* @brief Checks if device is connected
*
* @return void
****************************************************************************************
*/
bool is_connected(void);

/// @} APP

#endif // _USER_CODELESS_H_
