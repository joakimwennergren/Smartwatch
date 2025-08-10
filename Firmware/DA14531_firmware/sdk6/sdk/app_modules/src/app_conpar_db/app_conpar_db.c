/**
 ****************************************************************************************
 *
 * @file app_conpar_db.c
 *
 * @brief Connection parameters database source file.
 *
 * Copyright (C) 2019-2023 Renesas Electronics Corporation and/or its affiliates.
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
 * @addtogroup APP_CONPAR_DB
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"
#include "app_non_volatile_storage.h"
#include "app_conpar_db.h"
#include "user_at_commands.h"
#include "user_config.h"


/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

#if defined(USE_AT_CONPAR) || defined(USE_AT_MAXMTU) || defined(USE_AT_DLEEN)


struct conpar_db
{
    uint16_t start_hdr;
    struct connection_configuration_t cc;
    uint16_t end_hdr;
};

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

static struct conpar_db cpdb __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY

#if defined (USER_CFG_APP_CONPAR_DB_USE_SPI_FLASH)
    #if !NVM_DOUBLE_BUFFERING
        static struct nvm_information storage_info=
        {
            .ptr_to_data = &cpdb,
            .address = APP_CONPAR_DB_DATA_OFFSET,
            .data_size = sizeof(struct conpar_db)
        };
    #endif 
#endif
/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */


/*
 * STATIC FUNCTION DEFINITIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Store connection parameters database to external memory
 * @param[in] scheduler_en  Only used if external memory is Flash
                            True: Enable rwip_scheduler while Flash is being erased
 *                          False: Do not enable rwip_scheduler. Blocking mode
 * @return none
 ****************************************************************************************
 */

static void conpar_db_store_ext(bool scheduler_en)
{
#if defined (USER_CFG_APP_CONPAR_DB_USE_SPI_FLASH)
    #if NVM_DOUBLE_BUFFERING
        struct nvm_information storage_info=
        {
            .ptr_to_data = &cpdb,
            .address = APP_CONPAR_DB_DATA_OFFSET,
            .data_size = sizeof(struct conpar_db)
        };
    #endif
    generic_store_flash(scheduler_en, &storage_info);
#endif
}

/**
 ****************************************************************************************
 * @brief Clear connection params 
 * @param[in] scheduler_en  True: Enable rwip_scheduler while Flash is being erased
 *                          False: Do not enable rwip_scheduler. Blocking mode
 *
 * @return void
 ****************************************************************************************
 */

static void conpar_db_clear(bool scheduler_en)
{
    memset((void *)&cpdb, 0, sizeof(struct conpar_db) ); // zero bond data
    cpdb.start_hdr = CONPAR_DB_HEADER_START;
    cpdb.end_hdr = CONPAR_DB_HEADER_END;
    set_default_connection_parameters(&cpdb.cc);
    #ifdef __DA14531__
    cpdb.cc.max_mtu = 65; // TODO: Create a define for this constant
    #else
    cpdb.cc.max_mtu = 123;
    #endif
    
    cpdb.cc.dle_en = true;
    #ifdef __DA14531__
    cpdb.cc.dle_tx_pkt_len = CFG_MAX_TX_PACKET_LENGTH; // TODO: Create a define for 
    cpdb.cc.dle_rx_pkt_len = CFG_MAX_RX_PACKET_LENGTH; // these constants
    #else
    cpdb.cc.dle_tx_pkt_len = CFG_MAX_TX_PACKET_LENGTH;
    cpdb.cc.dle_rx_pkt_len = CFG_MAX_RX_PACKET_LENGTH;
    #endif
   
    // Store connection paremeters to external memory
    // In case of Flash (erase then write) do not enable the scheduler
    conpar_db_store_ext(scheduler_en);
}

/**
 ****************************************************************************************
 * @brief Load connection parameters database from external memory
 * @return none
 ****************************************************************************************
 */

static void conpar_db_load_ext(void)
{
#if defined (USER_CFG_APP_CONPAR_DB_USE_SPI_FLASH)
    #if NVM_DOUBLE_BUFFERING
    struct nvm_information storage_info=
    {
        .ptr_to_data = &cpdb,
        .address = APP_CONPAR_DB_DATA_OFFSET,
        .data_size = sizeof(struct conpar_db)
    };
    #endif
    generic_load_flash(&storage_info);
#endif
}

/*
 * EXPOSED FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void app_cpdb_init(void)
{
    // Load handlers data from the external memory resource if available
    conpar_db_load_ext();

    // Simple check for garbage in memory (this also catches the 0xFF of cleared memory)
    if ((cpdb.start_hdr != CONPAR_DB_HEADER_START) || (cpdb.end_hdr != CONPAR_DB_HEADER_END))
    {
        conpar_db_clear(false);
    }
}

void app_store_cpdb_conf_to_flash(const struct connection_configuration_t* cc_ptr)
{
    if (cc_ptr !=NULL)
    {
        memcpy((void*)&cpdb.cc,(void*)cc_ptr,sizeof(struct connection_configuration_t));
        conpar_db_store_ext(true);
    }
}

void app_load_cpdb_conf_from_flash(struct connection_configuration_t* cc_ptr)
{
    if (cc_ptr !=NULL)
    {
        conpar_db_load_ext();
        memcpy((void*)cc_ptr,(void*)&cpdb.cc, sizeof(struct connection_configuration_t));
    }
}

void set_default_connection_parameters(struct connection_configuration_t* cc)
{
    cc->connection_interval = user_connection_param_conf.intv_max; // Both intv_max and intv_min values should be the same 
    cc->latency = user_connection_param_conf.latency;
    cc->time_out = TIMERUNITS_TO_MS(user_connection_param_conf.time_out); // The _conf.time_out parameter is in timerunits
    cc->param_update_enable = true;
}

#endif // USE_AT_CONPAR

/// @} APP_CONPAR_DB
