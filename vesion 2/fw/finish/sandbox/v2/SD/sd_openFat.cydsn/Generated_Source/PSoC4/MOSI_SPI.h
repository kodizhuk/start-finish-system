/*******************************************************************************
* File Name: MOSI_SPI.h  
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

#if !defined(CY_PINS_MOSI_SPI_H) /* Pins MOSI_SPI_H */
#define CY_PINS_MOSI_SPI_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MOSI_SPI_aliases.h"


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
} MOSI_SPI_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   MOSI_SPI_Read(void);
void    MOSI_SPI_Write(uint8 value);
uint8   MOSI_SPI_ReadDataReg(void);
#if defined(MOSI_SPI__PC) || (CY_PSOC4_4200L) 
    void    MOSI_SPI_SetDriveMode(uint8 mode);
#endif
void    MOSI_SPI_SetInterruptMode(uint16 position, uint16 mode);
uint8   MOSI_SPI_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void MOSI_SPI_Sleep(void); 
void MOSI_SPI_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(MOSI_SPI__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define MOSI_SPI_DRIVE_MODE_BITS        (3)
    #define MOSI_SPI_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MOSI_SPI_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the MOSI_SPI_SetDriveMode() function.
         *  @{
         */
        #define MOSI_SPI_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define MOSI_SPI_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define MOSI_SPI_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define MOSI_SPI_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define MOSI_SPI_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define MOSI_SPI_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define MOSI_SPI_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define MOSI_SPI_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define MOSI_SPI_MASK               MOSI_SPI__MASK
#define MOSI_SPI_SHIFT              MOSI_SPI__SHIFT
#define MOSI_SPI_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MOSI_SPI_SetInterruptMode() function.
     *  @{
     */
        #define MOSI_SPI_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define MOSI_SPI_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define MOSI_SPI_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define MOSI_SPI_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(MOSI_SPI__SIO)
    #define MOSI_SPI_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(MOSI_SPI__PC) && (CY_PSOC4_4200L)
    #define MOSI_SPI_USBIO_ENABLE               ((uint32)0x80000000u)
    #define MOSI_SPI_USBIO_DISABLE              ((uint32)(~MOSI_SPI_USBIO_ENABLE))
    #define MOSI_SPI_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define MOSI_SPI_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define MOSI_SPI_USBIO_ENTER_SLEEP          ((uint32)((1u << MOSI_SPI_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << MOSI_SPI_USBIO_SUSPEND_DEL_SHIFT)))
    #define MOSI_SPI_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << MOSI_SPI_USBIO_SUSPEND_SHIFT)))
    #define MOSI_SPI_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << MOSI_SPI_USBIO_SUSPEND_DEL_SHIFT)))
    #define MOSI_SPI_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(MOSI_SPI__PC)
    /* Port Configuration */
    #define MOSI_SPI_PC                 (* (reg32 *) MOSI_SPI__PC)
#endif
/* Pin State */
#define MOSI_SPI_PS                     (* (reg32 *) MOSI_SPI__PS)
/* Data Register */
#define MOSI_SPI_DR                     (* (reg32 *) MOSI_SPI__DR)
/* Input Buffer Disable Override */
#define MOSI_SPI_INP_DIS                (* (reg32 *) MOSI_SPI__PC2)

/* Interrupt configuration Registers */
#define MOSI_SPI_INTCFG                 (* (reg32 *) MOSI_SPI__INTCFG)
#define MOSI_SPI_INTSTAT                (* (reg32 *) MOSI_SPI__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define MOSI_SPI_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(MOSI_SPI__SIO)
    #define MOSI_SPI_SIO_REG            (* (reg32 *) MOSI_SPI__SIO)
#endif /* (MOSI_SPI__SIO_CFG) */

/* USBIO registers */
#if !defined(MOSI_SPI__PC) && (CY_PSOC4_4200L)
    #define MOSI_SPI_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define MOSI_SPI_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define MOSI_SPI_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define MOSI_SPI_DRIVE_MODE_SHIFT       (0x00u)
#define MOSI_SPI_DRIVE_MODE_MASK        (0x07u << MOSI_SPI_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins MOSI_SPI_H */


/* [] END OF FILE */
