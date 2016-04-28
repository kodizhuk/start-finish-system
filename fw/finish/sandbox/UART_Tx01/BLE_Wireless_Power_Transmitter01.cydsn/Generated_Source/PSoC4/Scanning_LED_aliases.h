/*******************************************************************************
* File Name: Scanning_LED.h  
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

#if !defined(CY_PINS_Scanning_LED_ALIASES_H) /* Pins Scanning_LED_ALIASES_H */
#define CY_PINS_Scanning_LED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Scanning_LED_0			(Scanning_LED__0__PC)
#define Scanning_LED_0_PS		(Scanning_LED__0__PS)
#define Scanning_LED_0_PC		(Scanning_LED__0__PC)
#define Scanning_LED_0_DR		(Scanning_LED__0__DR)
#define Scanning_LED_0_SHIFT	(Scanning_LED__0__SHIFT)
#define Scanning_LED_0_INTR	((uint16)((uint16)0x0003u << (Scanning_LED__0__SHIFT*2u)))

#define Scanning_LED_INTR_ALL	 ((uint16)(Scanning_LED_0_INTR))


#endif /* End Pins Scanning_LED_ALIASES_H */


/* [] END OF FILE */
