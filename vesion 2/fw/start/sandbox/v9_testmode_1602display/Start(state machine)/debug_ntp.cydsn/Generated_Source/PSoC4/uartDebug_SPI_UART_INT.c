/***************************************************************************//**
* \file uartDebug_SPI_UART_INT.c
* \version 3.20
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "uartDebug_PVT.h"
#include "uartDebug_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (uartDebug_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: uartDebug_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(uartDebug_SPI_UART_ISR)
{
#if (uartDebug_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (uartDebug_INTERNAL_RX_SW_BUFFER_CONST) */

#if (uartDebug_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (uartDebug_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef uartDebug_SPI_UART_ISR_ENTRY_CALLBACK
    uartDebug_SPI_UART_ISR_EntryCallback();
#endif /* uartDebug_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != uartDebug_customIntrHandler)
    {
        uartDebug_customIntrHandler();
    }

    #if(uartDebug_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        uartDebug_ClearSpiExtClkInterruptSource(uartDebug_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (uartDebug_CHECK_RX_SW_BUFFER)
    {
        if (uartDebug_CHECK_INTR_RX_MASKED(uartDebug_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (uartDebug_rxBufferHead + 1u);

                /* Adjust local head index */
                if (uartDebug_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == uartDebug_rxBufferTail)
                {
                    #if (uartDebug_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        uartDebug_INTR_RX_MASK_REG &= ~uartDebug_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) uartDebug_RX_FIFO_RD_REG;
                        uartDebug_rxBufferOverflow = (uint8) uartDebug_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    uartDebug_PutWordInRxBuffer(locHead, uartDebug_RX_FIFO_RD_REG);

                    /* Move head index */
                    uartDebug_rxBufferHead = locHead;
                }
            }
            while(0u != uartDebug_GET_RX_FIFO_ENTRIES);

            uartDebug_ClearRxInterruptSource(uartDebug_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (uartDebug_CHECK_TX_SW_BUFFER)
    {
        if (uartDebug_CHECK_INTR_TX_MASKED(uartDebug_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (uartDebug_txBufferHead != uartDebug_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (uartDebug_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (uartDebug_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    uartDebug_TX_FIFO_WR_REG = uartDebug_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    uartDebug_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    uartDebug_DISABLE_INTR_TX(uartDebug_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (uartDebug_SPI_UART_FIFO_SIZE != uartDebug_GET_TX_FIFO_ENTRIES);

            uartDebug_ClearTxInterruptSource(uartDebug_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef uartDebug_SPI_UART_ISR_EXIT_CALLBACK
    uartDebug_SPI_UART_ISR_ExitCallback();
#endif /* uartDebug_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (uartDebug_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
