/*
 * display.hpp
 *
 *  Created on: Aug 10, 2025
 *      Author: Joakim Wennergren
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"

// CST820 Touch IC 7-bit I2C address (shifted left by 1 for HAL)
// Register 	Address	Name			Description
// --------     ------------            ------------------------------------------------------
// 0x00			Device ID				Returns device ID or chip version
// 0x01			Gesture Status			Shows gesture events detected
// 0x02			Touch Status			Indicates which electrodes are touched
// 0x03			Sensor Data				Raw or processed sensor data
// 0x04			Control Register		Control bits for enabling/disabling touch, reset, etc.
// 0x05			Interrupt Status		Interrupt flags
// 0x06 - 0x0F	Calibration / Config	Calibration values and configuration parameters
#define CST820_I2C_ADDR  (0x15 << 1)

// Panel geometry / pixel format (RGB565 => 2 bytes per pixel)
#define PANEL_WIDTH          368
#define PANEL_HEIGHT         448
#define PIXEL_BYTES          2
#define FRAMEBUFFER_SIZE     (PANEL_WIDTH * PANEL_HEIGHT * PIXEL_BYTES)

// --- Low-level QSPI write command helper (1-line command/address/data) ---
// This sends instruction=0x02 with 24-bit address (0x00 CMD 0x00) and then data bytes.
HAL_StatusTypeDef CO5300_QSPI_WriteCmd(OSPI_HandleTypeDef hospi, uint8_t cmd, const uint8_t *params, uint32_t param_len);

// --- Send the supplier init sequence
HAL_StatusTypeDef CO5300_SendInitSequence(OSPI_HandleTypeDef hospi);

// --- Enter memory-mapped mode for pixel writes (4-line data) ---
HAL_StatusTypeDef CO5300_EnterMemoryMapped(OSPI_HandleTypeDef hospi);

// @TODO enter/exit sleep

/**
 * @brief External declaration of the frame buffer used for display rendering.
 *
 * This buffer holds the pixel data for the display. The size of the buffer is defined
 * by FRAMEBUFFER_SIZE, which should be set according to the display's resolution and color depth.
 *
 * @note The actual definition and initialization of this buffer should be provided in the corresponding source file.
 */
extern uint8_t frame_buffer[FRAMEBUFFER_SIZE];

#endif /* INC_DISPLAY_H_ */
