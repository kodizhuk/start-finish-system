/*******************************************************************************
* File Name: SwSPI_Master_SPI.h  
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

#if !defined(CY_PINS_SwSPI_Master_SPI_ALIASES_H) /* Pins SwSPI_Master_SPI_ALIASES_H */
#define CY_PINS_SwSPI_Master_SPI_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SwSPI_Master_SPI_0			(SwSPI_Master_SPI__0__PC)
#define SwSPI_Master_SPI_0_PS		(SwSPI_Master_SPI__0__PS)
#define SwSPI_Master_SPI_0_PC		(SwSPI_Master_SPI__0__PC)
#define SwSPI_Master_SPI_0_DR		(SwSPI_Master_SPI__0__DR)
#define SwSPI_Master_SPI_0_SHIFT	(SwSPI_Master_SPI__0__SHIFT)
#define SwSPI_Master_SPI_0_INTR	((uint16)((uint16)0x0003u << (SwSPI_Master_SPI__0__SHIFT*2u)))

#define SwSPI_Master_SPI_1			(SwSPI_Master_SPI__1__PC)
#define SwSPI_Master_SPI_1_PS		(SwSPI_Master_SPI__1__PS)
#define SwSPI_Master_SPI_1_PC		(SwSPI_Master_SPI__1__PC)
#define SwSPI_Master_SPI_1_DR		(SwSPI_Master_SPI__1__DR)
#define SwSPI_Master_SPI_1_SHIFT	(SwSPI_Master_SPI__1__SHIFT)
#define SwSPI_Master_SPI_1_INTR	((uint16)((uint16)0x0003u << (SwSPI_Master_SPI__1__SHIFT*2u)))

#define SwSPI_Master_SPI_2			(SwSPI_Master_SPI__2__PC)
#define SwSPI_Master_SPI_2_PS		(SwSPI_Master_SPI__2__PS)
#define SwSPI_Master_SPI_2_PC		(SwSPI_Master_SPI__2__PC)
#define SwSPI_Master_SPI_2_DR		(SwSPI_Master_SPI__2__DR)
#define SwSPI_Master_SPI_2_SHIFT	(SwSPI_Master_SPI__2__SHIFT)
#define SwSPI_Master_SPI_2_INTR	((uint16)((uint16)0x0003u << (SwSPI_Master_SPI__2__SHIFT*2u)))

#define SwSPI_Master_SPI_INTR_ALL	 ((uint16)(SwSPI_Master_SPI_0_INTR| SwSPI_Master_SPI_1_INTR| SwSPI_Master_SPI_2_INTR))
#define SwSPI_Master_SPI_CS			(SwSPI_Master_SPI__CS__PC)
#define SwSPI_Master_SPI_CS_PS		(SwSPI_Master_SPI__CS__PS)
#define SwSPI_Master_SPI_CS_PC		(SwSPI_Master_SPI__CS__PC)
#define SwSPI_Master_SPI_CS_DR		(SwSPI_Master_SPI__CS__DR)
#define SwSPI_Master_SPI_CS_SHIFT	(SwSPI_Master_SPI__CS__SHIFT)
#define SwSPI_Master_SPI_CS_INTR	((uint16)((uint16)0x0003u << (SwSPI_Master_SPI__0__SHIFT*2u)))

#define SwSPI_Master_SPI_CLK			(SwSPI_Master_SPI__CLK__PC)
#define SwSPI_Master_SPI_CLK_PS		(SwSPI_Master_SPI__CLK__PS)
#define SwSPI_Master_SPI_CLK_PC		(SwSPI_Master_SPI__CLK__PC)
#define SwSPI_Master_SPI_CLK_DR		(SwSPI_Master_SPI__CLK__DR)
#define SwSPI_Master_SPI_CLK_SHIFT	(SwSPI_Master_SPI__CLK__SHIFT)
#define SwSPI_Master_SPI_CLK_INTR	((uint16)((uint16)0x0003u << (SwSPI_Master_SPI__1__SHIFT*2u)))

#define SwSPI_Master_SPI_MOSI			(SwSPI_Master_SPI__MOSI__PC)
#define SwSPI_Master_SPI_MOSI_PS		(SwSPI_Master_SPI__MOSI__PS)
#define SwSPI_Master_SPI_MOSI_PC		(SwSPI_Master_SPI__MOSI__PC)
#define SwSPI_Master_SPI_MOSI_DR		(SwSPI_Master_SPI__MOSI__DR)
#define SwSPI_Master_SPI_MOSI_SHIFT	(SwSPI_Master_SPI__MOSI__SHIFT)
#define SwSPI_Master_SPI_MOSI_INTR	((uint16)((uint16)0x0003u << (SwSPI_Master_SPI__2__SHIFT*2u)))


#endif /* End Pins SwSPI_Master_SPI_ALIASES_H */


/* [] END OF FILE */
