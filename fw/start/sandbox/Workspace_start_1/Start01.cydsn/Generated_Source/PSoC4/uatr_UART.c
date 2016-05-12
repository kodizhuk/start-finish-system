/*******************************************************************************
* File Name: uatr_UART.c
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

#include "uatr_PVT.h"
#include "uatr_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const uatr_UART_INIT_STRUCT uatr_configUart =
    {
        uatr_UART_SUB_MODE,
        uatr_UART_DIRECTION,
        uatr_UART_DATA_BITS_NUM,
        uatr_UART_PARITY_TYPE,
        uatr_UART_STOP_BITS_NUM,
        uatr_UART_OVS_FACTOR,
        uatr_UART_IRDA_LOW_POWER,
        uatr_UART_MEDIAN_FILTER_ENABLE,
        uatr_UART_RETRY_ON_NACK,
        uatr_UART_IRDA_POLARITY,
        uatr_UART_DROP_ON_PARITY_ERR,
        uatr_UART_DROP_ON_FRAME_ERR,
        uatr_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        uatr_UART_MP_MODE_ENABLE,
        uatr_UART_MP_ACCEPT_ADDRESS,
        uatr_UART_MP_RX_ADDRESS,
        uatr_UART_MP_RX_ADDRESS_MASK,
        (uint32) uatr_SCB_IRQ_INTERNAL,
        uatr_UART_INTR_RX_MASK,
        uatr_UART_RX_TRIGGER_LEVEL,
        uatr_UART_INTR_TX_MASK,
        uatr_UART_TX_TRIGGER_LEVEL,
        (uint8) uatr_UART_BYTE_MODE_ENABLE,
        (uint8) uatr_UART_CTS_ENABLE,
        (uint8) uatr_UART_CTS_POLARITY,
        (uint8) uatr_UART_RTS_POLARITY,
        (uint8) uatr_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: uatr_UartInit
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
    void uatr_UartInit(const uatr_UART_INIT_STRUCT *config)
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

        #if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (uatr_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (uatr_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

            /* Configure pins */
            uatr_SetPins(uatr_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            uatr_scbMode       = (uint8) uatr_SCB_MODE_UART;
            uatr_scbEnableWake = (uint8) config->enableWake;
            uatr_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            uatr_rxBuffer      =         config->rxBuffer;
            uatr_rxDataBits    = (uint8) config->dataBits;
            uatr_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            uatr_txBuffer      =         config->txBuffer;
            uatr_txDataBits    = (uint8) config->dataBits;
            uatr_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(uatr_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                uatr_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (uatr_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (uatr_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                uatr_CTRL_REG  = uatr_GET_CTRL_OVS(config->oversample);
            }

            uatr_CTRL_REG     |= uatr_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             uatr_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             uatr_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            uatr_UART_CTRL_REG = uatr_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            uatr_UART_RX_CTRL_REG = uatr_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        uatr_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        uatr_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        uatr_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        uatr_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(uatr_UART_PARITY_NONE != config->parity)
            {
               uatr_UART_RX_CTRL_REG |= uatr_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    uatr_UART_RX_CTRL_PARITY_ENABLED;
            }

            uatr_RX_CTRL_REG      = uatr_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                uatr_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                uatr_GET_UART_RX_CTRL_ENABLED(config->direction);

            uatr_RX_FIFO_CTRL_REG = uatr_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            uatr_RX_MATCH_REG     = uatr_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                uatr_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            uatr_UART_TX_CTRL_REG = uatr_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                uatr_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(uatr_UART_PARITY_NONE != config->parity)
            {
               uatr_UART_TX_CTRL_REG |= uatr_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    uatr_UART_TX_CTRL_PARITY_ENABLED;
            }

            uatr_TX_CTRL_REG      = uatr_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                uatr_GET_UART_TX_CTRL_ENABLED(config->direction);

            uatr_TX_FIFO_CTRL_REG = uatr_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
            uatr_UART_FLOW_CTRL_REG = uatr_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            uatr_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            uatr_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            uatr_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (uatr_ISR_NUMBER);
            CyIntSetPriority(uatr_ISR_NUMBER, uatr_ISR_PRIORITY);
            (void) CyIntSetVector(uatr_ISR_NUMBER, &uatr_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(uatr_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (uatr_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(uatr_RX_WAKE_ISR_NUMBER, uatr_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(uatr_RX_WAKE_ISR_NUMBER, &uatr_UART_WAKEUP_ISR);
        #endif /* (uatr_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            uatr_INTR_I2C_EC_MASK_REG = uatr_NO_INTR_SOURCES;
            uatr_INTR_SPI_EC_MASK_REG = uatr_NO_INTR_SOURCES;
            uatr_INTR_SLAVE_MASK_REG  = uatr_NO_INTR_SOURCES;
            uatr_INTR_MASTER_MASK_REG = uatr_NO_INTR_SOURCES;
            uatr_INTR_RX_MASK_REG     = config->rxInterruptMask;
            uatr_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            uatr_rxBufferHead     = 0u;
            uatr_rxBufferTail     = 0u;
            uatr_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            uatr_txBufferHead = 0u;
            uatr_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: uatr_UartInit
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
    void uatr_UartInit(void)
    {
        /* Configure UART interface */
        uatr_CTRL_REG = uatr_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        uatr_UART_CTRL_REG = uatr_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        uatr_UART_RX_CTRL_REG = uatr_UART_DEFAULT_UART_RX_CTRL;
        uatr_RX_CTRL_REG      = uatr_UART_DEFAULT_RX_CTRL;
        uatr_RX_FIFO_CTRL_REG = uatr_UART_DEFAULT_RX_FIFO_CTRL;
        uatr_RX_MATCH_REG     = uatr_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        uatr_UART_TX_CTRL_REG = uatr_UART_DEFAULT_UART_TX_CTRL;
        uatr_TX_CTRL_REG      = uatr_UART_DEFAULT_TX_CTRL;
        uatr_TX_FIFO_CTRL_REG = uatr_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
        uatr_UART_FLOW_CTRL_REG = uatr_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(uatr_SCB_IRQ_INTERNAL)
        CyIntDisable    (uatr_ISR_NUMBER);
        CyIntSetPriority(uatr_ISR_NUMBER, uatr_ISR_PRIORITY);
        (void) CyIntSetVector(uatr_ISR_NUMBER, &uatr_SPI_UART_ISR);
    #endif /* (uatr_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(uatr_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (uatr_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(uatr_RX_WAKE_ISR_NUMBER, uatr_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(uatr_RX_WAKE_ISR_NUMBER, &uatr_UART_WAKEUP_ISR);
    #endif /* (uatr_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        uatr_INTR_I2C_EC_MASK_REG = uatr_UART_DEFAULT_INTR_I2C_EC_MASK;
        uatr_INTR_SPI_EC_MASK_REG = uatr_UART_DEFAULT_INTR_SPI_EC_MASK;
        uatr_INTR_SLAVE_MASK_REG  = uatr_UART_DEFAULT_INTR_SLAVE_MASK;
        uatr_INTR_MASTER_MASK_REG = uatr_UART_DEFAULT_INTR_MASTER_MASK;
        uatr_INTR_RX_MASK_REG     = uatr_UART_DEFAULT_INTR_RX_MASK;
        uatr_INTR_TX_MASK_REG     = uatr_UART_DEFAULT_INTR_TX_MASK;

    #if(uatr_INTERNAL_RX_SW_BUFFER_CONST)
        uatr_rxBufferHead     = 0u;
        uatr_rxBufferTail     = 0u;
        uatr_rxBufferOverflow = 0u;
    #endif /* (uatr_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(uatr_INTERNAL_TX_SW_BUFFER_CONST)
        uatr_txBufferHead = 0u;
        uatr_txBufferTail = 0u;
    #endif /* (uatr_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: uatr_UartPostEnable
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
void uatr_UartPostEnable(void)
{
#if (uatr_SCB_MODE_UNCONFIG_CONST_CFG)

#if (uatr_TX_SDA_MISO_PIN)
    if (uatr_CHECK_TX_SDA_MISO_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        uatr_SET_HSIOM_SEL(uatr_TX_SDA_MISO_HSIOM_REG, uatr_TX_SDA_MISO_HSIOM_MASK,
                                       uatr_TX_SDA_MISO_HSIOM_POS, uatr_HSIOM_UART_SEL);
    }
#endif /* (uatr_TX_SDA_MISO_PIN_PIN) */

#if (uatr_SS0_PIN)
    if (uatr_CHECK_SS0_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        uatr_SET_HSIOM_SEL(uatr_SS0_HSIOM_REG, uatr_SS0_HSIOM_MASK,
                                       uatr_SS0_HSIOM_POS, uatr_HSIOM_UART_SEL);
    }
#endif /* (uatr_SS0_PIN) */

#else
#if (uatr_UART_TX_PIN)
     /* Set SCB UART to drive the output pin */
    uatr_SET_HSIOM_SEL(uatr_TX_HSIOM_REG, uatr_TX_HSIOM_MASK,
                                   uatr_TX_HSIOM_POS, uatr_HSIOM_UART_SEL);
#endif /* (uatr_UART_TX_PIN) */

#if (uatr_UART_RTS_PIN)
    /* Set SCB UART to drive the output pin */
    uatr_SET_HSIOM_SEL(uatr_RTS_HSIOM_REG, uatr_RTS_HSIOM_MASK,
                                   uatr_RTS_HSIOM_POS, uatr_HSIOM_UART_SEL);
#endif /* (uatr_UART_RTS_PIN) */

#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: uatr_UartStop
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
void uatr_UartStop(void)
{
#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (uatr_TX_SDA_MISO_PIN)
        if (uatr_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            uatr_SET_HSIOM_SEL(uatr_TX_SDA_MISO_HSIOM_REG, uatr_TX_SDA_MISO_HSIOM_MASK,
                                           uatr_TX_SDA_MISO_HSIOM_POS, uatr_HSIOM_GPIO_SEL);
        }
    #endif /* (uatr_TX_SDA_MISO_PIN_PIN) */

    #if (uatr_SS0_PIN)
        if (uatr_CHECK_SS0_PIN_USED)
        {
            /* Set output pin state after block is disabled */
            uatr_spi_ss0_Write(uatr_GET_UART_RTS_INACTIVE);

            /* Set GPIO to drive output pin */
            uatr_SET_HSIOM_SEL(uatr_SS0_HSIOM_REG, uatr_SS0_HSIOM_MASK,
                                           uatr_SS0_HSIOM_POS, uatr_HSIOM_GPIO_SEL);
        }
    #endif /* (uatr_SS0_PIN) */

#else
    #if (uatr_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        uatr_SET_HSIOM_SEL(uatr_TX_HSIOM_REG, uatr_TX_HSIOM_MASK,
                                       uatr_TX_HSIOM_POS, uatr_HSIOM_GPIO_SEL);
    #endif /* (uatr_UART_TX_PIN) */

    #if (uatr_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        uatr_rts_Write(uatr_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        uatr_SET_HSIOM_SEL(uatr_RTS_HSIOM_REG, uatr_RTS_HSIOM_MASK,
                                       uatr_RTS_HSIOM_POS, uatr_HSIOM_GPIO_SEL);
    #endif /* (uatr_UART_RTS_PIN) */

#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (uatr_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    uatr_UART_RX_CTRL_REG &= (uint32) ~uatr_UART_RX_CTRL_SKIP_START;
#endif /* (uatr_UART_WAKE_ENABLE_CONST) */
}


/*******************************************************************************
* Function Name: uatr_UartSetRxAddress
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
void uatr_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = uatr_RX_MATCH_REG;

    matchReg &= ((uint32) ~uatr_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & uatr_RX_MATCH_ADDR_MASK)); /* Set address  */

    uatr_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: uatr_UartSetRxAddressMask
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
void uatr_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = uatr_RX_MATCH_REG;

    matchReg &= ((uint32) ~uatr_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << uatr_RX_MATCH_MASK_POS));

    uatr_RX_MATCH_REG = matchReg;
}


#if(uatr_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: uatr_UartGetChar
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
    uint32 uatr_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != uatr_SpiUartGetRxBufferSize())
        {
            rxData = uatr_SpiUartReadRxData();
        }

        if (uatr_CHECK_INTR_RX(uatr_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            uatr_ClearRxInterruptSource(uatr_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: uatr_UartGetByte
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
    uint32 uatr_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (uatr_CHECK_RX_SW_BUFFER)
        {
            uatr_DisableInt();
        }
        #endif

        if (0u != uatr_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (uatr_CHECK_RX_SW_BUFFER)
            {            
                uatr_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = uatr_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = uatr_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            #if (uatr_CHECK_RX_SW_BUFFER)
            {
                uatr_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (uatr_GetRxInterruptSource() & uatr_INTR_RX_ERR);
        uatr_ClearRxInterruptSource(uatr_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: uatr_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   uatr_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   uatr_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void uatr_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                uatr_UART_FLOW_CTRL_REG |= (uint32)  uatr_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                uatr_UART_FLOW_CTRL_REG &= (uint32) ~uatr_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: uatr_UartSetRtsFifoLevel
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
        void uatr_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = uatr_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~uatr_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (uatr_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            uatr_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

#endif /* (uatr_UART_RX_DIRECTION) */


#if(uatr_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: uatr_UartPutString
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
    void uatr_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            uatr_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: uatr_UartPutCRLF
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
    void uatr_UartPutCRLF(uint32 txDataByte)
    {
        uatr_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        uatr_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        uatr_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: uatrSCB_UartEnableCts
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
        void uatr_UartEnableCts(void)
        {
            uatr_UART_FLOW_CTRL_REG |= (uint32)  uatr_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: uatr_UartDisableCts
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
        void uatr_UartDisableCts(void)
        {
            uatr_UART_FLOW_CTRL_REG &= (uint32) ~uatr_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: uatr_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   uatr_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   uatr_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void uatr_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                uatr_UART_FLOW_CTRL_REG |= (uint32)  uatr_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                uatr_UART_FLOW_CTRL_REG &= (uint32) ~uatr_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

#endif /* (uatr_UART_TX_DIRECTION) */


#if(uatr_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: uatr_UartSaveConfig
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
    void uatr_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        uatr_UART_RX_CTRL_REG |= uatr_UART_RX_CTRL_SKIP_START;

    #if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(uatr_MOSI_SCL_RX_WAKE_PIN)
            (void) uatr_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt();
        #endif /* (uatr_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(uatr_UART_RX_WAKE_PIN)
            (void) uatr_rx_wake_ClearInterrupt();
        #endif /* (uatr_UART_RX_WAKE_PIN) */
    #endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(uatr_UART_RX_WAKEUP_IRQ)
        uatr_RxWakeClearPendingInt();
        uatr_RxWakeEnableInt();
    #endif /* (uatr_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: uatr_UartRestoreConfig
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
    void uatr_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(uatr_UART_RX_WAKEUP_IRQ)
        uatr_RxWakeDisableInt();
    #endif /* (uatr_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (uatr_UART_WAKE_ENABLE_CONST) */


#if(uatr_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: uatr_UART_WAKEUP_ISR
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
    CY_ISR(uatr_UART_WAKEUP_ISR)
    {
    #ifdef uatr_UART_WAKEUP_ISR_ENTRY_CALLBACK
        uatr_UART_WAKEUP_ISR_EntryCallback();
    #endif /* uatr_UART_WAKEUP_ISR_ENTRY_CALLBACK */

        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by uatr_UartRestoreConfig() call.
        */
    #if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(uatr_MOSI_SCL_RX_WAKE_PIN)
            (void) uatr_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt();
        #endif /* (uatr_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(uatr_UART_RX_WAKE_PIN)
            (void) uatr_rx_wake_ClearInterrupt();
        #endif /* (uatr_UART_RX_WAKE_PIN) */
    #endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */

    #ifdef uatr_UART_WAKEUP_ISR_EXIT_CALLBACK
        uatr_UART_WAKEUP_ISR_ExitCallback();
    #endif /* uatr_UART_WAKEUP_ISR_EXIT_CALLBACK */
    }
#endif /* (uatr_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
