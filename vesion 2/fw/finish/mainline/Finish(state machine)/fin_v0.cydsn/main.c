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
#include "lib_DS1307\DS1307.h"
#include "lib_LED\LED.h"
#include "lib_Display\display.h"
#include "lib_Network\network.h"
#include "lib_Gate\gate.h"
#include "lib_Fat\ff.h"
#include "lib_DB\database.h"

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    typedef enum {SYSTEM_INIT = 0, READY, CHECK_GATE, SAVE_RESULT, REINIT_DB} StateType; 
    StateType currentState;
    
    currentState = SYSTEM_INIT;
    uint32_t result;
    

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
                }else
                {
                    currentState = REINIT_DB;
                }
                break;
            }
            case REINIT_DB:
            {
                result = ReinitDB();
                if(result == NO_ERROR)
                {
                    currentState = SAVE_RESULT;
                }else
                {
                    currentState = SYSTEM_INIT;
                }
                break;
            }            
        }
        AppDelay(TIMEOUT_STATE);
        #ifdef DEBUG_PC
            char buff[100];
            uint32_t time;
            time = RTC_GetTime();
            sprintf(buff, "%02lu:%02lu:%02lu        ", RTC_GetHours(time),RTC_GetMinutes(time), RTC_GetSecond(time));
            LCD_Position(1,0);
            LCD_PrintString(buff);
        #endif
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
    InitBuff();
    
    //DS1307_SetUnixTime(1470415687);
    unixTime = DS1307_GetUnixTime();
    
    if(unixTime > 0)
    {
        RTC_SetUnixTime(unixTime);
        result = DataBaseStart();
        if(result == FR_OK)
        {
            result = NO_ERROR;
        }else
        {
            result = ERROR;
            SendFinStatus(FIN_NO_READY);
        }
    }else
    {
        result = ERROR;
        SendFinStatus(FIN_NO_READY);
    }
    
    return result;
    
}

uint32_t Ready(void)
{
    uint32_t result;   
    
    if(NetworkStatus() == NETWORK_DISCONN)
    {
        DisplayPrintf("No connect");
        LedBlink(FREQ_ERR_BLINK);
        SendFinStatus(FIN_NO_READY);
        
        result = ERROR;
    }else if(SkierOnWay() >= MAX_SKIERS_ON_WAY)
    {
        DisplayPrintf("Max skier on way");
        SendFinStatus(FIN_NO_READY);
        AppDelay(TIMEOUT_USER_READ_INFO);
        
        result = NO_ERROR;      
    }else if(SkierOnWay() == 0)
    {
        DisplayPrintf("No skier on way");
        AppDelay(TIMEOUT_USER_READ_INFO);
        SendFinStatus(FIN_READY);
        
        result = ERROR;      
    }else 
    {
        SendFinStatus(FIN_READY);
        
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
        AppDelay(TIMEOUT_USER_READ_INFO);
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
    AppDelay(TIMEOUT_USER_READ_INFO);
    
    /*write log in SD*/
    GetFinTime(&finUnixTime, &finRecentMs);
    WriteFinishTime(finUnixTime,finRecentMs);
    result = WriteSkierResult(&skierDB[skiersFinished-1]);
    
    if(result == FR_OK)
    {
        result = NO_ERROR;
        
        /*printf result last skier*/
        char _tmpBuff[20];
        sprintf(_tmpBuff, "Result %02u:%02u:%03u",LastSecTimeOnWay()/60,LastSecTimeOnWay()%60, LastMillsTimeOnWay());
        DisplayPrintf(_tmpBuff);
        AppDelay(3*TIMEOUT_USER_READ_INFO);
    }else
    {
        DisplayPrintf("Error save data");
        AppDelay(TIMEOUT_USER_READ_INFO);
        result = ERROR;
    }
    
    return result;
    
}
uint32_t ReinitDB(void)
{
    uint32_t result;
    
    result = logStart();
    if(result == FR_OK)
    {
        DisplayPrintf("Save data OK!");
        AppDelay(TIMEOUT_USER_READ_INFO);
        result = NO_ERROR;
    }else
    {
        result = ERROR;
    }
    
    return result;
}
/* [] END OF FILE */
