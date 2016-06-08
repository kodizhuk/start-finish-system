/*******************************************************************************
* File Name: start.h  
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

#if !defined(CY_PINS_start_H) /* Pins start_H */
#define CY_PINS_start_H

#include "cytypes.h"
#include "cyfitter.h"
#include "start_aliases.h"


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
} start_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   start_Read(void);
void    start_Write(uint8 value);
uint8   start_ReadDataReg(void);
#if defined(start__PC) || (CY_PSOC4_4200L) 
    void    start_SetDriveMode(uint8 mode);
#endif
void    start_SetInterruptMode(uint16 position, uint16 mode);
uint8   start_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void start_Sleep(void); 
void start_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(start__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define start_DRIVE_MODE_BITS        (3)
    #define start_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - start_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the start_SetDriveMode() function.
         *  @{
         */
        #define start_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define start_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define start_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define start_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define start_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define start_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define start_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define start_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define start_MASK               start__MASK
#define start_SHIFT              start__SHIFT
#define start_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in start_SetInterruptMode() function.
     *  @{
     */
        #define start_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define start_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define start_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define start_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(start__SIO)
    #define start_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(start__PC) && (CY_PSOC4_4200L)
    #define start_USBIO_ENABLE               ((uint32)0x80000000u)
    #define start_USBIO_DISABLE              ((uint32)(~start_USBIO_ENABLE))
    #define start_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define start_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define start_USBIO_ENTER_SLEEP          ((uint32)((1u << start_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << start_USBIO_SUSPEND_DEL_SHIFT)))
    #define start_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << start_USBIO_SUSPEND_SHIFT)))
    #define start_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << start_USBIO_SUSPEND_DEL_SHIFT)))
    #define start_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(start__PC)
    /* Port Configuration */
    #define start_PC                 (* (reg32 *) start__PC)
#endif
/* Pin State */
#define start_PS                     (* (reg32 *) start__PS)
/* Data Register */
#define start_DR                     (* (reg32 *) start__DR)
/* Input Buffer Disable Override */
#define start_INP_DIS                (* (reg32 *) start__PC2)

/* Interrupt configuration Registers */
#define start_INTCFG                 (* (reg32 *) start__INTCFG)
#define start_INTSTAT                (* (reg32 *) start__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define start_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(start__SIO)
    #define start_SIO_REG            (* (reg32 *) start__SIO)
#endif /* (start__SIO_CFG) */

/* USBIO registers */
#if !defined(start__PC) && (CY_PSOC4_4200L)
    #define start_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define start_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define start_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define start_DRIVE_MODE_SHIFT       (0x00u)
#define start_DRIVE_MODE_MASK        (0x07u << start_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins start_H */


/* [] END OF FILE */
