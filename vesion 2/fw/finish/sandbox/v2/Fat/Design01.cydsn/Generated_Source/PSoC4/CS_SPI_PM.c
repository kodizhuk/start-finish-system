/*******************************************************************************
* File Name: CS_SPI.c  
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
#include "CS_SPI.h"

static CS_SPI_BACKUP_STRUCT  CS_SPI_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: CS_SPI_Sleep
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
*  \snippet CS_SPI_SUT.c usage_CS_SPI_Sleep_Wakeup
*******************************************************************************/
void CS_SPI_Sleep(void)
{
    #if defined(CS_SPI__PC)
        CS_SPI_backup.pcState = CS_SPI_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            CS_SPI_backup.usbState = CS_SPI_CR1_REG;
            CS_SPI_USB_POWER_REG |= CS_SPI_USBIO_ENTER_SLEEP;
            CS_SPI_CR1_REG &= CS_SPI_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CS_SPI__SIO)
        CS_SPI_backup.sioState = CS_SPI_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        CS_SPI_SIO_REG &= (uint32)(~CS_SPI_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: CS_SPI_Wakeup
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
*  Refer to CS_SPI_Sleep() for an example usage.
*******************************************************************************/
void CS_SPI_Wakeup(void)
{
    #if defined(CS_SPI__PC)
        CS_SPI_PC = CS_SPI_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            CS_SPI_USB_POWER_REG &= CS_SPI_USBIO_EXIT_SLEEP_PH1;
            CS_SPI_CR1_REG = CS_SPI_backup.usbState;
            CS_SPI_USB_POWER_REG &= CS_SPI_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CS_SPI__SIO)
        CS_SPI_SIO_REG = CS_SPI_backup.sioState;
    #endif
}


/* [] END OF FILE */