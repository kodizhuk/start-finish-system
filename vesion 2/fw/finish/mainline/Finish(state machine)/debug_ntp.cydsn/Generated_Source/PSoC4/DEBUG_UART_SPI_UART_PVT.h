/***************************************************************************//**
* \file DEBUG_UART_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_DEBUG_UART_H)
#define CY_SCB_SPI_UART_PVT_DEBUG_UART_H

#include "DEBUG_UART_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (DEBUG_UART_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  DEBUG_UART_rxBufferHead;
    extern volatile uint32  DEBUG_UART_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   DEBUG_UART_rxBufferOverflow;
    /** @} globals */
#endif /* (DEBUG_UART_INTERNAL_RX_SW_BUFFER_CONST) */

#if (DEBUG_UART_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  DEBUG_UART_txBufferHead;
    extern volatile uint32  DEBUG_UART_txBufferTail;
#endif /* (DEBUG_UART_INTERNAL_TX_SW_BUFFER_CONST) */

#if (DEBUG_UART_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 DEBUG_UART_rxBufferInternal[DEBUG_UART_INTERNAL_RX_BUFFER_SIZE];
#endif /* (DEBUG_UART_INTERNAL_RX_SW_BUFFER) */

#if (DEBUG_UART_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 DEBUG_UART_txBufferInternal[DEBUG_UART_TX_BUFFER_SIZE];
#endif /* (DEBUG_UART_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void DEBUG_UART_SpiPostEnable(void);
void DEBUG_UART_SpiStop(void);

#if (DEBUG_UART_SCB_MODE_SPI_CONST_CFG)
    void DEBUG_UART_SpiInit(void);
#endif /* (DEBUG_UART_SCB_MODE_SPI_CONST_CFG) */

#if (DEBUG_UART_SPI_WAKE_ENABLE_CONST)
    void DEBUG_UART_SpiSaveConfig(void);
    void DEBUG_UART_SpiRestoreConfig(void);
#endif /* (DEBUG_UART_SPI_WAKE_ENABLE_CONST) */

void DEBUG_UART_UartPostEnable(void);
void DEBUG_UART_UartStop(void);

#if (DEBUG_UART_SCB_MODE_UART_CONST_CFG)
    void DEBUG_UART_UartInit(void);
#endif /* (DEBUG_UART_SCB_MODE_UART_CONST_CFG) */

#if (DEBUG_UART_UART_WAKE_ENABLE_CONST)
    void DEBUG_UART_UartSaveConfig(void);
    void DEBUG_UART_UartRestoreConfig(void);
#endif /* (DEBUG_UART_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in DEBUG_UART_SetPins() */
#define DEBUG_UART_UART_RX_PIN_ENABLE    (DEBUG_UART_UART_RX)
#define DEBUG_UART_UART_TX_PIN_ENABLE    (DEBUG_UART_UART_TX)

/* UART RTS and CTS position to be used in  DEBUG_UART_SetPins() */
#define DEBUG_UART_UART_RTS_PIN_ENABLE    (0x10u)
#define DEBUG_UART_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define DEBUG_UART_SpiUartEnableIntRx(intSourceMask)  DEBUG_UART_SetRxInterruptMode(intSourceMask)
#define DEBUG_UART_SpiUartEnableIntTx(intSourceMask)  DEBUG_UART_SetTxInterruptMode(intSourceMask)
uint32  DEBUG_UART_SpiUartDisableIntRx(void);
uint32  DEBUG_UART_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_DEBUG_UART_H) */


/* [] END OF FILE */
