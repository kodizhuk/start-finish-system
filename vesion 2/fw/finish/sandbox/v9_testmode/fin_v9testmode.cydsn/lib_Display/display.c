
#include <CyLib.h>
#include <stdio.h>
//#include "lib_RTC\RTC_WDT.h"
#include "lib_Display\display.h"
#include "nokia5110/LCD5110_Graph.h"
#include "project.h"

#define BATT_0_PERCENT      0.36
#define BATT_25_PERCENT     0.41
#define BATT_50_PERCENT     0.46
#define BATT_75_PERCENT     0.51
#define BATT_100_PERCENT    0.56

extern unsigned char SmallFont[];
extern unsigned char TinyFont[];
extern unsigned char BigNumbers[];
extern unsigned char MediumNumbers[];
extern uint8_t logoCypress[];
extern uint8_t homeSkreen[];
extern uint8_t homeSkreenNull[];
extern uint8_t networkOn[];
extern uint8_t SDinsert[];
extern uint8_t SDnoInsert[];

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
    /*backlight off*/
    LCD_BL_Write(1);
    
    InitLCD(LCD_CONTRAST);
    setContrast(0x40);
    setFont(SmallFont);
    clrScr();
    drawBitmap(0, 0, homeSkreenNull, 84, 48);
    update();
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
    //if(strlen(message) > 11)return;
    uint8_t len;
    char strNull[11] = {"           "};
    strncpy(buff,message,11);
    len = strlen(message);
    if(len<11)
    {
        strncat(buff,strNull,11-len);
    }
    
    setFont(SmallFont);
    print(buff,8,40);
    update();
}

/*******************************************************************************
* Function name: DisplayPutIndicatorSD
********************************************************************************
*
* Summary:
*   print incator SD card 
*
* Parametrs:
*   state = SD_INSERT or state = SD_NO_INSERT
*******************************************************************************/
void DisplayIndicatorSD(SDindicator indicator)
{
    if(indicator == SD_INSERT)
    {
        drawBitmap(64, 1, SDinsert, 10, 8);
    }
    else
    {
        drawBitmap(64, 1, SDnoInsert, 10, 8);
    }
    update();
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
    if(indicator == CONNECT)
    {
        drawBitmap(1,3,networkOn,6,35);
    }
    else
    {
        clrVLine(1,3,35);
        clrVLine(2,3,35);
        clrVLine(3,3,35);
        clrVLine(4,3,35);
        clrVLine(5,3,35);
    }
    update();
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
    
    setFont(SmallFont);
    time = RTC_GetTime();
    sprintf(buff, "%02lu:%02lu:%02lu", RTC_GetHours(time),RTC_GetMinutes(time), RTC_GetSecond(time));
    print(buff,10,0);
    update();
    
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
//    if(numLoad == 0)
//    {
//        /*clear row 1*/
//        LCD_Position(1,0);
//        LCD_PrintString("             ");
//    }
//    if((numLoad > 0) && numLoad < 16)
//    {
//        LCD_Position(1,numLoad-1);
//        LCD_PutChar(LCD_CUSTOM_4);
//    }
}

/*******************************************************************************
* Function name: DisplayBattVoltage
********************************************************************************
*
* print voltage battery
*
*******************************************************************************/
void DisplayBattVoltage(float voltage)
{
    if(voltage < 0)return;
    
    /*clear image batt*/
    uint8_t i;
    for(i=0;i<5;i++)
    {
        clrVLine(77+i,4,35);
    }
    
    if(voltage > BATT_0_PERCENT)
    {
        drawVLine(79,31,7);
        drawVLine(80,31,7);
        drawVLine(81,31,7);
    }
    if(voltage > BATT_25_PERCENT)
    {
        drawVLine(79,22,7);
        drawVLine(80,22,7);
        drawVLine(81,22,7);
    }
    if(voltage > BATT_50_PERCENT)
    {
        drawVLine(78,13,7);
        drawVLine(79,13,7);
        drawVLine(80,13,7);
        drawVLine(81,13,7);
    }
    if(voltage > BATT_75_PERCENT)
    {
        drawVLine(77,4,7);
        drawVLine(78,4,7);
        drawVLine(79,4,7);
        drawVLine(80,4,7);
        drawVLine(81,4,7);
    }
    update();
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
    if(sec > 60000 || milisec >= 1000)return;
        
    setFont(SmallFont);
    printNumI(sec/60,22,11,3,' ');
    printNumI(sec%60,28,20,2,' ');
    printNumI(milisec,22,29,3,' ');
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
    setFont(MediumNumbers);
    printNumI(num,43,14,1,' ');
    printNumI(4,64,14,1,' ');
    update();
}

void DisplayTestMode(uint8_t state)
{
    setFont(TinyFont);
    if(state > 0)
    {
        print("test",43,31);
    }
    else
    {
        print("    ",43,31); 
    }
}

/* [] END OF FILE */