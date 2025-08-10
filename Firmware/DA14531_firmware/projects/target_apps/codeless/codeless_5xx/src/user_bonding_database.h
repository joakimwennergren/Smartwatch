/**
 ****************************************************************************************
 *
 * @file user_bonding_database.h
 *
 * @brief user_bonding_database header file.
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

#ifndef _USER_BONDING_DATABASE_H_
#define _USER_BONDING_DATABASE_H_

#include "stdbool.h"
#include "stdint.h"

/**
 ****************************************************************************************
 * @brief      Checks if the console argument for the bonding database commands is valid
 *
 * @param[in]  argument, the argument specified in the console
 * @param[out] index, the database index to return
 *
 * @return     bool, true if input is valid false otherwise
 *****************************************************************************************
 */
bool user_is_iebnde_command_argument_valid(const char* argument, uint8_t* index);

/**
 ****************************************************************************************
 * @brief      Checks if the console argument for the bonding database commands is valid
 *
 * @param[in]  arg1, first console argument
 * @param[in]  arg2, second console argument
 * @param[out] arg1_num_ptr, the first argument as number
 * @param[out] arg2_num_ptr, the second argument as number
 *
 * @return     bool, true if inputs are valid false otherwise
 *****************************************************************************************
 */

bool user_verify_persistence_args(const char* arg1, const char* arg2,
                                  uint8_t* arg1_num_ptr, uint8_t* arg2_num_ptr);

/**
 ****************************************************************************************
 * @brief      Checks if the argument for the at+iebnde command is valid
 *
 * @param[in]  argument, a string containing information to be imported
 * @param[out] byte_array, the string converted to byte array with the
                           delimiters stripped off
 *
 * @return     bool, true if input is valid false otherwise
 *****************************************************************************************
 */

bool is_at_iebnde_string_arg_valid(const char * const argument, uint8_t * byte_array);


#endif //_USER_BONDING_DATABASE_H_
/// @} APP
