/*******************************************************************************
* File Name: BtnUp.h  
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

#if !defined(CY_PINS_BtnUp_ALIASES_H) /* Pins BtnUp_ALIASES_H */
#define CY_PINS_BtnUp_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BtnUp_0			(BtnUp__0__PC)
#define BtnUp_0_PS		(BtnUp__0__PS)
#define BtnUp_0_PC		(BtnUp__0__PC)
#define BtnUp_0_DR		(BtnUp__0__DR)
#define BtnUp_0_SHIFT	(BtnUp__0__SHIFT)
#define BtnUp_0_INTR	((uint16)((uint16)0x0003u << (BtnUp__0__SHIFT*2u)))

#define BtnUp_INTR_ALL	 ((uint16)(BtnUp_0_INTR))


#endif /* End Pins BtnUp_ALIASES_H */


/* [] END OF FILE */
