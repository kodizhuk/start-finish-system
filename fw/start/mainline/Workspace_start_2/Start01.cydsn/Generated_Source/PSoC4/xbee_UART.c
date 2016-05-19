/*******************************************************************************
* File Name: xbee_UART.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
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
#include "cyapicallbacks.h"

#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const xbee_UART_INIT_STRUCT xbee_configUart =
    {
        xbee_UART_SUB_MODE,
        xbee_UART_DIRECTION,
        xbee_UART_DATA_BITS_NUM,
        xbee_UART_PARITY_TYPE,
        xbee_UART_STOP_BITS_NUM,
        xbee_UART_OVS_FACTOR,
        xbee_UART_IRDA_LOW_POWER,
        xbee_UART_MEDIAN_FILTER_ENABLE,
        xbee_UART_RETRY_ON_NACK,
        xbee_UART_IRDA_POLARITY,
        xbee_UART_DROP_ON_PARITY_ERR,
        xbee_UART_DROP_ON_FRAME_ERR,
        xbee_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        xbee_UART_MP_MODE_ENABLE,
        xbee_UART_MP_ACCEPT_ADDRESS,
        xbee_UART_MP_RX_ADDRESS,
        xbee_UART_MP_RX_ADDRESS_MASK,
        (uint32) xbee_SCB_IRQ_INTERNAL,
        xbee_UART_INTR_RX_MASK,
        xbee_UART_RX_TRIGGER_LEVEL,
        xbee_UART_INTR_TX_MASK,
        xbee_UART_TX_TRIGGER_LEVEL,
        (uint8) xbee_UART_BYTE_MODE_ENABLE,
        (uint8) xbee_UART_CTS_ENABLE,
        (uint8) xbee_UART_CTS_POLARITY,
        (uint8) xbee_UART_RTS_POLARITY,
        (uint8) xbee_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: xbee_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void xbee_UartInit(const xbee_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (xbee_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (xbee_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */

            /* Configure pins */
            xbee_SetPins(xbee_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            xbee_scbMode       = (uint8) xbee_SCB_MODE_UART;
            xbee_scbEnableWake = (uint8) config->enableWake;
            xbee_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            xbee_rxBuffer      =         config->rxBuffer;
            xbee_rxDataBits    = (uint8) config->dataBits;
            xbee_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            xbee_txBuffer      =         config->txBuffer;
            xbee_txDataBits    = (uint8) config->dataBits;
            xbee_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(xbee_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                xbee_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (xbee_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (xbee_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                xbee_CTRL_REG  = xbee_GET_CTRL_OVS(config->oversample);
            }

            xbee_CTRL_REG     |= xbee_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             xbee_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             xbee_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            xbee_UART_CTRL_REG = xbee_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            xbee_UART_RX_CTRL_REG = xbee_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        xbee_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        xbee_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        xbee_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        xbee_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(xbee_UART_PARITY_NONE != config->parity)
            {
               xbee_UART_RX_CTRL_REG |= xbee_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    xbee_UART_RX_CTRL_PARITY_ENABLED;
            }

            xbee_RX_CTRL_REG      = xbee_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                xbee_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                xbee_GET_UART_RX_CTRL_ENABLED(config->direction);

            xbee_RX_FIFO_CTRL_REG = xbee_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            xbee_RX_MATCH_REG     = xbee_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                xbee_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            xbee_UART_TX_CTRL_REG = xbee_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                xbee_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(xbee_UART_PARITY_NONE != config->parity)
            {
               xbee_UART_TX_CTRL_REG |= xbee_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    xbee_UART_TX_CTRL_PARITY_ENABLED;
            }

            xbee_TX_CTRL_REG      = xbee_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                xbee_GET_UART_TX_CTRL_ENABLED(config->direction);

            xbee_TX_FIFO_CTRL_REG = xbee_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
            xbee_UART_FLOW_CTRL_REG = xbee_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            xbee_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            xbee_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            xbee_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (xbee_ISR_NUMBER);
            CyIntSetPriority(xbee_ISR_NUMBER, xbee_ISR_PRIORITY);
            (void) CyIntSetVector(xbee_ISR_NUMBER, &xbee_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(xbee_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (xbee_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(xbee_RX_WAKE_ISR_NUMBER, xbee_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(xbee_RX_WAKE_ISR_NUMBER, &xbee_UART_WAKEUP_ISR);
        #endif /* (xbee_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            xbee_INTR_I2C_EC_MASK_REG = xbee_NO_INTR_SOURCES;
            xbee_INTR_SPI_EC_MASK_REG = xbee_NO_INTR_SOURCES;
            xbee_INTR_SLAVE_MASK_REG  = xbee_NO_INTR_SOURCES;
            xbee_INTR_MASTER_MASK_REG = xbee_NO_INTR_SOURCES;
            xbee_INTR_RX_MASK_REG     = config->rxInterruptMask;
            xbee_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            xbee_rxBufferHead     = 0u;
            xbee_rxBufferTail     = 0u;
            xbee_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            xbee_txBufferHead = 0u;
            xbee_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: xbee_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void xbee_UartInit(void)
    {
        /* Configure UART interface */
        xbee_CTRL_REG = xbee_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        xbee_UART_CTRL_REG = xbee_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        xbee_UART_RX_CTRL_REG = xbee_UART_DEFAULT_UART_RX_CTRL;
        xbee_RX_CTRL_REG      = xbee_UART_DEFAULT_RX_CTRL;
        xbee_RX_FIFO_CTRL_REG = xbee_UART_DEFAULT_RX_FIFO_CTRL;
        xbee_RX_MATCH_REG     = xbee_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        xbee_UART_TX_CTRL_REG = xbee_UART_DEFAULT_UART_TX_CTRL;
        xbee_TX_CTRL_REG      = xbee_UART_DEFAULT_TX_CTRL;
        xbee_TX_FIFO_CTRL_REG = xbee_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
        xbee_UART_FLOW_CTRL_REG = xbee_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(xbee_SCB_IRQ_INTERNAL)
        CyIntDisable    (xbee_ISR_NUMBER);
        CyIntSetPriority(xbee_ISR_NUMBER, xbee_ISR_PRIORITY);
        (void) CyIntSetVector(xbee_ISR_NUMBER, &xbee_SPI_UART_ISR);
    #endif /* (xbee_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(xbee_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (xbee_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(xbee_RX_WAKE_ISR_NUMBER, xbee_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(xbee_RX_WAKE_ISR_NUMBER, &xbee_UART_WAKEUP_ISR);
    #endif /* (xbee_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        xbee_INTR_I2C_EC_MASK_REG = xbee_UART_DEFAULT_INTR_I2C_EC_MASK;
        xbee_INTR_SPI_EC_MASK_REG = xbee_UART_DEFAULT_INTR_SPI_EC_MASK;
        xbee_INTR_SLAVE_MASK_REG  = xbee_UART_DEFAULT_INTR_SLAVE_MASK;
        xbee_INTR_MASTER_MASK_REG = xbee_UART_DEFAULT_INTR_MASTER_MASK;
        xbee_INTR_RX_MASK_REG     = xbee_UART_DEFAULT_INTR_RX_MASK;
        xbee_INTR_TX_MASK_REG     = xbee_UART_DEFAULT_INTR_TX_MASK;

    #if(xbee_INTERNAL_RX_SW_BUFFER_CONST)
        xbee_rxBufferHead     = 0u;
        xbee_rxBufferTail     = 0u;
        xbee_rxBufferOverflow = 0u;
    #endif /* (xbee_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(xbee_INTERNAL_TX_SW_BUFFER_CONST)
        xbee_txBufferHead = 0u;
        xbee_txBufferTail = 0u;
    #endif /* (xbee_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: xbee_UartPostEnable
********************************************************************************
*
* Summary:
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be 
*  controlled by the SCB UART.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void xbee_UartPostEnable(void)
{
#if (xbee_SCB_MODE_UNCONFIG_CONST_CFG)

#if (xbee_TX_SDA_MISO_PIN)
    if (xbee_CHECK_TX_SDA_MISO_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        xbee_SET_HSIOM_SEL(xbee_TX_SDA_MISO_HSIOM_REG, xbee_TX_SDA_MISO_HSIOM_MASK,
                                       xbee_TX_SDA_MISO_HSIOM_POS, xbee_HSIOM_UART_SEL);
    }
#endif /* (xbee_TX_SDA_MISO_PIN_PIN) */

#if (xbee_SS0_PIN)
    if (xbee_CHECK_SS0_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        xbee_SET_HSIOM_SEL(xbee_SS0_HSIOM_REG, xbee_SS0_HSIOM_MASK,
                                       xbee_SS0_HSIOM_POS, xbee_HSIOM_UART_SEL);
    }
#endif /* (xbee_SS0_PIN) */

#else
#if (xbee_UART_TX_PIN)
     /* Set SCB UART to drive the output pin */
    xbee_SET_HSIOM_SEL(xbee_TX_HSIOM_REG, xbee_TX_HSIOM_MASK,
                                   xbee_TX_HSIOM_POS, xbee_HSIOM_UART_SEL);
#endif /* (xbee_UART_TX_PIN) */

#if (xbee_UART_RTS_PIN)
    /* Set SCB UART to drive the output pin */
    xbee_SET_HSIOM_SEL(xbee_RTS_HSIOM_REG, xbee_RTS_HSIOM_MASK,
                                   xbee_RTS_HSIOM_POS, xbee_HSIOM_UART_SEL);
#endif /* (xbee_UART_RTS_PIN) */

#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: xbee_UartStop
********************************************************************************
*
* Summary:
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature to
*  not cause it to trigger after the component is enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void xbee_UartStop(void)
{
#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (xbee_TX_SDA_MISO_PIN)
        if (xbee_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            xbee_SET_HSIOM_SEL(xbee_TX_SDA_MISO_HSIOM_REG, xbee_TX_SDA_MISO_HSIOM_MASK,
                                           xbee_TX_SDA_MISO_HSIOM_POS, xbee_HSIOM_GPIO_SEL);
        }
    #endif /* (xbee_TX_SDA_MISO_PIN_PIN) */

    #if (xbee_SS0_PIN)
        if (xbee_CHECK_SS0_PIN_USED)
        {
            /* Set output pin state after block is disabled */
            xbee_spi_ss0_Write(xbee_GET_UART_RTS_INACTIVE);

            /* Set GPIO to drive output pin */
            xbee_SET_HSIOM_SEL(xbee_SS0_HSIOM_REG, xbee_SS0_HSIOM_MASK,
                                           xbee_SS0_HSIOM_POS, xbee_HSIOM_GPIO_SEL);
        }
    #endif /* (xbee_SS0_PIN) */

#else
    #if (xbee_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        xbee_SET_HSIOM_SEL(xbee_TX_HSIOM_REG, xbee_TX_HSIOM_MASK,
                                       xbee_TX_HSIOM_POS, xbee_HSIOM_GPIO_SEL);
    #endif /* (xbee_UART_TX_PIN) */

    #if (xbee_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        xbee_rts_Write(xbee_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        xbee_SET_HSIOM_SEL(xbee_RTS_HSIOM_REG, xbee_RTS_HSIOM_MASK,
                                       xbee_RTS_HSIOM_POS, xbee_HSIOM_GPIO_SEL);
    #endif /* (xbee_UART_RTS_PIN) */

#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (xbee_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    xbee_UART_RX_CTRL_REG &= (uint32) ~xbee_UART_RX_CTRL_SKIP_START;
#endif /* (xbee_UART_WAKE_ENABLE_CONST) */
}


/*******************************************************************************
* Function Name: xbee_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void xbee_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = xbee_RX_MATCH_REG;

    matchReg &= ((uint32) ~xbee_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & xbee_RX_MATCH_ADDR_MASK)); /* Set address  */

    xbee_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: xbee_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void xbee_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = xbee_RX_MATCH_REG;

    matchReg &= ((uint32) ~xbee_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << xbee_RX_MATCH_MASK_POS));

    xbee_RX_MATCH_REG = matchReg;
}


#if(xbee_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: xbee_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element
    *    retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from
    *    the software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is enabled: The internal software buffer overflow
    *  does not treat as an error condition.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 xbee_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != xbee_SpiUartGetRxBufferSize())
        {
            rxData = xbee_SpiUartReadRxData();
        }

        if (xbee_CHECK_INTR_RX(xbee_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            xbee_ClearRxInterruptSource(xbee_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: xbee_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 7-0 contain the next data element from the receive buffer and
    *  other bits contain the error condition.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is disabled: The internal software buffer overflow
    *  is not returned as status by this function.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 xbee_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (xbee_CHECK_RX_SW_BUFFER)
        {
            xbee_DisableInt();
        }
        #endif

        if (0u != xbee_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (xbee_CHECK_RX_SW_BUFFER)
            {            
                xbee_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = xbee_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = xbee_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            #if (xbee_CHECK_RX_SW_BUFFER)
            {
                xbee_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (xbee_GetRxInterruptSource() & xbee_INTR_RX_ERR);
        xbee_ClearRxInterruptSource(xbee_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: xbee_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   xbee_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   xbee_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void xbee_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                xbee_UART_FLOW_CTRL_REG |= (uint32)  xbee_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                xbee_UART_FLOW_CTRL_REG &= (uint32) ~xbee_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: xbee_UartSetRtsFifoLevel
        ********************************************************************************
        *
        * Summary:
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *
        * Parameters:
        *  level: Level in the RX FIFO for RTS signal activation.
        *         The range of valid level values is between 0 and RX FIFO depth - 1.
        *         Setting level value to 0 disables RTS signal activation.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void xbee_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = xbee_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~xbee_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (xbee_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            xbee_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */

#endif /* (xbee_UART_RX_DIRECTION) */


#if(xbee_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: xbee_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void xbee_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            xbee_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: xbee_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and
    *  line feed (0x0A) into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void xbee_UartPutCRLF(uint32 txDataByte)
    {
        xbee_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        xbee_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        xbee_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: xbeeSCB_UartEnableCts
        ********************************************************************************
        *
        * Summary:
        *  Enables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void xbee_UartEnableCts(void)
        {
            xbee_UART_FLOW_CTRL_REG |= (uint32)  xbee_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: xbee_UartDisableCts
        ********************************************************************************
        *
        * Summary:
        *  Disables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void xbee_UartDisableCts(void)
        {
            xbee_UART_FLOW_CTRL_REG &= (uint32) ~xbee_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: xbee_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   xbee_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   xbee_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void xbee_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                xbee_UART_FLOW_CTRL_REG |= (uint32)  xbee_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                xbee_UART_FLOW_CTRL_REG &= (uint32) ~xbee_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */

#endif /* (xbee_UART_TX_DIRECTION) */


#if(xbee_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: xbee_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the
    *  active mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void xbee_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        xbee_UART_RX_CTRL_REG |= xbee_UART_RX_CTRL_SKIP_START;

    #if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(xbee_MOSI_SCL_RX_WAKE_PIN)
            (void) xbee_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt();
        #endif /* (xbee_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(xbee_UART_RX_WAKE_PIN)
            (void) xbee_rx_wake_ClearInterrupt();
        #endif /* (xbee_UART_RX_WAKE_PIN) */
    #endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(xbee_UART_RX_WAKEUP_IRQ)
        xbee_RxWakeClearPendingInt();
        xbee_RxWakeEnableInt();
    #endif /* (xbee_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: xbee_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void xbee_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(xbee_UART_RX_WAKEUP_IRQ)
        xbee_RxWakeDisableInt();
    #endif /* (xbee_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (xbee_UART_WAKE_ENABLE_CONST) */


#if(xbee_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: xbee_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
    *  event. This event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(xbee_UART_WAKEUP_ISR)
    {
    #ifdef xbee_UART_WAKEUP_ISR_ENTRY_CALLBACK
        xbee_UART_WAKEUP_ISR_EntryCallback();
    #endif /* xbee_UART_WAKEUP_ISR_ENTRY_CALLBACK */

        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by xbee_UartRestoreConfig() call.
        */
    #if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(xbee_MOSI_SCL_RX_WAKE_PIN)
            (void) xbee_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt();
        #endif /* (xbee_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(xbee_UART_RX_WAKE_PIN)
            (void) xbee_rx_wake_ClearInterrupt();
        #endif /* (xbee_UART_RX_WAKE_PIN) */
    #endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */

    #ifdef xbee_UART_WAKEUP_ISR_EXIT_CALLBACK
        xbee_UART_WAKEUP_ISR_ExitCallback();
    #endif /* xbee_UART_WAKEUP_ISR_EXIT_CALLBACK */
    }
#endif /* (xbee_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
