/*******************************************************************************
* File Name: PinDebugTime.h  
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

#if !defined(CY_PINS_PinDebugTime_H) /* Pins PinDebugTime_H */
#define CY_PINS_PinDebugTime_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PinDebugTime_aliases.h"


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
} PinDebugTime_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PinDebugTime_Read(void);
void    PinDebugTime_Write(uint8 value);
uint8   PinDebugTime_ReadDataReg(void);
#if defined(PinDebugTime__PC) || (CY_PSOC4_4200L) 
    void    PinDebugTime_SetDriveMode(uint8 mode);
#endif
void    PinDebugTime_SetInterruptMode(uint16 position, uint16 mode);
uint8   PinDebugTime_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PinDebugTime_Sleep(void); 
void PinDebugTime_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PinDebugTime__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PinDebugTime_DRIVE_MODE_BITS        (3)
    #define PinDebugTime_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PinDebugTime_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PinDebugTime_SetDriveMode() function.
         *  @{
         */
        #define PinDebugTime_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PinDebugTime_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PinDebugTime_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PinDebugTime_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PinDebugTime_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PinDebugTime_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PinDebugTime_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PinDebugTime_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PinDebugTime_MASK               PinDebugTime__MASK
#define PinDebugTime_SHIFT              PinDebugTime__SHIFT
#define PinDebugTime_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PinDebugTime_SetInterruptMode() function.
     *  @{
     */
        #define PinDebugTime_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PinDebugTime_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PinDebugTime_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PinDebugTime_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PinDebugTime__SIO)
    #define PinDebugTime_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PinDebugTime__PC) && (CY_PSOC4_4200L)
    #define PinDebugTime_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PinDebugTime_USBIO_DISABLE              ((uint32)(~PinDebugTime_USBIO_ENABLE))
    #define PinDebugTime_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PinDebugTime_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PinDebugTime_USBIO_ENTER_SLEEP          ((uint32)((1u << PinDebugTime_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PinDebugTime_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinDebugTime_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PinDebugTime_USBIO_SUSPEND_SHIFT)))
    #define PinDebugTime_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PinDebugTime_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinDebugTime_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PinDebugTime__PC)
    /* Port Configuration */
    #define PinDebugTime_PC                 (* (reg32 *) PinDebugTime__PC)
#endif
/* Pin State */
#define PinDebugTime_PS                     (* (reg32 *) PinDebugTime__PS)
/* Data Register */
#define PinDebugTime_DR                     (* (reg32 *) PinDebugTime__DR)
/* Input Buffer Disable Override */
#define PinDebugTime_INP_DIS                (* (reg32 *) PinDebugTime__PC2)

/* Interrupt configuration Registers */
#define PinDebugTime_INTCFG                 (* (reg32 *) PinDebugTime__INTCFG)
#define PinDebugTime_INTSTAT                (* (reg32 *) PinDebugTime__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PinDebugTime_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PinDebugTime__SIO)
    #define PinDebugTime_SIO_REG            (* (reg32 *) PinDebugTime__SIO)
#endif /* (PinDebugTime__SIO_CFG) */

/* USBIO registers */
#if !defined(PinDebugTime__PC) && (CY_PSOC4_4200L)
    #define PinDebugTime_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PinDebugTime_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PinDebugTime_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PinDebugTime_DRIVE_MODE_SHIFT       (0x00u)
#define PinDebugTime_DRIVE_MODE_MASK        (0x07u << PinDebugTime_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PinDebugTime_H */


/* [] END OF FILE */
