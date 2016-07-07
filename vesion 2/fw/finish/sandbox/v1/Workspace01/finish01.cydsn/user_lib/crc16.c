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
#include "crc16.h"

#define CRC16_POLYNOM	0xA001

uint16_t crc16_update(uint16_t crc, uint8_t a)
{
	int i;
	crc ^= a;
	for (i = 0; i < 8; ++i)
	{
		if (crc & 1)
			crc = (crc >> 1) ^ CRC16_POLYNOM;
		else
			crc = (crc >> 1);
	}
	return crc;
}

uint16_t crc16_calc(uint8_t *buf, uint32_t Size, uint16_t init)
{
	uint32_t i;
	uint16_t _crc = init;
	for (i = 0; i < Size; i++)
		_crc = crc16_update(_crc, buf[i]);
	return _crc;
}

/* [] END OF FILE */
