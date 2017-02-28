/*******************************************************************************
* File Name: DIN.h  
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

#if !defined(CY_PINS_DIN_H) /* Pins DIN_H */
#define CY_PINS_DIN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DIN_aliases.h"


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
} DIN_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DIN_Read(void);
void    DIN_Write(uint8 value);
uint8   DIN_ReadDataReg(void);
#if defined(DIN__PC) || (CY_PSOC4_4200L) 
    void    DIN_SetDriveMode(uint8 mode);
#endif
void    DIN_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIN_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DIN_Sleep(void); 
void DIN_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DIN__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DIN_DRIVE_MODE_BITS        (3)
    #define DIN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DIN_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DIN_SetDriveMode() function.
         *  @{
         */
        #define DIN_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DIN_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DIN_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DIN_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DIN_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DIN_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DIN_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DIN_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DIN_MASK               DIN__MASK
#define DIN_SHIFT              DIN__SHIFT
#define DIN_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIN_SetInterruptMode() function.
     *  @{
     */
        #define DIN_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DIN_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DIN_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DIN_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DIN__SIO)
    #define DIN_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DIN__PC) && (CY_PSOC4_4200L)
    #define DIN_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DIN_USBIO_DISABLE              ((uint32)(~DIN_USBIO_ENABLE))
    #define DIN_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DIN_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DIN_USBIO_ENTER_SLEEP          ((uint32)((1u << DIN_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DIN_USBIO_SUSPEND_DEL_SHIFT)))
    #define DIN_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DIN_USBIO_SUSPEND_SHIFT)))
    #define DIN_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DIN_USBIO_SUSPEND_DEL_SHIFT)))
    #define DIN_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DIN__PC)
    /* Port Configuration */
    #define DIN_PC                 (* (reg32 *) DIN__PC)
#endif
/* Pin State */
#define DIN_PS                     (* (reg32 *) DIN__PS)
/* Data Register */
#define DIN_DR                     (* (reg32 *) DIN__DR)
/* Input Buffer Disable Override */
#define DIN_INP_DIS                (* (reg32 *) DIN__PC2)

/* Interrupt configuration Registers */
#define DIN_INTCFG                 (* (reg32 *) DIN__INTCFG)
#define DIN_INTSTAT                (* (reg32 *) DIN__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DIN_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DIN__SIO)
    #define DIN_SIO_REG            (* (reg32 *) DIN__SIO)
#endif /* (DIN__SIO_CFG) */

/* USBIO registers */
#if !defined(DIN__PC) && (CY_PSOC4_4200L)
    #define DIN_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DIN_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DIN_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DIN_DRIVE_MODE_SHIFT       (0x00u)
#define DIN_DRIVE_MODE_MASK        (0x07u << DIN_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DIN_H */


/* [] END OF FILE */
