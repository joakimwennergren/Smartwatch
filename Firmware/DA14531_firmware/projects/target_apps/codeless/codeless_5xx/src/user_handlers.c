/**
 ****************************************************************************************
 *
 * @file user_handlers.c
 *
 * @brief Handlers source file
 *
 * Copyright (C) 2019-2024 Renesas Electronics Corporation and/or its affiliates.
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

#include "user_handlers.h"
#include "user_codeless_env.h"
#include "user_utility_functions.h"
#include "arch_console.h"

/****************************************************************************************
 * Structures
 ****************************************************************************************/
/**
 * \brief  handlers configuration struct
 */

#ifdef USE_AT_HNDL
int user_enable_handler(EVENT_HANDLERS_ENUM handler, char * commands, int size)
{
    int return_value=0;
    do
    {
        if (commands == NULL)
        {
            return_value = -1;
            break;
        }

        if (size > sizeof(app_get_hdb_entry(0)->handler_commands)-1)
        {
            return_value = -1;
            break;
        }
        for (size_t i=0;i < NUMBER_OF_HANDLERS; i++)
        {
            if (handler == app_get_hdb_entry(i)->handler)
            {
                // At this point we need to write the new command but first
                // we must ensure that all old information is erased from the ram
                memset(app_get_hdb_entry(i)->handler_commands, (int)0, sizeof(app_get_hdb_entry(i)->handler_commands));
                handlers_db_store_ext(true);

                // Now the new information can be written
                app_get_hdb_entry(i)->is_handler_enabled = true;
                memcpy(app_get_hdb_entry(i)->handler_commands, commands, size);
                // update the flash if available
                handlers_db_store_ext(true);
                return_value=0;
                break;
            }
        }
    }
    while (0);
    return return_value;
}


void user_disable_handler(EVENT_HANDLERS_ENUM handler)
{
    size_t jj=0;
    for (jj=0;jj < NUMBER_OF_HANDLERS; jj++)
    {
        if (handler == app_get_hdb_entry(jj)->handler)
        {
            app_get_hdb_entry(jj)->is_handler_enabled = false;
            memset(app_get_hdb_entry(jj)->handler_commands, (int)0, sizeof(app_get_hdb_entry(jj)->handler_commands));
            // Write the new status to flash if available
            handlers_db_store_ext(true);
        }
    }
}

bool user_is_handler_enabled(EVENT_HANDLERS_ENUM handler)
{
    size_t kk=0;
    for (kk=0; kk < NUMBER_OF_HANDLERS; kk++)
    {
        if (handler == app_get_hdb_entry(kk)->handler)
        {
            break;
        }
    }
    return app_get_hdb_entry(kk)->is_handler_enabled;
}

const char * user_get_handler_command_string(EVENT_HANDLERS_ENUM handler)
{
    size_t kk=0;
    for (kk=0; kk < NUMBER_OF_HANDLERS; kk++)
    {
        if (handler == app_get_hdb_entry(kk)->handler)
        {
            break;
        }
    }
    if (app_get_hdb_entry(kk)->is_handler_enabled)
    {
        return &app_get_hdb_entry(kk)->handler_commands[0];
    }
    else
    {
        return NULL;
    }
}

bool user_is_handler_argument_valid(const char * const argument, EVENT_HANDLERS_ENUM * handler)
{
    bool is_valid=false;
    EVENT_HANDLERS_ENUM temp_handler;

    uint32_t number=0;
    int conversion_error=0;
    uint8_t conv_result = 0;

    conversion_error=atoui32_with_error_checking((char*)argument, 0, &number);
    if (conversion_error==0)
    {
        if (number >= 1 && number <= NUMBER_OF_HANDLERS)
        {
            is_valid = true;
            conv_result=(uint8_t)number;
            temp_handler = (EVENT_HANDLERS_ENUM)conv_result;
        }
    }
    if (is_valid && (handler !=NULL))
    {
        *handler=temp_handler;
    }
    return is_valid;
}
#endif // USE_AT_HNDL

/// @} APP
