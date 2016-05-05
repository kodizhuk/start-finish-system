/*******************************************************************************
* File Name: int_cancel.h
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
#if !defined(CY_ISR_int_cancel_H)
#define CY_ISR_int_cancel_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void int_cancel_Start(void);
void int_cancel_StartEx(cyisraddress address);
void int_cancel_Stop(void);

CY_ISR_PROTO(int_cancel_Interrupt);

void int_cancel_SetVector(cyisraddress address);
cyisraddress int_cancel_GetVector(void);

void int_cancel_SetPriority(uint8 priority);
uint8 int_cancel_GetPriority(void);

void int_cancel_Enable(void);
uint8 int_cancel_GetState(void);
void int_cancel_Disable(void);

void int_cancel_SetPending(void);
void int_cancel_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the int_cancel ISR. */
#define int_cancel_INTC_VECTOR            ((reg32 *) int_cancel__INTC_VECT)

/* Address of the int_cancel ISR priority. */
#define int_cancel_INTC_PRIOR             ((reg32 *) int_cancel__INTC_PRIOR_REG)

/* Priority of the int_cancel interrupt. */
#define int_cancel_INTC_PRIOR_NUMBER      int_cancel__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable int_cancel interrupt. */
#define int_cancel_INTC_SET_EN            ((reg32 *) int_cancel__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the int_cancel interrupt. */
#define int_cancel_INTC_CLR_EN            ((reg32 *) int_cancel__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the int_cancel interrupt state to pending. */
#define int_cancel_INTC_SET_PD            ((reg32 *) int_cancel__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the int_cancel interrupt. */
#define int_cancel_INTC_CLR_PD            ((reg32 *) int_cancel__INTC_CLR_PD_REG)



#endif /* CY_ISR_int_cancel_H */


/* [] END OF FILE */
