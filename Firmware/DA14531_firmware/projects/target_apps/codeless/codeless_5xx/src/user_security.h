/**
 ****************************************************************************************
 *
 * @file user_security.h
 *
 * @brief Security application header file.
 *
 * Copyright (C) 2020-2024 Renesas Electronics Corporation and/or its affiliates.
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

#ifndef _USER_SECURITY_H_
#define _USER_SECURITY_H_

#include "stdbool.h"
#include "stdint.h"
#include "user_codeless_env.h"

typedef enum
{
    USER_SECURE_CONNECTIONS = 0,                   // Secure connections pairing - do not modify the value
    USER_LEGACY_PAIRING_WITH_PASSKEY,              // Authenticated MITM protection
    USER_JUST_WORKS_WITH_ENCRYPTION,               // Unauthenticated MITM protection
    USER_NO_SECURITY,                              // No security
    USER_SECURE_CONNECTIONS_WITH_LEGACY_FALLBACK   // Use secure connections if the remote peer supports it.Fall back to legacy pairing if not
}
security_and_pairing_t;

#if defined(CFG_USE_DYNAMIC_PRF_PERMS)

typedef enum
{
    PRF_DB_EXEC_STATE_ADV_STOP,
    PRF_DB_EXEC_STATE_CHANGE_ROLE,
    PRF_DB_EXEC_STATE_RESTORE_ROLE,
}
prf_db_exec_state_t;

typedef struct
{
    gap_activity_t original_gap_activity;
    uint8_t original_bt_role;
}
prf_db_ble_original_conf_t;

typedef struct
{
    prf_db_ble_original_conf_t conf;
    prf_db_exec_state_t state;
    bool is_prf_db_perm_chg_req_received;
}
prf_db_perms_info_t;

#endif

/**
 ****************************************************************************************
 * @brief      Retrieves the current security and pairing mode
 *
 * @return     security_and_paiting_t, the security and pairing mode
 *****************************************************************************************
 */
security_and_pairing_t get_security_and_pairing_mode(void);

/**
 ****************************************************************************************
 * @brief      Sets the new security and pairing mode
 *
 * @param[in]  new_mode, the new security and pairing mode
 *
 * @return     void
 *****************************************************************************************
 */

void set_security_and_pairing_mode(security_and_pairing_t new_mode);

/**
 ****************************************************************************************
 * @brief      Sets the restore flag - USER_SECURE_CONNECTIONS_WITH_LEGACY_FALLBACK
 *             mode will be restored on disconnection if changed
 *
 * @return     void
 *****************************************************************************************
 */
void set_restore_sec_pair_mode_flag(void);

/**
 ****************************************************************************************
 * @brief      Clears the restore flag - USER_SECURE_CONNECTIONS_WITH_LEGACY_FALLBACK
 *             mode will not be restored on disconnection
 *
 * @return     void
 *****************************************************************************************
 */

void reset_restore_sec_pair_mode_flag(void);

/**
 ****************************************************************************************
 * @brief      Retrieves the status of the USER_SECURE_CONNECTIONS_WITH_LEGACY_FALLBACK
 *             restore flag
 *
 * @return     void
 *****************************************************************************************
 */

bool is_restore_sec_pair_mode_flag_set(void);

#if defined(CFG_USE_DYNAMIC_PRF_PERMS)
/**
 ****************************************************************************************
 * @brief      Retrieves the stored information about the permissions and current status
 *             of the profile database
 *
 * @return     prf_db_perms_info_t*
 *****************************************************************************************
 */

prf_db_perms_info_t* get_prf_db_perms_info(void);
#endif


#endif //_USER_SECURITY_H_
/// @} APP
