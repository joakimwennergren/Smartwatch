/*
 * util.c
 *
 *  Created on: Aug 29, 2025
 *      Author: joakim-wennergren
 */
#include "util.h"

void delay_us(uint32_t us) {
    uint32_t start = TIM16->CNT;
    while ((uint32_t)(TIM16->CNT - start) < us) {
        /* spin */
    }
}

