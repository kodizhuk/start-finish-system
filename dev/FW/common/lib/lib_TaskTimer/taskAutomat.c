#include <..\..\common\lib\lib_TaskTimer\taskAutomat.h>
#include "lib_Network\network.h"
#include "..\..\common\lib\lib_Display\display.h"
#include "..\..\common\lib\lib_Batt\batt.h"
#include "..\..\common\lib\lib_IDskier\IDskier.h"
#include "appGlobal.h"
#ifdef FINISH_MODULE
#include <SDinsert.h>
 #include <stdio.h>
#include "..\..\common\lib\lib_DB\logResult.h"
#include "..\..\common\lib\lib_BLE\bluetooth.h"
#include "..\..\common\lib\lib_DS1307\DS1307.h"
#endif

#define MAX_NUM_OF_TIMERS   5

#define WRITE_ERROR     1
#define WRITE_NO_ERROR  0
static uint16_t writeFlag;

uint8_t flag[MAX_NUM_OF_TIMERS];

volatile static struct
{
    uint8_t Number;
    uint16_t Time;
}SoftTimer[MAX_NUM_OF_TIMERS];

void Action1(void);
void Action2(void);
void Action3(void);
void Action4(void);
void Action5(void);

CY_ISR(TIMER_HANDLER)
{
    int i;
    for(i=0; i<MAX_NUM_OF_TIMERS; i++)
    {
        if(SoftTimer[i].Number == 255)continue;     /*if timer empty, next timer*/
        
        if(SoftTimer[i].Time > 0)
        {
            SoftTimer[i].Time --;
        }
        else
        {
            /*set flag*/
            flag[SoftTimer[i].Number] = 1;
            
            /*reset timer*/
            SoftTimer[i].Number = 255;
        }
    }
    isr_timer_ClearPending();
    Timer_ClearInterrupt(Timer_INTR_MASK_CC_MATCH);
}

/*******************************************************************************
* Function Name: TaskCheck
********************************************************************************
*
* Summary:
*   check flag machine
*
*******************************************************************************/
void TaskCheck(void)
{
    if(flag[ACTION1] == 1)Action1();
    if(flag[ACTION2] == 1)Action2();
    if(flag[ACTION3] == 1)Action3();
    if(flag[ACTION4] == 1)Action4();
    if(flag[ACTION5] == 1)Action5();
}

/*******************************************************************************
* Function Name: TaskTimerInit
********************************************************************************
*
* Summary:
*   init flag machine
*
*******************************************************************************/
void TaskTimerInit(void)
{
    int i;
    for(i=0; i<MAX_NUM_OF_TIMERS; i++)
        SoftTimer[i].Number = 255;
    
    isr_timer_StartEx(TIMER_HANDLER);
    Timer_Start();  
}

/*******************************************************************************
* Function Name: SetTaskTimer
********************************************************************************
*
* Summary:
*   set the time for the program timer
*
* Parameters:
*  newNumber - new number task
*  newTime - new time from task
*
*******************************************************************************/
void SetTaskTimer(uint8_t newNumber, uint16_t newTime)
{
    //CyGlobalIntDisable;
    int i;
    
    /*search existing timer*/
    for(i=0; i< MAX_NUM_OF_TIMERS; i++)
    {
        if(SoftTimer[i].Number == newNumber)
        {
            /*set new time*/
            SoftTimer[i].Time = newTime;
            
            //CyGlobalIntEnable;
            return;
        }
    }
    
    /*search new empty timer*/
    for(i=0; i< MAX_NUM_OF_TIMERS; i++)
    {
        if(SoftTimer[i].Number == 255)
        {
            SoftTimer[i].Number = newNumber;
            SoftTimer[i].Time = newTime;
            
            //CyGlobalIntEnable;
            return;
        }
    }
}


#ifdef START_MODULE
void Action1(void)
{
    flag[ACTION1] = 0;
    SendData();  
    SetTaskTimer(ACTION1,ACTION1_TIMEOUT);
}

void Action2(void)
{
    flag[ACTION2] = 0;
    DisplayRealTime();
    DisplayBattVoltage(ReadBattVoltage());
    
    ButtCheck();
    DisplayIDskier(ReadIdSkier());
    
    SetTaskTimer(ACTION2, ACTION2_TIMEOUT);
}

void Action3(void)
{
    flag[ACTION3] = 0;
    
    /*indicator network*/
    DisplayNetworkQuality(NetworkQuality());
//    if(NetworkStatus() == NETWORK_CONN)
//    {
//        DisplayIndicatorNetwork(CONNECT);
//    }
//    else
//    {
//        DisplayIndicatorNetwork(DISCONNECT);
//    }
    
    SetTaskTimer(ACTION3, ACTION3_TIMEOUT);
}

void Action4(void)
{
    flag[ACTION3] = 0; 
    //SetTaskTimer(ACTION4, ACTION4_TIMEOUT);
}

void Action5(void)
{    
    flag[ACTION3] = 0;
    //SetTaskTimer(ACTION4, ACTION5_TIMEOUT);
}
#endif
#ifdef FINISH_MODULE
void Action1(void)
{
    flag[ACTION1] = 0;
    
    /*write result skier on log 
    (if there is no memory card that is a record in fifo)*/    
    if((FifoGetSize() > 0) || (writeFlag == WRITE_ERROR))
    {
        uint32_t result;
        skierDB_El tmpStruct;
        static uint32_t lastFifoSize;
        static uint32_t tmpIDSkier;
        
        if (writeFlag == WRITE_NO_ERROR)
        {
            FifoGet(&tmpStruct);
            FifoPushLast(tmpStruct);
        }
        else
        {
            tmpStruct = FifoGetLast();
        }

        
        /*send finish skier result by buetooth*/
        if(writeFlag == WRITE_NO_ERROR )
        {
            /*SD only*/
            tmpIDSkier = GetIDskierFinished();
            BLE_sendOneSkierTimeResult(&tmpStruct,tmpIDSkier+1,SkierOnWay(),MAX_SKIERS_ON_WAY);
        }
        else
        {
            if(FifoGetSize() != lastFifoSize)
            {
                tmpIDSkier++;
                BLE_sendOneSkierTimeResult(&tmpStruct,tmpIDSkier+1,SkierOnWay(),MAX_SKIERS_ON_WAY);
                lastFifoSize = FifoGetSize();
            }
        }
        
        /*write data to SD card*/
        result = WriteSkierResult(&tmpStruct);
        if(result != FR_OK)
        {
            LogStart();
            writeFlag = WRITE_ERROR;          
        }
        else
        {
            writeFlag = WRITE_NO_ERROR; 
        }      
    }
    SetTaskTimer(ACTION1, ACTION1_TIMEOUT);
    
}

void Action2(void)
{   
    flag[ACTION2] = 0;
    SendData();  
    SetTaskTimer(ACTION2,ACTION2_TIMEOUT);
}

void Action3(void)
{
    flag[ACTION3] = 0;
    
    /*print indicator SD card*/
    if(SDinsert_Read() == 0)
    {
        DisplayIndicatorSD(SD_INSERT);
        BLE_sendSDcardStatus(STATUS_OK);
    }
    else
    {
        DisplayIndicatorSD(SD_NO_INSERT);
        BLE_sendSDcardStatus(STATUS_ERROR);
    }
    
    /*printindicator network*/
    DisplayNetworkQuality(NetworkQuality());
    if(NetworkStatus() == NETWORK_CONNECT)
    {
        //DisplayIndicatorNetwork(CONNECT);        
        BLE_sendNetworkStatus(STATUS_OK);
    }
    else
    {
        //DisplayIndicatorNetwork(DISCONNECT);
        BLE_sendNetworkStatus(STATUS_ERROR);
    }
    
    SetTaskTimer(ACTION3, ACTION3_TIMEOUT);
}

void Action4(void)
{
    flag[ACTION4] = 0;
    
    /*printf real time and num skier on way*/ 
    DisplayRealTime();
    DisplayNumSkierOnWay(SkierOnWay());   
    DisplayBattVoltage(ReadBattVoltage());
    
    SetTaskTimer(ACTION4, ACTION4_TIMEOUT);
}

void Action5(void)
{
    /*update time*/    
    
    static uint32_t oldUnixTime;
    uint32_t unixTime;
    
    flag[ACTION5] = 0;

    BLE_processEvents();
    
    unixTime = BLE_getUnixTime();
    if(oldUnixTime != unixTime)
    {
        /*atomic block*/
        uint32 interruptState;
        interruptState = CyEnterCriticalSection(); 
        
        /*set unix time in RTC DS1307*/
        DS1307_SetUnixTime(unixTime);
        RTC_SetUnixTime(unixTime);
        
        CyExitCriticalSection(interruptState);
        /*atomic block*/
        
        oldUnixTime = unixTime;
        
        SetRebootFlag();      
    }
    SetTaskTimer(ACTION5, ACTION5_TIMEOUT);
}
#endif

/* [] END OF FILE */
