/*******************************************************************************
* File Name: int_start.h
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
#if !defined(CY_ISR_int_start_H)
#define CY_ISR_int_start_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void int_start_Start(void);
void int_start_StartEx(cyisraddress address);
void int_start_Stop(void);

CY_ISR_PROTO(int_start_Interrupt);

void int_start_SetVector(cyisraddress address);
cyisraddress int_start_GetVector(void);

void int_start_SetPriority(uint8 priority);
uint8 int_start_GetPriority(void);

void int_start_Enable(void);
uint8 int_start_GetState(void);
void int_start_Disable(void);

void int_start_SetPending(void);
void int_start_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the int_start ISR. */
#define int_start_INTC_VECTOR            ((reg32 *) int_start__INTC_VECT)

/* Address of the int_start ISR priority. */
#define int_start_INTC_PRIOR             ((reg32 *) int_start__INTC_PRIOR_REG)

/* Priority of the int_start interrupt. */
#define int_start_INTC_PRIOR_NUMBER      int_start__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable int_start interrupt. */
#define int_start_INTC_SET_EN            ((reg32 *) int_start__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the int_start interrupt. */
#define int_start_INTC_CLR_EN            ((reg32 *) int_start__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the int_start interrupt state to pending. */
#define int_start_INTC_SET_PD            ((reg32 *) int_start__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the int_start interrupt. */
#define int_start_INTC_CLR_PD            ((reg32 *) int_start__INTC_CLR_PD_REG)



#endif /* CY_ISR_int_start_H */


/* [] END OF FILE */
