/***************************************************************************//**
* \file UART_DEBUG_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_UART_DEBUG_H)
#define CY_SCB_SPI_UART_PVT_UART_DEBUG_H

#include "UART_DEBUG_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (UART_DEBUG_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART_DEBUG_rxBufferHead;
    extern volatile uint32  UART_DEBUG_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   UART_DEBUG_rxBufferOverflow;
    /** @} globals */
#endif /* (UART_DEBUG_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART_DEBUG_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART_DEBUG_txBufferHead;
    extern volatile uint32  UART_DEBUG_txBufferTail;
#endif /* (UART_DEBUG_INTERNAL_TX_SW_BUFFER_CONST) */

#if (UART_DEBUG_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART_DEBUG_rxBufferInternal[UART_DEBUG_INTERNAL_RX_BUFFER_SIZE];
#endif /* (UART_DEBUG_INTERNAL_RX_SW_BUFFER) */

#if (UART_DEBUG_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART_DEBUG_txBufferInternal[UART_DEBUG_TX_BUFFER_SIZE];
#endif /* (UART_DEBUG_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void UART_DEBUG_SpiPostEnable(void);
void UART_DEBUG_SpiStop(void);

#if (UART_DEBUG_SCB_MODE_SPI_CONST_CFG)
    void UART_DEBUG_SpiInit(void);
#endif /* (UART_DEBUG_SCB_MODE_SPI_CONST_CFG) */

#if (UART_DEBUG_SPI_WAKE_ENABLE_CONST)
    void UART_DEBUG_SpiSaveConfig(void);
    void UART_DEBUG_SpiRestoreConfig(void);
#endif /* (UART_DEBUG_SPI_WAKE_ENABLE_CONST) */

void UART_DEBUG_UartPostEnable(void);
void UART_DEBUG_UartStop(void);

#if (UART_DEBUG_SCB_MODE_UART_CONST_CFG)
    void UART_DEBUG_UartInit(void);
#endif /* (UART_DEBUG_SCB_MODE_UART_CONST_CFG) */

#if (UART_DEBUG_UART_WAKE_ENABLE_CONST)
    void UART_DEBUG_UartSaveConfig(void);
    void UART_DEBUG_UartRestoreConfig(void);
#endif /* (UART_DEBUG_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART_DEBUG_SetPins() */
#define UART_DEBUG_UART_RX_PIN_ENABLE    (UART_DEBUG_UART_RX)
#define UART_DEBUG_UART_TX_PIN_ENABLE    (UART_DEBUG_UART_TX)

/* UART RTS and CTS position to be used in  UART_DEBUG_SetPins() */
#define UART_DEBUG_UART_RTS_PIN_ENABLE    (0x10u)
#define UART_DEBUG_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define UART_DEBUG_SpiUartEnableIntRx(intSourceMask)  UART_DEBUG_SetRxInterruptMode(intSourceMask)
#define UART_DEBUG_SpiUartEnableIntTx(intSourceMask)  UART_DEBUG_SetTxInterruptMode(intSourceMask)
uint32  UART_DEBUG_SpiUartDisableIntRx(void);
uint32  UART_DEBUG_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_UART_DEBUG_H) */


/* [] END OF FILE */
