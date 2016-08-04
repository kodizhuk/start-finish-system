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

static uint32_t gateOpen ;
//static uint64_t FinTime;
//static uint32_t FinMillis;

CY_ISR(GATE_INTERRUPT)
{
    
    if(SkierOnWay() > 0)
    {
        gateOpen = GATE_OPEN;    
        /*write skier result in buffer database*/
        WriteFinishTime(RTCGetUnixTime(),RTCgetRecentMs());
        /*off interrupt, on after seve time result*/
        GATE_INT_Disable();
    }
    
    GatePin_ClearInterrupt();
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
    return gateOpen;
}

void GateClose(void)
{
    gateOpen = GATE_CLOSE;
}

void AllowNextSkier(void)
{
    GATE_INT_Enable();
}
/* [] END OF FILE */