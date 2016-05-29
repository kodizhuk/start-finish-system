/*******************************************************************************
* File Name: display_PM.c
* Version 2.20
*
* Description:
*  This file provides the API source code for the Static Segment LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "display.h"


static display_BACKUP_STRUCT display_backup;


/*******************************************************************************
* Function Name: display_SaveConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void display_SaveConfig(void) 
{
}


/*******************************************************************************
* Function Name: display_RestoreConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void display_RestoreConfig(void) 
{
}


/*******************************************************************************
* Function Name: display_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void display_Sleep(void) 
{
    display_backup.enableState = display_enableState;
    display_SaveConfig();
    display_Stop();
}


/*******************************************************************************
* Function Name: display_Wakeup
********************************************************************************
*
* Summary:
*  Wakes the component from sleep mode. Configures DMA and enables the component
*  for normal operation.
*
* Parameters:
*  display_enableState - Global variable.
*
* Return:
*  Status one of standard status for PSoC3 Component
*       CYRET_SUCCESS - Function completed successfully.
*       CYRET_LOCKED - The object was locked, already in use. Some of TDs or
*                      a channel already in use.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void display_Wakeup(void) 
{
    display_RestoreConfig();

    if(display_backup.enableState == 1u)
    {
        display_Enable();
    }
}


/* [] END OF FILE */
