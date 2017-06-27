/* ========================================
 *
 * File Name: SwSPI_Master_1.c
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

#include "SwSPI_Master_1_PVT.h"

/*******************************************************************************
* Function Name: SwSPI_Master_1_Init
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

void SwSPI_Master_1_Init(void) 
{
   SwSPI_Master_1_CS_DR_REG |= SwSPI_Master_1_CS;
   SwSPI_Master_1_SCK_DR_REG &= ((uint8)(~SwSPI_Master_1_CLK));
   SwSPI_Master_1_MOSI_DR_REG &= ((uint8)(~SwSPI_Master_1_MOSI));
}

/*******************************************************************************
* Function Name: SwSPI_Master_1_ChipSelect
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

void SwSPI_Master_1_ChipSelect(void) 
{
/*    SwSPI_Master_1_OUTPORT_DR_REG &= ((uint8)(~SwSPI_Master_1_CS));*/
}

/*******************************************************************************
* Function Name: SwSPI_Master_1_ChipDeselect
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

void SwSPI_Master_1_ChipDeselect(void) 
{
/*    SwSPI_Master_1_OUTPORT_DR_REG |= SwSPI_Master_1_CS;*/
}

/*******************************************************************************
* Function Name: SwSPI_Master_1_SendByte
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

void SwSPI_Master_1_SendByte(uint8 byte) 
{
    uint8 countBites;
    for (countBites = BITES_ON_ONE_BYTE; countBites > 0; countBites--)
    {
    
        if (byte & MASK_HIGH_BIT)
        {
            SwSPI_Master_1_MOSI_DR_REG |= SwSPI_Master_1_MOSI;
        }
        else
        {
            SwSPI_Master_1_MOSI_DR_REG &= ((uint8)(~SwSPI_Master_1_MOSI));
        }  
        SwSPI_Master_1_SCK_DR_REG |= SwSPI_Master_1_CLK;
        
        CyDelayCycles(DELAY_HIGH_STATE);
        
        SwSPI_Master_1_SCK_DR_REG &= ((uint8)(~SwSPI_Master_1_CLK));
        CyDelayCycles(DELAY_LOW_STATE);      
        byte <<=  SHIFT_ONE_BIT;
    }
    
    SwSPI_Master_1_MOSI_DR_REG &= ((uint8)(~SwSPI_Master_1_MOSI));    
}

/*******************************************************************************
* Function Name: SwSPI_Master_1_SendBuff
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

void SwSPI_Master_1_SendBuff(const uint8 buff[], uint16 cnt) 
{
    uint16_t tmpData;
    for (tmpData = 0; tmpData < cnt; tmpData ++)
    {
        SwSPI_Master_1_SendByte(buff[tmpData]);
    }
}

/*******************************************************************************
* Function Name: SwSPI_Master_1_RecvByte
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

uint8 SwSPI_Master_1_RecvByte(void) 
{
    uint32_t countBites;
    uint32_t tmpBuff = 0;
    uint8 tmpPin;
    for (countBites = BITES_ON_ONE_BYTE; countBites > 0; countBites--)
    {
        SwSPI_Master_1_MOSI_DR_REG |= SwSPI_Master_1_MOSI;
        SwSPI_Master_1_SCK_DR_REG |= SwSPI_Master_1_CLK;
        tmpPin = (uint8)((SwSPI_Master_1_MISO_PS_REG & SwSPI_Master_1_MISO_MASK) >> SwSPI_Master_1_MISO_SHIFT);
        if (tmpPin == 1u)
        {
            tmpBuff |= MASK_LOW_BIT;
        }
        CyDelayCycles(DELAY_HIGH_STATE);
        
        SwSPI_Master_1_SCK_DR_REG &= ((uint8)(~SwSPI_Master_1_CLK));
        
        CyDelayCycles(DELAY_LOW_STATE);
        
        tmpBuff <<= SHIFT_ONE_BIT;
    }
    tmpBuff >>= SHIFT_ONE_BIT;
    
    SwSPI_Master_1_MOSI_DR_REG &= ((uint8)(~SwSPI_Master_1_MOSI));
    
    return (uint8_t)tmpBuff;
}

/*******************************************************************************
* Function Name: SwSPI_Master_1_RecvBuff
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


void SwSPI_Master_1_RecvBuff(uint8 *buff, uint16 cnt) 
{
    uint16_t tmpData;
    for (tmpData = 0; tmpData < cnt; tmpData ++)
    {
        buff[tmpData] = SwSPI_Master_1_RecvByte(); 
    }
}

/*******************************************************************************
* Function Name: SwSPI_Master_1_ReadAndWriteByte
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


uint8 SwSPI_Master_1_ReadAndWriteByte(uint8 byte)
{
    uint8 countBites;
    uint32_t tmpBuff = 0;
    uint8 tmpPin;
    for (countBites = BITES_ON_ONE_BYTE; countBites > 0; countBites--)
    {
    
        if (byte & MASK_HIGH_BIT)
        {
            SwSPI_Master_1_MOSI_DR_REG |= SwSPI_Master_1_MOSI;
        }
        else
        {
            SwSPI_Master_1_MOSI_DR_REG &= ((uint8)(~SwSPI_Master_1_MOSI));
        }
        
        SwSPI_Master_1_SCK_DR_REG |= SwSPI_Master_1_CLK;
        
        tmpPin = (uint8)((SwSPI_Master_1_MISO_PS_REG & SwSPI_Master_1_MISO_MASK) >> SwSPI_Master_1_MISO_SHIFT);
        if (tmpPin == 1u)
        {
            tmpBuff |= MASK_LOW_BIT;
        }
        
        CyDelayCycles(DELAY_HIGH_STATE);
        
         SwSPI_Master_1_SCK_DR_REG &= ((uint8)(~SwSPI_Master_1_CLK));
        byte <<=  SHIFT_ONE_BIT;
        tmpBuff <<= SHIFT_ONE_BIT;
        CyDelayCycles(DELAY_LOW_STATE);        
    }    
    tmpBuff >>= SHIFT_ONE_BIT;
        
    return (uint8_t)tmpBuff;
    
}    

/* [] END OF FILE */
