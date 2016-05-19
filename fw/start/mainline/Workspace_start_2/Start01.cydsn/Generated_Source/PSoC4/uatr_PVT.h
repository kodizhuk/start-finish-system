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

#if !defined(CY_SCB_PVT_uatr_H)
#define CY_SCB_PVT_uatr_H

#include "uatr.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define uatr_SetI2CExtClkInterruptMode(interruptMask) uatr_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define uatr_ClearI2CExtClkInterruptSource(interruptMask) uatr_CLEAR_INTR_I2C_EC(interruptMask)
#define uatr_GetI2CExtClkInterruptSource()                (uatr_INTR_I2C_EC_REG)
#define uatr_GetI2CExtClkInterruptMode()                  (uatr_INTR_I2C_EC_MASK_REG)
#define uatr_GetI2CExtClkInterruptSourceMasked()          (uatr_INTR_I2C_EC_MASKED_REG)

#if (!uatr_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define uatr_SetSpiExtClkInterruptMode(interruptMask) \
                                                                uatr_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define uatr_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                uatr_CLEAR_INTR_SPI_EC(interruptMask)
    #define uatr_GetExtSpiClkInterruptSource()                 (uatr_INTR_SPI_EC_REG)
    #define uatr_GetExtSpiClkInterruptMode()                   (uatr_INTR_SPI_EC_MASK_REG)
    #define uatr_GetExtSpiClkInterruptSourceMasked()           (uatr_INTR_SPI_EC_MASKED_REG)
#endif /* (!uatr_CY_SCBIP_V1) */

#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void uatr_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (uatr_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_uatr_CUSTOM_INTR_HANDLER)
    extern cyisraddress uatr_customIntrHandler;
#endif /* !defined (CY_REMOVE_uatr_CUSTOM_INTR_HANDLER) */
#endif /* (uatr_SCB_IRQ_INTERNAL) */

extern uatr_BACKUP_STRUCT uatr_backup;

#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 uatr_scbMode;
    extern uint8 uatr_scbEnableWake;
    extern uint8 uatr_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 uatr_mode;
    extern uint8 uatr_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * uatr_rxBuffer;
    extern uint8   uatr_rxDataBits;
    extern uint32  uatr_rxBufferSize;

    extern volatile uint8 * uatr_txBuffer;
    extern uint8   uatr_txDataBits;
    extern uint32  uatr_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 uatr_numberOfAddr;
    extern uint8 uatr_subAddrSize;
#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define uatr_SCB_MODE_I2C_RUNTM_CFG     (uatr_SCB_MODE_I2C      == uatr_scbMode)
    #define uatr_SCB_MODE_SPI_RUNTM_CFG     (uatr_SCB_MODE_SPI      == uatr_scbMode)
    #define uatr_SCB_MODE_UART_RUNTM_CFG    (uatr_SCB_MODE_UART     == uatr_scbMode)
    #define uatr_SCB_MODE_EZI2C_RUNTM_CFG   (uatr_SCB_MODE_EZI2C    == uatr_scbMode)
    #define uatr_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (uatr_SCB_MODE_UNCONFIG == uatr_scbMode)

    /* Defines wakeup enable */
    #define uatr_SCB_WAKE_ENABLE_CHECK       (0u != uatr_scbEnableWake)
#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!uatr_CY_SCBIP_V1)
    #define uatr_SCB_PINS_NUMBER    (7u)
#else
    #define uatr_SCB_PINS_NUMBER    (2u)
#endif /* (!uatr_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_uatr_H) */


/* [] END OF FILE */
