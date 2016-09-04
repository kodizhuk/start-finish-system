/* ========================================
 *
 * File Name: `$INSTANCE_NAME`.c
 * Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` 
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

#include "`$INSTANCE_NAME`_PVT.h"

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
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

void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil("`$INSTANCE_NAME`_Init")`
{
   `$INSTANCE_NAME`_OUTPORT_DR_REG |= `$INSTANCE_NAME`_CS;
   `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_CLK));
   `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_MOSI));
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ChipSelect
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

void `$INSTANCE_NAME`_ChipSelect(void) `=ReentrantKeil("`$INSTANCE_NAME`_ChipSelect")`
{
    `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_CS));
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ChipDeselect
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

void `$INSTANCE_NAME`_ChipDeselect(void) `=ReentrantKeil("`$INSTANCE_NAME`_ChipDeselect")`
{
    `$INSTANCE_NAME`_OUTPORT_DR_REG |= `$INSTANCE_NAME`_CS;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SendByte
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
        `$INSTANCE_NAME`_OUTPORT_DR_REG |= `$INSTANCE_NAME`_CLK;
        
        CyDelayCycles(DELAY_HIGH_STATE);
        
        `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_CLK));
        CyDelayCycles(DELAY_LOW_STATE);      
        byte <<=  SHIFT_ONE_BIT;
    }
    
    `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_MOSI));    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SendBuff
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

void `$INSTANCE_NAME`_SendBuff(const uint8 buff[], uint16 cnt) `=ReentrantKeil("`$INSTANCE_NAME`_SendBuff")`
{
    uint16_t tmpData;
    for (tmpData = 0; tmpData < cnt; tmpData ++)
    {
        `$INSTANCE_NAME`_SendByte(buff[tmpData]);
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RecvByte
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

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RecvBuff
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


void `$INSTANCE_NAME`_RecvBuff(uint8 *buff, uint16 cnt) `=ReentrantKeil("`$INSTANCE_NAME`_RecvBuff")`
{
    uint16_t tmpData;
    for (tmpData = 0; tmpData < cnt; tmpData ++)
    {
        buff[tmpData] = `$INSTANCE_NAME`_RecvByte(); 
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadAndWriteByte
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


uint8 `$INSTANCE_NAME`_ReadAndWriteByte(uint8 byte)
{
    uint8 countBites;
    uint32_t tmpBuff = 0;
    uint8 tmpPin;
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
        
        `$INSTANCE_NAME`_OUTPORT_DR_REG |= `$INSTANCE_NAME`_CLK;
        
        tmpPin = (uint8)((`$INSTANCE_NAME`_INPORT_PS_REG & `$INSTANCE_NAME`_MISO_MASK) >> `$INSTANCE_NAME`_MISO_SHIFT);
        if (tmpPin == 1u)
        {
            tmpBuff |= MASK_LOW_BIT;
        }
        
        CyDelayCycles(DELAY_HIGH_STATE);
        
         `$INSTANCE_NAME`_OUTPORT_DR_REG &= ((uint8)(~`$INSTANCE_NAME`_CLK));
        byte <<=  SHIFT_ONE_BIT;
        tmpBuff <<= SHIFT_ONE_BIT;
        CyDelayCycles(DELAY_LOW_STATE);        
    }    
    tmpBuff >>= SHIFT_ONE_BIT;
        
    return (uint8_t)tmpBuff;
    
}    

/* [] END OF FILE */
