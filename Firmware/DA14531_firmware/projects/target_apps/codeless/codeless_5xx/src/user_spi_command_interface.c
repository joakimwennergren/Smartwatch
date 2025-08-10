/**
 ****************************************************************************************
 *
 * @file user_spi_command_interface.c
 *
 * @brief Functions and supporting the spi command interface in CodeLess
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


 /**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup
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


#include "user_spi_command_interface.h"
#include "user_periph_setup.h"
#include "gpio.h"
#include "stdlib.h"
#include "ctype.h"

#if (CMD_LOCAL_SOURCE==CMD_SPI)

spi_rx_callback_t spi_rx_callback = NULL;

void register_spi_rx_callback(spi_rx_callback_t cb)
{
    spi_rx_callback = cb;
}

//Start adding the necessary spihddr functions
typedef enum
{
    SPIHDDR_STATE_IDLE,
    SPIHDDR_STATE_READ_REQUESTED_IN_IDLE,
    SPIHDDR_STATE_CS_WAIT_FOR_MASTER_OPCODE,
    SPIHDDR_STATE_MASTER_TRANSMISSION,
    SPIHDDR_STATE_MASTER_RECEPTION,
}
spihddr_state_t;

typedef enum
{
    SPIHDDR_EVENT_NONE,
    SPIHDDR_EVENT_CS_ASSERTION_DETECTED,
    SPIHDDR_EVENT_MASTER_OPCODE_RECEIVED,
    SPIHDDR_EVENT_CS_DEASSERTION_DETECTED
}
spihddr_event_t;

typedef enum
{
    SPIHDDR_ERROR_NO_ERROR,
    SPIHDDR_ERROR_INVALID_OPCODE,
    SPIHDDR_ERROR_INVALID_PROTOCOL_SEQUENCE,
}
spihddr_com_error_t;

volatile spihddr_state_t spihddr_state __SECTION_ZERO("retention_mem_area0");

volatile spihddr_com_error_t spihddr_error __SECTION_ZERO("retention_mem_area0");


volatile struct spihddr_info_t spihddr_env __SECTION_ZERO("retention_mem_area0");

#if defined(__DA14585__) || defined(__DA14586__)
    #define DRDY_GPIO_PORT               GPIO_PORT_1
    #define DRDY_GPIO_PIN                GPIO_PIN_2
#elif defined (__DA14531__)
    #define DRDY_GPIO_PORT               GPIO_PORT_0
    #define DRDY_GPIO_PIN                GPIO_PIN_9
#endif

void setup_spi_command_interface_pins(void)
{
#if defined (__DA14585__) || defined(__DA14586__)
    /*
    Set the appropriate GPIO ports in SPI clock mode (input), SPI Chip Select mode (input), SPI Data Out mode (output),
    and SPI Data In mode (input)
    */
    GPIO_ConfigurePin(SPI_EN_GPIO_PORT ,  SPI_EN_GPIO_PIN ,  INPUT , PID_SPI_EN ,  false);
    GPIO_ConfigurePin(SPI_CLK_GPIO_PORT,  SPI_CLK_GPIO_PIN,  INPUT , PID_SPI_CLK,  false);
    GPIO_ConfigurePin(SPI_DO_GPIO_PORT ,  SPI_DO_GPIO_PIN ,  OUTPUT, PID_SPI_DO ,  false); // This is the MISO port
    GPIO_ConfigurePin(SPI_DI_GPIO_PORT ,  SPI_DI_GPIO_PIN ,  INPUT , PID_SPI_DI ,  false); // This is the MOSI port

    // This is the DRDY Pin to indicate that spi data is available
    GPIO_ConfigurePin(DRDY_GPIO_PORT ,  DRDY_GPIO_PIN ,  OUTPUT, PID_GPIO   ,  false);

#elif defined (__DA14531__)
    /*
    Set the appropriate GPIO ports in SPI clock mode (input), SPI Chip Select mode (input), SPI Data Out mode (output),
    and SPI Data In mode (input)
    */
    GPIO_ConfigurePin(SPI_EN_GPIO_PORT,  SPI_EN_GPIO_PIN,  INPUT,  PID_SPI_EN,  false);
    GPIO_ConfigurePin(SPI_CLK_GPIO_PORT, SPI_CLK_GPIO_PIN, INPUT,  PID_SPI_CLK, false);
    GPIO_ConfigurePin(SPI_DO_GPIO_PORT,  SPI_DO_GPIO_PIN,  OUTPUT, PID_SPI_DO,  false);
    GPIO_ConfigurePin(SPI_DI_GPIO_PORT,  SPI_DI_GPIO_PIN,  INPUT,  PID_SPI_DI,  false);

    // This is the DRDY Pin to indicate that spi data is available
    GPIO_ConfigurePin(DRDY_GPIO_PORT ,  DRDY_GPIO_PIN ,  OUTPUT, PID_GPIO   ,  false);
#else
      #error "No configuration defined"
#endif

    // set_pad_functions();
    // GPIO_set_pad_latch_en(true);
}

#if defined (__DA14585__) || defined(__DA14586__)
int8_t spi_initialize_in_slave_mode(const spi_cfg_t *spi_cfg)
{
    // Force CS line to inactive state
    GPIO_SetActive(spi_cfg->cs_pad.port, spi_cfg->cs_pad.pin);

    // Enable Clock for SPI
    spi_enable();

    // Close SPI block and write control register with selected configuration
    SetWord16(&spi->SPI_CTRL_REGF,  (spi_cfg->spi_ms << 6) | (spi_cfg->spi_cp << 1) |
                                    (spi_cfg->spi_speed << 3) | (spi_cfg->spi_wsz << 7) |
                                    (spi_cfg->spi_irq << 14));

    // pin enabled in slave mode
    SetBits16(&spi->SPI_CTRL_REGF,SPI_EN_CTRL,1);

    // No FIFOs used (backwards compatible mode).
    // We need one character at a time
    SetBits16(&spi->SPI_CTRL_REG1F, SPI_FIFO_MODE, 3);

    // Clear the interrupt flag
    SetWord16(&spi->SPI_CLEAR_INT_REGF, 0x01);

    // Enable SPI block
    SetBits16(&spi->SPI_CTRL_REGF, SPI_ON, 1);

    NVIC_DisableIRQ(SPI_IRQn);
    NVIC_ClearPendingIRQ(SPI_IRQn);
    NVIC_SetPriority(SPI_IRQn,0);
    NVIC_EnableIRQ(SPI_IRQn);

    return SPI_STATUS_ERR_OK;
}
#elif defined (__DA14531__)
int8_t spi_initialize_in_slave_mode(const spi_cfg_t *spi_cfg)
{
    // Enable Clock for SPI
    spi_enable(); // Enable SPI clock by setting CLK_PER_REG[SPI_ENABLE] = 1

    // Disable SPI / Reset FIFO in SPI Control Register
    spi_ctrl_reg_setf(SPI_FIFO_RESET);

    // Set SPI Mode (CPOL, CPHA)
    SetBits16(&spi->SPI_CONFIG_REGF, SPI_MODE, spi_cfg->spi_cp);

    // Set SPI Master/Slave mode
    spi_config_reg_ms_mode_setf(spi_cfg->spi_ms);

    // Set SPI Word length
    spi_set_bitmode(spi_cfg->spi_wsz);

    // Set SPI FIFO threshold levels to 0
    SetWord16(&spi->SPI_FIFO_CONFIG_REGF, 0);

    // Set SPI clock in async mode (mandatory)
    spi_clock_reg_master_clk_mode_setf();

    spi_irq_rx_full_en_setf(SPI_IRQ_ENABLED);
    spi_irq_tx_empty_en_setf(SPI_IRQ_DISABLED);

    // Disable FIFO reset
    spi_ctrl_reg_spi_fifo_reset_setf(SPI_BIT_DIS);

    // Enable SPI TX path by setting SPI_CTRL_REG[SPI_TX_EN] = 1.
    spi_ctrl_reg_spi_tx_en_setf(SPI_BIT_EN);

    // Enable SPI RX path by setting SPI_CTRL_REG[SPI_RX_EN] = 1.
    spi_ctrl_reg_spi_rx_en_setf(SPI_BIT_EN);

    // Enable spi
    spi_ctrl_reg_spi_en_setf(SPI_BIT_EN);
    spi_txbuffer_low_force_write(0x55); //Alternating bit

    NVIC_ClearPendingIRQ(SPI_IRQn); // Clear interrupt requests while disabled
    NVIC_SetPriority(SPI_IRQn, 0);  // Set spi priority
    NVIC_EnableIRQ(SPI_IRQn);       // Enable SPI interrupt to CPU

    return SPI_STATUS_ERR_OK;
}
#endif


void reset_spihddr_state_machine(void)
{
    memset((struct spihddr_info_t*)&spihddr_env,(int)0,sizeof(struct spihddr_info_t));
    spihddr_state = SPIHDDR_STATE_IDLE;
    spihddr_error = SPIHDDR_ERROR_NO_ERROR;
}


void conf_spi_slave_cmd_interface(void)
{
    reset_spihddr_state_machine();
    spi_cfg_t spi_slave_cfg =
    {
        .spi_ms = SPI_MS_MODE_SLAVE,
        .spi_cp = SPI_CP_MODE_0,
        /*
        The speed parameter is not important in slave mode. It will work with the
        speed of the master regardless of the speed configured here.
        */
        .spi_speed = SPI_SPEED_MODE_2MHz,
        .spi_wsz = SPI_MODE_8BIT,
        .spi_cs = SPI_CS_0,
        .cs_pad.port = SPI_EN_GPIO_PORT,
        .cs_pad.pin = SPI_EN_GPIO_PIN,
#if defined (__DA14531__)
        .spi_capture = SPI_MASTER_EDGE_CAPTURE,
#endif
        .spi_irq = SPI_IRQ_ENABLED,
    };
    spi_initialize_in_slave_mode(&spi_slave_cfg);
}



void assert_spi_drdy_pin(void)
{
    GPIO_SetActive(DRDY_GPIO_PORT, DRDY_GPIO_PIN);
}

void deassert_spi_drdy_pin(void)
{
    GPIO_SetInactive(DRDY_GPIO_PORT, DRDY_GPIO_PIN);
}


#if defined(__DA14531__)


void send_data_to_spi_master(void)
{
    /*
    Since a transaction is already in progress there is no need to perform an
    spi_txbuffer_low_force_write.
    */
    while (spihddr_env.slave_tx_data.number_of_bytes_to_send >= 0)
    {
        // Wait until TX-FIFO is not full
        while (spi_tx_fifo_full_status_getf() == SPI_TX_FIFO_IS_FULL);
        spi_tx_fifo_write(spihddr_env.slave_tx_data.tx_buffer[spihddr_env.slave_tx_data.number_of_bytes_sent] & 0xFF);
        spihddr_env.slave_tx_data.number_of_bytes_sent++;
        spihddr_env.slave_tx_data.number_of_bytes_to_send--;
    }
    while (spi_tx_fifo_level_getf() != 0);
}
#endif


void spihddr_state_update(spihddr_state_t spihddr_new_state)
{
    spihddr_state = spihddr_new_state;
}

spihddr_state_t spihddr_get_state(void)
{
    return spihddr_state;
}

bool spihddr_is_idle(void)
{
    return (spihddr_state==SPIHDDR_STATE_IDLE);
}

// This function must be executed within the cs deassertion isr
volatile struct spi_slave_rx_data_t* get_spi_rx_data(void)
{
    return &spihddr_env.slave_rx_data;
}

typedef struct
{
    spihddr_state_t state;
    spihddr_event_t event;
}
state_and_event_t;

typedef struct
{
    state_and_event_t state_and_event[10];
    int index;
}
debug_state_and_event_t;

debug_state_and_event_t dbg_state_and_event;

void init_state_sequence(void)
{
    dbg_state_and_event.index = 0;
}

void store_state_sequence(spihddr_state_t state, spihddr_event_t event)
{
    dbg_state_and_event.state_and_event[dbg_state_and_event.index].state = state;
    dbg_state_and_event.state_and_event[dbg_state_and_event.index].event = event;
    dbg_state_and_event.index++;
}

static struct spi_slave_tx_data_t temp_tx={{0},0,0};

void spihddr_store_slave_tx_msg(uint8_t* data,uint8_t length)
{
    // This function is not called from an isr. This is a critical section

    GLOBAL_INT_DISABLE();
    memcpy(temp_tx.tx_buffer, data, length);
    temp_tx.number_of_bytes_to_send = length;

    // If the interface is not busy try to send the message
    if (!spihddr_env.is_busy)
    {
        assert_spi_drdy_pin();
    }
    /*
    If the interface is busy the message will be sent when the current
    operation is over
    */
    GLOBAL_INT_RESTORE();
}




static void spihddr_event_update(spihddr_event_t new_event)
{
    switch(spihddr_state)
    {
        case SPIHDDR_STATE_IDLE:
        case SPIHDDR_STATE_READ_REQUESTED_IN_IDLE:
        {
            if (new_event == SPIHDDR_EVENT_CS_ASSERTION_DETECTED)
            {
                store_state_sequence(SPIHDDR_STATE_READ_REQUESTED_IN_IDLE, SPIHDDR_EVENT_CS_ASSERTION_DETECTED);
                spihddr_env.waiting_for_master_opcode = true;

                spihddr_env.slave_rx_data.number_of_bytes_received = 0;
                spihddr_env.slave_rx_data.number_of_bytes_to_receive = 1;

                spihddr_env.slave_tx_data.number_of_bytes_sent = 0;
                spihddr_env.slave_tx_data.number_of_bytes_to_send =0;

                spihddr_state = SPIHDDR_STATE_CS_WAIT_FOR_MASTER_OPCODE;

                assert_spi_drdy_pin();  // This may be already asserted
            }
            else
            {
                // In this state any other event is invalid - protocol error
                spihddr_error = SPIHDDR_ERROR_INVALID_PROTOCOL_SEQUENCE;
            }
        }
        break;

        case SPIHDDR_STATE_CS_WAIT_FOR_MASTER_OPCODE:
        {
            if (new_event == SPIHDDR_EVENT_MASTER_OPCODE_RECEIVED)
            {
                store_state_sequence(SPIHDDR_STATE_CS_WAIT_FOR_MASTER_OPCODE, SPIHDDR_EVENT_MASTER_OPCODE_RECEIVED);
                spihddr_env.waiting_for_master_opcode = false;
                uint8_t opcode = spihddr_env.slave_rx_data.rx_buffer[0];

                /*
                This part is common for both opcodes.The receive buffer must be cleared since now either
                the buffer size or the number of available data must be sent.
                */
                //memset((void*)&spihddr_env.slave_rx_data.rx_buffer[0],(int)0, sizeof(spihddr_env.slave_rx_data.rx_buffer));
                spihddr_env.slave_rx_data.number_of_bytes_received = 0;
                spihddr_env.slave_rx_data.number_of_bytes_to_receive = 0;

                switch (opcode)
                {
                    case SPIHDDR_MASTER_TX_OPCODE:
                    {
                        /*
                        The master will transmit an amount of data. Therefore the slave will have to indicate
                        the size of the available spi buffer. The first two bytes of the rx buffer will have to
                        be discarded.
                        */

                        spihddr_env.slave_tx_data.number_of_bytes_to_send = 2;
                        spihddr_env.slave_tx_data.number_of_bytes_sent = 0;

                        // Send the size of the available buffer
                        spihddr_env.slave_tx_data.tx_buffer[0] = CMD_BUFFER_SIZE;
                        spihddr_env.slave_tx_data.tx_buffer[1] = 0;

                        spihddr_env.slave_rx_data.number_of_bytes_received = 0;
                        spihddr_env.slave_rx_data.number_of_bytes_to_receive = CMD_BUFFER_SIZE;

                     #if defined (__DA14531__)
                        /*
                        Disabling and enabling spi will reset the value in SPI_TXBUFFER_FORCE_L_REG
                        so that the actual data can be written
                        */

                         // Clear Tx, Rx and DMA enable paths in Control Register
                        spi_ctrl_reg_clear_enable_setf();
                        // Enable TX path
                        spi_ctrl_reg_spi_tx_en_setf(SPI_BIT_EN);
                        // Enable RX path
                        spi_ctrl_reg_spi_rx_en_setf(SPI_BIT_EN);
                        // Enable SPI
                        spi_ctrl_reg_spi_en_setf(SPI_BIT_EN);

                        spi_txbuffer_low_force_write(spihddr_env.slave_tx_data.tx_buffer[0] & 0xFF );

                        GPIO_ConfigurePin( SPI_EN_GPIO_PORT,  SPI_EN_GPIO_PIN,  INPUT, PID_GPIO,   false );
                        GPIO_ConfigurePin( SPI_EN_GPIO_PORT,  SPI_EN_GPIO_PIN,  INPUT, PID_SPI_EN, false );


                        spihddr_env.slave_tx_data.number_of_bytes_sent = 1;
                        spihddr_env.slave_tx_data.number_of_bytes_to_send--;

                     #endif
                        spihddr_state = SPIHDDR_STATE_MASTER_TRANSMISSION;
                        deassert_spi_drdy_pin();
                    }
                    break;

                    case SPIHDDR_MASTER_RX_OPCODE:
                    {
                        /*
                        The master has sent a receive request due to the assertion of the DRDY pin. All the
                        information necessary is already available.A buffer will be prepared containing the
                        byte count in the first two positions and the rest of the data in the next positions.
                        */

                        // Fill in the data
                        memcpy((void*)&spihddr_env.slave_tx_data.tx_buffer[2], temp_tx.tx_buffer,temp_tx.number_of_bytes_to_send);
                        spihddr_env.slave_tx_data.number_of_bytes_to_send = 2+temp_tx.number_of_bytes_to_send;

                        // Place the size of the pending data to spi tx buffer
                        spihddr_env.slave_tx_data.tx_buffer[0] = temp_tx.number_of_bytes_to_send;
                        spihddr_env.slave_tx_data.tx_buffer[1] = 0x00;
                        spihddr_env.slave_tx_data.number_of_bytes_sent = 0;

                        // The temporary message is no longer necessary. It needs to be cleared
                        memset(temp_tx.tx_buffer,(int)0, sizeof(temp_tx.tx_buffer));
                        temp_tx.number_of_bytes_to_send = 0;

                     #if defined (__DA14585__) || defined(__DA14586__)
                        SetWord16(&spi->SPI_RX_TX_REG0F, spihddr_env.slave_tx_data.tx_buffer[0] & 0xFF);
                        spihddr_env.slave_tx_data.number_of_bytes_sent = 1;
                        spihddr_env.slave_tx_data.number_of_bytes_to_send--;
                        spihddr_state = SPIHDDR_STATE_MASTER_RECEPTION;
                        deassert_spi_drdy_pin();

                     #elif defined (__DA14531__)
                        /*
                        Disabling and enabling spi will reset the value in SPI_TXBUFFER_FORCE_L_REG
                        so that the actual data can be written
                        */

                         // Clear Tx, Rx and DMA enable paths in Control Register
                        spi_ctrl_reg_clear_enable_setf();
                        // Enable TX path
                        spi_ctrl_reg_spi_tx_en_setf(SPI_BIT_EN);
                        // Enable RX path
                        spi_ctrl_reg_spi_rx_en_setf(SPI_BIT_EN);
                        // Enable SPI
                        spi_ctrl_reg_spi_en_setf(SPI_BIT_EN);

                        // Ensure that the old value in low force reg is erased
                        spi_txbuffer_low_force_write(spihddr_env.slave_tx_data.tx_buffer[0] & 0xFF );
                        GPIO_ConfigurePin( SPI_EN_GPIO_PORT,  SPI_EN_GPIO_PIN,  INPUT, PID_GPIO,   false );
                        GPIO_ConfigurePin( SPI_EN_GPIO_PORT,  SPI_EN_GPIO_PIN,  INPUT, PID_SPI_EN, false );

                        spihddr_env.slave_tx_data.number_of_bytes_sent = 1;
                        spihddr_env.slave_tx_data.number_of_bytes_to_send--;

                        spihddr_state = SPIHDDR_STATE_MASTER_RECEPTION;
                        deassert_spi_drdy_pin();
                        send_data_to_spi_master();
                     #endif
                    }
                    break;

                    default:
                        // This is an opcode error
                        spihddr_error = SPIHDDR_ERROR_INVALID_OPCODE;
                    break;
                }
            }
            else
            {
                // This is a protocol error
                spihddr_error = SPIHDDR_ERROR_INVALID_PROTOCOL_SEQUENCE;
            }
        }
        break;

        case SPIHDDR_STATE_MASTER_RECEPTION:
        case SPIHDDR_STATE_MASTER_TRANSMISSION:

            // As long as data is sent the state machine will be in this state.
            if (new_event == SPIHDDR_EVENT_CS_DEASSERTION_DETECTED)
            {
                store_state_sequence(SPIHDDR_STATE_MASTER_RECEPTION, SPIHDDR_EVENT_CS_DEASSERTION_DETECTED);
                if (spihddr_env.slave_rx_data.number_of_bytes_received > 0)
                {
                    // The first two rx bytes must be discarded
                    memmove((void*)&spihddr_env.slave_rx_data.rx_buffer[0],
                            (void*)&spihddr_env.slave_rx_data.rx_buffer[2],
                            spihddr_env.slave_rx_data.number_of_bytes_received);
                   // And the number of bytes must be adjusted accordingly
                   spihddr_env.slave_rx_data.number_of_bytes_received -=2;
                }

                #if defined (__DA14531__)
                {
                     //spi_irq_rx_full_en_setf(SPI_IRQ_ENABLED);
                     //spi_irq_tx_empty_en_setf(SPI_IRQ_DISABLED);
                }
                #endif
                // a packet is sent
                spihddr_state = SPIHDDR_STATE_IDLE;
            }
            else
            {
                // no other event expected here.This is a protocol error.
                spihddr_error = SPIHDDR_ERROR_INVALID_PROTOCOL_SEQUENCE;
            }
        break;
        default:
            // This is an enumeration error
            ASSERT_WARNING(0);
        break;
    }
}

/**
 ****************************************************************************************
 * @brief Handler for the GPIO IRQ assigned to CS deassertion
 *
 ****************************************************************************************
 */
void spihddr_cs_deassertion_gpio_isr_handler(void)
{
    GPIO_ResetIRQ(GPIO1_IRQn);

    spihddr_event_update(SPIHDDR_EVENT_CS_DEASSERTION_DETECTED);

    // Store the message received if any
    if (spihddr_env.slave_rx_data.number_of_bytes_received > 0)
    {
        if (spi_rx_callback != NULL)
        {
            spi_rx_callback(0);
        }
    }

    // Ensure that the state machine is at a known state.
    reset_spihddr_state_machine();
    spihddr_env.is_busy = false;

    // If there is a pending message to send to master attempt to send it.
    if (temp_tx.number_of_bytes_to_send > 0)
    {
        assert_spi_drdy_pin();
    }
}

/**
 ****************************************************************************************
 * @brief Initialize the GPIO IRQ assigned to CS deassertion
 *
 ****************************************************************************************
 */
void spihddr_cs_deassertion_gpio_isr_init(void)
{
    GPIO_RegisterCallback(GPIO1_IRQn, spihddr_cs_deassertion_gpio_isr_handler);
    GPIO_EnableIRQ(SPI_EN_GPIO_PORT, SPI_EN_GPIO_PIN, GPIO1_IRQn, false, true, 0);
}

/**
 ****************************************************************************************
 * @brief Handler for the GPIO IRQ assigned to CS assertion
 *
 ****************************************************************************************
 */
void spihddr_cs_assertion_gpio_isr_handler(void)
{
    GPIO_ResetIRQ(GPIO1_IRQn);
    arch_ble_force_wakeup();

    // Ensure that the state machine is at a known state
    reset_spihddr_state_machine();

    // Debugging
    init_state_sequence();

    spihddr_env.is_busy = true;

    // Update state machine with new event
    spihddr_event_update(SPIHDDR_EVENT_CS_ASSERTION_DETECTED);
}

/**
 ****************************************************************************************
 * @brief Initialize the GPIO IRQ assigned to CS assertion
 *
 ****************************************************************************************
 */
void spihddr_cs_assertion_gpio_isr_init(void)
{
    GPIO_RegisterCallback(GPIO2_IRQn, spihddr_cs_assertion_gpio_isr_handler);
    GPIO_EnableIRQ(SPI_EN_GPIO_PORT, SPI_EN_GPIO_PIN, GPIO2_IRQn, true, true, 0);
}

void setup_spihddr_gpios(void)
{
    spihddr_cs_assertion_gpio_isr_init();
    spihddr_cs_deassertion_gpio_isr_init();


    NVIC_ClearPendingIRQ(GPIO1_IRQn); // Clear interrupt requests while disabled
    NVIC_ClearPendingIRQ(GPIO2_IRQn); // Clear interrupt requests while disabled


    NVIC_SetPriority(GPIO1_IRQn, 0);  // Set GPIO1 priority
    NVIC_SetPriority(GPIO2_IRQn, 0);  // Set GPIO2 priority

    NVIC_EnableIRQ(GPIO1_IRQn);       // Enable GPIO1 interrupt to CPU
    NVIC_EnableIRQ(GPIO2_IRQn);       // Enable GPIO1 interrupt to CPU
}



/**
 ****************************************************************************************
 * @brief Exported function for SPI interrupt handler.
 ****************************************************************************************
 */

#if defined (__DA14585__) || defined(__DA14586__)

void SPI_Handler(void)
{
    uint8_t data = (uint8_t)(GetWord16(&spi->SPI_RX_TX_REG0F) & 0xFF);
    if (spihddr_env.waiting_for_master_opcode)
    {
        spihddr_env.slave_rx_data.rx_buffer[0] = data;
        spihddr_env.slave_rx_data.number_of_bytes_received = 1;
        spihddr_event_update(SPIHDDR_EVENT_MASTER_OPCODE_RECEIVED);
    }
    else
    {
        if (spihddr_env.slave_rx_data.number_of_bytes_to_receive > 0)
        {
            if (spihddr_env.slave_rx_data.number_of_bytes_received < sizeof(spihddr_env.slave_rx_data.rx_buffer))
            {
                spihddr_env.slave_rx_data.rx_buffer[spihddr_env.slave_rx_data.number_of_bytes_received] = data;
                spihddr_env.slave_rx_data.number_of_bytes_received++;
            }
        }
    }
    if (spihddr_env.slave_tx_data.number_of_bytes_to_send > 0)
    {
        SetWord16(&spi->SPI_RX_TX_REG0F, spihddr_env.slave_tx_data.tx_buffer[spihddr_env.slave_tx_data.number_of_bytes_sent] & 0xFF);
        spihddr_env.slave_tx_data.number_of_bytes_sent++;
        spihddr_env.slave_tx_data.number_of_bytes_to_send--;
    }
    // Clear the interrupt flag
    SetWord16(&spi->SPI_CLEAR_INT_REGF, 0x01);
}

#elif defined(__DA14531__)

void SPI_Handler(void)
{
    uint16_t spi_fifo_status;

    // Read FIFO Status
    spi_fifo_status = spi_fifo_status_getf();
    // Check for overflows
    if ((spi_fifo_status & SPI_RX_FIFO_OVFL) !=0)
    {
        spi_ctrl_reg_spi_fifo_reset_setf(SPI_BIT_EN);
        spi_ctrl_reg_spi_fifo_reset_setf(SPI_BIT_DIS);
    }
    if (spihddr_env.slave_rx_data.number_of_bytes_to_receive > 0 )
    {
        // Read access is permitted only if SPI_STATUS_RX_EMPTY
        // This should be always the case here
        if ((spi_fifo_status & (SPI_STATUS_RX_EMPTY)) == 0)
        {
            uint8_t data = (uint8_t)(spi_rx_fifo_read() & 0xFF);
            if (spihddr_env.waiting_for_master_opcode)
            {
                spihddr_env.slave_rx_data.rx_buffer[0] = data;
                spihddr_env.slave_rx_data.number_of_bytes_received = 1;
                spihddr_event_update(SPIHDDR_EVENT_MASTER_OPCODE_RECEIVED);
            }
            else
            {
                if (spihddr_env.slave_rx_data.number_of_bytes_received <= CMD_BUFFER_SIZE)
                {
                    spihddr_env.slave_rx_data.rx_buffer[spihddr_env.slave_rx_data.number_of_bytes_received] = data;
                    spihddr_env.slave_rx_data.number_of_bytes_received++;
                }
            }
        }
    }

    /*
    Reading the fifo does not clear it. Therefore the fifo must be reset
    and then restored to its normal state. The interrupt should be cleared as well.
    */
    spi_ctrl_reg_spi_fifo_reset_setf(SPI_BIT_EN);
    spi_ctrl_reg_spi_fifo_reset_setf(SPI_BIT_DIS);
}
#endif

#endif // CMD_LOCAL_SOURCE==CMD_SPI

/// @} APP
