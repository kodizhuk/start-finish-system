
#include "appGlobal.h"


int main()
{      
    while(SystemInit() == ERROR);
    BLE_start();
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
        MyDelay(TIMEOUT_DELAY);
    }
}


uint32_t SystemInit(void)
{
    uint32_t result;
    uint32_t unixTime;
        
    SetRebootFlag();
    LedInit();   
    DisplayStart();   
    RTC_WDT_Init(); 
    InitNetwork();
    GateInit();
    InitBuff();
    BattADC_Init(); //0.5% flash

    /* Enable global interrupts */
    CyGlobalIntEnable;
   
    /*sync real time*/
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
            Display("Please insert SD");
            result = ERROR;
            SendFinStatus(FIN_NO_READY);
        }
    }
    else
    {
        Display("Error sync time");
        result = ERROR;
        SendFinStatus(FIN_NO_READY);
    }
    
    return result;    
}

uint32_t TimeSynchronize(void)
{
    uint32_t result;
    
    LedBlink(FREQ_INIT_BLINK);
    
    /* network connect */
    if(NetworkStatus() == NETWORK_DISCONNECT)
    {
        Display("Network conn...");
        MyDelay(TIMEOUT_DELAY);
    }
    else
    {  
        /* time sync */
        Display("Sync time...");
        if(NTPsync() == TIME_SYNC_OK)
        {
            Display("Sync ok");
            ClearRebootFlag();
            BLE_sendSystemStatus(STATUS_OK);
            ResetTimerForTimeSync();
            
            MyDelay(4 * TIMEOUT_USER_READ_INFO);
            
            result = TIME_SYNC_OK;
        }
        else
        {
            Display("Sync time error");
            SetRebootFlag();
            BLE_sendSystemStatus(STATUS_ERROR);
            MyDelay(4 * TIMEOUT_USER_READ_INFO);
            
            result = TIME_SYNC_ERR;
        }
    }
    
    return result;
}


uint32_t CheckReady(void)
{
    uint32_t result;   
 
    /*sise FIFO*/
    if ((FifoGetSize() >= MAX_SKIERS_ON_BUF/*main_db_buffer) */)&& (FifoGetSize() <= MAX_FIFO_SIZE)/*reserv, max_fifo rec*/)
    {
        /*skier finish successful*/
        Display("Error SD Card!");
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
        Display("Error SD Card!");
        SendFinStatus(FIN_NO_READY); 
        
        result = ERROR;                
    }
    else if(SkierOnWay() >= MAX_SKIERS_ON_WAY/*MAX_COUNT, TRACK_OVERFLOW*/)
    {
        /*max skier on way*/
     
        Display("Max skier on way");
        SendFinStatus(FIN_NO_READY);
        MyDelay(TIMEOUT_USER_READ_INFO);
        
        result = NO_ERROR;      
    }
    else if(SkierOnWay() == 0)
    {
        Display("Finish Ready");
        SendFinStatus(FIN_READY);
        SetLedState(LED_DISABLE);        
        
        result = ERROR;      
    }
    else
    {
        /*finish ready*/
        SendFinStatus(FIN_READY);
        Display("Finish Ready");
        
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
        MyDelay(TIMEOUT_USER_READ_INFO);
    }
    else
    {
        AllowNextSkier();
    }
    
    return result;  
}

void SaveResult(void)
{
    uint64_t finUnixTime;
    uint32_t finRecentMs;
    
    SendFinStatus(FIN_READY);
    LedBlink(FREQ_INIT_BLINK);
    Display("Save data");
    MyDelay(TIMEOUT_USER_READ_INFO);
    
    /*write time in fifo*/
    GetFinTime(&finUnixTime, &finRecentMs);
    WriteFinishTime(finUnixTime,finRecentMs);
    
    FifoPushLastFinished();
    
    /*print time result last skier finished*/
    DisplayLastSkierTime(LastSecTimeOnWay(),LastMillsTimeOnWay());/*LastTimeOnWaySecs(), LastTimeOnWayMillis()*/
    MyDelay(2*TIMEOUT_USER_READ_INFO);
}

/* [] END OF FILE */
