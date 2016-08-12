/*******************************************************************************
* File Name: debug_reset_fin.h  
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

#if !defined(CY_PINS_debug_reset_fin_H) /* Pins debug_reset_fin_H */
#define CY_PINS_debug_reset_fin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "debug_reset_fin_aliases.h"


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
} debug_reset_fin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   debug_reset_fin_Read(void);
void    debug_reset_fin_Write(uint8 value);
uint8   debug_reset_fin_ReadDataReg(void);
#if defined(debug_reset_fin__PC) || (CY_PSOC4_4200L) 
    void    debug_reset_fin_SetDriveMode(uint8 mode);
#endif
void    debug_reset_fin_SetInterruptMode(uint16 position, uint16 mode);
uint8   debug_reset_fin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void debug_reset_fin_Sleep(void); 
void debug_reset_fin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(debug_reset_fin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define debug_reset_fin_DRIVE_MODE_BITS        (3)
    #define debug_reset_fin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - debug_reset_fin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the debug_reset_fin_SetDriveMode() function.
         *  @{
         */
        #define debug_reset_fin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define debug_reset_fin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define debug_reset_fin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define debug_reset_fin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define debug_reset_fin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define debug_reset_fin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define debug_reset_fin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define debug_reset_fin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define debug_reset_fin_MASK               debug_reset_fin__MASK
#define debug_reset_fin_SHIFT              debug_reset_fin__SHIFT
#define debug_reset_fin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in debug_reset_fin_SetInterruptMode() function.
     *  @{
     */
        #define debug_reset_fin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define debug_reset_fin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define debug_reset_fin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define debug_reset_fin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(debug_reset_fin__SIO)
    #define debug_reset_fin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(debug_reset_fin__PC) && (CY_PSOC4_4200L)
    #define debug_reset_fin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define debug_reset_fin_USBIO_DISABLE              ((uint32)(~debug_reset_fin_USBIO_ENABLE))
    #define debug_reset_fin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define debug_reset_fin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define debug_reset_fin_USBIO_ENTER_SLEEP          ((uint32)((1u << debug_reset_fin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << debug_reset_fin_USBIO_SUSPEND_DEL_SHIFT)))
    #define debug_reset_fin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << debug_reset_fin_USBIO_SUSPEND_SHIFT)))
    #define debug_reset_fin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << debug_reset_fin_USBIO_SUSPEND_DEL_SHIFT)))
    #define debug_reset_fin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(debug_reset_fin__PC)
    /* Port Configuration */
    #define debug_reset_fin_PC                 (* (reg32 *) debug_reset_fin__PC)
#endif
/* Pin State */
#define debug_reset_fin_PS                     (* (reg32 *) debug_reset_fin__PS)
/* Data Register */
#define debug_reset_fin_DR                     (* (reg32 *) debug_reset_fin__DR)
/* Input Buffer Disable Override */
#define debug_reset_fin_INP_DIS                (* (reg32 *) debug_reset_fin__PC2)

/* Interrupt configuration Registers */
#define debug_reset_fin_INTCFG                 (* (reg32 *) debug_reset_fin__INTCFG)
#define debug_reset_fin_INTSTAT                (* (reg32 *) debug_reset_fin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define debug_reset_fin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(debug_reset_fin__SIO)
    #define debug_reset_fin_SIO_REG            (* (reg32 *) debug_reset_fin__SIO)
#endif /* (debug_reset_fin__SIO_CFG) */

/* USBIO registers */
#if !defined(debug_reset_fin__PC) && (CY_PSOC4_4200L)
    #define debug_reset_fin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define debug_reset_fin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define debug_reset_fin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define debug_reset_fin_DRIVE_MODE_SHIFT       (0x00u)
#define debug_reset_fin_DRIVE_MODE_MASK        (0x07u << debug_reset_fin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins debug_reset_fin_H */


/* [] END OF FILE */
