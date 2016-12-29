/*******************************************************************************
* File Name: pinDebugNtp.h  
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

#if !defined(CY_PINS_pinDebugNtp_H) /* Pins pinDebugNtp_H */
#define CY_PINS_pinDebugNtp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "pinDebugNtp_aliases.h"


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
} pinDebugNtp_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   pinDebugNtp_Read(void);
void    pinDebugNtp_Write(uint8 value);
uint8   pinDebugNtp_ReadDataReg(void);
#if defined(pinDebugNtp__PC) || (CY_PSOC4_4200L) 
    void    pinDebugNtp_SetDriveMode(uint8 mode);
#endif
void    pinDebugNtp_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinDebugNtp_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void pinDebugNtp_Sleep(void); 
void pinDebugNtp_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(pinDebugNtp__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define pinDebugNtp_DRIVE_MODE_BITS        (3)
    #define pinDebugNtp_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - pinDebugNtp_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the pinDebugNtp_SetDriveMode() function.
         *  @{
         */
        #define pinDebugNtp_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define pinDebugNtp_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define pinDebugNtp_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define pinDebugNtp_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define pinDebugNtp_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define pinDebugNtp_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define pinDebugNtp_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define pinDebugNtp_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define pinDebugNtp_MASK               pinDebugNtp__MASK
#define pinDebugNtp_SHIFT              pinDebugNtp__SHIFT
#define pinDebugNtp_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinDebugNtp_SetInterruptMode() function.
     *  @{
     */
        #define pinDebugNtp_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define pinDebugNtp_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define pinDebugNtp_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define pinDebugNtp_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(pinDebugNtp__SIO)
    #define pinDebugNtp_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(pinDebugNtp__PC) && (CY_PSOC4_4200L)
    #define pinDebugNtp_USBIO_ENABLE               ((uint32)0x80000000u)
    #define pinDebugNtp_USBIO_DISABLE              ((uint32)(~pinDebugNtp_USBIO_ENABLE))
    #define pinDebugNtp_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define pinDebugNtp_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define pinDebugNtp_USBIO_ENTER_SLEEP          ((uint32)((1u << pinDebugNtp_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << pinDebugNtp_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinDebugNtp_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << pinDebugNtp_USBIO_SUSPEND_SHIFT)))
    #define pinDebugNtp_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << pinDebugNtp_USBIO_SUSPEND_DEL_SHIFT)))
    #define pinDebugNtp_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(pinDebugNtp__PC)
    /* Port Configuration */
    #define pinDebugNtp_PC                 (* (reg32 *) pinDebugNtp__PC)
#endif
/* Pin State */
#define pinDebugNtp_PS                     (* (reg32 *) pinDebugNtp__PS)
/* Data Register */
#define pinDebugNtp_DR                     (* (reg32 *) pinDebugNtp__DR)
/* Input Buffer Disable Override */
#define pinDebugNtp_INP_DIS                (* (reg32 *) pinDebugNtp__PC2)

/* Interrupt configuration Registers */
#define pinDebugNtp_INTCFG                 (* (reg32 *) pinDebugNtp__INTCFG)
#define pinDebugNtp_INTSTAT                (* (reg32 *) pinDebugNtp__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define pinDebugNtp_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(pinDebugNtp__SIO)
    #define pinDebugNtp_SIO_REG            (* (reg32 *) pinDebugNtp__SIO)
#endif /* (pinDebugNtp__SIO_CFG) */

/* USBIO registers */
#if !defined(pinDebugNtp__PC) && (CY_PSOC4_4200L)
    #define pinDebugNtp_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define pinDebugNtp_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define pinDebugNtp_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define pinDebugNtp_DRIVE_MODE_SHIFT       (0x00u)
#define pinDebugNtp_DRIVE_MODE_MASK        (0x07u << pinDebugNtp_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins pinDebugNtp_H */


/* [] END OF FILE */
