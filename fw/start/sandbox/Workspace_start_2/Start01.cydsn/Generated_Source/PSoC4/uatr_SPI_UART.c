/*******************************************************************************
* File Name: uatr_SPI_UART.c
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

#include "uatr_PVT.h"
#include "uatr_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(uatr_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 uatr_rxBufferHead;
    volatile uint32 uatr_rxBufferTail;
    volatile uint8  uatr_rxBufferOverflow;
#endif /* (uatr_INTERNAL_RX_SW_BUFFER_CONST) */

#if(uatr_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 uatr_txBufferHead;
    volatile uint32 uatr_txBufferTail;
#endif /* (uatr_INTERNAL_TX_SW_BUFFER_CONST) */

#if(uatr_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 uatr_rxBufferInternal[uatr_INTERNAL_RX_BUFFER_SIZE];
#endif /* (uatr_INTERNAL_RX_SW_BUFFER) */

#if(uatr_INTERNAL_TX_SW_BUFFER)
    volatile uint8 uatr_txBufferInternal[uatr_TX_BUFFER_SIZE];
#endif /* (uatr_INTERNAL_TX_SW_BUFFER) */


#if(uatr_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: uatr_SpiUartReadRxData
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
    *  Look into uatr_SpiInit for description.
    *
    *******************************************************************************/
    uint32 uatr_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (uatr_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (uatr_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (uatr_CHECK_RX_SW_BUFFER)
        {
            if (uatr_rxBufferHead != uatr_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (uatr_rxBufferTail + 1u);

                if (uatr_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = uatr_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                uatr_rxBufferTail = locTail;

                #if (uatr_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (uatr_INTR_RX_MASK_REG & uatr_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        uatr_INTR_RX_MASK_REG |= uatr_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = uatr_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: uatr_SpiUartGetRxBufferSize
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
    uint32 uatr_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (uatr_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (uatr_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (uatr_CHECK_RX_SW_BUFFER)
        {
            locHead = uatr_rxBufferHead;

            if(locHead >= uatr_rxBufferTail)
            {
                size = (locHead - uatr_rxBufferTail);
            }
            else
            {
                size = (locHead + (uatr_INTERNAL_RX_BUFFER_SIZE - uatr_rxBufferTail));
            }
        }
        #else
        {
            size = uatr_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: uatr_SpiUartClearRxBuffer
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
    void uatr_SpiUartClearRxBuffer(void)
    {
        #if (uatr_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            uatr_DisableInt();

            /* Flush RX software buffer */
            uatr_rxBufferHead = uatr_rxBufferTail;
            uatr_rxBufferOverflow = 0u;

            uatr_CLEAR_RX_FIFO;
            uatr_ClearRxInterruptSource(uatr_INTR_RX_ALL);

            #if (uatr_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                uatr_INTR_RX_MASK_REG |= uatr_INTR_RX_NOT_EMPTY;
            }
            #endif

            /* Release lock */
            uatr_EnableInt();
        }
        #else
        {
            uatr_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (uatr_RX_DIRECTION) */


#if(uatr_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: uatr_SpiUartWriteTxData
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
    void uatr_SpiUartWriteTxData(uint32 txData)
    {
    #if (uatr_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (uatr_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (uatr_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((uatr_txBufferHead == uatr_txBufferTail) &&
                (uatr_SPI_UART_FIFO_SIZE != uatr_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                uatr_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (uatr_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (uatr_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == uatr_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                uatr_ClearTxInterruptSource(uatr_INTR_TX_NOT_FULL);

                uatr_PutWordInTxBuffer(locHead, txData);

                uatr_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (uatr_INTR_TX_MASK_REG & uatr_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    uatr_INTR_TX_MASK_REG |= (uint32) uatr_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (uatr_SPI_UART_FIFO_SIZE == uatr_GET_TX_FIFO_ENTRIES)
            {
            }

            uatr_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: uatr_SpiUartPutArray
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
    void uatr_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            uatr_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: uatr_SpiUartGetTxBufferSize
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
    uint32 uatr_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (uatr_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (uatr_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (uatr_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = uatr_txBufferTail;

            if (uatr_txBufferHead >= locTail)
            {
                size = (uatr_txBufferHead - locTail);
            }
            else
            {
                size = (uatr_txBufferHead + (uatr_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = uatr_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: uatr_SpiUartClearTxBuffer
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
    void uatr_SpiUartClearTxBuffer(void)
    {
        #if (uatr_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            uatr_DisableInt();

            /* Flush TX software buffer */
            uatr_txBufferHead = uatr_txBufferTail;

            uatr_INTR_TX_MASK_REG &= (uint32) ~uatr_INTR_TX_NOT_FULL;
            uatr_CLEAR_TX_FIFO;
            uatr_ClearTxInterruptSource(uatr_INTR_TX_ALL);

            /* Release lock */
            uatr_EnableInt();
        }
        #else
        {
            uatr_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (uatr_TX_DIRECTION) */


/*******************************************************************************
* Function Name: uatr_SpiUartDisableIntRx
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
uint32 uatr_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = uatr_GetRxInterruptMode();

    uatr_SetRxInterruptMode(uatr_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: uatr_SpiUartDisableIntTx
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
uint32 uatr_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = uatr_GetTxInterruptMode();

    uatr_SetTxInterruptMode(uatr_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: uatr_PutWordInRxBuffer
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
    void uatr_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (uatr_ONE_BYTE_WIDTH == uatr_rxDataBits)
        {
            uatr_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            uatr_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            uatr_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: uatr_GetWordFromRxBuffer
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
    uint32 uatr_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (uatr_ONE_BYTE_WIDTH == uatr_rxDataBits)
        {
            value = uatr_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) uatr_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)uatr_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: uatr_PutWordInTxBuffer
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
    void uatr_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (uatr_ONE_BYTE_WIDTH == uatr_txDataBits)
        {
            uatr_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            uatr_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            uatr_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: uatr_GetWordFromTxBuffer
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
    uint32 uatr_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (uatr_ONE_BYTE_WIDTH == uatr_txDataBits)
        {
            value = (uint32) uatr_txBuffer[idx];
        }
        else
        {
            value  = (uint32) uatr_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) uatr_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
