#include <display.h>

/*******************************************************************************
* Function name: DisplayConfig
********************************************************************************
*
* initialization display
*
*******************************************************************************/	
void DisplayConfig(void)
{
    LCD_Start();
}
	

/*******************************************************************************
* Function Name: DisplayPrintf
********************************************************************************
*
* Summary:
*  Writes a zero terminated string to the LCD.
*
* Parameters:
*  string: Pointer to head of char8 array to be written to the LCD module
*
*******************************************************************************/
void DisplayPrintf(char *message)
{
    
    LCD_Position(0,0);
    LCD_PrintString(message);
    LCD_PrintString("          ");
}

void DisplayPrintTime(uint64_t time)
{
    char outInfo[16];
    int hour, min, sec, ms;
    
    hour = RTCgetHours(time);
    min = RTCgetMinutes(time);
    sec = RTCgetSecond(time);
    ms = RTCgetMiliecond(time);
    
    sprintf(outInfo,"%i:%i:%i:%i",hour,min, sec, ms);
    LCD_Position(1,0);
    LCD_PrintString(outInfo);
    
}
/* [] END OF FILE */
