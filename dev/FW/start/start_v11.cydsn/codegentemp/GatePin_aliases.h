/*******************************************************************************
* File Name: GatePin.h  
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

#if !defined(CY_PINS_GatePin_ALIASES_H) /* Pins GatePin_ALIASES_H */
#define CY_PINS_GatePin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define GatePin_0			(GatePin__0__PC)
#define GatePin_0_PS		(GatePin__0__PS)
#define GatePin_0_PC		(GatePin__0__PC)
#define GatePin_0_DR		(GatePin__0__DR)
#define GatePin_0_SHIFT	(GatePin__0__SHIFT)
#define GatePin_0_INTR	((uint16)((uint16)0x0003u << (GatePin__0__SHIFT*2u)))

#define GatePin_INTR_ALL	 ((uint16)(GatePin_0_INTR))


#endif /* End Pins GatePin_ALIASES_H */


/* [] END OF FILE */
