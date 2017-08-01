/*******************************************************************************
* File Name: BtnGateEnable.h  
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

#if !defined(CY_PINS_BtnGateEnable_H) /* Pins BtnGateEnable_H */
#define CY_PINS_BtnGateEnable_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BtnGateEnable_aliases.h"


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
} BtnGateEnable_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BtnGateEnable_Read(void);
void    BtnGateEnable_Write(uint8 value);
uint8   BtnGateEnable_ReadDataReg(void);
#if defined(BtnGateEnable__PC) || (CY_PSOC4_4200L) 
    void    BtnGateEnable_SetDriveMode(uint8 mode);
#endif
void    BtnGateEnable_SetInterruptMode(uint16 position, uint16 mode);
uint8   BtnGateEnable_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BtnGateEnable_Sleep(void); 
void BtnGateEnable_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BtnGateEnable__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BtnGateEnable_DRIVE_MODE_BITS        (3)
    #define BtnGateEnable_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BtnGateEnable_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BtnGateEnable_SetDriveMode() function.
         *  @{
         */
        #define BtnGateEnable_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BtnGateEnable_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BtnGateEnable_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BtnGateEnable_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BtnGateEnable_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BtnGateEnable_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BtnGateEnable_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BtnGateEnable_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BtnGateEnable_MASK               BtnGateEnable__MASK
#define BtnGateEnable_SHIFT              BtnGateEnable__SHIFT
#define BtnGateEnable_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BtnGateEnable_SetInterruptMode() function.
     *  @{
     */
        #define BtnGateEnable_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BtnGateEnable_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BtnGateEnable_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BtnGateEnable_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BtnGateEnable__SIO)
    #define BtnGateEnable_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BtnGateEnable__PC) && (CY_PSOC4_4200L)
    #define BtnGateEnable_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BtnGateEnable_USBIO_DISABLE              ((uint32)(~BtnGateEnable_USBIO_ENABLE))
    #define BtnGateEnable_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BtnGateEnable_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BtnGateEnable_USBIO_ENTER_SLEEP          ((uint32)((1u << BtnGateEnable_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BtnGateEnable_USBIO_SUSPEND_DEL_SHIFT)))
    #define BtnGateEnable_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BtnGateEnable_USBIO_SUSPEND_SHIFT)))
    #define BtnGateEnable_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BtnGateEnable_USBIO_SUSPEND_DEL_SHIFT)))
    #define BtnGateEnable_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BtnGateEnable__PC)
    /* Port Configuration */
    #define BtnGateEnable_PC                 (* (reg32 *) BtnGateEnable__PC)
#endif
/* Pin State */
#define BtnGateEnable_PS                     (* (reg32 *) BtnGateEnable__PS)
/* Data Register */
#define BtnGateEnable_DR                     (* (reg32 *) BtnGateEnable__DR)
/* Input Buffer Disable Override */
#define BtnGateEnable_INP_DIS                (* (reg32 *) BtnGateEnable__PC2)

/* Interrupt configuration Registers */
#define BtnGateEnable_INTCFG                 (* (reg32 *) BtnGateEnable__INTCFG)
#define BtnGateEnable_INTSTAT                (* (reg32 *) BtnGateEnable__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BtnGateEnable_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BtnGateEnable__SIO)
    #define BtnGateEnable_SIO_REG            (* (reg32 *) BtnGateEnable__SIO)
#endif /* (BtnGateEnable__SIO_CFG) */

/* USBIO registers */
#if !defined(BtnGateEnable__PC) && (CY_PSOC4_4200L)
    #define BtnGateEnable_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BtnGateEnable_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BtnGateEnable_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BtnGateEnable_DRIVE_MODE_SHIFT       (0x00u)
#define BtnGateEnable_DRIVE_MODE_MASK        (0x07u << BtnGateEnable_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BtnGateEnable_H */


/* [] END OF FILE */
