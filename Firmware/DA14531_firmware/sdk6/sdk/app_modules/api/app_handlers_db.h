/**
 ****************************************************************************************
 *
 * @file app_handlers_db.h
 *
 * @brief Handlers database header file.
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


#ifndef _APP_HANDLERS_DB_H_
#define _APP_HANDLERS_DB_H_

/**
 ****************************************************************************************
 * @addtogroup APP_HANDLERS_DB
 *
 * @brief
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"

#include "user_profiles_config.h"
#include "app_utils.h"
#include "user_periph_setup.h"
#include "user_config.h"
#include "gpio.h"

// Support for SPI flash
#if defined (CFG_SPI_FLASH_ENABLE)
    #include "spi.h"
    #include "spi_flash.h"
    #define USER_CFG_APP_HANDLERS_DB_USE_SPI_FLASH
#endif

/*
 * DEFINES
 ****************************************************************************************
 */

// SPI FLASH data offset
#ifndef USER_CFG_HANDLERS_DB_DATA_OFFSET
    #if defined (USER_CFG_APP_HANDLERS_DB_USE_SPI_FLASH)
        #if defined(__DA14585__) || defined(__DA14586__)
            #define APP_HANDLERS_DB_DATA_OFFSET     (0x19000)
        #elif defined(__DA14531__)
            #define APP_HANDLERS_DB_DATA_OFFSET     (0x0F000)
        #else
            #error "No configuration defined"
        #endif
    #endif
#else
    #define APP_HANDLERS_DB_DATA_OFFSET     (USER_CFG_HANDLERS_DB_DATA_OFFSET)
#endif // USER_CFG_HANDLERS_DB_DATA_OFFSET

// Database version
#define HANDLERS_DB_VERSION                 (0x0001)

// Start and end header used to mark the handlers data in memory
#define HANDLERS_DB_HEADER_START            ((0x5678) + HANDLERS_DB_VERSION)
#define HANDLERS_DB_HEADER_END              ((0x8765) + HANDLERS_DB_VERSION)

// Size of the AT Commands array for storing AT commands
#define MAX_HANDLER_COMMANDS_LENGTH         (50)
#define NUMBER_OF_HANDLERS                   (3)

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef enum 
{
    CONNECTION_EVENT_HANDLER = 1,   // Do not modify. Argument validation is based on this value
    DISCONNECTION_EVENT_HANDLER,
    WAKEUP_EVENT_HANDLER
}
EVENT_HANDLERS_ENUM;



struct event_handlers_cfg_t
{
    EVENT_HANDLERS_ENUM handler;                        /**<  the handler */
    bool is_handler_enabled;                            /**<  the status of the handler */
    char handler_commands[MAX_HANDLER_COMMANDS_LENGTH]; /**<  the placeholder for the at commands */
};


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Load Bond Database from external memory
 * @return none
 ****************************************************************************************
 */
void handlers_db_load_ext(void);


/**
 ****************************************************************************************
 * @brief Store handlers database to external memory
 * @param[in] scheduler_en  Only used if external memory is Flash
                            True: Enable rwip_scheduler while Flash is being erased
 *                          False: Do not enable rwip_scheduler. Blocking mode
 * @return none
 ****************************************************************************************
 */
void handlers_db_store_ext(bool scheduler_en);



/**
 ****************************************************************************************
 * @brief Do initial fetch of stored handlers data.
 * @return void
 ****************************************************************************************
 */
void app_hdb_init(void);


/**
 ****************************************************************************************
 * @brief Provide access to handlers database.
 * @param[in] index  The database entry that will be returned 
 * @return A pointer to the handlers database entry specified by index
 ****************************************************************************************
 */
struct event_handlers_cfg_t* app_get_hdb_entry(uint8_t index);


/// @} APP_HANDLERS_DB

#endif // _APP_HANDLERS_DB_H_
