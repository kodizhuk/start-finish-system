/*******************************************************************************
* File Name: uatr_PM.c
* Version 3.10
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "uatr.h"
#include "uatr_PVT.h"

#if(uatr_SCB_MODE_I2C_INC)
    #include "uatr_I2C_PVT.h"
#endif /* (uatr_SCB_MODE_I2C_INC) */

#if(uatr_SCB_MODE_EZI2C_INC)
    #include "uatr_EZI2C_PVT.h"
#endif /* (uatr_SCB_MODE_EZI2C_INC) */

#if(uatr_SCB_MODE_SPI_INC || uatr_SCB_MODE_UART_INC)
    #include "uatr_SPI_UART_PVT.h"
#endif /* (uatr_SCB_MODE_SPI_INC || uatr_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG || \
   (uatr_SCB_MODE_I2C_CONST_CFG   && (!uatr_I2C_WAKE_ENABLE_CONST))   || \
   (uatr_SCB_MODE_EZI2C_CONST_CFG && (!uatr_EZI2C_WAKE_ENABLE_CONST)) || \
   (uatr_SCB_MODE_SPI_CONST_CFG   && (!uatr_SPI_WAKE_ENABLE_CONST))   || \
   (uatr_SCB_MODE_UART_CONST_CFG  && (!uatr_UART_WAKE_ENABLE_CONST)))

    uatr_BACKUP_STRUCT uatr_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: uatr_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void uatr_Sleep(void)
{
#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)

    if(uatr_SCB_WAKE_ENABLE_CHECK)
    {
        if(uatr_SCB_MODE_I2C_RUNTM_CFG)
        {
            uatr_I2CSaveConfig();
        }
        else if(uatr_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            uatr_EzI2CSaveConfig();
        }
    #if(!uatr_CY_SCBIP_V1)
        else if(uatr_SCB_MODE_SPI_RUNTM_CFG)
        {
            uatr_SpiSaveConfig();
        }
        else if(uatr_SCB_MODE_UART_RUNTM_CFG)
        {
            uatr_UartSaveConfig();
        }
    #endif /* (!uatr_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        uatr_backup.enableState = (uint8) uatr_GET_CTRL_ENABLED;

        if(0u != uatr_backup.enableState)
        {
            uatr_Stop();
        }
    }

#else

    #if (uatr_SCB_MODE_I2C_CONST_CFG && uatr_I2C_WAKE_ENABLE_CONST)
        uatr_I2CSaveConfig();

    #elif (uatr_SCB_MODE_EZI2C_CONST_CFG && uatr_EZI2C_WAKE_ENABLE_CONST)
        uatr_EzI2CSaveConfig();

    #elif (uatr_SCB_MODE_SPI_CONST_CFG && uatr_SPI_WAKE_ENABLE_CONST)
        uatr_SpiSaveConfig();

    #elif (uatr_SCB_MODE_UART_CONST_CFG && uatr_UART_WAKE_ENABLE_CONST)
        uatr_UartSaveConfig();

    #else

        uatr_backup.enableState = (uint8) uatr_GET_CTRL_ENABLED;

        if(0u != uatr_backup.enableState)
        {
            uatr_Stop();
        }

    #endif /* defined (uatr_SCB_MODE_I2C_CONST_CFG) && (uatr_I2C_WAKE_ENABLE_CONST) */

#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: uatr_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void uatr_Wakeup(void)
{
#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)

    if(uatr_SCB_WAKE_ENABLE_CHECK)
    {
        if(uatr_SCB_MODE_I2C_RUNTM_CFG)
        {
            uatr_I2CRestoreConfig();
        }
        else if(uatr_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            uatr_EzI2CRestoreConfig();
        }
    #if(!uatr_CY_SCBIP_V1)
        else if(uatr_SCB_MODE_SPI_RUNTM_CFG)
        {
            uatr_SpiRestoreConfig();
        }
        else if(uatr_SCB_MODE_UART_RUNTM_CFG)
        {
            uatr_UartRestoreConfig();
        }
    #endif /* (!uatr_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != uatr_backup.enableState)
        {
            uatr_Enable();
        }
    }

#else

    #if (uatr_SCB_MODE_I2C_CONST_CFG  && uatr_I2C_WAKE_ENABLE_CONST)
        uatr_I2CRestoreConfig();

    #elif (uatr_SCB_MODE_EZI2C_CONST_CFG && uatr_EZI2C_WAKE_ENABLE_CONST)
        uatr_EzI2CRestoreConfig();

    #elif (uatr_SCB_MODE_SPI_CONST_CFG && uatr_SPI_WAKE_ENABLE_CONST)
        uatr_SpiRestoreConfig();

    #elif (uatr_SCB_MODE_UART_CONST_CFG && uatr_UART_WAKE_ENABLE_CONST)
        uatr_UartRestoreConfig();

    #else

        if(0u != uatr_backup.enableState)
        {
            uatr_Enable();
        }

    #endif /* (uatr_I2C_WAKE_ENABLE_CONST) */

#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
