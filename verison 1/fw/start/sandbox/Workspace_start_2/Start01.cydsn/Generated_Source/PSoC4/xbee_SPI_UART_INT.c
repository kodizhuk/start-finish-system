/*******************************************************************************
* File Name: xbee_SPI_UART_INT.c
* Version 3.10
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "xbee_PVT.h"
#include "xbee_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (xbee_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: xbee_SPI_UART_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(xbee_SPI_UART_ISR)
{
#if (xbee_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (xbee_INTERNAL_RX_SW_BUFFER_CONST) */

#if (xbee_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (xbee_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef xbee_SPI_UART_ISR_ENTRY_CALLBACK
    xbee_SPI_UART_ISR_EntryCallback();
#endif /* xbee_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != xbee_customIntrHandler)
    {
        xbee_customIntrHandler();
    }

    #if (xbee_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        xbee_ClearSpiExtClkInterruptSource(xbee_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (xbee_CHECK_RX_SW_BUFFER)
    {
        if (xbee_CHECK_INTR_RX_MASKED(xbee_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (xbee_rxBufferHead + 1u);

                /* Adjust local head index */
                if (xbee_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == xbee_rxBufferTail)
                {
                    #if (xbee_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        xbee_INTR_RX_MASK_REG &= ~xbee_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) xbee_RX_FIFO_RD_REG;
                        xbee_rxBufferOverflow = (uint8) xbee_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    xbee_PutWordInRxBuffer(locHead, xbee_RX_FIFO_RD_REG);

                    /* Move head index */
                    xbee_rxBufferHead = locHead;
                }
            }
            while(0u != xbee_GET_RX_FIFO_ENTRIES);

            xbee_ClearRxInterruptSource(xbee_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (xbee_CHECK_TX_SW_BUFFER)
    {
        if (xbee_CHECK_INTR_TX_MASKED(xbee_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (xbee_txBufferHead != xbee_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (xbee_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (xbee_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    xbee_TX_FIFO_WR_REG = xbee_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    xbee_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    xbee_DISABLE_INTR_TX(xbee_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (xbee_SPI_UART_FIFO_SIZE != xbee_GET_TX_FIFO_ENTRIES);

            xbee_ClearTxInterruptSource(xbee_INTR_TX_NOT_FULL);
        }
    }
    #endif
    
#ifdef xbee_SPI_UART_ISR_EXIT_CALLBACK
    xbee_SPI_UART_ISR_ExitCallback();
#endif /* xbee_SPI_UART_ISR_EXIT_CALLBACK */
    
}

#endif /* (xbee_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
