/*******************************************************************************
* File Name: BtnDown.c  
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
#include "BtnDown.h"

static BtnDown_BACKUP_STRUCT  BtnDown_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: BtnDown_Sleep
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
*  \snippet BtnDown_SUT.c usage_BtnDown_Sleep_Wakeup
*******************************************************************************/
void BtnDown_Sleep(void)
{
    #if defined(BtnDown__PC)
        BtnDown_backup.pcState = BtnDown_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            BtnDown_backup.usbState = BtnDown_CR1_REG;
            BtnDown_USB_POWER_REG |= BtnDown_USBIO_ENTER_SLEEP;
            BtnDown_CR1_REG &= BtnDown_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BtnDown__SIO)
        BtnDown_backup.sioState = BtnDown_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        BtnDown_SIO_REG &= (uint32)(~BtnDown_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: BtnDown_Wakeup
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
*  Refer to BtnDown_Sleep() for an example usage.
*******************************************************************************/
void BtnDown_Wakeup(void)
{
    #if defined(BtnDown__PC)
        BtnDown_PC = BtnDown_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            BtnDown_USB_POWER_REG &= BtnDown_USBIO_EXIT_SLEEP_PH1;
            BtnDown_CR1_REG = BtnDown_backup.usbState;
            BtnDown_USB_POWER_REG &= BtnDown_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BtnDown__SIO)
        BtnDown_SIO_REG = BtnDown_backup.sioState;
    #endif
}


/* [] END OF FILE */
