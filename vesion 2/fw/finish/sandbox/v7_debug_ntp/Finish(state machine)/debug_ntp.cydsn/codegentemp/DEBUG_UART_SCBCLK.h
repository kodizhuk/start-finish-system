/*******************************************************************************
* File Name: DEBUG_UART_SCBCLK.h
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

#if !defined(CY_CLOCK_DEBUG_UART_SCBCLK_H)
#define CY_CLOCK_DEBUG_UART_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void DEBUG_UART_SCBCLK_StartEx(uint32 alignClkDiv);
#define DEBUG_UART_SCBCLK_Start() \
    DEBUG_UART_SCBCLK_StartEx(DEBUG_UART_SCBCLK__PA_DIV_ID)

#else

void DEBUG_UART_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void DEBUG_UART_SCBCLK_Stop(void);

void DEBUG_UART_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 DEBUG_UART_SCBCLK_GetDividerRegister(void);
uint8  DEBUG_UART_SCBCLK_GetFractionalDividerRegister(void);

#define DEBUG_UART_SCBCLK_Enable()                         DEBUG_UART_SCBCLK_Start()
#define DEBUG_UART_SCBCLK_Disable()                        DEBUG_UART_SCBCLK_Stop()
#define DEBUG_UART_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    DEBUG_UART_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define DEBUG_UART_SCBCLK_SetDivider(clkDivider)           DEBUG_UART_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define DEBUG_UART_SCBCLK_SetDividerValue(clkDivider)      DEBUG_UART_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define DEBUG_UART_SCBCLK_DIV_ID     DEBUG_UART_SCBCLK__DIV_ID

#define DEBUG_UART_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define DEBUG_UART_SCBCLK_CTRL_REG   (*(reg32 *)DEBUG_UART_SCBCLK__CTRL_REGISTER)
#define DEBUG_UART_SCBCLK_DIV_REG    (*(reg32 *)DEBUG_UART_SCBCLK__DIV_REGISTER)

#define DEBUG_UART_SCBCLK_CMD_DIV_SHIFT          (0u)
#define DEBUG_UART_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define DEBUG_UART_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define DEBUG_UART_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define DEBUG_UART_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << DEBUG_UART_SCBCLK_CMD_DISABLE_SHIFT))
#define DEBUG_UART_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << DEBUG_UART_SCBCLK_CMD_ENABLE_SHIFT))

#define DEBUG_UART_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define DEBUG_UART_SCBCLK_DIV_FRAC_SHIFT (3u)
#define DEBUG_UART_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define DEBUG_UART_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define DEBUG_UART_SCBCLK_DIV_REG        (*(reg32 *)DEBUG_UART_SCBCLK__REGISTER)
#define DEBUG_UART_SCBCLK_ENABLE_REG     DEBUG_UART_SCBCLK_DIV_REG
#define DEBUG_UART_SCBCLK_DIV_FRAC_MASK  DEBUG_UART_SCBCLK__FRAC_MASK
#define DEBUG_UART_SCBCLK_DIV_FRAC_SHIFT (16u)
#define DEBUG_UART_SCBCLK_DIV_INT_MASK   DEBUG_UART_SCBCLK__DIVIDER_MASK
#define DEBUG_UART_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_DEBUG_UART_SCBCLK_H) */

/* [] END OF FILE */
