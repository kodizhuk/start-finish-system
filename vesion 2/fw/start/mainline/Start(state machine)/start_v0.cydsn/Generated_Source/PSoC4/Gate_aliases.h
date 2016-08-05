/*******************************************************************************
* File Name: Gate.h  
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

#if !defined(CY_PINS_Gate_ALIASES_H) /* Pins Gate_ALIASES_H */
#define CY_PINS_Gate_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Gate_0			(Gate__0__PC)
#define Gate_0_PS		(Gate__0__PS)
#define Gate_0_PC		(Gate__0__PC)
#define Gate_0_DR		(Gate__0__DR)
#define Gate_0_SHIFT	(Gate__0__SHIFT)
#define Gate_0_INTR	((uint16)((uint16)0x0003u << (Gate__0__SHIFT*2u)))

#define Gate_INTR_ALL	 ((uint16)(Gate_0_INTR))


#endif /* End Pins Gate_ALIASES_H */


/* [] END OF FILE */
