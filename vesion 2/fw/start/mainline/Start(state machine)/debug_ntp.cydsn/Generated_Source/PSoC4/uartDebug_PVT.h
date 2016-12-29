/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_uartDebug_H)
#define CY_SCB_PVT_uartDebug_H

#include "uartDebug.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define uartDebug_SetI2CExtClkInterruptMode(interruptMask) uartDebug_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define uartDebug_ClearI2CExtClkInterruptSource(interruptMask) uartDebug_CLEAR_INTR_I2C_EC(interruptMask)
#define uartDebug_GetI2CExtClkInterruptSource()                (uartDebug_INTR_I2C_EC_REG)
#define uartDebug_GetI2CExtClkInterruptMode()                  (uartDebug_INTR_I2C_EC_MASK_REG)
#define uartDebug_GetI2CExtClkInterruptSourceMasked()          (uartDebug_INTR_I2C_EC_MASKED_REG)

#if (!uartDebug_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define uartDebug_SetSpiExtClkInterruptMode(interruptMask) \
                                                                uartDebug_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define uartDebug_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                uartDebug_CLEAR_INTR_SPI_EC(interruptMask)
    #define uartDebug_GetExtSpiClkInterruptSource()                 (uartDebug_INTR_SPI_EC_REG)
    #define uartDebug_GetExtSpiClkInterruptMode()                   (uartDebug_INTR_SPI_EC_MASK_REG)
    #define uartDebug_GetExtSpiClkInterruptSourceMasked()           (uartDebug_INTR_SPI_EC_MASKED_REG)
#endif /* (!uartDebug_CY_SCBIP_V1) */

#if(uartDebug_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void uartDebug_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (uartDebug_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_uartDebug_CUSTOM_INTR_HANDLER)
    extern cyisraddress uartDebug_customIntrHandler;
#endif /* !defined (CY_REMOVE_uartDebug_CUSTOM_INTR_HANDLER) */
#endif /* (uartDebug_SCB_IRQ_INTERNAL) */

extern uartDebug_BACKUP_STRUCT uartDebug_backup;

#if(uartDebug_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 uartDebug_scbMode;
    extern uint8 uartDebug_scbEnableWake;
    extern uint8 uartDebug_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 uartDebug_mode;
    extern uint8 uartDebug_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * uartDebug_rxBuffer;
    extern uint8   uartDebug_rxDataBits;
    extern uint32  uartDebug_rxBufferSize;

    extern volatile uint8 * uartDebug_txBuffer;
    extern uint8   uartDebug_txDataBits;
    extern uint32  uartDebug_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 uartDebug_numberOfAddr;
    extern uint8 uartDebug_subAddrSize;
#endif /* (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (uartDebug_SCB_MODE_I2C_CONST_CFG || \
        uartDebug_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 uartDebug_IntrTxMask;
#endif /* (! (uartDebug_SCB_MODE_I2C_CONST_CFG || \
              uartDebug_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(uartDebug_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define uartDebug_SCB_MODE_I2C_RUNTM_CFG     (uartDebug_SCB_MODE_I2C      == uartDebug_scbMode)
    #define uartDebug_SCB_MODE_SPI_RUNTM_CFG     (uartDebug_SCB_MODE_SPI      == uartDebug_scbMode)
    #define uartDebug_SCB_MODE_UART_RUNTM_CFG    (uartDebug_SCB_MODE_UART     == uartDebug_scbMode)
    #define uartDebug_SCB_MODE_EZI2C_RUNTM_CFG   (uartDebug_SCB_MODE_EZI2C    == uartDebug_scbMode)
    #define uartDebug_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (uartDebug_SCB_MODE_UNCONFIG == uartDebug_scbMode)

    /* Defines wakeup enable */
    #define uartDebug_SCB_WAKE_ENABLE_CHECK       (0u != uartDebug_scbEnableWake)
#endif /* (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!uartDebug_CY_SCBIP_V1)
    #define uartDebug_SCB_PINS_NUMBER    (7u)
#else
    #define uartDebug_SCB_PINS_NUMBER    (2u)
#endif /* (!uartDebug_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_uartDebug_H) */


/* [] END OF FILE */
