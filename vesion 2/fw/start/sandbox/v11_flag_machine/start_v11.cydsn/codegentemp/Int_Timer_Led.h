/*******************************************************************************
* File Name: Int_Timer_Led.h
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
#if !defined(CY_ISR_Int_Timer_Led_H)
#define CY_ISR_Int_Timer_Led_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Int_Timer_Led_Start(void);
void Int_Timer_Led_StartEx(cyisraddress address);
void Int_Timer_Led_Stop(void);

CY_ISR_PROTO(Int_Timer_Led_Interrupt);

void Int_Timer_Led_SetVector(cyisraddress address);
cyisraddress Int_Timer_Led_GetVector(void);

void Int_Timer_Led_SetPriority(uint8 priority);
uint8 Int_Timer_Led_GetPriority(void);

void Int_Timer_Led_Enable(void);
uint8 Int_Timer_Led_GetState(void);
void Int_Timer_Led_Disable(void);

void Int_Timer_Led_SetPending(void);
void Int_Timer_Led_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Int_Timer_Led ISR. */
#define Int_Timer_Led_INTC_VECTOR            ((reg32 *) Int_Timer_Led__INTC_VECT)

/* Address of the Int_Timer_Led ISR priority. */
#define Int_Timer_Led_INTC_PRIOR             ((reg32 *) Int_Timer_Led__INTC_PRIOR_REG)

/* Priority of the Int_Timer_Led interrupt. */
#define Int_Timer_Led_INTC_PRIOR_NUMBER      Int_Timer_Led__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Int_Timer_Led interrupt. */
#define Int_Timer_Led_INTC_SET_EN            ((reg32 *) Int_Timer_Led__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Int_Timer_Led interrupt. */
#define Int_Timer_Led_INTC_CLR_EN            ((reg32 *) Int_Timer_Led__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Int_Timer_Led interrupt state to pending. */
#define Int_Timer_Led_INTC_SET_PD            ((reg32 *) Int_Timer_Led__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Int_Timer_Led interrupt. */
#define Int_Timer_Led_INTC_CLR_PD            ((reg32 *) Int_Timer_Led__INTC_CLR_PD_REG)



#endif /* CY_ISR_Int_Timer_Led_H */


/* [] END OF FILE */
