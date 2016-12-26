/*******************************************************************************
* File Name: DEBUG_UART_SCB_IRQ.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_DEBUG_UART_SCB_IRQ_H)
#define CY_ISR_DEBUG_UART_SCB_IRQ_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void DEBUG_UART_SCB_IRQ_Start(void);
void DEBUG_UART_SCB_IRQ_StartEx(cyisraddress address);
void DEBUG_UART_SCB_IRQ_Stop(void);

CY_ISR_PROTO(DEBUG_UART_SCB_IRQ_Interrupt);

void DEBUG_UART_SCB_IRQ_SetVector(cyisraddress address);
cyisraddress DEBUG_UART_SCB_IRQ_GetVector(void);

void DEBUG_UART_SCB_IRQ_SetPriority(uint8 priority);
uint8 DEBUG_UART_SCB_IRQ_GetPriority(void);

void DEBUG_UART_SCB_IRQ_Enable(void);
uint8 DEBUG_UART_SCB_IRQ_GetState(void);
void DEBUG_UART_SCB_IRQ_Disable(void);

void DEBUG_UART_SCB_IRQ_SetPending(void);
void DEBUG_UART_SCB_IRQ_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the DEBUG_UART_SCB_IRQ ISR. */
#define DEBUG_UART_SCB_IRQ_INTC_VECTOR            ((reg32 *) DEBUG_UART_SCB_IRQ__INTC_VECT)

/* Address of the DEBUG_UART_SCB_IRQ ISR priority. */
#define DEBUG_UART_SCB_IRQ_INTC_PRIOR             ((reg32 *) DEBUG_UART_SCB_IRQ__INTC_PRIOR_REG)

/* Priority of the DEBUG_UART_SCB_IRQ interrupt. */
#define DEBUG_UART_SCB_IRQ_INTC_PRIOR_NUMBER      DEBUG_UART_SCB_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable DEBUG_UART_SCB_IRQ interrupt. */
#define DEBUG_UART_SCB_IRQ_INTC_SET_EN            ((reg32 *) DEBUG_UART_SCB_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the DEBUG_UART_SCB_IRQ interrupt. */
#define DEBUG_UART_SCB_IRQ_INTC_CLR_EN            ((reg32 *) DEBUG_UART_SCB_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the DEBUG_UART_SCB_IRQ interrupt state to pending. */
#define DEBUG_UART_SCB_IRQ_INTC_SET_PD            ((reg32 *) DEBUG_UART_SCB_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the DEBUG_UART_SCB_IRQ interrupt. */
#define DEBUG_UART_SCB_IRQ_INTC_CLR_PD            ((reg32 *) DEBUG_UART_SCB_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_DEBUG_UART_SCB_IRQ_H */


/* [] END OF FILE */
