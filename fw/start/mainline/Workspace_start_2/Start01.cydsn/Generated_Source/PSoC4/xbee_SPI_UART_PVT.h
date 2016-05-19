/*******************************************************************************
* File Name: xbee_SPI_UART_PVT.h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_xbee_H)
#define CY_SCB_SPI_UART_PVT_xbee_H

#include "xbee_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (xbee_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  xbee_rxBufferHead;
    extern volatile uint32  xbee_rxBufferTail;
    extern volatile uint8   xbee_rxBufferOverflow;
#endif /* (xbee_INTERNAL_RX_SW_BUFFER_CONST) */

#if (xbee_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  xbee_txBufferHead;
    extern volatile uint32  xbee_txBufferTail;
#endif /* (xbee_INTERNAL_TX_SW_BUFFER_CONST) */

#if (xbee_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 xbee_rxBufferInternal[xbee_INTERNAL_RX_BUFFER_SIZE];
#endif /* (xbee_INTERNAL_RX_SW_BUFFER) */

#if (xbee_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 xbee_txBufferInternal[xbee_TX_BUFFER_SIZE];
#endif /* (xbee_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void xbee_SpiPostEnable(void);
void xbee_SpiStop(void);

#if (xbee_SCB_MODE_SPI_CONST_CFG)
    void xbee_SpiInit(void);
#endif /* (xbee_SCB_MODE_SPI_CONST_CFG) */

#if (xbee_SPI_WAKE_ENABLE_CONST)
    void xbee_SpiSaveConfig(void);
    void xbee_SpiRestoreConfig(void);
#endif /* (xbee_SPI_WAKE_ENABLE_CONST) */

void xbee_UartPostEnable(void);
void xbee_UartStop(void);

#if (xbee_SCB_MODE_UART_CONST_CFG)
    void xbee_UartInit(void);
#endif /* (xbee_SCB_MODE_UART_CONST_CFG) */

#if (xbee_UART_WAKE_ENABLE_CONST)
    void xbee_UartSaveConfig(void);
    void xbee_UartRestoreConfig(void);
#endif /* (xbee_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in xbee_SetPins() */
#define xbee_UART_RX_PIN_ENABLE    (xbee_UART_RX)
#define xbee_UART_TX_PIN_ENABLE    (xbee_UART_TX)

/* UART RTS and CTS position to be used in  xbee_SetPins() */
#define xbee_UART_RTS_PIN_ENABLE    (0x10u)
#define xbee_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define xbee_SpiUartEnableIntRx(intSourceMask)  xbee_SetRxInterruptMode(intSourceMask)
#define xbee_SpiUartEnableIntTx(intSourceMask)  xbee_SetTxInterruptMode(intSourceMask)
uint32  xbee_SpiUartDisableIntRx(void);
uint32  xbee_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_xbee_H) */


/* [] END OF FILE */
