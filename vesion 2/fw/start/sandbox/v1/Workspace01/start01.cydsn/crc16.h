/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef _CRC16_H_
#define _CRC16_H_

#include <stdint.h>

#define CRC16_INIT			0

uint16_t crc16_update(uint16_t crc, uint8_t a);
uint16_t crc16_calc(uint8_t *buf, uint32_t Size, uint16_t init);

#endif

/* [] END OF FILE */
