/***************************************************************************//**
* \file uartDebug_PM.c
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

#include "uartDebug.h"
#include "uartDebug_PVT.h"

#if(uartDebug_SCB_MODE_I2C_INC)
    #include "uartDebug_I2C_PVT.h"
#endif /* (uartDebug_SCB_MODE_I2C_INC) */

#if(uartDebug_SCB_MODE_EZI2C_INC)
    #include "uartDebug_EZI2C_PVT.h"
#endif /* (uartDebug_SCB_MODE_EZI2C_INC) */

#if(uartDebug_SCB_MODE_SPI_INC || uartDebug_SCB_MODE_UART_INC)
    #include "uartDebug_SPI_UART_PVT.h"
#endif /* (uartDebug_SCB_MODE_SPI_INC || uartDebug_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(uartDebug_SCB_MODE_UNCONFIG_CONST_CFG || \
   (uartDebug_SCB_MODE_I2C_CONST_CFG   && (!uartDebug_I2C_WAKE_ENABLE_CONST))   || \
   (uartDebug_SCB_MODE_EZI2C_CONST_CFG && (!uartDebug_EZI2C_WAKE_ENABLE_CONST)) || \
   (uartDebug_SCB_MODE_SPI_CONST_CFG   && (!uartDebug_SPI_WAKE_ENABLE_CONST))   || \
   (uartDebug_SCB_MODE_UART_CONST_CFG  && (!uartDebug_UART_WAKE_ENABLE_CONST)))

    uartDebug_BACKUP_STRUCT uartDebug_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: uartDebug_Sleep
****************************************************************************//**
*
*  Prepares the uartDebug component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the uartDebug_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void uartDebug_Sleep(void)
{
#if(uartDebug_SCB_MODE_UNCONFIG_CONST_CFG)

    if(uartDebug_SCB_WAKE_ENABLE_CHECK)
    {
        if(uartDebug_SCB_MODE_I2C_RUNTM_CFG)
        {
            uartDebug_I2CSaveConfig();
        }
        else if(uartDebug_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            uartDebug_EzI2CSaveConfig();
        }
    #if(!uartDebug_CY_SCBIP_V1)
        else if(uartDebug_SCB_MODE_SPI_RUNTM_CFG)
        {
            uartDebug_SpiSaveConfig();
        }
        else if(uartDebug_SCB_MODE_UART_RUNTM_CFG)
        {
            uartDebug_UartSaveConfig();
        }
    #endif /* (!uartDebug_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        uartDebug_backup.enableState = (uint8) uartDebug_GET_CTRL_ENABLED;

        if(0u != uartDebug_backup.enableState)
        {
            uartDebug_Stop();
        }
    }

#else

    #if (uartDebug_SCB_MODE_I2C_CONST_CFG && uartDebug_I2C_WAKE_ENABLE_CONST)
        uartDebug_I2CSaveConfig();

    #elif (uartDebug_SCB_MODE_EZI2C_CONST_CFG && uartDebug_EZI2C_WAKE_ENABLE_CONST)
        uartDebug_EzI2CSaveConfig();

    #elif (uartDebug_SCB_MODE_SPI_CONST_CFG && uartDebug_SPI_WAKE_ENABLE_CONST)
        uartDebug_SpiSaveConfig();

    #elif (uartDebug_SCB_MODE_UART_CONST_CFG && uartDebug_UART_WAKE_ENABLE_CONST)
        uartDebug_UartSaveConfig();

    #else

        uartDebug_backup.enableState = (uint8) uartDebug_GET_CTRL_ENABLED;

        if(0u != uartDebug_backup.enableState)
        {
            uartDebug_Stop();
        }

    #endif /* defined (uartDebug_SCB_MODE_I2C_CONST_CFG) && (uartDebug_I2C_WAKE_ENABLE_CONST) */

#endif /* (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: uartDebug_Wakeup
****************************************************************************//**
*
*  Prepares the uartDebug component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the uartDebug_Wakeup() function without first calling the 
*   uartDebug_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void uartDebug_Wakeup(void)
{
#if(uartDebug_SCB_MODE_UNCONFIG_CONST_CFG)

    if(uartDebug_SCB_WAKE_ENABLE_CHECK)
    {
        if(uartDebug_SCB_MODE_I2C_RUNTM_CFG)
        {
            uartDebug_I2CRestoreConfig();
        }
        else if(uartDebug_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            uartDebug_EzI2CRestoreConfig();
        }
    #if(!uartDebug_CY_SCBIP_V1)
        else if(uartDebug_SCB_MODE_SPI_RUNTM_CFG)
        {
            uartDebug_SpiRestoreConfig();
        }
        else if(uartDebug_SCB_MODE_UART_RUNTM_CFG)
        {
            uartDebug_UartRestoreConfig();
        }
    #endif /* (!uartDebug_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != uartDebug_backup.enableState)
        {
            uartDebug_Enable();
        }
    }

#else

    #if (uartDebug_SCB_MODE_I2C_CONST_CFG  && uartDebug_I2C_WAKE_ENABLE_CONST)
        uartDebug_I2CRestoreConfig();

    #elif (uartDebug_SCB_MODE_EZI2C_CONST_CFG && uartDebug_EZI2C_WAKE_ENABLE_CONST)
        uartDebug_EzI2CRestoreConfig();

    #elif (uartDebug_SCB_MODE_SPI_CONST_CFG && uartDebug_SPI_WAKE_ENABLE_CONST)
        uartDebug_SpiRestoreConfig();

    #elif (uartDebug_SCB_MODE_UART_CONST_CFG && uartDebug_UART_WAKE_ENABLE_CONST)
        uartDebug_UartRestoreConfig();

    #else

        if(0u != uartDebug_backup.enableState)
        {
            uartDebug_Enable();
        }

    #endif /* (uartDebug_I2C_WAKE_ENABLE_CONST) */

#endif /* (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
