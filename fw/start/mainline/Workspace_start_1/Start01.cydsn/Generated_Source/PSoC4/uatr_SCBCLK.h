/*******************************************************************************
* File Name: uatr_SCBCLK.h
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

#if !defined(CY_CLOCK_uatr_SCBCLK_H)
#define CY_CLOCK_uatr_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void uatr_SCBCLK_StartEx(uint32 alignClkDiv);
#define uatr_SCBCLK_Start() \
    uatr_SCBCLK_StartEx(uatr_SCBCLK__PA_DIV_ID)

#else

void uatr_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void uatr_SCBCLK_Stop(void);

void uatr_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 uatr_SCBCLK_GetDividerRegister(void);
uint8  uatr_SCBCLK_GetFractionalDividerRegister(void);

#define uatr_SCBCLK_Enable()                         uatr_SCBCLK_Start()
#define uatr_SCBCLK_Disable()                        uatr_SCBCLK_Stop()
#define uatr_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    uatr_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define uatr_SCBCLK_SetDivider(clkDivider)           uatr_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define uatr_SCBCLK_SetDividerValue(clkDivider)      uatr_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define uatr_SCBCLK_DIV_ID     uatr_SCBCLK__DIV_ID

#define uatr_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define uatr_SCBCLK_CTRL_REG   (*(reg32 *)uatr_SCBCLK__CTRL_REGISTER)
#define uatr_SCBCLK_DIV_REG    (*(reg32 *)uatr_SCBCLK__DIV_REGISTER)

#define uatr_SCBCLK_CMD_DIV_SHIFT          (0u)
#define uatr_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define uatr_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define uatr_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define uatr_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << uatr_SCBCLK_CMD_DISABLE_SHIFT))
#define uatr_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << uatr_SCBCLK_CMD_ENABLE_SHIFT))

#define uatr_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define uatr_SCBCLK_DIV_FRAC_SHIFT (3u)
#define uatr_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define uatr_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define uatr_SCBCLK_DIV_REG        (*(reg32 *)uatr_SCBCLK__REGISTER)
#define uatr_SCBCLK_ENABLE_REG     uatr_SCBCLK_DIV_REG
#define uatr_SCBCLK_DIV_FRAC_MASK  uatr_SCBCLK__FRAC_MASK
#define uatr_SCBCLK_DIV_FRAC_SHIFT (16u)
#define uatr_SCBCLK_DIV_INT_MASK   uatr_SCBCLK__DIVIDER_MASK
#define uatr_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_uatr_SCBCLK_H) */

/* [] END OF FILE */
