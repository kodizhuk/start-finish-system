#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include "cydevice_trm.h"

/* LCD_LCDPort */
#define LCD_LCDPort__0__DM__MASK 0x07u
#define LCD_LCDPort__0__DM__SHIFT 0u
#define LCD_LCDPort__0__DR CYREG_PRT2_DR
#define LCD_LCDPort__0__HSIOM CYREG_HSIOM_PORT_SEL2
#define LCD_LCDPort__0__HSIOM_MASK 0x0000000Fu
#define LCD_LCDPort__0__HSIOM_SHIFT 0u
#define LCD_LCDPort__0__INTCFG CYREG_PRT2_INTCFG
#define LCD_LCDPort__0__INTSTAT CYREG_PRT2_INTSTAT
#define LCD_LCDPort__0__MASK 0x01u
#define LCD_LCDPort__0__PA__CFG0 CYREG_UDB_PA2_CFG0
#define LCD_LCDPort__0__PA__CFG1 CYREG_UDB_PA2_CFG1
#define LCD_LCDPort__0__PA__CFG10 CYREG_UDB_PA2_CFG10
#define LCD_LCDPort__0__PA__CFG11 CYREG_UDB_PA2_CFG11
#define LCD_LCDPort__0__PA__CFG12 CYREG_UDB_PA2_CFG12
#define LCD_LCDPort__0__PA__CFG13 CYREG_UDB_PA2_CFG13
#define LCD_LCDPort__0__PA__CFG14 CYREG_UDB_PA2_CFG14
#define LCD_LCDPort__0__PA__CFG2 CYREG_UDB_PA2_CFG2
#define LCD_LCDPort__0__PA__CFG3 CYREG_UDB_PA2_CFG3
#define LCD_LCDPort__0__PA__CFG4 CYREG_UDB_PA2_CFG4
#define LCD_LCDPort__0__PA__CFG5 CYREG_UDB_PA2_CFG5
#define LCD_LCDPort__0__PA__CFG6 CYREG_UDB_PA2_CFG6
#define LCD_LCDPort__0__PA__CFG7 CYREG_UDB_PA2_CFG7
#define LCD_LCDPort__0__PA__CFG8 CYREG_UDB_PA2_CFG8
#define LCD_LCDPort__0__PA__CFG9 CYREG_UDB_PA2_CFG9
#define LCD_LCDPort__0__PC CYREG_PRT2_PC
#define LCD_LCDPort__0__PC2 CYREG_PRT2_PC2
#define LCD_LCDPort__0__PORT 2u
#define LCD_LCDPort__0__PS CYREG_PRT2_PS
#define LCD_LCDPort__0__SHIFT 0u
#define LCD_LCDPort__1__DM__MASK 0x38u
#define LCD_LCDPort__1__DM__SHIFT 3u
#define LCD_LCDPort__1__DR CYREG_PRT2_DR
#define LCD_LCDPort__1__HSIOM CYREG_HSIOM_PORT_SEL2
#define LCD_LCDPort__1__HSIOM_MASK 0x000000F0u
#define LCD_LCDPort__1__HSIOM_SHIFT 4u
#define LCD_LCDPort__1__INTCFG CYREG_PRT2_INTCFG
#define LCD_LCDPort__1__INTSTAT CYREG_PRT2_INTSTAT
#define LCD_LCDPort__1__MASK 0x02u
#define LCD_LCDPort__1__PA__CFG0 CYREG_UDB_PA2_CFG0
#define LCD_LCDPort__1__PA__CFG1 CYREG_UDB_PA2_CFG1
#define LCD_LCDPort__1__PA__CFG10 CYREG_UDB_PA2_CFG10
#define LCD_LCDPort__1__PA__CFG11 CYREG_UDB_PA2_CFG11
#define LCD_LCDPort__1__PA__CFG12 CYREG_UDB_PA2_CFG12
#define LCD_LCDPort__1__PA__CFG13 CYREG_UDB_PA2_CFG13
#define LCD_LCDPort__1__PA__CFG14 CYREG_UDB_PA2_CFG14
#define LCD_LCDPort__1__PA__CFG2 CYREG_UDB_PA2_CFG2
#define LCD_LCDPort__1__PA__CFG3 CYREG_UDB_PA2_CFG3
#define LCD_LCDPort__1__PA__CFG4 CYREG_UDB_PA2_CFG4
#define LCD_LCDPort__1__PA__CFG5 CYREG_UDB_PA2_CFG5
#define LCD_LCDPort__1__PA__CFG6 CYREG_UDB_PA2_CFG6
#define LCD_LCDPort__1__PA__CFG7 CYREG_UDB_PA2_CFG7
#define LCD_LCDPort__1__PA__CFG8 CYREG_UDB_PA2_CFG8
#define LCD_LCDPort__1__PA__CFG9 CYREG_UDB_PA2_CFG9
#define LCD_LCDPort__1__PC CYREG_PRT2_PC
#define LCD_LCDPort__1__PC2 CYREG_PRT2_PC2
#define LCD_LCDPort__1__PORT 2u
#define LCD_LCDPort__1__PS CYREG_PRT2_PS
#define LCD_LCDPort__1__SHIFT 1u
#define LCD_LCDPort__2__DM__MASK 0x1C0u
#define LCD_LCDPort__2__DM__SHIFT 6u
#define LCD_LCDPort__2__DR CYREG_PRT2_DR
#define LCD_LCDPort__2__HSIOM CYREG_HSIOM_PORT_SEL2
#define LCD_LCDPort__2__HSIOM_MASK 0x00000F00u
#define LCD_LCDPort__2__HSIOM_SHIFT 8u
#define LCD_LCDPort__2__INTCFG CYREG_PRT2_INTCFG
#define LCD_LCDPort__2__INTSTAT CYREG_PRT2_INTSTAT
#define LCD_LCDPort__2__MASK 0x04u
#define LCD_LCDPort__2__PA__CFG0 CYREG_UDB_PA2_CFG0
#define LCD_LCDPort__2__PA__CFG1 CYREG_UDB_PA2_CFG1
#define LCD_LCDPort__2__PA__CFG10 CYREG_UDB_PA2_CFG10
#define LCD_LCDPort__2__PA__CFG11 CYREG_UDB_PA2_CFG11
#define LCD_LCDPort__2__PA__CFG12 CYREG_UDB_PA2_CFG12
#define LCD_LCDPort__2__PA__CFG13 CYREG_UDB_PA2_CFG13
#define LCD_LCDPort__2__PA__CFG14 CYREG_UDB_PA2_CFG14
#define LCD_LCDPort__2__PA__CFG2 CYREG_UDB_PA2_CFG2
#define LCD_LCDPort__2__PA__CFG3 CYREG_UDB_PA2_CFG3
#define LCD_LCDPort__2__PA__CFG4 CYREG_UDB_PA2_CFG4
#define LCD_LCDPort__2__PA__CFG5 CYREG_UDB_PA2_CFG5
#define LCD_LCDPort__2__PA__CFG6 CYREG_UDB_PA2_CFG6
#define LCD_LCDPort__2__PA__CFG7 CYREG_UDB_PA2_CFG7
#define LCD_LCDPort__2__PA__CFG8 CYREG_UDB_PA2_CFG8
#define LCD_LCDPort__2__PA__CFG9 CYREG_UDB_PA2_CFG9
#define LCD_LCDPort__2__PC CYREG_PRT2_PC
#define LCD_LCDPort__2__PC2 CYREG_PRT2_PC2
#define LCD_LCDPort__2__PORT 2u
#define LCD_LCDPort__2__PS CYREG_PRT2_PS
#define LCD_LCDPort__2__SHIFT 2u
#define LCD_LCDPort__3__DM__MASK 0xE00u
#define LCD_LCDPort__3__DM__SHIFT 9u
#define LCD_LCDPort__3__DR CYREG_PRT2_DR
#define LCD_LCDPort__3__HSIOM CYREG_HSIOM_PORT_SEL2
#define LCD_LCDPort__3__HSIOM_MASK 0x0000F000u
#define LCD_LCDPort__3__HSIOM_SHIFT 12u
#define LCD_LCDPort__3__INTCFG CYREG_PRT2_INTCFG
#define LCD_LCDPort__3__INTSTAT CYREG_PRT2_INTSTAT
#define LCD_LCDPort__3__MASK 0x08u
#define LCD_LCDPort__3__PA__CFG0 CYREG_UDB_PA2_CFG0
#define LCD_LCDPort__3__PA__CFG1 CYREG_UDB_PA2_CFG1
#define LCD_LCDPort__3__PA__CFG10 CYREG_UDB_PA2_CFG10
#define LCD_LCDPort__3__PA__CFG11 CYREG_UDB_PA2_CFG11
#define LCD_LCDPort__3__PA__CFG12 CYREG_UDB_PA2_CFG12
#define LCD_LCDPort__3__PA__CFG13 CYREG_UDB_PA2_CFG13
#define LCD_LCDPort__3__PA__CFG14 CYREG_UDB_PA2_CFG14
#define LCD_LCDPort__3__PA__CFG2 CYREG_UDB_PA2_CFG2
#define LCD_LCDPort__3__PA__CFG3 CYREG_UDB_PA2_CFG3
#define LCD_LCDPort__3__PA__CFG4 CYREG_UDB_PA2_CFG4
#define LCD_LCDPort__3__PA__CFG5 CYREG_UDB_PA2_CFG5
#define LCD_LCDPort__3__PA__CFG6 CYREG_UDB_PA2_CFG6
#define LCD_LCDPort__3__PA__CFG7 CYREG_UDB_PA2_CFG7
#define LCD_LCDPort__3__PA__CFG8 CYREG_UDB_PA2_CFG8
#define LCD_LCDPort__3__PA__CFG9 CYREG_UDB_PA2_CFG9
#define LCD_LCDPort__3__PC CYREG_PRT2_PC
#define LCD_LCDPort__3__PC2 CYREG_PRT2_PC2
#define LCD_LCDPort__3__PORT 2u
#define LCD_LCDPort__3__PS CYREG_PRT2_PS
#define LCD_LCDPort__3__SHIFT 3u
#define LCD_LCDPort__4__DM__MASK 0x7000u
#define LCD_LCDPort__4__DM__SHIFT 12u
#define LCD_LCDPort__4__DR CYREG_PRT2_DR
#define LCD_LCDPort__4__HSIOM CYREG_HSIOM_PORT_SEL2
#define LCD_LCDPort__4__HSIOM_MASK 0x000F0000u
#define LCD_LCDPort__4__HSIOM_SHIFT 16u
#define LCD_LCDPort__4__INTCFG CYREG_PRT2_INTCFG
#define LCD_LCDPort__4__INTSTAT CYREG_PRT2_INTSTAT
#define LCD_LCDPort__4__MASK 0x10u
#define LCD_LCDPort__4__PA__CFG0 CYREG_UDB_PA2_CFG0
#define LCD_LCDPort__4__PA__CFG1 CYREG_UDB_PA2_CFG1
#define LCD_LCDPort__4__PA__CFG10 CYREG_UDB_PA2_CFG10
#define LCD_LCDPort__4__PA__CFG11 CYREG_UDB_PA2_CFG11
#define LCD_LCDPort__4__PA__CFG12 CYREG_UDB_PA2_CFG12
#define LCD_LCDPort__4__PA__CFG13 CYREG_UDB_PA2_CFG13
#define LCD_LCDPort__4__PA__CFG14 CYREG_UDB_PA2_CFG14
#define LCD_LCDPort__4__PA__CFG2 CYREG_UDB_PA2_CFG2
#define LCD_LCDPort__4__PA__CFG3 CYREG_UDB_PA2_CFG3
#define LCD_LCDPort__4__PA__CFG4 CYREG_UDB_PA2_CFG4
#define LCD_LCDPort__4__PA__CFG5 CYREG_UDB_PA2_CFG5
#define LCD_LCDPort__4__PA__CFG6 CYREG_UDB_PA2_CFG6
#define LCD_LCDPort__4__PA__CFG7 CYREG_UDB_PA2_CFG7
#define LCD_LCDPort__4__PA__CFG8 CYREG_UDB_PA2_CFG8
#define LCD_LCDPort__4__PA__CFG9 CYREG_UDB_PA2_CFG9
#define LCD_LCDPort__4__PC CYREG_PRT2_PC
#define LCD_LCDPort__4__PC2 CYREG_PRT2_PC2
#define LCD_LCDPort__4__PORT 2u
#define LCD_LCDPort__4__PS CYREG_PRT2_PS
#define LCD_LCDPort__4__SHIFT 4u
#define LCD_LCDPort__5__DM__MASK 0x38000u
#define LCD_LCDPort__5__DM__SHIFT 15u
#define LCD_LCDPort__5__DR CYREG_PRT2_DR
#define LCD_LCDPort__5__HSIOM CYREG_HSIOM_PORT_SEL2
#define LCD_LCDPort__5__HSIOM_MASK 0x00F00000u
#define LCD_LCDPort__5__HSIOM_SHIFT 20u
#define LCD_LCDPort__5__INTCFG CYREG_PRT2_INTCFG
#define LCD_LCDPort__5__INTSTAT CYREG_PRT2_INTSTAT
#define LCD_LCDPort__5__MASK 0x20u
#define LCD_LCDPort__5__PA__CFG0 CYREG_UDB_PA2_CFG0
#define LCD_LCDPort__5__PA__CFG1 CYREG_UDB_PA2_CFG1
#define LCD_LCDPort__5__PA__CFG10 CYREG_UDB_PA2_CFG10
#define LCD_LCDPort__5__PA__CFG11 CYREG_UDB_PA2_CFG11
#define LCD_LCDPort__5__PA__CFG12 CYREG_UDB_PA2_CFG12
#define LCD_LCDPort__5__PA__CFG13 CYREG_UDB_PA2_CFG13
#define LCD_LCDPort__5__PA__CFG14 CYREG_UDB_PA2_CFG14
#define LCD_LCDPort__5__PA__CFG2 CYREG_UDB_PA2_CFG2
#define LCD_LCDPort__5__PA__CFG3 CYREG_UDB_PA2_CFG3
#define LCD_LCDPort__5__PA__CFG4 CYREG_UDB_PA2_CFG4
#define LCD_LCDPort__5__PA__CFG5 CYREG_UDB_PA2_CFG5
#define LCD_LCDPort__5__PA__CFG6 CYREG_UDB_PA2_CFG6
#define LCD_LCDPort__5__PA__CFG7 CYREG_UDB_PA2_CFG7
#define LCD_LCDPort__5__PA__CFG8 CYREG_UDB_PA2_CFG8
#define LCD_LCDPort__5__PA__CFG9 CYREG_UDB_PA2_CFG9
#define LCD_LCDPort__5__PC CYREG_PRT2_PC
#define LCD_LCDPort__5__PC2 CYREG_PRT2_PC2
#define LCD_LCDPort__5__PORT 2u
#define LCD_LCDPort__5__PS CYREG_PRT2_PS
#define LCD_LCDPort__5__SHIFT 5u
#define LCD_LCDPort__6__DM__MASK 0x1C0000u
#define LCD_LCDPort__6__DM__SHIFT 18u
#define LCD_LCDPort__6__DR CYREG_PRT2_DR
#define LCD_LCDPort__6__HSIOM CYREG_HSIOM_PORT_SEL2
#define LCD_LCDPort__6__HSIOM_MASK 0x0F000000u
#define LCD_LCDPort__6__HSIOM_SHIFT 24u
#define LCD_LCDPort__6__INTCFG CYREG_PRT2_INTCFG
#define LCD_LCDPort__6__INTSTAT CYREG_PRT2_INTSTAT
#define LCD_LCDPort__6__MASK 0x40u
#define LCD_LCDPort__6__PA__CFG0 CYREG_UDB_PA2_CFG0
#define LCD_LCDPort__6__PA__CFG1 CYREG_UDB_PA2_CFG1
#define LCD_LCDPort__6__PA__CFG10 CYREG_UDB_PA2_CFG10
#define LCD_LCDPort__6__PA__CFG11 CYREG_UDB_PA2_CFG11
#define LCD_LCDPort__6__PA__CFG12 CYREG_UDB_PA2_CFG12
#define LCD_LCDPort__6__PA__CFG13 CYREG_UDB_PA2_CFG13
#define LCD_LCDPort__6__PA__CFG14 CYREG_UDB_PA2_CFG14
#define LCD_LCDPort__6__PA__CFG2 CYREG_UDB_PA2_CFG2
#define LCD_LCDPort__6__PA__CFG3 CYREG_UDB_PA2_CFG3
#define LCD_LCDPort__6__PA__CFG4 CYREG_UDB_PA2_CFG4
#define LCD_LCDPort__6__PA__CFG5 CYREG_UDB_PA2_CFG5
#define LCD_LCDPort__6__PA__CFG6 CYREG_UDB_PA2_CFG6
#define LCD_LCDPort__6__PA__CFG7 CYREG_UDB_PA2_CFG7
#define LCD_LCDPort__6__PA__CFG8 CYREG_UDB_PA2_CFG8
#define LCD_LCDPort__6__PA__CFG9 CYREG_UDB_PA2_CFG9
#define LCD_LCDPort__6__PC CYREG_PRT2_PC
#define LCD_LCDPort__6__PC2 CYREG_PRT2_PC2
#define LCD_LCDPort__6__PORT 2u
#define LCD_LCDPort__6__PS CYREG_PRT2_PS
#define LCD_LCDPort__6__SHIFT 6u
#define LCD_LCDPort__DR CYREG_PRT2_DR
#define LCD_LCDPort__INTCFG CYREG_PRT2_INTCFG
#define LCD_LCDPort__INTSTAT CYREG_PRT2_INTSTAT
#define LCD_LCDPort__MASK 0x7Fu
#define LCD_LCDPort__PA__CFG0 CYREG_UDB_PA2_CFG0
#define LCD_LCDPort__PA__CFG1 CYREG_UDB_PA2_CFG1
#define LCD_LCDPort__PA__CFG10 CYREG_UDB_PA2_CFG10
#define LCD_LCDPort__PA__CFG11 CYREG_UDB_PA2_CFG11
#define LCD_LCDPort__PA__CFG12 CYREG_UDB_PA2_CFG12
#define LCD_LCDPort__PA__CFG13 CYREG_UDB_PA2_CFG13
#define LCD_LCDPort__PA__CFG14 CYREG_UDB_PA2_CFG14
#define LCD_LCDPort__PA__CFG2 CYREG_UDB_PA2_CFG2
#define LCD_LCDPort__PA__CFG3 CYREG_UDB_PA2_CFG3
#define LCD_LCDPort__PA__CFG4 CYREG_UDB_PA2_CFG4
#define LCD_LCDPort__PA__CFG5 CYREG_UDB_PA2_CFG5
#define LCD_LCDPort__PA__CFG6 CYREG_UDB_PA2_CFG6
#define LCD_LCDPort__PA__CFG7 CYREG_UDB_PA2_CFG7
#define LCD_LCDPort__PA__CFG8 CYREG_UDB_PA2_CFG8
#define LCD_LCDPort__PA__CFG9 CYREG_UDB_PA2_CFG9
#define LCD_LCDPort__PC CYREG_PRT2_PC
#define LCD_LCDPort__PC2 CYREG_PRT2_PC2
#define LCD_LCDPort__PORT 2u
#define LCD_LCDPort__PS CYREG_PRT2_PS
#define LCD_LCDPort__SHIFT 0u

/* GatePin */
#define GatePin__0__DM__MASK 0xE00000u
#define GatePin__0__DM__SHIFT 21u
#define GatePin__0__DR CYREG_PRT0_DR
#define GatePin__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define GatePin__0__HSIOM_MASK 0xF0000000u
#define GatePin__0__HSIOM_SHIFT 28u
#define GatePin__0__INTCFG CYREG_PRT0_INTCFG
#define GatePin__0__INTSTAT CYREG_PRT0_INTSTAT
#define GatePin__0__MASK 0x80u
#define GatePin__0__PA__CFG0 CYREG_UDB_PA0_CFG0
#define GatePin__0__PA__CFG1 CYREG_UDB_PA0_CFG1
#define GatePin__0__PA__CFG10 CYREG_UDB_PA0_CFG10
#define GatePin__0__PA__CFG11 CYREG_UDB_PA0_CFG11
#define GatePin__0__PA__CFG12 CYREG_UDB_PA0_CFG12
#define GatePin__0__PA__CFG13 CYREG_UDB_PA0_CFG13
#define GatePin__0__PA__CFG14 CYREG_UDB_PA0_CFG14
#define GatePin__0__PA__CFG2 CYREG_UDB_PA0_CFG2
#define GatePin__0__PA__CFG3 CYREG_UDB_PA0_CFG3
#define GatePin__0__PA__CFG4 CYREG_UDB_PA0_CFG4
#define GatePin__0__PA__CFG5 CYREG_UDB_PA0_CFG5
#define GatePin__0__PA__CFG6 CYREG_UDB_PA0_CFG6
#define GatePin__0__PA__CFG7 CYREG_UDB_PA0_CFG7
#define GatePin__0__PA__CFG8 CYREG_UDB_PA0_CFG8
#define GatePin__0__PA__CFG9 CYREG_UDB_PA0_CFG9
#define GatePin__0__PC CYREG_PRT0_PC
#define GatePin__0__PC2 CYREG_PRT0_PC2
#define GatePin__0__PORT 0u
#define GatePin__0__PS CYREG_PRT0_PS
#define GatePin__0__SHIFT 7u
#define GatePin__DR CYREG_PRT0_DR
#define GatePin__INTCFG CYREG_PRT0_INTCFG
#define GatePin__INTSTAT CYREG_PRT0_INTSTAT
#define GatePin__MASK 0x80u
#define GatePin__PA__CFG0 CYREG_UDB_PA0_CFG0
#define GatePin__PA__CFG1 CYREG_UDB_PA0_CFG1
#define GatePin__PA__CFG10 CYREG_UDB_PA0_CFG10
#define GatePin__PA__CFG11 CYREG_UDB_PA0_CFG11
#define GatePin__PA__CFG12 CYREG_UDB_PA0_CFG12
#define GatePin__PA__CFG13 CYREG_UDB_PA0_CFG13
#define GatePin__PA__CFG14 CYREG_UDB_PA0_CFG14
#define GatePin__PA__CFG2 CYREG_UDB_PA0_CFG2
#define GatePin__PA__CFG3 CYREG_UDB_PA0_CFG3
#define GatePin__PA__CFG4 CYREG_UDB_PA0_CFG4
#define GatePin__PA__CFG5 CYREG_UDB_PA0_CFG5
#define GatePin__PA__CFG6 CYREG_UDB_PA0_CFG6
#define GatePin__PA__CFG7 CYREG_UDB_PA0_CFG7
#define GatePin__PA__CFG8 CYREG_UDB_PA0_CFG8
#define GatePin__PA__CFG9 CYREG_UDB_PA0_CFG9
#define GatePin__PC CYREG_PRT0_PC
#define GatePin__PC2 CYREG_PRT0_PC2
#define GatePin__PORT 0u
#define GatePin__PS CYREG_PRT0_PS
#define GatePin__SHIFT 7u

/* LED_PIN */
#define LED_PIN__0__DM__MASK 0x1C0u
#define LED_PIN__0__DM__SHIFT 6u
#define LED_PIN__0__DR CYREG_PRT0_DR
#define LED_PIN__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define LED_PIN__0__HSIOM_MASK 0x00000F00u
#define LED_PIN__0__HSIOM_SHIFT 8u
#define LED_PIN__0__INTCFG CYREG_PRT0_INTCFG
#define LED_PIN__0__INTSTAT CYREG_PRT0_INTSTAT
#define LED_PIN__0__MASK 0x04u
#define LED_PIN__0__PA__CFG0 CYREG_UDB_PA0_CFG0
#define LED_PIN__0__PA__CFG1 CYREG_UDB_PA0_CFG1
#define LED_PIN__0__PA__CFG10 CYREG_UDB_PA0_CFG10
#define LED_PIN__0__PA__CFG11 CYREG_UDB_PA0_CFG11
#define LED_PIN__0__PA__CFG12 CYREG_UDB_PA0_CFG12
#define LED_PIN__0__PA__CFG13 CYREG_UDB_PA0_CFG13
#define LED_PIN__0__PA__CFG14 CYREG_UDB_PA0_CFG14
#define LED_PIN__0__PA__CFG2 CYREG_UDB_PA0_CFG2
#define LED_PIN__0__PA__CFG3 CYREG_UDB_PA0_CFG3
#define LED_PIN__0__PA__CFG4 CYREG_UDB_PA0_CFG4
#define LED_PIN__0__PA__CFG5 CYREG_UDB_PA0_CFG5
#define LED_PIN__0__PA__CFG6 CYREG_UDB_PA0_CFG6
#define LED_PIN__0__PA__CFG7 CYREG_UDB_PA0_CFG7
#define LED_PIN__0__PA__CFG8 CYREG_UDB_PA0_CFG8
#define LED_PIN__0__PA__CFG9 CYREG_UDB_PA0_CFG9
#define LED_PIN__0__PC CYREG_PRT0_PC
#define LED_PIN__0__PC2 CYREG_PRT0_PC2
#define LED_PIN__0__PORT 0u
#define LED_PIN__0__PS CYREG_PRT0_PS
#define LED_PIN__0__SHIFT 2u
#define LED_PIN__DR CYREG_PRT0_DR
#define LED_PIN__INTCFG CYREG_PRT0_INTCFG
#define LED_PIN__INTSTAT CYREG_PRT0_INTSTAT
#define LED_PIN__MASK 0x04u
#define LED_PIN__PA__CFG0 CYREG_UDB_PA0_CFG0
#define LED_PIN__PA__CFG1 CYREG_UDB_PA0_CFG1
#define LED_PIN__PA__CFG10 CYREG_UDB_PA0_CFG10
#define LED_PIN__PA__CFG11 CYREG_UDB_PA0_CFG11
#define LED_PIN__PA__CFG12 CYREG_UDB_PA0_CFG12
#define LED_PIN__PA__CFG13 CYREG_UDB_PA0_CFG13
#define LED_PIN__PA__CFG14 CYREG_UDB_PA0_CFG14
#define LED_PIN__PA__CFG2 CYREG_UDB_PA0_CFG2
#define LED_PIN__PA__CFG3 CYREG_UDB_PA0_CFG3
#define LED_PIN__PA__CFG4 CYREG_UDB_PA0_CFG4
#define LED_PIN__PA__CFG5 CYREG_UDB_PA0_CFG5
#define LED_PIN__PA__CFG6 CYREG_UDB_PA0_CFG6
#define LED_PIN__PA__CFG7 CYREG_UDB_PA0_CFG7
#define LED_PIN__PA__CFG8 CYREG_UDB_PA0_CFG8
#define LED_PIN__PA__CFG9 CYREG_UDB_PA0_CFG9
#define LED_PIN__PC CYREG_PRT0_PC
#define LED_PIN__PC2 CYREG_PRT0_PC2
#define LED_PIN__PORT 0u
#define LED_PIN__PS CYREG_PRT0_PS
#define LED_PIN__SHIFT 2u

/* UART_XB_rx */
#define UART_XB_rx__0__DM__MASK 0x07u
#define UART_XB_rx__0__DM__SHIFT 0u
#define UART_XB_rx__0__DR CYREG_PRT4_DR
#define UART_XB_rx__0__HSIOM CYREG_HSIOM_PORT_SEL4
#define UART_XB_rx__0__HSIOM_GPIO 0u
#define UART_XB_rx__0__HSIOM_I2C 14u
#define UART_XB_rx__0__HSIOM_I2C_SCL 14u
#define UART_XB_rx__0__HSIOM_MASK 0x0000000Fu
#define UART_XB_rx__0__HSIOM_SHIFT 0u
#define UART_XB_rx__0__HSIOM_SPI 15u
#define UART_XB_rx__0__HSIOM_SPI_MOSI 15u
#define UART_XB_rx__0__HSIOM_UART 9u
#define UART_XB_rx__0__HSIOM_UART_RX 9u
#define UART_XB_rx__0__INTCFG CYREG_PRT4_INTCFG
#define UART_XB_rx__0__INTSTAT CYREG_PRT4_INTSTAT
#define UART_XB_rx__0__MASK 0x01u
#define UART_XB_rx__0__PC CYREG_PRT4_PC
#define UART_XB_rx__0__PC2 CYREG_PRT4_PC2
#define UART_XB_rx__0__PORT 4u
#define UART_XB_rx__0__PS CYREG_PRT4_PS
#define UART_XB_rx__0__SHIFT 0u
#define UART_XB_rx__DR CYREG_PRT4_DR
#define UART_XB_rx__INTCFG CYREG_PRT4_INTCFG
#define UART_XB_rx__INTSTAT CYREG_PRT4_INTSTAT
#define UART_XB_rx__MASK 0x01u
#define UART_XB_rx__PC CYREG_PRT4_PC
#define UART_XB_rx__PC2 CYREG_PRT4_PC2
#define UART_XB_rx__PORT 4u
#define UART_XB_rx__PS CYREG_PRT4_PS
#define UART_XB_rx__SHIFT 0u

/* UART_XB_SCB */
#define UART_XB_SCB__BIST_CONTROL CYREG_SCB0_BIST_CONTROL
#define UART_XB_SCB__BIST_DATA CYREG_SCB0_BIST_DATA
#define UART_XB_SCB__CTRL CYREG_SCB0_CTRL
#define UART_XB_SCB__EZ_DATA00 CYREG_SCB0_EZ_DATA00
#define UART_XB_SCB__EZ_DATA01 CYREG_SCB0_EZ_DATA01
#define UART_XB_SCB__EZ_DATA02 CYREG_SCB0_EZ_DATA02
#define UART_XB_SCB__EZ_DATA03 CYREG_SCB0_EZ_DATA03
#define UART_XB_SCB__EZ_DATA04 CYREG_SCB0_EZ_DATA04
#define UART_XB_SCB__EZ_DATA05 CYREG_SCB0_EZ_DATA05
#define UART_XB_SCB__EZ_DATA06 CYREG_SCB0_EZ_DATA06
#define UART_XB_SCB__EZ_DATA07 CYREG_SCB0_EZ_DATA07
#define UART_XB_SCB__EZ_DATA08 CYREG_SCB0_EZ_DATA08
#define UART_XB_SCB__EZ_DATA09 CYREG_SCB0_EZ_DATA09
#define UART_XB_SCB__EZ_DATA10 CYREG_SCB0_EZ_DATA10
#define UART_XB_SCB__EZ_DATA11 CYREG_SCB0_EZ_DATA11
#define UART_XB_SCB__EZ_DATA12 CYREG_SCB0_EZ_DATA12
#define UART_XB_SCB__EZ_DATA13 CYREG_SCB0_EZ_DATA13
#define UART_XB_SCB__EZ_DATA14 CYREG_SCB0_EZ_DATA14
#define UART_XB_SCB__EZ_DATA15 CYREG_SCB0_EZ_DATA15
#define UART_XB_SCB__EZ_DATA16 CYREG_SCB0_EZ_DATA16
#define UART_XB_SCB__EZ_DATA17 CYREG_SCB0_EZ_DATA17
#define UART_XB_SCB__EZ_DATA18 CYREG_SCB0_EZ_DATA18
#define UART_XB_SCB__EZ_DATA19 CYREG_SCB0_EZ_DATA19
#define UART_XB_SCB__EZ_DATA20 CYREG_SCB0_EZ_DATA20
#define UART_XB_SCB__EZ_DATA21 CYREG_SCB0_EZ_DATA21
#define UART_XB_SCB__EZ_DATA22 CYREG_SCB0_EZ_DATA22
#define UART_XB_SCB__EZ_DATA23 CYREG_SCB0_EZ_DATA23
#define UART_XB_SCB__EZ_DATA24 CYREG_SCB0_EZ_DATA24
#define UART_XB_SCB__EZ_DATA25 CYREG_SCB0_EZ_DATA25
#define UART_XB_SCB__EZ_DATA26 CYREG_SCB0_EZ_DATA26
#define UART_XB_SCB__EZ_DATA27 CYREG_SCB0_EZ_DATA27
#define UART_XB_SCB__EZ_DATA28 CYREG_SCB0_EZ_DATA28
#define UART_XB_SCB__EZ_DATA29 CYREG_SCB0_EZ_DATA29
#define UART_XB_SCB__EZ_DATA30 CYREG_SCB0_EZ_DATA30
#define UART_XB_SCB__EZ_DATA31 CYREG_SCB0_EZ_DATA31
#define UART_XB_SCB__I2C_CFG CYREG_SCB0_I2C_CFG
#define UART_XB_SCB__I2C_CTRL CYREG_SCB0_I2C_CTRL
#define UART_XB_SCB__I2C_M_CMD CYREG_SCB0_I2C_M_CMD
#define UART_XB_SCB__I2C_S_CMD CYREG_SCB0_I2C_S_CMD
#define UART_XB_SCB__I2C_STATUS CYREG_SCB0_I2C_STATUS
#define UART_XB_SCB__INTR_CAUSE CYREG_SCB0_INTR_CAUSE
#define UART_XB_SCB__INTR_I2C_EC CYREG_SCB0_INTR_I2C_EC
#define UART_XB_SCB__INTR_I2C_EC_MASK CYREG_SCB0_INTR_I2C_EC_MASK
#define UART_XB_SCB__INTR_I2C_EC_MASKED CYREG_SCB0_INTR_I2C_EC_MASKED
#define UART_XB_SCB__INTR_M CYREG_SCB0_INTR_M
#define UART_XB_SCB__INTR_M_MASK CYREG_SCB0_INTR_M_MASK
#define UART_XB_SCB__INTR_M_MASKED CYREG_SCB0_INTR_M_MASKED
#define UART_XB_SCB__INTR_M_SET CYREG_SCB0_INTR_M_SET
#define UART_XB_SCB__INTR_RX CYREG_SCB0_INTR_RX
#define UART_XB_SCB__INTR_RX_MASK CYREG_SCB0_INTR_RX_MASK
#define UART_XB_SCB__INTR_RX_MASKED CYREG_SCB0_INTR_RX_MASKED
#define UART_XB_SCB__INTR_RX_SET CYREG_SCB0_INTR_RX_SET
#define UART_XB_SCB__INTR_S CYREG_SCB0_INTR_S
#define UART_XB_SCB__INTR_S_MASK CYREG_SCB0_INTR_S_MASK
#define UART_XB_SCB__INTR_S_MASKED CYREG_SCB0_INTR_S_MASKED
#define UART_XB_SCB__INTR_S_SET CYREG_SCB0_INTR_S_SET
#define UART_XB_SCB__INTR_SPI_EC CYREG_SCB0_INTR_SPI_EC
#define UART_XB_SCB__INTR_SPI_EC_MASK CYREG_SCB0_INTR_SPI_EC_MASK
#define UART_XB_SCB__INTR_SPI_EC_MASKED CYREG_SCB0_INTR_SPI_EC_MASKED
#define UART_XB_SCB__INTR_TX CYREG_SCB0_INTR_TX
#define UART_XB_SCB__INTR_TX_MASK CYREG_SCB0_INTR_TX_MASK
#define UART_XB_SCB__INTR_TX_MASKED CYREG_SCB0_INTR_TX_MASKED
#define UART_XB_SCB__INTR_TX_SET CYREG_SCB0_INTR_TX_SET
#define UART_XB_SCB__RX_CTRL CYREG_SCB0_RX_CTRL
#define UART_XB_SCB__RX_FIFO_CTRL CYREG_SCB0_RX_FIFO_CTRL
#define UART_XB_SCB__RX_FIFO_RD CYREG_SCB0_RX_FIFO_RD
#define UART_XB_SCB__RX_FIFO_RD_SILENT CYREG_SCB0_RX_FIFO_RD_SILENT
#define UART_XB_SCB__RX_FIFO_STATUS CYREG_SCB0_RX_FIFO_STATUS
#define UART_XB_SCB__RX_MATCH CYREG_SCB0_RX_MATCH
#define UART_XB_SCB__SPI_CTRL CYREG_SCB0_SPI_CTRL
#define UART_XB_SCB__SPI_STATUS CYREG_SCB0_SPI_STATUS
#define UART_XB_SCB__SS0_POSISTION 0u
#define UART_XB_SCB__SS1_POSISTION 1u
#define UART_XB_SCB__SS2_POSISTION 2u
#define UART_XB_SCB__SS3_POSISTION 3u
#define UART_XB_SCB__STATUS CYREG_SCB0_STATUS
#define UART_XB_SCB__TX_CTRL CYREG_SCB0_TX_CTRL
#define UART_XB_SCB__TX_FIFO_CTRL CYREG_SCB0_TX_FIFO_CTRL
#define UART_XB_SCB__TX_FIFO_STATUS CYREG_SCB0_TX_FIFO_STATUS
#define UART_XB_SCB__TX_FIFO_WR CYREG_SCB0_TX_FIFO_WR
#define UART_XB_SCB__UART_CTRL CYREG_SCB0_UART_CTRL
#define UART_XB_SCB__UART_RX_CTRL CYREG_SCB0_UART_RX_CTRL
#define UART_XB_SCB__UART_RX_STATUS CYREG_SCB0_UART_RX_STATUS
#define UART_XB_SCB__UART_TX_CTRL CYREG_SCB0_UART_TX_CTRL

/* UART_XB_SCBCLK */
#define UART_XB_SCBCLK__DIVIDER_MASK 0x0000FFFFu
#define UART_XB_SCBCLK__ENABLE CYREG_CLK_DIVIDER_A00
#define UART_XB_SCBCLK__ENABLE_MASK 0x80000000u
#define UART_XB_SCBCLK__MASK 0x80000000u
#define UART_XB_SCBCLK__REGISTER CYREG_CLK_DIVIDER_A00

/* UART_XB_tx */
#define UART_XB_tx__0__DM__MASK 0x38u
#define UART_XB_tx__0__DM__SHIFT 3u
#define UART_XB_tx__0__DR CYREG_PRT4_DR
#define UART_XB_tx__0__HSIOM CYREG_HSIOM_PORT_SEL4
#define UART_XB_tx__0__HSIOM_GPIO 0u
#define UART_XB_tx__0__HSIOM_I2C 14u
#define UART_XB_tx__0__HSIOM_I2C_SDA 14u
#define UART_XB_tx__0__HSIOM_MASK 0x000000F0u
#define UART_XB_tx__0__HSIOM_SHIFT 4u
#define UART_XB_tx__0__HSIOM_SPI 15u
#define UART_XB_tx__0__HSIOM_SPI_MISO 15u
#define UART_XB_tx__0__HSIOM_UART 9u
#define UART_XB_tx__0__HSIOM_UART_TX 9u
#define UART_XB_tx__0__INTCFG CYREG_PRT4_INTCFG
#define UART_XB_tx__0__INTSTAT CYREG_PRT4_INTSTAT
#define UART_XB_tx__0__MASK 0x02u
#define UART_XB_tx__0__PC CYREG_PRT4_PC
#define UART_XB_tx__0__PC2 CYREG_PRT4_PC2
#define UART_XB_tx__0__PORT 4u
#define UART_XB_tx__0__PS CYREG_PRT4_PS
#define UART_XB_tx__0__SHIFT 1u
#define UART_XB_tx__DR CYREG_PRT4_DR
#define UART_XB_tx__INTCFG CYREG_PRT4_INTCFG
#define UART_XB_tx__INTSTAT CYREG_PRT4_INTSTAT
#define UART_XB_tx__MASK 0x02u
#define UART_XB_tx__PC CYREG_PRT4_PC
#define UART_XB_tx__PC2 CYREG_PRT4_PC2
#define UART_XB_tx__PORT 4u
#define UART_XB_tx__PS CYREG_PRT4_PS
#define UART_XB_tx__SHIFT 1u

/* Timer_LED_cy_m0s8_tcpwm_1 */
#define Timer_LED_cy_m0s8_tcpwm_1__CC CYREG_TCPWM_CNT0_CC
#define Timer_LED_cy_m0s8_tcpwm_1__CC_BUFF CYREG_TCPWM_CNT0_CC_BUFF
#define Timer_LED_cy_m0s8_tcpwm_1__COUNTER CYREG_TCPWM_CNT0_COUNTER
#define Timer_LED_cy_m0s8_tcpwm_1__CTRL CYREG_TCPWM_CNT0_CTRL
#define Timer_LED_cy_m0s8_tcpwm_1__INTR CYREG_TCPWM_CNT0_INTR
#define Timer_LED_cy_m0s8_tcpwm_1__INTR_MASK CYREG_TCPWM_CNT0_INTR_MASK
#define Timer_LED_cy_m0s8_tcpwm_1__INTR_MASKED CYREG_TCPWM_CNT0_INTR_MASKED
#define Timer_LED_cy_m0s8_tcpwm_1__INTR_SET CYREG_TCPWM_CNT0_INTR_SET
#define Timer_LED_cy_m0s8_tcpwm_1__PERIOD CYREG_TCPWM_CNT0_PERIOD
#define Timer_LED_cy_m0s8_tcpwm_1__PERIOD_BUFF CYREG_TCPWM_CNT0_PERIOD_BUFF
#define Timer_LED_cy_m0s8_tcpwm_1__STATUS CYREG_TCPWM_CNT0_STATUS
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_CMD CYREG_TCPWM_CMD
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_CMDCAPTURE_MASK 0x01u
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_CMDCAPTURE_SHIFT 0u
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_CMDRELOAD_MASK 0x100u
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_CMDRELOAD_SHIFT 8u
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_CMDSTART_MASK 0x1000000u
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_CMDSTART_SHIFT 24u
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_CMDSTOP_MASK 0x10000u
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_CMDSTOP_SHIFT 16u
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_CTRL CYREG_TCPWM_CTRL
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK 0x01u
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_CTRL_SHIFT 0u
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE CYREG_TCPWM_INTR_CAUSE
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE_MASK 0x01u
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE_SHIFT 0u
#define Timer_LED_cy_m0s8_tcpwm_1__TCPWM_NUMBER 0u
#define Timer_LED_cy_m0s8_tcpwm_1__TR_CTRL0 CYREG_TCPWM_CNT0_TR_CTRL0
#define Timer_LED_cy_m0s8_tcpwm_1__TR_CTRL1 CYREG_TCPWM_CNT0_TR_CTRL1
#define Timer_LED_cy_m0s8_tcpwm_1__TR_CTRL2 CYREG_TCPWM_CNT0_TR_CTRL2

/* timer_clock */
#define timer_clock__DIVIDER_MASK 0x0000FFFFu
#define timer_clock__ENABLE CYREG_CLK_DIVIDER_B00
#define timer_clock__ENABLE_MASK 0x80000000u
#define timer_clock__MASK 0x80000000u
#define timer_clock__REGISTER CYREG_CLK_DIVIDER_B00

/* Int_Timer_Led */
#define Int_Timer_Led__INTC_CLR_EN_REG CYREG_CM0_ICER
#define Int_Timer_Led__INTC_CLR_PD_REG CYREG_CM0_ICPR
#define Int_Timer_Led__INTC_MASK 0x10000u
#define Int_Timer_Led__INTC_NUMBER 16u
#define Int_Timer_Led__INTC_PRIOR_MASK 0xC0u
#define Int_Timer_Led__INTC_PRIOR_NUM 3u
#define Int_Timer_Led__INTC_PRIOR_REG CYREG_CM0_IPR4
#define Int_Timer_Led__INTC_SET_EN_REG CYREG_CM0_ISER
#define Int_Timer_Led__INTC_SET_PD_REG CYREG_CM0_ISPR

/* Miscellaneous */
#define CY_PROJECT_NAME "start01"
#define CY_VERSION "PSoC Creator  3.3 SP2"
#define CYDEV_BANDGAP_VOLTAGE 1.024
#define CYDEV_BCLK__HFCLK__HZ 24000000U
#define CYDEV_BCLK__HFCLK__KHZ 24000U
#define CYDEV_BCLK__HFCLK__MHZ 24U
#define CYDEV_BCLK__SYSCLK__HZ 24000000U
#define CYDEV_BCLK__SYSCLK__KHZ 24000U
#define CYDEV_BCLK__SYSCLK__MHZ 24U
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 19u
#define CYDEV_CHIP_DIE_PSOC4A 11u
#define CYDEV_CHIP_DIE_PSOC5LP 18u
#define CYDEV_CHIP_DIE_TMA4 2u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC4
#define CYDEV_CHIP_JTAG_ID 0x04C81193u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 11u
#define CYDEV_CHIP_MEMBER_4C 16u
#define CYDEV_CHIP_MEMBER_4D 7u
#define CYDEV_CHIP_MEMBER_4E 4u
#define CYDEV_CHIP_MEMBER_4F 12u
#define CYDEV_CHIP_MEMBER_4G 2u
#define CYDEV_CHIP_MEMBER_4H 10u
#define CYDEV_CHIP_MEMBER_4I 15u
#define CYDEV_CHIP_MEMBER_4J 8u
#define CYDEV_CHIP_MEMBER_4K 9u
#define CYDEV_CHIP_MEMBER_4L 14u
#define CYDEV_CHIP_MEMBER_4M 13u
#define CYDEV_CHIP_MEMBER_4N 6u
#define CYDEV_CHIP_MEMBER_4O 5u
#define CYDEV_CHIP_MEMBER_4U 3u
#define CYDEV_CHIP_MEMBER_5A 18u
#define CYDEV_CHIP_MEMBER_5B 17u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_4A
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_MEMBER_USED
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REV_TMA4_ES 17u
#define CYDEV_CHIP_REV_TMA4_ES2 33u
#define CYDEV_CHIP_REV_TMA4_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4C_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4D_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4E_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0u
#define CYDEV_CHIP_REVISION_4G_ES 17u
#define CYDEV_CHIP_REVISION_4G_ES2 33u
#define CYDEV_CHIP_REVISION_4G_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4H_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4I_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4J_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4K_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4L_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4M_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4N_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4O_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4U_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_4A_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REVISION_USED
#define CYDEV_CONFIG_READ_ACCELERATOR 1
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_DEBUG_PROTECT_KILL 4
#define CYDEV_DEBUG_PROTECT_OPEN 1
#define CYDEV_DEBUG_PROTECT CYDEV_DEBUG_PROTECT_OPEN
#define CYDEV_DEBUG_PROTECT_PROTECTED 2
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DFT_SELECT_CLK0 1u
#define CYDEV_DFT_SELECT_CLK1 2u
#define CYDEV_HEAP_SIZE 0x80
#define CYDEV_IMO_TRIMMED_BY_USB 0u
#define CYDEV_IMO_TRIMMED_BY_WCO 0u
#define CYDEV_IS_EXPORTING_CODE 0
#define CYDEV_IS_IMPORTING_CODE 0
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LAUNCHER 5
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER 4
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_STACK_SIZE 0x0400
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 1
#define CYDEV_VDDA 3.3
#define CYDEV_VDDA_MV 3300
#define CYDEV_VDDD 3.3
#define CYDEV_VDDD_MV 3300
#define CYDEV_WDT_GENERATE_ISR 1u
#define CYIPBLOCK_M0S8_CTBM_VERSION 0
#define CYIPBLOCK_m0s8cpuss_VERSION 0
#define CYIPBLOCK_m0s8csd_VERSION 0
#define CYIPBLOCK_m0s8gpio2_VERSION 0
#define CYIPBLOCK_m0s8hsiom4a_VERSION 0
#define CYIPBLOCK_m0s8lcd_VERSION 0
#define CYIPBLOCK_m0s8lpcomp_VERSION 0
#define CYIPBLOCK_m0s8pclk_VERSION 0
#define CYIPBLOCK_m0s8sar_VERSION 0
#define CYIPBLOCK_m0s8scb_VERSION 0
#define CYIPBLOCK_m0s8srssv2_VERSION 1
#define CYIPBLOCK_m0s8tcpwm_VERSION 0
#define CYIPBLOCK_m0s8udbif_VERSION 0
#define CYIPBLOCK_S8_GPIO_VERSION 2
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
