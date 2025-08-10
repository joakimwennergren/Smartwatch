/**
 ****************************************************************************************
 *
 * @file app_conpar_db.h
 *
 * @brief Connection parameters database header file.
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

#ifndef _APP_CONPAR_DB_H_
#define _APP_CONPAR_DB_H_

/**
 ****************************************************************************************
 * @addtogroup APP_CONPAR_DB
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
#include "user_codeless_env.h"

// Support for SPI flash
#if defined (CFG_SPI_FLASH_ENABLE)
    #include "spi.h"
    #include "spi_flash.h"
    #define USER_CFG_APP_CONPAR_DB_USE_SPI_FLASH
#endif

/*
 * DEFINES
 ****************************************************************************************
 */

// SPI FLASH data offset
#ifndef USER_CFG_CONPAR_DB_DATA_OFFSET
    #if defined (USER_CFG_APP_CONPAR_DB_USE_SPI_FLASH)
        #if defined (__DA14585__) || defined(__DA14586__)
            #define APP_CONPAR_DB_DATA_OFFSET   (0x17000)
        #elif defined (__DA14531__)
            #define APP_CONPAR_DB_DATA_OFFSET   (0x0D000)
        #else
            #error "No configuration defined"
        #endif
    #endif
#else
    #define APP_CONPAR_DB_DATA_OFFSET     (USER_CFG_CONPAR_DB_DATA_OFFSET)
#endif // USER_CFG_CONPAR_DB_DATA_OFFSET

// Database version
#define CONPAR_DB_VERSION                   (0x0001)

// Start and end header used to mark the handlers data in memory
#define CONPAR_DB_HEADER_START              ((0x3456) + CONPAR_DB_VERSION)
#define CONPAR_DB_HEADER_END                ((0x6543) + CONPAR_DB_VERSION)


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Do initial fetch of stored connection parameters 
 * @return void
 ****************************************************************************************
 */
void app_cpdb_init(void);

/**
 ****************************************************************************************
 * @brief Store the connection parameters to flash
 * @param[in] cc_ptr the connection configuration that will be saved to flash
 * @return none
 ****************************************************************************************
 */
void app_store_cpdb_conf_to_flash(const struct connection_configuration_t* cc_ptr);

/**
 ****************************************************************************************
 * @brief Load the connection parameters to flash
 * @param[in] cc_ptr a pointer to a connection configuration where the information from 
                     flash will be eventually stored
 * @return none
 ****************************************************************************************
 */
void app_load_cpdb_conf_from_flash(struct connection_configuration_t* cc_ptr);

/**
 ****************************************************************************************
 * @brief Set the default connection parameters
 * @param[in] cc_ptr a pointer to a connection configuration where the default connection 
              parameters will be set
 * @return none
 ****************************************************************************************
 */
void set_default_connection_parameters(struct connection_configuration_t* cc_ptr);

/// @} APP_CONPAR_DB

#endif // _APP_CONPAR_DB_H_
