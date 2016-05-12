/*******************************************************************************
* File Name: uatr.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component.
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

#if (uatr_SCB_MODE_I2C_INC)
    #include "uatr_I2C_PVT.h"
#endif /* (uatr_SCB_MODE_I2C_INC) */

#if (uatr_SCB_MODE_EZI2C_INC)
    #include "uatr_EZI2C_PVT.h"
#endif /* (uatr_SCB_MODE_EZI2C_INC) */

#if (uatr_SCB_MODE_SPI_INC || uatr_SCB_MODE_UART_INC)
    #include "uatr_SPI_UART_PVT.h"
#endif /* (uatr_SCB_MODE_SPI_INC || uatr_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 uatr_scbMode = uatr_SCB_MODE_UNCONFIG;
    uint8 uatr_scbEnableWake;
    uint8 uatr_scbEnableIntr;

    /* I2C configuration variables */
    uint8 uatr_mode;
    uint8 uatr_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * uatr_rxBuffer;
    uint8  uatr_rxDataBits;
    uint32 uatr_rxBufferSize;

    volatile uint8 * uatr_txBuffer;
    uint8  uatr_txDataBits;
    uint32 uatr_txBufferSize;

    /* EZI2C configuration variables */
    uint8 uatr_numberOfAddr;
    uint8 uatr_subAddrSize;
#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 uatr_initVar = 0u;

#if (uatr_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_uatr_CUSTOM_INTR_HANDLER)
    void (*uatr_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_uatr_CUSTOM_INTR_HANDLER) */
#endif /* (uatr_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void uatr_ScbEnableIntr(void);
static void uatr_ScbModeStop(void);
static void uatr_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: uatr_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void uatr_Init(void)
{
#if (uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    if (uatr_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        uatr_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (uatr_SCB_MODE_I2C_CONST_CFG)
    uatr_I2CInit();

#elif (uatr_SCB_MODE_SPI_CONST_CFG)
    uatr_SpiInit();

#elif (uatr_SCB_MODE_UART_CONST_CFG)
    uatr_UartInit();

#elif (uatr_SCB_MODE_EZI2C_CONST_CFG)
    uatr_EzI2CInit();

#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: uatr_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void uatr_Enable(void)
{
#if (uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!uatr_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        uatr_CTRL_REG |= uatr_CTRL_ENABLED;

        uatr_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        uatr_ScbModePostEnable();
    }
#else
    uatr_CTRL_REG |= uatr_CTRL_ENABLED;

    uatr_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    uatr_ScbModePostEnable();
#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: uatr_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  uatr_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void uatr_Start(void)
{
    if (0u == uatr_initVar)
    {
        uatr_Init();
        uatr_initVar = 1u; /* Component was initialized */
    }

    uatr_Enable();
}


/*******************************************************************************
* Function Name: uatr_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*  It also disables all TX interrupt sources so as not to cause an unexpected
*  interrupt trigger because after the component is enabled, the TX FIFO 
*  is empty.
*
* Parameters:
*  None
*
* Return:
*  None
* 
*******************************************************************************/
void uatr_Stop(void)
{
#if (uatr_SCB_IRQ_INTERNAL)
    uatr_DisableInt();
#endif /* (uatr_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    uatr_ScbModeStop();

    /* Disable SCB IP */
    uatr_CTRL_REG &= (uint32) ~uatr_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    uatr_SetTxInterruptMode(uatr_NO_INTR_SOURCES);

#if (uatr_SCB_IRQ_INTERNAL)
    uatr_ClearPendingInt();
#endif /* (uatr_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: uatr_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void uatr_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = uatr_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~uatr_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (uatr_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    uatr_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: uatr_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void uatr_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = uatr_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~uatr_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (uatr_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    uatr_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (uatr_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: uatr_SetCustomInterruptHandler
    ********************************************************************************
    *
    * Summary:
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    * Parameters:
    *  func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void uatr_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_uatr_CUSTOM_INTR_HANDLER)
        uatr_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_uatr_CUSTOM_INTR_HANDLER) */
    }
#endif /* (uatr_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: uatr_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void uatr_ScbEnableIntr(void)
{
#if (uatr_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (uatr_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != uatr_scbEnableIntr)
        {
            uatr_EnableInt();
        }

    #else
        uatr_EnableInt();

    #endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (uatr_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: uatr_ScbModePostEnable
********************************************************************************
*
* Summary:
*  Calls the PostEnable function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void uatr_ScbModePostEnable(void)
{
#if (uatr_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!uatr_CY_SCBIP_V1)
    if (uatr_SCB_MODE_SPI_RUNTM_CFG)
    {
        uatr_SpiPostEnable();
    }
    else if (uatr_SCB_MODE_UART_RUNTM_CFG)
    {
        uatr_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!uatr_CY_SCBIP_V1) */

#elif (uatr_SCB_MODE_SPI_CONST_CFG)
    uatr_SpiPostEnable();

#elif (uatr_SCB_MODE_UART_CONST_CFG)
    uatr_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: uatr_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void uatr_ScbModeStop(void)
{
#if (uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    if (uatr_SCB_MODE_I2C_RUNTM_CFG)
    {
        uatr_I2CStop();
    }
    else if (uatr_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        uatr_EzI2CStop();
    }
#if (!uatr_CY_SCBIP_V1)
    else if (uatr_SCB_MODE_SPI_RUNTM_CFG)
    {
        uatr_SpiStop();
    }
    else if (uatr_SCB_MODE_UART_RUNTM_CFG)
    {
        uatr_UartStop();
    }
#endif /* (!uatr_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (uatr_SCB_MODE_I2C_CONST_CFG)
    uatr_I2CStop();

#elif (uatr_SCB_MODE_EZI2C_CONST_CFG)
    uatr_EzI2CStop();

#elif (uatr_SCB_MODE_SPI_CONST_CFG)
    uatr_SpiStop();

#elif (uatr_SCB_MODE_UART_CONST_CFG)
    uatr_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: uatr_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void uatr_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [uatr_SCB_PINS_NUMBER];
        uint32 pinsDm   [uatr_SCB_PINS_NUMBER];

    #if (!uatr_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!uatr_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < uatr_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = uatr_HSIOM_DEF_SEL;
            pinsDm[i]    = uatr_PIN_DM_ALG_HIZ;
        }

        if ((uatr_SCB_MODE_I2C   == mode) ||
           (uatr_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[uatr_RX_SCL_MOSI_PIN_INDEX] = uatr_HSIOM_I2C_SEL;
            hsiomSel[uatr_TX_SDA_MISO_PIN_INDEX] = uatr_HSIOM_I2C_SEL;

            pinsDm[uatr_RX_SCL_MOSI_PIN_INDEX] = uatr_PIN_DM_OD_LO;
            pinsDm[uatr_TX_SDA_MISO_PIN_INDEX] = uatr_PIN_DM_OD_LO;
        }
    #if (!uatr_CY_SCBIP_V1)
        else if (uatr_SCB_MODE_SPI == mode)
        {
            hsiomSel[uatr_RX_SCL_MOSI_PIN_INDEX] = uatr_HSIOM_SPI_SEL;
            hsiomSel[uatr_TX_SDA_MISO_PIN_INDEX] = uatr_HSIOM_SPI_SEL;
            hsiomSel[uatr_SCLK_PIN_INDEX] = uatr_HSIOM_SPI_SEL;

            if (uatr_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[uatr_RX_SCL_MOSI_PIN_INDEX] = uatr_PIN_DM_DIG_HIZ;
                pinsDm[uatr_TX_SDA_MISO_PIN_INDEX] = uatr_PIN_DM_STRONG;
                pinsDm[uatr_SCLK_PIN_INDEX] = uatr_PIN_DM_DIG_HIZ;

            #if (uatr_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[uatr_SS0_PIN_INDEX] = uatr_HSIOM_SPI_SEL;
                pinsDm  [uatr_SS0_PIN_INDEX] = uatr_PIN_DM_DIG_HIZ;
            #endif /* (uatr_SS0_PIN) */

            #if (uatr_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= uatr_TX_SDA_MISO_PIN_MASK;
            #endif /* (uatr_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[uatr_RX_SCL_MOSI_PIN_INDEX] = uatr_PIN_DM_STRONG;
                pinsDm[uatr_TX_SDA_MISO_PIN_INDEX] = uatr_PIN_DM_DIG_HIZ;
                pinsDm[uatr_SCLK_PIN_INDEX] = uatr_PIN_DM_STRONG;

            #if (uatr_SS0_PIN)
                hsiomSel [uatr_SS0_PIN_INDEX] = uatr_HSIOM_SPI_SEL;
                pinsDm   [uatr_SS0_PIN_INDEX] = uatr_PIN_DM_STRONG;
                pinsInBuf |= uatr_SS0_PIN_MASK;
            #endif /* (uatr_SS0_PIN) */

            #if (uatr_SS1_PIN)
                hsiomSel [uatr_SS1_PIN_INDEX] = uatr_HSIOM_SPI_SEL;
                pinsDm   [uatr_SS1_PIN_INDEX] = uatr_PIN_DM_STRONG;
                pinsInBuf |= uatr_SS1_PIN_MASK;
            #endif /* (uatr_SS1_PIN) */

            #if (uatr_SS2_PIN)
                hsiomSel [uatr_SS2_PIN_INDEX] = uatr_HSIOM_SPI_SEL;
                pinsDm   [uatr_SS2_PIN_INDEX] = uatr_PIN_DM_STRONG;
                pinsInBuf |= uatr_SS2_PIN_MASK;
            #endif /* (uatr_SS2_PIN) */

            #if (uatr_SS3_PIN)
                hsiomSel [uatr_SS3_PIN_INDEX] = uatr_HSIOM_SPI_SEL;
                pinsDm   [uatr_SS3_PIN_INDEX] = uatr_PIN_DM_STRONG;
                pinsInBuf |= uatr_SS3_PIN_MASK;
            #endif /* (uatr_SS3_PIN) */

                /* Disable input buffers */
            #if (uatr_RX_SCL_MOSI_PIN)
                pinsInBuf |= uatr_RX_SCL_MOSI_PIN_MASK;
            #endif /* (uatr_RX_SCL_MOSI_PIN) */

             #if (uatr_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= uatr_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (uatr_RX_WAKE_SCL_MOSI_PIN) */

            #if (uatr_SCLK_PIN)
                pinsInBuf |= uatr_SCLK_PIN_MASK;
            #endif /* (uatr_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (uatr_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[uatr_TX_SDA_MISO_PIN_INDEX] = uatr_HSIOM_UART_SEL;
                pinsDm  [uatr_TX_SDA_MISO_PIN_INDEX] = uatr_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (uatr_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[uatr_RX_SCL_MOSI_PIN_INDEX] = uatr_HSIOM_UART_SEL;
                    pinsDm  [uatr_RX_SCL_MOSI_PIN_INDEX] = uatr_PIN_DM_DIG_HIZ;
                }

                if (0u != (uatr_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[uatr_TX_SDA_MISO_PIN_INDEX] = uatr_HSIOM_UART_SEL;
                    pinsDm  [uatr_TX_SDA_MISO_PIN_INDEX] = uatr_PIN_DM_STRONG;

                #if (uatr_TX_SDA_MISO_PIN)
                     pinsInBuf |= uatr_TX_SDA_MISO_PIN_MASK;
                #endif /* (uatr_TX_SDA_MISO_PIN) */
                }

            #if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
                if (uatr_UART_MODE_STD == subMode)
                {
                    if (0u != (uatr_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[uatr_SCLK_PIN_INDEX] = uatr_HSIOM_UART_SEL;
                        pinsDm  [uatr_SCLK_PIN_INDEX] = uatr_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (uatr_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[uatr_SS0_PIN_INDEX] = uatr_HSIOM_UART_SEL;
                        pinsDm  [uatr_SS0_PIN_INDEX] = uatr_PIN_DM_STRONG;

                    #if (uatr_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= uatr_SS0_PIN_MASK;
                    #endif /* (uatr_SS0_PIN) */
                    }
                }
            #endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */
            }
        }
    #endif /* (!uatr_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (uatr_RX_WAKE_SCL_MOSI_PIN)
        uatr_SET_HSIOM_SEL(uatr_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       uatr_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       uatr_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[uatr_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        uatr_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[uatr_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        uatr_SET_INP_DIS(uatr_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     uatr_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & uatr_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        uatr_SET_INCFG_TYPE(uatr_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        uatr_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        uatr_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        uatr_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (uatr_RX_WAKE_SCL_MOSI_PIN) */

    #if (uatr_RX_SCL_MOSI_PIN)
        uatr_SET_HSIOM_SEL(uatr_RX_SCL_MOSI_HSIOM_REG,
                                       uatr_RX_SCL_MOSI_HSIOM_MASK,
                                       uatr_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[uatr_RX_SCL_MOSI_PIN_INDEX]);

        uatr_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[uatr_RX_SCL_MOSI_PIN_INDEX]);

    #if (!uatr_CY_SCBIP_V1)
        uatr_SET_INP_DIS(uatr_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     uatr_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & uatr_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!uatr_CY_SCBIP_V1) */
    #endif /* (uatr_RX_SCL_MOSI_PIN) */

    #if (uatr_TX_SDA_MISO_PIN)
        uatr_SET_HSIOM_SEL(uatr_TX_SDA_MISO_HSIOM_REG,
                                       uatr_TX_SDA_MISO_HSIOM_MASK,
                                       uatr_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[uatr_TX_SDA_MISO_PIN_INDEX]);

        uatr_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[uatr_TX_SDA_MISO_PIN_INDEX]);

    #if (!uatr_CY_SCBIP_V1)
        uatr_SET_INP_DIS(uatr_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     uatr_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & uatr_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!uatr_CY_SCBIP_V1) */
    #endif /* (uatr_RX_SCL_MOSI_PIN) */

    #if (uatr_SCLK_PIN)
        uatr_SET_HSIOM_SEL(uatr_SCLK_HSIOM_REG,
                                       uatr_SCLK_HSIOM_MASK,
                                       uatr_SCLK_HSIOM_POS,
                                       hsiomSel[uatr_SCLK_PIN_INDEX]);

        uatr_spi_sclk_SetDriveMode((uint8) pinsDm[uatr_SCLK_PIN_INDEX]);

        uatr_SET_INP_DIS(uatr_spi_sclk_INP_DIS,
                                     uatr_spi_sclk_MASK,
                                     (0u != (pinsInBuf & uatr_SCLK_PIN_MASK)));
    #endif /* (uatr_SCLK_PIN) */

    #if (uatr_SS0_PIN)
        uatr_SET_HSIOM_SEL(uatr_SS0_HSIOM_REG,
                                       uatr_SS0_HSIOM_MASK,
                                       uatr_SS0_HSIOM_POS,
                                       hsiomSel[uatr_SS0_PIN_INDEX]);

        uatr_spi_ss0_SetDriveMode((uint8) pinsDm[uatr_SS0_PIN_INDEX]);

        uatr_SET_INP_DIS(uatr_spi_ss0_INP_DIS,
                                     uatr_spi_ss0_MASK,
                                     (0u != (pinsInBuf & uatr_SS0_PIN_MASK)));
    #endif /* (uatr_SS0_PIN) */

    #if (uatr_SS1_PIN)
        uatr_SET_HSIOM_SEL(uatr_SS1_HSIOM_REG,
                                       uatr_SS1_HSIOM_MASK,
                                       uatr_SS1_HSIOM_POS,
                                       hsiomSel[uatr_SS1_PIN_INDEX]);

        uatr_spi_ss1_SetDriveMode((uint8) pinsDm[uatr_SS1_PIN_INDEX]);

        uatr_SET_INP_DIS(uatr_spi_ss1_INP_DIS,
                                     uatr_spi_ss1_MASK,
                                     (0u != (pinsInBuf & uatr_SS1_PIN_MASK)));
    #endif /* (uatr_SS1_PIN) */

    #if (uatr_SS2_PIN)
        uatr_SET_HSIOM_SEL(uatr_SS2_HSIOM_REG,
                                       uatr_SS2_HSIOM_MASK,
                                       uatr_SS2_HSIOM_POS,
                                       hsiomSel[uatr_SS2_PIN_INDEX]);

        uatr_spi_ss2_SetDriveMode((uint8) pinsDm[uatr_SS2_PIN_INDEX]);

        uatr_SET_INP_DIS(uatr_spi_ss2_INP_DIS,
                                     uatr_spi_ss2_MASK,
                                     (0u != (pinsInBuf & uatr_SS2_PIN_MASK)));
    #endif /* (uatr_SS2_PIN) */

    #if (uatr_SS3_PIN)
        uatr_SET_HSIOM_SEL(uatr_SS3_HSIOM_REG,
                                       uatr_SS3_HSIOM_MASK,
                                       uatr_SS3_HSIOM_POS,
                                       hsiomSel[uatr_SS3_PIN_INDEX]);

        uatr_spi_ss3_SetDriveMode((uint8) pinsDm[uatr_SS3_PIN_INDEX]);

        uatr_SET_INP_DIS(uatr_spi_ss3_INP_DIS,
                                     uatr_spi_ss3_MASK,
                                     (0u != (pinsInBuf & uatr_SS3_PIN_MASK)));
    #endif /* (uatr_SS3_PIN) */
    }

#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: uatr_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void uatr_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (uatr_CTRL_REG & uatr_CTRL_EC_AM_MODE)) &&
            (0u == (uatr_I2C_CTRL_REG & uatr_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            uatr_CTRL_REG &= ~uatr_CTRL_EC_AM_MODE;
            uatr_CTRL_REG |=  uatr_CTRL_EC_AM_MODE;
        }

        uatr_I2C_SLAVE_CMD_REG = uatr_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */


/* [] END OF FILE */
