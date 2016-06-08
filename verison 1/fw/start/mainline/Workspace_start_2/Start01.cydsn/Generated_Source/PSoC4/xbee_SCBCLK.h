/*******************************************************************************
* File Name: xbee_SCBCLK.h
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

#if !defined(CY_CLOCK_xbee_SCBCLK_H)
#define CY_CLOCK_xbee_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void xbee_SCBCLK_StartEx(uint32 alignClkDiv);
#define xbee_SCBCLK_Start() \
    xbee_SCBCLK_StartEx(xbee_SCBCLK__PA_DIV_ID)

#else

void xbee_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void xbee_SCBCLK_Stop(void);

void xbee_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 xbee_SCBCLK_GetDividerRegister(void);
uint8  xbee_SCBCLK_GetFractionalDividerRegister(void);

#define xbee_SCBCLK_Enable()                         xbee_SCBCLK_Start()
#define xbee_SCBCLK_Disable()                        xbee_SCBCLK_Stop()
#define xbee_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    xbee_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define xbee_SCBCLK_SetDivider(clkDivider)           xbee_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define xbee_SCBCLK_SetDividerValue(clkDivider)      xbee_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define xbee_SCBCLK_DIV_ID     xbee_SCBCLK__DIV_ID

#define xbee_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define xbee_SCBCLK_CTRL_REG   (*(reg32 *)xbee_SCBCLK__CTRL_REGISTER)
#define xbee_SCBCLK_DIV_REG    (*(reg32 *)xbee_SCBCLK__DIV_REGISTER)

#define xbee_SCBCLK_CMD_DIV_SHIFT          (0u)
#define xbee_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define xbee_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define xbee_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define xbee_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << xbee_SCBCLK_CMD_DISABLE_SHIFT))
#define xbee_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << xbee_SCBCLK_CMD_ENABLE_SHIFT))

#define xbee_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define xbee_SCBCLK_DIV_FRAC_SHIFT (3u)
#define xbee_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define xbee_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define xbee_SCBCLK_DIV_REG        (*(reg32 *)xbee_SCBCLK__REGISTER)
#define xbee_SCBCLK_ENABLE_REG     xbee_SCBCLK_DIV_REG
#define xbee_SCBCLK_DIV_FRAC_MASK  xbee_SCBCLK__FRAC_MASK
#define xbee_SCBCLK_DIV_FRAC_SHIFT (16u)
#define xbee_SCBCLK_DIV_INT_MASK   xbee_SCBCLK__DIVIDER_MASK
#define xbee_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_xbee_SCBCLK_H) */

/* [] END OF FILE */
