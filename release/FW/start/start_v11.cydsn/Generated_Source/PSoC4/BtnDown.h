/*******************************************************************************
* File Name: BtnDown.h  
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

#if !defined(CY_PINS_BtnDown_H) /* Pins BtnDown_H */
#define CY_PINS_BtnDown_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BtnDown_aliases.h"


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
} BtnDown_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BtnDown_Read(void);
void    BtnDown_Write(uint8 value);
uint8   BtnDown_ReadDataReg(void);
#if defined(BtnDown__PC) || (CY_PSOC4_4200L) 
    void    BtnDown_SetDriveMode(uint8 mode);
#endif
void    BtnDown_SetInterruptMode(uint16 position, uint16 mode);
uint8   BtnDown_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BtnDown_Sleep(void); 
void BtnDown_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BtnDown__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BtnDown_DRIVE_MODE_BITS        (3)
    #define BtnDown_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BtnDown_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BtnDown_SetDriveMode() function.
         *  @{
         */
        #define BtnDown_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BtnDown_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BtnDown_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BtnDown_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BtnDown_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BtnDown_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BtnDown_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BtnDown_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BtnDown_MASK               BtnDown__MASK
#define BtnDown_SHIFT              BtnDown__SHIFT
#define BtnDown_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BtnDown_SetInterruptMode() function.
     *  @{
     */
        #define BtnDown_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BtnDown_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BtnDown_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BtnDown_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BtnDown__SIO)
    #define BtnDown_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BtnDown__PC) && (CY_PSOC4_4200L)
    #define BtnDown_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BtnDown_USBIO_DISABLE              ((uint32)(~BtnDown_USBIO_ENABLE))
    #define BtnDown_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BtnDown_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BtnDown_USBIO_ENTER_SLEEP          ((uint32)((1u << BtnDown_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BtnDown_USBIO_SUSPEND_DEL_SHIFT)))
    #define BtnDown_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BtnDown_USBIO_SUSPEND_SHIFT)))
    #define BtnDown_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BtnDown_USBIO_SUSPEND_DEL_SHIFT)))
    #define BtnDown_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BtnDown__PC)
    /* Port Configuration */
    #define BtnDown_PC                 (* (reg32 *) BtnDown__PC)
#endif
/* Pin State */
#define BtnDown_PS                     (* (reg32 *) BtnDown__PS)
/* Data Register */
#define BtnDown_DR                     (* (reg32 *) BtnDown__DR)
/* Input Buffer Disable Override */
#define BtnDown_INP_DIS                (* (reg32 *) BtnDown__PC2)

/* Interrupt configuration Registers */
#define BtnDown_INTCFG                 (* (reg32 *) BtnDown__INTCFG)
#define BtnDown_INTSTAT                (* (reg32 *) BtnDown__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BtnDown_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BtnDown__SIO)
    #define BtnDown_SIO_REG            (* (reg32 *) BtnDown__SIO)
#endif /* (BtnDown__SIO_CFG) */

/* USBIO registers */
#if !defined(BtnDown__PC) && (CY_PSOC4_4200L)
    #define BtnDown_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BtnDown_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BtnDown_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BtnDown_DRIVE_MODE_SHIFT       (0x00u)
#define BtnDown_DRIVE_MODE_MASK        (0x07u << BtnDown_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BtnDown_H */


/* [] END OF FILE */
