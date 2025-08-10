/**
 ****************************************************************************************
 *
 * @file user_baud.c
 *
 * @brief Functions for supporting the baud change command
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
#include "user_baud.h"
#include "user_codeless_env.h"
#include "user_utility_functions.h"
#include "arch_console.h"

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
#if defined(USE_AT_BAUD)

typedef struct
{
    UART_BAUDRATE baud_rate_reg_value;
    uint32_t baud_rate;
}
baud_rate_regs_and_values_t;

 const baud_rate_regs_and_values_t baud_rates[]=
 {
    { UART_BAUDRATE_230400 ,  230400 },
    { UART_BAUDRATE_115200 ,  115200 },
    { UART_BAUDRATE_57600  ,   57600 },
    { UART_BAUDRATE_38400  ,   38400 },
    { UART_BAUDRATE_28800  ,   28800 },
    { UART_BAUDRATE_19200  ,   19200 },
    { UART_BAUDRATE_14400  ,   14400 },
    { UART_BAUDRATE_9600   ,    9600 },
    { UART_BAUDRATE_4800   ,    4800 },
    { UART_BAUDRATE_2400   ,    2400 }
 };

 /*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

int32_t user_uart_baudrate_getf(uart_t *uart_id)
{
    int32_t baud_rate=-1;
    // Wait as long as UART is in busy state
    while(uart_is_busy_getf(uart_id));

    // Set Divisor Latch Access Bit in LCR register to access DLL & DLH registers
    SetBits16(&uart_id->UART_LCR_REGF, UART_DLAB, UART_BIT_EN);

    // Get fraction byte of baud rate.Only the 3:0 bits are useful
    uint16_t fraction=GetWord16(&uart_id->UART_DLF_REGF);
    fraction &=0x0F;

    // Get low byte of baud rate.Only the 7:0 bits are useful
    uint16_t low_byte=GetWord16(&uart_id->UART_RBR_THR_DLL_REGF);
    low_byte &=0xFF;

    // Set high byte of baud rate.Only the 6:4 bits are useful
    uint16_t high_byte=GetWord16(&uart_id->UART_IER_DLH_REGF);
    high_byte &=0x70;

    // Reset Divisor Latch Access Bit in LCR register
    SetBits16(&uart_id->UART_LCR_REGF, UART_DLAB, UART_BIT_DIS);

    uint32_t reg_value= 0;
    reg_value = ((uint32_t)high_byte)<<16 | ((uint32_t)low_byte)<<8
                | ((uint32_t)fraction)<<0;

    size_t num_of_baud_rates=sizeof(baud_rates)/sizeof(baud_rates[0]);

    uint32_t kk=0;
    do
    {
        if (reg_value==baud_rates[kk].baud_rate_reg_value)
        {
            baud_rate=(int32_t)baud_rates[kk].baud_rate;
            break;
        }
        kk++;
    }
    while (kk < num_of_baud_rates);
    return baud_rate;
}

bool is_baud_rate_valid(int32_t baud_as_int, UART_BAUDRATE * uart_baud_rate)
{
    uint32_t jj=0;
    bool is_valid=false;
    size_t num_of_baud_rates = sizeof(baud_rates) / sizeof(baud_rates[0]);
    for (jj=0; jj < num_of_baud_rates ; jj++)
    {
        if (baud_as_int==baud_rates[jj].baud_rate)
        {
            is_valid=true;
            if (uart_baud_rate !=NULL)
            {
                *uart_baud_rate=baud_rates[jj].baud_rate_reg_value;
            }
            break;
        }
    }
    return is_valid;
}
#endif


/// @} APP
