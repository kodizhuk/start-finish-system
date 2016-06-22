/*START*/
#include <test.h> // Empty library functions

#define INIT_BLINK 500 // time in ms for one period
#define ERR_BLINK 100 // 100 ms in one period = 10Hz

	/*світлодіодна індикація*/
	void LedBlink(uint16_t Period);

	bool RTS_sync(void);
	uint32_t RTC_GetTime(void); 
	
	/*перевірка зєднанння встановлено*/
	bool CheckConnections();
	
	/*перевірка чи стартові ворота закриті*/
	bool GateClosedTest();
	
	/*перевірка чи фініш готовий до роботи*/
	bool CheckFinishReady();
	
	bool DatabaseSync();
	bool DatabaseWrite();
	
	void DisplayInformation(char *DisplayData);	
	
int main(void)
{
	if (!SystemInit()) 
		Display("System not started");
	for(;;){
		while(!skier_started)
		{		
			if(CheckRoaderReadyToStart())
			{
				SkierStart();
				skier_started = 1;
			}else 
			{
				DisplayError();
			}
		}
		WaitForNextSkier();
	}
	return 1;
}


uint8_t StartConfig(void)
{
	uint8_t Res;
	Res = 1;
	// May process other function for reporting errors
	DisplayConfig();
	LedBlink(INIT_BLINK);
	if (!RTC_Start() || !СommunicationStart() || !RTS_sync()) 
		Res = 0;
	return Res; 
	//СommunicationStart();
	//LedIndicationStart();	
}


bool RoaderReadyToStart(void)
{
	//LedBlink(READY_BLINK);
	RTS_sync();	
	CheckConnections();	
	GateClosedTest();
	CheckFinishReady();
	DatabaseSync();
	return Res;
}

void SkierStarted(void)
{
	uint32_t time;
	
	while(!GateOpen());
	time = RTC_GetTime();
	DatabaseWrite(time)
	DisplayPrintf(time);
	
}

void ErrorStarted();
{
	DisplayPrintf("Error");
	LedBlink(ERR_BLINK);
}