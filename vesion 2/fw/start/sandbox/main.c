/*START*/

	/*світлодіодна індикація*/
	LedIndication(period);

	RTS_sync();
	RTC_read();
	
	/*перевірка зєднанння встановлено*/
	CheckConnections();
	
	/*перевірка чи стартові ворота закриті*/
	GateClosedTest();
	
	/*перевірка чи фініш готовий до роботи*/
	CheckFinishReady();
	
	DatabaseSync();
	DatabaseWrite();
	
	DisplayPrintf();	
	
int main(void)
{
	StartConfig();
	if(RoaderStart())
	{
		SkierStarted();
	}else 
	{
		ErrorStarted();
	}
}


void StartConfig(void)
{
	RTCStart();
	СommunicationStart();
	DisplayStart();
	LedIndicationStart();	
}


int RoaderStart()
{
	LedIndication(period);
	RTS_sync();	
	CheckConnections();	
	GateClosedTest();
	CheckFinishReady();
	DatabaseSync();
}

void SkierStarted()
{
	if(GateOpen())
	{
		time = RTC_read();
		DatabaseWrite(time);
		DisplayPrintf(time);
	}
	
}

void ErrorStarted();
{
	DisplayPrintf("Error");
	LedIndication(period);
}