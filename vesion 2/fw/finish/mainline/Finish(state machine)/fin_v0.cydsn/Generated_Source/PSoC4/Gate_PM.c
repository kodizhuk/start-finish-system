/*******************************************************************************
* File Name: Gate.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Gate.h"

static Gate_BACKUP_STRUCT  Gate_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Gate_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Gate_SUT.c usage_Gate_Sleep_Wakeup
*******************************************************************************/
void Gate_Sleep(void)
{
    #if defined(Gate__PC)
        Gate_backup.pcState = Gate_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Gate_backup.usbState = Gate_CR1_REG;
            Gate_USB_POWER_REG |= Gate_USBIO_ENTER_SLEEP;
            Gate_CR1_REG &= Gate_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Gate__SIO)
        Gate_backup.sioState = Gate_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Gate_SIO_REG &= (uint32)(~Gate_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Gate_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Gate_Sleep() for an example usage.
*******************************************************************************/
void Gate_Wakeup(void)
{
    #if defined(Gate__PC)
        Gate_PC = Gate_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Gate_USB_POWER_REG &= Gate_USBIO_EXIT_SLEEP_PH1;
            Gate_CR1_REG = Gate_backup.usbState;
            Gate_USB_POWER_REG &= Gate_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Gate__SIO)
        Gate_SIO_REG = Gate_backup.sioState;
    #endif
}


/* [] END OF FILE */
