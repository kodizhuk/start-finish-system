/*******************************************************************************
* File Name: start.h  
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

#if !defined(CY_PINS_start_ALIASES_H) /* Pins start_ALIASES_H */
#define CY_PINS_start_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define start_0			(start__0__PC)
#define start_0_PS		(start__0__PS)
#define start_0_PC		(start__0__PC)
#define start_0_DR		(start__0__DR)
#define start_0_SHIFT	(start__0__SHIFT)
#define start_0_INTR	((uint16)((uint16)0x0003u << (start__0__SHIFT*2u)))

#define start_INTR_ALL	 ((uint16)(start_0_INTR))


#endif /* End Pins start_ALIASES_H */


/* [] END OF FILE */
