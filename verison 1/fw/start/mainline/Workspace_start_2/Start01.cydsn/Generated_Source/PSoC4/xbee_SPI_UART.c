/*******************************************************************************
* File Name: xbee_SPI_UART.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "xbee_PVT.h"
#include "xbee_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(xbee_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 xbee_rxBufferHead;
    volatile uint32 xbee_rxBufferTail;
    volatile uint8  xbee_rxBufferOverflow;
#endif /* (xbee_INTERNAL_RX_SW_BUFFER_CONST) */

#if(xbee_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 xbee_txBufferHead;
    volatile uint32 xbee_txBufferTail;
#endif /* (xbee_INTERNAL_TX_SW_BUFFER_CONST) */

#if(xbee_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 xbee_rxBufferInternal[xbee_INTERNAL_RX_BUFFER_SIZE];
#endif /* (xbee_INTERNAL_RX_SW_BUFFER) */

#if(xbee_INTERNAL_TX_SW_BUFFER)
    volatile uint8 xbee_txBufferInternal[xbee_TX_BUFFER_SIZE];
#endif /* (xbee_INTERNAL_TX_SW_BUFFER) */


#if(xbee_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: xbee_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into xbee_SpiInit for description.
    *
    *******************************************************************************/
    uint32 xbee_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (xbee_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (xbee_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (xbee_CHECK_RX_SW_BUFFER)
        {
            if (xbee_rxBufferHead != xbee_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (xbee_rxBufferTail + 1u);

                if (xbee_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = xbee_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                xbee_rxBufferTail = locTail;

                #if (xbee_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (xbee_INTR_RX_MASK_REG & xbee_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        xbee_INTR_RX_MASK_REG |= xbee_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = xbee_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: xbee_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 xbee_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (xbee_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (xbee_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (xbee_CHECK_RX_SW_BUFFER)
        {
            locHead = xbee_rxBufferHead;

            if(locHead >= xbee_rxBufferTail)
            {
                size = (locHead - xbee_rxBufferTail);
            }
            else
            {
                size = (locHead + (xbee_INTERNAL_RX_BUFFER_SIZE - xbee_rxBufferTail));
            }
        }
        #else
        {
            size = xbee_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: xbee_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void xbee_SpiUartClearRxBuffer(void)
    {
        #if (xbee_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            xbee_DisableInt();

            /* Flush RX software buffer */
            xbee_rxBufferHead = xbee_rxBufferTail;
            xbee_rxBufferOverflow = 0u;

            xbee_CLEAR_RX_FIFO;
            xbee_ClearRxInterruptSource(xbee_INTR_RX_ALL);

            #if (xbee_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                xbee_INTR_RX_MASK_REG |= xbee_INTR_RX_NOT_EMPTY;
            }
            #endif

            /* Release lock */
            xbee_EnableInt();
        }
        #else
        {
            xbee_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (xbee_RX_DIRECTION) */


#if(xbee_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: xbee_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void xbee_SpiUartWriteTxData(uint32 txData)
    {
    #if (xbee_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (xbee_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (xbee_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((xbee_txBufferHead == xbee_txBufferTail) &&
                (xbee_SPI_UART_FIFO_SIZE != xbee_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                xbee_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (xbee_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (xbee_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == xbee_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                xbee_ClearTxInterruptSource(xbee_INTR_TX_NOT_FULL);

                xbee_PutWordInTxBuffer(locHead, txData);

                xbee_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (xbee_INTR_TX_MASK_REG & xbee_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    xbee_INTR_TX_MASK_REG |= (uint32) xbee_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (xbee_SPI_UART_FIFO_SIZE == xbee_GET_TX_FIFO_ENTRIES)
            {
            }

            xbee_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: xbee_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void xbee_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            xbee_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: xbee_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    * Returns the number of elements currently in the transmit buffer.
    *  - TX software buffer is disabled: returns the number of used entries in
    *    TX FIFO.
    *  - TX software buffer is enabled: returns the number of elements currently
    *    used in the transmit buffer. This number does not include used entries in
    *    the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *    not full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 xbee_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (xbee_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (xbee_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (xbee_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = xbee_txBufferTail;

            if (xbee_txBufferHead >= locTail)
            {
                size = (xbee_txBufferHead - locTail);
            }
            else
            {
                size = (xbee_txBufferHead + (xbee_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = xbee_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: xbee_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void xbee_SpiUartClearTxBuffer(void)
    {
        #if (xbee_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            xbee_DisableInt();

            /* Flush TX software buffer */
            xbee_txBufferHead = xbee_txBufferTail;

            xbee_INTR_TX_MASK_REG &= (uint32) ~xbee_INTR_TX_NOT_FULL;
            xbee_CLEAR_TX_FIFO;
            xbee_ClearTxInterruptSource(xbee_INTR_TX_ALL);

            /* Release lock */
            xbee_EnableInt();
        }
        #else
        {
            xbee_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (xbee_TX_DIRECTION) */


/*******************************************************************************
* Function Name: xbee_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables the RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 xbee_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = xbee_GetRxInterruptMode();

    xbee_SetRxInterruptMode(xbee_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: xbee_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 xbee_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = xbee_GetTxInterruptMode();

    xbee_SetTxInterruptMode(xbee_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: xbee_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void xbee_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (xbee_ONE_BYTE_WIDTH == xbee_rxDataBits)
        {
            xbee_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            xbee_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            xbee_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: xbee_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 xbee_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (xbee_ONE_BYTE_WIDTH == xbee_rxDataBits)
        {
            value = xbee_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) xbee_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)xbee_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: xbee_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void xbee_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (xbee_ONE_BYTE_WIDTH == xbee_txDataBits)
        {
            xbee_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            xbee_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            xbee_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: xbee_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 xbee_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (xbee_ONE_BYTE_WIDTH == xbee_txDataBits)
        {
            value = (uint32) xbee_txBuffer[idx];
        }
        else
        {
            value  = (uint32) xbee_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) xbee_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
