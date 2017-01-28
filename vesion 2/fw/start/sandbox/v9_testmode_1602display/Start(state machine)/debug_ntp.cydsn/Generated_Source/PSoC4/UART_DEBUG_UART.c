/***************************************************************************//**
* \file UART_DEBUG_UART.c
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

#include "UART_DEBUG_PVT.h"
#include "UART_DEBUG_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (UART_DEBUG_UART_WAKE_ENABLE_CONST && UART_DEBUG_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when UART_DEBUG_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 UART_DEBUG_skipStart = 1u;
    /** \} globals */
#endif /* (UART_DEBUG_UART_WAKE_ENABLE_CONST && UART_DEBUG_UART_RX_WAKEUP_IRQ) */

#if(UART_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const UART_DEBUG_UART_INIT_STRUCT UART_DEBUG_configUart =
    {
        UART_DEBUG_UART_SUB_MODE,
        UART_DEBUG_UART_DIRECTION,
        UART_DEBUG_UART_DATA_BITS_NUM,
        UART_DEBUG_UART_PARITY_TYPE,
        UART_DEBUG_UART_STOP_BITS_NUM,
        UART_DEBUG_UART_OVS_FACTOR,
        UART_DEBUG_UART_IRDA_LOW_POWER,
        UART_DEBUG_UART_MEDIAN_FILTER_ENABLE,
        UART_DEBUG_UART_RETRY_ON_NACK,
        UART_DEBUG_UART_IRDA_POLARITY,
        UART_DEBUG_UART_DROP_ON_PARITY_ERR,
        UART_DEBUG_UART_DROP_ON_FRAME_ERR,
        UART_DEBUG_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        UART_DEBUG_UART_MP_MODE_ENABLE,
        UART_DEBUG_UART_MP_ACCEPT_ADDRESS,
        UART_DEBUG_UART_MP_RX_ADDRESS,
        UART_DEBUG_UART_MP_RX_ADDRESS_MASK,
        (uint32) UART_DEBUG_SCB_IRQ_INTERNAL,
        UART_DEBUG_UART_INTR_RX_MASK,
        UART_DEBUG_UART_RX_TRIGGER_LEVEL,
        UART_DEBUG_UART_INTR_TX_MASK,
        UART_DEBUG_UART_TX_TRIGGER_LEVEL,
        (uint8) UART_DEBUG_UART_BYTE_MODE_ENABLE,
        (uint8) UART_DEBUG_UART_CTS_ENABLE,
        (uint8) UART_DEBUG_UART_CTS_POLARITY,
        (uint8) UART_DEBUG_UART_RTS_POLARITY,
        (uint8) UART_DEBUG_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: UART_DEBUG_UartInit
    ****************************************************************************//**
    *
    *  Configures the UART_DEBUG for UART operation.
    *
    *  This function is intended specifically to be used when the UART_DEBUG
    *  configuration is set to “Unconfigured UART_DEBUG” in the customizer.
    *  After initializing the UART_DEBUG in UART mode using this function,
    *  the component can be enabled using the UART_DEBUG_Start() or
    * UART_DEBUG_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void UART_DEBUG_UartInit(const UART_DEBUG_UART_INIT_STRUCT *config)
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

        #if !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (UART_DEBUG_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (UART_DEBUG_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1) */

            /* Configure pins */
            UART_DEBUG_SetPins(UART_DEBUG_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            UART_DEBUG_scbMode       = (uint8) UART_DEBUG_SCB_MODE_UART;
            UART_DEBUG_scbEnableWake = (uint8) config->enableWake;
            UART_DEBUG_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            UART_DEBUG_rxBuffer      =         config->rxBuffer;
            UART_DEBUG_rxDataBits    = (uint8) config->dataBits;
            UART_DEBUG_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            UART_DEBUG_txBuffer      =         config->txBuffer;
            UART_DEBUG_txDataBits    = (uint8) config->dataBits;
            UART_DEBUG_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(UART_DEBUG_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                UART_DEBUG_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (UART_DEBUG_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (UART_DEBUG_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                UART_DEBUG_CTRL_REG  = UART_DEBUG_GET_CTRL_OVS(config->oversample);
            }

            UART_DEBUG_CTRL_REG     |= UART_DEBUG_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             UART_DEBUG_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             UART_DEBUG_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            UART_DEBUG_UART_CTRL_REG = UART_DEBUG_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            UART_DEBUG_UART_RX_CTRL_REG = UART_DEBUG_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        UART_DEBUG_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        UART_DEBUG_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        UART_DEBUG_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        UART_DEBUG_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(UART_DEBUG_UART_PARITY_NONE != config->parity)
            {
               UART_DEBUG_UART_RX_CTRL_REG |= UART_DEBUG_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    UART_DEBUG_UART_RX_CTRL_PARITY_ENABLED;
            }

            UART_DEBUG_RX_CTRL_REG      = UART_DEBUG_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                UART_DEBUG_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                UART_DEBUG_GET_UART_RX_CTRL_ENABLED(config->direction);

            UART_DEBUG_RX_FIFO_CTRL_REG = UART_DEBUG_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            UART_DEBUG_RX_MATCH_REG     = UART_DEBUG_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                UART_DEBUG_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            UART_DEBUG_UART_TX_CTRL_REG = UART_DEBUG_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                UART_DEBUG_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(UART_DEBUG_UART_PARITY_NONE != config->parity)
            {
               UART_DEBUG_UART_TX_CTRL_REG |= UART_DEBUG_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    UART_DEBUG_UART_TX_CTRL_PARITY_ENABLED;
            }

            UART_DEBUG_TX_CTRL_REG      = UART_DEBUG_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                UART_DEBUG_GET_UART_TX_CTRL_ENABLED(config->direction);

            UART_DEBUG_TX_FIFO_CTRL_REG = UART_DEBUG_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1)
            UART_DEBUG_UART_FLOW_CTRL_REG = UART_DEBUG_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            UART_DEBUG_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            UART_DEBUG_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            UART_DEBUG_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (UART_DEBUG_ISR_NUMBER);
            CyIntSetPriority(UART_DEBUG_ISR_NUMBER, UART_DEBUG_ISR_PRIORITY);
            (void) CyIntSetVector(UART_DEBUG_ISR_NUMBER, &UART_DEBUG_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(UART_DEBUG_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (UART_DEBUG_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(UART_DEBUG_RX_WAKE_ISR_NUMBER, UART_DEBUG_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(UART_DEBUG_RX_WAKE_ISR_NUMBER, &UART_DEBUG_UART_WAKEUP_ISR);
        #endif /* (UART_DEBUG_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            UART_DEBUG_INTR_I2C_EC_MASK_REG = UART_DEBUG_NO_INTR_SOURCES;
            UART_DEBUG_INTR_SPI_EC_MASK_REG = UART_DEBUG_NO_INTR_SOURCES;
            UART_DEBUG_INTR_SLAVE_MASK_REG  = UART_DEBUG_NO_INTR_SOURCES;
            UART_DEBUG_INTR_MASTER_MASK_REG = UART_DEBUG_NO_INTR_SOURCES;
            UART_DEBUG_INTR_RX_MASK_REG     = config->rxInterruptMask;
            UART_DEBUG_INTR_TX_MASK_REG     = config->txInterruptMask;
        
            /* Configure TX interrupt sources to restore. */
            UART_DEBUG_IntrTxMask = LO16(UART_DEBUG_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            UART_DEBUG_rxBufferHead     = 0u;
            UART_DEBUG_rxBufferTail     = 0u;
            UART_DEBUG_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            UART_DEBUG_txBufferHead = 0u;
            UART_DEBUG_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: UART_DEBUG_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void UART_DEBUG_UartInit(void)
    {
        /* Configure UART interface */
        UART_DEBUG_CTRL_REG = UART_DEBUG_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        UART_DEBUG_UART_CTRL_REG = UART_DEBUG_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        UART_DEBUG_UART_RX_CTRL_REG = UART_DEBUG_UART_DEFAULT_UART_RX_CTRL;
        UART_DEBUG_RX_CTRL_REG      = UART_DEBUG_UART_DEFAULT_RX_CTRL;
        UART_DEBUG_RX_FIFO_CTRL_REG = UART_DEBUG_UART_DEFAULT_RX_FIFO_CTRL;
        UART_DEBUG_RX_MATCH_REG     = UART_DEBUG_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        UART_DEBUG_UART_TX_CTRL_REG = UART_DEBUG_UART_DEFAULT_UART_TX_CTRL;
        UART_DEBUG_TX_CTRL_REG      = UART_DEBUG_UART_DEFAULT_TX_CTRL;
        UART_DEBUG_TX_FIFO_CTRL_REG = UART_DEBUG_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1)
        UART_DEBUG_UART_FLOW_CTRL_REG = UART_DEBUG_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(UART_DEBUG_SCB_IRQ_INTERNAL)
        CyIntDisable    (UART_DEBUG_ISR_NUMBER);
        CyIntSetPriority(UART_DEBUG_ISR_NUMBER, UART_DEBUG_ISR_PRIORITY);
        (void) CyIntSetVector(UART_DEBUG_ISR_NUMBER, &UART_DEBUG_SPI_UART_ISR);
    #endif /* (UART_DEBUG_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(UART_DEBUG_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (UART_DEBUG_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(UART_DEBUG_RX_WAKE_ISR_NUMBER, UART_DEBUG_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(UART_DEBUG_RX_WAKE_ISR_NUMBER, &UART_DEBUG_UART_WAKEUP_ISR);
    #endif /* (UART_DEBUG_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        UART_DEBUG_INTR_I2C_EC_MASK_REG = UART_DEBUG_UART_DEFAULT_INTR_I2C_EC_MASK;
        UART_DEBUG_INTR_SPI_EC_MASK_REG = UART_DEBUG_UART_DEFAULT_INTR_SPI_EC_MASK;
        UART_DEBUG_INTR_SLAVE_MASK_REG  = UART_DEBUG_UART_DEFAULT_INTR_SLAVE_MASK;
        UART_DEBUG_INTR_MASTER_MASK_REG = UART_DEBUG_UART_DEFAULT_INTR_MASTER_MASK;
        UART_DEBUG_INTR_RX_MASK_REG     = UART_DEBUG_UART_DEFAULT_INTR_RX_MASK;
        UART_DEBUG_INTR_TX_MASK_REG     = UART_DEBUG_UART_DEFAULT_INTR_TX_MASK;
    
        /* Configure TX interrupt sources to restore. */
        UART_DEBUG_IntrTxMask = LO16(UART_DEBUG_INTR_TX_MASK_REG);

    #if(UART_DEBUG_INTERNAL_RX_SW_BUFFER_CONST)
        UART_DEBUG_rxBufferHead     = 0u;
        UART_DEBUG_rxBufferTail     = 0u;
        UART_DEBUG_rxBufferOverflow = 0u;
    #endif /* (UART_DEBUG_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(UART_DEBUG_INTERNAL_TX_SW_BUFFER_CONST)
        UART_DEBUG_txBufferHead = 0u;
        UART_DEBUG_txBufferTail = 0u;
    #endif /* (UART_DEBUG_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (UART_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: UART_DEBUG_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void UART_DEBUG_UartPostEnable(void)
{
#if (UART_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (UART_DEBUG_TX_SCL_MISO_PIN)
        if (UART_DEBUG_CHECK_TX_SCL_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            UART_DEBUG_SET_HSIOM_SEL(UART_DEBUG_TX_SCL_MISO_HSIOM_REG, UART_DEBUG_TX_SCL_MISO_HSIOM_MASK,
                                           UART_DEBUG_TX_SCL_MISO_HSIOM_POS, UART_DEBUG_TX_SCL_MISO_HSIOM_SEL_UART);
        }
    #endif /* (UART_DEBUG_TX_SCL_MISO_PIN_PIN) */

    #if !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1)
        #if (UART_DEBUG_RTS_SS0_PIN)
            if (UART_DEBUG_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                UART_DEBUG_SET_HSIOM_SEL(UART_DEBUG_RTS_SS0_HSIOM_REG, UART_DEBUG_RTS_SS0_HSIOM_MASK,
                                               UART_DEBUG_RTS_SS0_HSIOM_POS, UART_DEBUG_RTS_SS0_HSIOM_SEL_UART);
            }
        #endif /* (UART_DEBUG_RTS_SS0_PIN) */
    #endif /* !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1) */

#else
    #if (UART_DEBUG_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        UART_DEBUG_SET_HSIOM_SEL(UART_DEBUG_TX_HSIOM_REG, UART_DEBUG_TX_HSIOM_MASK,
                                       UART_DEBUG_TX_HSIOM_POS, UART_DEBUG_TX_HSIOM_SEL_UART);
    #endif /* (UART_DEBUG_UART_TX_PIN) */

    #if (UART_DEBUG_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        UART_DEBUG_SET_HSIOM_SEL(UART_DEBUG_RTS_HSIOM_REG, UART_DEBUG_RTS_HSIOM_MASK,
                                       UART_DEBUG_RTS_HSIOM_POS, UART_DEBUG_RTS_HSIOM_SEL_UART);
    #endif /* (UART_DEBUG_UART_RTS_PIN) */
#endif /* (UART_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    UART_DEBUG_SetTxInterruptMode(UART_DEBUG_IntrTxMask);
}


/*******************************************************************************
* Function Name: UART_DEBUG_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void UART_DEBUG_UartStop(void)
{
#if(UART_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (UART_DEBUG_TX_SCL_MISO_PIN)
        if (UART_DEBUG_CHECK_TX_SCL_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            UART_DEBUG_SET_HSIOM_SEL(UART_DEBUG_TX_SCL_MISO_HSIOM_REG, UART_DEBUG_TX_SCL_MISO_HSIOM_MASK,
                                           UART_DEBUG_TX_SCL_MISO_HSIOM_POS, UART_DEBUG_TX_SCL_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (UART_DEBUG_TX_SCL_MISO_PIN_PIN) */

    #if !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1)
        #if (UART_DEBUG_RTS_SS0_PIN)
            if (UART_DEBUG_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                UART_DEBUG_uart_rts_spi_ss0_Write(UART_DEBUG_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                UART_DEBUG_SET_HSIOM_SEL(UART_DEBUG_RTS_SS0_HSIOM_REG, UART_DEBUG_RTS_SS0_HSIOM_MASK,
                                               UART_DEBUG_RTS_SS0_HSIOM_POS, UART_DEBUG_RTS_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (UART_DEBUG_RTS_SS0_PIN) */
    #endif /* !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1) */

#else
    #if (UART_DEBUG_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        UART_DEBUG_SET_HSIOM_SEL(UART_DEBUG_TX_HSIOM_REG, UART_DEBUG_TX_HSIOM_MASK,
                                       UART_DEBUG_TX_HSIOM_POS, UART_DEBUG_TX_HSIOM_SEL_GPIO);
    #endif /* (UART_DEBUG_UART_TX_PIN) */

    #if (UART_DEBUG_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        UART_DEBUG_rts_Write(UART_DEBUG_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        UART_DEBUG_SET_HSIOM_SEL(UART_DEBUG_RTS_HSIOM_REG, UART_DEBUG_RTS_HSIOM_MASK,
                                       UART_DEBUG_RTS_HSIOM_POS, UART_DEBUG_RTS_HSIOM_SEL_GPIO);
    #endif /* (UART_DEBUG_UART_RTS_PIN) */

#endif /* (UART_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (UART_DEBUG_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    UART_DEBUG_UART_RX_CTRL_REG &= (uint32) ~UART_DEBUG_UART_RX_CTRL_SKIP_START;
#endif /* (UART_DEBUG_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    UART_DEBUG_IntrTxMask = LO16(UART_DEBUG_GetTxInterruptMode() & UART_DEBUG_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: UART_DEBUG_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void UART_DEBUG_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = UART_DEBUG_RX_MATCH_REG;

    matchReg &= ((uint32) ~UART_DEBUG_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & UART_DEBUG_RX_MATCH_ADDR_MASK)); /* Set address  */

    UART_DEBUG_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: UART_DEBUG_UartSetRxAddressMask
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
void UART_DEBUG_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = UART_DEBUG_RX_MATCH_REG;

    matchReg &= ((uint32) ~UART_DEBUG_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << UART_DEBUG_RX_MATCH_MASK_POS));

    UART_DEBUG_RX_MATCH_REG = matchReg;
}


#if(UART_DEBUG_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: UART_DEBUG_UartGetChar
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
    *   Check UART_DEBUG_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 UART_DEBUG_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != UART_DEBUG_SpiUartGetRxBufferSize())
        {
            rxData = UART_DEBUG_SpiUartReadRxData();
        }

        if (UART_DEBUG_CHECK_INTR_RX(UART_DEBUG_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            UART_DEBUG_ClearRxInterruptSource(UART_DEBUG_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: UART_DEBUG_UartGetByte
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
    *   - UART_DEBUG_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - UART_DEBUG_UART_RX_UNDERFLOW	Attempt to read from an empty
    *     receiver FIFO.
    *   - UART_DEBUG_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - UART_DEBUG_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check UART_DEBUG_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 UART_DEBUG_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (UART_DEBUG_CHECK_RX_SW_BUFFER)
        {
            UART_DEBUG_DisableInt();
        }
        #endif

        if (0u != UART_DEBUG_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (UART_DEBUG_CHECK_RX_SW_BUFFER)
            {
                UART_DEBUG_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = UART_DEBUG_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = UART_DEBUG_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            #if (UART_DEBUG_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                UART_DEBUG_ClearRxInterruptSource(UART_DEBUG_INTR_RX_NOT_EMPTY);

                UART_DEBUG_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (UART_DEBUG_GetRxInterruptSource() & UART_DEBUG_INTR_RX_ERR);
        UART_DEBUG_ClearRxInterruptSource(UART_DEBUG_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: UART_DEBUG_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - UART_DEBUG_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - UART_DEBUG_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void UART_DEBUG_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                UART_DEBUG_UART_FLOW_CTRL_REG |= (uint32)  UART_DEBUG_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                UART_DEBUG_UART_FLOW_CTRL_REG &= (uint32) ~UART_DEBUG_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: UART_DEBUG_UartSetRtsFifoLevel
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
        void UART_DEBUG_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = UART_DEBUG_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~UART_DEBUG_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (UART_DEBUG_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            UART_DEBUG_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1) */

#endif /* (UART_DEBUG_UART_RX_DIRECTION) */


#if(UART_DEBUG_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: UART_DEBUG_UartPutString
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
    void UART_DEBUG_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            UART_DEBUG_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: UART_DEBUG_UartPutCRLF
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
    void UART_DEBUG_UartPutCRLF(uint32 txDataByte)
    {
        UART_DEBUG_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        UART_DEBUG_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        UART_DEBUG_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: UART_DEBUGSCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void UART_DEBUG_UartEnableCts(void)
        {
            UART_DEBUG_UART_FLOW_CTRL_REG |= (uint32)  UART_DEBUG_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: UART_DEBUG_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void UART_DEBUG_UartDisableCts(void)
        {
            UART_DEBUG_UART_FLOW_CTRL_REG &= (uint32) ~UART_DEBUG_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: UART_DEBUG_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of CTS output signal.
        *   - UART_DEBUG_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - UART_DEBUG_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void UART_DEBUG_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                UART_DEBUG_UART_FLOW_CTRL_REG |= (uint32)  UART_DEBUG_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                UART_DEBUG_UART_FLOW_CTRL_REG &= (uint32) ~UART_DEBUG_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(UART_DEBUG_CY_SCBIP_V0 || UART_DEBUG_CY_SCBIP_V1) */

#endif /* (UART_DEBUG_UART_TX_DIRECTION) */


#if (UART_DEBUG_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: UART_DEBUG_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be 
    *  cleared by this API.
    *
    *******************************************************************************/
    void UART_DEBUG_UartSaveConfig(void)
    {
    #if (UART_DEBUG_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != UART_DEBUG_skipStart)
        {
            UART_DEBUG_UART_RX_CTRL_REG |= (uint32)  UART_DEBUG_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            UART_DEBUG_UART_RX_CTRL_REG &= (uint32) ~UART_DEBUG_UART_RX_CTRL_SKIP_START;
        }
        
        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        UART_DEBUG_CLEAR_UART_RX_WAKE_INTR;
        UART_DEBUG_RxWakeClearPendingInt();
        UART_DEBUG_RxWakeEnableInt();
    #endif /* (UART_DEBUG_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: UART_DEBUG_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void UART_DEBUG_UartRestoreConfig(void)
    {
    #if (UART_DEBUG_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        UART_DEBUG_RxWakeDisableInt();
    #endif /* (UART_DEBUG_UART_RX_WAKEUP_IRQ) */
    }


    #if (UART_DEBUG_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: UART_DEBUG_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(UART_DEBUG_UART_WAKEUP_ISR)
        {
        #ifdef UART_DEBUG_UART_WAKEUP_ISR_ENTRY_CALLBACK
            UART_DEBUG_UART_WAKEUP_ISR_EntryCallback();
        #endif /* UART_DEBUG_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            UART_DEBUG_CLEAR_UART_RX_WAKE_INTR;

        #ifdef UART_DEBUG_UART_WAKEUP_ISR_EXIT_CALLBACK
            UART_DEBUG_UART_WAKEUP_ISR_ExitCallback();
        #endif /* UART_DEBUG_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (UART_DEBUG_UART_RX_WAKEUP_IRQ) */
#endif /* (UART_DEBUG_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
