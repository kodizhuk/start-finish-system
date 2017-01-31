#include "project.h"
#include <stdlib.h>

#include <stdio.h>
#include <lib_Display\Display.h>
#include <lib_Network\network.h>
#include <lib_Testmode\testMode.h>

#define COUNTER_TEST_MODE_ON   5
#define COUNTER_TEST_MODE_OFF  7
#define MAX_DELAY_CYCLES_IN_READING 2

enum status {STOPPED=0, RUN};
typedef enum {HIGH_LEVEL, RISING_EDGE, FALLING_EDGE, LOW_LEVEL}funcReturnValue;

uint8_t statusTestMode = STOPPED;

funcReturnValue switchState = LOW_LEVEL;
funcReturnValue networkState = LOW_LEVEL;

funcReturnValue ReadSwitchState();
funcReturnValue ReadNetworkState();

static uint8_t enableTestMode;

CY_ISR(testModeHandler)
{
    Pin_testMode_Write(0);
    Pin_testMode_Write(1);
    
    TimerTestMode_ClearInterrupt(TimerTestMode_INTR_MASK_CC_MATCH);
    statusTestMode = STOPPED;
}


void newFuncTestMode()
{   
    ReadSwitchState();
    ReadNetworkState();
    
    if(switchState == RISING_EDGE || networkState == RISING_EDGE)   //enable test mode
    {
        DisplayTestMode(1);
        NetworkSendTestModeStatus(1);
        statusTestMode = STOPPED;
        if(networkState == RISING_EDGE && switchState == LOW_LEVEL)
            switchState = RISING_EDGE;
        if(networkState == LOW_LEVEL && switchState == RISING_EDGE)
            networkState = RISING_EDGE;
    }
    if(switchState == FALLING_EDGE || networkState == FALLING_EDGE)        //disable test mode
    {
        TimerTestMode_Stop();
        DisplayTestMode(0);
        NetworkSendTestModeStatus(0);
        statusTestMode = STOPPED;
        if(networkState == FALLING_EDGE && switchState != FALLING_EDGE)
            switchState = LOW_LEVEL;
        if(networkState != FALLING_EDGE && switchState == FALLING_EDGE)
            networkState = LOW_LEVEL;
    }
    //else    
    //{
    /*update test mode*/
    if(networkState == HIGH_LEVEL && switchState == HIGH_LEVEL )
    {
        if(NetworkStatus() != NETWORK_DISCONN && FinWriteInDB() != NO_WRITE && FinReady() != NO_READY)
        {
            /*start timer*/
            TestMode_UpdateNewRandomTime();
            Int_timerTestMode_StartEx(testModeHandler);
            statusTestMode = RUN;
        }
    }
    //}
}


void TestMode_UpdateNewRandomTime()
{
    uint8_t num;
    
    num = 30+rand()%60;
    
    char buff[11];
    sprintf(buff,"%d",num);
    Display(buff);
    
    TimerTestMode_WriteCounter(0);
    TimerTestMode_WriteCompare(num*100);
    TimerTestMode_Start();   
}

funcReturnValue ReadSwitchState()
{  
    static uint8_t tmpCounter;
    
    if(SW_RunTestMode_Read() == 0)
        tmpCounter++;
    else
        tmpCounter = 0;
    
    if(tmpCounter > COUNTER_TEST_MODE_ON)
    {
        if(switchState == LOW_LEVEL)switchState = RISING_EDGE;
        else if(switchState == HIGH_LEVEL)switchState = FALLING_EDGE;
    }
    else
    {
        if(switchState == RISING_EDGE)switchState = HIGH_LEVEL;
        else if(switchState == FALLING_EDGE)switchState = LOW_LEVEL;
    }

      
    return switchState;
}


funcReturnValue ReadNetworkState()
{
    if(networkState == LOW_LEVEL && NetworkReadTestModeStatus()==1)  networkState = RISING_EDGE;
    else if(networkState == HIGH_LEVEL && NetworkReadTestModeStatus() == 0)  networkState = FALLING_EDGE;
    else if(networkState == RISING_EDGE && NetworkReadTestModeStatus() ==1)  networkState = HIGH_LEVEL;
    else if(networkState == FALLING_EDGE && NetworkReadTestModeStatus() == 0)  networkState = LOW_LEVEL;

    return networkState;   
}