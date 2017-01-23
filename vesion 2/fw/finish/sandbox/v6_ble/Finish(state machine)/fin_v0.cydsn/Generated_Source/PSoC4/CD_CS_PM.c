/*******************************************************************************
* File Name: CD_CS.c  
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
#include "CD_CS.h"

static CD_CS_BACKUP_STRUCT  CD_CS_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: CD_CS_Sleep
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
*  \snippet CD_CS_SUT.c usage_CD_CS_Sleep_Wakeup
*******************************************************************************/
void CD_CS_Sleep(void)
{
    #if defined(CD_CS__PC)
        CD_CS_backup.pcState = CD_CS_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            CD_CS_backup.usbState = CD_CS_CR1_REG;
            CD_CS_USB_POWER_REG |= CD_CS_USBIO_ENTER_SLEEP;
            CD_CS_CR1_REG &= CD_CS_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CD_CS__SIO)
        CD_CS_backup.sioState = CD_CS_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        CD_CS_SIO_REG &= (uint32)(~CD_CS_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: CD_CS_Wakeup
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
*  Refer to CD_CS_Sleep() for an example usage.
*******************************************************************************/
void CD_CS_Wakeup(void)
{
    #if defined(CD_CS__PC)
        CD_CS_PC = CD_CS_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            CD_CS_USB_POWER_REG &= CD_CS_USBIO_EXIT_SLEEP_PH1;
            CD_CS_CR1_REG = CD_CS_backup.usbState;
            CD_CS_USB_POWER_REG &= CD_CS_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CD_CS__SIO)
        CD_CS_SIO_REG = CD_CS_backup.sioState;
    #endif
}


/* [] END OF FILE */
