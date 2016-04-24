#include <project.h>

CY_ISR(buttHandler)
{
    Pin_blue_Write(~Pin_blue_Read());
    Pin_wire_Write(1);
    CyDelay(1);
    Pin_wire_Write(0);
    UART_UartPutString("start\0");
    
    Pin_start_ClearInterrupt(); 
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();
    int_start_StartEx(buttHandler);
    for(;;)
    {    
        UART_UartPutChar('f');
        CyDelay(100);
    }
}

/* [] END OF FILE */
