/*
 * battery.h
 *
 *  Created on: Aug 22, 2025
 *      Author: joakimwennergren
 */

#ifndef INC_BATTERY_H_
#define INC_BATTERY_H_

#include "main.h"

// MAX17048/MAX17049 7-bit I2C address is 0x36.
// STM32 HAL expects the address left-shifted by 1 bit.
#define MAX17048_I2C_ADDR   (0x36 << 1)
#define REG_SOC             0x04
#define REG_VCELL           0x02

// Reads SOC as a float percentage (e.g., 76.5f for 76.5%)
HAL_StatusTypeDef MAX1704x_ReadSOC(float *soc_out);

HAL_StatusTypeDef MAX1704x_ReadVoltage(float *voltage_out);



#endif /* INC_BATTERY_H_ */
