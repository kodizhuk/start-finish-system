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

/* 
    CARCAS FINISH SYSTEM
*/

#include "AppGlobal.h"
#include "LED.h"
#include "test.h"
#include "RTC_WDT.h"
#include "network.h"

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    SystemInit();
    
    while (!SystemStart())
    {
        LCD_1_PrintString("SystemNotInit");
            #ifdef DEBUG_W_UART
                UART_PC_UartPutString("SystemNotInit");
                UART_PC_UartPutString(LR);
            #endif
        // If System Can't Be inited Then try again after 1s 
        CyDelay(1000);
    }
    
    LCD_1_PrintString("SystemInit");
    
    #ifdef DEBUG_W_UART
        UART_PC_UartPutString("SystemInit");
        UART_PC_UartPutString(LR);
    #endif
    
    
    for(;;)
    {
        /* Application Here */
    }
}

void SystemInit()
{
    // UARTPC ----> To PC
    UART_PC_Start();
    // UARTXP ----> To Xbee Module
    UART_XB_Start();
    // RTC With WatchDog Timer.
    // Up Resolution to 1ms. 
    RTC_WDT_Init();
    // Init Timer for Blink LED
    LedInit();
    
    LCD_1_Start();
    LCD_1_DisplayOn();
    
    /*
    UART_XB_UartPutString("XB COM Test Succeful");
    UART_XB_UartPutString(LR);
    */
    
    #ifdef DEBUG_W_UART
    UART_PC_UartPutString("PC COM Test Succeful");
    UART_PC_UartPutString(LR);
    UART_PC_UartPutString("UART Translator v1.0");
    UART_PC_UartPutString(LR);
    #endif
}
    

uint32_t SystemStart(void) 
{
    uint32_t SysStat = 1;
    
    LedBlink(FREQ_INIT_BLINK);
    LCD_1_Position(CURSOR_ROW_0, CURSOR_COL_0);
    
    if (!CheckConnection()){
        SysStat = 0;
        LCD_1_PrintString(ERR_CHECK_CON);
        #ifdef DEBUG_W_UART
            UART_PC_UartPutString(ERR_CHECK_CON);
            UART_PC_UartPutString(LR);
        #endif
        
    }
    
    /* RTC SYNC NO NEED ON START MODULE
    if (!RTCSync()){
        SysStat = 0;
        LCD_1_PrintString(ERR_RTC_SYNC);
        #ifdef DEBUG_W_UART
            UART_PC_UartPutString(ERR_RTC_SYNC);
            UART_PC_UartPutString(LR);
        #endif
    }
    */
    
    LCD_1_Position(CURSOR_ROW_1, CURSOR_COL_0);
    // 0u or 1u 
    return SysStat;   
}

/* [] END OF FILE */
