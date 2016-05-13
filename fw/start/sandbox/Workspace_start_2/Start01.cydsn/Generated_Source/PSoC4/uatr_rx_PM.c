/*******************************************************************************
* File Name: uatr_rx.c  
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
#include "uatr_rx.h"

static uatr_rx_BACKUP_STRUCT  uatr_rx_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: uatr_rx_Sleep
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
*  \snippet uatr_rx_SUT.c usage_uatr_rx_Sleep_Wakeup
*******************************************************************************/
void uatr_rx_Sleep(void)
{
    #if defined(uatr_rx__PC)
        uatr_rx_backup.pcState = uatr_rx_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            uatr_rx_backup.usbState = uatr_rx_CR1_REG;
            uatr_rx_USB_POWER_REG |= uatr_rx_USBIO_ENTER_SLEEP;
            uatr_rx_CR1_REG &= uatr_rx_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(uatr_rx__SIO)
        uatr_rx_backup.sioState = uatr_rx_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        uatr_rx_SIO_REG &= (uint32)(~uatr_rx_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: uatr_rx_Wakeup
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
*  Refer to uatr_rx_Sleep() for an example usage.
*******************************************************************************/
void uatr_rx_Wakeup(void)
{
    #if defined(uatr_rx__PC)
        uatr_rx_PC = uatr_rx_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            uatr_rx_USB_POWER_REG &= uatr_rx_USBIO_EXIT_SLEEP_PH1;
            uatr_rx_CR1_REG = uatr_rx_backup.usbState;
            uatr_rx_USB_POWER_REG &= uatr_rx_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(uatr_rx__SIO)
        uatr_rx_SIO_REG = uatr_rx_backup.sioState;
    #endif
}


/* [] END OF FILE */
