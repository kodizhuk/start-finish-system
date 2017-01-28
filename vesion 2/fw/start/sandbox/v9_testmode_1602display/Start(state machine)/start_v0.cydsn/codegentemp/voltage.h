/*******************************************************************************
* File Name: voltage.h  
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

#if !defined(CY_PINS_voltage_H) /* Pins voltage_H */
#define CY_PINS_voltage_H

#include "cytypes.h"
#include "cyfitter.h"
#include "voltage_aliases.h"


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
} voltage_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   voltage_Read(void);
void    voltage_Write(uint8 value);
uint8   voltage_ReadDataReg(void);
#if defined(voltage__PC) || (CY_PSOC4_4200L) 
    void    voltage_SetDriveMode(uint8 mode);
#endif
void    voltage_SetInterruptMode(uint16 position, uint16 mode);
uint8   voltage_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void voltage_Sleep(void); 
void voltage_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(voltage__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define voltage_DRIVE_MODE_BITS        (3)
    #define voltage_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - voltage_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the voltage_SetDriveMode() function.
         *  @{
         */
        #define voltage_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define voltage_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define voltage_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define voltage_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define voltage_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define voltage_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define voltage_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define voltage_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define voltage_MASK               voltage__MASK
#define voltage_SHIFT              voltage__SHIFT
#define voltage_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in voltage_SetInterruptMode() function.
     *  @{
     */
        #define voltage_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define voltage_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define voltage_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define voltage_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(voltage__SIO)
    #define voltage_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(voltage__PC) && (CY_PSOC4_4200L)
    #define voltage_USBIO_ENABLE               ((uint32)0x80000000u)
    #define voltage_USBIO_DISABLE              ((uint32)(~voltage_USBIO_ENABLE))
    #define voltage_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define voltage_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define voltage_USBIO_ENTER_SLEEP          ((uint32)((1u << voltage_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << voltage_USBIO_SUSPEND_DEL_SHIFT)))
    #define voltage_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << voltage_USBIO_SUSPEND_SHIFT)))
    #define voltage_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << voltage_USBIO_SUSPEND_DEL_SHIFT)))
    #define voltage_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(voltage__PC)
    /* Port Configuration */
    #define voltage_PC                 (* (reg32 *) voltage__PC)
#endif
/* Pin State */
#define voltage_PS                     (* (reg32 *) voltage__PS)
/* Data Register */
#define voltage_DR                     (* (reg32 *) voltage__DR)
/* Input Buffer Disable Override */
#define voltage_INP_DIS                (* (reg32 *) voltage__PC2)

/* Interrupt configuration Registers */
#define voltage_INTCFG                 (* (reg32 *) voltage__INTCFG)
#define voltage_INTSTAT                (* (reg32 *) voltage__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define voltage_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(voltage__SIO)
    #define voltage_SIO_REG            (* (reg32 *) voltage__SIO)
#endif /* (voltage__SIO_CFG) */

/* USBIO registers */
#if !defined(voltage__PC) && (CY_PSOC4_4200L)
    #define voltage_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define voltage_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define voltage_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define voltage_DRIVE_MODE_SHIFT       (0x00u)
#define voltage_DRIVE_MODE_MASK        (0x07u << voltage_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins voltage_H */


/* [] END OF FILE */
