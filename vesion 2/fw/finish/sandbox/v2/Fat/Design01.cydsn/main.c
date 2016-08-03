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
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#include "logResult.h"

char uartInputBuffer[255];
uint8 uartIBufferPtr = 0;

void SendMenu();


int main()
{
    char uartchar;
       
    /* Start serial port. Send initial message.*/
    UART_Start();
    RTC_Start();
    SendMenu();
    logStart();
    skierDB_El res = {1470039198, 100, 1470039229, 200, 1470039243, 300};
    
    for(;;)
    {   
        WriteSkierResult(&res);
        CyDelay(500);
    }
    
}

void SendMenu()
{
    UART_UartPutString("\n\nPSoC FatFs. PSoC 4200BLE FatFs Test.\n\r");
    
    UART_UartPutString("Start test :>\n\r");    
}


/* [] END OF FILE */
