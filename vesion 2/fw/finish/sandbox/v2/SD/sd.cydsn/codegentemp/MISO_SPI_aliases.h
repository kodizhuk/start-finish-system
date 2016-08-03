/*******************************************************************************
* File Name: MISO_SPI.h  
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

#if !defined(CY_PINS_MISO_SPI_ALIASES_H) /* Pins MISO_SPI_ALIASES_H */
#define CY_PINS_MISO_SPI_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define MISO_SPI_0			(MISO_SPI__0__PC)
#define MISO_SPI_0_PS		(MISO_SPI__0__PS)
#define MISO_SPI_0_PC		(MISO_SPI__0__PC)
#define MISO_SPI_0_DR		(MISO_SPI__0__DR)
#define MISO_SPI_0_SHIFT	(MISO_SPI__0__SHIFT)
#define MISO_SPI_0_INTR	((uint16)((uint16)0x0003u << (MISO_SPI__0__SHIFT*2u)))

#define MISO_SPI_INTR_ALL	 ((uint16)(MISO_SPI_0_INTR))


#endif /* End Pins MISO_SPI_ALIASES_H */


/* [] END OF FILE */
