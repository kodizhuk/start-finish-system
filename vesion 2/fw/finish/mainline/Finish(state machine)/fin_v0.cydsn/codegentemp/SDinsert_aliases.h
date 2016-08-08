/*******************************************************************************
* File Name: SDinsert.h  
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

#if !defined(CY_PINS_SDinsert_ALIASES_H) /* Pins SDinsert_ALIASES_H */
#define CY_PINS_SDinsert_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SDinsert_0			(SDinsert__0__PC)
#define SDinsert_0_PS		(SDinsert__0__PS)
#define SDinsert_0_PC		(SDinsert__0__PC)
#define SDinsert_0_DR		(SDinsert__0__DR)
#define SDinsert_0_SHIFT	(SDinsert__0__SHIFT)
#define SDinsert_0_INTR	((uint16)((uint16)0x0003u << (SDinsert__0__SHIFT*2u)))

#define SDinsert_INTR_ALL	 ((uint16)(SDinsert_0_INTR))


#endif /* End Pins SDinsert_ALIASES_H */


/* [] END OF FILE */
