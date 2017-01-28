/*******************************************************************************
* File Name: debug.c  
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
#include "debug.h"

static debug_BACKUP_STRUCT  debug_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: debug_Sleep
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
*  \snippet debug_SUT.c usage_debug_Sleep_Wakeup
*******************************************************************************/
void debug_Sleep(void)
{
    #if defined(debug__PC)
        debug_backup.pcState = debug_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            debug_backup.usbState = debug_CR1_REG;
            debug_USB_POWER_REG |= debug_USBIO_ENTER_SLEEP;
            debug_CR1_REG &= debug_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(debug__SIO)
        debug_backup.sioState = debug_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        debug_SIO_REG &= (uint32)(~debug_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: debug_Wakeup
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
*  Refer to debug_Sleep() for an example usage.
*******************************************************************************/
void debug_Wakeup(void)
{
    #if defined(debug__PC)
        debug_PC = debug_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            debug_USB_POWER_REG &= debug_USBIO_EXIT_SLEEP_PH1;
            debug_CR1_REG = debug_backup.usbState;
            debug_USB_POWER_REG &= debug_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(debug__SIO)
        debug_SIO_REG = debug_backup.sioState;
    #endif
}


/* [] END OF FILE */
