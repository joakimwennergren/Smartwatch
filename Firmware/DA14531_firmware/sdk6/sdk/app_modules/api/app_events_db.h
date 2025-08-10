/**
 ****************************************************************************************
 *
 * @file app_events_db.h
 *
 * @brief Events database header file.
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


#ifndef _APP_EVENTS_DB_H_
#define _APP_EVENTS_DB_H_

/**
 ****************************************************************************************
 * @addtogroup APP_EVENTS_DB
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
    #define USER_CFG_APP_EVENTS_DB_USE_SPI_FLASH
#endif

/*
 * DEFINES
 ****************************************************************************************
 */

// SPI FLASH data offset
#ifndef USER_CFG_EVENTS_DB_DATA_OFFSET
    #if defined (USER_CFG_APP_EVENTS_DB_USE_SPI_FLASH)
        #if defined(__DA14585__) || defined(__DA14586__)
            #define APP_EVENTS_DB_DATA_OFFSET     (0x1B000) // This sector and the next will be used
        #elif defined(__DA14531__)
            #define APP_EVENTS_DB_DATA_OFFSET     (0x11000) // This sector and the next will be used
        #else
            #error "No configuration defined"
        #endif
    #endif
#else
    #define APP_EVENTS_DB_DATA_OFFSET     (USER_CFG_EVENTS_DB_DATA_OFFSET)
#endif // USER_CFG_EVENTS_DB_DATA_OFFSET

// Database version
#define EVENTS_DB_VERSION                 (0x0001)

// Start and end header used to mark the handlers data in memory
#define EVENTS_DB_HEADER_START            ((0xABCD) + EVENTS_DB_VERSION)
#define EVENTS_DB_HEADER_END              ((0xDCBA) + EVENTS_DB_VERSION)


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef enum 
{
    INITIALIZATION_EVENT  = 0,   // Do not modify, indexes of the events array
    CONNECTION_EVENT,            
    DISCONNECTION_EVENT,
    WAKEUP_EVENT,
    NUMBER_OF_EVENTS             // Must always be the last event - enumeration length
}
EVENTS_ENUM;

struct events_cfg_t
{
    bool is_event_enabled;      /**<  the status of the event */
};

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Do initial fetch of stored events
 * @return void
 ****************************************************************************************
 */
void app_evdb_init(void);

/**
 ****************************************************************************************
 * @brief Enable an event or disable an event
 * @param[in] event  event that will be enabled/disabled
 * @param[in] new_status  true if the event will be enabled false otherwise
 * @return none
 ****************************************************************************************
 */
void app_set_event_status(EVENTS_ENUM event, bool new_status);

/**
 ****************************************************************************************
 * @brief Disable an event
 * @param[in] event  The event that will be disabled
 * @return none
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Get the event status in a format that can be printed to the console
 * @param[out] string  A string that will be filled with the event status
 * @return none
 ****************************************************************************************
 */
void app_get_printable_event_table(char * string);

/**
 ****************************************************************************************
 * @brief Test if a specific event is enabled or not
 * @param[in] event  The specific event that will be tested
 * @return true if the event is enabled, false otherwise
 ****************************************************************************************
 */
bool app_is_event_enabled(EVENTS_ENUM event);

/// @} APP_HANDLERS_DB

#endif // _APP_HANDLERS_DB_H_
