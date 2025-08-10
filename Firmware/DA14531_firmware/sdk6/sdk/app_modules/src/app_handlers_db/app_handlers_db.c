/**
 ****************************************************************************************
 *
 * @file app_handlers_db.c
 *
 * @brief Handlers database source file 
 *
 * Copyright (C) 2018-2023 Renesas Electronics Corporation and/or its affiliates.
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
 * @addtogroup APP_HANDLERS_DB
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"
#include "app_non_volatile_storage.h"
#include "app_handlers_db.h"
#include "user_at_commands.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

 #ifdef USE_AT_HNDL

struct event_handlers_db
{
    uint16_t start_hdr;
    struct event_handlers_cfg_t event_handlers[NUMBER_OF_HANDLERS];
    uint16_t end_hdr;
};

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

static struct event_handlers_db hdb __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY

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
 * @brief Clear handler data
 * @param[in] schheduler_en  True: Enable rwip_scheduler while Flash is being erased
 *                           False: Do not enable rwip_scheduler. Blocking mode
 *
 * @return void
 ****************************************************************************************
 */

static void handlers_db_clear(bool scheduler_en)
{
    memset((void *)&hdb, 0, sizeof(struct event_handlers_db) ); // zero bond data
    hdb.start_hdr = HANDLERS_DB_HEADER_START;
    hdb.end_hdr = HANDLERS_DB_HEADER_END;
    
    hdb.event_handlers[0].handler = CONNECTION_EVENT_HANDLER;    
    hdb.event_handlers[1].handler = DISCONNECTION_EVENT_HANDLER;
    hdb.event_handlers[2].handler = WAKEUP_EVENT_HANDLER;
    
    // Store zero handlers data to external memory
    // In case of Flash (erase then write) do not enable the scheduler
    handlers_db_store_ext(scheduler_en);
}


/*
 * EXPOSED FUNCTION DEFINITIONS
 ****************************************************************************************
 */



void handlers_db_load_ext(void)
{
    #if defined (USER_CFG_APP_HANDLERS_DB_USE_SPI_FLASH)
        struct nvm_information storage_info=
        {
            .ptr_to_data = &hdb,
            .address = APP_HANDLERS_DB_DATA_OFFSET,
            .data_size = sizeof(struct event_handlers_db)
        };
        generic_load_flash(&storage_info);
    #endif
}

void handlers_db_store_ext(bool scheduler_en)
{
    #if defined (USER_CFG_APP_HANDLERS_DB_USE_SPI_FLASH)
    struct nvm_information storage_info=
    {
        .ptr_to_data = &hdb,
        .address = APP_HANDLERS_DB_DATA_OFFSET,
        .data_size = sizeof(struct event_handlers_db)
    };
    generic_store_flash(scheduler_en, &storage_info);
    #endif
}

void app_hdb_init(void)
{
    // Load handlers data from the external memory resource if available
    handlers_db_load_ext();

    // Simple check for garbage in memory (this also catches the 0xFF of cleared memory)
    if ((hdb.start_hdr != HANDLERS_DB_HEADER_START) || (hdb.end_hdr != HANDLERS_DB_HEADER_END))
    {
        handlers_db_clear(false);
    }
}

struct event_handlers_cfg_t* app_get_hdb_entry(uint8_t index)
{
    return &hdb.event_handlers[index];
}
#endif // USE_AT_HNDL


/// @} APP_HANDLERS_DB
