#include "project.h"
#include <display.h>
#include <network.h>
#include <RTC_WDT.h>

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

    while((result = NTPsync()) != TIME_SYNC_OK)
    {
        Display("Sync time error");
        //CyDelay(4*TIMEOUT_USER_READ_INFO);
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
