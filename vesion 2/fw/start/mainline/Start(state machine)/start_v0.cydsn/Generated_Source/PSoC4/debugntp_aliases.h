/*******************************************************************************
* File Name: debugntp.h  
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

#if !defined(CY_PINS_debugntp_ALIASES_H) /* Pins debugntp_ALIASES_H */
#define CY_PINS_debugntp_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define debugntp_0			(debugntp__0__PC)
#define debugntp_0_PS		(debugntp__0__PS)
#define debugntp_0_PC		(debugntp__0__PC)
#define debugntp_0_DR		(debugntp__0__DR)
#define debugntp_0_SHIFT	(debugntp__0__SHIFT)
#define debugntp_0_INTR	((uint16)((uint16)0x0003u << (debugntp__0__SHIFT*2u)))

#define debugntp_INTR_ALL	 ((uint16)(debugntp_0_INTR))


#endif /* End Pins debugntp_ALIASES_H */


/* [] END OF FILE */
