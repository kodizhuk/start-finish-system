/*START*/
#include "test.h" // Empty library functions
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define INIT_BLINK 500 // time in ms for one period
#define ERR_BLINK 100 // 100 ms in one period = 10Hz

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
	if(GateClosedTest() && CheckFinishReady() && DatabaseSync())
	{
		rez = true;
	}
	
	return rez;
}

void SkierStart(void)
{
	uint32_t time;
	
	
	LedOn();	
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