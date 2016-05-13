/*******************************************************************************
* File Name: uatr_SPI_UART_INT.c
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

#include "uatr_PVT.h"
#include "uatr_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (uatr_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: uatr_SPI_UART_ISR
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
CY_ISR(uatr_SPI_UART_ISR)
{
#if (uatr_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (uatr_INTERNAL_RX_SW_BUFFER_CONST) */

#if (uatr_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (uatr_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef uatr_SPI_UART_ISR_ENTRY_CALLBACK
    uatr_SPI_UART_ISR_EntryCallback();
#endif /* uatr_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != uatr_customIntrHandler)
    {
        uatr_customIntrHandler();
    }

    #if (uatr_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        uatr_ClearSpiExtClkInterruptSource(uatr_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (uatr_CHECK_RX_SW_BUFFER)
    {
        if (uatr_CHECK_INTR_RX_MASKED(uatr_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (uatr_rxBufferHead + 1u);

                /* Adjust local head index */
                if (uatr_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == uatr_rxBufferTail)
                {
                    #if (uatr_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        uatr_INTR_RX_MASK_REG &= ~uatr_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) uatr_RX_FIFO_RD_REG;
                        uatr_rxBufferOverflow = (uint8) uatr_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    uatr_PutWordInRxBuffer(locHead, uatr_RX_FIFO_RD_REG);

                    /* Move head index */
                    uatr_rxBufferHead = locHead;
                }
            }
            while(0u != uatr_GET_RX_FIFO_ENTRIES);

            uatr_ClearRxInterruptSource(uatr_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (uatr_CHECK_TX_SW_BUFFER)
    {
        if (uatr_CHECK_INTR_TX_MASKED(uatr_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (uatr_txBufferHead != uatr_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (uatr_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (uatr_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    uatr_TX_FIFO_WR_REG = uatr_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    uatr_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    uatr_DISABLE_INTR_TX(uatr_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (uatr_SPI_UART_FIFO_SIZE != uatr_GET_TX_FIFO_ENTRIES);

            uatr_ClearTxInterruptSource(uatr_INTR_TX_NOT_FULL);
        }
    }
    #endif
    
#ifdef uatr_SPI_UART_ISR_EXIT_CALLBACK
    uatr_SPI_UART_ISR_ExitCallback();
#endif /* uatr_SPI_UART_ISR_EXIT_CALLBACK */
    
}

#endif /* (uatr_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
