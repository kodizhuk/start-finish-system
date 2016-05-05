/*******************************************************************************
* File Name: display.h
* Version 2.20
*
* Description:
*  This header file contains registers and constants associated with the
*  Character LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CHARLCD_display_H)
#define CY_CHARLCD_display_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define display_CONVERSION_ROUTINES     (1u)
#define display_CUSTOM_CHAR_SET         (0u)

/* Custom character set types */
#define display_NONE                     (0u)    /* No Custom Fonts      */
#define display_HORIZONTAL_BG            (1u)    /* Horizontal Bar Graph */
#define display_VERTICAL_BG              (2u)    /* Vertical Bar Graph   */
#define display_USER_DEFINED             (3u)    /* User Defined Fonts   */


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} display_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void display_Init(void) ;
void display_Enable(void) ;
void display_Start(void) ;
void display_Stop(void) ;
void display_WriteControl(uint8 cByte) ;
void display_WriteData(uint8 dByte) ;
void display_PrintString(char8 const string[]) ;
void display_Position(uint8 row, uint8 column) ;
void display_PutChar(char8 character) ;
void display_IsReady(void) ;
void display_SaveConfig(void) ;
void display_RestoreConfig(void) ;
void display_Sleep(void) ;
void display_Wakeup(void) ;

#if((display_CUSTOM_CHAR_SET == display_VERTICAL_BG) || \
                (display_CUSTOM_CHAR_SET == display_HORIZONTAL_BG))

    void  display_LoadCustomFonts(uint8 const customData[])
                        ;

    void  display_DrawHorizontalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                         ;

    void display_DrawVerticalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                        ;

#endif /* ((display_CUSTOM_CHAR_SET == display_VERTICAL_BG) */

#if(display_CUSTOM_CHAR_SET == display_USER_DEFINED)

    void display_LoadCustomFonts(uint8 const customData[])
                            ;

#endif /* ((display_CUSTOM_CHAR_SET == display_USER_DEFINED) */

#if(display_CONVERSION_ROUTINES == 1u)

    /* ASCII Conversion Routines */
    void display_PrintInt8(uint8 value) ;
    void display_PrintInt16(uint16 value) ;
    void display_PrintInt32(uint32 value) ;
    void display_PrintNumber(uint16 value) ; 
    void display_PrintU32Number(uint32 value) ;
    
#endif /* display_CONVERSION_ROUTINES == 1u */

/* Clear Macro */
#define display_ClearDisplay() display_WriteControl(display_CLEAR_DISPLAY)

/* Off Macro */
#define display_DisplayOff() display_WriteControl(display_DISPLAY_CURSOR_OFF)

/* On Macro */
#define display_DisplayOn() display_WriteControl(display_DISPLAY_ON_CURSOR_OFF)

#define display_PrintNumber(value) display_PrintU32Number((uint16) (value))


/***************************************
*           Global Variables
***************************************/

extern uint8 display_initVar;
extern uint8 display_enableState;
extern uint8 const CYCODE display_customFonts[64u];


/***************************************
*           API Constants
***************************************/

/* Full Byte Commands Sent as Two Nibbles */
#define display_DISPLAY_8_BIT_INIT       (0x03u)
#define display_DISPLAY_4_BIT_INIT       (0x02u)
#define display_DISPLAY_CURSOR_OFF       (0x08u)
#define display_CLEAR_DISPLAY            (0x01u)
#define display_CURSOR_AUTO_INCR_ON      (0x06u)
#define display_DISPLAY_CURSOR_ON        (0x0Eu)
#define display_DISPLAY_2_LINES_5x10     (0x2Cu)
#define display_DISPLAY_ON_CURSOR_OFF    (0x0Cu)

#define display_RESET_CURSOR_POSITION    (0x03u)
#define display_CURSOR_WINK              (0x0Du)
#define display_CURSOR_BLINK             (0x0Fu)
#define display_CURSOR_SH_LEFT           (0x10u)
#define display_CURSOR_SH_RIGHT          (0x14u)
#define display_DISPLAY_SCRL_LEFT        (0x18u)
#define display_DISPLAY_SCRL_RIGHT       (0x1Eu)
#define display_CURSOR_HOME              (0x02u)
#define display_CURSOR_LEFT              (0x04u)
#define display_CURSOR_RIGHT             (0x06u)

/* Point to Character Generator Ram 0 */
#define display_CGRAM_0                  (0x40u)

/* Point to Display Data Ram 0 */
#define display_DDRAM_0                  (0x80u)

/* LCD Characteristics */
#define display_CHARACTER_WIDTH          (0x05u)
#define display_CHARACTER_HEIGHT         (0x08u)

#if(display_CONVERSION_ROUTINES == 1u)
    #define display_NUMBER_OF_REMAINDERS_U32 (0x0Au)
    #define display_TEN                      (0x0Au)
    #define display_8_BIT_SHIFT              (8u)
    #define display_32_BIT_SHIFT             (32u)
    #define display_ZERO_CHAR_ASCII          (48u)
#endif /* display_CONVERSION_ROUTINES == 1u */

/* Nibble Offset and Mask */
#define display_NIBBLE_SHIFT             (0x04u)
#define display_NIBBLE_MASK              (0x0Fu)

/* LCD Module Address Constants */
#define display_ROW_0_START              (0x80u)
#define display_ROW_1_START              (0xC0u)
#define display_ROW_2_START              (0x94u)
#define display_ROW_3_START              (0xD4u)

/* Custom Character References */
#define display_CUSTOM_0                 (0x00u)
#define display_CUSTOM_1                 (0x01u)
#define display_CUSTOM_2                 (0x02u)
#define display_CUSTOM_3                 (0x03u)
#define display_CUSTOM_4                 (0x04u)
#define display_CUSTOM_5                 (0x05u)
#define display_CUSTOM_6                 (0x06u)
#define display_CUSTOM_7                 (0x07u)

/* Other constants */
#define display_BYTE_UPPER_NIBBLE_SHIFT  (0x04u)
#define display_BYTE_LOWER_NIBBLE_MASK   (0x0Fu)
#define display_U16_UPPER_BYTE_SHIFT     (0x08u)
#define display_U16_LOWER_BYTE_MASK      (0xFFu)
#define display_CUSTOM_CHAR_SET_LEN      (0x40u)

#define display_LONGEST_CMD_US           (0x651u)
#define display_WAIT_CYCLE               (0x10u)
#define display_READY_DELAY              ((display_LONGEST_CMD_US * 4u)/(display_WAIT_CYCLE))


/***************************************
*             Registers
***************************************/

/* Device specific registers */
#if (CY_PSOC4)

    #define display_PORT_DR_REG           (*(reg32 *) display_LCDPort__DR)  /* Data Output Register */
    #define display_PORT_DR_PTR           ( (reg32 *) display_LCDPort__DR)
    #define display_PORT_PS_REG           (*(reg32 *) display_LCDPort__PS)  /* Pin State Register */
    #define display_PORT_PS_PTR           ( (reg32 *) display_LCDPort__PS)
    
    #define display_PORT_PC_REG           (*(reg32 *) display_LCDPort__PC)
    #define display_PORT_PC_PTR           (*(reg32 *) display_LCDPort__PC)
    
#else

    #define display_PORT_DR_REG           (*(reg8 *) display_LCDPort__DR)  /* Data Output Register */
    #define display_PORT_DR_PTR           ( (reg8 *) display_LCDPort__DR)
    #define display_PORT_PS_REG           (*(reg8 *) display_LCDPort__PS)  /* Pin State Register */
    #define display_PORT_PS_PTR           ( (reg8 *) display_LCDPort__PS)

    #define display_PORT_DM0_REG          (*(reg8 *) display_LCDPort__DM0) /* Port Drive Mode 0 */
    #define display_PORT_DM0_PTR          ( (reg8 *) display_LCDPort__DM0)
    #define display_PORT_DM1_REG          (*(reg8 *) display_LCDPort__DM1) /* Port Drive Mode 1 */
    #define display_PORT_DM1_PTR          ( (reg8 *) display_LCDPort__DM1)
    #define display_PORT_DM2_REG          (*(reg8 *) display_LCDPort__DM2) /* Port Drive Mode 2 */
    #define display_PORT_DM2_PTR          ( (reg8 *) display_LCDPort__DM2)

#endif /* CY_PSOC4 */


/***************************************
*       Register Constants
***************************************/

/* SHIFT must be 1 or 0 */
#if (0 == display_LCDPort__SHIFT)
    #define display_PORT_SHIFT               (0x00u)
#else
    #define display_PORT_SHIFT               (0x01u)
#endif /* (0 == display_LCDPort__SHIFT) */

#define display_PORT_MASK                ((uint32) (display_LCDPort__MASK))

#if (CY_PSOC4)

    #define display_DM_PIN_STEP              (3u)
    /* Hi-Z Digital is defined by the value of "001b" and this should be set for
    * four data pins, in this way we get - 0x00000249. A similar Strong drive
    * is defined with "110b" so we get 0x00000DB6.
    */
    #define display_HIGH_Z_DATA_DM           ((0x00000249ul) << (display_PORT_SHIFT *\
                                                                          display_DM_PIN_STEP))
    #define display_STRONG_DATA_DM           ((0x00000DB6ul) << (display_PORT_SHIFT *\
                                                                          display_DM_PIN_STEP))
    #define display_DATA_PINS_MASK           (0x00000FFFul)
    #define display_DM_DATA_MASK             ((uint32) (display_DATA_PINS_MASK << \
                                                      (display_PORT_SHIFT * display_DM_PIN_STEP)))

#else

    /* Drive Mode register values for High Z */
    #define display_HIGH_Z_DM0               (0xFFu)
    #define display_HIGH_Z_DM1               (0x00u)
    #define display_HIGH_Z_DM2               (0x00u)

    /* Drive Mode register values for High Z Analog */
    #define display_HIGH_Z_A_DM0             (0x00u)
    #define display_HIGH_Z_A_DM1             (0x00u)
    #define display_HIGH_Z_A_DM2             (0x00u)

    /* Drive Mode register values for Strong */
    #define display_STRONG_DM0               (0x00u)
    #define display_STRONG_DM1               (0xFFu)
    #define display_STRONG_DM2               (0xFFu)

#endif /* CY_PSOC4 */

/* Pin Masks */
#define display_RS                     ((uint32) \
                                                (((uint32) 0x20u) << display_LCDPort__SHIFT))
#define display_RW                     ((uint32) \
                                                (((uint32) 0x40u) << display_LCDPort__SHIFT))
#define display_E                      ((uint32) \
                                                (((uint32) 0x10u) << display_LCDPort__SHIFT))
#define display_READY_BIT              ((uint32) \
                                                (((uint32) 0x08u) << display_LCDPort__SHIFT))
#define display_DATA_MASK              ((uint32) \
                                                (((uint32) 0x0Fu) << display_LCDPort__SHIFT))

/* These names are obsolete and will be removed in future revisions */
#define display_PORT_DR                  display_PORT_DR_REG
#define display_PORT_PS                  display_PORT_PS_REG
#define display_PORT_DM0                 display_PORT_DM0_REG
#define display_PORT_DM1                 display_PORT_DM1_REG
#define display_PORT_DM2                 display_PORT_DM2_REG


/***************************************
*       Obsolete function names
***************************************/
#if(display_CONVERSION_ROUTINES == 1u)
    /* This function names are obsolete and will be removed in future 
    * revisions of the component.
    */
    #define display_PrintDecUint16(x)   display_PrintNumber(x)  
    #define display_PrintHexUint8(x)    display_PrintInt8(x)
    #define display_PrintHexUint16(x)   display_PrintInt16(x)        

#endif /* display_CONVERSION_ROUTINES == 1u */

#endif /* CY_CHARLCD_display_H */


/* [] END OF FILE */
