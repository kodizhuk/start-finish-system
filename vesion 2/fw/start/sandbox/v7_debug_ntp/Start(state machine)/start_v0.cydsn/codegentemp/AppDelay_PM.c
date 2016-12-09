/*******************************************************************************
* File Name: AppDelay_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "AppDelay.h"

static AppDelay_backupStruct AppDelay_backup;


/*******************************************************************************
* Function Name: AppDelay_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  AppDelay_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void AppDelay_SaveConfig(void) 
{
    #if (!AppDelay_UsingFixedFunction)
        AppDelay_backup.TimerUdb = AppDelay_ReadCounter();
        AppDelay_backup.InterruptMaskValue = AppDelay_STATUS_MASK;
        #if (AppDelay_UsingHWCaptureCounter)
            AppDelay_backup.TimerCaptureCounter = AppDelay_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!AppDelay_UDB_CONTROL_REG_REMOVED)
            AppDelay_backup.TimerControlRegister = AppDelay_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: AppDelay_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  AppDelay_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void AppDelay_RestoreConfig(void) 
{   
    #if (!AppDelay_UsingFixedFunction)

        AppDelay_WriteCounter(AppDelay_backup.TimerUdb);
        AppDelay_STATUS_MASK =AppDelay_backup.InterruptMaskValue;
        #if (AppDelay_UsingHWCaptureCounter)
            AppDelay_SetCaptureCount(AppDelay_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!AppDelay_UDB_CONTROL_REG_REMOVED)
            AppDelay_WriteControlRegister(AppDelay_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: AppDelay_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  AppDelay_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void AppDelay_Sleep(void) 
{
    #if(!AppDelay_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(AppDelay_CTRL_ENABLE == (AppDelay_CONTROL & AppDelay_CTRL_ENABLE))
        {
            /* Timer is enabled */
            AppDelay_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            AppDelay_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    AppDelay_Stop();
    AppDelay_SaveConfig();
}


/*******************************************************************************
* Function Name: AppDelay_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  AppDelay_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void AppDelay_Wakeup(void) 
{
    AppDelay_RestoreConfig();
    #if(!AppDelay_UDB_CONTROL_REG_REMOVED)
        if(AppDelay_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                AppDelay_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
