/*FINISH*/	
#include "test.h" // Empty library functions
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/*frequency blinc led*/
#define INIT_BLINK 	2 
#define ERR_BLINK 	10

/*time left to wait for skier, min*/
#define TIMEOUT  5

/*led state*/
#define LED_ENABLE 	1
#define LED_DISABLE	0

bool CheckRoaderReadyToFinish(void);
void SystemInit(void);
void SkierFinish(void);
void ErrorStarted(void);
	
int main(void)
{
	SystemInit() ;
	
	for(;;)
	{
		while(!CheckRoaderReadyToFinish())
		{
			ErrorStarted();
		}
		SkierFinish();
	}
	
	return 1;
}


void SystemInit(void)
{
	// May process other function for reporting errors
	LedInit();
	LedBlink(INIT_BLINK);
	DisplayConfig();
	RTC_Start();	
	
	while (!CheckConnections() && !RTS_Sync())
	{
		DisplayPrintf("Error init system");
	}
}


bool CheckRoaderReadyToFinish(void)
{
	bool rez;
	
	rez = false;
	if(!GateOpen() && CheckStartReady() && DatabaseSync())
	{
		rez = true;
	}
	
	return rez;
}

void SkierFinish(void)
{
	uint32_t time;
	
	SetLedState(LED_ENABLE);	
	while(!GateOpen() && !WaitingTime(TIMEOUT));
	time = RTC_GetTime();
	if(!DatabaseWrite(time))
	{
		DisplayPrintf("Error record time");
	}
	DisplayPrintf(time);	
}

void ErrorStarted()
{
	DisplayPrintf("Error");
	LedBlink(ERR_BLINK);
}