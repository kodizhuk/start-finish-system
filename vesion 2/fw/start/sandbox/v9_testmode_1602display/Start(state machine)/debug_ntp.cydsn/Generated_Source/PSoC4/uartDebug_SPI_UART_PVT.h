/***************************************************************************//**
* \file uartDebug_SPI_UART_PVT.h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_uartDebug_H)
#define CY_SCB_SPI_UART_PVT_uartDebug_H

#include "uartDebug_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (uartDebug_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  uartDebug_rxBufferHead;
    extern volatile uint32  uartDebug_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   uartDebug_rxBufferOverflow;
    /** @} globals */
#endif /* (uartDebug_INTERNAL_RX_SW_BUFFER_CONST) */

#if (uartDebug_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  uartDebug_txBufferHead;
    extern volatile uint32  uartDebug_txBufferTail;
#endif /* (uartDebug_INTERNAL_TX_SW_BUFFER_CONST) */

#if (uartDebug_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 uartDebug_rxBufferInternal[uartDebug_INTERNAL_RX_BUFFER_SIZE];
#endif /* (uartDebug_INTERNAL_RX_SW_BUFFER) */

#if (uartDebug_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 uartDebug_txBufferInternal[uartDebug_TX_BUFFER_SIZE];
#endif /* (uartDebug_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void uartDebug_SpiPostEnable(void);
void uartDebug_SpiStop(void);

#if (uartDebug_SCB_MODE_SPI_CONST_CFG)
    void uartDebug_SpiInit(void);
#endif /* (uartDebug_SCB_MODE_SPI_CONST_CFG) */

#if (uartDebug_SPI_WAKE_ENABLE_CONST)
    void uartDebug_SpiSaveConfig(void);
    void uartDebug_SpiRestoreConfig(void);
#endif /* (uartDebug_SPI_WAKE_ENABLE_CONST) */

void uartDebug_UartPostEnable(void);
void uartDebug_UartStop(void);

#if (uartDebug_SCB_MODE_UART_CONST_CFG)
    void uartDebug_UartInit(void);
#endif /* (uartDebug_SCB_MODE_UART_CONST_CFG) */

#if (uartDebug_UART_WAKE_ENABLE_CONST)
    void uartDebug_UartSaveConfig(void);
    void uartDebug_UartRestoreConfig(void);
#endif /* (uartDebug_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in uartDebug_SetPins() */
#define uartDebug_UART_RX_PIN_ENABLE    (uartDebug_UART_RX)
#define uartDebug_UART_TX_PIN_ENABLE    (uartDebug_UART_TX)

/* UART RTS and CTS position to be used in  uartDebug_SetPins() */
#define uartDebug_UART_RTS_PIN_ENABLE    (0x10u)
#define uartDebug_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define uartDebug_SpiUartEnableIntRx(intSourceMask)  uartDebug_SetRxInterruptMode(intSourceMask)
#define uartDebug_SpiUartEnableIntTx(intSourceMask)  uartDebug_SetTxInterruptMode(intSourceMask)
uint32  uartDebug_SpiUartDisableIntRx(void);
uint32  uartDebug_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_uartDebug_H) */


/* [] END OF FILE */
