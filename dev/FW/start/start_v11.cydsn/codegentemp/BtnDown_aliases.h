/*******************************************************************************
* File Name: BtnDown.h  
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

#if !defined(CY_PINS_BtnDown_ALIASES_H) /* Pins BtnDown_ALIASES_H */
#define CY_PINS_BtnDown_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BtnDown_0			(BtnDown__0__PC)
#define BtnDown_0_PS		(BtnDown__0__PS)
#define BtnDown_0_PC		(BtnDown__0__PC)
#define BtnDown_0_DR		(BtnDown__0__DR)
#define BtnDown_0_SHIFT	(BtnDown__0__SHIFT)
#define BtnDown_0_INTR	((uint16)((uint16)0x0003u << (BtnDown__0__SHIFT*2u)))

#define BtnDown_INTR_ALL	 ((uint16)(BtnDown_0_INTR))


#endif /* End Pins BtnDown_ALIASES_H */


/* [] END OF FILE */
