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
#include "project.h"
#include <stdio.h>

int main(void)
{
    int32_t conversion;
    float voltage;
    char outBuff[16];
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    LCD_Start();
    ADC_Start();
    
    LCD_Position(0,5);
    LCD_PrintString("ADC");

    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    for(;;)
    {
        conversion = ADC_GetResult16(0);
        voltage = ADC_CountsTo_Volts(0,conversion);
        
        sprintf(outBuff,"%.4f   ",voltage);

        LCD_Position(1,5);
        LCD_PrintString(outBuff);
        CyDelay(50);
        
    }
}

/* [] END OF FILE */
