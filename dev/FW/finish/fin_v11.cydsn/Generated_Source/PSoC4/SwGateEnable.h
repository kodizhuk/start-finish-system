/*******************************************************************************
* File Name: SwGateEnable.h  
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

#if !defined(CY_PINS_SwGateEnable_H) /* Pins SwGateEnable_H */
#define CY_PINS_SwGateEnable_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SwGateEnable_aliases.h"


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
} SwGateEnable_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SwGateEnable_Read(void);
void    SwGateEnable_Write(uint8 value);
uint8   SwGateEnable_ReadDataReg(void);
#if defined(SwGateEnable__PC) || (CY_PSOC4_4200L) 
    void    SwGateEnable_SetDriveMode(uint8 mode);
#endif
void    SwGateEnable_SetInterruptMode(uint16 position, uint16 mode);
uint8   SwGateEnable_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SwGateEnable_Sleep(void); 
void SwGateEnable_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SwGateEnable__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SwGateEnable_DRIVE_MODE_BITS        (3)
    #define SwGateEnable_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SwGateEnable_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SwGateEnable_SetDriveMode() function.
         *  @{
         */
        #define SwGateEnable_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SwGateEnable_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SwGateEnable_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SwGateEnable_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SwGateEnable_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SwGateEnable_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SwGateEnable_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SwGateEnable_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SwGateEnable_MASK               SwGateEnable__MASK
#define SwGateEnable_SHIFT              SwGateEnable__SHIFT
#define SwGateEnable_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SwGateEnable_SetInterruptMode() function.
     *  @{
     */
        #define SwGateEnable_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SwGateEnable_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SwGateEnable_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SwGateEnable_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SwGateEnable__SIO)
    #define SwGateEnable_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SwGateEnable__PC) && (CY_PSOC4_4200L)
    #define SwGateEnable_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SwGateEnable_USBIO_DISABLE              ((uint32)(~SwGateEnable_USBIO_ENABLE))
    #define SwGateEnable_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SwGateEnable_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SwGateEnable_USBIO_ENTER_SLEEP          ((uint32)((1u << SwGateEnable_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SwGateEnable_USBIO_SUSPEND_DEL_SHIFT)))
    #define SwGateEnable_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SwGateEnable_USBIO_SUSPEND_SHIFT)))
    #define SwGateEnable_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SwGateEnable_USBIO_SUSPEND_DEL_SHIFT)))
    #define SwGateEnable_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SwGateEnable__PC)
    /* Port Configuration */
    #define SwGateEnable_PC                 (* (reg32 *) SwGateEnable__PC)
#endif
/* Pin State */
#define SwGateEnable_PS                     (* (reg32 *) SwGateEnable__PS)
/* Data Register */
#define SwGateEnable_DR                     (* (reg32 *) SwGateEnable__DR)
/* Input Buffer Disable Override */
#define SwGateEnable_INP_DIS                (* (reg32 *) SwGateEnable__PC2)

/* Interrupt configuration Registers */
#define SwGateEnable_INTCFG                 (* (reg32 *) SwGateEnable__INTCFG)
#define SwGateEnable_INTSTAT                (* (reg32 *) SwGateEnable__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SwGateEnable_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SwGateEnable__SIO)
    #define SwGateEnable_SIO_REG            (* (reg32 *) SwGateEnable__SIO)
#endif /* (SwGateEnable__SIO_CFG) */

/* USBIO registers */
#if !defined(SwGateEnable__PC) && (CY_PSOC4_4200L)
    #define SwGateEnable_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SwGateEnable_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SwGateEnable_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SwGateEnable_DRIVE_MODE_SHIFT       (0x00u)
#define SwGateEnable_DRIVE_MODE_MASK        (0x07u << SwGateEnable_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SwGateEnable_H */


/* [] END OF FILE */
