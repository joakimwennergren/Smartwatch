/*
 * battery.c
 *
 *  Created on: Aug 22, 2025
 *      Author: joakimwennergren
 */
#include "battery.h"

HAL_StatusTypeDef MAX1704x_ReadSOC(float *soc_out)
{
    uint8_t buf[2] = {0};

    // Read 2 bytes from register 0x04 in one transaction (required by the IC)
    HAL_StatusTypeDef st = HAL_I2C_Mem_Read(
        &hi2c1,
		MAX17048_I2C_ADDR,
        REG_SOC,
        I2C_MEMADD_SIZE_8BIT,
        buf,
        sizeof(buf),
        100 /* timeout ms */
    );
    if (st != HAL_OK) return st;

    // Datasheet: 16-bit word, MSB first. Units are 1/256 % per LSB.
    uint16_t raw = ((uint16_t)buf[0] << 8) | buf[1];
    *soc_out = ((float)raw) / 256.0f;

    return HAL_OK;
}



HAL_StatusTypeDef MAX1704x_ReadVoltage(float *voltage_out) {
    uint8_t buf[2] = {0};

    HAL_StatusTypeDef st = HAL_I2C_Mem_Read(
        &hi2c1,
		MAX17048_I2C_ADDR,
        REG_VCELL,
        I2C_MEMADD_SIZE_8BIT,
        buf,
        sizeof(buf),
        100
    );
    if (st != HAL_OK) return st;

    uint16_t raw = ((uint16_t)buf[0] << 8) | buf[1];

    // Datasheet: LSB = 78.125 µV
    *voltage_out = ((float)raw) * 78.125e-6f;

    return HAL_OK;
}
