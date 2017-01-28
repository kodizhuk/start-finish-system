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
        MyDelay(TIMEOUT_STATE);
    }
}

void  SystemInit(void)
{   
    SetRebootFlag();
    LedInit();
    LedBlink(FREQ_INIT_BLINK);
    
    DisplayStart();
    Display("System init...");
    
    RTC_WDT_Init(); 
    InitNetwork();
    GateInit();
    BattADC_Init();
    
    /* Enable global interrupts. */ 
    CyGlobalIntEnable; 
    
}

uint32_t TimeSynchronize(void)
{
    uint32_t result;
    
    LedBlink(FREQ_INIT_BLINK);
    
    /*network connect*/
    if(NetworkStatus() == NETWORK_DISCONN)
    {
        Display("Network conn...");
        MyDelay(TIMEOUT_STATE);
    }
    else
    {
        /*time sync*/
        Display("Sync time...");
        
        if(NTPsync() == TIME_SYNC_OK)
        {
            Display("Sync ok");
            ClearRebootFlag();
            MyDelay(4*TIMEOUT_USER_READ_INFO);
            
            result = TIME_SYNC_OK;
        }
        else
        {
            Display("Sync time error");
            SetRebootFlag();
            MyDelay(TIMEOUT_USER_READ_INFO);
      
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
        LedBlink(FREQ_ERR_BLINK);
        result = ERROR;
        Display("Fin no ready");
        DisAllowNextSkier();
        MyDelay(TIMEOUT_USER_READ_INFO);
    }
    else
    {
        result = NO_ERROR;
    }
    
    if(IsRebootFinishFlag() == REBOOT)
    {
        result = REBOOT;    
    }
         
    return result;
    
}

uint32_t CheckGate(void)
{
    uint32_t result;
    
    result = GateIsOpen();
    
    if(result == GATE_OPEN)
    {
        Display("Skier Started");
        LedBlink(FREQ_INIT_BLINK);
        MyDelay(TIMEOUT_USER_READ_INFO);

    }
    else
    {
        Display("Start ready");
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
    Display("Save result");
    MyDelay(TIMEOUT_USER_READ_INFO);
    
    GetStartTime(&startUnixTime, &startRecentMs);
    SendSkierStart(startUnixTime, startRecentMs);
    
    Display("Wait next skier");
    MyDelay(TIMEOUT_NEXT_SKIER);
    
    result = NO_ERROR;
    
    return result;
    
}

/* [] END OF FILE */
