/* ========================================
 *
 * File Name: SPI.h
 * Version 1.20 
 * Copyright ANDREY TKACHOV, 2016
  
 * Descriprion: 
 *  This file provides constants and parameter values 
 *  for the Software Serial Programming Interface Component.

 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF PERSONAL LICENSE.
 *
 * ========================================
*/

#ifndef CY_SW_SPI_SPI_H
#define CY_SW_SPI_SPI_H
        
#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"

/* Nop ASM implementation*/
#define nop() \
            asm("mov r0,r0")

/***************************************
*        Function Prototypes
***************************************/

void SPI_Start(void) ;    
void SPI_Stop(void) ;
void SPI_Init(void) ;
void SPI_ChipSelect(void) ;
void SPI_ChipDeselect(void) ;
void SPI_SendBuff(const uint8 buff[], uint16 cnt) ;
void SPI_SendByte(uint8 byte) ;
uint8 SPI_ReadAndWriteByte(uint8 byte) ;
void SPI_RecvBuff(uint8 *buff, uint16 cnt) ;
uint8 SPI_RecvByte(void) ;

#endif /* CY_SW_SPI_SPI_H */
    
    
/* [] END OF FILE */
