#include "appGlobal.h"

int main()
{
    SystemInit();
    currentState = TIME_SYNC;

    for(;;)
    {
        switch (currentState)
        {
            case TIME_SYNC:
            {
                result = TimeSynchronize();
                if(result == TIME_SYNC_OK)
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
                else if(result == REBOOT)  
                {
                    currentState = TIME_SYNC;
                }
                break;
            }
            case CHECK_GATE:
            {
                result = CheckGate();
                if(result == GATE_OPEN)
                {
                    currentState = SAVE_RESULT;
                }
                else
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
        //CyDelay(TIMEOUT_STATE);
        TaskCheck();
    }
}

void  SystemInit(void)
{   
    SetRebootFlag();
    LedInit();
    SetLedsState(LED_ENABLE, LED_DISABLE);
    
    DisplayStart();
    Display("System init...");
    DisplaBacklightOn();
    
    RTC_WDT_Init();
    InitNetwork();
    GateInit();
    BattADC_Init();
    ButtInit();
    
    TaskTimerInit();    
    SetTaskTimer(ACTION1, ACTION1_TIMEOUT); //network
    SetTaskTimer(ACTION2, ACTION2_TIMEOUT); //display real time
    SetTaskTimer(ACTION3, ACTION3_TIMEOUT); //display indicator
    
    /* Enable global interrupts. */ 
    CyGlobalIntEnable; 
    
}

uint32_t TimeSynchronize(void)
{
    uint32_t result;
    
    SetLedsState(LED_ENABLE, LED_DISABLE);
    
    /*network connect*/
    if(NetworkStatus() == NETWORK_DISCONN)
    {
        Display("Connect...");
        Delay(TIMEOUT_STATE);
    }
    else
    {
        /*time sync*/
        Display("Sync time...");
        
        if(NTPsync() == TIME_SYNC_OK)
        {
            Display("  Sync ok");
            ClearRebootFlag();
            Delay(TIMEOUT_USER_READ_INFO);
            
            result = TIME_SYNC_OK;
        }
        else
        {
            Display("Sync error");
            SetRebootFlag();
            Delay(TIMEOUT_USER_READ_INFO);
      
            result = TIME_SYNC_ERR;
        }
    }
    
    return result;
}

uint32_t GetFinishStatus(void)
{
    uint32_t result;
    
    if (NetworkStatus() == NETWORK_DISCONN || FinWriteInDB() == NO_WRITE || FinReady() == NO_READY)
    {
        //LedRedBlink(FREQ_ERR_BLINK);
        SetLedsState(LED_ENABLE, LED_DISABLE);
        Display(" No ready");
        DisAllowNextSkier();
        Delay(TIMEOUT_USER_READ_INFO);
        result = ERROR;
    }
    else
    {
        result = NO_ERROR;
    }
    
    if(IsRebootFinishFlag() == REBOOT)
    {
        result = REBOOT;    
    }
    
    TestMode();
    
    return result;
    
}

uint32_t CheckGate(void)
{
    uint32_t result;
    
    result = GateIsOpen();
    
    if(result == GATE_OPEN)
    {
        DisAllowNextSkier();
        Display("Skier Started");
        SetLedsState(LED_ENABLE, LED_DISABLE);
        Delay(TIMEOUT_USER_READ_INFO);
    }
    else
    {
        Display("Start ready");
        SetLedsState(LED_DISABLE, LED_ENABLE);
        AllowNextSkier();
    }

    return result;
    
}

uint32_t SaveResult(void)
{
    uint32_t result;
    uint64_t startUnixTime;
    uint32_t startRecentMs;
    
    //LedRedBlink(FREQ_INIT_BLINK);
    SetLedsState(LED_ENABLE, LED_DISABLE);
    
    Display("Save result");
    
    GetStartTime(&startUnixTime, &startRecentMs);
    SendSkierStart(startUnixTime, startRecentMs);
    Delay(TIMEOUT_USER_READ_INFO);
    
    Display("Next skier");
    Delay(TIMEOUT_NEXT_SKIER);
    
    result = NO_ERROR;
    
    return result;
    
}

void Delay(uint32_t delayMs)
{
    while(delayMs --)
    {
        CyDelay(1);
        TaskCheck();
    }
}

/* [] END OF FILE */
