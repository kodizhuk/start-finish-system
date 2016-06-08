/*******************************************************************************
* File Name: uatr_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_uatr_H)
#define CY_SCB_SPI_UART_PVT_uatr_H

#include "uatr_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (uatr_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  uatr_rxBufferHead;
    extern volatile uint32  uatr_rxBufferTail;
    extern volatile uint8   uatr_rxBufferOverflow;
#endif /* (uatr_INTERNAL_RX_SW_BUFFER_CONST) */

#if (uatr_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  uatr_txBufferHead;
    extern volatile uint32  uatr_txBufferTail;
#endif /* (uatr_INTERNAL_TX_SW_BUFFER_CONST) */

#if (uatr_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 uatr_rxBufferInternal[uatr_INTERNAL_RX_BUFFER_SIZE];
#endif /* (uatr_INTERNAL_RX_SW_BUFFER) */

#if (uatr_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 uatr_txBufferInternal[uatr_TX_BUFFER_SIZE];
#endif /* (uatr_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void uatr_SpiPostEnable(void);
void uatr_SpiStop(void);

#if (uatr_SCB_MODE_SPI_CONST_CFG)
    void uatr_SpiInit(void);
#endif /* (uatr_SCB_MODE_SPI_CONST_CFG) */

#if (uatr_SPI_WAKE_ENABLE_CONST)
    void uatr_SpiSaveConfig(void);
    void uatr_SpiRestoreConfig(void);
#endif /* (uatr_SPI_WAKE_ENABLE_CONST) */

void uatr_UartPostEnable(void);
void uatr_UartStop(void);

#if (uatr_SCB_MODE_UART_CONST_CFG)
    void uatr_UartInit(void);
#endif /* (uatr_SCB_MODE_UART_CONST_CFG) */

#if (uatr_UART_WAKE_ENABLE_CONST)
    void uatr_UartSaveConfig(void);
    void uatr_UartRestoreConfig(void);
#endif /* (uatr_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in uatr_SetPins() */
#define uatr_UART_RX_PIN_ENABLE    (uatr_UART_RX)
#define uatr_UART_TX_PIN_ENABLE    (uatr_UART_TX)

/* UART RTS and CTS position to be used in  uatr_SetPins() */
#define uatr_UART_RTS_PIN_ENABLE    (0x10u)
#define uatr_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define uatr_SpiUartEnableIntRx(intSourceMask)  uatr_SetRxInterruptMode(intSourceMask)
#define uatr_SpiUartEnableIntTx(intSourceMask)  uatr_SetTxInterruptMode(intSourceMask)
uint32  uatr_SpiUartDisableIntRx(void);
uint32  uatr_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_uatr_H) */


/* [] END OF FILE */
