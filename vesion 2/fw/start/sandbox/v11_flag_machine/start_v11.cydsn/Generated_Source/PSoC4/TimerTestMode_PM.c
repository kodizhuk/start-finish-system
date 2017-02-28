/*******************************************************************************
* File Name: TimerTestMode_PM.c
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

#include "TimerTestMode.h"

static TimerTestMode_BACKUP_STRUCT TimerTestMode_backup;


/*******************************************************************************
* Function Name: TimerTestMode_SaveConfig
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
void TimerTestMode_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: TimerTestMode_Sleep
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
void TimerTestMode_Sleep(void)
{
    if(0u != (TimerTestMode_BLOCK_CONTROL_REG & TimerTestMode_MASK))
    {
        TimerTestMode_backup.enableState = 1u;
    }
    else
    {
        TimerTestMode_backup.enableState = 0u;
    }

    TimerTestMode_Stop();
    TimerTestMode_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerTestMode_RestoreConfig
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
void TimerTestMode_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: TimerTestMode_Wakeup
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
void TimerTestMode_Wakeup(void)
{
    TimerTestMode_RestoreConfig();

    if(0u != TimerTestMode_backup.enableState)
    {
        TimerTestMode_Enable();
    }
}


/* [] END OF FILE */
