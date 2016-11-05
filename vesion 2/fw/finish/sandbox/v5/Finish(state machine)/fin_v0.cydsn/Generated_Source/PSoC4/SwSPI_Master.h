/* ========================================
 *
 * File Name: SwSPI_Master.h
 * Version 1.10 
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

#ifndef CY_SW_SPI_SwSPI_Master_H
#define CY_SW_SPI_SwSPI_Master_H
        
#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"

/* Nop ASM implementation*/
#define nop() \
            asm("mov r0,r0")

/***************************************
*        Function Prototypes
***************************************/

void SwSPI_Master_Start(void) ;    
void SwSPI_Master_Stop(void) ;
void SwSPI_Master_Init(void) ;
void SwSPI_Master_ChipSelect(void) ;
void SwSPI_Master_ChipDeselect(void) ;
void SwSPI_Master_SendBuff(const uint8 buff[], uint16 cnt) ;
void SwSPI_Master_SendByte(uint8 byte) ;
uint8 SwSPI_Master_ReadAndWriteByte(uint8 byte) ;
void SwSPI_Master_RecvBuff(uint8 *buff, uint16 cnt) ;
uint8 SwSPI_Master_RecvByte(void) ;

#endif /* CY_SW_SPI_SwSPI_Master_H */
    
    
/* [] END OF FILE */
