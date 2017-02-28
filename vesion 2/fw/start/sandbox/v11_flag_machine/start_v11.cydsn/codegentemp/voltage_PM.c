/*******************************************************************************
* File Name: voltage.c  
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
#include "voltage.h"

static voltage_BACKUP_STRUCT  voltage_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: voltage_Sleep
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
*  \snippet voltage_SUT.c usage_voltage_Sleep_Wakeup
*******************************************************************************/
void voltage_Sleep(void)
{
    #if defined(voltage__PC)
        voltage_backup.pcState = voltage_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            voltage_backup.usbState = voltage_CR1_REG;
            voltage_USB_POWER_REG |= voltage_USBIO_ENTER_SLEEP;
            voltage_CR1_REG &= voltage_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(voltage__SIO)
        voltage_backup.sioState = voltage_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        voltage_SIO_REG &= (uint32)(~voltage_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: voltage_Wakeup
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
*  Refer to voltage_Sleep() for an example usage.
*******************************************************************************/
void voltage_Wakeup(void)
{
    #if defined(voltage__PC)
        voltage_PC = voltage_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            voltage_USB_POWER_REG &= voltage_USBIO_EXIT_SLEEP_PH1;
            voltage_CR1_REG = voltage_backup.usbState;
            voltage_USB_POWER_REG &= voltage_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(voltage__SIO)
        voltage_SIO_REG = voltage_backup.sioState;
    #endif
}


/* [] END OF FILE */
