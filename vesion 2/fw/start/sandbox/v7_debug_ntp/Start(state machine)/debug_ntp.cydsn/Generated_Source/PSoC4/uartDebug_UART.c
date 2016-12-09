/***************************************************************************//**
* \file uartDebug_UART.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
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
#include "cyapicallbacks.h"

#if (uartDebug_UART_WAKE_ENABLE_CONST && uartDebug_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when uartDebug_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 uartDebug_skipStart = 1u;
    /** \} globals */
#endif /* (uartDebug_UART_WAKE_ENABLE_CONST && uartDebug_UART_RX_WAKEUP_IRQ) */

#if(uartDebug_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const uartDebug_UART_INIT_STRUCT uartDebug_configUart =
    {
        uartDebug_UART_SUB_MODE,
        uartDebug_UART_DIRECTION,
        uartDebug_UART_DATA_BITS_NUM,
        uartDebug_UART_PARITY_TYPE,
        uartDebug_UART_STOP_BITS_NUM,
        uartDebug_UART_OVS_FACTOR,
        uartDebug_UART_IRDA_LOW_POWER,
        uartDebug_UART_MEDIAN_FILTER_ENABLE,
        uartDebug_UART_RETRY_ON_NACK,
        uartDebug_UART_IRDA_POLARITY,
        uartDebug_UART_DROP_ON_PARITY_ERR,
        uartDebug_UART_DROP_ON_FRAME_ERR,
        uartDebug_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        uartDebug_UART_MP_MODE_ENABLE,
        uartDebug_UART_MP_ACCEPT_ADDRESS,
        uartDebug_UART_MP_RX_ADDRESS,
        uartDebug_UART_MP_RX_ADDRESS_MASK,
        (uint32) uartDebug_SCB_IRQ_INTERNAL,
        uartDebug_UART_INTR_RX_MASK,
        uartDebug_UART_RX_TRIGGER_LEVEL,
        uartDebug_UART_INTR_TX_MASK,
        uartDebug_UART_TX_TRIGGER_LEVEL,
        (uint8) uartDebug_UART_BYTE_MODE_ENABLE,
        (uint8) uartDebug_UART_CTS_ENABLE,
        (uint8) uartDebug_UART_CTS_POLARITY,
        (uint8) uartDebug_UART_RTS_POLARITY,
        (uint8) uartDebug_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: uartDebug_UartInit
    ****************************************************************************//**
    *
    *  Configures the uartDebug for UART operation.
    *
    *  This function is intended specifically to be used when the uartDebug
    *  configuration is set to “Unconfigured uartDebug” in the customizer.
    *  After initializing the uartDebug in UART mode using this function,
    *  the component can be enabled using the uartDebug_Start() or
    * uartDebug_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void uartDebug_UartInit(const uartDebug_UART_INIT_STRUCT *config)
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

        #if !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (uartDebug_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (uartDebug_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1) */

            /* Configure pins */
            uartDebug_SetPins(uartDebug_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            uartDebug_scbMode       = (uint8) uartDebug_SCB_MODE_UART;
            uartDebug_scbEnableWake = (uint8) config->enableWake;
            uartDebug_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            uartDebug_rxBuffer      =         config->rxBuffer;
            uartDebug_rxDataBits    = (uint8) config->dataBits;
            uartDebug_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            uartDebug_txBuffer      =         config->txBuffer;
            uartDebug_txDataBits    = (uint8) config->dataBits;
            uartDebug_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(uartDebug_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                uartDebug_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (uartDebug_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (uartDebug_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                uartDebug_CTRL_REG  = uartDebug_GET_CTRL_OVS(config->oversample);
            }

            uartDebug_CTRL_REG     |= uartDebug_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             uartDebug_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             uartDebug_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            uartDebug_UART_CTRL_REG = uartDebug_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            uartDebug_UART_RX_CTRL_REG = uartDebug_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        uartDebug_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        uartDebug_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        uartDebug_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        uartDebug_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(uartDebug_UART_PARITY_NONE != config->parity)
            {
               uartDebug_UART_RX_CTRL_REG |= uartDebug_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    uartDebug_UART_RX_CTRL_PARITY_ENABLED;
            }

            uartDebug_RX_CTRL_REG      = uartDebug_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                uartDebug_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                uartDebug_GET_UART_RX_CTRL_ENABLED(config->direction);

            uartDebug_RX_FIFO_CTRL_REG = uartDebug_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            uartDebug_RX_MATCH_REG     = uartDebug_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                uartDebug_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            uartDebug_UART_TX_CTRL_REG = uartDebug_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                uartDebug_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(uartDebug_UART_PARITY_NONE != config->parity)
            {
               uartDebug_UART_TX_CTRL_REG |= uartDebug_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    uartDebug_UART_TX_CTRL_PARITY_ENABLED;
            }

            uartDebug_TX_CTRL_REG      = uartDebug_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                uartDebug_GET_UART_TX_CTRL_ENABLED(config->direction);

            uartDebug_TX_FIFO_CTRL_REG = uartDebug_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1)
            uartDebug_UART_FLOW_CTRL_REG = uartDebug_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            uartDebug_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            uartDebug_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            uartDebug_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (uartDebug_ISR_NUMBER);
            CyIntSetPriority(uartDebug_ISR_NUMBER, uartDebug_ISR_PRIORITY);
            (void) CyIntSetVector(uartDebug_ISR_NUMBER, &uartDebug_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(uartDebug_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (uartDebug_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(uartDebug_RX_WAKE_ISR_NUMBER, uartDebug_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(uartDebug_RX_WAKE_ISR_NUMBER, &uartDebug_UART_WAKEUP_ISR);
        #endif /* (uartDebug_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            uartDebug_INTR_I2C_EC_MASK_REG = uartDebug_NO_INTR_SOURCES;
            uartDebug_INTR_SPI_EC_MASK_REG = uartDebug_NO_INTR_SOURCES;
            uartDebug_INTR_SLAVE_MASK_REG  = uartDebug_NO_INTR_SOURCES;
            uartDebug_INTR_MASTER_MASK_REG = uartDebug_NO_INTR_SOURCES;
            uartDebug_INTR_RX_MASK_REG     = config->rxInterruptMask;
            uartDebug_INTR_TX_MASK_REG     = config->txInterruptMask;
        
            /* Configure TX interrupt sources to restore. */
            uartDebug_IntrTxMask = LO16(uartDebug_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            uartDebug_rxBufferHead     = 0u;
            uartDebug_rxBufferTail     = 0u;
            uartDebug_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            uartDebug_txBufferHead = 0u;
            uartDebug_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: uartDebug_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void uartDebug_UartInit(void)
    {
        /* Configure UART interface */
        uartDebug_CTRL_REG = uartDebug_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        uartDebug_UART_CTRL_REG = uartDebug_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        uartDebug_UART_RX_CTRL_REG = uartDebug_UART_DEFAULT_UART_RX_CTRL;
        uartDebug_RX_CTRL_REG      = uartDebug_UART_DEFAULT_RX_CTRL;
        uartDebug_RX_FIFO_CTRL_REG = uartDebug_UART_DEFAULT_RX_FIFO_CTRL;
        uartDebug_RX_MATCH_REG     = uartDebug_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        uartDebug_UART_TX_CTRL_REG = uartDebug_UART_DEFAULT_UART_TX_CTRL;
        uartDebug_TX_CTRL_REG      = uartDebug_UART_DEFAULT_TX_CTRL;
        uartDebug_TX_FIFO_CTRL_REG = uartDebug_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1)
        uartDebug_UART_FLOW_CTRL_REG = uartDebug_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(uartDebug_SCB_IRQ_INTERNAL)
        CyIntDisable    (uartDebug_ISR_NUMBER);
        CyIntSetPriority(uartDebug_ISR_NUMBER, uartDebug_ISR_PRIORITY);
        (void) CyIntSetVector(uartDebug_ISR_NUMBER, &uartDebug_SPI_UART_ISR);
    #endif /* (uartDebug_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(uartDebug_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (uartDebug_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(uartDebug_RX_WAKE_ISR_NUMBER, uartDebug_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(uartDebug_RX_WAKE_ISR_NUMBER, &uartDebug_UART_WAKEUP_ISR);
    #endif /* (uartDebug_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        uartDebug_INTR_I2C_EC_MASK_REG = uartDebug_UART_DEFAULT_INTR_I2C_EC_MASK;
        uartDebug_INTR_SPI_EC_MASK_REG = uartDebug_UART_DEFAULT_INTR_SPI_EC_MASK;
        uartDebug_INTR_SLAVE_MASK_REG  = uartDebug_UART_DEFAULT_INTR_SLAVE_MASK;
        uartDebug_INTR_MASTER_MASK_REG = uartDebug_UART_DEFAULT_INTR_MASTER_MASK;
        uartDebug_INTR_RX_MASK_REG     = uartDebug_UART_DEFAULT_INTR_RX_MASK;
        uartDebug_INTR_TX_MASK_REG     = uartDebug_UART_DEFAULT_INTR_TX_MASK;
    
        /* Configure TX interrupt sources to restore. */
        uartDebug_IntrTxMask = LO16(uartDebug_INTR_TX_MASK_REG);

    #if(uartDebug_INTERNAL_RX_SW_BUFFER_CONST)
        uartDebug_rxBufferHead     = 0u;
        uartDebug_rxBufferTail     = 0u;
        uartDebug_rxBufferOverflow = 0u;
    #endif /* (uartDebug_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(uartDebug_INTERNAL_TX_SW_BUFFER_CONST)
        uartDebug_txBufferHead = 0u;
        uartDebug_txBufferTail = 0u;
    #endif /* (uartDebug_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: uartDebug_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void uartDebug_UartPostEnable(void)
{
#if (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (uartDebug_TX_SCL_MISO_PIN)
        if (uartDebug_CHECK_TX_SCL_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            uartDebug_SET_HSIOM_SEL(uartDebug_TX_SCL_MISO_HSIOM_REG, uartDebug_TX_SCL_MISO_HSIOM_MASK,
                                           uartDebug_TX_SCL_MISO_HSIOM_POS, uartDebug_TX_SCL_MISO_HSIOM_SEL_UART);
        }
    #endif /* (uartDebug_TX_SCL_MISO_PIN_PIN) */

    #if !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1)
        #if (uartDebug_RTS_SS0_PIN)
            if (uartDebug_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                uartDebug_SET_HSIOM_SEL(uartDebug_RTS_SS0_HSIOM_REG, uartDebug_RTS_SS0_HSIOM_MASK,
                                               uartDebug_RTS_SS0_HSIOM_POS, uartDebug_RTS_SS0_HSIOM_SEL_UART);
            }
        #endif /* (uartDebug_RTS_SS0_PIN) */
    #endif /* !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1) */

#else
    #if (uartDebug_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        uartDebug_SET_HSIOM_SEL(uartDebug_TX_HSIOM_REG, uartDebug_TX_HSIOM_MASK,
                                       uartDebug_TX_HSIOM_POS, uartDebug_TX_HSIOM_SEL_UART);
    #endif /* (uartDebug_UART_TX_PIN) */

    #if (uartDebug_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        uartDebug_SET_HSIOM_SEL(uartDebug_RTS_HSIOM_REG, uartDebug_RTS_HSIOM_MASK,
                                       uartDebug_RTS_HSIOM_POS, uartDebug_RTS_HSIOM_SEL_UART);
    #endif /* (uartDebug_UART_RTS_PIN) */
#endif /* (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    uartDebug_SetTxInterruptMode(uartDebug_IntrTxMask);
}


/*******************************************************************************
* Function Name: uartDebug_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void uartDebug_UartStop(void)
{
#if(uartDebug_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (uartDebug_TX_SCL_MISO_PIN)
        if (uartDebug_CHECK_TX_SCL_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            uartDebug_SET_HSIOM_SEL(uartDebug_TX_SCL_MISO_HSIOM_REG, uartDebug_TX_SCL_MISO_HSIOM_MASK,
                                           uartDebug_TX_SCL_MISO_HSIOM_POS, uartDebug_TX_SCL_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (uartDebug_TX_SCL_MISO_PIN_PIN) */

    #if !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1)
        #if (uartDebug_RTS_SS0_PIN)
            if (uartDebug_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                uartDebug_uart_rts_spi_ss0_Write(uartDebug_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                uartDebug_SET_HSIOM_SEL(uartDebug_RTS_SS0_HSIOM_REG, uartDebug_RTS_SS0_HSIOM_MASK,
                                               uartDebug_RTS_SS0_HSIOM_POS, uartDebug_RTS_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (uartDebug_RTS_SS0_PIN) */
    #endif /* !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1) */

#else
    #if (uartDebug_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        uartDebug_SET_HSIOM_SEL(uartDebug_TX_HSIOM_REG, uartDebug_TX_HSIOM_MASK,
                                       uartDebug_TX_HSIOM_POS, uartDebug_TX_HSIOM_SEL_GPIO);
    #endif /* (uartDebug_UART_TX_PIN) */

    #if (uartDebug_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        uartDebug_rts_Write(uartDebug_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        uartDebug_SET_HSIOM_SEL(uartDebug_RTS_HSIOM_REG, uartDebug_RTS_HSIOM_MASK,
                                       uartDebug_RTS_HSIOM_POS, uartDebug_RTS_HSIOM_SEL_GPIO);
    #endif /* (uartDebug_UART_RTS_PIN) */

#endif /* (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (uartDebug_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    uartDebug_UART_RX_CTRL_REG &= (uint32) ~uartDebug_UART_RX_CTRL_SKIP_START;
#endif /* (uartDebug_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    uartDebug_IntrTxMask = LO16(uartDebug_GetTxInterruptMode() & uartDebug_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: uartDebug_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void uartDebug_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = uartDebug_RX_MATCH_REG;

    matchReg &= ((uint32) ~uartDebug_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & uartDebug_RX_MATCH_ADDR_MASK)); /* Set address  */

    uartDebug_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: uartDebug_UartSetRxAddressMask
****************************************************************************//**
*
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
*  \param addressMask: Address mask.
*   - Bit value 0 – excludes bit from address comparison.
*   - Bit value 1 – the bit needs to match with the corresponding bit
*     of the address.
*
*******************************************************************************/
void uartDebug_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = uartDebug_RX_MATCH_REG;

    matchReg &= ((uint32) ~uartDebug_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << uartDebug_RX_MATCH_MASK_POS));

    uartDebug_RX_MATCH_REG = matchReg;
}


#if(uartDebug_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: uartDebug_UartGetChar
    ****************************************************************************//**
    *
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char where
    *  1 to 255 are valid characters and 0 indicates an error occurred or no data
    *  is present.
    *  - RX software buffer is disabled: Returns data element retrieved from RX
    *    FIFO.
    *  - RX software buffer is enabled: Returns data element from the software
    *    receive buffer.
    *
    *  \return
    *   Next data element from the receive buffer. ASCII character values from
    *   1 to 255 are valid. A returned zero signifies an error condition or no
    *   data available.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check uartDebug_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 uartDebug_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != uartDebug_SpiUartGetRxBufferSize())
        {
            rxData = uartDebug_SpiUartReadRxData();
        }

        if (uartDebug_CHECK_INTR_RX(uartDebug_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            uartDebug_ClearRxInterruptSource(uartDebug_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: uartDebug_UartGetByte
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    *  \return
    *   Bits 7-0 contain the next data element from the receive buffer and
    *   other bits contain the error condition.
    *   - uartDebug_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - uartDebug_UART_RX_UNDERFLOW	Attempt to read from an empty
    *     receiver FIFO.
    *   - uartDebug_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - uartDebug_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check uartDebug_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 uartDebug_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (uartDebug_CHECK_RX_SW_BUFFER)
        {
            uartDebug_DisableInt();
        }
        #endif

        if (0u != uartDebug_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (uartDebug_CHECK_RX_SW_BUFFER)
            {
                uartDebug_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = uartDebug_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = uartDebug_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            #if (uartDebug_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                uartDebug_ClearRxInterruptSource(uartDebug_INTR_RX_NOT_EMPTY);

                uartDebug_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (uartDebug_GetRxInterruptSource() & uartDebug_INTR_RX_ERR);
        uartDebug_ClearRxInterruptSource(uartDebug_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: uartDebug_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - uartDebug_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - uartDebug_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void uartDebug_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                uartDebug_UART_FLOW_CTRL_REG |= (uint32)  uartDebug_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                uartDebug_UART_FLOW_CTRL_REG &= (uint32) ~uartDebug_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: uartDebug_UartSetRtsFifoLevel
        ****************************************************************************//**
        *
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param level: Level in the RX FIFO for RTS signal activation.
        *   The range of valid level values is between 0 and RX FIFO depth - 1.
        *   Setting level value to 0 disables RTS signal activation.
        *
        *******************************************************************************/
        void uartDebug_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = uartDebug_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~uartDebug_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (uartDebug_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            uartDebug_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1) */

#endif /* (uartDebug_UART_RX_DIRECTION) */


#if(uartDebug_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: uartDebug_UartPutString
    ****************************************************************************//**
    *
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  requested data in transmit buffer.
    *
    *  \param string: pointer to the null terminated string array to be placed in the
    *   transmit buffer.
    *
    *******************************************************************************/
    void uartDebug_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            uartDebug_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: uartDebug_UartPutCRLF
    ****************************************************************************//**
    *
    *  Places byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) in the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *
    *******************************************************************************/
    void uartDebug_UartPutCRLF(uint32 txDataByte)
    {
        uartDebug_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        uartDebug_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        uartDebug_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: uartDebugSCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void uartDebug_UartEnableCts(void)
        {
            uartDebug_UART_FLOW_CTRL_REG |= (uint32)  uartDebug_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: uartDebug_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void uartDebug_UartDisableCts(void)
        {
            uartDebug_UART_FLOW_CTRL_REG &= (uint32) ~uartDebug_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: uartDebug_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of CTS output signal.
        *   - uartDebug_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - uartDebug_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void uartDebug_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                uartDebug_UART_FLOW_CTRL_REG |= (uint32)  uartDebug_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                uartDebug_UART_FLOW_CTRL_REG &= (uint32) ~uartDebug_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1) */

#endif /* (uartDebug_UART_TX_DIRECTION) */


#if (uartDebug_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: uartDebug_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be 
    *  cleared by this API.
    *
    *******************************************************************************/
    void uartDebug_UartSaveConfig(void)
    {
    #if (uartDebug_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != uartDebug_skipStart)
        {
            uartDebug_UART_RX_CTRL_REG |= (uint32)  uartDebug_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            uartDebug_UART_RX_CTRL_REG &= (uint32) ~uartDebug_UART_RX_CTRL_SKIP_START;
        }
        
        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        uartDebug_CLEAR_UART_RX_WAKE_INTR;
        uartDebug_RxWakeClearPendingInt();
        uartDebug_RxWakeEnableInt();
    #endif /* (uartDebug_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: uartDebug_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void uartDebug_UartRestoreConfig(void)
    {
    #if (uartDebug_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        uartDebug_RxWakeDisableInt();
    #endif /* (uartDebug_UART_RX_WAKEUP_IRQ) */
    }


    #if (uartDebug_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: uartDebug_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(uartDebug_UART_WAKEUP_ISR)
        {
        #ifdef uartDebug_UART_WAKEUP_ISR_ENTRY_CALLBACK
            uartDebug_UART_WAKEUP_ISR_EntryCallback();
        #endif /* uartDebug_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            uartDebug_CLEAR_UART_RX_WAKE_INTR;

        #ifdef uartDebug_UART_WAKEUP_ISR_EXIT_CALLBACK
            uartDebug_UART_WAKEUP_ISR_ExitCallback();
        #endif /* uartDebug_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (uartDebug_UART_RX_WAKEUP_IRQ) */
#endif /* (uartDebug_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
