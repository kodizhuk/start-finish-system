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
#ifndef _CRC32_H_
#define _CRC32_H_

#include <stdint.h>

#define CRC32_INIT			0xFFFFFFFFL

#define crc32_reset(...)	(CRC32_INIT)
#define crc32_final(crc)	(crc ^ CRC32_INIT)

uint32_t crc32_update(uint32_t crc, uint8_t c);
uint32_t crc32_calc_block(uint8_t *buf, uint32_t Size, uint32_t init);

uint32_t crc32_calc(uint8_t *buf, uint32_t Size);

#endif

/* [] END OF FILE */
