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
        DisplayPrintfRealTime();
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
    
    /*if(NetworkStatus() == NETWORK_DISCONN)
    {
        DisplayPrintf("No connect");
        LedBlink(FREQ_ERR_BLINK);
        SendFinStatus(FIN_NO_READY);
        
        result = ERROR;
    }else*/ if(SkierOnWay() >= MAX_SKIERS_ON_WAY)
    {
        DisplayPrintf("Max skier on way");
        SendFinStatus(FIN_NO_READY);
        MyDelay(TIMEOUT_USER_READ_INFO);
        
        result = NO_ERROR;      
    }else if(SkierOnWay() == 0)
    {
        DisplayPrintf("No skier on way");
        MyDelay(TIMEOUT_USER_READ_INFO);
        SendFinStatus(FIN_READY);
        SetLedState(LED_ENABLE);
        
        result = ERROR;      
    }
    else
    {
        SendFinStatus(FIN_READY);
        
        result = NO_ERROR;
    }
    
    if ((FifoGetSize() >= MAX_SKIERS_ON_BUF) && (FifoGetSize() <= MAX_FIFO_SIZE))
    {
        /*skier finish successful*/
        DisplayPrintf("Error SD Card!");
        SendFinStatus(FIN_NO_READY);        
        if (SkierOnWay() == 0)
        {
            result = ERROR;
        }
        else
        {
            result = NO_ERROR;
        }        
    }
    else if(FifoGetSize() >= MAX_FIFO_SIZE)
    {
        /*skier finish no successful*/
        DisplayPrintf("Error SD Card!");
        SendFinStatus(FIN_NO_READY);        
        result = ERROR;                
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
        char _tmpBuff[20];
        sprintf(_tmpBuff, "%d skiers on Way", SkierOnWay());
        DisplayPrintf(_tmpBuff);
        AllowNextSkier();
    }
    return result;
    
}

uint32_t SaveResult(void)
{
    uint32_t result;
    uint64_t finUnixTime;
    uint32_t finRecentMs;
    
    SendFinStatus(FIN_NO_READY);
    LedBlink(FREQ_INIT_BLINK);
    DisplayPrintf("Save data");
    MyDelay(TIMEOUT_USER_READ_INFO);
    
    /*write time in fifo*/
    GetFinTime(&finUnixTime, &finRecentMs);
    WriteFinishTime(finUnixTime,finRecentMs);
    FifoPush(skierDB[skiersFinished-1]);
     
    /*app delay*/
    //result = WriteSkierResult(&skierDB[skiersFinished-1]);
    
    /*
    if(result == FR_OK)
    {
        result = NO_ERROR;
        reinitDB = NO_ERROR;
        
        /*printf result last skier*/
    /*
        char _tmpBuff[20];
        sprintf(_tmpBuff, "Result %02u:%02u:%03u",LastSecTimeOnWay()/60,LastSecTimeOnWay()%60, LastMillsTimeOnWay());
        DisplayPrintf(_tmpBuff);
        MyDelay(3*TIMEOUT_USER_READ_INFO);
    }else
    {
        DisplayPrintf("Error save data");
        MyDelay(TIMEOUT_USER_READ_INFO);
        reinitDB = ERROR;
        
        result = ERROR;
    }
    
    */
    result = NO_ERROR;
    
    return result;
    
}
/*
uint32_t ReinitDB(void)
{
    uint32_t result;
    
    result = logStart();
    if(result == FR_OK)
    {
        DisplayPrintf("Save data OK!");
        MyDelay(TIMEOUT_USER_READ_INFO);
        result = NO_ERROR;
    }else
    {
        
        result = ERROR;
    }
    
    return result;
}
*/
/* [] END OF FILE */
