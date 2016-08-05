#include "lib_Display\display.h"

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

void DisplayPrintTime(uint64_t time, uint16_t mills)
{
    char Restime[30], buff[30];
    struct tm lt;
        
    (void) localtime_r(&time, &lt); 
    strftime(Restime, sizeof(Restime), default_format, &lt); 
    sprintf(buff, "%s:%d", Restime, mills); 
    sprintf(buff, "%d:%d", LastSecTimeOnWay(), LastMillsTimeOnWay());
    //sprintf(outInfo,"%i:%i:%i:%i",hour,min, sec, ms);
    LCD_Position(1,0);
    LCD_PrintString("               ");    
    LCD_Position(1,0);
    LCD_PrintString(buff);
    
}
/* [] END OF FILE */