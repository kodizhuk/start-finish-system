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
#include <RTC.h>

#define USE_WDT_RTC

#ifdef USE_WDT_RTC
     #include <CyLFClk.h>
#endif

#define RTC_TIME_FORMAT_SHIFT       (39u)
#define RTC_PERIOD_OF_DAY_SHIFT     (38u)
#define RTC_10_HOURS_SHIFT          (36u)
#define RTC_HOURS_SHIFT             (32u)
#define RTC_10_MINUTES_SHIFT        (28u)
#define RTC_MINUTES_SHIFT           (24u)
#define RTC_10_SECONDS_SHIFT        (20u)
#define RTC_SECONDS_SHIFT           (16u)
#define RTC_100_MILISECONDS_SHIFT   (12u)
#define RTC_10_MILISECONDS_SHIFT    (8u)
#define RTC_MILISECONDS_SHIFT       (0u)

#define RTC_MASK_TIME_FORMAT       (0x00000001ull << RTC_TIME_FORMAT_SHIFT )
#define RTC_MASK_PERIOD_OF_DAY     (0x00000001ull << RTC_PERIOD_OF_DAY_SHIFT)
#define RTC_MASK_10_HOURS          (0x00000003ull << RTC_10_HOURS_SHIFT )
#define RTC_MASK_HOURS             (0x0000000Full << RTC_HOURS_SHIFT )
#define RTC_MASK_10_MINUTES        (0x00000007uL << RTC_10_MINUTES_SHIFT )
#define RTC_MASK_MINUTES           (0x0000000FuL << RTC_MINUTES_SHIFT )
#define RTC_MASK_10_SECONDS        (0x00000007uL << RTC_10_SECONDS_SHIFT )
#define RTC_MASK_SECONDS           (0x0000000FuL << RTC_SECONDS_SHIFT )
#define RTC_MASK_100_MILISECONDS    (0x0000000FuL << RTC_100_MILISECONDS_SHIFT )
#define RTC_MASK_10_MILISECONDS     (0x0000000FuL << RTC_10_MILISECONDS_SHIFT )
#define RTC_MASK_MILISECONDS        (0x0000000FuL << RTC_MILISECONDS_SHIFT )

/*time format*/
#define RTC_HOUR12 1
#define RTC_HOUR24 0

//bool RTCSync ();
void RTC_WDT_Init();
void CallBackCounter();

uint64_t RTCGetUnixTime(void);
uint32_t RTCgetRecentMs(void);
uint32_t RTCSynced(void);
uint64_t RTCgetTime(uint64_t timeFormat);
uint32_t RTCgetHours(uint64_t readTime);
uint32_t RTCgetMinutes(uint64_t readTime);
uint32_t RTCgetSecond(uint64_t readTime);
uint32_t RTCgetMiliecond(uint64_t readTime);
void RTCSync(uint32_t unixTime, uint16_t resentMs);

extern uint16_t msRTC; 
extern uint32_t RTCSyncWithDS;
/* [] END OF FILE */
