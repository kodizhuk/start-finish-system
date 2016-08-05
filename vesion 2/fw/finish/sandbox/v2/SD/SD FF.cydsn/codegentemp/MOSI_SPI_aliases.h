/*******************************************************************************
* File Name: MOSI_SPI.h  
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

#if !defined(CY_PINS_MOSI_SPI_ALIASES_H) /* Pins MOSI_SPI_ALIASES_H */
#define CY_PINS_MOSI_SPI_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define MOSI_SPI_0			(MOSI_SPI__0__PC)
#define MOSI_SPI_0_PS		(MOSI_SPI__0__PS)
#define MOSI_SPI_0_PC		(MOSI_SPI__0__PC)
#define MOSI_SPI_0_DR		(MOSI_SPI__0__DR)
#define MOSI_SPI_0_SHIFT	(MOSI_SPI__0__SHIFT)
#define MOSI_SPI_0_INTR	((uint16)((uint16)0x0003u << (MOSI_SPI__0__SHIFT*2u)))

#define MOSI_SPI_INTR_ALL	 ((uint16)(MOSI_SPI_0_INTR))


#endif /* End Pins MOSI_SPI_ALIASES_H */


/* [] END OF FILE */
