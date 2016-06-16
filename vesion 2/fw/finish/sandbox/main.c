/*FINISH*/

	/*світлодіодна індикація*/
	LedIndication(period);

	RTS_sync();
	RTC_read();
	
	/*перевірка зєднанння встановлено*/
	CheckConnections();
	
	/*перевірка на фініші нікого немає*/
	GateClosedTest();
	
	
	DatabaseSync();
	DatabaseWrite();
	
	DisplayPrintf();	
	
int main(void)
{
	StartConfig();
	if(RoaderReadyToFinish())
	{
		SkierFinished();
	}else 
	{
		ErrorFinished();
	}
}


void StartConfig(void)
{
	RTC_Start();
	СommunicationStart();
	DisplayStart();
	LedIndicationStart();	
}


bool RoaderReadyToFinish()
{
	LedIndication(period);
	RTS_sync();	
	CheckConnections();	
	GateClosedTest();
	CheckStartReady();
	DatabaseSync();
}

void SkierFinished()
{
	if(GateOpen())
	{
		time = RTC_read();
		DatabaseWrite(time);
		DisplayPrintf(time);
	}
	
}

void ErrorFinished();
{
	DisplayPrintf("Error");
	LedIndication(period);
}