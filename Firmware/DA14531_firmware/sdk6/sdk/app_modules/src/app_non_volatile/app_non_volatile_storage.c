/**
 ****************************************************************************************
 *
 * @file non_volatile_storage.c
 *
 * @brief Non volatile storage source file
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
 * @addtogroup NON_VOLATILE_STORAGE
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "app_non_volatile_storage.h"
#include "rwip_config.h"
#include "rwip.h"
#include "arch_console.h"
#include "user_profiles_config.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
#if defined(CFG_SPI_FLASH_ENABLE)

#if NVM_DOUBLE_BUFFERING
struct sequence 
{
    uint32_t sequence_number;
    uint32_t complementary_sequence_number;
};

static struct sequence seq = {0x12345678, ~0x12345678};
#endif // NVM_DOUBLE_BUFFERING

/*
 * STATIC FUNCTION DEFINITIONS
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Perform initialization of spi flash memory
 * @return void
 ****************************************************************************************
 */


static void generic_spi_flash_init(void)
{
    uint8_t dev_id;

    // Release Flash from power down
    spi_flash_release_from_power_down();

    // Try to auto-detect the device
    spi_flash_auto_detect(&dev_id);

    // Disable the SPI flash memory protection (unprotect all sectors)
    spi_flash_configure_memory_protection(SPI_FLASH_MEM_PROT_NONE);
}

#if NVM_DOUBLE_BUFFERING
void update_sequence_number_and_parameters(const struct nvm_information * const storage_info, bool restore_parameters)
{
    uint32_t actual_size =0;
    uint32_t address = 0;
    struct sequence temp_seq[2] = {{0, 0},{0, 0}};
    size_t size_of_data_to_read = storage_info->data_size + sizeof(struct sequence);
    uint8_t *data_to_read=ke_malloc(size_of_data_to_read,KE_MEM_ENV);
    
    generic_spi_flash_init();
    
    address = storage_info->address;
    for (int i = 0 ; i < 2; i++)
    {
        memset(data_to_read, (int)0, size_of_data_to_read);
        spi_flash_read_data(data_to_read, 
                            address, size_of_data_to_read, &actual_size);
        
       // Restore the sequence
       memcpy(&temp_seq[i], &data_to_read[storage_info->data_size], sizeof(struct sequence)); 
       address +=SPI_FLASH_SECTOR_SIZE;
    }
    
    // At this point we have found the two sequence numbers 
    bool is_valid[2] = {false, false};
    for (int i = 0; i < 2;i++)
    {
        if (temp_seq[i].sequence_number == ~ temp_seq[i].complementary_sequence_number)
        {
            is_valid[i] = true;
        }
    }
    
    int index = 0;
    if (is_valid[0] && is_valid[1]) // both sequence numbers are valid
    {
        if (temp_seq[1].sequence_number > temp_seq[0].sequence_number)
        {
            index = 1;
        }
        memcpy(&seq,&temp_seq[index],sizeof(struct sequence));
    }
    else if (!is_valid[0] && !is_valid[1]) // none is valid
    {
        seq.sequence_number = 0x01234567;
        seq.complementary_sequence_number = ~seq.sequence_number;
    }
    else // only one sequence number is valid
    {
        index = (is_valid[0]==true) ? 1:0;
        memcpy(&seq,&temp_seq[index],sizeof(struct sequence));
    }
    // Restore the parameters 
    if (restore_parameters)
    {
        memset(data_to_read, (int)0, size_of_data_to_read);
        spi_flash_read_data((uint8_t *)data_to_read, 
                            storage_info->address+index*SPI_FLASH_SECTOR_SIZE, size_of_data_to_read, &actual_size);
        memcpy(storage_info->ptr_to_data,data_to_read,storage_info->data_size);
    }
    ke_free(data_to_read);
    // Power down flash
    spi_flash_power_down();
}

#endif
/*
 * EXPOSED FUNCTION DEFINITIONS
 ****************************************************************************************
 */


void generic_load_flash(const struct nvm_information * const storage_info)
{
    #if NVM_DOUBLE_BUFFERING
    update_sequence_number_and_parameters(storage_info, true);
    #else
    uint32_t actual_size;
    generic_spi_flash_init();
    
    spi_flash_read_data((uint8_t *)storage_info->ptr_to_data, 
                        storage_info->address, storage_info->data_size, &actual_size);
    // Power down flash
    spi_flash_power_down();
    #endif
}


int8_t generic_erase_flash_sectors(bool scheduler_en, const struct nvm_information * const storage_info)
{
    uint32_t sector_nb;
    uint32_t offset;
    int8_t ret;
    int i;
    uint32_t timeout_cnt;

    // Calculate the starting sector offset
    offset = (storage_info->address / SPI_FLASH_SECTOR_SIZE) * SPI_FLASH_SECTOR_SIZE;

    // Calculate the numbers of sectors to erase
    sector_nb = (storage_info->data_size / SPI_FLASH_SECTOR_SIZE);
    if (storage_info->data_size % SPI_FLASH_SECTOR_SIZE)
        sector_nb++;

    for (i = 0; i < sector_nb; i++)
    {
        if (scheduler_en)
        {
            // Non-Blocking Erase of a Flash sector
            ret = spi_flash_block_erase_no_wait(offset, SPI_FLASH_OP_SE);
            if (ret != SPI_FLASH_ERR_OK)
                break;

            timeout_cnt = 0;

            while ((spi_flash_read_status_reg() & SPI_FLASH_SR_BUSY) != 0)
            {
                // Check if BLE is on and not in deep sleep and call rwip_schedule()
                if ((GetBits16(CLK_RADIO_REG, BLE_ENABLE) == 1) &&
                   (GetBits32(BLE_DEEPSLCNTL_REG, DEEP_SLEEP_STAT) == 0))
                {
                    // Assuming that the WDG is not active, timeout will be reached in case of a Flash erase error.
                    // NOTE: In case the WDG is active, the WDG timer will expire (much) earlier than the timeout
                    // is reached and therefore an NMI will be triggered.
                    if (++timeout_cnt > SPI_FLASH_WAIT)
                    {
                        return SPI_FLASH_ERR_TIMEOUT;
                    }
                    rwip_schedule();
                }
            }
        }
        else
        {
            // Blocking Erase of a Flash sector
            ret = spi_flash_block_erase(offset, SPI_FLASH_OP_SE);
            if (ret != SPI_FLASH_ERR_OK)
                break;
        }
        offset += SPI_FLASH_SECTOR_SIZE;
    }
    return ret;
}


void generic_store_flash(bool scheduler_en, struct nvm_information * const storage_info)
{
    uint32_t actual_size;
    int8_t ret;

#if NVM_DOUBLE_BUFFERING
    size_t size_of_data_to_write = storage_info->data_size+sizeof(struct sequence);
    uint8_t * data_to_write=ke_malloc(size_of_data_to_write,KE_MEM_ENV);
    
    // First update the sequence number
    update_sequence_number_and_parameters(storage_info, false);
    for (int i = 0 ; i < 2 ; i++)
    {
        generic_spi_flash_init();
        ret = generic_erase_flash_sectors(scheduler_en, storage_info); 
        if (ret == SPI_FLASH_ERR_OK)
        {
            // The sector is erased 
            // We need to add the sequence number and write the data to storage_info->address
            memset(data_to_write, (int)0x00, size_of_data_to_write);
            memcpy(data_to_write, storage_info->ptr_to_data, storage_info->data_size);
            
            seq.sequence_number++;
            seq.complementary_sequence_number = ~ seq.sequence_number;
            
            memcpy(data_to_write+storage_info->data_size,&seq ,sizeof(struct sequence));
            spi_flash_write_data((uint8_t *)data_to_write, 
                                 storage_info->address, size_of_data_to_write, &actual_size);
        }
        storage_info->address +=SPI_FLASH_SECTOR_SIZE; // Write next sector
        // Power down flash
        spi_flash_power_down();
    }
    ke_free(data_to_write);
#else
    generic_spi_flash_init();

    ret = generic_erase_flash_sectors(scheduler_en, storage_info);
    if (ret == SPI_FLASH_ERR_OK)
    {
        spi_flash_write_data((uint8_t *)storage_info->ptr_to_data, 
                              storage_info->address, storage_info->data_size, &actual_size);
    }

    // Power down flash
    spi_flash_power_down();
#endif

}
#endif // (CFG_SPI_FLASH_ENABLE)

/// @} NON_VOLATILE_STORAGE
