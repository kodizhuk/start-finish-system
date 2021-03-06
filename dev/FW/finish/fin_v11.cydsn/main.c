
#include "appGlobal.h"

static uint8_t result;

int main()
{    
    SystemInit();
    while(InitRTC() == ERROR);

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
                    currentState = READY;
                }
                break;
            }
            case READY:
            {
                result = CheckReady();
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
                    currentState = READY;
                }
                break;
            }
            case SAVE_RESULT:
            {
                SaveResult();
                currentState = READY;
                break;
            }            
        }
        //CyDelay(100);
        TaskCheck();
    }
}

void SystemInit(void)
{
    DisplayStart(); 
    DisplaBacklightOn();
    LedInit(); 
    RTC_WDT_Init();
    InitNetwork();
    GateInit();
    InitBuff();
    BattADC_Init();
    
    BLE_start();
    
    TaskTimerInit();    
    SetTaskTimer(ACTION1, ACTION1_TIMEOUT); //network
    SetTaskTimer(ACTION2, ACTION2_TIMEOUT); //write result skier on log 
    SetTaskTimer(ACTION3, ACTION3_TIMEOUT); //display indicator
    SetTaskTimer(ACTION4, ACTION4_TIMEOUT);//printf real time and num skier on way
    SetTaskTimer(ACTION5, ACTION5_TIMEOUT); //ble
    
    CyGlobalIntEnable;
}

uint32_t InitRTC(void)
{
    uint32_t result;
    uint32_t unixTime;
        
    SetRebootFlag();
    /*sync real time*/
    //DS1307_SetUnixTime(1486482814);
    unixTime = DS1307_GetUnixTime();
    if(unixTime > 0)
    {      
        RTC_SetUnixTime(unixTime);
        
        result = DataBaseStart();
        if(result == DB_NO_ERROR)
        {
            Display("System init...");
            result = NO_ERROR;
        }
        else
        {
            Display(" Insert SD");
            result = ERROR;
            SendFinStatus(FIN_NO_READY);
            CyDelay(300);
        }
    }
    else
    {
        Display("Error sync");
        result = ERROR;
        SendFinStatus(FIN_NO_READY);
        CyDelay(500);
    }
    
    return result;    
}

uint32_t TimeSynchronize(void)
{
    uint32_t result = TIME_SYNC_ERR;
    
    LedBlink(FREQ_INIT_BLINK);
    
    /* network connect */
    if(NetworkStatus() == NETWORK_DISCONNECT)
    {
        Display("Connect...");
    }
    else
    {  
        /* time sync */
        Display("Sync time...");
        if(NTPsync() == TIME_SYNC_OK)
        {
            Display("  Sync ok");
            ClearRebootFlag();
            BLE_sendSystemStatus(STATUS_OK);
            ResetTimerForTimeSync();
            
            CyDelay(TIMEOUT_USER_READ_INFO);
            
            result = TIME_SYNC_OK;
        }
        else
        {
            Display("Sync error");
            SetRebootFlag();
            BLE_sendSystemStatus(STATUS_ERROR);
            CyDelay(TIMEOUT_USER_READ_INFO);
            
            result = TIME_SYNC_ERR;
        }
    }
    
    return result;
}


uint32_t CheckReady(void)
{
    uint32_t result;   
 
    /*sise FIFO*/
    if ((FifoGetSize() >= MAX_SKIERS_ON_BUF/*main_db_buffer) */)&&
    (FifoGetSize() <= MAX_FIFO_SIZE)/*reserv, max_fifo rec*/)
    {
        /*skier finish successful*/
        Display("Err SD Card!");
        SendFinStatus(FIN_NO_READY); 
        
        if (SkierOnWay() != 0)
        {
            /*if skiers on way*/
            result = NO_ERROR;
        }
        else
        {
            /*if not skiers on way*/
            result = ERROR;
        }        
    }
    else if(FifoGetSize() > MAX_FIFO_SIZE)
    {
        /*skier finish no successful*/
        Display("Err SD Card!");
        SendFinStatus(FIN_NO_READY); 
        
        result = ERROR;                
    }
    else if(SkierOnWay() >= MAX_SKIERS_ON_WAY/*MAX_COUNT, TRACK_OVERFLOW*/)
    {
        /*max skier on way*/
        Display(" Max skier");
        SendFinStatus(FIN_NO_READY);
        ////CyDelay(TIMEOUT_USER_READ_INFO);
        
        result = NO_ERROR;      
    }
    else if(SkierOnWay() == 0)
    {
        Display("   Ready");
        SendFinStatus(FIN_READY);
        SetLedState(LED_DISABLE);        
        
        result = ERROR;      
    }
    else
    {
        /*finish ready*/
        SendFinStatus(FIN_READY);
        Display("   Ready");
        
        result = NO_ERROR;
    }
    
    //if(ReadRebootStartFlag() == REBOOT/*IS*/)
    if(IsRebootStartFlag() == REBOOT)
    {
        result = REBOOT;
    }
    
    /*if  admin , read skier time from SD card and send bluetooth*/
    if(BLE_getFlagAdminOnly() != 0)
    {
        ReadSkierResultAndSendBLE();
    }
    
    if(ChekTimerForTimeSync() == SYNC_REQUIRES)
    {
        SetRebootFlag();
    }
   
    /*test mode on/off*/
    TestMode();
 
    return result;
}

uint32_t CheckGate(void)
{
    uint32_t result;
    
    SetLedState(LED_ENABLE);
    result = GateIsOpen();/*IsGateOpen(), CheckGateStatus()*/
    
    if(result == GATE_OPEN)
    {
        Display("Skier Finished");
        //CyDelay(TIMEOUT_USER_READ_INFO);
        //CyDelay(2000);
    }
    else
    {
        AllowNextSkier();
        AllowNextTestSkier();
    }
    
    return result;  
}

void SaveResult(void)
{
    uint64_t finUnixTime;
    uint32_t finRecentMs;
    uint8_t permissFin;
    
    LedBlink(FREQ_INIT_BLINK);
    Display(" Save data");
    ////CyDelay(TIMEOUT_USER_READ_INFO);
    
    /*write time in fifo*/
    GetFinTime(&finUnixTime, &finRecentMs);
    permissFin = GetPermissFin();
    WriteFinishTime(finUnixTime,finRecentMs, permissFin);
    
    /*print time result last skier finished*/
    DisplayLastSkierTime(LastSecTimeOnWay(),LastMillsTimeOnWay());/*LastTimeOnWaySecs(), LastTimeOnWayMillis()*/
    CyDelay(TIMEOUT_USER_READ_INFO);
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
