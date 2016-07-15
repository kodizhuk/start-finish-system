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
#include <stdbool.h>


#ifdef USE_WDT_RTC
    #include <WDT0_ISR.h>
    
    CY_ISR_PROTO(Wdt0_Handler);
#endif

/* Definition of time register fields */
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

void     RTCLib_Interrupt(void);
void     RTCLib_WDT_Init(void);
bool     RTCLibSync (void);
uint32_t RTCLib_getRecentMs(void);
uint64_t RTCLib_getTime(uint64_t timeFormat);

uint32_t RTCLib_getHours(uint64_t readTime);
uint32_t RTCLib_getMinutes(uint64_t readTime);
uint32_t RTCLib_getSecond(uint64_t readTime);
uint32_t RTCLib_getMiliecond(uint64_t readTime);


/* [] END OF FILE */
