/**
 ****************************************************************************************
 *
 * @file user_security.c
 *
 * @brief Functions for handling CodeLess security
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


/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "user_at_commands.h"
#include "user_config.h"
#include "user_security.h"
#include "user_codeless_env.h"
#if defined(CFG_USE_DYNAMIC_PRF_PERMS)
#include "app_prf_perm_types.h"
#include "user_gap.h"
#endif

/*
 ****************************************************************************************
 *
 * Security related configuration
 *
 ****************************************************************************************
 */


struct security_configuration user_security_conf = {
    /**************************************************************************************
     * IO capabilities (@see gap_io_cap)
     *
     * - GAP_IO_CAP_DISPLAY_ONLY          Display Only
     * - GAP_IO_CAP_DISPLAY_YES_NO        Display Yes No
     * - GAP_IO_CAP_KB_ONLY               Keyboard Only
     * - GAP_IO_CAP_NO_INPUT_NO_OUTPUT    No Input No Output
     * - GAP_IO_CAP_KB_DISPLAY            Keyboard Display
     *
     **************************************************************************************
     */
    .iocap          = GAP_IO_CAP_DISPLAY_ONLY,

    /**************************************************************************************
     * OOB information (@see gap_oob)
     *
     * - GAP_OOB_AUTH_DATA_NOT_PRESENT    OOB Data not present
     * - GAP_OOB_AUTH_DATA_PRESENT        OOB data present
     *
     **************************************************************************************
     */
     .oob            = GAP_OOB_AUTH_DATA_NOT_PRESENT,

    /**************************************************************************************
     * Authentication (@see gap_auth)
     *
     * - GAP_AUTH_REQ_NO_MITM_NO_BOND     No MITM No Bonding
     * - GAP_AUTH_REQ_NO_MITM_BOND        No MITM Bonding
     * - GAP_AUTH_REQ_MITM_NO_BOND        MITM No Bonding
     * - GAP_AUTH_REQ_MITM_BOND           MITM and Bonding
     *
     **************************************************************************************
     */
    .auth           = (GAP_AUTH_BOND | GAP_AUTH_MITM | GAP_AUTH_SEC),

    /**************************************************************************************
     * Device security requirements (minimum security level). (@see gap_sec_req)
     *
     * - GAP_NO_SEC                       No security (no authentication and encryption)
     * - GAP_SEC1_NOAUTH_PAIR_ENC         Unauthenticated pairing with encryption
     * - GAP_SEC1_AUTH_PAIR_ENC           Authenticated pairing with encryption
     * - GAP_SEC2_NOAUTH_DATA_SGN         Unauthenticated pairing with data signing
     * - GAP_SEC2_AUTH_DATA_SGN           Authentication pairing with data signing
     * - GAP_SEC_UNDEFINED                Unrecognized security
     *
     **************************************************************************************
     */
    .sec_req        = GAP_SEC1_SEC_PAIR_ENC,

     /// Encryption key size (7 to 16) - LTK Key Size
    .key_size       = KEY_LEN,

    /**************************************************************************************
     * Initiator key distribution (@see gap_kdist)
     *
     * - GAP_KDIST_NONE                   No Keys to distribute
     * - GAP_KDIST_ENCKEY                 LTK (Encryption key) in distribution
     * - GAP_KDIST_IDKEY                  IRK (ID key)in distribution
     * - GAP_KDIST_SIGNKEY                CSRK (Signature key) in distribution
     * - Any combination of the above
     *
     **************************************************************************************
     */
    .ikey_dist      = (GAP_KDIST_SIGNKEY|GAP_KDIST_IDKEY),

    /**************************************************************************************
     * Responder key distribution (@see gap_kdist)
     *
     * - GAP_KDIST_NONE                   No Keys to distribute
     * - GAP_KDIST_ENCKEY                 LTK (Encryption key) in distribution
     * - GAP_KDIST_IDKEY                  IRK (ID key)in distribution
     * - GAP_KDIST_SIGNKEY                CSRK (Signature key) in distribution
     * - Any combination of the above
     *
     **************************************************************************************
     */
    .rkey_dist      = GAP_KDIST_ENCKEY,
};

#if defined (USE_AT_SEC)

security_and_pairing_t sec_pair_mode = USER_NO_SECURITY;
bool restore_sec_pair_mode_on_discon_if_legacy __SECTION_ZERO("retention_mem_area0");

#if defined(CFG_USE_DYNAMIC_PRF_PERMS)
static prf_db_perms_info_t prf_db_perms_info __SECTION_ZERO("retention_mem_area0");
#endif

/****************************************************************************************
 * FUNCTIONS
 ****************************************************************************************/

security_and_pairing_t get_security_and_pairing_mode(void)
{
    return sec_pair_mode;
}

#if defined(CFG_USE_DYNAMIC_PRF_PERMS)

prf_db_perms_info_t* get_prf_db_perms_info(void)
{
    return &prf_db_perms_info;
}

void set_prf_db_perms_dynamically(app_prf_srv_perm_t srv_perm)
{
    app_set_prf_srv_perm(TASK_ID_CUSTS1, srv_perm);
    app_set_prf_srv_perm(TASK_ID_CUSTS2, srv_perm);
    app_set_prf_srv_perm(TASK_ID_SUOTAR, srv_perm);
/*
     In order for these changes to change effect, the device configuration must change.
     A valid configuration change can only occur when the device is not advertising. Therefore
     the following steps must take place:

     1.Stop advertising if advertising was active
     2.Change the configuration from peripheral or central to broadcaster (supported by all targets)
     3.Restore the original configuration
     4.Restore advertising if it was active
*/

    // Store the advertising/current role information so they
    // can be restored in the end
    prf_db_perms_info.conf.original_bt_role = codeless_env.bt_role;
    prf_db_perms_info.conf.original_gap_activity = codeless_env.gap_activity;

    // A callback function will be called when advertising is stopped or
    // when the configuration is changed. In either case the callback
    // must be able to tell that this was an internal request and not
    // a request issued externally by AT commands.
    prf_db_perms_info.is_prf_db_perm_chg_req_received = true;

    // Check current status  current activity state
    if (codeless_env.gap_activity == ADVERTISING)
    {
        // The stop advertising callback will be called
        app_easy_gap_advertise_stop();
        codeless_env.gap_activity = IDLE;
        get_prf_db_perms_info()->state = PRF_DB_EXEC_STATE_ADV_STOP;
    }
    else if (codeless_env.gap_activity == IDLE)
    {
        // The configuration changed callback will be called
        user_app_configuration_func(GAP_ROLE_BROADCASTER);
        get_prf_db_perms_info()->state = PRF_DB_EXEC_STATE_RESTORE_ROLE;
    }
}
#endif //


void set_security_and_pairing_mode(security_and_pairing_t new_mode)
{
#if (BOND_CMD_SUPPORTED)
    extern struct codeless_env_t codeless_env;
#endif
    switch (new_mode)
    {
        case USER_SECURE_CONNECTIONS:
        case USER_SECURE_CONNECTIONS_WITH_LEGACY_FALLBACK:
        {
#if (BOND_CMD_SUPPORTED)

            // LE Secure Connections pairing with MITM protection through passkey entry.
            if (codeless_env.bt_role == GAP_ROLE_CENTRAL)
            {
                user_security_conf.iocap = GAP_IO_CAP_KB_DISPLAY;
            }
            else
            {
                user_security_conf.iocap = GAP_IO_CAP_DISPLAY_ONLY;
            }
#else
            user_security_conf.iocap = GAP_IO_CAP_DISPLAY_ONLY;
#endif
            user_security_conf.sec_req = GAP_SEC1_SEC_PAIR_ENC;
            user_security_conf.auth = (GAP_AUTH_BOND | GAP_AUTH_MITM | GAP_AUTH_SEC);

#if defined(CFG_USE_DYNAMIC_PRF_PERMS)
            set_prf_db_perms_dynamically(SRV_PERM_SECURE);
#endif

            break;
        }
        case USER_LEGACY_PAIRING_WITH_PASSKEY:
        {
            // LE Secure Connections pairing with MITM protection through passkey entry.
#if (BOND_CMD_SUPPORTED)
            if (codeless_env.bt_role == GAP_ROLE_CENTRAL)
            {
                user_security_conf.iocap = GAP_IO_CAP_KB_DISPLAY;
            }
            else
            {
                user_security_conf.iocap = GAP_IO_CAP_DISPLAY_ONLY;
            }
#else
            user_security_conf.iocap = GAP_IO_CAP_DISPLAY_ONLY;
#endif
            user_security_conf.sec_req = GAP_SEC1_AUTH_PAIR_ENC;
            user_security_conf.auth = (GAP_AUTH_BOND|GAP_AUTH_MITM);

#if defined(CFG_USE_DYNAMIC_PRF_PERMS)
            set_prf_db_perms_dynamically(SRV_PERM_AUTH);
#endif
            break;
        }
        case USER_JUST_WORKS_WITH_ENCRYPTION:
        {
            // Unauthenticated no MITM protection with encryption
            user_security_conf.iocap = GAP_IO_CAP_NO_INPUT_NO_OUTPUT;
            user_security_conf.sec_req = GAP_SEC1_NOAUTH_PAIR_ENC;
            user_security_conf.auth = GAP_AUTH_BOND;

#if defined(CFG_USE_DYNAMIC_PRF_PERMS)
            set_prf_db_perms_dynamically(SRV_PERM_ENABLE);
#endif
            break;
        }
        case USER_NO_SECURITY:
        {
            /*
            Pairing with no authentication and no encryption - No security mode.
            This mode can be used when the information transferred is not sensitive.
            */
            user_security_conf.iocap = GAP_IO_CAP_NO_INPUT_NO_OUTPUT;
            user_security_conf.sec_req = GAP_NO_SEC;
            user_security_conf.auth = GAP_AUTH_BOND;


#if defined(CFG_USE_DYNAMIC_PRF_PERMS)
            set_prf_db_perms_dynamically(SRV_PERM_ENABLE);
#endif

            break;
        }
    }
#if (BOND_CMD_SUPPORTED)
    if (codeless_env.bt_role == GAP_ROLE_CENTRAL)
    {
        user_security_conf.ikey_dist = (GAP_KDIST_SIGNKEY|GAP_KDIST_IDKEY|GAP_KDIST_ENCKEY);
        user_security_conf.rkey_dist = (GAP_KDIST_SIGNKEY|GAP_KDIST_IDKEY|GAP_KDIST_ENCKEY);
    }
    else
    {
        user_security_conf.ikey_dist = (GAP_KDIST_SIGNKEY|GAP_KDIST_IDKEY);
        user_security_conf.rkey_dist = GAP_KDIST_ENCKEY;
    }
#endif
    sec_pair_mode = new_mode;
}

void set_restore_sec_pair_mode_flag(void)
{
    restore_sec_pair_mode_on_discon_if_legacy = true;
}

void reset_restore_sec_pair_mode_flag(void)
{
    restore_sec_pair_mode_on_discon_if_legacy = false;
}

bool is_restore_sec_pair_mode_flag_set(void)
{
    return restore_sec_pair_mode_on_discon_if_legacy;
}

#endif // USE_AT_SEC

/// @} APP
