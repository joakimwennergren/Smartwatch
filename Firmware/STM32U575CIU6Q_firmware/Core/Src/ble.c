/*
 * ble.c
 *
 *  Created on: Aug 10, 2025
 *      Author: Joakim Wennergren
 */

/* Called for each received byte (in main context) */
static void process_rx_byte(uint8_t b) {
  /* Example: echo received byte back (non-blocking) */
  /* Wait if previous TX still busy (or implement TX queue) */
  while (tx_busy) { /* simple spin-wait; replace with queue in real app */ }

  tx_busy = 1;
  HAL_UART_Transmit_IT(&huart1, &b, 1);
}

/* ---------------- HAL callbacks -------------------- */

/* Called by HAL when a receive completes (1 byte in this example) */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART1)
  {
    /* push byte into ring buffer (ISR context -> use volatile indexes) */
    uint16_t next = (rx_head + 1);
    if (next >= RX_BUF_SIZE) next = 0;

    /* if buffer full, drop oldest or new byte (here we drop new byte) */
    if (next != rx_tail)
    {
      rx_ring[rx_head] = rx_byte;
      rx_head = next;
    }
    /* restart reception for next byte */
    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
  }
}

/* Called by HAL when a transmit completes */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART1)
  {
    tx_busy = 0;
  }
}

/* Optional: error callback */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART1)
  {
    /* handle framing/overrun errors - for example, restart RX */
    __NOP();
    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
  }
}

/* LVGL tick source */
void uart_poll(void* argument) {
  for(;;)
  {
    lv_tick_inc(10);
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void create_uart_poll_task(void) {
    xTaskCreate(
    	uart_poll,
        "uart_poll",
        256,
        NULL,
        tskIDLE_PRIORITY + 1,
        &uart_poll_handle_g
    );
}

/* ---------------- IRQ Handler -------------------- */

/* Make sure your vector table maps USART1_IRQn to this handler (CubeMX does). */
void USART1_IRQHandler(void) {
  HAL_UART_IRQHandler(&huart1);
}


