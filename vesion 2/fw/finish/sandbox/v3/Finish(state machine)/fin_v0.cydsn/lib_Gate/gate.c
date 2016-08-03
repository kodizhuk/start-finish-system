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
    gateOpen = GATE_OPEN;
    
    /*write skier result in buffer database*/
    WriteFinishTime(RTCGetUnixTime(),RTCgetRecentMs());
    
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
    return gateOpen;;
}

void GateClose(void)
{
    gateOpen = GATE_CLOSE;
}
/* [] END OF FILE */