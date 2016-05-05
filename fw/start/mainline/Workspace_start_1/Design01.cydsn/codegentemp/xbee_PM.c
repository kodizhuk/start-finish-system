/*******************************************************************************
* File Name: xbee_PM.c
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

#include "xbee.h"
#include "xbee_PVT.h"

#if(xbee_SCB_MODE_I2C_INC)
    #include "xbee_I2C_PVT.h"
#endif /* (xbee_SCB_MODE_I2C_INC) */

#if(xbee_SCB_MODE_EZI2C_INC)
    #include "xbee_EZI2C_PVT.h"
#endif /* (xbee_SCB_MODE_EZI2C_INC) */

#if(xbee_SCB_MODE_SPI_INC || xbee_SCB_MODE_UART_INC)
    #include "xbee_SPI_UART_PVT.h"
#endif /* (xbee_SCB_MODE_SPI_INC || xbee_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG || \
   (xbee_SCB_MODE_I2C_CONST_CFG   && (!xbee_I2C_WAKE_ENABLE_CONST))   || \
   (xbee_SCB_MODE_EZI2C_CONST_CFG && (!xbee_EZI2C_WAKE_ENABLE_CONST)) || \
   (xbee_SCB_MODE_SPI_CONST_CFG   && (!xbee_SPI_WAKE_ENABLE_CONST))   || \
   (xbee_SCB_MODE_UART_CONST_CFG  && (!xbee_UART_WAKE_ENABLE_CONST)))

    xbee_BACKUP_STRUCT xbee_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: xbee_Sleep
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
void xbee_Sleep(void)
{
#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)

    if(xbee_SCB_WAKE_ENABLE_CHECK)
    {
        if(xbee_SCB_MODE_I2C_RUNTM_CFG)
        {
            xbee_I2CSaveConfig();
        }
        else if(xbee_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            xbee_EzI2CSaveConfig();
        }
    #if(!xbee_CY_SCBIP_V1)
        else if(xbee_SCB_MODE_SPI_RUNTM_CFG)
        {
            xbee_SpiSaveConfig();
        }
        else if(xbee_SCB_MODE_UART_RUNTM_CFG)
        {
            xbee_UartSaveConfig();
        }
    #endif /* (!xbee_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        xbee_backup.enableState = (uint8) xbee_GET_CTRL_ENABLED;

        if(0u != xbee_backup.enableState)
        {
            xbee_Stop();
        }
    }

#else

    #if (xbee_SCB_MODE_I2C_CONST_CFG && xbee_I2C_WAKE_ENABLE_CONST)
        xbee_I2CSaveConfig();

    #elif (xbee_SCB_MODE_EZI2C_CONST_CFG && xbee_EZI2C_WAKE_ENABLE_CONST)
        xbee_EzI2CSaveConfig();

    #elif (xbee_SCB_MODE_SPI_CONST_CFG && xbee_SPI_WAKE_ENABLE_CONST)
        xbee_SpiSaveConfig();

    #elif (xbee_SCB_MODE_UART_CONST_CFG && xbee_UART_WAKE_ENABLE_CONST)
        xbee_UartSaveConfig();

    #else

        xbee_backup.enableState = (uint8) xbee_GET_CTRL_ENABLED;

        if(0u != xbee_backup.enableState)
        {
            xbee_Stop();
        }

    #endif /* defined (xbee_SCB_MODE_I2C_CONST_CFG) && (xbee_I2C_WAKE_ENABLE_CONST) */

#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: xbee_Wakeup
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
void xbee_Wakeup(void)
{
#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)

    if(xbee_SCB_WAKE_ENABLE_CHECK)
    {
        if(xbee_SCB_MODE_I2C_RUNTM_CFG)
        {
            xbee_I2CRestoreConfig();
        }
        else if(xbee_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            xbee_EzI2CRestoreConfig();
        }
    #if(!xbee_CY_SCBIP_V1)
        else if(xbee_SCB_MODE_SPI_RUNTM_CFG)
        {
            xbee_SpiRestoreConfig();
        }
        else if(xbee_SCB_MODE_UART_RUNTM_CFG)
        {
            xbee_UartRestoreConfig();
        }
    #endif /* (!xbee_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != xbee_backup.enableState)
        {
            xbee_Enable();
        }
    }

#else

    #if (xbee_SCB_MODE_I2C_CONST_CFG  && xbee_I2C_WAKE_ENABLE_CONST)
        xbee_I2CRestoreConfig();

    #elif (xbee_SCB_MODE_EZI2C_CONST_CFG && xbee_EZI2C_WAKE_ENABLE_CONST)
        xbee_EzI2CRestoreConfig();

    #elif (xbee_SCB_MODE_SPI_CONST_CFG && xbee_SPI_WAKE_ENABLE_CONST)
        xbee_SpiRestoreConfig();

    #elif (xbee_SCB_MODE_UART_CONST_CFG && xbee_UART_WAKE_ENABLE_CONST)
        xbee_UartRestoreConfig();

    #else

        if(0u != xbee_backup.enableState)
        {
            xbee_Enable();
        }

    #endif /* (xbee_I2C_WAKE_ENABLE_CONST) */

#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
