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

#if !defined(CY_SCB_PVT_DEBUG_UART_H)
#define CY_SCB_PVT_DEBUG_UART_H

#include "DEBUG_UART.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define DEBUG_UART_SetI2CExtClkInterruptMode(interruptMask) DEBUG_UART_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define DEBUG_UART_ClearI2CExtClkInterruptSource(interruptMask) DEBUG_UART_CLEAR_INTR_I2C_EC(interruptMask)
#define DEBUG_UART_GetI2CExtClkInterruptSource()                (DEBUG_UART_INTR_I2C_EC_REG)
#define DEBUG_UART_GetI2CExtClkInterruptMode()                  (DEBUG_UART_INTR_I2C_EC_MASK_REG)
#define DEBUG_UART_GetI2CExtClkInterruptSourceMasked()          (DEBUG_UART_INTR_I2C_EC_MASKED_REG)

#if (!DEBUG_UART_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define DEBUG_UART_SetSpiExtClkInterruptMode(interruptMask) \
                                                                DEBUG_UART_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define DEBUG_UART_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                DEBUG_UART_CLEAR_INTR_SPI_EC(interruptMask)
    #define DEBUG_UART_GetExtSpiClkInterruptSource()                 (DEBUG_UART_INTR_SPI_EC_REG)
    #define DEBUG_UART_GetExtSpiClkInterruptMode()                   (DEBUG_UART_INTR_SPI_EC_MASK_REG)
    #define DEBUG_UART_GetExtSpiClkInterruptSourceMasked()           (DEBUG_UART_INTR_SPI_EC_MASKED_REG)
#endif /* (!DEBUG_UART_CY_SCBIP_V1) */

#if(DEBUG_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void DEBUG_UART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (DEBUG_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (DEBUG_UART_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_DEBUG_UART_CUSTOM_INTR_HANDLER)
    extern cyisraddress DEBUG_UART_customIntrHandler;
#endif /* !defined (CY_REMOVE_DEBUG_UART_CUSTOM_INTR_HANDLER) */
#endif /* (DEBUG_UART_SCB_IRQ_INTERNAL) */

extern DEBUG_UART_BACKUP_STRUCT DEBUG_UART_backup;

#if(DEBUG_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 DEBUG_UART_scbMode;
    extern uint8 DEBUG_UART_scbEnableWake;
    extern uint8 DEBUG_UART_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 DEBUG_UART_mode;
    extern uint8 DEBUG_UART_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * DEBUG_UART_rxBuffer;
    extern uint8   DEBUG_UART_rxDataBits;
    extern uint32  DEBUG_UART_rxBufferSize;

    extern volatile uint8 * DEBUG_UART_txBuffer;
    extern uint8   DEBUG_UART_txDataBits;
    extern uint32  DEBUG_UART_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 DEBUG_UART_numberOfAddr;
    extern uint8 DEBUG_UART_subAddrSize;
#endif /* (DEBUG_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (DEBUG_UART_SCB_MODE_I2C_CONST_CFG || \
        DEBUG_UART_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 DEBUG_UART_IntrTxMask;
#endif /* (! (DEBUG_UART_SCB_MODE_I2C_CONST_CFG || \
              DEBUG_UART_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(DEBUG_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define DEBUG_UART_SCB_MODE_I2C_RUNTM_CFG     (DEBUG_UART_SCB_MODE_I2C      == DEBUG_UART_scbMode)
    #define DEBUG_UART_SCB_MODE_SPI_RUNTM_CFG     (DEBUG_UART_SCB_MODE_SPI      == DEBUG_UART_scbMode)
    #define DEBUG_UART_SCB_MODE_UART_RUNTM_CFG    (DEBUG_UART_SCB_MODE_UART     == DEBUG_UART_scbMode)
    #define DEBUG_UART_SCB_MODE_EZI2C_RUNTM_CFG   (DEBUG_UART_SCB_MODE_EZI2C    == DEBUG_UART_scbMode)
    #define DEBUG_UART_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (DEBUG_UART_SCB_MODE_UNCONFIG == DEBUG_UART_scbMode)

    /* Defines wakeup enable */
    #define DEBUG_UART_SCB_WAKE_ENABLE_CHECK       (0u != DEBUG_UART_scbEnableWake)
#endif /* (DEBUG_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!DEBUG_UART_CY_SCBIP_V1)
    #define DEBUG_UART_SCB_PINS_NUMBER    (7u)
#else
    #define DEBUG_UART_SCB_PINS_NUMBER    (2u)
#endif /* (!DEBUG_UART_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_DEBUG_UART_H) */


/* [] END OF FILE */
