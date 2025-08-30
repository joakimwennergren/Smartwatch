/*
 * display.hpp
 *
 *  Created on: Aug 10, 2025
 *      Author: Joakim Wennergren
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"
#include "util.h"

// CST820 7-bit I2C address (shifted left by 1 for HAL)
#define CST820_I2C_ADDR  		(0x15 << 1)

// Touch point data register
#define CST820_TP_DATA_REG   	(0x21)

// TP and DISP reset delay
#define RST_DELAY				(32)

// safe per DMA block
#define OSPI_DMA_MAX_BYTES    	(65532u)

// Panel geometry / pixel format (RGB565 => 1 bytes per pixel)
#define PANEL_WIDTH          	(368 + 16)
#define PANEL_HEIGHT         	(448)
#define PIXEL_BYTES          	(1)
#define FRAMEBUFFER_SIZE     	(PANEL_WIDTH * PANEL_HEIGHT * PIXEL_BYTES)

/**
 * @brief Structure to hold touch data from the CST820 touch controller.
 *
 * This structure contains information about the number of touch points detected
 * and the coordinates of up to two touch points.
 *
 * @param touch_count Number of touch points detected (e.g., 1 or 2).
 * @param x1 X coordinate of the first touch point.
 * @param y1 Y coordinate of the first touch point.
 * @param x2 X coordinate of the second touch point (if present).
 * @param y2 Y coordinate of the second touch point (if present).
 */
typedef struct {
    uint8_t touch_count;
    uint16_t x1, y1;
    uint16_t x2, y2;
} CST820_TouchData;

extern HAL_DMA_CallbackIDTypeDef dma_callback_id;

/**
 * @brief  Callback function called when the OSPI (OctoSPI) transmit operation is complete.
 * @param  h: Pointer to an OSPI_HandleTypeDef structure that contains
 *         the configuration information for the specified OSPI module.
 * @note   This function should be implemented by the user to handle post-transmission processing.
 */
void hal_qspi_transfer_complete_cb(OSPI_HandleTypeDef *h);

/**
 * @brief Resets the display to its default state.
 *
 * This function performs any necessary operations to clear or reinitialize
 * the display hardware or software state, preparing it for fresh use.
 */
void reset_display(void);

/**
 * @brief Resets the touch controller hardware.
 *
 * This function performs a hardware reset of the touch controller,
 * reinitializing its state and ensuring it is ready for operation.
 * It may be used to recover from errors or to reinitialize the controller
 * during system startup or after a firmware update.
 */
void reset_touchcontroller(void);

/**
 * @brief Sends a command along with optional parameters to the CO5300 display via QSPI.
 *
 * This function transmits a command byte and an optional array of parameter bytes to the CO5300 display
 * using the QSPI interface. It is typically used to configure or control the display by sending specific
 * commands defined in the display's datasheet.
 *
 * @param cmd        The command byte to send to the display.
 * @param params     Pointer to an array of parameter bytes to send after the command. Can be NULL if no parameters.
 * @param param_len  The number of parameter bytes to send. Set to 0 if no parameters.
 * @return HAL status code indicating the result of the operation (e.g., HAL_OK on success).
 */
HAL_StatusTypeDef co5300_qspi_write_cmd(uint8_t cmd, const uint8_t *params, uint32_t param_len);

/**
 * @brief Sends the initialization sequence to the CO5300 display.
 *
 * This function transmits the required commands to initialize the CO5300 display module.
 * It should be called before any other operations are performed on the display.
 *
 * @retval HAL_OK      Initialization sequence sent successfully.
 * @retval HAL_ERROR   An error occurred while sending the sequence.
 * @retval HAL_BUSY    The HAL is busy and cannot process the request.
 * @retval HAL_TIMEOUT The operation timed out.
 */
HAL_StatusTypeDef co5300_send_init_sequence();

/**
 * @brief Enters the Quad mode for the CO5300 QSPI device.
 *
 * This function configures the CO5300 QSPI device to operate in Quad mode,
 * enabling four data lines for faster data transfer.
 *
 * @retval HAL_OK      Operation completed successfully.
 * @retval HAL_ERROR   An error occurred while entering Quad mode.
 * @retval HAL_BUSY    The QSPI peripheral is currently busy.
 * @retval HAL_TIMEOUT The operation timed out.
 */
HAL_StatusTypeDef co5300_qspi_enter_quad_mode();

/**
 * @brief Enters single mode operation for the CO5300 QSPI display.
 *
 * This function configures the QSPI interface to operate in single mode,
 * which may be required for certain display operations or commands.
 *
 * @retval HAL_OK      Operation was successful.
 * @retval HAL_ERROR   Operation failed.
 * @retval HAL_BUSY    QSPI is currently busy.
 * @retval HAL_TIMEOUT Operation timed out.
 */
HAL_StatusTypeDef co5300_qspi_enter_single_mode();

/**
 * @brief Writes a buffer of pixel data to the CO5300 display.
 *
 * This function sends a buffer of pixel data to the CO5300 display controller
 * via GPDMA channel 2. The number of bytes to write is specified
 * by the num_bytes parameter.
 *
 * @param pixels     Pointer to the buffer containing the pixel data to be written.
 * @param num_bytes  Number of bytes in the pixel data buffer to write.
 * @return HAL status code indicating the result of the operation.
 *         - HAL_OK: Operation successful.
 *         - HAL_ERROR: Operation failed.
 *         - HAL_BUSY: Peripheral is busy.
 *         - HAL_TIMEOUT: Operation timed out.
 */
HAL_StatusTypeDef co5300_write_pixels_dma_chunked(const uint8_t *pixels, uint32_t len);

/**
 * @brief Sets the active drawing window on the CO5300 display.
 *
 * This function defines a rectangular area (window) on the display where subsequent
 * pixel data will be written. The window is specified by its top-left (x0, y0) and
 * bottom-right (x1, y1) coordinates.
 *
 * @param x0 The X coordinate of the top-left corner of the window.
 * @param y0 The Y coordinate of the top-left corner of the window.
 * @param x1 The X coordinate of the bottom-right corner of the window.
 * @param y1 The Y coordinate of the bottom-right corner of the window.
 * @return HAL status indicating success or error code.
 */
HAL_StatusTypeDef co5300_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

/**
 * @brief Writes pixel data to the CO5300 display in 4-line mode.
 *
 * This function sends a buffer of pixel data to the CO5300 display controller,
 * writing up to four lines of pixels at a time. The pixel data should be formatted
 * according to the display's requirements.
 *
 * @param pixels Pointer to the buffer containing the pixel data to be written.
 * @param len    Length of the pixel data buffer in bytes.
 * @return HAL_StatusTypeDef HAL_OK if successful, or an appropriate HAL error code.
 */
//HAL_StatusTypeDef CO5300_WritePixels_4line(const uint8_t *pixels, uint32_t len);

/**
 * @brief Reads touch data from the CST820 touch controller.
 *
 * This function retrieves the current touch data and stores it in the provided
 * CST820_TouchData structure.
 *
 * @param[out] touch Pointer to a CST820_TouchData structure where the touch data will be stored.
 * @retval HAL_OK      Operation completed successfully.
 * @retval HAL_ERROR   An error occurred during the read operation.
 * @retval HAL_BUSY    The device is currently busy.
 * @retval HAL_TIMEOUT The operation timed out.
 */
HAL_StatusTypeDef cst820_read_touch(CST820_TouchData *touch);

#endif /* INC_DISPLAY_H_ */
