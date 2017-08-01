/*******************************************************************************
* File Name: BtnGateEnable.h  
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

#if !defined(CY_PINS_BtnGateEnable_ALIASES_H) /* Pins BtnGateEnable_ALIASES_H */
#define CY_PINS_BtnGateEnable_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BtnGateEnable_0			(BtnGateEnable__0__PC)
#define BtnGateEnable_0_PS		(BtnGateEnable__0__PS)
#define BtnGateEnable_0_PC		(BtnGateEnable__0__PC)
#define BtnGateEnable_0_DR		(BtnGateEnable__0__DR)
#define BtnGateEnable_0_SHIFT	(BtnGateEnable__0__SHIFT)
#define BtnGateEnable_0_INTR	((uint16)((uint16)0x0003u << (BtnGateEnable__0__SHIFT*2u)))

#define BtnGateEnable_INTR_ALL	 ((uint16)(BtnGateEnable_0_INTR))


#endif /* End Pins BtnGateEnable_ALIASES_H */


/* [] END OF FILE */
