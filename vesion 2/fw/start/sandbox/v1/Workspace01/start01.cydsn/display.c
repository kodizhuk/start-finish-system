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
}

/* [] END OF FILE */
