/*******************************************************************************
* File Name: MISO_SPI.h  
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

#if !defined(CY_PINS_MISO_SPI_H) /* Pins MISO_SPI_H */
#define CY_PINS_MISO_SPI_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MISO_SPI_aliases.h"


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
} MISO_SPI_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   MISO_SPI_Read(void);
void    MISO_SPI_Write(uint8 value);
uint8   MISO_SPI_ReadDataReg(void);
#if defined(MISO_SPI__PC) || (CY_PSOC4_4200L) 
    void    MISO_SPI_SetDriveMode(uint8 mode);
#endif
void    MISO_SPI_SetInterruptMode(uint16 position, uint16 mode);
uint8   MISO_SPI_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void MISO_SPI_Sleep(void); 
void MISO_SPI_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(MISO_SPI__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define MISO_SPI_DRIVE_MODE_BITS        (3)
    #define MISO_SPI_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MISO_SPI_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the MISO_SPI_SetDriveMode() function.
         *  @{
         */
        #define MISO_SPI_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define MISO_SPI_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define MISO_SPI_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define MISO_SPI_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define MISO_SPI_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define MISO_SPI_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define MISO_SPI_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define MISO_SPI_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define MISO_SPI_MASK               MISO_SPI__MASK
#define MISO_SPI_SHIFT              MISO_SPI__SHIFT
#define MISO_SPI_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MISO_SPI_SetInterruptMode() function.
     *  @{
     */
        #define MISO_SPI_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define MISO_SPI_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define MISO_SPI_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define MISO_SPI_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(MISO_SPI__SIO)
    #define MISO_SPI_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(MISO_SPI__PC) && (CY_PSOC4_4200L)
    #define MISO_SPI_USBIO_ENABLE               ((uint32)0x80000000u)
    #define MISO_SPI_USBIO_DISABLE              ((uint32)(~MISO_SPI_USBIO_ENABLE))
    #define MISO_SPI_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define MISO_SPI_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define MISO_SPI_USBIO_ENTER_SLEEP          ((uint32)((1u << MISO_SPI_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << MISO_SPI_USBIO_SUSPEND_DEL_SHIFT)))
    #define MISO_SPI_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << MISO_SPI_USBIO_SUSPEND_SHIFT)))
    #define MISO_SPI_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << MISO_SPI_USBIO_SUSPEND_DEL_SHIFT)))
    #define MISO_SPI_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(MISO_SPI__PC)
    /* Port Configuration */
    #define MISO_SPI_PC                 (* (reg32 *) MISO_SPI__PC)
#endif
/* Pin State */
#define MISO_SPI_PS                     (* (reg32 *) MISO_SPI__PS)
/* Data Register */
#define MISO_SPI_DR                     (* (reg32 *) MISO_SPI__DR)
/* Input Buffer Disable Override */
#define MISO_SPI_INP_DIS                (* (reg32 *) MISO_SPI__PC2)

/* Interrupt configuration Registers */
#define MISO_SPI_INTCFG                 (* (reg32 *) MISO_SPI__INTCFG)
#define MISO_SPI_INTSTAT                (* (reg32 *) MISO_SPI__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define MISO_SPI_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(MISO_SPI__SIO)
    #define MISO_SPI_SIO_REG            (* (reg32 *) MISO_SPI__SIO)
#endif /* (MISO_SPI__SIO_CFG) */

/* USBIO registers */
#if !defined(MISO_SPI__PC) && (CY_PSOC4_4200L)
    #define MISO_SPI_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define MISO_SPI_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define MISO_SPI_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define MISO_SPI_DRIVE_MODE_SHIFT       (0x00u)
#define MISO_SPI_DRIVE_MODE_MASK        (0x07u << MISO_SPI_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins MISO_SPI_H */


/* [] END OF FILE */
