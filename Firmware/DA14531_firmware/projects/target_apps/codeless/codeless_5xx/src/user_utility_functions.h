/**
 ****************************************************************************************
 *
 * @file user_utility_functions.h
 *
 * @brief Utility functions used in CodeLess project.
 *
 * Copyright (C) 2018-2024 Renesas Electronics Corporation and/or its affiliates.
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

#ifndef _USER_UTILITY_FUNCTIONS_H_
#define _USER_UTILITY_FUNCTIONS_H_
/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup APP_CODELESS
 *
 * @brief Codeless AT commands implementation.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "co_bt.h"
#include "user_codeless_strings.h"
#include "user_at_commands.h"
#include "user_codeless_env.h"


struct argument_info
{
    char * argument;
    uint8_t min_range_inclusive;
    uint8_t max_range_inclusive;
    uint8_t additional_arg_count;
};


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Generate  random BD Address.
 *
 * Reads device specific data from OTP in order to generate a unique random BD Address
 *****************************************************************************************
 */
struct bd_addr generate_random_bd_addr(void);

/**
 ****************************************************************************************
 * @brief Get bluetooth address from OTP or NVDS
 *
 * Reads the bluetooth address from OTP or returns the default address found in CFG_NVDS_TAG_ADDRESS
 *****************************************************************************************
 */
struct bd_addr get_bd_addr_from_otp_or_nvds(void);

/**
 ****************************************************************************************
 * @brief Converts hexadecimal string to integer - 32bit integer.
 *
 * @param[in]  str Pointer to hex string to convert to integer.
 *****************************************************************************************
 */
uint32_t ahtoi(char *str);

/**
 **********************************************************************************************
 * @brief Performs a thorough error check of the numeric arguments specified in the Codeless
 *        v2 command line.In particular the function performs the following checks:
 *        1. That the argument specified is not null or empty and has the right length
 *        2. That the argument specified is a valid decimal or hexadecimal number
 *        3. That the argument specified is within a certain range or equal to a predefined
 *           list of numbers
 *
 * @param[in]  info Pointer to a structure containing the information for performing
 *                  the error check
 * @param[out] result Pointer to the converted value if is valid
 * @param[in]  (...) A list of uint32_t numbers. If the argument is equal to one of the
 *                   numbers in this list it will be considered valid even if not within the limits.
 * @return     0 for success, a negative number for error
 **********************************************************************************************
 */
int validate_argument(const struct argument_info* info, uint32_t* result, ...);

/**
 ****************************************************************************************
 * @brief String to bluetooth device address.
 *
 * Converts from a string to a Bluetooth Device Address
 *
 * @param[in]  str Pointer to hex string to convert to bluetooth address.
 *****************************************************************************************
 */
struct bd_addr strtobdaddr(char *str);

/**
 ****************************************************************************************
 * @brief Converts hexadecimal string to uint32_t with error check
 *
 * @param[in]  str Pointer to the string to convert to integer.
 * @param[in]  base The base according to which the number will be interpeted
 * @param[out] result Pointer to the converted value
 *
 * @return     0 for success, a negative number for error
 *****************************************************************************************
 */
int atoui32_with_error_checking(char * str, uint8_t base, uint32_t * result);


/**
 ****************************************************************************************
 * @brief Validates a provided advertisement string
 *
 * Validate advertisemnt data are in the correct format. SSting passed as adv data
 * should be in the format XX:YY:ZZ where XX is the length, YY is the type, ZZ are
 * Data i.e 04:09:44:4F:47  length is the length of data + type.
 *
 * @param[in]  str Pointer to adv data in hex string.
 * @param[out] result Pointer to array containing adv data in integer format.
 * @param[in]  length Advertise data length.
 *****************************************************************************************
 */
bool validate_adv_data(char* str, uint8_t* result, uint8_t* length);

/**
 ****************************************************************************************
 * @brief Allocates memory for string
 *
 * Returns true if memory has been allocated succesfully from requested heap type
 * otherwise false. Currently mem check is working only for 585 codeless version.
 * In this case user_malloc will always return true and if an overflow occurs
 * a platform reset will be triggered.
 *
 * @param[in]  str      Pointer to the reply string to allocate memory to.
 * @param[in]  str_size Size of memory to be allocated to str.
 * @param[in]  type     Type of memory heap to try to allocate memory from.
 *****************************************************************************************
 */
bool user_malloc(char** str, size_t str_size, uint8_t type);

/**
 ****************************************************************************************
 * @brief Initialize UART with SPS settings (binary mode)
 *
 * @return void
 ****************************************************************************************
 */
void user_set_uart_to_dsps_settings(void);

/**
 ****************************************************************************************
 * @brief Initialize UART with Codeless settings (commnand mode)
 *
 * @return void
 ****************************************************************************************
 */
void user_set_uart_to_codeless_settings(void);

/**
 ****************************************************************************************
 * @brief Activates DLE and sets TX/RX packet length
 *
 * @param[in]  dle_env true or false to enable/disable DLE
 *
 * @param[in]  tx_pkt_len tx packet length in octets 27 - 251
 *
 * @param[in]  rx_pkt_len rx packet length in octets 27 - 251
 *
 * @return void
 ****************************************************************************************
 */
void user_activate_dle(bool dle_en, uint16_t tx_pkt_len, uint16_t rx_pkt_len);

/**
 ****************************************************************************************
 * @brief Starts parameter update
 *
 * @param[in]  conidx connection index
 *
 * @return void
 ****************************************************************************************
 */
void user_param_update_start(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Assignm a function to specific pin
 *
 * @param[in] port_pin the pin that the function should be assigned
 *
 * @param[in] func the function
 *
 * @return void
 ****************************************************************************************
 */
void user_assign_pin(uint8_t port_pin, io_func_t func);

/**
 ****************************************************************************************
 * @brief Triggers host wakeup guarding the printf process
 *
 * @return void
 ****************************************************************************************
 */
void user_host_wakeup_process(void);

/**
 ****************************************************************************************
 * @brief Preparation of wakeup controller for device wakeup
 *
 * @param[in]  polarity polarity high or low that should wakeup the device
 *
 * @return void
 ****************************************************************************************
 */
void user_prepare_wkup_controller(uint32_t polarity);

/**
 ****************************************************************************************
 * @brief checks if ke_msgs_malloc is possible for binaty mode buffer allocation
 *
 * @param[in]  param_len length of memory to be allocated
 *
 * @return void
 ****************************************************************************************
 */
bool ke_check_msg_alloc(uint16_t const param_len);

/**
 ****************************************************************************************
 * @brief Exit sleep immediately, connection or disconnection
 *
 * @return void
 ****************************************************************************************
 */
void user_exit_sleep(void);

#if defined(OUTBOUND_CHAR_QUEUE)

/**
 ****************************************************************************************
 * @brief Initialize command queue for the outbound characteristic
 *
 * @return void
 ****************************************************************************************
 */
void outbound_char_init_queue(void);

/**
 ****************************************************************************************
 * @brief Flush command queue for the outbound characteristic
 *
 * @return void
 ****************************************************************************************
 */
void outbound_char_flush_queue(void);

/**
 ****************************************************************************************
 * @brief Add an item to command queue for the outbound characteristic
 *
 * @return void
 ****************************************************************************************
 */
void outbound_char_enqueue(const char* string_ptr);

/**
 ****************************************************************************************
 * @brief Remove an item from the command queue for the outbound characteristic
 *
 * @return void
 ****************************************************************************************
 */
char* outbound_char_dequeue(void);

#endif // OUTBOUND_CHAR_QUEUE


#endif //_USER_UTILITY_FUNCTIONS_H_

/// @} APP
