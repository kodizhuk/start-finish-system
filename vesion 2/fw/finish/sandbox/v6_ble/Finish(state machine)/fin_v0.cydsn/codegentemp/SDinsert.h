/*******************************************************************************
* File Name: SDinsert.h  
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

#if !defined(CY_PINS_SDinsert_H) /* Pins SDinsert_H */
#define CY_PINS_SDinsert_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SDinsert_aliases.h"


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
} SDinsert_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SDinsert_Read(void);
void    SDinsert_Write(uint8 value);
uint8   SDinsert_ReadDataReg(void);
#if defined(SDinsert__PC) || (CY_PSOC4_4200L) 
    void    SDinsert_SetDriveMode(uint8 mode);
#endif
void    SDinsert_SetInterruptMode(uint16 position, uint16 mode);
uint8   SDinsert_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SDinsert_Sleep(void); 
void SDinsert_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SDinsert__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SDinsert_DRIVE_MODE_BITS        (3)
    #define SDinsert_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SDinsert_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SDinsert_SetDriveMode() function.
         *  @{
         */
        #define SDinsert_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SDinsert_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SDinsert_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SDinsert_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SDinsert_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SDinsert_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SDinsert_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SDinsert_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SDinsert_MASK               SDinsert__MASK
#define SDinsert_SHIFT              SDinsert__SHIFT
#define SDinsert_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SDinsert_SetInterruptMode() function.
     *  @{
     */
        #define SDinsert_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SDinsert_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SDinsert_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SDinsert_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SDinsert__SIO)
    #define SDinsert_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SDinsert__PC) && (CY_PSOC4_4200L)
    #define SDinsert_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SDinsert_USBIO_DISABLE              ((uint32)(~SDinsert_USBIO_ENABLE))
    #define SDinsert_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SDinsert_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SDinsert_USBIO_ENTER_SLEEP          ((uint32)((1u << SDinsert_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SDinsert_USBIO_SUSPEND_DEL_SHIFT)))
    #define SDinsert_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SDinsert_USBIO_SUSPEND_SHIFT)))
    #define SDinsert_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SDinsert_USBIO_SUSPEND_DEL_SHIFT)))
    #define SDinsert_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SDinsert__PC)
    /* Port Configuration */
    #define SDinsert_PC                 (* (reg32 *) SDinsert__PC)
#endif
/* Pin State */
#define SDinsert_PS                     (* (reg32 *) SDinsert__PS)
/* Data Register */
#define SDinsert_DR                     (* (reg32 *) SDinsert__DR)
/* Input Buffer Disable Override */
#define SDinsert_INP_DIS                (* (reg32 *) SDinsert__PC2)

/* Interrupt configuration Registers */
#define SDinsert_INTCFG                 (* (reg32 *) SDinsert__INTCFG)
#define SDinsert_INTSTAT                (* (reg32 *) SDinsert__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SDinsert_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SDinsert__SIO)
    #define SDinsert_SIO_REG            (* (reg32 *) SDinsert__SIO)
#endif /* (SDinsert__SIO_CFG) */

/* USBIO registers */
#if !defined(SDinsert__PC) && (CY_PSOC4_4200L)
    #define SDinsert_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SDinsert_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SDinsert_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SDinsert_DRIVE_MODE_SHIFT       (0x00u)
#define SDinsert_DRIVE_MODE_MASK        (0x07u << SDinsert_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SDinsert_H */


/* [] END OF FILE */
