/* ========================================
 *
 * File Name: SPI.c
 * Version 1.20 
 * Copyright ANDREY TKACHOV, 2016
 
 * Description:
 *  This file provides source code for the Software SPI component's API.

 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF PERSONAL LICENSE.
 *
 * ========================================
*/

#include "SPI_PVT.h"

/*******************************************************************************
* Function Name: SPI_Init
********************************************************************************
*
* Summary:
*  Performs initialization required for the components normal work.
*  This function initializes the Software SPI hardware module as follows:
*        Sets initial state for CS, CLK, MOSI pin
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/

void SPI_Init(void) 
{
   SPI_CS_DR_REG |= SPI_CS;
   SPI_SCK_DR_REG &= ((uint8)(~SPI_CLK));
   SPI_MOSI_DR_REG &= ((uint8)(~SPI_MOSI));
}

/*******************************************************************************
* Function Name: SPI_ChipSelect
********************************************************************************
*
* Summary:
*  Sets active state on CS pin.
*  For this mode active state CS is low.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/

void SPI_ChipSelect(void) 
{
/*    SPI_OUTPORT_DR_REG &= ((uint8)(~SPI_CS));*/
}

/*******************************************************************************
* Function Name: SPI_ChipDeselect
********************************************************************************
*
* Summary:
*  Sets disable state on CS pin.
*  For this mode disable state CS is high.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/

void SPI_ChipDeselect(void) 
{
/*    SPI_OUTPORT_DR_REG |= SPI_CS;*/
}

/*******************************************************************************
* Function Name: SPI_SendByte
********************************************************************************
*
* Summary:
*  Sends one byte via Software SPI.
*  One byte are transmitted after 8 periods CLK.
*
* Parameters:
*  Byte to be transmitted
*
* Note:
*  CS must be in active(low) state.
*
* Return:
*  None
*
*******************************************************************************/

void SPI_SendByte(uint8 byte) 
{
    uint8 countBites;
    for (countBites = BITES_ON_ONE_BYTE; countBites > 0; countBites--)
    {
    
        if (byte & MASK_HIGH_BIT)
        {
            SPI_MOSI_DR_REG |= SPI_MOSI;
        }
        else
        {
            SPI_MOSI_DR_REG &= ((uint8)(~SPI_MOSI));
        }  
        SPI_SCK_DR_REG |= SPI_CLK;
        
        CyDelayCycles(DELAY_HIGH_STATE);
        
        SPI_SCK_DR_REG &= ((uint8)(~SPI_CLK));
        CyDelayCycles(DELAY_LOW_STATE);      
        byte <<=  SHIFT_ONE_BIT;
    }
    
    SPI_MOSI_DR_REG &= ((uint8)(~SPI_MOSI));    
}

/*******************************************************************************
* Function Name: SPI_SendBuff
********************************************************************************
*
* Summary:
*  Sends one byte via Software SPI.
*  One byte are transmitted after 8 periods CLK.
*
* Parameters:
*  buff: Pointer to buffer who will be transmitted via SPI.
*  cnt: Count bytes in buffer for transmit.
*
* Note:
*  CS must be in active(low) state.
*  Transmitt no more 65535 bytes. (2^16 - 1)
*
* Return:
*  None
*
*******************************************************************************/

void SPI_SendBuff(const uint8 buff[], uint16 cnt) 
{
    uint16_t tmpData;
    for (tmpData = 0; tmpData < cnt; tmpData ++)
    {
        SPI_SendByte(buff[tmpData]);
    }
}

/*******************************************************************************
* Function Name: SPI_RecvByte
********************************************************************************
*
* Summary:
*  Recieve one byte via Software SPI.
*  One byte are recieved after 8 periods CLK.
*
* Parameters:
*  None.
*
* Note:
*  CS must be in active(low) state.
*
* Return:
*  Recieved byte.
*
*******************************************************************************/

uint8 SPI_RecvByte(void) 
{
    uint32_t countBites;
    uint32_t tmpBuff = 0;
    uint8 tmpPin;
    for (countBites = BITES_ON_ONE_BYTE; countBites > 0; countBites--)
    {
        SPI_MOSI_DR_REG |= SPI_MOSI;
        SPI_SCK_DR_REG |= SPI_CLK;
        tmpPin = (uint8)((SPI_MISO_PS_REG & SPI_MISO_MASK) >> SPI_MISO_SHIFT);
        if (tmpPin == 1u)
        {
            tmpBuff |= MASK_LOW_BIT;
        }
        CyDelayCycles(DELAY_HIGH_STATE);
        
        SPI_SCK_DR_REG &= ((uint8)(~SPI_CLK));
        
        CyDelayCycles(DELAY_LOW_STATE);
        
        tmpBuff <<= SHIFT_ONE_BIT;
    }
    tmpBuff >>= SHIFT_ONE_BIT;
    
    SPI_MOSI_DR_REG &= ((uint8)(~SPI_MOSI));
    
    return (uint8_t)tmpBuff;
}

/*******************************************************************************
* Function Name: SPI_RecvBuff
********************************************************************************
*
* Summary:
*  Recieve few or more bytes via SPI.
*
* Parameters:
*  buff: Pointer to buffer who will be recieved via SPI.
*  cnt: Count bytes in buffer for recieve.
*
* Note:
*  CS must be in active(low) state.
*  Recieve no more 65535 bytes. (2^16 - 1)
*
* Return:
*  None
*
*******************************************************************************/


void SPI_RecvBuff(uint8 *buff, uint16 cnt) 
{
    uint16_t tmpData;
    for (tmpData = 0; tmpData < cnt; tmpData ++)
    {
        buff[tmpData] = SPI_RecvByte(); 
    }
}

/*******************************************************************************
* Function Name: SPI_ReadAndWriteByte
********************************************************************************
*
* Summary:
*  Recieve and Transmitt one bytes via SPI in 8 CLK Periods.
*  (One SPI Perios).
*
* Parameters:
*  byte: Byte who will be transmitted via SPI.
*
* Note:
*  CS must be in active(low) state.
*
* Return:
*  Byte who will be recieved via SPI.
*
*******************************************************************************/


uint8 SPI_ReadAndWriteByte(uint8 byte)
{
    uint8 countBites;
    uint32_t tmpBuff = 0;
    uint8 tmpPin;
    for (countBites = BITES_ON_ONE_BYTE; countBites > 0; countBites--)
    {
    
        if (byte & MASK_HIGH_BIT)
        {
            SPI_MOSI_DR_REG |= SPI_MOSI;
        }
        else
        {
            SPI_MOSI_DR_REG &= ((uint8)(~SPI_MOSI));
        }
        
        SPI_SCK_DR_REG |= SPI_CLK;
        
        tmpPin = (uint8)((SPI_MISO_PS_REG & SPI_MISO_MASK) >> SPI_MISO_SHIFT);
        if (tmpPin == 1u)
        {
            tmpBuff |= MASK_LOW_BIT;
        }
        
        CyDelayCycles(DELAY_HIGH_STATE);
        
         SPI_SCK_DR_REG &= ((uint8)(~SPI_CLK));
        byte <<=  SHIFT_ONE_BIT;
        tmpBuff <<= SHIFT_ONE_BIT;
        CyDelayCycles(DELAY_LOW_STATE);        
    }    
    tmpBuff >>= SHIFT_ONE_BIT;
        
    return (uint8_t)tmpBuff;
    
}    

/* [] END OF FILE */
