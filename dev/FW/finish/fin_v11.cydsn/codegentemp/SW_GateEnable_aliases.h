/*******************************************************************************
* File Name: SW_GateEnable.h  
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

#if !defined(CY_PINS_SW_GateEnable_ALIASES_H) /* Pins SW_GateEnable_ALIASES_H */
#define CY_PINS_SW_GateEnable_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SW_GateEnable_0			(SW_GateEnable__0__PC)
#define SW_GateEnable_0_PS		(SW_GateEnable__0__PS)
#define SW_GateEnable_0_PC		(SW_GateEnable__0__PC)
#define SW_GateEnable_0_DR		(SW_GateEnable__0__DR)
#define SW_GateEnable_0_SHIFT	(SW_GateEnable__0__SHIFT)
#define SW_GateEnable_0_INTR	((uint16)((uint16)0x0003u << (SW_GateEnable__0__SHIFT*2u)))

#define SW_GateEnable_INTR_ALL	 ((uint16)(SW_GateEnable_0_INTR))


#endif /* End Pins SW_GateEnable_ALIASES_H */


/* [] END OF FILE */
