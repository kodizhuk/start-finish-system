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
#include "DS1307.h"


int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    uint64_t unixTime;
    //DS1307_SetUnixTime(1470066420);
    
    for(;;)
    {
        unixTime = DS1307_GetUnixTime();
        
        CyDelay(100);
    }
}

/* [] END OF FILE */
