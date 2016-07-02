#include <project.h>
#include <stdbool.h>

#include "LED.h"
#include "display.h"

/*frequency blinc led*/
#define INIT_BLINK 	2 
#define ERR_BLINK 	10

/*time left to wait for skier, min*/
#define TIMEOUT  5

/*led state*/
#define LED_ENABLE 	1
#define LED_DISABLE	0


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
	//RTC_Start();	
	
	//while ((!CheckConnections()) && (!RTS_Sync())
	{
		DisplayPrintf("Error init");
	}
}

bool SystemReadyToStart(void)
{
	bool result;
	
	result = false;
	/*if(!GateOpen() && CheckFinishReady() && DatabaseSync())
	{
		result = true;
	}
	*/
	return result;
}

void SkierStart(void)
{
	uint32_t time;
		
	SetLedState(LED_ENABLE);
/*
	while(!GateOpen() && !WaitingTime(TIMEOUT));
	
	time = RTC_GetTime();
	if(!DatabaseWrite(time))
	{
		DisplayPrintf("Error record time");
	}
	DisplayPrintf(time);	*/
}

void ErrorStarted(void)
{
	/*DisplayPrintf("Error");
	LedBlink(ERR_BLINK);*/
}
/* [] END OF FILE */
