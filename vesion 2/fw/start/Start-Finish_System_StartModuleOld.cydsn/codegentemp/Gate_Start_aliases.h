/*******************************************************************************
* File Name: Gate_Start.h  
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

#if !defined(CY_PINS_Gate_Start_ALIASES_H) /* Pins Gate_Start_ALIASES_H */
#define CY_PINS_Gate_Start_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Gate_Start_0			(Gate_Start__0__PC)
#define Gate_Start_0_PS		(Gate_Start__0__PS)
#define Gate_Start_0_PC		(Gate_Start__0__PC)
#define Gate_Start_0_DR		(Gate_Start__0__DR)
#define Gate_Start_0_SHIFT	(Gate_Start__0__SHIFT)
#define Gate_Start_0_INTR	((uint16)((uint16)0x0003u << (Gate_Start__0__SHIFT*2u)))

#define Gate_Start_INTR_ALL	 ((uint16)(Gate_Start_0_INTR))


#endif /* End Pins Gate_Start_ALIASES_H */


/* [] END OF FILE */
