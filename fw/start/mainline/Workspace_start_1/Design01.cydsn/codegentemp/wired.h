/*******************************************************************************
* File Name: wired.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_wired_H) /* Pins wired_H */
#define CY_PINS_wired_H

#include "cytypes.h"
#include "cyfitter.h"
#include "wired_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} wired_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   wired_Read(void);
void    wired_Write(uint8 value);
uint8   wired_ReadDataReg(void);
#if defined(wired__PC) || (CY_PSOC4_4200L) 
    void    wired_SetDriveMode(uint8 mode);
#endif
void    wired_SetInterruptMode(uint16 position, uint16 mode);
uint8   wired_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void wired_Sleep(void); 
void wired_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(wired__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define wired_DRIVE_MODE_BITS        (3)
    #define wired_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - wired_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the wired_SetDriveMode() function.
         *  @{
         */
        #define wired_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define wired_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define wired_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define wired_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define wired_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define wired_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define wired_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define wired_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define wired_MASK               wired__MASK
#define wired_SHIFT              wired__SHIFT
#define wired_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in wired_SetInterruptMode() function.
     *  @{
     */
        #define wired_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define wired_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define wired_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define wired_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(wired__SIO)
    #define wired_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(wired__PC) && (CY_PSOC4_4200L)
    #define wired_USBIO_ENABLE               ((uint32)0x80000000u)
    #define wired_USBIO_DISABLE              ((uint32)(~wired_USBIO_ENABLE))
    #define wired_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define wired_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define wired_USBIO_ENTER_SLEEP          ((uint32)((1u << wired_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << wired_USBIO_SUSPEND_DEL_SHIFT)))
    #define wired_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << wired_USBIO_SUSPEND_SHIFT)))
    #define wired_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << wired_USBIO_SUSPEND_DEL_SHIFT)))
    #define wired_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(wired__PC)
    /* Port Configuration */
    #define wired_PC                 (* (reg32 *) wired__PC)
#endif
/* Pin State */
#define wired_PS                     (* (reg32 *) wired__PS)
/* Data Register */
#define wired_DR                     (* (reg32 *) wired__DR)
/* Input Buffer Disable Override */
#define wired_INP_DIS                (* (reg32 *) wired__PC2)

/* Interrupt configuration Registers */
#define wired_INTCFG                 (* (reg32 *) wired__INTCFG)
#define wired_INTSTAT                (* (reg32 *) wired__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define wired_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(wired__SIO)
    #define wired_SIO_REG            (* (reg32 *) wired__SIO)
#endif /* (wired__SIO_CFG) */

/* USBIO registers */
#if !defined(wired__PC) && (CY_PSOC4_4200L)
    #define wired_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define wired_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define wired_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define wired_DRIVE_MODE_SHIFT       (0x00u)
#define wired_DRIVE_MODE_MASK        (0x07u << wired_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins wired_H */


/* [] END OF FILE */
