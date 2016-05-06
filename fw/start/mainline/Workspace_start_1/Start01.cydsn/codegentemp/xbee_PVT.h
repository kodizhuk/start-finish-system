/*******************************************************************************
* File Name: .h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_xbee_H)
#define CY_SCB_PVT_xbee_H

#include "xbee.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define xbee_SetI2CExtClkInterruptMode(interruptMask) xbee_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define xbee_ClearI2CExtClkInterruptSource(interruptMask) xbee_CLEAR_INTR_I2C_EC(interruptMask)
#define xbee_GetI2CExtClkInterruptSource()                (xbee_INTR_I2C_EC_REG)
#define xbee_GetI2CExtClkInterruptMode()                  (xbee_INTR_I2C_EC_MASK_REG)
#define xbee_GetI2CExtClkInterruptSourceMasked()          (xbee_INTR_I2C_EC_MASKED_REG)

#if (!xbee_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define xbee_SetSpiExtClkInterruptMode(interruptMask) \
                                                                xbee_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define xbee_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                xbee_CLEAR_INTR_SPI_EC(interruptMask)
    #define xbee_GetExtSpiClkInterruptSource()                 (xbee_INTR_SPI_EC_REG)
    #define xbee_GetExtSpiClkInterruptMode()                   (xbee_INTR_SPI_EC_MASK_REG)
    #define xbee_GetExtSpiClkInterruptSourceMasked()           (xbee_INTR_SPI_EC_MASKED_REG)
#endif /* (!xbee_CY_SCBIP_V1) */

#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void xbee_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (xbee_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_xbee_CUSTOM_INTR_HANDLER)
    extern cyisraddress xbee_customIntrHandler;
#endif /* !defined (CY_REMOVE_xbee_CUSTOM_INTR_HANDLER) */
#endif /* (xbee_SCB_IRQ_INTERNAL) */

extern xbee_BACKUP_STRUCT xbee_backup;

#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 xbee_scbMode;
    extern uint8 xbee_scbEnableWake;
    extern uint8 xbee_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 xbee_mode;
    extern uint8 xbee_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * xbee_rxBuffer;
    extern uint8   xbee_rxDataBits;
    extern uint32  xbee_rxBufferSize;

    extern volatile uint8 * xbee_txBuffer;
    extern uint8   xbee_txDataBits;
    extern uint32  xbee_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 xbee_numberOfAddr;
    extern uint8 xbee_subAddrSize;
#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define xbee_SCB_MODE_I2C_RUNTM_CFG     (xbee_SCB_MODE_I2C      == xbee_scbMode)
    #define xbee_SCB_MODE_SPI_RUNTM_CFG     (xbee_SCB_MODE_SPI      == xbee_scbMode)
    #define xbee_SCB_MODE_UART_RUNTM_CFG    (xbee_SCB_MODE_UART     == xbee_scbMode)
    #define xbee_SCB_MODE_EZI2C_RUNTM_CFG   (xbee_SCB_MODE_EZI2C    == xbee_scbMode)
    #define xbee_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (xbee_SCB_MODE_UNCONFIG == xbee_scbMode)

    /* Defines wakeup enable */
    #define xbee_SCB_WAKE_ENABLE_CHECK       (0u != xbee_scbEnableWake)
#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!xbee_CY_SCBIP_V1)
    #define xbee_SCB_PINS_NUMBER    (7u)
#else
    #define xbee_SCB_PINS_NUMBER    (2u)
#endif /* (!xbee_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_xbee_H) */


/* [] END OF FILE */
