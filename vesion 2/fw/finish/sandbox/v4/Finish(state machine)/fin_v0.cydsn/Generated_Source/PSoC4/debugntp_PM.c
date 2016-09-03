/*******************************************************************************
* File Name: debugntp.c  
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
#include "debugntp.h"

static debugntp_BACKUP_STRUCT  debugntp_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: debugntp_Sleep
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
*  \snippet debugntp_SUT.c usage_debugntp_Sleep_Wakeup
*******************************************************************************/
void debugntp_Sleep(void)
{
    #if defined(debugntp__PC)
        debugntp_backup.pcState = debugntp_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            debugntp_backup.usbState = debugntp_CR1_REG;
            debugntp_USB_POWER_REG |= debugntp_USBIO_ENTER_SLEEP;
            debugntp_CR1_REG &= debugntp_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(debugntp__SIO)
        debugntp_backup.sioState = debugntp_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        debugntp_SIO_REG &= (uint32)(~debugntp_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: debugntp_Wakeup
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
*  Refer to debugntp_Sleep() for an example usage.
*******************************************************************************/
void debugntp_Wakeup(void)
{
    #if defined(debugntp__PC)
        debugntp_PC = debugntp_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            debugntp_USB_POWER_REG &= debugntp_USBIO_EXIT_SLEEP_PH1;
            debugntp_CR1_REG = debugntp_backup.usbState;
            debugntp_USB_POWER_REG &= debugntp_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(debugntp__SIO)
        debugntp_SIO_REG = debugntp_backup.sioState;
    #endif
}


/* [] END OF FILE */
