/**
 ****************************************************************************************
 *
 * @file user_codeles_env.h
 *
 * @brief CodeLess enviroment settings and structures
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

#ifndef _USER_CODELESS_ENV_H_
#define _USER_CODELESS_ENV_H_
/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup APP_CODELESS
 *
 * @brief Codeless environment.
 *
 * Declares global codeless environment to be used throughout the application.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "app_api.h"
#include "battery.h"
#include "user_at_console.h"
#include "user_at_commands.h"
#include "user_periph_setup.h"
#include "user_custs1_def_585.h"

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

#define USER_MEMCMD_SLOT_NUMBER 4 /**< Number of availiable command slots for AT+MEMCMD */
#if (USER_MEMCMD_SLOT_NUMBER>99)
    #error "maximum supported number of cmd slots is 99"
#endif
#define USER_MEMCMD_LENGTH 100    /**< Number for each memcmd slot */
#define USER_MEMORY_SLOT_NUMBER 4 /**< Number of availiable slots for AT+MEM */
#define USER_MEMORY_LENGTH 100    /**< Number for each mem slot */
#if ((USER_MEMCMD_LENGTH>CMD_BUFFER_SIZE)||(USER_MEMORY_LENGTH>CMD_BUFFER_SIZE))
    #error "maximum memcmd or memory length cannot be less than cmd buffer size"
#endif

#define CODELESS_DEFAULT_I2C_ADDR_BITS 7  /**< Default I2C adress width: 7 bits */
#define CODELESS_DEFAULT_I2C_BITRATE 2    /**< Default I2C bitrate: 400kbit/s */
#define CODELESS_DEFAULT_I2C_REG_BITS 8   /**< Default I2C register width: 8bit */
#define CODELESS_SLEEP_AFTER_X10MSEC 1000 /**< Device will sleep if no command is received after
                                               This amount of time. (1000 is for 10sec)*/
#define CODELESS_BATTERY_TYPE BATT_CR2032 /**< Select battery type used for codeless hw. */

#define USER_MALLOC_CHECK /**< Define this in order to check when using user_malloc */

#define NUM_OF_ESCAPE_CHARACTERS 3
#define CODELESS_DEFAULT_ESC_TIME1 1000 /**<Time in msec needed to check the escape sequence to exit binary mode.  */
#define CODELESS_DEFAULT_ESC_TIME2 1000 /**<Time in msec needed to check the escape sequence to exit binary mode after the reception of escape characters.  */
#define CODELESS_DEFAULT_RESEND_ESC_TIME 100 /**<Time in x10msec to resend escape sequence in case that an AT acknowledge is not received*/

#define MSEC_TO_ESC_TIMER1(X) ((X)*1000/625)
#define MSEC_TO_ESC_TIMER2(X) ((X)/10)

#define ESC_TIMER1_TO_MSEC(X) ((X)*625/1000)
#define ESC_TIMER2_TO_MSEC(X) ((X)*10)

#define ESC_TIMER1_TO_TIMER2(X) (((X)*625/1000)/10) //Should be used to convert number of SLOTS to TIMER (x10msc) value

#define ELEMENT_SIZE_RX  codeless_env.sps_env.tx_size

#define HOSTSL_DEFAULT_SLP_MODE 0 /** Host wakeup is enabled */
#define HOSTSL_DEFAULT_WKUP_BYTE 0x00/** This value results in the maximum low time for host UART Rx */
#define HOSTSL_DEFAULT_WKUP_INTERVAL 1000/** Wakeup retry time in MSEC */
#define HOSTSL_DEFAULT_WKUP_TRIES 10 /** Wakeup retries */

//Valid only for DA14531
#define BLE_FEATURES_DLE  (BLE_ENC_FEATURE /*| BLE_CON_PARAM_REQ_PROC_FEATURE**/ | BLE_REJ_IND_EXT_FEATURE | BLE_SLAVE_INIT_EXCHG_FEATURE | BLE_PING_FEATURE | BLE_LE_LENGTH_FEATURE)
#define BLE_FEATURES_NO_DLE  (BLE_ENC_FEATURE /*| BLE_CON_PARAM_REQ_PROC_FEATURE*/ | BLE_REJ_IND_EXT_FEATURE | BLE_SLAVE_INIT_EXCHG_FEATURE | BLE_PING_FEATURE )
/**
 * \brief Bluetooth activity state
 *
 * This enumeration type is used to keep track of current device Bluetooth activity state
 */
typedef enum gap_activity
{
    IDLE,
    ADVERTISING,
    SCANNING,
    DISCOVERING,
    INITIATING_CONNECTION,
    BONDING,
    DISCONNECTING
} gap_activity_t;


/**
 * \brief IO functionality
 */
typedef enum io_func
{
    IO_FUNC_UNDEFINED = 0,      /**< IOtype 0 Default at bootup */
    IO_FUNC_INPUT,              /**< IOtype 1 */
    IO_FUNC_INPUT_PULLUP,       /**< IOtype 2 */
    IO_FUNC_INPUT_PULLDOWN,     /**< IOtype 3 */
    IO_FUNC_OUTPUT,             /**< IOtype 4 Push-Pull */
    IO_FUNC_ANALOG_INPUT,       /**< IOtype 5 P0_0 to P0_3 for 585/586.P0_1,P0_2,P0_6,P0_7 for 531 */
    IO_FUNC_ANALOG_INPUT_ATT3,  /**< IOtype 6 P0_0 to P0_3 for 585/586.P0_1,P0_2,P0_6,P0_7 for 531.Attenuates input voltage. */
    IO_FUNC_I2C_CLOCK,          /**< IOtype 7 Only one pin can be defined. */
    IO_FUNC_I2C_DATA,           /**< IOtype 8 Only one pin can be defined. */
    IO_FUNC_CONN_IND_HI,        /**< IOtype 9 Low to high on connection. */
    IO_FUNC_CONN_IND_LO,        /**< IOtype 10 High to low on connections. */
    // The settings below are not supported in this revision
    IO_FUNC_UART1_TX,           /**< IOtype 11 */
    IO_FUNC_UART1_RX,           /**< IOtype 12 */
    IO_FUNC_UART1_CTS,          /**< IOtype 13 */
    IO_FUNC_UART1_RTS,          /**< IOtype 14 */
    IO_FUNC_UART2_TX,           /**< IOtype 15 */
    IO_FUNC_UART2_RX,           /**< IOtype 16 */
    IO_FUNC_UART2_CTS,          /**< IOtype 17 */
    IO_FUNC_UART2_RTS,          /**< IOtype 18 */
    IO_FUNC_SPI_CLK,            /**< IOtype 19 */
    IO_FUNC_SPI_CS,             /**< IOtype 20 */
    IO_FUNC_SPI_MOSI,           /**< IOtype 21 */
    IO_FUNC_SPI_MISO,           /**< IOtype 22 */
    IO_FUNC_PWM1,               /**< IOtype 23 */
    IO_FUNC_PWM2,               /**< IOtype 24 This setting is supported */
    IO_FUNC_PWM3,               /**< IOtype 25 */
    IO_FUNC_PWM4,               /**< IOtype 26 */
    IO_FUNC_HRTBT,              /**< IOtype 27 */
    IO_FUNC_NOT_AVAILABLE       /**< IOtype 28 */
} io_func_t;


/**
 * \brief  Connection parameters
 */

struct connection_configuration_t
{
    uint16_t connection_interval;     /**< Connection Interval in BLE slots */
    uint16_t latency;                 /**< Latency in connection events */
    uint16_t time_out;                /**< Connection timeout in timer uints (x10ms) */
    uint16_t max_mtu;                 /**< maximum MTU in octets */

    uint16_t dle_tx_pkt_len;
    uint16_t dle_rx_pkt_len;


    bool param_update_enable;         /**< Parameter update action type */
    bool dle_en;                     /**< True is DLE is enabled */
    bool restore_params;             /**< Variable to restore params after disconnection */
};
 #ifdef CUSTS_SPSS
struct sps_env_t
{
    bool tx_flow_en;
    bool rx_flow_en;

    uint32_t uart_flow_off;
    uint32_t ble_flow_off;
    uint32_t ble_forced_flow_off;

    uint32_t power_on_state;

    uint32_t rx_bytes;
    uint32_t tx_bytes;

    bool lists_initialized;
    /* Holds buffers received by the UART and stored by the DMA */
    struct co_list rx_list_ready;
    struct ke_msg *p_rx_ready_active;
    struct ke_msg *p_rx_active;
    struct ke_msg *p_rx_ready_active_copy;

    //timer_hnd rx_to_timer;
    uint32_t rx_to_cnt;
    uint32_t rx_cnt_prev;
    uint32_t rx_zero_data_cnt;

    /* Holds buffers waiting to be transmitted by the UART */
    struct co_list tx_list_ready;
    struct ke_msg *p_tx_active;

    uint32_t nof_uart_tx_allocs;
    uint32_t nof_uart_tx_buffers;

    uint32_t nof_uart_rx_allocs;
    uint32_t nof_uart_rx_buffers;

    uint8_t peer_supports_dle;
    uint32_t mtu;
    uint32_t tx_size;
    //uint32_t tx_wait_level;
    uint16_t tx_cfg;

    /* Counters */
    uint32_t uart_rx_bytes;
    uint32_t uart_rx_pkts;
    uint32_t uart_rx_intr;

    uint32_t uart_to_cntr;

    uint32_t ble_tx_bytes;
    uint32_t ble_tx_pkts;
    uint32_t ble_tx_pkts_ack;
    uint32_t ble_tx_pkts_nack;

    uint32_t uart_tx_bytes;
    uint32_t uart_tx_pkts;
    uint32_t uart_tx_intr;

    uint32_t ble_rx_bytes;
    uint32_t ble_rx_pkts;

    uint32_t ble_flow_ntf_tx;
    uint32_t ble_flow_ntf_tx_cmp;
};
#endif
/**
 * \brief  CodeLess environment
 */

struct codeless_const_env_t
{
    #ifndef USE_AT_BINARY_MODE
    const uint8_t *adv_service_uuid;            /**< CL or DSPS Service UUID */
    #endif
    const uint8_t *service_uuid;                /**< Service UUID */
    const uint8_t *char_uuid_inbound;           /**< Inbound string UUID */
    const uint8_t *char_uuid_outbound;          /**< Outbound string UUID  */
    const uint8_t *char_uuid_flow_ctrl;         /**< Flow control UUID  */
    const uint8_t *dsps_service_uuid;           /**< Service UUID */
    #ifdef USE_AT_BINARY_MODE
    const uint8_t *dsps_char_uuid_rx;           /**< Inbound string UUID */
    const uint8_t *dsps_char_uuid_tx;           /**< Outbound string UUID  */
    const uint8_t *dsps_char_uuid_flow_ctrl;    /**< Flow control UUID  */
    #endif
};

struct codeless_env_t
{
    uint8_t connection_index;
    uint16_t hdl_inbound_val;                   /**< Inbound string peer handle */
    uint16_t hdl_outbound_val;                  /**< Outbound string peer handle */
    uint16_t hdl_flow_ctrl;                     /**< Flow control peer handle  */

    bool codeless_notif_enabled;
    #ifdef USE_AT_BINARY_MODE
    bool dsps_notif_enabled;
    #endif //USE_AT_BINARY_MODE

    #ifdef USE_AT_CONPAR
    struct connection_configuration_t conn_conf;/**< Connection configuration container  */
    #endif

    #ifdef USE_AT_BINARY_MODE
    uint16_t hdl_dsps_rx_val;                   /**< Inbound string peer handle */
    uint16_t hdl_dsps_tx_val;                   /**< Outbound string peer handle */
    uint16_t hdl_dsps_flow_ctrl;                /**< Flow control peer handle  */
    #endif

    #ifdef USE_AT_BINARY_MODE
    bool binary_mode;                           /**< Device is operating in binary mode */
    bool req_binary_mode;                       /**< Device is operating in binary mode */

    int escape_time1;                           /**< Guard Time #1 for binary escape sequence */
    int escape_time2;                           /**< Guard Time #2 for binary escape sequence */
    char escape_chars[NUM_OF_ESCAPE_CHARACTERS];/**< Escape characters needed for escape sequence , escape time1 -> escape_chars -> escape_time2*/
    uint32_t escape_chars_command_input;        /**< Escape characters as set by the user */
    bool wait_esc_ack_from_host;                /**< Wait esc ack from host while CODELESS_DEFAULT_RESEND_ESC_TIME  */

    uint32_t current_time;
    uint32_t prev_time;
    timer_hnd command_mode_second_guard_time_timer;
    bool command_mode_second_guard_time_timer_active;
    timer_hnd host_guard_time_timer1;
    bool disconnection_event;
    bool postpone_uart_rx_to;

    struct sps_env_t sps_env;
    #endif //USE_AT_BINARY_MODE

    #ifdef USE_AT_FLOWCONTROL
    bool flow_control_enabled;

    uint8_t rts_port_pin_input;
#if !defined(__DA14531__)
    uint8_t rts_port;
#endif
    uint8_t rts_pin;

    uint8_t cts_port_pin_input;
#if !defined(__DA14531__)
    uint8_t cts_port;
#endif
    uint8_t cts_pin;
    #endif //USE_AT_FLOWCONTROL

    #ifdef USE_AT_HOSTSLP
    uint8_t hst_sleep_mode;                      /**< */
    uint8_t hst_sleep_wakeup_byte;
    uint32_t hst_sleep_wakeup_retry_times;
    uint32_t hst_sleep_wakeup_retry_interval;     /**< in msec*/
    uint32_t hst_sleep_wakeup_retry_times_cnt;
    timer_hnd host_wakeup_attemt_timer;
    #endif

    bool event_trigger;
    bool disable_local_reply;                   /**< Some binary commands are local and remote, this variable blocks local reply  */

    io_func_t port_configuration[MAX_PIN_NUMBER];     /**< GPIO configuration array */
    bool port_io_state[MAX_PIN_NUMBER];               /**< GPIO state */

    #ifdef USE_AT_CMD
    timer_hnd tmr[4];                           /**< User Timer handles */
    #endif

    uint16_t adv_intv;                          /**< Advertising interval */
    uint8_t adv_data[28];                       /**< Advertising data */
    uint8_t adv_data_len;                       /**< Advertising data length */
    uint8_t resp_data[28];                      /**< Scan response data */
    uint8_t resp_data_len;                      /**< Scan response data length */
    uint8_t bt_role;                            /**< Codeless ble role */
    gap_activity_t gap_activity;                /**< Codeless ble state*/
    bool is_tk_entry_pending;                   /**< A temporary key entry is requested */
    bool is_connectable;                        /**< True if codeless is connectable */

    #ifdef USE_AT_CMD
    char* command_slot[USER_MEMCMD_SLOT_NUMBER];/**< Pointer to user command slot */
    #endif

    #ifdef USE_AT_MEM
    char* memory_slot[USER_MEMORY_SLOT_NUMBER]; /**< Pointer to user memory slot */
    #endif

    bool user_allow_to_go_to_sleep_flag;        /**< Flag to determine if application allows sleep*/
    uint8_t sleep_active;
    #ifdef USE_AT_RSSI
    uint8_t rssi;                               /**< RSSI indication when connected*/
    #endif
    #ifdef USE_AT_BAUD
    UART_BAUDRATE baud_rate;                    /**< Current baud rate */
    #endif

#if defined(USE_AT_BINARY_MODE)
    bool remote_codeless_support_prompt_sent_to_local;
    bool remote_dsps_support_prompt_sent_to_local;
    bool in_binary_mode;
#endif //defined(USE_AT_BINARY_MODE)
};

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
// Reversed bytes of the sps service as existed previously
#define SPS_SERV_ADV_UUID_REV_BYTES 0xb7, 0x5c, 0x49, 0xd2, 0x04, 0xa3, 0x40, 0x71, 0xa0, 0xb5, 0x35, 0x85, 0x3e, 0xb0, 0x83, 0x07

static const struct codeless_const_env_t codeless_const_env = {
    #ifndef USE_AT_BINARY_MODE
    .adv_service_uuid = custs1_svc,
    #endif
    .service_uuid               = custs1_svc,
    .char_uuid_inbound          = CUST1_INBOUND_UUID_128,
    .char_uuid_outbound         = CUST1_OUTBOUND_UUID_128,
    .char_uuid_flow_ctrl        = CUST1_FLOW_CONTROL_UUID_128,
    .dsps_service_uuid          = custs1_sps_svc,
    #ifdef USE_AT_BINARY_MODE
    .dsps_char_uuid_rx          = CUST1_SPS_RX_UUID_128,
    .dsps_char_uuid_tx          = CUST1_SPS_TX_UUID_128,
    .dsps_char_uuid_flow_ctrl   = CUST1_SPS_FLOW_CONTROL_UUID_128,
    #endif
};

extern struct codeless_env_t codeless_env;

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

#endif //_USER_CODELESS_ENV_H_

/// @} APP
