/***************************************************************************//**
* \file uartDebug_SPI_UART.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "uartDebug_PVT.h"
#include "uartDebug_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(uartDebug_INTERNAL_RX_SW_BUFFER_CONST)
    /* Start index to put data into the software receive buffer.*/
    volatile uint32 uartDebug_rxBufferHead;
    /* Start index to get data from the software receive buffer.*/
    volatile uint32 uartDebug_rxBufferTail;
    /**
    * \addtogroup group_globals
    * \{
    */
    /** Sets when internal software receive buffer overflow
    *  was occurred.
    */
    volatile uint8  uartDebug_rxBufferOverflow;
    /** \} globals */
#endif /* (uartDebug_INTERNAL_RX_SW_BUFFER_CONST) */

#if(uartDebug_INTERNAL_TX_SW_BUFFER_CONST)
    /* Start index to put data into the software transmit buffer.*/
    volatile uint32 uartDebug_txBufferHead;
    /* Start index to get data from the software transmit buffer.*/
    volatile uint32 uartDebug_txBufferTail;
#endif /* (uartDebug_INTERNAL_TX_SW_BUFFER_CONST) */

#if(uartDebug_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 uartDebug_rxBufferInternal[uartDebug_INTERNAL_RX_BUFFER_SIZE];
#endif /* (uartDebug_INTERNAL_RX_SW_BUFFER) */

#if(uartDebug_INTERNAL_TX_SW_BUFFER)
    volatile uint8 uartDebug_txBufferInternal[uartDebug_TX_BUFFER_SIZE];
#endif /* (uartDebug_INTERNAL_TX_SW_BUFFER) */


#if(uartDebug_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: uartDebug_SpiUartReadRxData
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * \return
    *  Next data element from the receive buffer. 
    *  The amount of data bits to be received depends on RX data bits selection 
    *  (the data bit counting starts from LSB of return value).
    *
    * \globalvars
    *  uartDebug_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  uartDebug_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 uartDebug_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (uartDebug_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (uartDebug_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (uartDebug_CHECK_RX_SW_BUFFER)
        {
            if (uartDebug_rxBufferHead != uartDebug_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (uartDebug_rxBufferTail + 1u);

                if (uartDebug_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = uartDebug_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                uartDebug_rxBufferTail = locTail;

                #if (uartDebug_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (uartDebug_INTR_RX_MASK_REG & uartDebug_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        uartDebug_INTR_RX_MASK_REG |= uartDebug_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = uartDebug_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: uartDebug_SpiUartGetRxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * \return
    *  Number of received data elements.
    *
    * \globalvars
    *  uartDebug_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  uartDebug_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 uartDebug_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (uartDebug_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (uartDebug_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (uartDebug_CHECK_RX_SW_BUFFER)
        {
            locHead = uartDebug_rxBufferHead;

            if(locHead >= uartDebug_rxBufferTail)
            {
                size = (locHead - uartDebug_rxBufferTail);
            }
            else
            {
                size = (locHead + (uartDebug_INTERNAL_RX_BUFFER_SIZE - uartDebug_rxBufferTail));
            }
        }
        #else
        {
            size = uartDebug_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: uartDebug_SpiUartClearRxBuffer
    ****************************************************************************//**
    *
    *  Clears the receive buffer and RX FIFO.
    *
    * \globalvars
    *  uartDebug_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  uartDebug_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    void uartDebug_SpiUartClearRxBuffer(void)
    {
        #if (uartDebug_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            uartDebug_DisableInt();

            /* Flush RX software buffer */
            uartDebug_rxBufferHead = uartDebug_rxBufferTail;
            uartDebug_rxBufferOverflow = 0u;

            uartDebug_CLEAR_RX_FIFO;
            uartDebug_ClearRxInterruptSource(uartDebug_INTR_RX_ALL);

            #if (uartDebug_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                uartDebug_INTR_RX_MASK_REG |= uartDebug_INTR_RX_NOT_EMPTY;
            }
            #endif
            
            /* Release lock */
            uartDebug_EnableInt();
        }
        #else
        {
            uartDebug_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (uartDebug_RX_DIRECTION) */


#if(uartDebug_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: uartDebug_SpiUartWriteTxData
    ****************************************************************************//**
    *
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *   The amount of data bits to be transmitted depends on TX data bits selection 
    *   (the data bit counting starts from LSB of txDataByte).
    *
    * \globalvars
    *  uartDebug_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  uartDebug_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void uartDebug_SpiUartWriteTxData(uint32 txData)
    {
    #if (uartDebug_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (uartDebug_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (uartDebug_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((uartDebug_txBufferHead == uartDebug_txBufferTail) &&
                (uartDebug_SPI_UART_FIFO_SIZE != uartDebug_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                uartDebug_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (uartDebug_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (uartDebug_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == uartDebug_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                uartDebug_ClearTxInterruptSource(uartDebug_INTR_TX_NOT_FULL);

                uartDebug_PutWordInTxBuffer(locHead, txData);

                uartDebug_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (uartDebug_INTR_TX_MASK_REG & uartDebug_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    uartDebug_INTR_TX_MASK_REG |= (uint32) uartDebug_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (uartDebug_SPI_UART_FIFO_SIZE == uartDebug_GET_TX_FIFO_ENTRIES)
            {
            }

            uartDebug_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: uartDebug_SpiUartPutArray
    ****************************************************************************//**
    *
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * \param wrBuf: pointer to an array of data to be placed in transmit buffer. 
    *  The width of the data to be transmitted depends on TX data width selection 
    *  (the data bit counting starts from LSB for each array element).
    * \param count: number of data elements to be placed in the transmit buffer.
    *
    * \globalvars
    *  uartDebug_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  uartDebug_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void uartDebug_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            uartDebug_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: uartDebug_SpiUartGetTxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of elements currently in the transmit buffer.
    *   - TX software buffer is disabled: returns the number of used entries in
    *     TX FIFO.
    *   - TX software buffer is enabled: returns the number of elements currently
    *     used in the transmit buffer. This number does not include used entries in
    *     the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *     not full.
    *
    * \return
    *  Number of data elements ready to transmit.
    *
    * \globalvars
    *  uartDebug_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  uartDebug_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    uint32 uartDebug_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (uartDebug_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (uartDebug_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (uartDebug_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = uartDebug_txBufferTail;

            if (uartDebug_txBufferHead >= locTail)
            {
                size = (uartDebug_txBufferHead - locTail);
            }
            else
            {
                size = (uartDebug_txBufferHead + (uartDebug_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = uartDebug_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: uartDebug_SpiUartClearTxBuffer
    ****************************************************************************//**
    *
    *  Clears the transmit buffer and TX FIFO.
    *
    * \globalvars
    *  uartDebug_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  uartDebug_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void uartDebug_SpiUartClearTxBuffer(void)
    {
        #if (uartDebug_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            uartDebug_DisableInt();

            /* Flush TX software buffer */
            uartDebug_txBufferHead = uartDebug_txBufferTail;

            uartDebug_INTR_TX_MASK_REG &= (uint32) ~uartDebug_INTR_TX_NOT_FULL;
            uartDebug_CLEAR_TX_FIFO;
            uartDebug_ClearTxInterruptSource(uartDebug_INTR_TX_ALL);

            /* Release lock */
            uartDebug_EnableInt();
        }
        #else
        {
            uartDebug_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (uartDebug_TX_DIRECTION) */


/*******************************************************************************
* Function Name: uartDebug_SpiUartDisableIntRx
****************************************************************************//**
*
*  Disables the RX interrupt sources.
*
*  \return
*   Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 uartDebug_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = uartDebug_GetRxInterruptMode();

    uartDebug_SetRxInterruptMode(uartDebug_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: uartDebug_SpiUartDisableIntTx
****************************************************************************//**
*
*  Disables TX interrupt sources.
*
*  \return
*   Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 uartDebug_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = uartDebug_GetTxInterruptMode();

    uartDebug_SetTxInterruptMode(uartDebug_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(uartDebug_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: uartDebug_PutWordInRxBuffer
    ****************************************************************************//**
    *
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param index:      index to store data byte/word in the RX buffer.
    *  \param rxDataByte: byte/word to store.
    *
    *******************************************************************************/
    void uartDebug_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (uartDebug_ONE_BYTE_WIDTH == uartDebug_rxDataBits)
        {
            uartDebug_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            uartDebug_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            uartDebug_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: uartDebug_GetWordFromRxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \return
    *   Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 uartDebug_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (uartDebug_ONE_BYTE_WIDTH == uartDebug_rxDataBits)
        {
            value = uartDebug_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) uartDebug_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)uartDebug_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: uartDebug_PutWordInTxBuffer
    ****************************************************************************//**
    *
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx:        index to store data byte/word in the TX buffer.
    *  \param txDataByte: byte/word to store.
    *
    *******************************************************************************/
    void uartDebug_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (uartDebug_ONE_BYTE_WIDTH == uartDebug_txDataBits)
        {
            uartDebug_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            uartDebug_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            uartDebug_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: uartDebug_GetWordFromTxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx: index to get data byte/word from the TX buffer.
    *
    *  \return
    *   Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 uartDebug_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (uartDebug_ONE_BYTE_WIDTH == uartDebug_txDataBits)
        {
            value = (uint32) uartDebug_txBuffer[idx];
        }
        else
        {
            value  = (uint32) uartDebug_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) uartDebug_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
