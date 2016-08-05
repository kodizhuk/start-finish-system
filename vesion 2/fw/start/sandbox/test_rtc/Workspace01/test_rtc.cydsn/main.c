/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    LCD_Start();

    RTC_Init();
    RTC_Start();    
    LCD_Position(0,0);
    LCD_PrintString("init");

    for(;;)
    {
        LCD_Position(1,0);
        uint32_t time = RTC_GetTime();
        uint32_t sec = RTC_GetSecond(time);
        LCD_PrintNumber(sec);
        RTC_Update();
        CyDelay(500);
    }
}

/* [] END OF FILE */
