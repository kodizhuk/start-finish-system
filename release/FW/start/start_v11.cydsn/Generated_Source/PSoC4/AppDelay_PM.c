/*******************************************************************************
* File Name: AppDelay_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "AppDelay.h"

static AppDelay_BACKUP_STRUCT AppDelay_backup;


/*******************************************************************************
* Function Name: AppDelay_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void AppDelay_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: AppDelay_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void AppDelay_Sleep(void)
{
    if(0u != (AppDelay_BLOCK_CONTROL_REG & AppDelay_MASK))
    {
        AppDelay_backup.enableState = 1u;
    }
    else
    {
        AppDelay_backup.enableState = 0u;
    }

    AppDelay_Stop();
    AppDelay_SaveConfig();
}


/*******************************************************************************
* Function Name: AppDelay_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void AppDelay_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: AppDelay_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void AppDelay_Wakeup(void)
{
    AppDelay_RestoreConfig();

    if(0u != AppDelay_backup.enableState)
    {
        AppDelay_Enable();
    }
}


/* [] END OF FILE */
