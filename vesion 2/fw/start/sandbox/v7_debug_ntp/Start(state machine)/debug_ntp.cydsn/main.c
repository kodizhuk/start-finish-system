#include "project.h"
#include <display.h>
#include <network.h>
#include <RTC_WDT.h>

#define TIMEOUT_USER_READ_INFO 500


uint32_t result;


CY_ISR(TX_ISR)
{
    
}

CY_ISR(RX_ISR)
{
    UART_XB2_GetChar();
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    DisplayStart();
    Display("System init...");
    
    RTC_WDT_Init(); 
    InitNetwork();
    
    
    //UART_XB2_Start();
    
    isr_tx_StartEx(TX_ISR);
    isr_rx_StartEx(RX_ISR);
    
    Display("Sync time...");

    while((result = NTPsync()) != TIME_SYNC_OK)
    {
        //Display("Sync time error");
        //CyDelay(4*TIMEOUT_USER_READ_INFO);
    }
    
    Display("Sync ok");
    CyDelay(4*TIMEOUT_USER_READ_INFO);
    
    for(;;)
    {
        DisplayRealTime();
        CyDelay(100);
        
    }
}

/* [] END OF FILE */
