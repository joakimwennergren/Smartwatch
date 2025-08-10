/**
 ****************************************************************************************
 *
 * @file user_bonding_database.c
 *
 * @brief Bonding database handling source file
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

#if (BLE_APP_SEC)
#include "user_bonding_database.h"
#include "user_codeless_env.h"
#include "user_utility_functions.h"
#include "app_bond_db.h"
#include "user_at_commands.h"
#include "rwip.h"

/****************************************************************************************
 * MACROS
 ****************************************************************************************/


/****************************************************************************************
 * FUNCTIONS
 ****************************************************************************************/

#if defined (USE_AT_BND)
    #if (BLE_APP_SEC)
bool user_is_iebnde_command_argument_valid(const char* argument, uint8_t* index)
{
    uint8_t conv_result = 0;
    bool is_arg_valid = false;

    uint32_t number=0;
    int conversion_error=atoui32_with_error_checking((char*)argument, 0, &number);
    if (conversion_error==0)
    {
        if (number >= 1 && number <= APP_BOND_DB_MAX_BONDED_PEERS)
        {
            is_arg_valid = true;
            conv_result=(uint8_t)number;
        }
    }
    if ((is_arg_valid) && (index != NULL))
    {
        *index= (uint8_t)(--conv_result);
    }
    return is_arg_valid;
}


bool user_verify_persistence_args(const char* arg1, const char* arg2,
                                  uint8_t* arg1_num_ptr, uint8_t* arg2_num_ptr)
{
    //arg_1 should be an integer between 1 and APP_BOND_DB_MAX_BONDED_PEERS or 0xFF.
    //arg_2 should be either 1 or 0 but it may be provided as 0x01 or 0x00

    bool is_arg1_valid = false;
    bool is_arg2_valid = false;

    uint8_t arg1_conv = 0;
    uint8_t arg2_conv = 0;

    uint32_t number=0;
    int conversion_error=0;

    conversion_error=atoui32_with_error_checking((char*)arg1, 0, &number);
    if (conversion_error==0)
    {
        if ((number==0xFF) || (number >= 1 && number <= APP_BOND_DB_MAX_BONDED_PEERS))
        {
            is_arg1_valid = true;
            arg1_conv=(uint8_t)number;
        }
    }
    conversion_error=atoui32_with_error_checking((char*)arg2, 0, &number);
    if (conversion_error==0)
    {
        if (number==0 || number==1)
        {
            is_arg2_valid = true;
            arg2_conv=(uint8_t)number;
        }
    }
    if (is_arg1_valid && is_arg2_valid)
    {
        if (arg1_num_ptr != NULL)
        {
            *arg1_num_ptr = arg1_conv;
        }
        if (arg2_num_ptr != NULL)
        {
            *arg2_num_ptr = arg2_conv;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool is_at_iebnde_string_arg_valid(const char * const argument, uint8_t * byte_array)
{
    bool is_argument_valid = false;
    const char delimiter = ';';
    const uint8_t valid_string_length = 150;
    const uint8_t delimiter_positions[] = {54, 105, 138, 141};
    const uint8_t number_of_delimiter_positions = sizeof(delimiter_positions)/sizeof(delimiter_positions[0]);
    do
    {
        // String argument should be exactly 150 characters
        if (argument == NULL || strlen(argument) != valid_string_length)
        {
            break;
        }
        // Delimiters must be located in specific positions
        bool are_delimiters_in_right_positions = true;
        for (int jj=0; jj < number_of_delimiter_positions ; jj++)
        {
            if (argument[delimiter_positions[jj]] != delimiter )
            {
                are_delimiters_in_right_positions = false;
                break;
            }
        }
        if (!are_delimiters_in_right_positions)
        {
            break;
        }
        //Ensure that the persistence is either 0 or 1
        if ((argument[139] != '0') || (argument[140] !='0' && argument[140] != '1'))
        {
            break;
        }
        // Try to convert the input hexadecimal string to an array of bytes
        // The delimiters should be ignored
        char string[3] = {0};
        bool is_conversion_ok = true;
        for (int i=0, j=0; i < valid_string_length; i+=2,j++)
        {
            // if a delimiter is found in this position skip it
            for (int k=0; k < number_of_delimiter_positions ; k++)
            {
                if (i == delimiter_positions[k])
                {
                    i++;
                    break;
                }
            }
            string[0] = argument[i];
            string[1] = argument[i+1];
            uint32_t conv_result=0;
            if (atoui32_with_error_checking(string, 16, &conv_result) != 0)
            {
                // an error occured while converting - the string is invalid
                is_conversion_ok = false;
                break;
            }
            if (byte_array != NULL)
            {
                byte_array[j] = (uint8_t)conv_result;
            }
        }
        if (!is_conversion_ok)
        {
            break;
        }
        else
        {
            is_argument_valid = true;
            break;
        }
    }
    while (0);
    return is_argument_valid;
}

    #endif  // (BLE_APP_SEC)
#endif // (USE_AT_BND)

#endif


/// @} APP
