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

//#include "CommonPrototypes.h"
#include "lib_Network\crc32.h"

#define         CRC32_POLYNOM        0xEDB88320L

static int      crc32_tab_init       = 0;//= FALSE;
static uint32_t    crc32_tab[256];

static void     crc32_init_tab( void );

uint32_t crc32_update( uint32_t crc, uint8_t c ) {

    uint32_t tmp, long_c;

    long_c = 0x000000ffL & (unsigned long) c;

    if ( ! crc32_tab_init ) crc32_init_tab();

    tmp = crc ^ long_c;
    crc = (crc >> 8) ^ crc32_tab[ tmp & 0xff ];

    return crc;

}

uint32_t crc32_calc_block(uint8_t *buf, uint32_t Size, uint32_t init)
{
	uint32_t i;
	uint32_t _crc = init;
	for (i = 0; i < Size; i++)
		_crc = crc32_update(_crc, buf[i]);

	return _crc;
}

uint32_t crc32_calc(uint8_t *buf, uint32_t Size)
{
	uint32_t _crc;

	_crc = crc32_reset();
	_crc = crc32_calc_block(buf, Size, _crc);
	return crc32_final(_crc);
}

static void crc32_init_tab( void ) {

    int i, j;
    uint32_t crc;

    for (i=0; i<256; i++) {

        crc = (uint32_t) i;

        for (j=0; j<8; j++) {

            if ( crc & 0x00000001L ) crc = ( crc >> 1 ) ^ CRC32_POLYNOM;
            else                     crc =   crc >> 1;
        }

        crc32_tab[i] = crc;
    }

    crc32_tab_init = 1;

}

/* [] END OF FILE */
