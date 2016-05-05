/*******************************************************************************
* File Name: xbee.c
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

#include "xbee_PVT.h"

#if (xbee_SCB_MODE_I2C_INC)
    #include "xbee_I2C_PVT.h"
#endif /* (xbee_SCB_MODE_I2C_INC) */

#if (xbee_SCB_MODE_EZI2C_INC)
    #include "xbee_EZI2C_PVT.h"
#endif /* (xbee_SCB_MODE_EZI2C_INC) */

#if (xbee_SCB_MODE_SPI_INC || xbee_SCB_MODE_UART_INC)
    #include "xbee_SPI_UART_PVT.h"
#endif /* (xbee_SCB_MODE_SPI_INC || xbee_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 xbee_scbMode = xbee_SCB_MODE_UNCONFIG;
    uint8 xbee_scbEnableWake;
    uint8 xbee_scbEnableIntr;

    /* I2C configuration variables */
    uint8 xbee_mode;
    uint8 xbee_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * xbee_rxBuffer;
    uint8  xbee_rxDataBits;
    uint32 xbee_rxBufferSize;

    volatile uint8 * xbee_txBuffer;
    uint8  xbee_txDataBits;
    uint32 xbee_txBufferSize;

    /* EZI2C configuration variables */
    uint8 xbee_numberOfAddr;
    uint8 xbee_subAddrSize;
#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 xbee_initVar = 0u;

#if (xbee_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_xbee_CUSTOM_INTR_HANDLER)
    void (*xbee_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_xbee_CUSTOM_INTR_HANDLER) */
#endif /* (xbee_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void xbee_ScbEnableIntr(void);
static void xbee_ScbModeStop(void);
static void xbee_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: xbee_Init
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
void xbee_Init(void)
{
#if (xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    if (xbee_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        xbee_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (xbee_SCB_MODE_I2C_CONST_CFG)
    xbee_I2CInit();

#elif (xbee_SCB_MODE_SPI_CONST_CFG)
    xbee_SpiInit();

#elif (xbee_SCB_MODE_UART_CONST_CFG)
    xbee_UartInit();

#elif (xbee_SCB_MODE_EZI2C_CONST_CFG)
    xbee_EzI2CInit();

#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: xbee_Enable
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
void xbee_Enable(void)
{
#if (xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!xbee_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        xbee_CTRL_REG |= xbee_CTRL_ENABLED;

        xbee_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        xbee_ScbModePostEnable();
    }
#else
    xbee_CTRL_REG |= xbee_CTRL_ENABLED;

    xbee_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    xbee_ScbModePostEnable();
#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: xbee_Start
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
*  xbee_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void xbee_Start(void)
{
    if (0u == xbee_initVar)
    {
        xbee_Init();
        xbee_initVar = 1u; /* Component was initialized */
    }

    xbee_Enable();
}


/*******************************************************************************
* Function Name: xbee_Stop
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
void xbee_Stop(void)
{
#if (xbee_SCB_IRQ_INTERNAL)
    xbee_DisableInt();
#endif /* (xbee_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    xbee_ScbModeStop();

    /* Disable SCB IP */
    xbee_CTRL_REG &= (uint32) ~xbee_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    xbee_SetTxInterruptMode(xbee_NO_INTR_SOURCES);

#if (xbee_SCB_IRQ_INTERNAL)
    xbee_ClearPendingInt();
#endif /* (xbee_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: xbee_SetRxFifoLevel
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
void xbee_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = xbee_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~xbee_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (xbee_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    xbee_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: xbee_SetTxFifoLevel
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
void xbee_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = xbee_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~xbee_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (xbee_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    xbee_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (xbee_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: xbee_SetCustomInterruptHandler
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
    void xbee_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_xbee_CUSTOM_INTR_HANDLER)
        xbee_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_xbee_CUSTOM_INTR_HANDLER) */
    }
#endif /* (xbee_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: xbee_ScbModeEnableIntr
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
static void xbee_ScbEnableIntr(void)
{
#if (xbee_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (xbee_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != xbee_scbEnableIntr)
        {
            xbee_EnableInt();
        }

    #else
        xbee_EnableInt();

    #endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (xbee_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: xbee_ScbModePostEnable
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
static void xbee_ScbModePostEnable(void)
{
#if (xbee_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!xbee_CY_SCBIP_V1)
    if (xbee_SCB_MODE_SPI_RUNTM_CFG)
    {
        xbee_SpiPostEnable();
    }
    else if (xbee_SCB_MODE_UART_RUNTM_CFG)
    {
        xbee_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!xbee_CY_SCBIP_V1) */

#elif (xbee_SCB_MODE_SPI_CONST_CFG)
    xbee_SpiPostEnable();

#elif (xbee_SCB_MODE_UART_CONST_CFG)
    xbee_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: xbee_ScbModeStop
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
static void xbee_ScbModeStop(void)
{
#if (xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    if (xbee_SCB_MODE_I2C_RUNTM_CFG)
    {
        xbee_I2CStop();
    }
    else if (xbee_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        xbee_EzI2CStop();
    }
#if (!xbee_CY_SCBIP_V1)
    else if (xbee_SCB_MODE_SPI_RUNTM_CFG)
    {
        xbee_SpiStop();
    }
    else if (xbee_SCB_MODE_UART_RUNTM_CFG)
    {
        xbee_UartStop();
    }
#endif /* (!xbee_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (xbee_SCB_MODE_I2C_CONST_CFG)
    xbee_I2CStop();

#elif (xbee_SCB_MODE_EZI2C_CONST_CFG)
    xbee_EzI2CStop();

#elif (xbee_SCB_MODE_SPI_CONST_CFG)
    xbee_SpiStop();

#elif (xbee_SCB_MODE_UART_CONST_CFG)
    xbee_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: xbee_SetPins
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
    void xbee_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [xbee_SCB_PINS_NUMBER];
        uint32 pinsDm   [xbee_SCB_PINS_NUMBER];

    #if (!xbee_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!xbee_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < xbee_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = xbee_HSIOM_DEF_SEL;
            pinsDm[i]    = xbee_PIN_DM_ALG_HIZ;
        }

        if ((xbee_SCB_MODE_I2C   == mode) ||
           (xbee_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[xbee_RX_SCL_MOSI_PIN_INDEX] = xbee_HSIOM_I2C_SEL;
            hsiomSel[xbee_TX_SDA_MISO_PIN_INDEX] = xbee_HSIOM_I2C_SEL;

            pinsDm[xbee_RX_SCL_MOSI_PIN_INDEX] = xbee_PIN_DM_OD_LO;
            pinsDm[xbee_TX_SDA_MISO_PIN_INDEX] = xbee_PIN_DM_OD_LO;
        }
    #if (!xbee_CY_SCBIP_V1)
        else if (xbee_SCB_MODE_SPI == mode)
        {
            hsiomSel[xbee_RX_SCL_MOSI_PIN_INDEX] = xbee_HSIOM_SPI_SEL;
            hsiomSel[xbee_TX_SDA_MISO_PIN_INDEX] = xbee_HSIOM_SPI_SEL;
            hsiomSel[xbee_SCLK_PIN_INDEX] = xbee_HSIOM_SPI_SEL;

            if (xbee_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[xbee_RX_SCL_MOSI_PIN_INDEX] = xbee_PIN_DM_DIG_HIZ;
                pinsDm[xbee_TX_SDA_MISO_PIN_INDEX] = xbee_PIN_DM_STRONG;
                pinsDm[xbee_SCLK_PIN_INDEX] = xbee_PIN_DM_DIG_HIZ;

            #if (xbee_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[xbee_SS0_PIN_INDEX] = xbee_HSIOM_SPI_SEL;
                pinsDm  [xbee_SS0_PIN_INDEX] = xbee_PIN_DM_DIG_HIZ;
            #endif /* (xbee_SS0_PIN) */

            #if (xbee_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= xbee_TX_SDA_MISO_PIN_MASK;
            #endif /* (xbee_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[xbee_RX_SCL_MOSI_PIN_INDEX] = xbee_PIN_DM_STRONG;
                pinsDm[xbee_TX_SDA_MISO_PIN_INDEX] = xbee_PIN_DM_DIG_HIZ;
                pinsDm[xbee_SCLK_PIN_INDEX] = xbee_PIN_DM_STRONG;

            #if (xbee_SS0_PIN)
                hsiomSel [xbee_SS0_PIN_INDEX] = xbee_HSIOM_SPI_SEL;
                pinsDm   [xbee_SS0_PIN_INDEX] = xbee_PIN_DM_STRONG;
                pinsInBuf |= xbee_SS0_PIN_MASK;
            #endif /* (xbee_SS0_PIN) */

            #if (xbee_SS1_PIN)
                hsiomSel [xbee_SS1_PIN_INDEX] = xbee_HSIOM_SPI_SEL;
                pinsDm   [xbee_SS1_PIN_INDEX] = xbee_PIN_DM_STRONG;
                pinsInBuf |= xbee_SS1_PIN_MASK;
            #endif /* (xbee_SS1_PIN) */

            #if (xbee_SS2_PIN)
                hsiomSel [xbee_SS2_PIN_INDEX] = xbee_HSIOM_SPI_SEL;
                pinsDm   [xbee_SS2_PIN_INDEX] = xbee_PIN_DM_STRONG;
                pinsInBuf |= xbee_SS2_PIN_MASK;
            #endif /* (xbee_SS2_PIN) */

            #if (xbee_SS3_PIN)
                hsiomSel [xbee_SS3_PIN_INDEX] = xbee_HSIOM_SPI_SEL;
                pinsDm   [xbee_SS3_PIN_INDEX] = xbee_PIN_DM_STRONG;
                pinsInBuf |= xbee_SS3_PIN_MASK;
            #endif /* (xbee_SS3_PIN) */

                /* Disable input buffers */
            #if (xbee_RX_SCL_MOSI_PIN)
                pinsInBuf |= xbee_RX_SCL_MOSI_PIN_MASK;
            #endif /* (xbee_RX_SCL_MOSI_PIN) */

             #if (xbee_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= xbee_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (xbee_RX_WAKE_SCL_MOSI_PIN) */

            #if (xbee_SCLK_PIN)
                pinsInBuf |= xbee_SCLK_PIN_MASK;
            #endif /* (xbee_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (xbee_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[xbee_TX_SDA_MISO_PIN_INDEX] = xbee_HSIOM_UART_SEL;
                pinsDm  [xbee_TX_SDA_MISO_PIN_INDEX] = xbee_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (xbee_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[xbee_RX_SCL_MOSI_PIN_INDEX] = xbee_HSIOM_UART_SEL;
                    pinsDm  [xbee_RX_SCL_MOSI_PIN_INDEX] = xbee_PIN_DM_DIG_HIZ;
                }

                if (0u != (xbee_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[xbee_TX_SDA_MISO_PIN_INDEX] = xbee_HSIOM_UART_SEL;
                    pinsDm  [xbee_TX_SDA_MISO_PIN_INDEX] = xbee_PIN_DM_STRONG;

                #if (xbee_TX_SDA_MISO_PIN)
                     pinsInBuf |= xbee_TX_SDA_MISO_PIN_MASK;
                #endif /* (xbee_TX_SDA_MISO_PIN) */
                }

            #if !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
                if (xbee_UART_MODE_STD == subMode)
                {
                    if (0u != (xbee_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[xbee_SCLK_PIN_INDEX] = xbee_HSIOM_UART_SEL;
                        pinsDm  [xbee_SCLK_PIN_INDEX] = xbee_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (xbee_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[xbee_SS0_PIN_INDEX] = xbee_HSIOM_UART_SEL;
                        pinsDm  [xbee_SS0_PIN_INDEX] = xbee_PIN_DM_STRONG;

                    #if (xbee_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= xbee_SS0_PIN_MASK;
                    #endif /* (xbee_SS0_PIN) */
                    }
                }
            #endif /* !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */
            }
        }
    #endif /* (!xbee_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (xbee_RX_WAKE_SCL_MOSI_PIN)
        xbee_SET_HSIOM_SEL(xbee_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       xbee_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       xbee_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[xbee_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        xbee_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[xbee_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        xbee_SET_INP_DIS(xbee_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     xbee_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & xbee_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        xbee_SET_INCFG_TYPE(xbee_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        xbee_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        xbee_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        xbee_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (xbee_RX_WAKE_SCL_MOSI_PIN) */

    #if (xbee_RX_SCL_MOSI_PIN)
        xbee_SET_HSIOM_SEL(xbee_RX_SCL_MOSI_HSIOM_REG,
                                       xbee_RX_SCL_MOSI_HSIOM_MASK,
                                       xbee_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[xbee_RX_SCL_MOSI_PIN_INDEX]);

        xbee_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[xbee_RX_SCL_MOSI_PIN_INDEX]);

    #if (!xbee_CY_SCBIP_V1)
        xbee_SET_INP_DIS(xbee_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     xbee_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & xbee_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!xbee_CY_SCBIP_V1) */
    #endif /* (xbee_RX_SCL_MOSI_PIN) */

    #if (xbee_TX_SDA_MISO_PIN)
        xbee_SET_HSIOM_SEL(xbee_TX_SDA_MISO_HSIOM_REG,
                                       xbee_TX_SDA_MISO_HSIOM_MASK,
                                       xbee_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[xbee_TX_SDA_MISO_PIN_INDEX]);

        xbee_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[xbee_TX_SDA_MISO_PIN_INDEX]);

    #if (!xbee_CY_SCBIP_V1)
        xbee_SET_INP_DIS(xbee_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     xbee_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & xbee_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!xbee_CY_SCBIP_V1) */
    #endif /* (xbee_RX_SCL_MOSI_PIN) */

    #if (xbee_SCLK_PIN)
        xbee_SET_HSIOM_SEL(xbee_SCLK_HSIOM_REG,
                                       xbee_SCLK_HSIOM_MASK,
                                       xbee_SCLK_HSIOM_POS,
                                       hsiomSel[xbee_SCLK_PIN_INDEX]);

        xbee_spi_sclk_SetDriveMode((uint8) pinsDm[xbee_SCLK_PIN_INDEX]);

        xbee_SET_INP_DIS(xbee_spi_sclk_INP_DIS,
                                     xbee_spi_sclk_MASK,
                                     (0u != (pinsInBuf & xbee_SCLK_PIN_MASK)));
    #endif /* (xbee_SCLK_PIN) */

    #if (xbee_SS0_PIN)
        xbee_SET_HSIOM_SEL(xbee_SS0_HSIOM_REG,
                                       xbee_SS0_HSIOM_MASK,
                                       xbee_SS0_HSIOM_POS,
                                       hsiomSel[xbee_SS0_PIN_INDEX]);

        xbee_spi_ss0_SetDriveMode((uint8) pinsDm[xbee_SS0_PIN_INDEX]);

        xbee_SET_INP_DIS(xbee_spi_ss0_INP_DIS,
                                     xbee_spi_ss0_MASK,
                                     (0u != (pinsInBuf & xbee_SS0_PIN_MASK)));
    #endif /* (xbee_SS0_PIN) */

    #if (xbee_SS1_PIN)
        xbee_SET_HSIOM_SEL(xbee_SS1_HSIOM_REG,
                                       xbee_SS1_HSIOM_MASK,
                                       xbee_SS1_HSIOM_POS,
                                       hsiomSel[xbee_SS1_PIN_INDEX]);

        xbee_spi_ss1_SetDriveMode((uint8) pinsDm[xbee_SS1_PIN_INDEX]);

        xbee_SET_INP_DIS(xbee_spi_ss1_INP_DIS,
                                     xbee_spi_ss1_MASK,
                                     (0u != (pinsInBuf & xbee_SS1_PIN_MASK)));
    #endif /* (xbee_SS1_PIN) */

    #if (xbee_SS2_PIN)
        xbee_SET_HSIOM_SEL(xbee_SS2_HSIOM_REG,
                                       xbee_SS2_HSIOM_MASK,
                                       xbee_SS2_HSIOM_POS,
                                       hsiomSel[xbee_SS2_PIN_INDEX]);

        xbee_spi_ss2_SetDriveMode((uint8) pinsDm[xbee_SS2_PIN_INDEX]);

        xbee_SET_INP_DIS(xbee_spi_ss2_INP_DIS,
                                     xbee_spi_ss2_MASK,
                                     (0u != (pinsInBuf & xbee_SS2_PIN_MASK)));
    #endif /* (xbee_SS2_PIN) */

    #if (xbee_SS3_PIN)
        xbee_SET_HSIOM_SEL(xbee_SS3_HSIOM_REG,
                                       xbee_SS3_HSIOM_MASK,
                                       xbee_SS3_HSIOM_POS,
                                       hsiomSel[xbee_SS3_PIN_INDEX]);

        xbee_spi_ss3_SetDriveMode((uint8) pinsDm[xbee_SS3_PIN_INDEX]);

        xbee_SET_INP_DIS(xbee_spi_ss3_INP_DIS,
                                     xbee_spi_ss3_MASK,
                                     (0u != (pinsInBuf & xbee_SS3_PIN_MASK)));
    #endif /* (xbee_SS3_PIN) */
    }

#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: xbee_I2CSlaveNackGeneration
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
    void xbee_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (xbee_CTRL_REG & xbee_CTRL_EC_AM_MODE)) &&
            (0u == (xbee_I2C_CTRL_REG & xbee_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            xbee_CTRL_REG &= ~xbee_CTRL_EC_AM_MODE;
            xbee_CTRL_REG |=  xbee_CTRL_EC_AM_MODE;
        }

        xbee_I2C_SLAVE_CMD_REG = xbee_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */


/* [] END OF FILE */
