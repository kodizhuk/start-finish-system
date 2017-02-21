/*******************************************************************************
* File Name: Int_timerTestMode.h
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
#if !defined(CY_ISR_Int_timerTestMode_H)
#define CY_ISR_Int_timerTestMode_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Int_timerTestMode_Start(void);
void Int_timerTestMode_StartEx(cyisraddress address);
void Int_timerTestMode_Stop(void);

CY_ISR_PROTO(Int_timerTestMode_Interrupt);

void Int_timerTestMode_SetVector(cyisraddress address);
cyisraddress Int_timerTestMode_GetVector(void);

void Int_timerTestMode_SetPriority(uint8 priority);
uint8 Int_timerTestMode_GetPriority(void);

void Int_timerTestMode_Enable(void);
uint8 Int_timerTestMode_GetState(void);
void Int_timerTestMode_Disable(void);

void Int_timerTestMode_SetPending(void);
void Int_timerTestMode_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Int_timerTestMode ISR. */
#define Int_timerTestMode_INTC_VECTOR            ((reg32 *) Int_timerTestMode__INTC_VECT)

/* Address of the Int_timerTestMode ISR priority. */
#define Int_timerTestMode_INTC_PRIOR             ((reg32 *) Int_timerTestMode__INTC_PRIOR_REG)

/* Priority of the Int_timerTestMode interrupt. */
#define Int_timerTestMode_INTC_PRIOR_NUMBER      Int_timerTestMode__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Int_timerTestMode interrupt. */
#define Int_timerTestMode_INTC_SET_EN            ((reg32 *) Int_timerTestMode__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Int_timerTestMode interrupt. */
#define Int_timerTestMode_INTC_CLR_EN            ((reg32 *) Int_timerTestMode__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Int_timerTestMode interrupt state to pending. */
#define Int_timerTestMode_INTC_SET_PD            ((reg32 *) Int_timerTestMode__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Int_timerTestMode interrupt. */
#define Int_timerTestMode_INTC_CLR_PD            ((reg32 *) Int_timerTestMode__INTC_CLR_PD_REG)



#endif /* CY_ISR_Int_timerTestMode_H */


/* [] END OF FILE */
