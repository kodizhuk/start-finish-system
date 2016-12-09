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

#if !defined(CY_SCB_PVT_UART_XB_H)
#define CY_SCB_PVT_UART_XB_H

#include "UART_XB.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_XB_SetI2CExtClkInterruptMode(interruptMask) UART_XB_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_XB_ClearI2CExtClkInterruptSource(interruptMask) UART_XB_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_XB_GetI2CExtClkInterruptSource()                (UART_XB_INTR_I2C_EC_REG)
#define UART_XB_GetI2CExtClkInterruptMode()                  (UART_XB_INTR_I2C_EC_MASK_REG)
#define UART_XB_GetI2CExtClkInterruptSourceMasked()          (UART_XB_INTR_I2C_EC_MASKED_REG)

#if (!UART_XB_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_XB_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_XB_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_XB_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_XB_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_XB_GetExtSpiClkInterruptSource()                 (UART_XB_INTR_SPI_EC_REG)
    #define UART_XB_GetExtSpiClkInterruptMode()                   (UART_XB_INTR_SPI_EC_MASK_REG)
    #define UART_XB_GetExtSpiClkInterruptSourceMasked()           (UART_XB_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_XB_CY_SCBIP_V1) */

#if(UART_XB_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_XB_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_XB_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_XB_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_XB_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_XB_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_XB_CUSTOM_INTR_HANDLER) */
#endif /* (UART_XB_SCB_IRQ_INTERNAL) */

extern UART_XB_BACKUP_STRUCT UART_XB_backup;

#if(UART_XB_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_XB_scbMode;
    extern uint8 UART_XB_scbEnableWake;
    extern uint8 UART_XB_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_XB_mode;
    extern uint8 UART_XB_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_XB_rxBuffer;
    extern uint8   UART_XB_rxDataBits;
    extern uint32  UART_XB_rxBufferSize;

    extern volatile uint8 * UART_XB_txBuffer;
    extern uint8   UART_XB_txDataBits;
    extern uint32  UART_XB_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_XB_numberOfAddr;
    extern uint8 UART_XB_subAddrSize;
#endif /* (UART_XB_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (UART_XB_SCB_MODE_I2C_CONST_CFG || \
        UART_XB_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 UART_XB_IntrTxMask;
#endif /* (! (UART_XB_SCB_MODE_I2C_CONST_CFG || \
              UART_XB_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_XB_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_XB_SCB_MODE_I2C_RUNTM_CFG     (UART_XB_SCB_MODE_I2C      == UART_XB_scbMode)
    #define UART_XB_SCB_MODE_SPI_RUNTM_CFG     (UART_XB_SCB_MODE_SPI      == UART_XB_scbMode)
    #define UART_XB_SCB_MODE_UART_RUNTM_CFG    (UART_XB_SCB_MODE_UART     == UART_XB_scbMode)
    #define UART_XB_SCB_MODE_EZI2C_RUNTM_CFG   (UART_XB_SCB_MODE_EZI2C    == UART_XB_scbMode)
    #define UART_XB_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_XB_SCB_MODE_UNCONFIG == UART_XB_scbMode)

    /* Defines wakeup enable */
    #define UART_XB_SCB_WAKE_ENABLE_CHECK       (0u != UART_XB_scbEnableWake)
#endif /* (UART_XB_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_XB_CY_SCBIP_V1)
    #define UART_XB_SCB_PINS_NUMBER    (7u)
#else
    #define UART_XB_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_XB_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_XB_H) */


/* [] END OF FILE */
