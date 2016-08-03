/* ========================================
 *
 * File Name: SwSPI_Master.c
 * Version 1.10 
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "SwSPI_Master_PVT.h"

void SwSPI_Master_Init(void) 
{
   SwSPI_Master_OUTPORT_DR_REG |= SwSPI_Master_CS;
   SwSPI_Master_OUTPORT_DR_REG &= ((uint8)(~SwSPI_Master_CLK));
   SwSPI_Master_OUTPORT_DR_REG &= ((uint8)(~SwSPI_Master_MOSI));
}

void SwSPI_Master_ChipSelect(void) 
{
    SwSPI_Master_OUTPORT_DR_REG &= ((uint8)(~SwSPI_Master_CS));
}

void SwSPI_Master_ChipDeselect(void) 
{
    SwSPI_Master_OUTPORT_DR_REG |= SwSPI_Master_CS;
}


void SwSPI_Master_SendByte(uint8 byte) 
{
    uint8 countBites;
    for (countBites = BITES_ON_ONE_BYTE; countBites > 0; countBites--)
    {
    
        if (byte & MASK_HIGH_BIT)
        {
            SwSPI_Master_OUTPORT_DR_REG |= SwSPI_Master_MOSI;
        }
        else
        {
            SwSPI_Master_OUTPORT_DR_REG &= ((uint8)(~SwSPI_Master_MOSI));
        }  
        SwSPI_Master_OUTPORT_DR_REG |= SwSPI_Master_CLK;
        
        CyDelayCycles(DELAY_HIGH_STATE);
        
        SwSPI_Master_OUTPORT_DR_REG &= ((uint8)(~SwSPI_Master_CLK));
        CyDelayCycles(DELAY_LOW_STATE);      
        byte <<=  SHIFT_ONE_BIT;
    }
    
    SwSPI_Master_OUTPORT_DR_REG &= ((uint8)(~SwSPI_Master_MOSI));    
}

void SwSPI_Master_SendBuff(const uint8 buff[], uint16 cnt) 
{
    uint16_t tmpData;
    for (tmpData = 0; tmpData < cnt; tmpData ++)
    {
        SwSPI_Master_SendByte(buff[tmpData]);
    }
}

uint8 SwSPI_Master_RecvByte(void) 
{
    uint32_t countBites;
    uint32_t tmpBuff = 0;
    uint8 tmpPin;
    for (countBites = BITES_ON_ONE_BYTE; countBites > 0; countBites--)
    {
        SwSPI_Master_OUTPORT_DR_REG |= SwSPI_Master_MOSI;
        SwSPI_Master_OUTPORT_DR_REG |= SwSPI_Master_CLK;
        tmpPin = (uint8)((SwSPI_Master_INPORT_PS_REG & SwSPI_Master_MISO_MASK) >> SwSPI_Master_MISO_SHIFT);
        if (tmpPin == 1u)
        {
            tmpBuff |= MASK_LOW_BIT;
        }
        CyDelayCycles(DELAY_HIGH_STATE);
        
        SwSPI_Master_OUTPORT_DR_REG &= ((uint8)(~SwSPI_Master_CLK));
        
        CyDelayCycles(DELAY_LOW_STATE);
        
        tmpBuff <<= SHIFT_ONE_BIT;
    }
    tmpBuff >>= SHIFT_ONE_BIT;
    
    SwSPI_Master_OUTPORT_DR_REG &= ((uint8)(~SwSPI_Master_MOSI));
    
    return (uint8_t)tmpBuff;
}

void SwSPI_Master_RecvBuff(uint8 *buff, uint16 cnt) 
{
    uint16_t tmpData;
    for (tmpData = 0; tmpData < cnt; tmpData ++)
    {
        buff[tmpData] = SwSPI_Master_RecvByte(); 
    }
}

uint8 SwSPI_Master_ReadAndWriteByte(uint8 byte)
{
    uint8 countBites;
    uint32_t tmpBuff = 0;
    uint8 tmpPin;
    for (countBites = BITES_ON_ONE_BYTE; countBites > 0; countBites--)
    {
    
        if (byte & MASK_HIGH_BIT)
        {
            SwSPI_Master_OUTPORT_DR_REG |= SwSPI_Master_MOSI;
        }
        else
        {
            SwSPI_Master_OUTPORT_DR_REG &= ((uint8)(~SwSPI_Master_MOSI));
        }
        
        SwSPI_Master_OUTPORT_DR_REG |= SwSPI_Master_CLK;
        
        tmpPin = (uint8)((SwSPI_Master_INPORT_PS_REG & SwSPI_Master_MISO_MASK) >> SwSPI_Master_MISO_SHIFT);
        if (tmpPin == 1u)
        {
            tmpBuff |= MASK_LOW_BIT;
        }
        
        CyDelayCycles(DELAY_HIGH_STATE);
        
        SwSPI_Master_OUTPORT_DR_REG &= ((uint8)(~SwSPI_Master_CLK));
        CyDelayCycles(DELAY_LOW_STATE);    
        byte <<=  SHIFT_ONE_BIT;
        tmpBuff <<= SHIFT_ONE_BIT;
    
    }    
    tmpBuff >>= SHIFT_ONE_BIT;
        
    return (uint8_t)tmpBuff;
    
}    

/* [] END OF FILE */
