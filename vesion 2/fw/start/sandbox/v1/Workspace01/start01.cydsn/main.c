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
void SkierStart(void);
void ErrorStarted(void);

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
	SystemInit() ;
    
	for(;;)
	{
		while(!SystemReadyToStart())
		{
			ErrorStarted();
		}
		SkierStart();
	}
}

void SystemInit(void)
{
    LedInit();
	LedBlink(INIT_BLINK);
	DisplayConfig();
    RTC_WDT_Init();
	//RTC_Start();	
	
	//while ((!CheckConnection()) && (!RTCSync()))
	{
		DisplayPrintf("Error init");
        CyDelay(500);
	}
}

bool SystemReadyToStart(void)
{
	bool result;
	
	result = false;
	if(!GateOpen() )//&& CheckFinishReady() && DatabaseSync())
	{
		result = true;
	}
	
	return result;
}

void SkierStart(void)
{
	uint64_t time;
    
	DisplayPrintf("System ready");
    
	SetLedState(LED_ENABLE);
    InitWaitingTimer(TIMEOUT);
    
	while(!GateOpen() && !WaitingTimeOut())
    {
    }
	
   if(!WaitingTimeOut()){
        /*printf time and write in database*/
	    time = RTCgetTime(RTC_HOUR12);
	    if(!DatabaseWrite(time))
	    {
	    	DisplayPrintf("Error record time");
	    }
        DisplayPrintf("time skier");
        
        DisplayPrintTime(time);
        CyDelay(5000);
    }else 
    {
        LedBlink(INIT_BLINK);
        DisplayPrintf("Time out");
        CyDelay(5000);
    }
}

void ErrorStarted(void)
{
	DisplayPrintf("Error started");
	LedBlink(ERR_BLINK);
}
/* [] END OF FILE */
