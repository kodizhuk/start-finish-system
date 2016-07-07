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

#include <CyLib.h>
#include <RTC_1.h>

#ifdef USE_WDT_RTC
    #include <WDT0_ISR.h>
    
    CY_ISR_PROTO(Wdt0_Handler);
#endif

uint32_t RTCgetMs();
uint32_t RTCSync ();
void RTC_WDT_Init();

extern uint16_t msRTC; 
/* [] END OF FILE */
