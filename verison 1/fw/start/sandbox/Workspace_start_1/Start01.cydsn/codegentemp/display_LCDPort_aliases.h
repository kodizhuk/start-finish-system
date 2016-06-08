/*******************************************************************************
* File Name: display_LCDPort.h  
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

#if !defined(CY_PINS_display_LCDPort_ALIASES_H) /* Pins display_LCDPort_ALIASES_H */
#define CY_PINS_display_LCDPort_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define display_LCDPort_0			(display_LCDPort__0__PC)
#define display_LCDPort_0_PS		(display_LCDPort__0__PS)
#define display_LCDPort_0_PC		(display_LCDPort__0__PC)
#define display_LCDPort_0_DR		(display_LCDPort__0__DR)
#define display_LCDPort_0_SHIFT	(display_LCDPort__0__SHIFT)
#define display_LCDPort_0_INTR	((uint16)((uint16)0x0003u << (display_LCDPort__0__SHIFT*2u)))

#define display_LCDPort_1			(display_LCDPort__1__PC)
#define display_LCDPort_1_PS		(display_LCDPort__1__PS)
#define display_LCDPort_1_PC		(display_LCDPort__1__PC)
#define display_LCDPort_1_DR		(display_LCDPort__1__DR)
#define display_LCDPort_1_SHIFT	(display_LCDPort__1__SHIFT)
#define display_LCDPort_1_INTR	((uint16)((uint16)0x0003u << (display_LCDPort__1__SHIFT*2u)))

#define display_LCDPort_2			(display_LCDPort__2__PC)
#define display_LCDPort_2_PS		(display_LCDPort__2__PS)
#define display_LCDPort_2_PC		(display_LCDPort__2__PC)
#define display_LCDPort_2_DR		(display_LCDPort__2__DR)
#define display_LCDPort_2_SHIFT	(display_LCDPort__2__SHIFT)
#define display_LCDPort_2_INTR	((uint16)((uint16)0x0003u << (display_LCDPort__2__SHIFT*2u)))

#define display_LCDPort_3			(display_LCDPort__3__PC)
#define display_LCDPort_3_PS		(display_LCDPort__3__PS)
#define display_LCDPort_3_PC		(display_LCDPort__3__PC)
#define display_LCDPort_3_DR		(display_LCDPort__3__DR)
#define display_LCDPort_3_SHIFT	(display_LCDPort__3__SHIFT)
#define display_LCDPort_3_INTR	((uint16)((uint16)0x0003u << (display_LCDPort__3__SHIFT*2u)))

#define display_LCDPort_4			(display_LCDPort__4__PC)
#define display_LCDPort_4_PS		(display_LCDPort__4__PS)
#define display_LCDPort_4_PC		(display_LCDPort__4__PC)
#define display_LCDPort_4_DR		(display_LCDPort__4__DR)
#define display_LCDPort_4_SHIFT	(display_LCDPort__4__SHIFT)
#define display_LCDPort_4_INTR	((uint16)((uint16)0x0003u << (display_LCDPort__4__SHIFT*2u)))

#define display_LCDPort_5			(display_LCDPort__5__PC)
#define display_LCDPort_5_PS		(display_LCDPort__5__PS)
#define display_LCDPort_5_PC		(display_LCDPort__5__PC)
#define display_LCDPort_5_DR		(display_LCDPort__5__DR)
#define display_LCDPort_5_SHIFT	(display_LCDPort__5__SHIFT)
#define display_LCDPort_5_INTR	((uint16)((uint16)0x0003u << (display_LCDPort__5__SHIFT*2u)))

#define display_LCDPort_6			(display_LCDPort__6__PC)
#define display_LCDPort_6_PS		(display_LCDPort__6__PS)
#define display_LCDPort_6_PC		(display_LCDPort__6__PC)
#define display_LCDPort_6_DR		(display_LCDPort__6__DR)
#define display_LCDPort_6_SHIFT	(display_LCDPort__6__SHIFT)
#define display_LCDPort_6_INTR	((uint16)((uint16)0x0003u << (display_LCDPort__6__SHIFT*2u)))

#define display_LCDPort_INTR_ALL	 ((uint16)(display_LCDPort_0_INTR| display_LCDPort_1_INTR| display_LCDPort_2_INTR| display_LCDPort_3_INTR| display_LCDPort_4_INTR| display_LCDPort_5_INTR| display_LCDPort_6_INTR))


#endif /* End Pins display_LCDPort_ALIASES_H */


/* [] END OF FILE */
