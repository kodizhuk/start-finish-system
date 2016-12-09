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

#if !defined(CY_SCB_PVT_UART_DEBUG_H)
#define CY_SCB_PVT_UART_DEBUG_H

#include "UART_DEBUG.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_DEBUG_SetI2CExtClkInterruptMode(interruptMask) UART_DEBUG_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_DEBUG_ClearI2CExtClkInterruptSource(interruptMask) UART_DEBUG_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_DEBUG_GetI2CExtClkInterruptSource()                (UART_DEBUG_INTR_I2C_EC_REG)
#define UART_DEBUG_GetI2CExtClkInterruptMode()                  (UART_DEBUG_INTR_I2C_EC_MASK_REG)
#define UART_DEBUG_GetI2CExtClkInterruptSourceMasked()          (UART_DEBUG_INTR_I2C_EC_MASKED_REG)

#if (!UART_DEBUG_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_DEBUG_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_DEBUG_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_DEBUG_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_DEBUG_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_DEBUG_GetExtSpiClkInterruptSource()                 (UART_DEBUG_INTR_SPI_EC_REG)
    #define UART_DEBUG_GetExtSpiClkInterruptMode()                   (UART_DEBUG_INTR_SPI_EC_MASK_REG)
    #define UART_DEBUG_GetExtSpiClkInterruptSourceMasked()           (UART_DEBUG_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_DEBUG_CY_SCBIP_V1) */

#if(UART_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_DEBUG_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_DEBUG_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_DEBUG_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_DEBUG_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_DEBUG_CUSTOM_INTR_HANDLER) */
#endif /* (UART_DEBUG_SCB_IRQ_INTERNAL) */

extern UART_DEBUG_BACKUP_STRUCT UART_DEBUG_backup;

#if(UART_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_DEBUG_scbMode;
    extern uint8 UART_DEBUG_scbEnableWake;
    extern uint8 UART_DEBUG_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_DEBUG_mode;
    extern uint8 UART_DEBUG_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_DEBUG_rxBuffer;
    extern uint8   UART_DEBUG_rxDataBits;
    extern uint32  UART_DEBUG_rxBufferSize;

    extern volatile uint8 * UART_DEBUG_txBuffer;
    extern uint8   UART_DEBUG_txDataBits;
    extern uint32  UART_DEBUG_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_DEBUG_numberOfAddr;
    extern uint8 UART_DEBUG_subAddrSize;
#endif /* (UART_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (UART_DEBUG_SCB_MODE_I2C_CONST_CFG || \
        UART_DEBUG_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 UART_DEBUG_IntrTxMask;
#endif /* (! (UART_DEBUG_SCB_MODE_I2C_CONST_CFG || \
              UART_DEBUG_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_DEBUG_SCB_MODE_I2C_RUNTM_CFG     (UART_DEBUG_SCB_MODE_I2C      == UART_DEBUG_scbMode)
    #define UART_DEBUG_SCB_MODE_SPI_RUNTM_CFG     (UART_DEBUG_SCB_MODE_SPI      == UART_DEBUG_scbMode)
    #define UART_DEBUG_SCB_MODE_UART_RUNTM_CFG    (UART_DEBUG_SCB_MODE_UART     == UART_DEBUG_scbMode)
    #define UART_DEBUG_SCB_MODE_EZI2C_RUNTM_CFG   (UART_DEBUG_SCB_MODE_EZI2C    == UART_DEBUG_scbMode)
    #define UART_DEBUG_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_DEBUG_SCB_MODE_UNCONFIG == UART_DEBUG_scbMode)

    /* Defines wakeup enable */
    #define UART_DEBUG_SCB_WAKE_ENABLE_CHECK       (0u != UART_DEBUG_scbEnableWake)
#endif /* (UART_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_DEBUG_CY_SCBIP_V1)
    #define UART_DEBUG_SCB_PINS_NUMBER    (7u)
#else
    #define UART_DEBUG_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_DEBUG_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_DEBUG_H) */


/* [] END OF FILE */
