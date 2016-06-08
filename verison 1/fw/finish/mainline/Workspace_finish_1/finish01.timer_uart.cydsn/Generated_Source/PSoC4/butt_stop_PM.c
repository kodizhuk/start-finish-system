/*******************************************************************************
* File Name: butt_stop.c  
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
#include "butt_stop.h"

static butt_stop_BACKUP_STRUCT  butt_stop_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: butt_stop_Sleep
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
*  \snippet butt_stop_SUT.c usage_butt_stop_Sleep_Wakeup
*******************************************************************************/
void butt_stop_Sleep(void)
{
    #if defined(butt_stop__PC)
        butt_stop_backup.pcState = butt_stop_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            butt_stop_backup.usbState = butt_stop_CR1_REG;
            butt_stop_USB_POWER_REG |= butt_stop_USBIO_ENTER_SLEEP;
            butt_stop_CR1_REG &= butt_stop_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(butt_stop__SIO)
        butt_stop_backup.sioState = butt_stop_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        butt_stop_SIO_REG &= (uint32)(~butt_stop_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: butt_stop_Wakeup
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
*  Refer to butt_stop_Sleep() for an example usage.
*******************************************************************************/
void butt_stop_Wakeup(void)
{
    #if defined(butt_stop__PC)
        butt_stop_PC = butt_stop_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            butt_stop_USB_POWER_REG &= butt_stop_USBIO_EXIT_SLEEP_PH1;
            butt_stop_CR1_REG = butt_stop_backup.usbState;
            butt_stop_USB_POWER_REG &= butt_stop_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(butt_stop__SIO)
        butt_stop_SIO_REG = butt_stop_backup.sioState;
    #endif
}


/* [] END OF FILE */
