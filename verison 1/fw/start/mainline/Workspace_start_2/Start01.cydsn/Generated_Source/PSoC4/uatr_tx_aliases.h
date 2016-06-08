/*******************************************************************************
* File Name: uatr_tx.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_uatr_tx_ALIASES_H) /* Pins uatr_tx_ALIASES_H */
#define CY_PINS_uatr_tx_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define uatr_tx_0			(uatr_tx__0__PC)
#define uatr_tx_0_PS		(uatr_tx__0__PS)
#define uatr_tx_0_PC		(uatr_tx__0__PC)
#define uatr_tx_0_DR		(uatr_tx__0__DR)
#define uatr_tx_0_SHIFT	(uatr_tx__0__SHIFT)
#define uatr_tx_0_INTR	((uint16)((uint16)0x0003u << (uatr_tx__0__SHIFT*2u)))

#define uatr_tx_INTR_ALL	 ((uint16)(uatr_tx_0_INTR))


#endif /* End Pins uatr_tx_ALIASES_H */


/* [] END OF FILE */
