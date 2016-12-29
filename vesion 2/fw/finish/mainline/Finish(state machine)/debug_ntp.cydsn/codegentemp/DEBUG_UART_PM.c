/***************************************************************************//**
* \file DEBUG_UART_PM.c
* \version 3.20
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DEBUG_UART.h"
#include "DEBUG_UART_PVT.h"

#if(DEBUG_UART_SCB_MODE_I2C_INC)
    #include "DEBUG_UART_I2C_PVT.h"
#endif /* (DEBUG_UART_SCB_MODE_I2C_INC) */

#if(DEBUG_UART_SCB_MODE_EZI2C_INC)
    #include "DEBUG_UART_EZI2C_PVT.h"
#endif /* (DEBUG_UART_SCB_MODE_EZI2C_INC) */

#if(DEBUG_UART_SCB_MODE_SPI_INC || DEBUG_UART_SCB_MODE_UART_INC)
    #include "DEBUG_UART_SPI_UART_PVT.h"
#endif /* (DEBUG_UART_SCB_MODE_SPI_INC || DEBUG_UART_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(DEBUG_UART_SCB_MODE_UNCONFIG_CONST_CFG || \
   (DEBUG_UART_SCB_MODE_I2C_CONST_CFG   && (!DEBUG_UART_I2C_WAKE_ENABLE_CONST))   || \
   (DEBUG_UART_SCB_MODE_EZI2C_CONST_CFG && (!DEBUG_UART_EZI2C_WAKE_ENABLE_CONST)) || \
   (DEBUG_UART_SCB_MODE_SPI_CONST_CFG   && (!DEBUG_UART_SPI_WAKE_ENABLE_CONST))   || \
   (DEBUG_UART_SCB_MODE_UART_CONST_CFG  && (!DEBUG_UART_UART_WAKE_ENABLE_CONST)))

    DEBUG_UART_BACKUP_STRUCT DEBUG_UART_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: DEBUG_UART_Sleep
****************************************************************************//**
*
*  Prepares the DEBUG_UART component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the DEBUG_UART_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void DEBUG_UART_Sleep(void)
{
#if(DEBUG_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(DEBUG_UART_SCB_WAKE_ENABLE_CHECK)
    {
        if(DEBUG_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            DEBUG_UART_I2CSaveConfig();
        }
        else if(DEBUG_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            DEBUG_UART_EzI2CSaveConfig();
        }
    #if(!DEBUG_UART_CY_SCBIP_V1)
        else if(DEBUG_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            DEBUG_UART_SpiSaveConfig();
        }
        else if(DEBUG_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            DEBUG_UART_UartSaveConfig();
        }
    #endif /* (!DEBUG_UART_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        DEBUG_UART_backup.enableState = (uint8) DEBUG_UART_GET_CTRL_ENABLED;

        if(0u != DEBUG_UART_backup.enableState)
        {
            DEBUG_UART_Stop();
        }
    }

#else

    #if (DEBUG_UART_SCB_MODE_I2C_CONST_CFG && DEBUG_UART_I2C_WAKE_ENABLE_CONST)
        DEBUG_UART_I2CSaveConfig();

    #elif (DEBUG_UART_SCB_MODE_EZI2C_CONST_CFG && DEBUG_UART_EZI2C_WAKE_ENABLE_CONST)
        DEBUG_UART_EzI2CSaveConfig();

    #elif (DEBUG_UART_SCB_MODE_SPI_CONST_CFG && DEBUG_UART_SPI_WAKE_ENABLE_CONST)
        DEBUG_UART_SpiSaveConfig();

    #elif (DEBUG_UART_SCB_MODE_UART_CONST_CFG && DEBUG_UART_UART_WAKE_ENABLE_CONST)
        DEBUG_UART_UartSaveConfig();

    #else

        DEBUG_UART_backup.enableState = (uint8) DEBUG_UART_GET_CTRL_ENABLED;

        if(0u != DEBUG_UART_backup.enableState)
        {
            DEBUG_UART_Stop();
        }

    #endif /* defined (DEBUG_UART_SCB_MODE_I2C_CONST_CFG) && (DEBUG_UART_I2C_WAKE_ENABLE_CONST) */

#endif /* (DEBUG_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DEBUG_UART_Wakeup
****************************************************************************//**
*
*  Prepares the DEBUG_UART component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the DEBUG_UART_Wakeup() function without first calling the 
*   DEBUG_UART_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void DEBUG_UART_Wakeup(void)
{
#if(DEBUG_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(DEBUG_UART_SCB_WAKE_ENABLE_CHECK)
    {
        if(DEBUG_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            DEBUG_UART_I2CRestoreConfig();
        }
        else if(DEBUG_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            DEBUG_UART_EzI2CRestoreConfig();
        }
    #if(!DEBUG_UART_CY_SCBIP_V1)
        else if(DEBUG_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            DEBUG_UART_SpiRestoreConfig();
        }
        else if(DEBUG_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            DEBUG_UART_UartRestoreConfig();
        }
    #endif /* (!DEBUG_UART_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != DEBUG_UART_backup.enableState)
        {
            DEBUG_UART_Enable();
        }
    }

#else

    #if (DEBUG_UART_SCB_MODE_I2C_CONST_CFG  && DEBUG_UART_I2C_WAKE_ENABLE_CONST)
        DEBUG_UART_I2CRestoreConfig();

    #elif (DEBUG_UART_SCB_MODE_EZI2C_CONST_CFG && DEBUG_UART_EZI2C_WAKE_ENABLE_CONST)
        DEBUG_UART_EzI2CRestoreConfig();

    #elif (DEBUG_UART_SCB_MODE_SPI_CONST_CFG && DEBUG_UART_SPI_WAKE_ENABLE_CONST)
        DEBUG_UART_SpiRestoreConfig();

    #elif (DEBUG_UART_SCB_MODE_UART_CONST_CFG && DEBUG_UART_UART_WAKE_ENABLE_CONST)
        DEBUG_UART_UartRestoreConfig();

    #else

        if(0u != DEBUG_UART_backup.enableState)
        {
            DEBUG_UART_Enable();
        }

    #endif /* (DEBUG_UART_I2C_WAKE_ENABLE_CONST) */

#endif /* (DEBUG_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
