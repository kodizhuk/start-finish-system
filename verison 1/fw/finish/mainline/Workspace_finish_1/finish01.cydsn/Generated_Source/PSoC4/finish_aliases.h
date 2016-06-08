/*******************************************************************************
* File Name: finish.h  
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

#if !defined(CY_PINS_finish_ALIASES_H) /* Pins finish_ALIASES_H */
#define CY_PINS_finish_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define finish_0			(finish__0__PC)
#define finish_0_PS		(finish__0__PS)
#define finish_0_PC		(finish__0__PC)
#define finish_0_DR		(finish__0__DR)
#define finish_0_SHIFT	(finish__0__SHIFT)
#define finish_0_INTR	((uint16)((uint16)0x0003u << (finish__0__SHIFT*2u)))

#define finish_INTR_ALL	 ((uint16)(finish_0_INTR))


#endif /* End Pins finish_ALIASES_H */


/* [] END OF FILE */
