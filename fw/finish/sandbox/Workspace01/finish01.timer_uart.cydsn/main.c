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
//#include <stdlib.h>       //include for itoa()
#include <stdio.h>

struct time{
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
    uint16_t msec;
};        
struct time segment = {0,0,0,0};

CY_ISR(wire_Handler)
{
    //uint16_t counter = Timer_ReadCapture();
    
    LCD_Position(1,0);
    if (++segment.sec==59){
        segment.sec = 0;   
        if (++segment.min==59){
            segment.min = 0;    
            if (++segment.hour==59) 
                segment.hour = 0;   
        }  
    }
    
    Timer_ClearInterrupt(Timer_INTR_MASK_CC_MATCH);
}
CY_ISR(finish_Handler)
{
    //LCD_Position(1,9);
    //LCD_PutChar(':');
    //LCD_PrintNumber(Timer_ReadCompare);
}

int main()
{
    
    char lcd_buffer[32];
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    wire_int_StartEx(wire_Handler);
    finish_int_StartEx(finish_Handler);
    Timer_Start();
    UART_Start();
    LCD_Start();
    
    LCD_Position(0,0);
    LCD_PrintString("Start-Finish ");
    
    for(;;)
    {
        uint16_t counter = Timer_ReadCounter();
        sprintf(lcd_buffer,"%i:%i:%i :%i",segment.hour,segment.min,segment.sec, counter);
        LCD_Position(1,0);
        LCD_PrintString(lcd_buffer);
        CyDelay(100);
    }
}

/* [] END OF FILE */
