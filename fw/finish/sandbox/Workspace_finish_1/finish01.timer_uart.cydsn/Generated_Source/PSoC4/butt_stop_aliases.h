/*******************************************************************************
* File Name: butt_stop.h  
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

#if !defined(CY_PINS_butt_stop_ALIASES_H) /* Pins butt_stop_ALIASES_H */
#define CY_PINS_butt_stop_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define butt_stop_0			(butt_stop__0__PC)
#define butt_stop_0_PS		(butt_stop__0__PS)
#define butt_stop_0_PC		(butt_stop__0__PC)
#define butt_stop_0_DR		(butt_stop__0__DR)
#define butt_stop_0_SHIFT	(butt_stop__0__SHIFT)
#define butt_stop_0_INTR	((uint16)((uint16)0x0003u << (butt_stop__0__SHIFT*2u)))

#define butt_stop_INTR_ALL	 ((uint16)(butt_stop_0_INTR))


#endif /* End Pins butt_stop_ALIASES_H */


/* [] END OF FILE */
