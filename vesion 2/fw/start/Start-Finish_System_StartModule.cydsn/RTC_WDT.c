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

#include "RTC_WDT.h"

#ifdef USE_WDT_RTC

    uint16_t msRTC = 0;

CY_ISR_PROTO(Wdt0_Handler){
    msRTC++;
    if (msRTC == 1000u) 
    {
        msRTC = 0u; 
        RTC_1_Update();
    }
    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
    WDT0_ISR_ClearPending();
}

#endif

uint32_t RTCgetMs()
{
    uint16_t TmsRTC = 0;
    #ifdef USE_WDT_RTC
        TmsRTC = msRTC;
    #endif
    return TmsRTC;
}

uint32_t RTCSync()
{
    return 1u;
}

void RTC_WDT_Init(){
    RTC_1_Start();
    
    #ifdef USE_WDT_RTC
        WDT0_ISR_StartEx(Wdt0_Handler);
    #endif
}
/* [] END OF FILE */
