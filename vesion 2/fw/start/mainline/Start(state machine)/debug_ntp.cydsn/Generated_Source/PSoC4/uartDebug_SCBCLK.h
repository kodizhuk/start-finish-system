/*******************************************************************************
* File Name: uartDebug_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_uartDebug_SCBCLK_H)
#define CY_CLOCK_uartDebug_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void uartDebug_SCBCLK_StartEx(uint32 alignClkDiv);
#define uartDebug_SCBCLK_Start() \
    uartDebug_SCBCLK_StartEx(uartDebug_SCBCLK__PA_DIV_ID)

#else

void uartDebug_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void uartDebug_SCBCLK_Stop(void);

void uartDebug_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 uartDebug_SCBCLK_GetDividerRegister(void);
uint8  uartDebug_SCBCLK_GetFractionalDividerRegister(void);

#define uartDebug_SCBCLK_Enable()                         uartDebug_SCBCLK_Start()
#define uartDebug_SCBCLK_Disable()                        uartDebug_SCBCLK_Stop()
#define uartDebug_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    uartDebug_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define uartDebug_SCBCLK_SetDivider(clkDivider)           uartDebug_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define uartDebug_SCBCLK_SetDividerValue(clkDivider)      uartDebug_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define uartDebug_SCBCLK_DIV_ID     uartDebug_SCBCLK__DIV_ID

#define uartDebug_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define uartDebug_SCBCLK_CTRL_REG   (*(reg32 *)uartDebug_SCBCLK__CTRL_REGISTER)
#define uartDebug_SCBCLK_DIV_REG    (*(reg32 *)uartDebug_SCBCLK__DIV_REGISTER)

#define uartDebug_SCBCLK_CMD_DIV_SHIFT          (0u)
#define uartDebug_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define uartDebug_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define uartDebug_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define uartDebug_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << uartDebug_SCBCLK_CMD_DISABLE_SHIFT))
#define uartDebug_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << uartDebug_SCBCLK_CMD_ENABLE_SHIFT))

#define uartDebug_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define uartDebug_SCBCLK_DIV_FRAC_SHIFT (3u)
#define uartDebug_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define uartDebug_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define uartDebug_SCBCLK_DIV_REG        (*(reg32 *)uartDebug_SCBCLK__REGISTER)
#define uartDebug_SCBCLK_ENABLE_REG     uartDebug_SCBCLK_DIV_REG
#define uartDebug_SCBCLK_DIV_FRAC_MASK  uartDebug_SCBCLK__FRAC_MASK
#define uartDebug_SCBCLK_DIV_FRAC_SHIFT (16u)
#define uartDebug_SCBCLK_DIV_INT_MASK   uartDebug_SCBCLK__DIVIDER_MASK
#define uartDebug_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_uartDebug_SCBCLK_H) */

/* [] END OF FILE */
