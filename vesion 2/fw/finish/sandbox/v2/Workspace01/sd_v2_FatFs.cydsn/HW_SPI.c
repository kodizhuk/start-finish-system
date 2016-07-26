/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "HW_SPI.h"

void SPI_Init(void)
{
    CS_SPI_Write(1u);
    CLK_SPI_Write(0u);
    MOSI_SPI_Write(0u);
}

void ChipSelect()
{
    CS_SPI_Write(0u);
}

void ChipDeselect()
{
    CS_SPI_Write(1u);
}


void SPI_SendByte(uint8_t byte)
{
    uint8_t countBites;
    for (countBites = 8; countBites > 0; countBites--)
    {
    
        if (byte & 0x80)
        {
            MOSI_SPI_Write(1u);
        }
        else
        {
            MOSI_SPI_Write(0u);
        }
        CyDelayCycles(10);        
        CLK_SPI_Write(1u);
        
        CyDelayCycles(20);
        
        CLK_SPI_Write(0u);
        byte <<=  1;
    }
    
    MOSI_SPI_Write(0u);    
}

void SPI_SendBuff(uint8_t* buff, uint8_t cnt)
{
    uint8_t tmpData;
    for (tmpData = 0; tmpData < cnt; tmpData ++)
    {
        SPI_SendByte(buff[tmpData]);
    }
}


uint8_t SPI_RecvByte(void)
{
    uint32_t countBites;
    uint32_t tmpBuff = 0, tmpPin;
    for (countBites = 8; countBites > 0; countBites--)
    {
        MOSI_SPI_Write(1u);
        CLK_SPI_Write(1u);
        tmpPin = MISO_SPI_Read();
        if (tmpPin == 1u)
        {
            tmpBuff |= 0x01;
        }

        CLK_SPI_Write(0u);
        CyDelayCycles(15);
        
        tmpBuff <<= 1;
    }
    tmpBuff >>= 1;
    MOSI_SPI_Write(0u);
    return (uint8_t)tmpBuff;
}

void SPI_RecvBuff(uint8_t* buff, uint8_t cnt)
{
    uint8_t tmpData;
    for (tmpData = 0; tmpData < cnt; tmpData ++)
    {
        buff[tmpData] = SPI_RecvByte(); 
    }
}

/* [] END OF FILE */
