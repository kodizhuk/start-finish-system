/*****************************************************
 *
 * File Name: `$INSTANCE_NAME`_PVT.h
 * Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` 
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

#ifndef CY_SW_TX_UART_`$INSTANCE_NAME`_PVT_H
#define CY_SW_TX_UART_`$INSTANCE_NAME`_PVT_H

#include "`$INSTANCE_NAME`.h"
#include "CyLib.h"
    
/* Device specific registers */
#if (CY_PSOC4)


    //#define `$INSTANCE_NAME`_OUTPORT_DR_REG           (*(reg32 *) `$INSTANCE_NAME`_SPI__DR)  /* Data Output Register */
    //#define `$INSTANCE_NAME`_OUTPORT_DR_PTR           ( (reg32 *) `$INSTANCE_NAME`_SPI__DR)
    //#define `$INSTANCE_NAME`_OUTPORT_PS_REG           (*(reg32 *) `$INSTANCE_NAME`_SPI__PS)  /* Pin State Register */
    //#define `$INSTANCE_NAME`_OUTPORT_PS_PTR           ( (reg32 *) `$INSTANCE_NAME`_SPI__PS)
    
    //#define `$INSTANCE_NAME`_OUTPORT_PC_REG           (*(reg32 *) `$INSTANCE_NAME`_SPI__PC)
    //#define `$INSTANCE_NAME`_OUTPORT_PC_PTR           (*(reg32 *) `$INSTANCE_NAME`_SPI__PC)

    /* Pin State */
    #define `$INSTANCE_NAME`_MISO_PS_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_MISO__PS)
    #define `$INSTANCE_NAME`_MISO_PS_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_MISO__PS)
    /* Port Configuration */
    #define `$INSTANCE_NAME`_MISO_PC_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_MISO__PC)
    #define `$INSTANCE_NAME`_MISO_PC_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_MISO__PC)
    /* Data Register */
    #define `$INSTANCE_NAME`_MISO_DR_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_MISO__DR)
    #define `$INSTANCE_NAME`_MISO_DR_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_MISO__DR)
    
    
    /* Pin State */
    #define `$INSTANCE_NAME`_MOSI_PS_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_MOSI__PS)
    #define `$INSTANCE_NAME`_MOSI_PS_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_MOSI__PS)
    /* Port Configuration */
    #define `$INSTANCE_NAME`_MOSI_PC_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_MOSI__PC)
    #define `$INSTANCE_NAME`_MOSI_PC_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_MOSI__PC)
    /* Data Register */
    #define `$INSTANCE_NAME`_MOSI_DR_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_MOSI__DR)
    #define `$INSTANCE_NAME`_MOSI_DR_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_MOSI__DR)

        /* Pin State */
    #define `$INSTANCE_NAME`_SCK_PS_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_SCK__PS)
    #define `$INSTANCE_NAME`_SCK_PS_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_SCK__PS)
    /* Port Configuration */
    #define `$INSTANCE_NAME`_SCK_PC_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_SCK__PC)
    #define `$INSTANCE_NAME`_SCK_PC_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_SCK__PC)
    /* Data Register */
    #define `$INSTANCE_NAME`_SCK_DR_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_SCK__DR)
    #define `$INSTANCE_NAME`_SCK_DR_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_SCK__DR)
    
    
    /* Pin State */
    #define `$INSTANCE_NAME`_CS_PS_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_CS__PS)
    #define `$INSTANCE_NAME`_CS_PS_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_CS__PS)
    /* Port Configuration */
    #define `$INSTANCE_NAME`_CS_PC_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_CS__PC)
    #define `$INSTANCE_NAME`_CS_PC_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_CS__PC)
    /* Data Register */
    #define `$INSTANCE_NAME`_CS_DR_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_CS__DR)
    #define `$INSTANCE_NAME`_CS_DR_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_CS__DR)

#else

    
    /* Pin State */
    #define `$INSTANCE_NAME`_MISO_PS_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_MISO__PS)
    #define `$INSTANCE_NAME`_MISO_PS_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_MISO__PS)
    /* Data Register */
    #define `$INSTANCE_NAME`_MISO_DR_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_MISO__DR)
    #define `$INSTANCE_NAME`_MISO_DR_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_MISO__DR)

    #define `$INSTANCE_NAME`_MOSI_PS_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_MOSI__PS)
    #define `$INSTANCE_NAME`_MOSI_PS_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_MOSI__PS)
    /* Data Register */
    #define `$INSTANCE_NAME`_MOSI_DR_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_MOSI__DR)
    #define `$INSTANCE_NAME`_MOSI_DR_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_MOSI__DR)

    #define `$INSTANCE_NAME`_SCK_PS_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_SCK__PS)
    #define `$INSTANCE_NAME`_SCK_PS_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_SCK__PS)
    /* Data Register */
    #define `$INSTANCE_NAME`_SCK_DR_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_SCK__DR)
    #define `$INSTANCE_NAME`_SCK_DR_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_SCK__DR)

    #define `$INSTANCE_NAME`_CS_PS_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_CS__PS)
    #define `$INSTANCE_NAME`_CS_PS_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_CS__PS)
    /* Data Register */
    #define `$INSTANCE_NAME`_CS_DR_REG            (* (reg32 *) `$INSTANCE_NAME`_SPI_CS__DR)
    #define `$INSTANCE_NAME`_CS_DR_PTR            (  (reg32 *) `$INSTANCE_NAME`_SPI_CS__DR)

    
//    #define `$INSTANCE_NAME`_OUTPORT_DM0_REG          (*(reg8 *) `$INSTANCE_NAME`_SPI__DM0) /* Port Drive Mode 0 */
//    #define `$INSTANCE_NAME`_OUTPORT_DM0_PTR          ( (reg8 *) `$INSTANCE_NAME`_SPI__DM0)
//    #define `$INSTANCE_NAME`_OUTPORT_DM1_REG          (*(reg8 *) `$INSTANCE_NAME`_SPI__DM1) /* Port Drive Mode 1 */
//    #define `$INSTANCE_NAME`_OUTPORT_DM1_PTR          ( (reg8 *) `$INSTANCE_NAME`_SPI__DM1)
//    #define `$INSTANCE_NAME`_OUTPORT_DM2_REG          (*(reg8 *) `$INSTANCE_NAME`_SPI__DM2) /* Port Drive Mode 2 */
//    #define `$INSTANCE_NAME`_OUTPORT_DM2_PTR          ( (reg8 *) `$INSTANCE_NAME`_SPI__DM2)
//
//    #define `$INSTANCE_NAME`_OUTPORT_DR_REG           (*(reg8 *) `$INSTANCE_NAME`_SPI__DR)  /* Data Output Register */
//    #define `$INSTANCE_NAME`_OUTPORT_DR_PTR           ( (reg8 *) `$INSTANCE_NAME`_SPI__DR)
//    #define `$INSTANCE_NAME`_OUTPORT_PS_REG           (*(reg8 *) `$INSTANCE_NAME`_SPI__PS)  /* Pin State Register */
//    #define `$INSTANCE_NAME`_OUTPORT_PS_PTR           ( (reg8 *) `$INSTANCE_NAME`_SPI__PS)
//    #define `$INSTANCE_NAME`_OUTPORT_PC_PTR           (*(reg32 *) `$INSTANCE_NAME`_SPI__PC)

#endif /* CY_PSOC4 */
    
/* Shift SPI on port*/
/*
#if (0 == `$INSTANCE_NAME`_SPI__SHIFT)
    #define `$INSTANCE_NAME`_OUTPORT_SHIFT               (0x00u)
#elif (1 == `$INSTANCE_NAME`_SPI__SHIFT)
    #define `$INSTANCE_NAME`_OUTPORT_SHIFT               (0x01u)
#elif (2 == `$INSTANCE_NAME`_SPI__SHIFT)
    #define `$INSTANCE_NAME`_OUTPORT_SHIFT               (0x02u)
#elif (3 == `$INSTANCE_NAME`_SPI__SHIFT)
    #define `$INSTANCE_NAME`_OUTPORT_SHIFT               (0x03u)
#elif (4 == `$INSTANCE_NAME`_SPI__SHIFT)
    #define `$INSTANCE_NAME`_OUTPORT_SHIFT               (0x04u)
#elif (5 == `$INSTANCE_NAME`_SPI__SHIFT)
    #define `$INSTANCE_NAME`_OUTPORT_SHIFT               (0x05u)
#else
    #define `$INSTANCE_NAME`_OUTPORT_SHIFT               (0x06u)
#endif /* (0 == `$INSTANCE_NAME`_LCDPort__SHIFT) */

/* OutPort mask */
//#define `$INSTANCE_NAME`_OUTPORT_MASK                ((uint8) (`$INSTANCE_NAME`_SPI__MASK))

/* Describe MISO pin-mode */
#if (CY_PSOC4)

    #define `$INSTANCE_NAME`_DM_PIN_STEP              (3u)
    /* Hi-Z Digital is defined by the value of "001b" and this should be set for
    * four data pins, in this way we get - 0x00000249. A similar Strong drive
    * is defined with "110b" so we get 0x00000DB6.
    */
    //#define `$INSTANCE_NAME`_HIGH_Z_DATA_DM           ((0x00000249ul) << (`$INSTANCE_NAME`_OUTPORT_SHIFT *\
                                                                          `$INSTANCE_NAME`_DM_PIN_STEP))
    //#define `$INSTANCE_NAME`_STRONG_DATA_DM           ((0x00000DB6ul) << (`$INSTANCE_NAME`_OUTPORT_SHIFT *\
                                                                          `$INSTANCE_NAME`_DM_PIN_STEP))
    //#define `$INSTANCE_NAME`_DATA_PINS_MASK           (0x00000FFFul)
    //#define `$INSTANCE_NAME`_DM_DATA_MASK             ((uint32) (`$INSTANCE_NAME`_DATA_PINS_MASK << \
                                                      (`$INSTANCE_NAME`_OUTPORT_SHIFT * `$INSTANCE_NAME`_DM_PIN_STEP)))

#else

    /* Drive Mode register values for High Z */
    #define `$INSTANCE_NAME`_HIGH_Z_DM0               (0xFFu)
    #define `$INSTANCE_NAME`_HIGH_Z_DM1               (0x00u)
    #define `$INSTANCE_NAME`_HIGH_Z_DM2               (0x00u)

    /* Drive Mode register values for High Z Analog */
    #define `$INSTANCE_NAME`_HIGH_Z_A_DM0             (0x00u)
    #define `$INSTANCE_NAME`_HIGH_Z_A_DM1             (0x00u)
    #define `$INSTANCE_NAME`_HIGH_Z_A_DM2             (0x00u)

    /* Drive Mode register values for Strong */
    #define `$INSTANCE_NAME`_STRONG_DM0               (0x00u)
    #define `$INSTANCE_NAME`_STRONG_DM1               (0xFFu)
    #define `$INSTANCE_NAME`_STRONG_DM2               (0xFFu)

#endif /* CY_PSOC4 */

/* Pin Masks */
#define `$INSTANCE_NAME`_CS                     ((uint8) \
                                                (((uint8) 0x01u) << `$INSTANCE_NAME`_SPI_CS__SHIFT))
#define `$INSTANCE_NAME`_CLK                     ((uint8) \
                                                (((uint8) 0x01u) << `$INSTANCE_NAME`_SPI_SCK__SHIFT))
#define `$INSTANCE_NAME`_MOSI                      ((uint8) \
                                                (((uint8) 0x01u) << `$INSTANCE_NAME`_SPI_MOSI__SHIFT))
#define `$INSTANCE_NAME`_MISO                      ((uint8) \
                                                (((uint8) 0x01u) << `$INSTANCE_NAME`_SPI_MISO__SHIFT))

#define `$INSTANCE_NAME`_MISO_MASK               `$INSTANCE_NAME`_SPI_MISO__MASK
#define `$INSTANCE_NAME`_MISO_SHIFT              `$INSTANCE_NAME`_SPI_MISO__SHIFT

#define `$INSTANCE_NAME`_MOSI_MASK               `$INSTANCE_NAME`_SPI_MOSI__MASK
#define `$INSTANCE_NAME`_MOSI_SHIFT              `$INSTANCE_NAME`_SPI_MOSI__SHIFT

#define `$INSTANCE_NAME`_SCK_MASK               `$INSTANCE_NAME`_SPI_SCK__MASK
#define `$INSTANCE_NAME`_SCK_SHIFT              `$INSTANCE_NAME`_SPI_SCK__SHIFT

#define `$INSTANCE_NAME`_CS_MASK               `$INSTANCE_NAME`_SPI_CS__MASK
#define `$INSTANCE_NAME`_CS_SHIFT              `$INSTANCE_NAME`_SPI_CS__SHIFT


/* These names are obsolete and will be removed in future revisions */

/*
#define `$INSTANCE_NAME`_OUTPORT_DR                  `$INSTANCE_NAME`_OUTPORT_DR_REG
#define `$INSTANCE_NAME`_OUTPORT_PS                  `$INSTANCE_NAME`_OUTPORT_PS_REG
#define `$INSTANCE_NAME`_OUTPORT_DM0                 `$INSTANCE_NAME`_OUTPORT_DM0_REG
#define `$INSTANCE_NAME`_OUTPORT_DM1                 `$INSTANCE_NAME`_OUTPORT_DM1_REG
#define `$INSTANCE_NAME`_OUTPORT_DM2                 `$INSTANCE_NAME`_OUTPORT_DM2_REG
*/

/* Common constants */
#define BITES_ON_ONE_BYTE       (8u)
#define SHIFT_ONE_BIT           (1u)

/* Mask for testing low or high bit in one byte */
#define MASK_HIGH_BIT       (0x80)
#define MASK_LOW_BIT        (0x01)

/* Delay low or high state in one period */
#define DELAY_HIGH_STATE        (`$Delay_High_State`u)
#define DELAY_LOW_STATE         (`$Delay_Low_State`u)

#endif /* CY_SW_TX_UART_`$INSTANCE_NAME`_PVT_H */

/* [] END OF FILE */
