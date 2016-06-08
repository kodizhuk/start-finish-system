/*******************************************************************************
* File Name: finish.h  
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

#if !defined(CY_PINS_finish_H) /* Pins finish_H */
#define CY_PINS_finish_H

#include "cytypes.h"
#include "cyfitter.h"
#include "finish_aliases.h"


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
} finish_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   finish_Read(void);
void    finish_Write(uint8 value);
uint8   finish_ReadDataReg(void);
#if defined(finish__PC) || (CY_PSOC4_4200L) 
    void    finish_SetDriveMode(uint8 mode);
#endif
void    finish_SetInterruptMode(uint16 position, uint16 mode);
uint8   finish_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void finish_Sleep(void); 
void finish_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(finish__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define finish_DRIVE_MODE_BITS        (3)
    #define finish_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - finish_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the finish_SetDriveMode() function.
         *  @{
         */
        #define finish_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define finish_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define finish_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define finish_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define finish_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define finish_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define finish_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define finish_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define finish_MASK               finish__MASK
#define finish_SHIFT              finish__SHIFT
#define finish_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in finish_SetInterruptMode() function.
     *  @{
     */
        #define finish_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define finish_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define finish_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define finish_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(finish__SIO)
    #define finish_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(finish__PC) && (CY_PSOC4_4200L)
    #define finish_USBIO_ENABLE               ((uint32)0x80000000u)
    #define finish_USBIO_DISABLE              ((uint32)(~finish_USBIO_ENABLE))
    #define finish_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define finish_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define finish_USBIO_ENTER_SLEEP          ((uint32)((1u << finish_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << finish_USBIO_SUSPEND_DEL_SHIFT)))
    #define finish_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << finish_USBIO_SUSPEND_SHIFT)))
    #define finish_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << finish_USBIO_SUSPEND_DEL_SHIFT)))
    #define finish_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(finish__PC)
    /* Port Configuration */
    #define finish_PC                 (* (reg32 *) finish__PC)
#endif
/* Pin State */
#define finish_PS                     (* (reg32 *) finish__PS)
/* Data Register */
#define finish_DR                     (* (reg32 *) finish__DR)
/* Input Buffer Disable Override */
#define finish_INP_DIS                (* (reg32 *) finish__PC2)

/* Interrupt configuration Registers */
#define finish_INTCFG                 (* (reg32 *) finish__INTCFG)
#define finish_INTSTAT                (* (reg32 *) finish__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define finish_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(finish__SIO)
    #define finish_SIO_REG            (* (reg32 *) finish__SIO)
#endif /* (finish__SIO_CFG) */

/* USBIO registers */
#if !defined(finish__PC) && (CY_PSOC4_4200L)
    #define finish_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define finish_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define finish_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define finish_DRIVE_MODE_SHIFT       (0x00u)
#define finish_DRIVE_MODE_MASK        (0x07u << finish_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins finish_H */


/* [] END OF FILE */
