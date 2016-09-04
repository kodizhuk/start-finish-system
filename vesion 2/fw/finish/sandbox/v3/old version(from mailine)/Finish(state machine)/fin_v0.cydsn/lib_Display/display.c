
#include <CyLib.h>
#include <LCD.h>
#include <stdio.h>
#include "lib_DB\database.h"
#include "lib_RTC\RTC_WDT.h"
#include "lib_Display\display.h"


/*buffer for print string on LCD*/
static  char buff[100];


/*******************************************************************************
* Function name: DisplayConfig
********************************************************************************
*
* Summary:
* initialization display
*
*******************************************************************************/	
void DisplayStart(void)
{
    LCD_Start();
}
	

/*******************************************************************************
* Function Name: DisplayPrintf
********************************************************************************
*
* Summary:
*   Writes a zero terminated string to the LCD.
*
* Parameters:
*  string: Pointer to head of char8 array to be written to the LCD module
* Note:
*   print string from position row = 0, column = 0
*
*******************************************************************************/
void Display(char *message)
{    
    LCD_Position(0,0);
    LCD_PrintString(message);
    LCD_PrintString("          ");
}

/*******************************************************************************
* Function name: DisplayPutIndicatorSD
********************************************************************************
*
* Summary:
*   print incator SD card from position row = 1, column = 15
*
* Parametrs:
*   state = SD_INSERT or state = SD_NO_INSERT
*******************************************************************************/
void DisplayIndicatorSD(SDindicator indicator)
{
    LCD_Position(1,15);
    if(indicator == SD_INSERT)
    {
        LCD_PutChar(LCD_CUSTOM_0);
    }
    else
    {
        LCD_PutChar(LCD_CUSTOM_1);
    }
}

/*******************************************************************************
* Function name: DisplayPutIndicatorNetwork
********************************************************************************
*
* Summary:
*   print incator connect  from position row = 1, column = 15
*
* Parametrs:
*   state = CONNECT or state = DISCONNECT
*******************************************************************************/
void DisplayIndicatorNetwork(NetworkIndicator indicator)
{
    LCD_Position(1,14);
    if(indicator == CONNECT)
    {
        LCD_PutChar(LCD_CUSTOM_2);
    }
    else
    {
        LCD_PutChar(LCD_CUSTOM_3);
    }
}

/*******************************************************************************
* Function name: DisplayPrintfRealTime
********************************************************************************
*
* Summary:
*   print real time from position row = 1, column = 0
*
*******************************************************************************/
void DisplayRealTime(void)
{
    uint32_t time;
    
    time = RTC_GetTime();
    sprintf(buff, "%02lu:%02lu:%02lu      ", RTC_GetHours(time),RTC_GetMinutes(time), RTC_GetSecond(time));
    LCD_Position(1,0);
    LCD_PrintString(buff);
}

/*******************************************************************************
* Function name: DisplayPrintLastTimeSkier
********************************************************************************
*
* Summary:
*   print time last skier from position row = 1, column = 0
*
*******************************************************************************/
void DisplayLastSkierTime(uint32_t sec, uint16_t milisec)
{
    /*printf time in format mm:ss:msmsms*/
    sprintf(buff, "Result %02u:%02u:%03u",sec/60,sec%60, milisec);
    LCD_Position(0,0);
    LCD_PrintString(buff);
}

/*******************************************************************************
* Function name: DisplayPrintNumSkierOnWay
********************************************************************************
*
* Summary:
*   print number skier on way from position row = 1, column = 11
*
*******************************************************************************/
void DisplayNumSkierOnWay(uint32_t num)
{
    sprintf(buff, "%u/%u", num, MAX_SKIERS_ON_WAY);
    LCD_Position(1,10);
    LCD_PrintString(buff);
}


/*******************************************************************************
* Function name: DisplayPrintfLoading
********************************************************************************
*
* print loading from position row = 1, column = 0
*
*******************************************************************************/
void DisplayLoading(uint32_t numLoad)
{
    if(numLoad == 0)
    {
        /*clear row 1*/
        LCD_Position(1,0);
        LCD_PrintString("             ");
    }
    if((numLoad > 0) && numLoad < 16)
    {
        LCD_Position(1,numLoad-1);
        LCD_PutChar(LCD_CUSTOM_4);
    }
}
/* [] END OF FILE */