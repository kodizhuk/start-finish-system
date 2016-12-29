/*******************************************************************************
* File Name: PinDebugTime.h  
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

#if !defined(CY_PINS_PinDebugTime_ALIASES_H) /* Pins PinDebugTime_ALIASES_H */
#define CY_PINS_PinDebugTime_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PinDebugTime_0			(PinDebugTime__0__PC)
#define PinDebugTime_0_PS		(PinDebugTime__0__PS)
#define PinDebugTime_0_PC		(PinDebugTime__0__PC)
#define PinDebugTime_0_DR		(PinDebugTime__0__DR)
#define PinDebugTime_0_SHIFT	(PinDebugTime__0__SHIFT)
#define PinDebugTime_0_INTR	((uint16)((uint16)0x0003u << (PinDebugTime__0__SHIFT*2u)))

#define PinDebugTime_INTR_ALL	 ((uint16)(PinDebugTime_0_INTR))


#endif /* End Pins PinDebugTime_ALIASES_H */


/* [] END OF FILE */
