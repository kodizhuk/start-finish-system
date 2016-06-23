/*START*/
#include "test.h" // Empty library functions
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/*frequency blinc led*/
#define INIT_BLINK 	2 
#define ERR_BLINK 	10

/*led state*/
#define LED_ENABLE 	1
#define LED_DISABLE	0

bool CheckRoaderReadyToStart(void);
void SystemInit(void);
void SkierStart(void);
void ErrorStarted(void);


	
int main(void)
{
	SystemInit() ;
	
	for(;;)
	{
		while(!CheckRoaderReadyToStart())
		{
			ErrorStarted();
		}
		SkierStart();
	}
	
	return 1;
}


void SystemInit(void)
{
	// May process other function for reporting errors
	LedBlink(INIT_BLINK);
	DisplayConfig();
	RTC_Start();	
	
	while (!CheckConnections() && !RTS_Sync())
	{
		DisplayPrintf("Error init system");
	}
}


bool CheckRoaderReadyToStart(void)
{
	bool rez;
	
	rez = false;
	if(!GateOpen() && CheckFinishReady() && DatabaseSync())
	{
		rez = true;
	}
	
	return rez;
}

void SkierStart(void)
{
	uint32_t time;
		
	SetLedState(LED_ENABLE);	
	while(!GateOpen());
	time = RTC_GetTime();
	if(!DatabaseWrite(time))
	{
		DisplayPrintf("Error record time");
	}
	DisplayPrintf(time);	
}

void ErrorStarted(void)
{
	DisplayPrintf("Error");
	LedBlink(ERR_BLINK);
}