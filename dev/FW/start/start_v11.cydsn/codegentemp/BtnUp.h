/*******************************************************************************
* File Name: BtnUp.h  
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

#if !defined(CY_PINS_BtnUp_H) /* Pins BtnUp_H */
#define CY_PINS_BtnUp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BtnUp_aliases.h"


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
} BtnUp_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BtnUp_Read(void);
void    BtnUp_Write(uint8 value);
uint8   BtnUp_ReadDataReg(void);
#if defined(BtnUp__PC) || (CY_PSOC4_4200L) 
    void    BtnUp_SetDriveMode(uint8 mode);
#endif
void    BtnUp_SetInterruptMode(uint16 position, uint16 mode);
uint8   BtnUp_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BtnUp_Sleep(void); 
void BtnUp_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BtnUp__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BtnUp_DRIVE_MODE_BITS        (3)
    #define BtnUp_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BtnUp_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BtnUp_SetDriveMode() function.
         *  @{
         */
        #define BtnUp_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BtnUp_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BtnUp_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BtnUp_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BtnUp_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BtnUp_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BtnUp_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BtnUp_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BtnUp_MASK               BtnUp__MASK
#define BtnUp_SHIFT              BtnUp__SHIFT
#define BtnUp_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BtnUp_SetInterruptMode() function.
     *  @{
     */
        #define BtnUp_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BtnUp_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BtnUp_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BtnUp_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BtnUp__SIO)
    #define BtnUp_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BtnUp__PC) && (CY_PSOC4_4200L)
    #define BtnUp_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BtnUp_USBIO_DISABLE              ((uint32)(~BtnUp_USBIO_ENABLE))
    #define BtnUp_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BtnUp_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BtnUp_USBIO_ENTER_SLEEP          ((uint32)((1u << BtnUp_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BtnUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define BtnUp_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BtnUp_USBIO_SUSPEND_SHIFT)))
    #define BtnUp_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BtnUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define BtnUp_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BtnUp__PC)
    /* Port Configuration */
    #define BtnUp_PC                 (* (reg32 *) BtnUp__PC)
#endif
/* Pin State */
#define BtnUp_PS                     (* (reg32 *) BtnUp__PS)
/* Data Register */
#define BtnUp_DR                     (* (reg32 *) BtnUp__DR)
/* Input Buffer Disable Override */
#define BtnUp_INP_DIS                (* (reg32 *) BtnUp__PC2)

/* Interrupt configuration Registers */
#define BtnUp_INTCFG                 (* (reg32 *) BtnUp__INTCFG)
#define BtnUp_INTSTAT                (* (reg32 *) BtnUp__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BtnUp_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BtnUp__SIO)
    #define BtnUp_SIO_REG            (* (reg32 *) BtnUp__SIO)
#endif /* (BtnUp__SIO_CFG) */

/* USBIO registers */
#if !defined(BtnUp__PC) && (CY_PSOC4_4200L)
    #define BtnUp_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BtnUp_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BtnUp_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BtnUp_DRIVE_MODE_SHIFT       (0x00u)
#define BtnUp_DRIVE_MODE_MASK        (0x07u << BtnUp_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BtnUp_H */


/* [] END OF FILE */
