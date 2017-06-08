/*******************************************************************************
* File Name: BTN_INT.h
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
#if !defined(CY_ISR_BTN_INT_H)
#define CY_ISR_BTN_INT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void BTN_INT_Start(void);
void BTN_INT_StartEx(cyisraddress address);
void BTN_INT_Stop(void);

CY_ISR_PROTO(BTN_INT_Interrupt);

void BTN_INT_SetVector(cyisraddress address);
cyisraddress BTN_INT_GetVector(void);

void BTN_INT_SetPriority(uint8 priority);
uint8 BTN_INT_GetPriority(void);

void BTN_INT_Enable(void);
uint8 BTN_INT_GetState(void);
void BTN_INT_Disable(void);

void BTN_INT_SetPending(void);
void BTN_INT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the BTN_INT ISR. */
#define BTN_INT_INTC_VECTOR            ((reg32 *) BTN_INT__INTC_VECT)

/* Address of the BTN_INT ISR priority. */
#define BTN_INT_INTC_PRIOR             ((reg32 *) BTN_INT__INTC_PRIOR_REG)

/* Priority of the BTN_INT interrupt. */
#define BTN_INT_INTC_PRIOR_NUMBER      BTN_INT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable BTN_INT interrupt. */
#define BTN_INT_INTC_SET_EN            ((reg32 *) BTN_INT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the BTN_INT interrupt. */
#define BTN_INT_INTC_CLR_EN            ((reg32 *) BTN_INT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the BTN_INT interrupt state to pending. */
#define BTN_INT_INTC_SET_PD            ((reg32 *) BTN_INT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the BTN_INT interrupt. */
#define BTN_INT_INTC_CLR_PD            ((reg32 *) BTN_INT__INTC_CLR_PD_REG)



#endif /* CY_ISR_BTN_INT_H */


/* [] END OF FILE */
