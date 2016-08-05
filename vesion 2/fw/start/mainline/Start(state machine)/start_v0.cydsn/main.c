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
#include <project.h>
#include "appGlobal.h"
/*user lib*/
#include "lib_RTC\RTC_WDT.h"
#include "lib_LED\LED.h"
#include "lib_Display\display.h"
#include "lib_Network\network.h"
#include "lib_Gate\gate.h"

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    typedef enum {SYSTEM_INIT = 0, GET_FIN_STATUS, CHECK_GATE, SAVE_RESULT} StateType; 
    StateType currentState;
    
    currentState = SYSTEM_INIT;
    uint32_t result;
    uint32_t CyclesCheckConn;
    for(;;)
    {
        switch (currentState)
        {
            case SYSTEM_INIT:
            {
                result = SystemInit();
                if(result == NO_ERROR)
                {
                    currentState = GET_FIN_STATUS;
                }
                break;
            }
            case GET_FIN_STATUS:
            {
                result = GetFinishStatus();

                if(result == NO_ERROR)
                {
                    currentState = CHECK_GATE;                   
                }
                break;
            }
            case CHECK_GATE:
            {
                result = CheckGate();
                if(result == GATE_OPEN)
                {
                    currentState = SAVE_RESULT;
                }else
                {
                    currentState = GET_FIN_STATUS;
                }
                break;
            }
            case SAVE_RESULT:
            {
                result = SaveResult();
                currentState = GET_FIN_STATUS;
    
                break;
            }           
        }
        AppDelay(TIMEOUT_STATE);
    }
}

uint32_t SystemInit(void)
{
    uint32_t result;
    uint64_t unixTime;
    
    LedInit();
    LedBlink(FREQ_INIT_BLINK);
    
    DisplayConfig();
    DisplayPrintf("System init...");
    
    RTC_WDT_Init(); 
    InitNetwork();
    GateInit();

    result = NO_ERROR;
    return result;
    
}

uint32_t GetFinishStatus(void)
{
    uint32_t result;
    
    if (NetworkStatus() == NETWORK_DISCONN || FinWriteInDB() == ERROR || FinReady() == NO_READY)
    {
        LedBlink(FREQ_ERR_BLINK);
        result = ERROR;
        DisplayPrintf("Fin no ready");
        DisAllowNextSkier();
        AppDelay(TIMEOUT_USER_READ_INFO);
    }
    else
    {
        result = NO_ERROR;
    }
          
    return result;
    
}

uint32_t CheckGate(void)
{
    uint32_t result;
    
    result = GateIsOpen();
    
    if(result == GATE_OPEN)
    {
        DisplayPrintf("Skier Started");
        LedBlink(FREQ_INIT_BLINK);
        AppDelay(TIMEOUT_USER_READ_INFO);

    }else
    {
        DisplayPrintf("Start ready");
        SetLedState(LED_ENABLE);
        AllowNextSkier();

    }
    return result;
    
}

uint32_t SaveResult(void)
{
    uint32_t result;
    uint64_t startUnixTime;
    uint32_t startRecentMs;
    
    LedBlink(FREQ_INIT_BLINK);
    DisplayPrintf("Save result");
    AppDelay(TIMEOUT_USER_READ_INFO);
    
    GetStartTime(&startUnixTime, &startRecentMs);
    SendSkierStart(startUnixTime, startRecentMs);
    
    DisplayPrintf("Please wait");
    AppDelay(TIMEOUT_NEXT_SKIER);
    
    result = NO_ERROR;
    
    return result;
    
}

/* [] END OF FILE */
