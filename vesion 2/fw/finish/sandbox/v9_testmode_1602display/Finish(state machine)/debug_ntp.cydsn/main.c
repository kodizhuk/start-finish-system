#include "project.h"
#include <stdio.h>
#include "RTC_WDT.h"
#include "display.h"
#include "network.h"

#define TIMEOUT_USER_READ_INFO 500

uint32_t result;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    InitNetwork();
    DisplayStart();
    RTC_WDT_Init();

    Display("Sync time...");
    CyDelay(2000);
    
    
    if(NTPsync() == TIME_SYNC_OK)
    {
        Display("Sync ok");
        CyDelay(4 * TIMEOUT_USER_READ_INFO);
        
        result = TIME_SYNC_OK;
    }
    else
    {
        Display("Sync time error");

        CyDelay(4 * TIMEOUT_USER_READ_INFO);
        
        result = TIME_SYNC_ERR;
    }

    for(;;)
    {
        DisplayRealTime();
        CyDelay(100);
    }
}

/* [] END OF FILE */
