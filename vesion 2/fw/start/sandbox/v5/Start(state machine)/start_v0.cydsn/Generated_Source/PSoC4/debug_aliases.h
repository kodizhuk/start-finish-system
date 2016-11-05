/*******************************************************************************
* File Name: debug.h  
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

#if !defined(CY_PINS_debug_ALIASES_H) /* Pins debug_ALIASES_H */
#define CY_PINS_debug_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define debug_0			(debug__0__PC)
#define debug_0_PS		(debug__0__PS)
#define debug_0_PC		(debug__0__PC)
#define debug_0_DR		(debug__0__DR)
#define debug_0_SHIFT	(debug__0__SHIFT)
#define debug_0_INTR	((uint16)((uint16)0x0003u << (debug__0__SHIFT*2u)))

#define debug_INTR_ALL	 ((uint16)(debug_0_INTR))


#endif /* End Pins debug_ALIASES_H */


/* [] END OF FILE */
