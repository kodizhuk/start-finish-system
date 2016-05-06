/*******************************************************************************
* File Name: wired.h  
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

#if !defined(CY_PINS_wired_ALIASES_H) /* Pins wired_ALIASES_H */
#define CY_PINS_wired_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define wired_0			(wired__0__PC)
#define wired_0_PS		(wired__0__PS)
#define wired_0_PC		(wired__0__PC)
#define wired_0_DR		(wired__0__DR)
#define wired_0_SHIFT	(wired__0__SHIFT)
#define wired_0_INTR	((uint16)((uint16)0x0003u << (wired__0__SHIFT*2u)))

#define wired_INTR_ALL	 ((uint16)(wired_0_INTR))


#endif /* End Pins wired_ALIASES_H */


/* [] END OF FILE */
