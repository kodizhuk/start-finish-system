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
#include "gate.h"

static uint8_t gateOpen;

CY_ISR(GATE_INTERRUPT)
{
    if(gateOpen == GATE_CLOSE)
    {
        gateOpen = GATE_OPEN;
        /*write skier result in buffer database*/
        //SendSkierSrart(RTCGetUnixTime(),RTCgetRecentMs());
    }
    GATE_INT_ClearPending();
}

void GateInit(void)
{
    GATE_INT_StartEx(GATE_INTERRUPT); 
    gateOpen = GATE_CLOSE;
}


/*******************************************************************************
* Function Name: GateOpen
********************************************************************************
*
* * verification or gate closed
*
* Return:
*  GATE_CLOSE or GATE_OPEN
*******************************************************************************/
uint32_t GateIsOpen(void)
{
    uint32_t result;
    
    if(gateOpen == GATE_OPEN)
    {
        result = GATE_OPEN;
        gateOpen = GATE_CLOSE;
    }else
    {
        result = GATE_CLOSE;
    }
    
    return result;
}
/* [] END OF FILE */