
#include "lib_Gate\gate.h"

/*gate interrupt*/
CY_ISR(GATE_INTERRUPT)
{   
    GATE_INT_Disable();
    
    gateOpen = GATE_OPEN;    

    savedUnixTime = RTCGetUnixTime();
    savedRecentMs = RTCgetRecentMs();
    
    GatePin_ClearInterrupt();
    GATE_INT_ClearPending();   
}

/*******************************************************************************
* Function Name: GateInit
********************************************************************************
*
* Summary:
*   inittilisation the gate pin
*   disable interrupt from gate
*
*******************************************************************************/
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
* Summary:
*  verification or gate closed
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


/*******************************************************************************
* Function Name: AllowNextSkier
********************************************************************************
*
* Summary:
*   allow the new skier on way(enable gate interrupt)
*
*******************************************************************************/
void AllowNextSkier(void)
{
    GatePin_ClearInterrupt();
    GATE_INT_ClearPending();
    GATE_INT_Enable();
}


/*******************************************************************************
* Function Name: GetFinTime
********************************************************************************
*
* Summary:
*   reading recorded in the interruption time finish skier
* Parametrs:
*   *unixTime - pointer from unix time skier
*   *recentMs - pointer from miliseconds time
*
*******************************************************************************/
void GetFinTime(uint64_t *unixTime,  uint32_t *recentMs)
{
    *unixTime = savedUnixTime;
    *recentMs = savedRecentMs;
}
/* [] END OF FILE */