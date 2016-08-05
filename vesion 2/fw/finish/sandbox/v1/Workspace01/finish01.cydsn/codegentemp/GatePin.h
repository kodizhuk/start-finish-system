/*******************************************************************************
* File Name: GatePin.h  
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

#if !defined(CY_PINS_GatePin_H) /* Pins GatePin_H */
#define CY_PINS_GatePin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GatePin_aliases.h"


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
} GatePin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   GatePin_Read(void);
void    GatePin_Write(uint8 value);
uint8   GatePin_ReadDataReg(void);
#if defined(GatePin__PC) || (CY_PSOC4_4200L) 
    void    GatePin_SetDriveMode(uint8 mode);
#endif
void    GatePin_SetInterruptMode(uint16 position, uint16 mode);
uint8   GatePin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void GatePin_Sleep(void); 
void GatePin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(GatePin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define GatePin_DRIVE_MODE_BITS        (3)
    #define GatePin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GatePin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the GatePin_SetDriveMode() function.
         *  @{
         */
        #define GatePin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define GatePin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define GatePin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define GatePin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define GatePin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define GatePin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define GatePin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define GatePin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define GatePin_MASK               GatePin__MASK
#define GatePin_SHIFT              GatePin__SHIFT
#define GatePin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in GatePin_SetInterruptMode() function.
     *  @{
     */
        #define GatePin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define GatePin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define GatePin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define GatePin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(GatePin__SIO)
    #define GatePin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(GatePin__PC) && (CY_PSOC4_4200L)
    #define GatePin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define GatePin_USBIO_DISABLE              ((uint32)(~GatePin_USBIO_ENABLE))
    #define GatePin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define GatePin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define GatePin_USBIO_ENTER_SLEEP          ((uint32)((1u << GatePin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << GatePin_USBIO_SUSPEND_DEL_SHIFT)))
    #define GatePin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << GatePin_USBIO_SUSPEND_SHIFT)))
    #define GatePin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << GatePin_USBIO_SUSPEND_DEL_SHIFT)))
    #define GatePin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(GatePin__PC)
    /* Port Configuration */
    #define GatePin_PC                 (* (reg32 *) GatePin__PC)
#endif
/* Pin State */
#define GatePin_PS                     (* (reg32 *) GatePin__PS)
/* Data Register */
#define GatePin_DR                     (* (reg32 *) GatePin__DR)
/* Input Buffer Disable Override */
#define GatePin_INP_DIS                (* (reg32 *) GatePin__PC2)

/* Interrupt configuration Registers */
#define GatePin_INTCFG                 (* (reg32 *) GatePin__INTCFG)
#define GatePin_INTSTAT                (* (reg32 *) GatePin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define GatePin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(GatePin__SIO)
    #define GatePin_SIO_REG            (* (reg32 *) GatePin__SIO)
#endif /* (GatePin__SIO_CFG) */

/* USBIO registers */
#if !defined(GatePin__PC) && (CY_PSOC4_4200L)
    #define GatePin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define GatePin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define GatePin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define GatePin_DRIVE_MODE_SHIFT       (0x00u)
#define GatePin_DRIVE_MODE_MASK        (0x07u << GatePin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins GatePin_H */


/* [] END OF FILE */
