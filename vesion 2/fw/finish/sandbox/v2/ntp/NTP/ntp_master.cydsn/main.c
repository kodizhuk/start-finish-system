
#include <project.h>
#include "lib_Display\Display.h"
#include "lib_RTC\RTC_WDT.h"
#include "lib_network\network.h"

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    DisplayConfig();
    DisplayPrintf("System init...");
    
    RTC_WDT_Init(); 
    InitNetwork();

    for(;;)
    {
        
    }
}

/* [] END OF FILE */
