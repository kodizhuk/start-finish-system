#include <project.h>
#include <stdbool.h>
#include <stdio.h>

#include "LED.h"
#include "display.h"
#include "RTC_WDT.h"
#include "gate.h"
#include "network.h"
#include "database.h"
#include "wait_timer.h"

/*frequency blinc led*/
#define INIT_BLINK 	2 
#define ERR_BLINK 	10

/*time left to wait for skier, min*/
#define TIMEOUT  1

/*led state*/
#define LED_ENABLE 	0
#define LED_DISABLE	1


bool SystemReadyToStart(void);
void SystemInit(void);
void SkierFinish(void);
void ErrorStarted(void);


int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
	SystemInit() ;
    
	for(;;)
	{
		if(SystemReadyToStart())
		{
			SkierFinish();          
		}else
        {
		    ErrorStarted();
        }
	}
}

void SystemInit(void)
{
    LedInit();
	LedBlink(INIT_BLINK);
	DisplayConfig();
    RTCLib_WDT_Init();
	//NetworkInit();
    
	//while ((!CheckConnection()) && (!RTCLibSync()))
	{
		DisplayPrintf("Error init");
        CyDelay(500);
	}
}

bool SystemReadyToStart(void)
{
	bool result;
	
	result = false;
	if(!IsGateOpen() /*&& CheckConnection() */&& DatabaseSync())
	{
		result = true;
	}
	
	return result;
}

void SkierFinish(void)
{
	uint64_t time;
    
	DisplayPrintf("System ready");
    
	SetLedState(LED_ENABLE);
    InitWaitingTimer(TIMEOUT);
    
	while(!IsGateOpen() && !WaitingTimeOut())
    {
    }
	if(!WaitingTimeOut()){
        /*printf time and write in database*/
	    time = RTCLib_getTime(RTC_HOUR12);
	    if(!DatabaseWrite(time))
	    {
	    	DisplayPrintf("Error record time");
	    }
        DisplayPrintf("time skier");
        
        DisplayPrintTime(time);
        CyDelay(1000);
    }else 
    {
        LedBlink(INIT_BLINK);
        DisplayPrintf("Time out");
        CyDelay(1000);
    }
}

void ErrorStarted(void)
{
	DisplayPrintf("Error started");
	LedBlink(ERR_BLINK);
}
/* [] END OF FILE */
