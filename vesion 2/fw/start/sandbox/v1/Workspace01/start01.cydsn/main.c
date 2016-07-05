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
#define TIMEOUT  5

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
	
	while ((!CheckConnection()) && (!RTCSync()))
	{
		DisplayPrintf("Error init");
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
	uint32_t time;
		
	SetLedState(LED_ENABLE);
    DisplayPrintf("System ready");

	while(!GateOpen() && !WaitingTime(TIMEOUT));
	
	time = RTC_GetTime();
	if(!DatabaseWrite(time))
	{
		DisplayPrintf("Error record time");
	}
	DisplayPrintf(time);	
}

void ErrorStarted(void)
{
	DisplayPrintf("Error started");
	LedBlink(ERR_BLINK);
}
/* [] END OF FILE */
