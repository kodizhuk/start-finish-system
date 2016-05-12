/*******************************************************************************
* File Name: xbee_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "xbee.h"


/***************************************
* Local data allocation
***************************************/

static xbee_BACKUP_STRUCT  xbee_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: xbee_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the xbee_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  xbee_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void xbee_SaveConfig(void)
{
    #if(xbee_CONTROL_REG_REMOVED == 0u)
        xbee_backup.cr = xbee_CONTROL_REG;
    #endif /* End xbee_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: xbee_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  xbee_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling xbee_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void xbee_RestoreConfig(void)
{
    #if(xbee_CONTROL_REG_REMOVED == 0u)
        xbee_CONTROL_REG = xbee_backup.cr;
    #endif /* End xbee_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: xbee_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The xbee_Sleep() API saves the current component state. Then it
*  calls the xbee_Stop() function and calls 
*  xbee_SaveConfig() to save the hardware configuration.
*  Call the xbee_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  xbee_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void xbee_Sleep(void)
{
    #if(xbee_RX_ENABLED || xbee_HD_ENABLED)
        if((xbee_RXSTATUS_ACTL_REG  & xbee_INT_ENABLE) != 0u)
        {
            xbee_backup.enableState = 1u;
        }
        else
        {
            xbee_backup.enableState = 0u;
        }
    #else
        if((xbee_TXSTATUS_ACTL_REG  & xbee_INT_ENABLE) !=0u)
        {
            xbee_backup.enableState = 1u;
        }
        else
        {
            xbee_backup.enableState = 0u;
        }
    #endif /* End xbee_RX_ENABLED || xbee_HD_ENABLED*/

    xbee_Stop();
    xbee_SaveConfig();
}


/*******************************************************************************
* Function Name: xbee_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  xbee_Sleep() was called. The xbee_Wakeup() function
*  calls the xbee_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  xbee_Sleep() function was called, the xbee_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  xbee_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void xbee_Wakeup(void)
{
    xbee_RestoreConfig();
    #if( (xbee_RX_ENABLED) || (xbee_HD_ENABLED) )
        xbee_ClearRxBuffer();
    #endif /* End (xbee_RX_ENABLED) || (xbee_HD_ENABLED) */
    #if(xbee_TX_ENABLED || xbee_HD_ENABLED)
        xbee_ClearTxBuffer();
    #endif /* End xbee_TX_ENABLED || xbee_HD_ENABLED */

    if(xbee_backup.enableState != 0u)
    {
        xbee_Enable();
    }
}


/* [] END OF FILE */
