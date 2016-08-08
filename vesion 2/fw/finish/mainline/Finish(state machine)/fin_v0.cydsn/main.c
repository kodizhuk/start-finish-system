
#include "appGlobal.h"


int main()
{
    /* Enable global interrupts */
    CyGlobalIntEnable; 
    
    currentState = SYSTEM_INIT;
    
    /*set unix time in RTC DS1307*/
    //DS1307_SetUnixTime(1470503047);
    
    for(;;)
    {
        switch (currentState)
        {
            case SYSTEM_INIT:
            {
                result = SystemInit();
                if(result == NO_ERROR)
                {
                    currentState = READY;
                }
                break;
            }
            case READY:
            {
                result = Ready();

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
                    currentState = READY;
                }
                break;
            }
            case SAVE_RESULT:
            {
                result = SaveResult();
                if(result == NO_ERROR)
                {
                    currentState = READY;
                }
                break;
            }            
        }
        MyDelay(TIMEOUT_STATE);
    }
}

uint32_t SystemInit(void)
{
    uint32_t result;
    uint64_t unixTime;
    
    LedInit();   
    DisplayConfig();   
    RTC_WDT_Init(); 
    InitNetwork();
    GateInit();
    InitBuff();
    
    /*sync real time*/
    unixTime = DS1307_GetUnixTime();
    
    if(unixTime > 0)
    {      
        RTC_SetUnixTime(unixTime);
        result = DataBaseStart();
        
        if(result == DB_START)
        {
            DisplayPrintf("System init...");
            result = NO_ERROR;
        }else
        {
            DisplayPrintf("Please insert SD");
            result = ERROR;
            SendFinStatus(FIN_NO_READY);
        }
    }else
    {
        DisplayPrintf("Error sync time");
        result = ERROR;
        SendFinStatus(FIN_NO_READY);
    }
    return result;
    
}

uint32_t Ready(void)
{
    uint32_t result;   
 
    /*sise FIFO*/
    if ((FifoGetSize() >= MAX_SKIERS_ON_BUF) && (FifoGetSize() <= MAX_FIFO_SIZE))
    {
        /*skier finish successful*/
        DisplayPrintf("Error SD Card!");
        SendFinStatus(FIN_NO_READY); 
        
        if (SkierOnWay() == 0)
        {
            /*if not skiers on way*/
            result = ERROR;
        }
        else
        {
            /*if skiers on way*/
            result = NO_ERROR;
        }        
    }
    else if(FifoGetSize() >= MAX_FIFO_SIZE)
    {
        /*skier finish no successful*/
        DisplayPrintf("Error SD Card!");
        SendFinStatus(FIN_NO_READY);        
        result = ERROR;                
    }else if(SkierOnWay() >= MAX_SKIERS_ON_WAY)
    {
        /*max skier on way*/
        
        DisplayPrintf("Max skier on way");
        SendFinStatus(FIN_NO_READY);
        MyDelay(TIMEOUT_USER_READ_INFO);
        
        result = NO_ERROR;      
    }else if(SkierOnWay() == 0)
    {
        /*no skier on way*/
        DisplayPrintf("Finish Ready");
        //MyDelay(TIMEOUT_USER_READ_INFO);
        SendFinStatus(FIN_READY);
        SetLedState(LED_ENABLE);
        
        result = ERROR;      
    }else
    {
        /*finish ready*/
        SendFinStatus(FIN_READY);
        DisplayPrintf("Finish Ready");
        
        result = NO_ERROR;
    }
       
    return result;
}

uint32_t CheckGate(void)
{
    uint32_t result;
    
    SetLedState(LED_ENABLE);
    result = GateIsOpen();
    
    if(result == GATE_OPEN)
    {
        DisplayPrintf("Skier Finished");
        MyDelay(TIMEOUT_USER_READ_INFO);
    }else
    {
        AllowNextSkier();
    }
    return result;
    
}

uint32_t SaveResult(void)
{
    uint64_t finUnixTime;
    uint32_t finRecentMs;
    
    SendFinStatus(FIN_READY);
    LedBlink(FREQ_INIT_BLINK);
    DisplayPrintf("Save data");
    MyDelay(TIMEOUT_USER_READ_INFO);
    
    /*write time in fifo*/
    GetFinTime(&finUnixTime, &finRecentMs);
    WriteFinishTime(finUnixTime,finRecentMs);
    FifoPush(skierDB[skiersFinished-1]);
    
    /*print time result last skier finished*/
    DisplayPrintLastTimeSkier(LastSecTimeOnWay(),LastMillsTimeOnWay());
    MyDelay(2*TIMEOUT_USER_READ_INFO);
    
    
    return NO_ERROR;   
}

/* [] END OF FILE */
