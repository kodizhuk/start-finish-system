
#include <CyLib.h>
#include <stdio.h>
//#include "lib_RTC\RTC_WDT.h"
#include "..\..\common\lib\lib_Display\display.h"
#include "..\..\common\lib\nokia5110\LCD5110_Graph.h"
#include "project.h"

/*resistive voltage divider 1/10 */
#define BATT_0_PERCENT      0.40
#define BATT_25_PERCENT     0.42
#define BATT_50_PERCENT     0.44
#define BATT_75_PERCENT     0.46
#define BATT_100_PERCENT    0.48

#define MAX_LEN_DISPLAY     11

/*network quality*/
#define NUM_STICK_NETWORK_QUALITY   4

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
    LCD_BL_Write(0);
    
    InitLCD(LCD_CONTRAST);
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
    uint8_t len;
    char strNull[11] = {"           "};
    strncpy(buff,message,MAX_LEN_DISPLAY);
    len = strlen(message);
    if(len < MAX_LEN_DISPLAY)
    {
        strncat(buff,strNull,MAX_LEN_DISPLAY-len);
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
* Function name: DisplayNetworkQuality
********************************************************************************
*
* Summary:
*   print quality network
*
* Parametrs:
*   quality - quality network 0..5
*******************************************************************************/
void DisplayNetworkQuality(uint8_t quality)
{
    clrVLine(1,3,35);
    clrVLine(2,3,35);
    clrVLine(3,3,35);
    clrVLine(4,3,35);
    clrVLine(5,3,35);
    
    if(quality > 1)
    {
        drawVLine(1,31,7);
        drawVLine(2,31,7);
        drawVLine(3,31,7);
    }
    if(quality > 2)
    {
        drawVLine(1,22,7);
        drawVLine(2,22,7);
        drawVLine(3,22,7);
    }
    if(quality > 3)
    {
        drawVLine(1,13,7);
        drawVLine(2,13,7);
        drawVLine(3,13,7);
        drawVLine(4,13,7);
    }
    if(quality > 4)
    {
        drawVLine(1,4,7);
        drawVLine(2,4,7);
        drawVLine(3,4,7);
        drawVLine(4,4,7);
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
    //sprintf(buff,"%02d:%02d:%02d", 13,59,59);
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

/*******************************************************************************
* Function name: DisplayTestMode
********************************************************************************
*
* Summary:
*   display on indicator test mode
*
*******************************************************************************/
void DisplayTestMode(uint8_t state)
{
    setFont(TinyFont);
    if(state > 0)
        print("test",43,31);
    else
        print("    ",43,31); 
}

/*******************************************************************************
* Function name: DisplaBacklightOn/DisplaBacklightOff
********************************************************************************
*
* Summary:
*   on and off backlight display
*
*******************************************************************************/
void DisplaBacklightOn(void)
{
    LCD_BL_Write(1);
}

void DisplaBacklightOff(void)
{
    LCD_BL_Write(0);
}

/*******************************************************************************
* Function name: DisplaBacklightOn/DisplaBacklightOff
********************************************************************************
*
* Summary:
*   display number id skier
*
*******************************************************************************/
void DisplayIDskier(uint8_t number)
{
    setFont(MediumNumbers);
    if(number <10)
    {
        printNumI(number,27,14,1,' ');
        setFont(SmallFont);
        print("  ",40,14);
        print("  ",40,22);
        print("  ",50,14);
        print("  ",50,22);
    }else if(number < 100)
    {
        printNumI(number,27,14,1,' ');
        setFont(SmallFont);
        print("  ",50,14);
        print("  ",50,22);
    }
    else
    {
        printNumI(number,27,14,1,' ');
    }
    update();
}
/* [] END OF FILE */