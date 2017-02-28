#include <lib_TaskTimer\taskAutomat.h>
#include "lib_Network\network.h"
#include "lib_Display\display.h"
#include "lib_Batt\batt.h"

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
    for(i=0; i!=MAX_NUM_OF_TIMERS; i++)
    {
        if(SoftTimer[i].Number == 255)continue;     /*if timer empty, next timer*/
        
        if(SoftTimer[i].Time != 0)
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
    for(i=0; i!= MAX_NUM_OF_TIMERS; i++)
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
    for(i=0; i!= MAX_NUM_OF_TIMERS; i++)
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
    SetTaskTimer(ACTION2, ACTION2_TIMEOUT);
}

void Action3(void)
{
    flag[ACTION3] = 0;
    
    /*indicator network*/
    if(NetworkStatus() == NETWORK_CONN)
    {
        DisplayIndicatorNetwork(CONNECT);
    }
    else
    {
        DisplayIndicatorNetwork(DISCONNECT);
    }
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


/* [] END OF FILE */
