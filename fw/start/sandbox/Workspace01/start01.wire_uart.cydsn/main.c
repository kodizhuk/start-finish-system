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

CY_ISR(butto_Handler)
{
    Pin_blue_Write(~Pin_blue_Read());
    Pin_wire_Write(1);
    
    button_ClearInterrupt();
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */ 
    butt_int_StartEx(butto_Handler);

    for(;;)
    {
        if(Pin_wire_Read())
        {
            CyDelay(1);
            Pin_wire_Write(0);
        }
    }
}

/* [] END OF FILE */
