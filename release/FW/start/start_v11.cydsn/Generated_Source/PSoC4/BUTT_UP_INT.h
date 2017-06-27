/*******************************************************************************
* File Name: BUTT_UP_INT.h
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
#if !defined(CY_ISR_BUTT_UP_INT_H)
#define CY_ISR_BUTT_UP_INT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void BUTT_UP_INT_Start(void);
void BUTT_UP_INT_StartEx(cyisraddress address);
void BUTT_UP_INT_Stop(void);

CY_ISR_PROTO(BUTT_UP_INT_Interrupt);

void BUTT_UP_INT_SetVector(cyisraddress address);
cyisraddress BUTT_UP_INT_GetVector(void);

void BUTT_UP_INT_SetPriority(uint8 priority);
uint8 BUTT_UP_INT_GetPriority(void);

void BUTT_UP_INT_Enable(void);
uint8 BUTT_UP_INT_GetState(void);
void BUTT_UP_INT_Disable(void);

void BUTT_UP_INT_SetPending(void);
void BUTT_UP_INT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the BUTT_UP_INT ISR. */
#define BUTT_UP_INT_INTC_VECTOR            ((reg32 *) BUTT_UP_INT__INTC_VECT)

/* Address of the BUTT_UP_INT ISR priority. */
#define BUTT_UP_INT_INTC_PRIOR             ((reg32 *) BUTT_UP_INT__INTC_PRIOR_REG)

/* Priority of the BUTT_UP_INT interrupt. */
#define BUTT_UP_INT_INTC_PRIOR_NUMBER      BUTT_UP_INT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable BUTT_UP_INT interrupt. */
#define BUTT_UP_INT_INTC_SET_EN            ((reg32 *) BUTT_UP_INT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the BUTT_UP_INT interrupt. */
#define BUTT_UP_INT_INTC_CLR_EN            ((reg32 *) BUTT_UP_INT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the BUTT_UP_INT interrupt state to pending. */
#define BUTT_UP_INT_INTC_SET_PD            ((reg32 *) BUTT_UP_INT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the BUTT_UP_INT interrupt. */
#define BUTT_UP_INT_INTC_CLR_PD            ((reg32 *) BUTT_UP_INT__INTC_CLR_PD_REG)



#endif /* CY_ISR_BUTT_UP_INT_H */


/* [] END OF FILE */
