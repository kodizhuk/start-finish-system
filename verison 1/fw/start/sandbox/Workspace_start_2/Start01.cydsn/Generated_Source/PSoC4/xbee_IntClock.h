/*******************************************************************************
* File Name: xbee_IntClock.h
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

#if !defined(CY_CLOCK_xbee_IntClock_H)
#define CY_CLOCK_xbee_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void xbee_IntClock_StartEx(uint32 alignClkDiv);
#define xbee_IntClock_Start() \
    xbee_IntClock_StartEx(xbee_IntClock__PA_DIV_ID)

#else

void xbee_IntClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void xbee_IntClock_Stop(void);

void xbee_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 xbee_IntClock_GetDividerRegister(void);
uint8  xbee_IntClock_GetFractionalDividerRegister(void);

#define xbee_IntClock_Enable()                         xbee_IntClock_Start()
#define xbee_IntClock_Disable()                        xbee_IntClock_Stop()
#define xbee_IntClock_SetDividerRegister(clkDivider, reset)  \
    xbee_IntClock_SetFractionalDividerRegister((clkDivider), 0u)
#define xbee_IntClock_SetDivider(clkDivider)           xbee_IntClock_SetDividerRegister((clkDivider), 1u)
#define xbee_IntClock_SetDividerValue(clkDivider)      xbee_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define xbee_IntClock_DIV_ID     xbee_IntClock__DIV_ID

#define xbee_IntClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define xbee_IntClock_CTRL_REG   (*(reg32 *)xbee_IntClock__CTRL_REGISTER)
#define xbee_IntClock_DIV_REG    (*(reg32 *)xbee_IntClock__DIV_REGISTER)

#define xbee_IntClock_CMD_DIV_SHIFT          (0u)
#define xbee_IntClock_CMD_PA_DIV_SHIFT       (8u)
#define xbee_IntClock_CMD_DISABLE_SHIFT      (30u)
#define xbee_IntClock_CMD_ENABLE_SHIFT       (31u)

#define xbee_IntClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << xbee_IntClock_CMD_DISABLE_SHIFT))
#define xbee_IntClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << xbee_IntClock_CMD_ENABLE_SHIFT))

#define xbee_IntClock_DIV_FRAC_MASK  (0x000000F8u)
#define xbee_IntClock_DIV_FRAC_SHIFT (3u)
#define xbee_IntClock_DIV_INT_MASK   (0xFFFFFF00u)
#define xbee_IntClock_DIV_INT_SHIFT  (8u)

#else 

#define xbee_IntClock_DIV_REG        (*(reg32 *)xbee_IntClock__REGISTER)
#define xbee_IntClock_ENABLE_REG     xbee_IntClock_DIV_REG
#define xbee_IntClock_DIV_FRAC_MASK  xbee_IntClock__FRAC_MASK
#define xbee_IntClock_DIV_FRAC_SHIFT (16u)
#define xbee_IntClock_DIV_INT_MASK   xbee_IntClock__DIVIDER_MASK
#define xbee_IntClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_xbee_IntClock_H) */

/* [] END OF FILE */
