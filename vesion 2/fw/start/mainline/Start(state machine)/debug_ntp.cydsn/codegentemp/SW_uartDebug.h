/*******************************************************************************
* File Name: SW_uartDebug.h
* Version 1.50
*
* Description:
*  This file provides constants and parameter values for the Software Transmit
*  UART Component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_SW_TX_UART_SW_uartDebug_H
#define CY_SW_TX_UART_SW_uartDebug_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"

#define SW_uartDebug_BAUD_RATE                      (9600u)
#define SW_uartDebug_PIN_STATIC_MODE                (1u)


/***************************************
*        Function Prototypes
***************************************/
#if(SW_uartDebug_PIN_STATIC_MODE == 1u)
    void SW_uartDebug_Start(void) ;
#else
    void SW_uartDebug_StartEx(uint8 port, uint8 pin) ;
#endif /* (SW_uartDebug_PIN_STATIC_MODE == 1u) */

void SW_uartDebug_Stop(void) ;
void SW_uartDebug_PutChar(uint8 txDataByte) ;
void SW_uartDebug_PutString(const char8 string[]) ;
void SW_uartDebug_PutArray(const uint8 array[], uint32 byteCount) ;
void SW_uartDebug_PutHexByte(uint8 txHexByte) ;
void SW_uartDebug_PutHexInt(uint16 txHexInt) ;
void SW_uartDebug_PutCRLF(void) ;

#endif /* CY_SW_TX_UART_SW_uartDebug_H */


/* [] END OF FILE */
