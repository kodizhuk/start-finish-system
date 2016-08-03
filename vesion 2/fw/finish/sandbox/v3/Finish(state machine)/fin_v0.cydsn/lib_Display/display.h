
#include <project.h>
#include <CyLib.h>
#include <LCD.h>
#include <LCD_LCDPort.h>
#include <lib_RTC\RTC_WDT.h>
#include <stdio.h>
#include <time.h>
#include "lib_DB\database.h"

static const char default_format[] = "%H:%M:%S";// %Y %T";

/***************************************
*        Function Prototypes
***************************************/
void DisplayConfig(void);	
void DisplayPrintf(char *message);
void DisplayPrintTime(uint64_t time, uint16_t mills);

/* [] END OF FILE */