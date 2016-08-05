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
#include "lib_Gate\gate.h"



CY_ISR(GATE_INTERRUPT)
{   
    GATE_INT_Disable();
    
    gateOpen = GATE_OPEN;    

    savedUnixTime = RTCGetUnixTime();
    savedRecentMs = RTCgetRecentMs();
    
    GatePin_ClearInterrupt();
    GATE_INT_ClearPending();   
}


void GateInit(void)
{
    GatePin_ClearInterrupt();
    GATE_INT_ClearPending();
    GATE_INT_StartEx(GATE_INTERRUPT); 
    GATE_INT_Disable();
    
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
    
    result = gateOpen;
    gateOpen = GATE_CLOSE;
    
    return result;
}


void AllowNextSkier(void)
{
    gateOpen = GATE_CLOSE;
     
    GatePin_ClearInterrupt();
    GATE_INT_ClearPending();
    GATE_INT_Enable();   
}

void DisAllowNextSkier(void)
{
    gateOpen = GATE_CLOSE;
     
    GatePin_ClearInterrupt();
    GATE_INT_ClearPending();
    GATE_INT_Disable();   
}

void GetStartTime(uint64_t *unixTime,  uint32_t *recentMs)
{
    *unixTime = savedUnixTime;
    *recentMs = savedRecentMs;
}
/* [] END OF FILE */