#include "appGlobal.h"

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    currentState = SYSTEM_INIT;

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
        MyDelay(TIMEOUT_STATE);
    }
}

uint32_t SystemInit(void)
{   
    LedInit();
    LedBlink(FREQ_INIT_BLINK);
    
    DisplayConfig();
    DisplayPrintf("System init...");
    
    RTC_WDT_Init(); 
    InitNetwork();
    GateInit();

    for(;;)
    {
        
        result = NTPsync();
        if(result == TIME_SYNC_OK)
        {
            DisplayPrintf("RTC sync ok");
            //DisplayPrintfRealTime();
            CyDelay(100);
            for(;;) DisplayPrintfRealTime();
        }else
        {
            DisplayPrintf("REC sync error");
        }
        DisplayPrintfRealTime();
    }
    return NO_ERROR;  
}

uint32_t GetFinishStatus(void)
{
    uint32_t result;
    
    if (NetworkStatus() == NETWORK_DISCONN || FinWriteInDB() == NO_WRITE || FinReady() == NO_READY)
    {
        LedBlink(FREQ_ERR_BLINK);
        result = ERROR;
        DisplayPrintf("Fin no ready");
        DisAllowNextSkier();
        MyDelay(TIMEOUT_USER_READ_INFO);
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
        MyDelay(TIMEOUT_USER_READ_INFO);

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
    MyDelay(TIMEOUT_USER_READ_INFO);
    
    GetStartTime(&startUnixTime, &startRecentMs);
    SendSkierStart(startUnixTime, startRecentMs);
    
    DisplayPrintf("Wait next skier");
    MyDelay(TIMEOUT_NEXT_SKIER);
    
    result = NO_ERROR;
    
    return result;
    
}

/* [] END OF FILE */
