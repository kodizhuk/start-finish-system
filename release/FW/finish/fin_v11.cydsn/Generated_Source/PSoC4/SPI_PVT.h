/*****************************************************
 *
 * File Name: SPI_PVT.h
 * Version 1.20 
 * Copyright ANDREY TKACHOV, 2016
 
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * Descriprion: 
 *  This file provides private constants and parameter values 
 *  for the Software Serial Programming Interface Component.

 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF PERSONAL LICENSE.
 *
 ****************************************************
*/

#ifndef CY_SW_TX_UART_SPI_PVT_H
#define CY_SW_TX_UART_SPI_PVT_H

#include "SPI.h"
#include "CyLib.h"
    
/* Device specific registers */
#if (CY_PSOC4)


    //#define SPI_OUTPORT_DR_REG           (*(reg32 *) SPI_SPI__DR)  /* Data Output Register */
    //#define SPI_OUTPORT_DR_PTR           ( (reg32 *) SPI_SPI__DR)
    //#define SPI_OUTPORT_PS_REG           (*(reg32 *) SPI_SPI__PS)  /* Pin State Register */
    //#define SPI_OUTPORT_PS_PTR           ( (reg32 *) SPI_SPI__PS)
    
    //#define SPI_OUTPORT_PC_REG           (*(reg32 *) SPI_SPI__PC)
    //#define SPI_OUTPORT_PC_PTR           (*(reg32 *) SPI_SPI__PC)

    /* Pin State */
    #define SPI_MISO_PS_REG            (* (reg32 *) SPI_SPI_MISO__PS)
    #define SPI_MISO_PS_PTR            (  (reg32 *) SPI_SPI_MISO__PS)
    /* Port Configuration */
    #define SPI_MISO_PC_REG            (* (reg32 *) SPI_SPI_MISO__PC)
    #define SPI_MISO_PC_PTR            (  (reg32 *) SPI_SPI_MISO__PC)
    /* Data Register */
    #define SPI_MISO_DR_REG            (* (reg32 *) SPI_SPI_MISO__DR)
    #define SPI_MISO_DR_PTR            (  (reg32 *) SPI_SPI_MISO__DR)
    
    
    /* Pin State */
    #define SPI_MOSI_PS_REG            (* (reg32 *) SPI_SPI_MOSI__PS)
    #define SPI_MOSI_PS_PTR            (  (reg32 *) SPI_SPI_MOSI__PS)
    /* Port Configuration */
    #define SPI_MOSI_PC_REG            (* (reg32 *) SPI_SPI_MOSI__PC)
    #define SPI_MOSI_PC_PTR            (  (reg32 *) SPI_SPI_MOSI__PC)
    /* Data Register */
    #define SPI_MOSI_DR_REG            (* (reg32 *) SPI_SPI_MOSI__DR)
    #define SPI_MOSI_DR_PTR            (  (reg32 *) SPI_SPI_MOSI__DR)

        /* Pin State */
    #define SPI_SCK_PS_REG            (* (reg32 *) SPI_SPI_SCK__PS)
    #define SPI_SCK_PS_PTR            (  (reg32 *) SPI_SPI_SCK__PS)
    /* Port Configuration */
    #define SPI_SCK_PC_REG            (* (reg32 *) SPI_SPI_SCK__PC)
    #define SPI_SCK_PC_PTR            (  (reg32 *) SPI_SPI_SCK__PC)
    /* Data Register */
    #define SPI_SCK_DR_REG            (* (reg32 *) SPI_SPI_SCK__DR)
    #define SPI_SCK_DR_PTR            (  (reg32 *) SPI_SPI_SCK__DR)
    
    
    /* Pin State */
    #define SPI_CS_PS_REG            (* (reg32 *) SPI_SPI_CS__PS)
    #define SPI_CS_PS_PTR            (  (reg32 *) SPI_SPI_CS__PS)
    /* Port Configuration */
    #define SPI_CS_PC_REG            (* (reg32 *) SPI_SPI_CS__PC)
    #define SPI_CS_PC_PTR            (  (reg32 *) SPI_SPI_CS__PC)
    /* Data Register */
    #define SPI_CS_DR_REG            (* (reg32 *) SPI_SPI_CS__DR)
    #define SPI_CS_DR_PTR            (  (reg32 *) SPI_SPI_CS__DR)

#else

    
    /* Pin State */
    #define SPI_MISO_PS_REG            (* (reg32 *) SPI_SPI_MISO__PS)
    #define SPI_MISO_PS_PTR            (  (reg32 *) SPI_SPI_MISO__PS)
    /* Data Register */
    #define SPI_MISO_DR_REG            (* (reg32 *) SPI_SPI_MISO__DR)
    #define SPI_MISO_DR_PTR            (  (reg32 *) SPI_SPI_MISO__DR)

    #define SPI_MOSI_PS_REG            (* (reg32 *) SPI_SPI_MOSI__PS)
    #define SPI_MOSI_PS_PTR            (  (reg32 *) SPI_SPI_MOSI__PS)
    /* Data Register */
    #define SPI_MOSI_DR_REG            (* (reg32 *) SPI_SPI_MOSI__DR)
    #define SPI_MOSI_DR_PTR            (  (reg32 *) SPI_SPI_MOSI__DR)

    #define SPI_SCK_PS_REG            (* (reg32 *) SPI_SPI_SCK__PS)
    #define SPI_SCK_PS_PTR            (  (reg32 *) SPI_SPI_SCK__PS)
    /* Data Register */
    #define SPI_SCK_DR_REG            (* (reg32 *) SPI_SPI_SCK__DR)
    #define SPI_SCK_DR_PTR            (  (reg32 *) SPI_SPI_SCK__DR)

    #define SPI_CS_PS_REG            (* (reg32 *) SPI_SPI_CS__PS)
    #define SPI_CS_PS_PTR            (  (reg32 *) SPI_SPI_CS__PS)
    /* Data Register */
    #define SPI_CS_DR_REG            (* (reg32 *) SPI_SPI_CS__DR)
    #define SPI_CS_DR_PTR            (  (reg32 *) SPI_SPI_CS__DR)

    
//    #define SPI_OUTPORT_DM0_REG          (*(reg8 *) SPI_SPI__DM0) /* Port Drive Mode 0 */
//    #define SPI_OUTPORT_DM0_PTR          ( (reg8 *) SPI_SPI__DM0)
//    #define SPI_OUTPORT_DM1_REG          (*(reg8 *) SPI_SPI__DM1) /* Port Drive Mode 1 */
//    #define SPI_OUTPORT_DM1_PTR          ( (reg8 *) SPI_SPI__DM1)
//    #define SPI_OUTPORT_DM2_REG          (*(reg8 *) SPI_SPI__DM2) /* Port Drive Mode 2 */
//    #define SPI_OUTPORT_DM2_PTR          ( (reg8 *) SPI_SPI__DM2)
//
//    #define SPI_OUTPORT_DR_REG           (*(reg8 *) SPI_SPI__DR)  /* Data Output Register */
//    #define SPI_OUTPORT_DR_PTR           ( (reg8 *) SPI_SPI__DR)
//    #define SPI_OUTPORT_PS_REG           (*(reg8 *) SPI_SPI__PS)  /* Pin State Register */
//    #define SPI_OUTPORT_PS_PTR           ( (reg8 *) SPI_SPI__PS)
//    #define SPI_OUTPORT_PC_PTR           (*(reg32 *) SPI_SPI__PC)

#endif /* CY_PSOC4 */
    
/* Shift SPI on port*/
/*
#if (0 == SPI_SPI__SHIFT)
    #define SPI_OUTPORT_SHIFT               (0x00u)
#elif (1 == SPI_SPI__SHIFT)
    #define SPI_OUTPORT_SHIFT               (0x01u)
#elif (2 == SPI_SPI__SHIFT)
    #define SPI_OUTPORT_SHIFT               (0x02u)
#elif (3 == SPI_SPI__SHIFT)
    #define SPI_OUTPORT_SHIFT               (0x03u)
#elif (4 == SPI_SPI__SHIFT)
    #define SPI_OUTPORT_SHIFT               (0x04u)
#elif (5 == SPI_SPI__SHIFT)
    #define SPI_OUTPORT_SHIFT               (0x05u)
#else
    #define SPI_OUTPORT_SHIFT               (0x06u)
#endif /* (0 == SPI_LCDPort__SHIFT) */

/* OutPort mask */
//#define SPI_OUTPORT_MASK                ((uint8) (SPI_SPI__MASK))

/* Describe MISO pin-mode */
#if (CY_PSOC4)

    #define SPI_DM_PIN_STEP              (3u)
    /* Hi-Z Digital is defined by the value of "001b" and this should be set for
    * four data pins, in this way we get - 0x00000249. A similar Strong drive
    * is defined with "110b" so we get 0x00000DB6.
    */
    //#define SPI_HIGH_Z_DATA_DM           ((0x00000249ul) << (SPI_OUTPORT_SHIFT *\
                                                                          SPI_DM_PIN_STEP))
    //#define SPI_STRONG_DATA_DM           ((0x00000DB6ul) << (SPI_OUTPORT_SHIFT *\
                                                                          SPI_DM_PIN_STEP))
    //#define SPI_DATA_PINS_MASK           (0x00000FFFul)
    //#define SPI_DM_DATA_MASK             ((uint32) (SPI_DATA_PINS_MASK << \
                                                      (SPI_OUTPORT_SHIFT * SPI_DM_PIN_STEP)))

#else

    /* Drive Mode register values for High Z */
    #define SPI_HIGH_Z_DM0               (0xFFu)
    #define SPI_HIGH_Z_DM1               (0x00u)
    #define SPI_HIGH_Z_DM2               (0x00u)

    /* Drive Mode register values for High Z Analog */
    #define SPI_HIGH_Z_A_DM0             (0x00u)
    #define SPI_HIGH_Z_A_DM1             (0x00u)
    #define SPI_HIGH_Z_A_DM2             (0x00u)

    /* Drive Mode register values for Strong */
    #define SPI_STRONG_DM0               (0x00u)
    #define SPI_STRONG_DM1               (0xFFu)
    #define SPI_STRONG_DM2               (0xFFu)

#endif /* CY_PSOC4 */

/* Pin Masks */
#define SPI_CS                     ((uint8) \
                                                (((uint8) 0x01u) << SPI_SPI_CS__SHIFT))
#define SPI_CLK                     ((uint8) \
                                                (((uint8) 0x01u) << SPI_SPI_SCK__SHIFT))
#define SPI_MOSI                      ((uint8) \
                                                (((uint8) 0x01u) << SPI_SPI_MOSI__SHIFT))
#define SPI_MISO                      ((uint8) \
                                                (((uint8) 0x01u) << SPI_SPI_MISO__SHIFT))

#define SPI_MISO_MASK               SPI_SPI_MISO__MASK
#define SPI_MISO_SHIFT              SPI_SPI_MISO__SHIFT

#define SPI_MOSI_MASK               SPI_SPI_MOSI__MASK
#define SPI_MOSI_SHIFT              SPI_SPI_MOSI__SHIFT

#define SPI_SCK_MASK               SPI_SPI_SCK__MASK
#define SPI_SCK_SHIFT              SPI_SPI_SCK__SHIFT

#define SPI_CS_MASK               SPI_SPI_CS__MASK
#define SPI_CS_SHIFT              SPI_SPI_CS__SHIFT


/* These names are obsolete and will be removed in future revisions */

/*
#define SPI_OUTPORT_DR                  SPI_OUTPORT_DR_REG
#define SPI_OUTPORT_PS                  SPI_OUTPORT_PS_REG
#define SPI_OUTPORT_DM0                 SPI_OUTPORT_DM0_REG
#define SPI_OUTPORT_DM1                 SPI_OUTPORT_DM1_REG
#define SPI_OUTPORT_DM2                 SPI_OUTPORT_DM2_REG
*/

/* Common constants */
#define BITES_ON_ONE_BYTE       (8u)
#define SHIFT_ONE_BIT           (1u)

/* Mask for testing low or high bit in one byte */
#define MASK_HIGH_BIT       (0x80)
#define MASK_LOW_BIT        (0x01)

/* Delay low or high state in one period */
#define DELAY_HIGH_STATE        (10u)
#define DELAY_LOW_STATE         (10u)

#endif /* CY_SW_TX_UART_SPI_PVT_H */

/* [] END OF FILE */
