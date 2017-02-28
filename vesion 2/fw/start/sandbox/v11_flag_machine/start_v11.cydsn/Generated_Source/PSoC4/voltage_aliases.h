/*******************************************************************************
* File Name: voltage.h  
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

#if !defined(CY_PINS_voltage_ALIASES_H) /* Pins voltage_ALIASES_H */
#define CY_PINS_voltage_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define voltage_0			(voltage__0__PC)
#define voltage_0_PS		(voltage__0__PS)
#define voltage_0_PC		(voltage__0__PC)
#define voltage_0_DR		(voltage__0__DR)
#define voltage_0_SHIFT	(voltage__0__SHIFT)
#define voltage_0_INTR	((uint16)((uint16)0x0003u << (voltage__0__SHIFT*2u)))

#define voltage_INTR_ALL	 ((uint16)(voltage_0_INTR))


#endif /* End Pins voltage_ALIASES_H */


/* [] END OF FILE */
