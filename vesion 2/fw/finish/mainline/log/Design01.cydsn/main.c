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

#include "diskio.h"
#include "ff.h"
#include "database.h"

char uartInputBuffer[255];
uint8 uartIBufferPtr = 0;

void SendMenu();
void FatFsError(FRESULT result);


int main()
{
    char uartchar;
       
    /* Start serial port. Send initial message.*/
    UART_Start();
    RTC_Start();
    SendMenu();
    dataBaseStart();
    struct skierDB rez = {1470039198, 100, 1470039229, 200, 1470039243, 300};
    


    for(;;)
    {
        WriteSkierRezult(&rez);
        CyDelay(100);
    }
    
}

void SendMenu()
{
    UART_UartPutString("\n\nPSoC FatFs. PSoC 4200BLE FatFs Test.\n\r");
    
    UART_UartPutString("Start test :>\n\r");    
}



void FatFsError(FRESULT result)
{
    switch (result)
    {
        case FR_DISK_ERR:
            UART_UartPutString("\n    error: (FR_DISK_ERR) low level error.\n"); break;
            
        case FR_INT_ERR:
            UART_UartPutString("\n    error: (FR_INT_ERR)\n"); break; 
            
        case FR_NOT_READY:
            UART_UartPutString("\n    error: (FR_NOT_READY) sdcard not ready.\n"); break;
            
        case FR_NO_FILE:
            UART_UartPutString("\n    error: (FR_NO_FILE) invalid file.\n"); break;
            
        case FR_NO_PATH:
            UART_UartPutString("\n    error: (FR_NO_PATH) invalid path.\n"); break;
            
        case FR_INVALID_NAME:
            UART_UartPutString("\n    error: (FR_INVALID_NAME) invalid name.\n"); break;
            
        case FR_DENIED:
            UART_UartPutString("\n    error: (FR_DENIED) operation denied.\n"); break;
            
        case FR_EXIST:
            UART_UartPutString("\n    error: (FR_EXIST) it exists yet...\n"); break;
            
        case FR_INVALID_OBJECT:
            UART_UartPutString("\n    error: (FR_INVALID_OBJECT)\n"); break;
            
        case FR_WRITE_PROTECTED:
            UART_UartPutString("\n    error: (FR_WRITE_PROTECTED)\n"); break;
            
        case FR_INVALID_DRIVE:
            UART_UartPutString("\n    error: (FR_INVALID_DRIVE)\n"); break;
            
        case FR_NOT_ENABLED:
            UART_UartPutString("\n    error: (FR_NOT_ENABLED) sdcard unmounted.\n"); break;
            
        case FR_NO_FILESYSTEM:
            UART_UartPutString("\n    error: (FR_NO_FILESYSTEM) no valid FAT volume.\n"); break;  
            
        case FR_MKFS_ABORTED:
            UART_UartPutString("\n    error: (FR_MKFS_ABORTED)\n"); break;
            
        case FR_TIMEOUT:
            UART_UartPutString("\n    error: (FR_TIMEOUT)\n"); break;
            
        case FR_LOCKED:
            UART_UartPutString("\n    error: (FR_LOCKED)\n"); break;
            
        case FR_NOT_ENOUGH_CORE:
            UART_UartPutString("\n    error: (FR_NOT_ENOUGH_CORE)\n"); break;     
            
        case FR_TOO_MANY_OPEN_FILES:
            UART_UartPutString("\n    error: (FR_TOO_MANY_OPEN_FILES)\n"); break;
            
        case FR_INVALID_PARAMETER:
            UART_UartPutString("\n    error: (FR_INVALID_PARAMETER)\n"); break; 
            
        default: {}; break;
    }
}

/* [] END OF FILE */
