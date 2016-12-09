/*******************************************************************************
* File Name: pinDebugNtp.h  
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

#if !defined(CY_PINS_pinDebugNtp_ALIASES_H) /* Pins pinDebugNtp_ALIASES_H */
#define CY_PINS_pinDebugNtp_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pinDebugNtp_0			(pinDebugNtp__0__PC)
#define pinDebugNtp_0_PS		(pinDebugNtp__0__PS)
#define pinDebugNtp_0_PC		(pinDebugNtp__0__PC)
#define pinDebugNtp_0_DR		(pinDebugNtp__0__DR)
#define pinDebugNtp_0_SHIFT	(pinDebugNtp__0__SHIFT)
#define pinDebugNtp_0_INTR	((uint16)((uint16)0x0003u << (pinDebugNtp__0__SHIFT*2u)))

#define pinDebugNtp_INTR_ALL	 ((uint16)(pinDebugNtp_0_INTR))


#endif /* End Pins pinDebugNtp_ALIASES_H */


/* [] END OF FILE */
