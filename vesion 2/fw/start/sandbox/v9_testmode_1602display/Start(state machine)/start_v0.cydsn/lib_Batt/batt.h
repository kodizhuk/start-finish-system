#ifndef _BATT_H
    #define _BATT_H
    
#include <CyLib.h>

void BattADC_Init(void);
float ReadBattVoltage(void);    
    
#endif