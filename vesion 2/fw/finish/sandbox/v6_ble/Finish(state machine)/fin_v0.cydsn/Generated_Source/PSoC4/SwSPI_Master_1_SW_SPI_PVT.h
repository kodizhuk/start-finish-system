/*****************************************************
 *
 * File Name: SwSPI_Master_1_PVT.h
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

#ifndef CY_SW_TX_UART_SwSPI_Master_1_PVT_H
#define CY_SW_TX_UART_SwSPI_Master_1_PVT_H

#include "SwSPI_Master_1.h"
#include "CyLib.h"
    
/* Device specific registers */
#if (CY_PSOC4)

    #define SwSPI_Master_1_OUTPORT_DR_REG           (*(reg32 *) SwSPI_Master_1_SPI__DR)  /* Data Output Register */
    #define SwSPI_Master_1_OUTPORT_DR_PTR           ( (reg32 *) SwSPI_Master_1_SPI__DR)
    #define SwSPI_Master_1_OUTPORT_PS_REG           (*(reg32 *) SwSPI_Master_1_SPI__PS)  /* Pin State Register */
    #define SwSPI_Master_1_OUTPORT_PS_PTR           ( (reg32 *) SwSPI_Master_1_SPI__PS)
    
    #define SwSPI_Master_1_OUTPORT_PC_REG           (*(reg32 *) SwSPI_Master_1_SPI__PC)
    #define SwSPI_Master_1_OUTPORT_PC_PTR           (*(reg32 *) SwSPI_Master_1_SPI__PC)
    /* Pin State */
    #define SwSPI_Master_1_INPORT_PS_REG            (* (reg32 *) SwSPI_Master_1_SPI_MISO__PS)
    #define SwSPI_Master_1_INPORT_PS_PTR            (  (reg32 *) SwSPI_Master_1_SPI_MISO__PS)
    /* Port Configuration */
    #define SwSPI_Master_1_INPORT_PC_REG            (* (reg32 *) SwSPI_Master_1_SPI_MISO__PC)
    #define SwSPI_Master_1_INPORT_PC_PTR            (  (reg32 *) SwSPI_Master_1_SPI_MISO__PC)
    /* Data Register */
    #define SwSPI_Master_1_INPORT_DR_REG            (* (reg32 *) SwSPI_Master_1_SPI_MISO__DR)
    #define SwSPI_Master_1_INPORT_DR_PTR            (  (reg32 *) SwSPI_Master_1_SPI_MISO__DR)
    
#else

    #define SwSPI_Master_1_OUTPORT_DR_REG           (*(reg8 *) SwSPI_Master_1_SPI__DR)  /* Data Output Register */
    #define SwSPI_Master_1_OUTPORT_DR_PTR           ( (reg8 *) SwSPI_Master_1_SPI__DR)
    #define SwSPI_Master_1_OUTPORT_PS_REG           (*(reg8 *) SwSPI_Master_1_SPI__PS)  /* Pin State Register */
    #define SwSPI_Master_1_OUTPORT_PS_PTR           ( (reg8 *) SwSPI_Master_1_SPI__PS)
    #define SwSPI_Master_1_OUTPORT_PC_PTR           (*(reg32 *) SwSPI_Master_1_SPI__PC)
    
    /* Pin State */
    #define SwSPI_Master_1_INPORT_PS_REG            (* (reg32 *) SwSPI_Master_1_SPI_MISO__PS)
    #define SwSPI_Master_1_INPORT_PS_PTR            (  (reg32 *) SwSPI_Master_1_SPI_MISO__PS)
    /* Data Register */
    #define SwSPI_Master_1_INPORT_DR_REG            (* (reg32 *) SwSPI_Master_1_SPI_MISO__DR)
    #define SwSPI_Master_1_INPORT_DR_PTR            (  (reg32 *) SwSPI_Master_1_SPI_MISO__DR)
        
    #define SwSPI_Master_1_OUTPORT_DM0_REG          (*(reg8 *) SwSPI_Master_1_SPI__DM0) /* Port Drive Mode 0 */
    #define SwSPI_Master_1_OUTPORT_DM0_PTR          ( (reg8 *) SwSPI_Master_1_SPI__DM0)
    #define SwSPI_Master_1_OUTPORT_DM1_REG          (*(reg8 *) SwSPI_Master_1_SPI__DM1) /* Port Drive Mode 1 */
    #define SwSPI_Master_1_OUTPORT_DM1_PTR          ( (reg8 *) SwSPI_Master_1_SPI__DM1)
    #define SwSPI_Master_1_OUTPORT_DM2_REG          (*(reg8 *) SwSPI_Master_1_SPI__DM2) /* Port Drive Mode 2 */
    #define SwSPI_Master_1_OUTPORT_DM2_PTR          ( (reg8 *) SwSPI_Master_1_SPI__DM2)

#endif /* CY_PSOC4 */
    
/* Shift SPI on port*/
#if (0 == SwSPI_Master_1_SPI__SHIFT)
    #define SwSPI_Master_1_OUTPORT_SHIFT               (0x00u)
#elif (1 == SwSPI_Master_1_SPI__SHIFT)
    #define SwSPI_Master_1_OUTPORT_SHIFT               (0x01u)
#elif (2 == SwSPI_Master_1_SPI__SHIFT)
    #define SwSPI_Master_1_OUTPORT_SHIFT               (0x02u)
#elif (3 == SwSPI_Master_1_SPI__SHIFT)
    #define SwSPI_Master_1_OUTPORT_SHIFT               (0x03u)
#elif (4 == SwSPI_Master_1_SPI__SHIFT)
    #define SwSPI_Master_1_OUTPORT_SHIFT               (0x04u)
#elif (5 == SwSPI_Master_1_SPI__SHIFT)
    #define SwSPI_Master_1_OUTPORT_SHIFT               (0x05u)
#else
    #define SwSPI_Master_1_OUTPORT_SHIFT               (0x06u)
#endif /* (0 == SwSPI_Master_1_LCDPort__SHIFT) */

/* OutPort mask */
#define SwSPI_Master_1_OUTPORT_MASK                ((uint8) (SwSPI_Master_1_SPI__MASK))

/* Describe MISO pin-mode */
#if (CY_PSOC4)

    #define SwSPI_Master_1_DM_PIN_STEP              (3u)
    /* Hi-Z Digital is defined by the value of "001b" and this should be set for
    * four data pins, in this way we get - 0x00000249. A similar Strong drive
    * is defined with "110b" so we get 0x00000DB6.
    */
    #define SwSPI_Master_1_HIGH_Z_DATA_DM           ((0x00000249ul) << (SwSPI_Master_1_OUTPORT_SHIFT *\
                                                                          SwSPI_Master_1_DM_PIN_STEP))
    #define SwSPI_Master_1_STRONG_DATA_DM           ((0x00000DB6ul) << (SwSPI_Master_1_OUTPORT_SHIFT *\
                                                                          SwSPI_Master_1_DM_PIN_STEP))
    #define SwSPI_Master_1_DATA_PINS_MASK           (0x00000FFFul)
    #define SwSPI_Master_1_DM_DATA_MASK             ((uint32) (SwSPI_Master_1_DATA_PINS_MASK << \
                                                      (SwSPI_Master_1_OUTPORT_SHIFT * SwSPI_Master_1_DM_PIN_STEP)))

#else

    /* Drive Mode register values for High Z */
    #define SwSPI_Master_1_HIGH_Z_DM0               (0xFFu)
    #define SwSPI_Master_1_HIGH_Z_DM1               (0x00u)
    #define SwSPI_Master_1_HIGH_Z_DM2               (0x00u)

    /* Drive Mode register values for High Z Analog */
    #define SwSPI_Master_1_HIGH_Z_A_DM0             (0x00u)
    #define SwSPI_Master_1_HIGH_Z_A_DM1             (0x00u)
    #define SwSPI_Master_1_HIGH_Z_A_DM2             (0x00u)

    /* Drive Mode register values for Strong */
    #define SwSPI_Master_1_STRONG_DM0               (0x00u)
    #define SwSPI_Master_1_STRONG_DM1               (0xFFu)
    #define SwSPI_Master_1_STRONG_DM2               (0xFFu)

#endif /* CY_PSOC4 */

/* Pin Masks */
#define SwSPI_Master_1_CS                     ((uint8) \
                                                (((uint8) 0x01u) << SwSPI_Master_1_SPI_CS__SHIFT))
#define SwSPI_Master_1_CLK                     ((uint8) \
                                                (((uint8) /*0x02u*/0x01u) << SwSPI_Master_1_SPI_CLK__SHIFT))
#define SwSPI_Master_1_MOSI                      ((uint8) \
                                                (((uint8) /*0x04u*/0x01u) << SwSPI_Master_1_SPI_MOSI__SHIFT))
#define SwSPI_Master_1_MISO                      ((uint8) \
                                                (((uint8) 0x01u) << SwSPI_Master_1_SPI_MISO__SHIFT))
#define SwSPI_Master_1_MISO_MASK               SwSPI_Master_1_SPI_MISO__MASK
#define SwSPI_Master_1_MISO_SHIFT              SwSPI_Master_1_SPI_MISO__SHIFT

/* These names are obsolete and will be removed in future revisions */
#define SwSPI_Master_1_OUTPORT_DR                  SwSPI_Master_1_OUTPORT_DR_REG
#define SwSPI_Master_1_OUTPORT_PS                  SwSPI_Master_1_OUTPORT_PS_REG
#define SwSPI_Master_1_OUTPORT_DM0                 SwSPI_Master_1_OUTPORT_DM0_REG
#define SwSPI_Master_1_OUTPORT_DM1                 SwSPI_Master_1_OUTPORT_DM1_REG
#define SwSPI_Master_1_OUTPORT_DM2                 SwSPI_Master_1_OUTPORT_DM2_REG


/* Common constants */
#define BITES_ON_ONE_BYTE       (8u)
#define SHIFT_ONE_BIT           (1u)

/* Mask for testing low or high bit in one byte */
#define MASK_HIGH_BIT       (0x80)
#define MASK_LOW_BIT        (0x01)

/* Delay low or high state in one period */
#define DELAY_HIGH_STATE        (u)
#define DELAY_LOW_STATE         (u)

#endif /* CY_SW_TX_UART_SwSPI_Master_1_PVT_H */

/* [] END OF FILE */
