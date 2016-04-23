/*******************************************************************************
* File Name: butt_stop.h  
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

#if !defined(CY_PINS_butt_stop_H) /* Pins butt_stop_H */
#define CY_PINS_butt_stop_H

#include "cytypes.h"
#include "cyfitter.h"
#include "butt_stop_aliases.h"


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
} butt_stop_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   butt_stop_Read(void);
void    butt_stop_Write(uint8 value);
uint8   butt_stop_ReadDataReg(void);
#if defined(butt_stop__PC) || (CY_PSOC4_4200L) 
    void    butt_stop_SetDriveMode(uint8 mode);
#endif
void    butt_stop_SetInterruptMode(uint16 position, uint16 mode);
uint8   butt_stop_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void butt_stop_Sleep(void); 
void butt_stop_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(butt_stop__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define butt_stop_DRIVE_MODE_BITS        (3)
    #define butt_stop_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - butt_stop_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the butt_stop_SetDriveMode() function.
         *  @{
         */
        #define butt_stop_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define butt_stop_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define butt_stop_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define butt_stop_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define butt_stop_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define butt_stop_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define butt_stop_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define butt_stop_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define butt_stop_MASK               butt_stop__MASK
#define butt_stop_SHIFT              butt_stop__SHIFT
#define butt_stop_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in butt_stop_SetInterruptMode() function.
     *  @{
     */
        #define butt_stop_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define butt_stop_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define butt_stop_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define butt_stop_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(butt_stop__SIO)
    #define butt_stop_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(butt_stop__PC) && (CY_PSOC4_4200L)
    #define butt_stop_USBIO_ENABLE               ((uint32)0x80000000u)
    #define butt_stop_USBIO_DISABLE              ((uint32)(~butt_stop_USBIO_ENABLE))
    #define butt_stop_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define butt_stop_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define butt_stop_USBIO_ENTER_SLEEP          ((uint32)((1u << butt_stop_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << butt_stop_USBIO_SUSPEND_DEL_SHIFT)))
    #define butt_stop_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << butt_stop_USBIO_SUSPEND_SHIFT)))
    #define butt_stop_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << butt_stop_USBIO_SUSPEND_DEL_SHIFT)))
    #define butt_stop_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(butt_stop__PC)
    /* Port Configuration */
    #define butt_stop_PC                 (* (reg32 *) butt_stop__PC)
#endif
/* Pin State */
#define butt_stop_PS                     (* (reg32 *) butt_stop__PS)
/* Data Register */
#define butt_stop_DR                     (* (reg32 *) butt_stop__DR)
/* Input Buffer Disable Override */
#define butt_stop_INP_DIS                (* (reg32 *) butt_stop__PC2)

/* Interrupt configuration Registers */
#define butt_stop_INTCFG                 (* (reg32 *) butt_stop__INTCFG)
#define butt_stop_INTSTAT                (* (reg32 *) butt_stop__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define butt_stop_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(butt_stop__SIO)
    #define butt_stop_SIO_REG            (* (reg32 *) butt_stop__SIO)
#endif /* (butt_stop__SIO_CFG) */

/* USBIO registers */
#if !defined(butt_stop__PC) && (CY_PSOC4_4200L)
    #define butt_stop_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define butt_stop_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define butt_stop_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define butt_stop_DRIVE_MODE_SHIFT       (0x00u)
#define butt_stop_DRIVE_MODE_MASK        (0x07u << butt_stop_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins butt_stop_H */


/* [] END OF FILE */
