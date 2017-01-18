/* ========================================
 *
 * File Name: `$INSTANCE_NAME`.c
 * Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` 
 * Copyright ANDREY TKACHOV, 2016
 
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF PERSONAL LICENSE.
 *
 * ========================================
*/

#include "`$INSTANCE_NAME`_PVT.h"

void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil("`$INSTANCE_NAME`_Init")`
{
   `$INSTANCE_NAME`_OUTPORT_DR_REG |= `$INSTANCE_NAME`_CS;
   `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_CLK));
   `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_MOSI));
}

void `$INSTANCE_NAME`_ChipSelect(void) `=ReentrantKeil("`$INSTANCE_NAME`_ChipSelect")`
{
    `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_CS));
}

void `$INSTANCE_NAME`_ChipDeselect(void) `=ReentrantKeil("`$INSTANCE_NAME`_ChipDeselect")`
{
    `$INSTANCE_NAME`_OUTPORT_DR_REG |= `$INSTANCE_NAME`_CS;
}


void `$INSTANCE_NAME`_SendByte(uint8 byte) `=ReentrantKeil("`$INSTANCE_NAME`_SendByte")`
{
    uint8 countBites;
    for (countBites = BITES_ON_ONE_BYTE; countBites > 0; countBites--)
    {
    
        if (byte & MASK_HIGH_BIT)
        {
            `$INSTANCE_NAME`_OUTPORT_DR_REG |= `$INSTANCE_NAME`_MOSI;
        }
        else
        {
            `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_MOSI));
        }
        CyDelayCycles(DELAY_HIGH_STATE);        
        `$INSTANCE_NAME`_OUTPORT_DR_REG |= `$INSTANCE_NAME`_CLK;
        
        CyDelayCycles(DELAY_LOW_STATE);
        
         `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_CLK));
        byte <<=  SHIFT_ONE_BIT;
    }
    
    `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_MOSI));    
}

void `$INSTANCE_NAME`_SendBuff(const uint8 buff[], uint16 cnt) `=ReentrantKeil("`$INSTANCE_NAME`_SendBuff")`
{
    uint16_t tmpData;
    for (tmpData = 0; tmpData < cnt; tmpData ++)
    {
        `$INSTANCE_NAME`_SendByte(buff[tmpData]);
    }
}

uint8 `$INSTANCE_NAME`_RecvByte(void) `=ReentrantKeil("`$INSTANCE_NAME`_RecvByte")`
{
    uint32_t countBites;
    uint32_t tmpBuff = 0;
    uint8 tmpPin;
    for (countBites = BITES_ON_ONE_BYTE; countBites > 0; countBites--)
    {
        `$INSTANCE_NAME`_OUTPORT_DR_REG |= `$INSTANCE_NAME`_MOSI;
        `$INSTANCE_NAME`_OUTPORT_DR_REG |= `$INSTANCE_NAME`_CLK;
        tmpPin = (uint8)((`$INSTANCE_NAME`_INPORT_PS_REG & `$INSTANCE_NAME`_MISO_MASK) >> `$INSTANCE_NAME`_MISO_SHIFT);
        if (tmpPin == 1u)
        {
            tmpBuff |= MASK_LOW_BIT;
        }
        CyDelayCycles(DELAY_HIGH_STATE);
        
        `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_CLK));
        
        CyDelayCycles(DELAY_LOW_STATE);
        
        tmpBuff <<= SHIFT_ONE_BIT;
    }
    tmpBuff >>= SHIFT_ONE_BIT;
    
    `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_MOSI));
    
    return (uint8_t)tmpBuff;
}

void `$INSTANCE_NAME`_RecvBuff(uint8 *buff, uint16 cnt) `=ReentrantKeil("`$INSTANCE_NAME`_RecvBuff")`
{
    uint16_t tmpData;
    for (tmpData = 0; tmpData < cnt; tmpData ++)
    {
        buff[tmpData] = `$INSTANCE_NAME`_RecvByte(); 
    }
}


/* [] END OF FILE */
