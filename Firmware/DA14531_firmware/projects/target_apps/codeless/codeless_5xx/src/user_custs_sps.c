/**
 ****************************************************************************************
 *
 * @file user_custs_sps.c
 *
 * @brief Functions to support binary mode using the sps custom service
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "hash.h"
#include "user_utility_functions.h"
#include "user_codeless_env.h"
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "ke_mem.h"
#include "uart.h"
#include "user_periph_setup.h"
#include "user_codeless_env.h"
#include "user_at_commands.h"
#include "user_gap.h"

#include "custs1_task.h"
#include "user_custs_sps.h"
#include "user_custs1_def_585.h"
#include "user_gatt.h"
#include "prf.h"
#include "ke_env.h"
#include "ke.h"
#include "lld_sleep.h"
#include "lld_evt.h"
#include "user_custs_sps.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define RX_CALLBACK_SIZE        (uint8_t)8
#define UART_RX_INTR_SIZE       8

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

bool uart_rx_activate(void);
bool spss_uart_to_ble_copy_send (void);
void user_character_parser_start(void);


uint32_t uart_sps_get_tx_buffer_size(void)
{
    uint8_t isr_enabled = uart_intr_config_getf(CODELESS_UART)&ETBEI_dlh1;
    return (uint32_t)isr_enabled;
}

static bool uart_sps_fifo_check(void)
{
    if ((uart_tx_empty_getf(CODELESS_UART) == 0)  || (uart_thr_empty_getf(CODELESS_UART) == 0)  || (uart_data_ready_getf(CODELESS_UART)!=0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void uart_sps_flow_on(void)
{
#if (UART_HW_FLOW_ENABLED)
    // Configure modem (HW flow control enable)
    #ifdef CODELESS_UART2
    SetWord32(UART2_MCR_REG, UART_AFCE|UART_RTS);
    #else
    SetWord32(UART_MCR_REG, UART_AFCE|UART_RTS);
    #endif
#endif //UART_HW_FLOW_ENABLED
}

bool uart_sps_flow_off(bool force)
{
    bool flow_off = true;
    if(force)
    {
#if (UART_HW_FLOW_ENABLED)
        #if defined(USE_AT_FLOWCONTROL)
        if( codeless_env.flow_control_enabled==false)
            return (flow_off);
        #endif

        // Configure modem (HW flow control disable, 'RTS flow off')
        #ifdef CODELESS_UART2
        SetWord32(UART2_MCR_REG, GetWord32(UART2_MCR_REG) & (~UART_RTS));
        #else
        SetWord32(UART_MCR_REG, GetWord32(UART_MCR_REG) & (~UART_RTS));
        #endif
#endif //UART_HW_FLOW_ENABLED

    }
    else do
    {
        if  (uart_sps_fifo_check())
        {
            flow_off = false;
            break;
        }
#if (UART_HW_FLOW_ENABLED)
        #if defined(USE_AT_FLOWCONTROL)
        if( codeless_env.flow_control_enabled==true)
        {
        #endif //USE_AT_FLOWCONTROL
        // Configure modem (HW flow control disable, 'RTS flow off')
        #ifdef CODELESS_UART2
        SetWord32(UART2_MCR_REG, GetWord32(UART2_MCR_REG) & (~UART_RTS));
        #else
        SetWord32(UART_MCR_REG, GetWord32(UART_MCR_REG) & (~UART_RTS));
        #endif
        #if defined(USE_AT_FLOWCONTROL)
        }
        #endif //USE_AT_FLOWCONTROL
#endif //UART_HW_FLOW_ENABLED

        // Wait for 1 character duration to ensure host has not started a transmission at the
        // same time
        for (int i=0;i<UART_WAIT_BYTE_COUNTER;i++);

        // Check if data has been received during wait time
        if(!(uart_data_ready_getf(CODELESS_UART)==0))
        {
            // Re-enable UART flow
            uart_sps_flow_on();

            // We failed stopping the flow
            flow_off = false;
        }
    } while(false);

    return (flow_off);
}


#ifdef USE_AT_BINARY_MODE
static struct custs1_val_ntf_ind_req *uart_allocate_rx_buffer_spss(uint16_t size)
{
    struct custs1_val_ntf_ind_req *p_buff = KE_MSG_ALLOC_DYN(CUSTS1_VAL_NTF_REQ,
                                                             prf_get_task_from_id(TASK_ID_CUSTS1),
                                                             TASK_APP,
                                                             custs1_val_ntf_ind_req,
                                                             size);
    ASSERT_ERROR(p_buff);

    return p_buff;
}

static void user_check_free_sps_buffer( struct ke_msg *buff )
{

    if( buff!=NULL)
    {
        __disable_irq();
        ke_msg_free(buff);
        __enable_irq();
    }
}
void user_free_sps_buffers(void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;

    __disable_irq();
    co_list_flush(&p_env->rx_list_ready);
    co_list_flush(&p_env->tx_list_ready);
    __enable_irq();

    user_check_free_sps_buffer(p_env->p_rx_active);
    user_check_free_sps_buffer(p_env->p_tx_active);
    user_check_free_sps_buffer(p_env->p_rx_ready_active);

    __disable_irq();
    p_env->p_rx_active = NULL;
    p_env->p_tx_active = NULL;
    p_env->p_rx_ready_active = NULL;
    __enable_irq();
    p_env->lists_initialized=0;
}

void command_mode_second_guard_time_timeout(void)
{
    codeless_env.binary_mode=false;
    user_set_uart_to_codeless_settings();
    console_env.parser_flag = CHAR_PARSER_ACTIVE;
    console_env.input_cmd_char_index = 0;
    user_free_sps_buffers();
    user_character_parser_start();

    user_ble_force_tx_flow_off();
    codeless_env.postpone_uart_rx_to=false;
    send_to_local("OK\r\n");
    codeless_env.command_mode_second_guard_time_timer_active = false;
}

bool user_check_escape_chars(uint8_t  *data, uint8_t length)
{
    if(length !=NUM_OF_ESCAPE_CHARACTERS)
        return false;

    if( (data[0]==codeless_env.escape_chars[0])&&(data[1]==codeless_env.escape_chars[0])&&(data[2]==codeless_env.escape_chars[0]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void check_escape_sequence(uint8_t *data, uint16_t length)
{
    codeless_env.prev_time=codeless_env.current_time;
    codeless_env.current_time=lld_evt_time_get();

    /* We have RX while 2nd guard time is active, this violates the binary mode exit condition */
    if (codeless_env.command_mode_second_guard_time_timer_active)
    {
        app_easy_timer_cancel(codeless_env.command_mode_second_guard_time_timer);
        codeless_env.command_mode_second_guard_time_timer_active = false;
        codeless_env.postpone_uart_rx_to=false;
    }

    /*Proceed to check for the escape characters if escape_time1 is 0 or there is inactivity larger than escape_time1 */
    /* current_time and prev_time are using multiples of 0.625 msec from lld_evt_time_get() */
    if( ((codeless_env.current_time-codeless_env.prev_time) > codeless_env.escape_time1) || (codeless_env.escape_time1==0))
    {
     /* Check for escape characters and switch to CL operation */
     if(user_check_escape_chars((uint8_t *)data , length)==true)
     {
         if(codeless_env.escape_time2>0)
         {
            codeless_env.command_mode_second_guard_time_timer_active =true;
            codeless_env.command_mode_second_guard_time_timer = app_easy_timer(codeless_env.escape_time2/16 , command_mode_second_guard_time_timeout);
            /*we do not release the uart rx buffer due to timeout */
            codeless_env.postpone_uart_rx_to=true;
         }
         else
         {
            command_mode_second_guard_time_timeout();
         }
        return;
      }
      }

}


bool spsc_uart_to_ble_copy_send (void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;

    struct custs1_val_ntf_ind_req * req_original = (struct custs1_val_ntf_ind_req *)ke_msg2param(p_env->p_rx_ready_active);
    bool check=ke_check_msg_alloc(req_original->length);

    if(!check)
    {
        //todo defer copy
        while(1);
    }
    user_prf_gatt_write(codeless_env.hdl_dsps_rx_val,  &req_original->value[0], req_original->length, GATTC_WRITE_NO_RESPONSE, 0xFE32);
    p_env->ble_tx_pkts+=1;
    p_env->ble_tx_bytes += req_original->length;

    return true;
}

bool spss_uart_to_ble_copy_send (void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;

    struct custs1_val_ntf_ind_req * req_original = (struct custs1_val_ntf_ind_req *)ke_msg2param(p_env->p_rx_ready_active);
    bool check=ke_check_msg_alloc(req_original->length);

    if(!check)
    {
        //todo defer copy
    }

    struct custs1_val_ntf_ind_req * req = (struct custs1_val_ntf_ind_req *)uart_allocate_rx_buffer_spss(req_original->length);
    p_env->p_rx_ready_active_copy=ke_param2msg(req); //DBG

    memcpy(&req->value[0], &req_original->value[0], req_original->length);

    req->length=req_original->length;
    p_env->ble_tx_bytes += req->length;
    p_env->ble_tx_pkts+=1;

    req->conidx=0;
    req->handle=CUST1_SPSS_IDX_TX_VAL;
    req->notification=true;

    ASSERT_ERROR(req);
    KE_MSG_SEND(req);
    return true;
}

void uart_to_ble_confirm(bool success)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;

    if ( success ) {
        p_env->ble_tx_pkts_ack++;
        if(p_env->p_rx_ready_active!=NULL)
        {
            __disable_irq();
            ke_msg_free(p_env->p_rx_ready_active);
            __enable_irq();
        }
        p_env->p_rx_ready_active = NULL;
    }
    else
    {
        p_env->ble_tx_pkts_nack++;
        if (!p_env->tx_flow_en)
        {
            return;
        }
        /* msg is free at profile, we should have a copy ? */
#if !defined(__DA14531_01__)
        if (codeless_env.bt_role == GAP_ROLE_CENTRAL)
        {
            spsc_uart_to_ble_copy_send();
        }
        else
#endif
        {
            spss_uart_to_ble_copy_send();
        }
    }
}

void uart_rx_callback(uint16_t read_size)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;
    struct custs1_val_ntf_ind_req *p_buff= (struct custs1_val_ntf_ind_req *) ke_msg2param(p_env->p_rx_active);

    if( p_env->p_rx_active == NULL)
    {
        //TO after flow off
        return;
    }

    p_buff->length+=read_size;

    uint16_t new_index=p_buff->length;
    uint16_t size_left=ELEMENT_SIZE_RX-new_index;
    p_env->uart_rx_intr++;

    if(size_left<RX_CALLBACK_SIZE)
    {
         p_env->uart_rx_bytes += p_buff->length;
         p_env->uart_rx_pkts++;
        __disable_irq();
        co_list_push_back( &p_env->rx_list_ready, &p_env->p_rx_active->hdr);
        __enable_irq();
        p_env->p_rx_active = NULL;

        check_escape_sequence(&p_buff->value[0], p_buff->length);
        if( !user_check_set_flow_off())
        {
            uart_rx_activate();
        }
    }
    else
    {
        uart_register_rx_cb(CODELESS_UART, &uart_rx_callback);
        uart_receive(CODELESS_UART, (uint8_t *)&p_buff->value[new_index], UART_RX_INTR_SIZE, UART_OP_INTR);
    }
}

uint16_t uart_get_nof_rx_items(void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;
    struct custs1_val_ntf_ind_req *p_buff=  (struct custs1_val_ntf_ind_req *)ke_msg2param(p_env->p_rx_active);
    return p_buff->length;
}

void user_check_uart_rx_to(void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;
    struct custs1_val_ntf_ind_req *p_buff=  (struct custs1_val_ntf_ind_req *)ke_msg2param(p_env->p_rx_active);

    uint32_t rx_length=p_buff->length;

    if( rx_length != 0 )
    {
        if(p_env->rx_cnt_prev==rx_length)
        {
            /*If data size is the same as previous data wait for some rounds */
            p_env->rx_to_cnt++;
            if ( p_env->rx_to_cnt>5)
            {
                p_env->rx_to_cnt=0;

               uart_rxdata_intr_setf(CODELESS_UART, UART_BIT_DIS);
               uart_rls_intr_setf(CODELESS_UART, UART_BIT_DIS);

               p_env->uart_rx_bytes += p_buff->length;
               p_env->uart_rx_pkts++;

               __disable_irq();
               co_list_push_back( &p_env->rx_list_ready, &p_env->p_rx_active->hdr);
               __enable_irq();

               check_escape_sequence(&p_buff->value[0], p_buff->length);
               p_env->p_rx_active = NULL;

                if( !user_check_set_flow_off())
                {
                    uart_rx_activate();
                }
            }
        }
        else
        {
           /* activity detected, wait */
            p_env->rx_cnt_prev = rx_length;
            p_env->rx_to_cnt=0;
        }
        p_env->rx_zero_data_cnt = 0;
    }
    else
    {
        /* Zero data */
        p_env->rx_zero_data_cnt++;
    }
}

bool uart_rx_activate(void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;
    bool check=ke_check_msg_alloc(ELEMENT_SIZE_RX);
    if(!check)
    {

        p_env->uart_flow_off = 1;
        __disable_irq();
        uart_sps_flow_off(false);
        __enable_irq();
        return false;
    }

    struct custs1_val_ntf_ind_req *p_buff = uart_allocate_rx_buffer_spss(ELEMENT_SIZE_RX);

    p_buff->length=0;

    p_env->nof_uart_rx_allocs++;

    __disable_irq();
    p_env->p_rx_active  = ( struct ke_msg * )ke_param2msg(p_buff);
    __enable_irq();

    p_env->rx_cnt_prev=0;
    p_env->rx_zero_data_cnt=0;
    p_env->rx_to_cnt=0;
    uart_register_rx_cb(CODELESS_UART, &uart_rx_callback);
    uart_receive(CODELESS_UART, (uint8_t *)p_buff->value, UART_RX_INTR_SIZE, UART_OP_INTR);
    return true;
}

void user_init_queues(void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;

    co_list_init(&p_env->rx_list_ready);
    co_list_init(&p_env->tx_list_ready);

    p_env->p_rx_active = NULL;
    p_env->p_tx_active = NULL;
    p_env->p_rx_ready_active = NULL;

    p_env->lists_initialized = true;
}

void uart_tx_callback(void *user_data, uint16_t len)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;
    /* Free the tx'ed message */
    struct custs1_val_write_ind *p_buff = NULL;
    KE_MSG_FREE(p_env->p_tx_active);
    p_env->p_tx_active = NULL;

    /*Check if buffers are pending for uart TX*/
    if( p_env->tx_list_ready.cnt > 0 ){
        __disable_irq();
        p_env->p_tx_active = ( struct ke_msg * )co_list_pop_front(&p_env->tx_list_ready);
        __enable_irq();
        p_buff = (struct custs1_val_write_ind *)ke_msg2param(p_env->p_tx_active);

        p_env->uart_tx_bytes+=p_buff->length;
        p_env->uart_tx_pkts++;
        p_env->uart_tx_intr++;

        uart_register_tx_cb(CODELESS_UART, (uart_cb_t)uart_tx_callback);
        uart_send(CODELESS_UART, (const uint8_t *)p_buff->value, p_buff->length, UART_OP_INTR);
    }
    uart_test_tx_queue_for_flow_on();
}

bool uart_test_tx_queue_for_flow_on(void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;
    if(p_env->ble_forced_flow_off == 1)
        return false;
    if ((p_env->tx_list_ready.cnt < TX_FLOW_ON_LVL) && (p_env->ble_flow_off==1) )
    {
        p_env->ble_flow_off = 0;
        user_send_sps_ble_flow(FLOW_ON);
        return true;
    }
    return false;
}

bool uart_test_tx_queue_for_flow_off(void)
{
     struct sps_env_t *p_env = &codeless_env.sps_env;

    if ( (p_env->tx_list_ready.cnt > TX_FLOW_OFF_LVL) && (p_env->ble_flow_off==0) )
    {
        p_env->ble_flow_off = 1;
        user_send_sps_ble_flow(FLOW_OFF);
        return true;
    }
    return false;
}

void sps_uart_tx_async(void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;
    __disable_irq();

    if( p_env->p_tx_active != NULL )
    {
        __enable_irq();
          return;
    }

    if( p_env->tx_list_ready.cnt !=0 ){
        p_env->p_tx_active = ( struct ke_msg * )co_list_pop_front(&p_env->tx_list_ready);
        struct custs1_val_write_ind *p_buff = (struct custs1_val_write_ind *)ke_msg2param(p_env->p_tx_active);

        p_env->uart_tx_bytes+=p_buff->length;
        p_env->uart_tx_pkts++;

        uart_register_tx_cb(CODELESS_UART, (uart_cb_t)uart_tx_callback);
        uart_send(CODELESS_UART, (const uint8_t *)p_buff->value, p_buff->length, UART_OP_INTR);
    }
    __enable_irq();

}

void user_ble_to_uart(void *msg)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;
    struct ke_msg *msg_tx = ke_param2msg( msg );

    __disable_irq();
    co_list_push_back(&p_env->tx_list_ready, &msg_tx->hdr);
    __enable_irq();

    uart_test_tx_queue_for_flow_off();
}

bool user_check_set_flow_off(void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;
    __disable_irq();
    if ((p_env->rx_list_ready.cnt>RX_FLOW_OFF_LVL) && (p_env->uart_flow_off == 0) )
    {

        p_env->uart_flow_off = 1;

        uart_sps_flow_off(false);
        __enable_irq();
        return true;
    }

    __enable_irq();
    return false;
}

bool user_check_set_flow_on(void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;
    __disable_irq();
    if ( (p_env->rx_list_ready.cnt < RX_FLOW_ON_LVL) && (p_env->uart_flow_off == 1))
    {
        p_env->uart_flow_off = 0;
        uart_sps_flow_on();
        __enable_irq();
        return true;
    }
    __enable_irq();
    return false;
}

void user_sps_ble_rx_buffer(void *msg_param_value, uint16_t length)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;

    if(codeless_env.binary_mode==false)
        return;

    struct custs1_val_write_ind *req=KE_MSG_ALLOC_DYN(0,0,0, custs1_val_write_ind, length);

    //SPS TODO FLOW OF IF BUFF NO AVAIL
    p_env->ble_rx_bytes+=length;
    p_env->ble_rx_pkts++;

    p_env->nof_uart_tx_allocs++;

    memcpy(req->value, msg_param_value, length);
    req->length=length;
    user_ble_to_uart((void*)req);
    sps_uart_tx_async();
}

void user_spss_val_write_ind( struct custs1_val_write_ind* msg_param)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;

    if (msg_param->handle == CUST1_SPSS_IDX_RX_VAL)
    {

        user_sps_ble_rx_buffer(msg_param->value, msg_param->length);

    }
    else if (msg_param->handle == CUST1_SPSS_IDX_FLOW_CONTROL_VAL)
    {
        if(msg_param->value[0] == FLOW_ON)
        {
            p_env->tx_flow_en = true;
        }
        else if (msg_param->value[0] == FLOW_OFF)
        {
            p_env->tx_flow_en = false;
        }
    }
    else if (msg_param->handle == CUST1_SPSS_IDX_TX_CFG)
    {
         p_env->tx_cfg = *(uint16_t *)&msg_param->value[0];
         codeless_env.dsps_notif_enabled = ((msg_param->value[0] & 0x01) && (msg_param->value[1] == 0x00));
#if defined(USE_AT_BINARY_MODE)
         remote_dsps_support_prompt_send_to_local();
#endif //defined(USE_AT_BINARY_MODE)
    }
    else if (msg_param->handle == CUST1_SPSS_IDX_FLOW_CONTROL_CFG)
    {
        uint16_t ntf_cfg = co_read16p(&msg_param->value[0]);
        if (ntf_cfg == PRF_CLI_START_NTF)
        {
            uint8_t flow = (p_env->rx_flow_en ? FLOW_ON : FLOW_OFF);
            user_send_sps_ble_flow(flow);
        }

    }
}

sleep_mode_t user_rwip_sleep_check(void)
{
    sleep_mode_t proc_sleep = mode_active;
    uint32_t sleep_duration =rom_cfg_table[max_sleep_duration_external_wakeup_pos];

   // return mode_sleeping; //ghar test

#if (BLE_APP_PRESENT)
    if ( arch_ble_ext_wakeup_get() || (rwip_env.ext_wakeup_enable == 2) )  // sleep forever!
        sleep_duration = 0;
#else
#if (!EXTERNAL_WAKEUP) // sleep_duration will remain as it was set above....
    if (rwip_env.ext_wakeup_enable == 2)
        sleep_duration = 0;
#endif //(!EXTERNAL_WAKEUP)
#endif //BLE_APP_PRESENT

    do
    {
        // Do not allow sleep if system is in startup period
        if (check_sys_startup_period())
            break;

        /************************************************************************
         **************            CHECK KERNEL EVENTS             **************
         ************************************************************************/
        // Check if some kernel processing is ongoing
        if (!ke_sleep_check())
            break;

        // Processor sleep can be enabled
        proc_sleep = mode_idle;

        /************************************************************************
         **************           CHECK RADIO POWER DOWN           **************
         ************************************************************************/
        // Check if BLE + Radio are still sleeping
        if(GetBits16(SYS_STAT_REG, RAD_IS_DOWN)) {
            // If BLE + Radio are in sleep return the appropriate mode for ARM
            proc_sleep = mode_sleeping;
            break;
        }

        /************************************************************************
         **************              CHECK RW FLAGS                **************
         ************************************************************************/
        // First check if no pending procedure prevents us from going to sleep
        if (rwip_prevent_sleep_get() != 0)
            break;

        /************************************************************************
         **************           CHECK EXT WAKEUP FLAG            **************
         ************************************************************************/
        /* If external wakeup is enabled, sleep duration can be set to maximum, otherwise
         * the system must be woken-up periodically to poll incoming packets from HCI */
        if((BLE_APP_PRESENT == 0) || (BLE_INTEGRATED_HOST_GTL == 1 )) // No need for periodic wakeup if we have full-hosted system
        {
            if(!rwip_env.ext_wakeup_enable)
                sleep_duration = rom_cfg_table[max_sleep_duration_periodic_wakeup_pos];
        }



        /************************************************************************
         *                                                                      *
         *                   CHECK DURATION UNTIL NEXT EVENT                    *
         *                                                                      *
         ************************************************************************/
        // If there's any timer pending, compute the time to wake-up to serve it
        if (ke_env.queue_timer.first != NULL)
            sleep_duration =  rom_cfg_table[max_sleep_duration_external_wakeup_pos];

        /************************************************************************
         **************            CHECK KERNEL TIMERS             **************
         ************************************************************************/
        // Compute the duration up to the next software timer expires
        if (!ke_timer_sleep_check(&sleep_duration, rwip_env.wakeup_delay))
            break;

        #if (BLE_EMB_PRESENT)
        /************************************************************************
         **************                 CHECK BLE                  **************
         ************************************************************************/
        // Compute the duration up to the next BLE event
        if (!ea_sleep_check(&sleep_duration, rwip_env.wakeup_delay))
            break;
        #endif // BLE_EMB_PRESENT

        proc_sleep = mode_sleeping;
     } while(0);

     return proc_sleep;
}

void user_sps_sleep_check(void)
{
//If the binary mode is not supporting HW flow control then falling in sleep will cause loss
//of data
#if defined(CUSTS_SPSS)&&(UART_HW_FLOW_ENABLED==1)
    struct sps_env_t *p_env = &codeless_env.sps_env;

    if (app_default_sleep_mode == ARCH_EXT_SLEEP_ON)
    {
        do
        {
            #ifdef USE_AT_FLOWCONTROL
            if(codeless_env.flow_control_enabled==false)
                break;
            #endif
             if(uart_data_ready_getf(CODELESS_UART)!=0)
             {
                  p_env->rx_zero_data_cnt=0;
                    break;
             }

            /* Buffer ready for BLE TX */
            if ( p_env->p_rx_ready_active != NULL )
                break;

            if (uart_get_nof_rx_items()!=0)
                break;

            /* Kernel process in progress */
            if (user_rwip_sleep_check() != mode_sleeping)
                break;

            /* Buffers pending for UART TX */
            if (p_env->tx_list_ready.cnt>0)
                break;

            /* Buffers pending for BLE TX */
            if (p_env->rx_list_ready.cnt>0)
                break;

            /* Data still in UART TX buffer */

            if (uart_sps_get_tx_buffer_size())
                break;

            /* Data still in UART Fifos */

            if (uart_sps_fifo_check())
                break;

            /* Check RX TO Counter */
            if (p_env->rx_zero_data_cnt<2)
                break;

            /* Attempt flow off, wait of 1 character etc */
            if (!uart_sps_flow_off(false))
                break;

           uart_disable(CODELESS_UART);
           if (p_env->p_rx_active!=NULL)
           {
                KE_MSG_FREE(p_env->p_rx_active);
                p_env->p_rx_active = NULL;
           }

           NVIC_DisableIRQ(GPIO0_IRQn);
           p_env->power_on_state = PON_STATE_IDLE;
           p_env->rx_zero_data_cnt=0;

           arch_set_extended_sleep(0);

           return;
        }
        while(0);

       arch_disable_sleep();
    }

#else
    arch_disable_sleep();
#endif   // defined(CUSTS_SPSS)&&(UART_HW_FLOW_ENABLED==1)
}

bool sps_uart_to_ble (void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;

    if(codeless_env.postpone_uart_rx_to)
    {
        return false;
    }

    if (!p_env->tx_flow_en)
    {
        return false;
    }

    __disable_irq();

    if( p_env->rx_list_ready.cnt !=0 )
    {
        __enable_irq();

        if( p_env->p_rx_ready_active != 0 )
        {
            return false;
        }
        __disable_irq();
        p_env->p_rx_ready_active = (struct ke_msg *)co_list_pop_front(&p_env->rx_list_ready);
        __enable_irq();
#if !defined(__DA14531_01__)
        if (codeless_env.bt_role == GAP_ROLE_CENTRAL)
        {
            spsc_uart_to_ble_copy_send();
        }
        else
#endif
        {
            spss_uart_to_ble_copy_send();
        }

        return true;
    }
    __enable_irq();

    return false;
}

void uart_rx_reactivate(void)
{
    //Reactivate only if there is enough memory
    bool check=ke_check_msg_alloc(ELEMENT_SIZE_RX);

    if (check)
    {
        if( user_check_set_flow_on())
        {
            uart_rx_activate();
            uart_sps_flow_on();
        }
    }
}

void user_ble_force_tx_flow_off(void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;
    if (p_env->ble_forced_flow_off==0)
    {
        p_env->ble_forced_flow_off = 1;
        p_env->ble_flow_off=1;
        user_send_sps_ble_flow(FLOW_OFF);
    }
}


#if (UART_HW_FLOW_ENABLED)
#if defined(USE_AT_FLOWCONTROL)
static void uart_init_fc_pin_status(void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;
#if defined(__DA14531__)
    if(GPIO_GetPinStatus((GPIO_PORT)0, (GPIO_PIN)codeless_env.cts_pin) == false)
#else
    if(GPIO_GetPinStatus((GPIO_PORT)codeless_env.cts_port, (GPIO_PIN)codeless_env.cts_pin) == false)
#endif
    {
        p_env->ble_forced_flow_off = 0;
        uart_test_tx_queue_for_flow_on();
        //Set interrupt to detect rising edge of CTS
#if defined(__DA14531__)
        GPIO_EnableIRQ((GPIO_PORT)0, (GPIO_PIN)codeless_env.cts_pin, GPIO0_IRQn, 0, 1, 0);
#else
        GPIO_EnableIRQ((GPIO_PORT)codeless_env.cts_port, (GPIO_PIN)codeless_env.cts_pin, GPIO0_IRQn, 0, 1, 0);
#endif
    }
    else
    {
        user_ble_force_tx_flow_off();
        //Set interrupt to detect falling edge of CTS
#if defined(__DA14531__)
        GPIO_EnableIRQ((GPIO_PORT)0, (GPIO_PIN)codeless_env.cts_pin, GPIO0_IRQn, 1, 0, 0);
#else
        GPIO_EnableIRQ((GPIO_PORT)codeless_env.cts_port, (GPIO_PIN)codeless_env.cts_pin, GPIO0_IRQn, 1, 0, 0);
#endif
    }
}
#else
static void uart_init_fc_pin_status(void)
{
    struct sps_env_t *p_env = &codeless_env.sps_env;

    if(GPIO_GetPinStatus((GPIO_PORT)GPIO_UARTx_CTS_PORT, (GPIO_PIN)GPIO_UARTx_CTS_PIN) == false)
    {
        p_env->ble_forced_flow_off = 0;
        uart_test_tx_queue_for_flow_on();
        //Set interrupt to detect rising edge of CTS
        GPIO_EnableIRQ((GPIO_PORT)GPIO_UARTx_CTS_PORT, (GPIO_PIN)GPIO_UARTx_CTS_PIN, GPIO0_IRQn, 0, 1, 0);
    }
    else
    {
        user_ble_force_tx_flow_off();
        //Set interrupt to detect falling edge of CTS
        GPIO_EnableIRQ((GPIO_PORT)GPIO_UARTx_CTS_PORT, (GPIO_PIN)GPIO_UARTx_CTS_PIN, GPIO0_IRQn, 1, 0, 0);
    }
}
#endif // USE_AT_FLOWCONTROL


void gpio0_callback(void)
{
    NVIC_DisableIRQ(GPIO0_IRQn);    // Disable this interrupt
    uart_init_fc_pin_status();
    NVIC_ClearPendingIRQ(GPIO0_IRQn);
    NVIC_EnableIRQ(GPIO0_IRQn);     // Enable this interrupt
}
#endif // UART_HW_FLOW_ENABLED

void uart_fc_init(void)
{
    #if defined(USE_AT_FLOWCONTROL)
    if( codeless_env.flow_control_enabled==true)
    #endif
    {
        #if (UART_HW_FLOW_ENABLED)
        GPIO_RegisterCallback(GPIO0_IRQn, gpio0_callback);
        uart_init_fc_pin_status();
        #endif
    }
}

void user_init_sps(void)
{

#ifdef CFG_PERIPHERAL_CE_LEN_LIMITING_ENABLED
    codeless_env.in_binary_mode = true;
#endif

    struct sps_env_t *p_env = &codeless_env.sps_env;
    p_env->tx_flow_en = true;
    p_env->rx_flow_en = true;
    p_env->rx_flow_en=1;
    user_send_sps_ble_flow(FLOW_ON);

}

void user_on_sps_disconnect(void)
{

#ifdef CFG_PERIPHERAL_CE_LEN_LIMITING_ENABLED
    codeless_env.in_binary_mode = false;
#endif

    struct sps_env_t *p_env = &codeless_env.sps_env;
    if( p_env->p_rx_ready_active!=NULL)
    {
        __disable_irq();
        co_list_push_front(&p_env->rx_list_ready, &p_env->p_rx_ready_active->hdr);
        p_env->p_rx_ready_active=NULL;
        __enable_irq();
    }

}

void user_send_escape_sequence_cb(void)
{

    //Send the 3 escape characters
    uart_send(CODELESS_UART,(uint8_t *)codeless_env.escape_chars, NUM_OF_ESCAPE_CHARACTERS, UART_OP_INTR);

    /*If we are in resending mode resend */
    codeless_env.host_guard_time_timer1=app_easy_timer(codeless_env.escape_time2+ESC_TIMER1_TO_TIMER2(codeless_env.escape_time1),user_send_escape_sequence_cb);

    /* Start parser once */
    if(codeless_env.wait_esc_ack_from_host==false)
    {
        user_character_parser_start();
        codeless_env.wait_esc_ack_from_host=true;
    }
}

void user_initiate_binary_exit(void)
{
    uart_disable(CODELESS_UART);
    user_free_sps_buffers();

    user_on_sps_disconnect();
    user_ble_force_tx_flow_off();

    user_set_uart_to_codeless_settings();

    codeless_env.postpone_uart_rx_to=false;
    console_env.parser_flag = CHAR_PARSER_ACTIVE;
    console_env.input_cmd_char_index = 0;
    codeless_env.binary_mode=false;
    codeless_env.host_guard_time_timer1=app_easy_timer(ESC_TIMER1_TO_TIMER2(codeless_env.escape_time1),user_send_escape_sequence_cb);
 }

bool activate_binary_mode(bool print_ok)
{
    if(codeless_env.req_binary_mode==false)
        return false;

    codeless_env.req_binary_mode=false;
    codeless_env.binary_mode=true;

    #ifdef CUSTS_SPSS
    user_init_queues();
    codeless_env.sps_env.power_on_state=PON_STATE_IDLE;
    #endif //CUSTS_SPSS
    codeless_env.postpone_uart_rx_to=false;

    //user_init_sps();

    if(print_ok)
    {
        uart_send(CODELESS_UART, (const uint8_t*)OK_TERMINATION_STRING, 6, UART_OP_BLOCKING);
    }
    // Wait until all characters are printed
    uart_wait_tx_finish(CODELESS_UART);
    #ifdef CUSTS_SPSS
    uart_disable(CODELESS_UART);
    user_init_sps();
    #endif

    //codeless_env.disable_local_reply=true;
    return true;
}


/**
 ****************************************************************************************
 * @brief Returns whether the peer device supports CODELESS
 *
 * @return true if the peer device supports CODELESS
 ****************************************************************************************
 */
bool peer_supports_codeless(void)
{
#if !defined(__DA14531_01__)
    return (((codeless_env.bt_role == GAP_ROLE_CENTRAL) && (codeless_env.hdl_inbound_val!=0)) ||
        ((codeless_env.bt_role == GAP_ROLE_PERIPHERAL) && (codeless_env.codeless_notif_enabled==true)));
#else
    return ((codeless_env.bt_role == GAP_ROLE_PERIPHERAL) && (codeless_env.codeless_notif_enabled==true));
#endif
}

/**
 ****************************************************************************************
 * @brief Returns whether the peer device supports DSPS
 *
 * @return true if the peer device supports DSPS
 ****************************************************************************************
 */
bool peer_supports_dsps(void)
{
#if !defined(__DA14531_01__)
    return (((codeless_env.bt_role == GAP_ROLE_CENTRAL) && (codeless_env.hdl_dsps_tx_val!=0)) ||
           ((codeless_env.bt_role == GAP_ROLE_PERIPHERAL) && (codeless_env.dsps_notif_enabled==true)));
#else
    return ((codeless_env.bt_role == GAP_ROLE_PERIPHERAL) && (codeless_env.dsps_notif_enabled==true));
#endif
}

#if defined(USE_AT_BINARY_MODE)
/**
 ****************************************************************************************
 * @brief Informs the local if the remote peers supports CODELESS
 *
 * @return void
 ****************************************************************************************
 */
void remote_codeless_support_prompt_send_to_local(void)
{
    if (peer_supports_codeless())
    {
        if (codeless_env.remote_codeless_support_prompt_sent_to_local == false)
        {
            codeless_env.remote_codeless_support_prompt_sent_to_local = true;
            send_to_local(CODELESS_PEER);
        }
    }
}

/**
 ****************************************************************************************
 * @brief Informs the local if the remote peers supports DSPS
 *
 * @return void
 ****************************************************************************************
 */
void remote_dsps_support_prompt_send_to_local(void)
{
    if (peer_supports_dsps())
    {
        if (codeless_env.remote_dsps_support_prompt_sent_to_local == false)
        {
            codeless_env.remote_dsps_support_prompt_sent_to_local = true;
            send_to_local(DSPS_PEER);
        }
    }
}
#endif //defined(USE_AT_BINARY_MODE)

void user_reset_peer_status_vars(void)
{
    codeless_env.hdl_inbound_val=0;
    codeless_env.hdl_dsps_tx_val=0;
    codeless_env.codeless_notif_enabled=false;
    codeless_env.dsps_notif_enabled=false;
    codeless_env.remote_codeless_support_prompt_sent_to_local = false;
    codeless_env.remote_dsps_support_prompt_sent_to_local = false;
}

#endif //USE_AT_BINARY_MODE
