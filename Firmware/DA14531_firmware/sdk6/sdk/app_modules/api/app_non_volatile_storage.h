/**
 ****************************************************************************************
 *
 * @file app_non_volatile_storage.h
 *
 * @brief Non volatile storage header file.
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

#ifndef _APP_NON_VOLATILE_STORAGE_H_
#define _APP_NON_VOLATILE_STORAGE_H_

/**
 ****************************************************************************************
 * @addtogroup APP_NON_VOLATILE_STORAGE
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


#include "app_utils.h"
#include "user_periph_setup.h"
#include "user_config.h"
#include "gpio.h"


// Support for SPI flash
#if defined (CFG_SPI_FLASH_ENABLE)
    #include "spi.h"
    #include "spi_flash.h"
#endif

/*
 * DEFINES
 ****************************************************************************************
 */
 
 #if defined(__DA14585__) || defined(__DA14586__)
 #define NVM_DOUBLE_BUFFERING (1)
 #else 
 #define NVM_DOUBLE_BUFFERING (0)
 #endif

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

struct nvm_information 
{
    void* ptr_to_data;
    uint32_t address;
    size_t data_size;
};

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Load data from flash memory
 * @param[in] storage_info  A pointer to flash memory information
 * @return void
 ****************************************************************************************
 */
void generic_load_flash(const struct nvm_information * const storage_info);


/**
 ****************************************************************************************
 * @brief Erase Flash sectors where data is stored
 * @param[in] scheduler_en  True: Enable rwip_scheduler while Flash is being erased
 *                          False: Do not enable rwip_scheduler. Blocking mode
 * @param[in] storage_info  A constant pointer to flash memory information
 * @return ret              Error code or success (ERR_OK)
 ****************************************************************************************
 */
int8_t generic_erase_flash_sectors(bool scheduler_en,const struct nvm_information * const storage_info);

/**
 ****************************************************************************************
 * @brief Store data to Flash memory
 * @param[in] scheduler_en  True: Enable rwip_scheduler while Flash is being erased
 *                          False: Do not enable rwip_scheduler. Blocking mode
 * @param[in] storage_info  A constant pointer to flash memory information
 * @return none
 ****************************************************************************************
 */
void generic_store_flash(bool scheduler_en, struct nvm_information * const storage_info);

/// @} APP_NON_VOLATILE_STORAGE

#endif // _APP_NON_VOLATILE_STORAGE_H_
