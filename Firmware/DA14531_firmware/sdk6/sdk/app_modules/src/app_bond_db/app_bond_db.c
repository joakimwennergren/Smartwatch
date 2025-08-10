/**
 *****************************************************************************************
 *
 * @file app_bond_db.c
 *
 * @brief Bond database code file.
 *
 * Copyright (C) 2012-2023 Renesas Electronics Corporation and/or its affiliates.
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
 *****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup APP_BOND_DB
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"

#if (BLE_APP_SEC)

#include "rwip.h"
#include "app_bond_db.h"
#include "arch_console.h"
#include "app_non_volatile_storage.h"


/*
 * DEFINES
 ****************************************************************************************
 */
#define BOND_DB_VALID_ENTRY             (0xAA)
#define BOND_DB_EMPTY_SLOT              (0)
#define BOND_DB_SLOT_NOT_FOUND          (0xFF)

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

struct bond_db bdb __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */


/*
 * STATIC FUNCTION DEFINITIONS
 ****************************************************************************************
 */

#if defined (USER_CFG_APP_BOND_DB_USE_SPI_FLASH)

#if !NVM_DOUBLE_BUFFERING
static struct nvm_information storage_info=
{
    .ptr_to_data = &bdb,
    .address = APP_BOND_DB_DATA_OFFSET,
    .data_size = sizeof(struct bond_db)
};
#endif 

static void bond_db_load_flash(void)
{
    #if NVM_DOUBLE_BUFFERING
    struct nvm_information storage_info=
    {
        .ptr_to_data = &bdb,
        .address = APP_BOND_DB_DATA_OFFSET,
        .data_size = sizeof(struct bond_db)
    };
    #endif 
    generic_load_flash(&storage_info);
}

#if 0
/**
 ****************************************************************************************
 * @brief Erase Flash sectors where bond database is stored
 * @param[in] scheduler_en  True: Enable rwip_scheduler while Flash is being erased
 *                          False: Do not enable rwip_scheduler. Blocking mode
 * @return ret              Error code or success (ERR_OK)
 ****************************************************************************************
 */
static int8_t bond_db_erase_flash_sectors(bool scheduler_en)
{
    struct nvm_information storage_info=
    {
        .ptr_to_data = &bdb,
        .address = APP_BOND_DB_DATA_OFFSET,
        .data_size = sizeof(struct bond_db)
    };
    return generic_erase_flash_sectors(scheduler_en, &storage_info);
}
#endif

/**
 ****************************************************************************************
 * @brief Store Bond Database to Flash memory
 * @param[in] scheduler_en  True: Enable rwip_scheduler while Flash is being erased
 *                          False: Do not enable rwip_scheduler. Blocking mode
 ****************************************************************************************
 */
static void bond_db_store_flash(bool scheduler_en)
{
    #if NVM_DOUBLE_BUFFERING
    struct nvm_information storage_info=
    {
        .ptr_to_data = &bdb,
        .address = APP_BOND_DB_DATA_OFFSET,
        .data_size = sizeof(struct bond_db)
    };
    #endif
    generic_store_flash(scheduler_en, &storage_info);
}

#elif defined (USER_CFG_APP_BOND_DB_USE_I2C_EEPROM)

static void bond_db_load_eeprom(void)
{
    uint32_t bytes_read;

    // Initialize I2C for Serial EEPROM
    i2c_eeprom_initialize();

    i2c_eeprom_read_data((uint8_t *)&bdb, APP_BOND_DB_DATA_OFFSET, sizeof(struct bond_db), &bytes_read);
    ASSERT_ERROR(bytes_read == sizeof(struct bond_db));

    i2c_eeprom_release();
}

static void bond_db_store_eeprom(void)
{
    uint32_t bytes_written;

    // Initialize I2C for Serial EEPROM
    i2c_eeprom_initialize();

    i2c_eeprom_write_data((uint8_t *)&bdb, APP_BOND_DB_DATA_OFFSET, sizeof(struct bond_db), &bytes_written);
    ASSERT_ERROR(bytes_written == sizeof(struct bond_db));

    i2c_eeprom_release();
}
#endif

/**
 ****************************************************************************************
 * @brief Load Bond Database from external memory
 ****************************************************************************************
 */
__STATIC_INLINE void bond_db_load_ext(void)
{
    #if defined (USER_CFG_APP_BOND_DB_USE_SPI_FLASH)
    bond_db_load_flash();
    #elif defined (USER_CFG_APP_BOND_DB_USE_I2C_EEPROM)
    bond_db_load_eeprom();
    #endif
}

/**
 ****************************************************************************************
 * @brief Store Bond Database to external memory
 * @param[in] scheduler_en  Only used if external memory is Flash
                            True: Enable rwip_scheduler while Flash is being erased
 *                          False: Do not enable rwip_scheduler. Blocking mode
 ****************************************************************************************
 */
__STATIC_INLINE void bond_db_store_ext(bool scheduler_en)
{
    #if defined (USER_CFG_APP_BOND_DB_USE_SPI_FLASH)
    bond_db_store_flash(scheduler_en);
    #elif defined (USER_CFG_APP_BOND_DB_USE_I2C_EEPROM)
    bond_db_store_eeprom();
    #endif
}

/**
 ****************************************************************************************
 * @brief Store Bond data entry to external memory
 * @param[in] *data  Data to be stored
 * @param[in] *idx   Entry in the database
 ****************************************************************************************
 */
static void bond_db_store_at_idx(struct app_sec_bond_data_env_tag *data, int idx)
{
    bdb.valid_slot[idx] = BOND_DB_VALID_ENTRY;
    // Update the cache
    memcpy(&bdb.data[idx], data, sizeof(struct app_sec_bond_data_env_tag));
    // Store new bond data to external memory
    // In case of Flash (erase then write) enable the scheduler
    bond_db_store_ext(true);
}

/**
 ****************************************************************************************
 * @brief Clear bond data.
 ****************************************************************************************
 */
static void bond_db_clear(bool scheduler_en)
{
    memset((void *)&bdb, 0, sizeof(struct bond_db) ); // zero bond data
    bdb.start_hdr = BOND_DB_HEADER_START;
    bdb.end_hdr = BOND_DB_HEADER_END;
    // Store zero bond data to external memory
    // In case of Flash (erase then write) do not enable the scheduler
    bond_db_store_ext(scheduler_en);
}

/*
 * EXPOSED FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void default_app_bdb_init(void)
{
    // Load bond data from the external memory resource
    bond_db_load_ext();

    // Simple check for garbage in memory (this also catches the 0xFF of cleared memory)
    if ((bdb.start_hdr != BOND_DB_HEADER_START) || (bdb.end_hdr != BOND_DB_HEADER_END))
    {
        bond_db_clear(false);
    }
}

uint8_t default_app_bdb_get_size(void)
{
    return APP_BOND_DB_MAX_BONDED_PEERS;
}

void find_slot_to_write(struct app_sec_bond_data_env_tag *data, uint8_t *slot_to_write_ptr, bool *first_empty_slot_found_ptr)
{
    bool first_empty_slot_found = false;
    uint8_t slot_to_write = BOND_DB_SLOT_NOT_FOUND;
    
    for(uint8_t i = 0; i < APP_BOND_DB_MAX_BONDED_PEERS; i++)
    {
        // If current slot is not valid (is empty)
        if (bdb.valid_slot[i] != BOND_DB_VALID_ENTRY)
        {
            // Check if an empty slot has already been found
            if (first_empty_slot_found == false)
            {
                // First empty slot has been found
                first_empty_slot_found = true;
                // Store empty slot to write
                slot_to_write = i;
            }
        }
        // If current slot is not empty
        else
        {
            // Check if IRK is present in current slot and in new pairing data
            if ((bdb.data[i].valid_keys & *(&data->valid_keys)) & RIRK_PRESENT)
            {
                // Check if stored IRK matches with new IRK
                if (memcmp(&data->rirk.irk, &bdb.data[i].rirk.irk, sizeof(struct gap_sec_key)) == 0)
                {
                    // IRK matches, store this slot to be replaced and exit
                    slot_to_write = i;
                    break;
                }
            }
            // If IRK is not present
            else
            {
                // Check if stored BD address matches with new BD address
                if (memcmp(&data->peer_bdaddr, &bdb.data[i].peer_bdaddr, sizeof(struct gap_bdaddr)) == 0)
                {
                    // BD address matches, store this slot to be replaced and exit
                    slot_to_write = i;
                    break;
                }
            }
        }
    }
    *first_empty_slot_found_ptr = first_empty_slot_found;
    *slot_to_write_ptr = slot_to_write;
}


void default_app_bdb_add_entry(struct app_sec_bond_data_env_tag *data)
{
    bool first_empty_slot_found = false;
    uint8_t i = 0;
    uint32_t min_timestamp = UINT32_MAX;
    uint8_t slot_to_write = BOND_DB_SLOT_NOT_FOUND;

    find_slot_to_write(data, &slot_to_write, &first_empty_slot_found);
   
    if (slot_to_write == BOND_DB_SLOT_NOT_FOUND) // no slot found
    {
        /* 
        A slot has not been found. Therefore no empty slots exist and no matching with 
        an existing slot took place.Normally at this point the least recently written 
        slot would be replaced.However the persistence must be taken into consideration.
        A persistent entry cannot be replaced. Therefore the least recently written slot 
        that is not persistent must be found. If all entries are persistent then no replacement 
        will take place.
        */
        
        for(i = 0; i < APP_BOND_DB_MAX_BONDED_PEERS; i++)
        {
            if (bdb.persistence[i] == 0) // not persistent
            {
            // Find the slot with the oldest (minimum) timestamp that is not persistent
                if (bdb.timestamp[i] < min_timestamp)
                {
                    min_timestamp = bdb.timestamp[i];
                    slot_to_write = i;
                }
            }
        }
        if (min_timestamp == UINT32_MAX)
        {
            // no action can be taken.No slot will be replaced
            return;
        }
    }
    else //A slot has been found. It is either empty or is matched.
    {
        if (first_empty_slot_found) // empty slot found
        {
            // The persistence will be zero by default on a new entry
            bdb.persistence[slot_to_write] = 0;
        }
        // if matched no other action is necessary. The old persistence 
        // value will be kept.
    }
    bdb.timestamp[slot_to_write] = bdb.timestamp_counter++;
    // Store bond db entry
    data->bdb_slot = slot_to_write;
    bond_db_store_at_idx(data, slot_to_write);
}

void default_app_bdb_change_persistence_status(uint8_t index, uint8_t new_persistence)
{
    // Check if the slot argument points to an actual slot
    // Also ensure that the slot specified is not empty
    if ((index < APP_BOND_DB_MAX_BONDED_PEERS) && (bdb.valid_slot[index] == BOND_DB_VALID_ENTRY)) 
    {
        //Avoid updating the flash if the persistence is the same
        if (bdb.persistence[index] != new_persistence) 
        {
            
            bdb.persistence[index]=new_persistence;
            // Store the updated cache to the external non volatile memory
            bond_db_store_ext(true);
        }
    }
}

void default_app_bdb_change_persistence_status_for_all_entries(uint8_t new_persistence)
{
    // Check if the slot argument points to an actual slot
    // Also ensure that the slot specified is not empty
    for (int index=0; index < APP_BOND_DB_MAX_BONDED_PEERS ; index++)
    {
        if (bdb.valid_slot[index] == BOND_DB_VALID_ENTRY) 
        {
            bdb.persistence[index] = new_persistence;   
        }
    }
    // When done store the updated cache to the external non volatile memory
    bond_db_store_ext(true);
}

void default_app_bdb_get_persistence_status(char* response)
{
    if (response != NULL)
    {
        for (int index=0; index < APP_BOND_DB_MAX_BONDED_PEERS; index++)
        {
            // Ensure that the slot specified is not empty
            if (bdb.valid_slot[index] == BOND_DB_VALID_ENTRY) 
            {
                size_t n=strlen(response);
                arch_sprintf(response+n,"%d,%d\r\n", (index+1), bdb.persistence[index]);
            }
            else //this is not a valid entry 
            {
                size_t n=strlen(response);
                arch_sprintf(response+n,"%d,%s\r\n", (index+1), "<empty>");
            }
        }
    }
}

static uint8_t find_slot(enum bdb_search_by_type search_type, void *search_param, uint8_t search_param_length)
{
    uint8_t slot_found = BOND_DB_SLOT_NOT_FOUND;
    for(uint8_t i = 0; i < APP_BOND_DB_MAX_BONDED_PEERS; i++)
    {
        // Check if EDIVs match
        if ((search_type == SEARCH_BY_EDIV_TYPE) &&
                ((memcmp(&bdb.data[i].ltk.ediv, search_param, search_param_length) == 0)))
        {
            slot_found = i;
            break;
        }
        // Check if BD addresses match
        else if ((search_type == SEARCH_BY_BDA_TYPE) &&
                     ((memcmp(&bdb.data[i].peer_bdaddr.addr, search_param, search_param_length) == 0)))
        {
            slot_found = i;
            break;
        }
        // Check if IRKs match
        else if ((search_type == SEARCH_BY_IRK_TYPE) &&
                     (memcmp(&bdb.data[i].rirk, search_param, search_param_length) == 0))
        {
            slot_found = i;
            break;
        }
        else if (search_type == SEARCH_BY_ID_TYPE)
        {
            // Check if bond_db BD address and given ID address match
            if ((memcmp(&bdb.data[i].rirk.addr.addr, search_param, search_param_length) == 0))
            {
                slot_found = i;
                break;
            }
        }
    }
    return slot_found;
}


void default_app_bdb_remove_entry(enum bdb_search_by_type search_type, enum bdb_remove_type remove_type,
                          void *search_param, uint8_t search_param_length)
{
    uint8_t i = 0;
    uint8_t slot_found = BOND_DB_SLOT_NOT_FOUND;

    if (remove_type == REMOVE_ALL)
    {
        bond_db_clear(true);
        return;
    }

    if (search_type == SEARCH_BY_SLOT_TYPE)
    {
        slot_found = *((uint8_t *)search_param);
    }
    else
    {
        slot_found = find_slot(search_type, search_param, search_param_length);
    }

    // Check if a valid slot has been found
    if (slot_found < APP_BOND_DB_MAX_BONDED_PEERS)
    {
        if (remove_type == REMOVE_THIS_ENTRY)
        {
            // Remove entry from cache
            memset((void *)&bdb.data[slot_found], 0, sizeof(struct app_sec_bond_data_env_tag));
            bdb.timestamp[slot_found] = 0;
            bdb.persistence[slot_found] = 0;
            bdb.valid_slot[slot_found] = BOND_DB_EMPTY_SLOT;
        }
        else
        {
            // If remove_all_but_this is true, remove all other entries from cache
            for(i = 0; i < APP_BOND_DB_MAX_BONDED_PEERS; i++)
            {
                if (i != slot_found)
                {
                    memset((void *)&bdb.data[i], 0, sizeof(struct app_sec_bond_data_env_tag));
                    bdb.timestamp[i] = 0;
                    bdb.persistence[i] = 0;
                    bdb.valid_slot[i] = BOND_DB_EMPTY_SLOT;
                }
            }
        }
        // Store the updated cache to the external non volatile memory
        bond_db_store_ext(true);
    }
}
// TODO: embed this function in the default_app_bdb_search entry function
const struct app_sec_bond_data_env_tag* user_app_bdb_retrieve(uint8_t index)
{
    return &bdb.data[index];
}

const struct app_sec_bond_data_env_tag* default_app_bdb_search_entry(enum bdb_search_by_type search_type,
                                                             void *search_param,
                                                             uint8_t search_param_length)
{
    struct app_sec_bond_data_env_tag *found_data = NULL;
    uint8_t slot = find_slot(search_type,search_param, search_param_length);
    if (slot != BOND_DB_SLOT_NOT_FOUND)
    {
        found_data = &bdb.data[slot];
    }

    return found_data;
}

uint8_t default_app_bdb_get_number_of_stored_irks(void)
{
    return default_app_bdb_get_stored_irks(NULL);
}

uint8_t default_app_bdb_get_stored_irks(struct gap_sec_key *valid_irk_irray)
{
    uint8_t nb_key = 0;

    // Search DB to find the entries which contain an IRK
    for(uint8_t i = 0; i < APP_BOND_DB_MAX_BONDED_PEERS; i++)
    {
        // Check if there is an IRK present in the current slot
        if ((bdb.data[i].valid_keys & RIRK_PRESENT) == RIRK_PRESENT)
        {
            // Copy IRK to the IRK array
            if (valid_irk_irray !=NULL)
            {
                memcpy(&valid_irk_irray[nb_key], &bdb.data[i].rirk.irk, sizeof(struct gap_sec_key));
            }
            nb_key++;
        }
    }

    return nb_key;
}

bool default_app_bdb_get_device_info_from_slot(uint8_t slot, struct gap_ral_dev_info *dev_info)
{
    // Check if the entry is valid and if there is an IRK
    if ((bdb.valid_slot[slot] == BOND_DB_VALID_ENTRY) && ((bdb.data[slot].valid_keys & RIRK_PRESENT) == RIRK_PRESENT))
    {
        memcpy(dev_info->addr, &bdb.data[slot].rirk.addr.addr.addr, BD_ADDR_LEN*sizeof(uint8_t));
        dev_info->addr_type = bdb.data[slot].rirk.addr.addr_type;
        memcpy(dev_info->peer_irk, &bdb.data[slot].rirk.irk, sizeof(struct gap_sec_key));
        return true;
    }
    return false;
}


void update_db_slot_timestamp_on_connection(uint8_t slot_to_update)
{
    do
    {
        //ensure that the slot is valid and within array bounds
        if (slot_to_update >= APP_BOND_DB_MAX_BONDED_PEERS)
        {
            break;
        }
        if (bdb.valid_slot[slot_to_update] != BOND_DB_VALID_ENTRY)
        {
            break;
        }
        //We just need to update the timestamp to make this entry the most recent one
        bdb.timestamp[slot_to_update] = bdb.timestamp_counter++;
    }
    while (0);
}

uint32_t app_retrieve_timestamp(uint8_t slot_to_read)
{
    return bdb.timestamp[slot_to_read];
}

uint32_t app_retrieve_persistence(uint8_t slot_to_read)
{
    return bdb.persistence[slot_to_read];
}

void app_bdb_add_entry_with_persistence_and_timestamp(struct app_sec_bond_data_env_tag *data, uint32_t persistence, 
                                                      uint32_t new_timestamp)
{
    /*
    This function will only be called when the AT+IEBNDE=X,<data> command is executed from the commandline.
    Therefore some comments below clarify the behaviour of this function in such a case:
    
    1.This command is very powerful. Apart from a minimum number of checks performed before this command is called 
      almost arbitrary information can be imported within the bdb database. A powerful command which may cause bonding 
      database problems if not used correctly.
    2.In particular a check is performed if the string that will be imported has the correct length, the delimiters are in the 
      right places, the persistence is correct (either 0 or 1) and that the characters of the string are hex numbers.
    3.If the new entry has the same IRK or the same BD address as an existing entry then the existing entry 
      will be replaced by the new entry.This will happen regardless of the timestamp.That is the new timestamp may 
      be smaller than the already existing timestamp.
    4.If the new entry has an IRK not in the bdb it will be inserted in the bdb.If an empty place exists the new 
      entry will be inserted there. If an empty place does not exist the new entry will replace the oldest entry in the bdb
      This will happen even if the new entry has an older timestamp than the oldest one in the database.The logic behind this
      is that we allow the user to change the entries at will.
    5.The persistence will not be taken into consideration when this command is used.
    
    Problems:
    1.If the user enters a very high timestamp number close to UINT32_MAX the number may wrap up
      In this case we will have bonding/connection inversion meaning that there always be one or more entries that
      will have the maximum or close to the maximum timestamp. All new entries will be considered older.
    2.No error checking in timestamps is performed. It would be possible to import five entries with exactly the same 
      timestamp.It is up to the user to ensure that this situation won't happen.
    */
    
    bool first_empty_slot_found = false;
    uint8_t i = 0;
    uint32_t min_timestamp;
    uint8_t slot_to_write = BOND_DB_SLOT_NOT_FOUND;

    find_slot_to_write(data, &slot_to_write, &first_empty_slot_found);
    
    // If there is no available slot, find the least recently written slot to replace
    if (slot_to_write == BOND_DB_SLOT_NOT_FOUND)
    {
        min_timestamp = bdb.timestamp[0];
        slot_to_write = 0;
        for(i = 1; i < APP_BOND_DB_MAX_BONDED_PEERS; i++)
        {
            // Find the slot with the oldest (minimum) timestamp
            if (bdb.timestamp[i] < min_timestamp)
            {
                min_timestamp = bdb.timestamp[i];
                slot_to_write = i;
            }
        }
    }
    
    /*
    At this point we know what slot we need to write.
    We must ensure that the timestamp_counter will always have a value that is greater than 
    all the timestamps (already in the bdb and the new one)by at least one. Therefore if a
    bluetooth newcomer arrives or a connection is attempted a correct timestamp will be assigned.
    */
    
    //find the maximum timestamp in the bdb
    uint32_t max_timestamp=0;
    for(i = 0; i < APP_BOND_DB_MAX_BONDED_PEERS; i++)
    {
        if (BOND_DB_VALID_ENTRY == bdb.valid_slot[i])
        {
            if (bdb.timestamp[i]>max_timestamp)
            {
                max_timestamp=bdb.timestamp[i];
            }
        }  
    }

    // Ensure that max_timestamp is also larger than/equal to the new timestamp 
    if (new_timestamp>max_timestamp)
    {
        max_timestamp=new_timestamp;
    }
    // Assign the timestamp and timestamp_counter
    bdb.timestamp[slot_to_write] = new_timestamp;
    bdb.timestamp_counter=max_timestamp+1;
    
    // Assign the persistence
    bdb.persistence[slot_to_write]=persistence;
    
    // Store bond db entry
    data->bdb_slot = slot_to_write;
    bond_db_store_at_idx(data, slot_to_write);
}

#endif // (BLE_APP_SEC)

/// @} APP_BOND_DB
