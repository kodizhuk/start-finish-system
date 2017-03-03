/*******************************************************************************
* File Name: SW_RunTestMode.h  
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

#if !defined(CY_PINS_SW_RunTestMode_ALIASES_H) /* Pins SW_RunTestMode_ALIASES_H */
#define CY_PINS_SW_RunTestMode_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SW_RunTestMode_0			(SW_RunTestMode__0__PC)
#define SW_RunTestMode_0_PS		(SW_RunTestMode__0__PS)
#define SW_RunTestMode_0_PC		(SW_RunTestMode__0__PC)
#define SW_RunTestMode_0_DR		(SW_RunTestMode__0__DR)
#define SW_RunTestMode_0_SHIFT	(SW_RunTestMode__0__SHIFT)
#define SW_RunTestMode_0_INTR	((uint16)((uint16)0x0003u << (SW_RunTestMode__0__SHIFT*2u)))

#define SW_RunTestMode_INTR_ALL	 ((uint16)(SW_RunTestMode_0_INTR))


#endif /* End Pins SW_RunTestMode_ALIASES_H */


/* [] END OF FILE */
