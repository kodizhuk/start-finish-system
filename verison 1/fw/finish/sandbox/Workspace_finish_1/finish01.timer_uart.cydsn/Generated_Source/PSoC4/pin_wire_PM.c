/*******************************************************************************
* File Name: pin_wire.c  
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
#include "pin_wire.h"

static pin_wire_BACKUP_STRUCT  pin_wire_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: pin_wire_Sleep
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
*  \snippet pin_wire_SUT.c usage_pin_wire_Sleep_Wakeup
*******************************************************************************/
void pin_wire_Sleep(void)
{
    #if defined(pin_wire__PC)
        pin_wire_backup.pcState = pin_wire_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            pin_wire_backup.usbState = pin_wire_CR1_REG;
            pin_wire_USB_POWER_REG |= pin_wire_USBIO_ENTER_SLEEP;
            pin_wire_CR1_REG &= pin_wire_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(pin_wire__SIO)
        pin_wire_backup.sioState = pin_wire_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        pin_wire_SIO_REG &= (uint32)(~pin_wire_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: pin_wire_Wakeup
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
*  Refer to pin_wire_Sleep() for an example usage.
*******************************************************************************/
void pin_wire_Wakeup(void)
{
    #if defined(pin_wire__PC)
        pin_wire_PC = pin_wire_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            pin_wire_USB_POWER_REG &= pin_wire_USBIO_EXIT_SLEEP_PH1;
            pin_wire_CR1_REG = pin_wire_backup.usbState;
            pin_wire_USB_POWER_REG &= pin_wire_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(pin_wire__SIO)
        pin_wire_SIO_REG = pin_wire_backup.sioState;
    #endif
}


/* [] END OF FILE */
