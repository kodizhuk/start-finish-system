#include <project.h>
//#include <stdlib.h>       //include for itoa()
#include <stdio.h>          //include for sprintf()

struct time{
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
    uint16_t msec;
};        
struct time wire = {0,0,0,0};
struct time uart = {0,0,0,0};

CY_ISR(wireHandler)
{
    if (++wire.sec==59){
        wire.sec = 0;   
        if (++wire.min==59){
            wire.min = 0;    
            if (++wire.hour==24) 
                wire.hour = 0;   
        }  
    }   
    Timer_wire_ClearInterrupt(Timer_wire_INTR_MASK_CC_MATCH);
}
CY_ISR(uartHandler)
{
    if (++uart.sec==59){
        uart.sec = 0;   
        if (++uart.min==59){
            uart.min = 0;    
            if (++uart.hour==24) 
                uart.hour = 0;   
        }  
    }   
    Timer_uart_ClearInterrupt(Timer_uart_INTR_MASK_CC_MATCH);
}
CY_ISR(stopHandler)
{
    Timer_wire_Stop();
    Timer_uart_Stop();
    butt_stop_ClearInterrupt();
}
CY_ISR(wstartHandler)
{
    Timer_wire_Start();
    pin_wire_ClearInterrupt();
}
CY_ISR(ustartHandler)
{
    if(UART_GetChar() == 's') 
    Timer_uart_Start();
    Pin_red_Write(~Pin_red_Read());
}
int main()
{   
    char out_buffer[32];
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_wire_StartEx(wireHandler);
    isr_uart_StartEx(uartHandler); 
    isr_stop_StartEx(stopHandler);
    isr_wstart_StartEx(wstartHandler);
    isr_ustart_StartEx(ustartHandler);
    UART_Start();
    //Timer_uart_Start();
    //LCD_Start();   
    //LCD_Position(0,0);
    //LCD_PrintString("Start-Finish ");
    uint16_t counter;
    for(;;)
    {
        //if(UART_UartGetChar() == 's') Timer_uart_Start();
        counter = Timer_wire_ReadCounter();
        sprintf(out_buffer,"Wired: %i:%i:%i:%i\n\r",wire.hour,wire.min,wire.sec, counter);
        UART_PutString(out_buffer);
        counter = Timer_uart_ReadCounter();
        sprintf(out_buffer,"Xbee:  %i:%i:%i:%i\n\n\r",uart.hour,uart.min,uart.sec, counter);
        UART_PutString(out_buffer);
        CyDelay(100);
    }
}

/* [] END OF FILE */
