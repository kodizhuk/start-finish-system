#ifndef _RTC_WDT_H
    #define _RTC_WDT_H

#include <CyLib.h>
#include <RTC.h>

#define DEBUG_RTC
#ifdef DEBUG_RTC
    #include <debug.h>
#endif

/*time format*/
#define RTC_HOUR12  1
#define RTC_HOUR24  0


void RTC_WDT_Init();
uint64_t RTCGetUnixTime(void);
uint32_t RTCgetRecentMs(void);
uint64_t RTCgetTime(uint64_t timeFormat);
uint32_t RTCgetHours(uint64_t readTime);
uint32_t RTCgetMinutes(uint64_t readTime);
uint32_t RTCgetSecond(uint64_t readTime);
uint32_t RTCgetMiliecond(uint64_t readTime);
void RTCSync(uint32_t unixTime, uint16_t recentMs);


#endif
/* [] END OF FILE */
