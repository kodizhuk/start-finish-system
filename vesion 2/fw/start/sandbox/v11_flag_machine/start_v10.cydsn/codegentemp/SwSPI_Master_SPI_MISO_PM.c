/*******************************************************************************
* File Name: SwSPI_Master_SPI_MISO.c  
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
#include "SwSPI_Master_SPI_MISO.h"

static SwSPI_Master_SPI_MISO_BACKUP_STRUCT  SwSPI_Master_SPI_MISO_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: SwSPI_Master_SPI_MISO_Sleep
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
*  \snippet SwSPI_Master_SPI_MISO_SUT.c usage_SwSPI_Master_SPI_MISO_Sleep_Wakeup
*******************************************************************************/
void SwSPI_Master_SPI_MISO_Sleep(void)
{
    #if defined(SwSPI_Master_SPI_MISO__PC)
        SwSPI_Master_SPI_MISO_backup.pcState = SwSPI_Master_SPI_MISO_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            SwSPI_Master_SPI_MISO_backup.usbState = SwSPI_Master_SPI_MISO_CR1_REG;
            SwSPI_Master_SPI_MISO_USB_POWER_REG |= SwSPI_Master_SPI_MISO_USBIO_ENTER_SLEEP;
            SwSPI_Master_SPI_MISO_CR1_REG &= SwSPI_Master_SPI_MISO_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SwSPI_Master_SPI_MISO__SIO)
        SwSPI_Master_SPI_MISO_backup.sioState = SwSPI_Master_SPI_MISO_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        SwSPI_Master_SPI_MISO_SIO_REG &= (uint32)(~SwSPI_Master_SPI_MISO_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: SwSPI_Master_SPI_MISO_Wakeup
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
*  Refer to SwSPI_Master_SPI_MISO_Sleep() for an example usage.
*******************************************************************************/
void SwSPI_Master_SPI_MISO_Wakeup(void)
{
    #if defined(SwSPI_Master_SPI_MISO__PC)
        SwSPI_Master_SPI_MISO_PC = SwSPI_Master_SPI_MISO_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            SwSPI_Master_SPI_MISO_USB_POWER_REG &= SwSPI_Master_SPI_MISO_USBIO_EXIT_SLEEP_PH1;
            SwSPI_Master_SPI_MISO_CR1_REG = SwSPI_Master_SPI_MISO_backup.usbState;
            SwSPI_Master_SPI_MISO_USB_POWER_REG &= SwSPI_Master_SPI_MISO_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SwSPI_Master_SPI_MISO__SIO)
        SwSPI_Master_SPI_MISO_SIO_REG = SwSPI_Master_SPI_MISO_backup.sioState;
    #endif
}


/* [] END OF FILE */
