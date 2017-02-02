#include "lib_Batt\batt.h"
#include "ADC.h"

float voltage;


void BattADC_Init(void)
{
    ADC_Start();
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);        
}

float ReadBattVoltage(void)
{
    int32_t conversion;
    
    conversion = ADC_GetResult16(0);
    voltage = ADC_CountsTo_Volts(0,conversion);
    
    return voltage;
}