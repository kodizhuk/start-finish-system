#include "..\..\common\lib\lib_Gate\gate.h"
#include <GatePin.h>
#include <GATE_INT.h>
#include "..\..\common\lib\lib_RTC\RTC_WDT.h"
#ifdef START_MODULE
    #include "..\..\common\lib\lib_IDskier\IDskier.h"
#endif
#ifdef FINISH_MODULE
    #include "SW_GateEnable.h"
#endif
#include "appGlobal.h"

static uint8_t savedIdSkier;
static uint64_t savedUnixTime;
static uint32_t savedRecentMs;
static uint8_t savedFinPermiss;
static uint32_t gateOpen ;


/*gate interrupt*/
CY_ISR(GATE_INTERRUPT)
{   
    GATE_INT_Disable();
    
    gateOpen = GATE_OPEN;    

    savedUnixTime = RTCGetUnixTime();
    savedRecentMs = RTCgetRecentMs();
    
    #ifdef FINISH_MODULE
    savedFinPermiss = SW_GateEnable_Read();
    #endif
    
    #ifdef START_MODULE
    savedIdSkier = ReadIdSkier();
    #endif
    
    //GatePin_ClearInterrupt();
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
    //GatePin_ClearInterrupt();
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
    //GatePin_ClearInterrupt();
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
#ifdef START_MODULE
void GetStartTime(uint8_t *idSkier,uint64_t *unixTime,  uint32_t *recentMs)
{
    *idSkier = savedIdSkier;
    *unixTime = savedUnixTime;
    *recentMs = savedRecentMs;
}
#endif
#ifdef FINISH_MODULE
void GetFinTime(uint64_t *unixTime,  uint32_t *recentMs)
{
    *unixTime = savedUnixTime;
    *recentMs = savedRecentMs;
}

uint8_t GetPermissFin(void)
{
    return savedFinPermiss;
}
#endif
/* [] END OF FILE */