/*******************************************************************************
* File Name: BtnUp.c  
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
#include "BtnUp.h"

static BtnUp_BACKUP_STRUCT  BtnUp_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: BtnUp_Sleep
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
*  \snippet BtnUp_SUT.c usage_BtnUp_Sleep_Wakeup
*******************************************************************************/
void BtnUp_Sleep(void)
{
    #if defined(BtnUp__PC)
        BtnUp_backup.pcState = BtnUp_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            BtnUp_backup.usbState = BtnUp_CR1_REG;
            BtnUp_USB_POWER_REG |= BtnUp_USBIO_ENTER_SLEEP;
            BtnUp_CR1_REG &= BtnUp_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BtnUp__SIO)
        BtnUp_backup.sioState = BtnUp_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        BtnUp_SIO_REG &= (uint32)(~BtnUp_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: BtnUp_Wakeup
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
*  Refer to BtnUp_Sleep() for an example usage.
*******************************************************************************/
void BtnUp_Wakeup(void)
{
    #if defined(BtnUp__PC)
        BtnUp_PC = BtnUp_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            BtnUp_USB_POWER_REG &= BtnUp_USBIO_EXIT_SLEEP_PH1;
            BtnUp_CR1_REG = BtnUp_backup.usbState;
            BtnUp_USB_POWER_REG &= BtnUp_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BtnUp__SIO)
        BtnUp_SIO_REG = BtnUp_backup.sioState;
    #endif
}


/* [] END OF FILE */
