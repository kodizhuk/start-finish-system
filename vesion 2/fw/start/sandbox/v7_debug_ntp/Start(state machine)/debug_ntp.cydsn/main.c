#include "project.h"
#include <display.h>
#include <network.h>
#include <RTC_WDT.h>
#include <stdio.h>

#define TIMEOUT_USER_READ_INFO 500


uint32_t result;




int main(void)
{    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    DisplayStart();
    Display("System init...");
    
    RTC_WDT_Init(); 
    InitNetwork();
    
    
    
    Display("Sync time...");

    uint8_t number = 0;
    while((result = NTPsync()) != TIME_SYNC_OK)
    {
        char buf[10];
        sprintf(buf, "Sync time -%d", number++);
        LCD_Position(0,0);
        LCD_PrintString(buf);
        CyDelay(500);
    }
    
    Display("Sync ok        ");
    CyDelay(4*TIMEOUT_USER_READ_INFO);
    
    for(;;)
    {
        DisplayRealTime();
        CyDelay(500);
    }
}

/* [] END OF FILE */
