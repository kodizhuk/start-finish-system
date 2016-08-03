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

#include "CS_SPI.h"
#include "CLK_SPI.h"
#include "MOSI_SPI.h"   
#include "MISO_SPI.h"   
#include <CyLib.h>

void SPI_Init(void);
// Low transmitt functions
void ChipSelect();
void ChipDeselect();

void SPI_SendBuff(uint8_t* buff, uint8_t cnt);
void SPI_SendByte(uint8_t byte);
void SPI_RecvBuff(uint8_t* buff, uint8_t cnt);
uint8_t SPI_RecvByte(void);

#define nop() \
            asm("mov r0,r0")

/* [] END OF FILE */
