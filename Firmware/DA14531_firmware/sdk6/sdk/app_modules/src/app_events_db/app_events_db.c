/**
 ****************************************************************************************
 *
 * @file app_events_db.c
 *
 * @brief Events database source file
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
#include "app_events_db.h"
#include "arch_console.h"
#include "user_at_commands.h"


/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

#ifdef USE_AT_EVENT

struct events_db
{
    uint16_t start_hdr;
    struct events_cfg_t events[NUMBER_OF_EVENTS];
    uint16_t end_hdr;
};

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

static struct events_db evdb __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY

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
 * @brief Store events database to external memory
 * @param[in] scheduler_en  Only used if external memory is Flash
                            True: Enable rwip_scheduler while Flash is being erased
 *                          False: Do not enable rwip_scheduler. Blocking mode
 * @return none
 ****************************************************************************************
 */

void events_db_store_ext(bool scheduler_en)
{
    #if defined (USER_CFG_APP_EVENTS_DB_USE_SPI_FLASH)
    struct nvm_information storage_info=
    {
        .ptr_to_data = &evdb,
        .address = APP_EVENTS_DB_DATA_OFFSET,
        .data_size = sizeof(struct events_db)
    };
    generic_store_flash(scheduler_en, &storage_info);
    #endif
}


/**
 ****************************************************************************************
 * @brief Clear events data
 * @param[in] schheduler_en  True: Enable rwip_scheduler while Flash is being erased
 *                           False: Do not enable rwip_scheduler. Blocking mode
 *
 * @return void
 ****************************************************************************************
 */

static void events_db_clear(bool scheduler_en)
{
    memset((void *)&evdb, 0, sizeof(struct events_db) ); // zero event data
    evdb.start_hdr = EVENTS_DB_HEADER_START;
    evdb.end_hdr = EVENTS_DB_HEADER_END;
    
    for (int ii=0; ii < NUMBER_OF_EVENTS; ii++)
    {
        evdb.events[ii].is_event_enabled = true; // Enabled by default
    }    
    // Store events to external memory
    // In case of Flash (erase then write) do not enable the scheduler
    events_db_store_ext(scheduler_en);
}

/**
 ****************************************************************************************
 * @brief Load event database from external memory
 * @return none
 ****************************************************************************************
 */

void events_db_load_ext(void)
{
    #if defined (USER_CFG_APP_EVENTS_DB_USE_SPI_FLASH)
        struct nvm_information storage_info=
        {
            .ptr_to_data = &evdb,
            .address = APP_EVENTS_DB_DATA_OFFSET,
            .data_size = sizeof(struct events_db)
        };
        generic_load_flash(&storage_info);
    #endif
}

/*
 * EXPOSED FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void app_evdb_init(void)
{
    // Load handlers data from the external memory resource if available
    events_db_load_ext();

    // Simple check for garbage in memory (this also catches the 0xFF of cleared memory)
    if ((evdb.start_hdr != EVENTS_DB_HEADER_START) || (evdb.end_hdr != EVENTS_DB_HEADER_END))
    {
        events_db_clear(false);
    }
}

void app_set_event_status(EVENTS_ENUM event, bool new_status)
{
    if (event < NUMBER_OF_EVENTS)
    {
        // If the new status is the same as the old one no action is taken
        if (evdb.events[event].is_event_enabled != new_status)
        {
            evdb.events[event].is_event_enabled = new_status;
            events_db_store_ext(true);
        }
    }
}

void app_get_printable_event_table(char * string)
{
    if (string != NULL)
    {
        int n=0;
        for (int event=0; event < NUMBER_OF_EVENTS; event++)
        {
            // In the console the event table is 1 -indexed
            arch_sprintf(string+n,"%d,%d\r\n",(event+1),(int)evdb.events[event].is_event_enabled);
            n=strlen(string);
        }
    }
}

bool app_is_event_enabled(EVENTS_ENUM event)
{
    if (event < NUMBER_OF_EVENTS)
    {
        return evdb.events[event].is_event_enabled;
    }
    else 
    {
        return false;
    }    
}
#endif // USE_AT_EVENT

/// @} APP_EVENTS_DB
