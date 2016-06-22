
	void LedBlink(uint16_t Period);
	void LedOn(void);
	
	void DisplayConfig(void);	
	void DisplayPrintf(char *DisplayInfo);
		
	void RTC_Start(void);
	bool RTS_Sync(void);
	uint32_t RTC_GetTime(void);
	
	bool ÑommunicationStart(void);
	bool CheckConnections(void);
	bool CheckFinishReady(void);
	
	bool GateClosedTest(void);
	bool GateOpen(void);
	
	bool DatabaseSync(void);
	bool DatabaseWrite(uint32_t);
		