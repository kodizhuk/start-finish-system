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
#include "rtc_fat.h"
#include "diskio.h"
#include "ff.h"

/*---------------------------------------------------------*/
/* User Provided RTC Function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support an RTC.                     */
/* This function is not required in read-only cfg.         */
#include <RTC.h>

static uint32_t rtcYear = 2016;
static uint32_t rtcMonth = 7;
static uint32_t rtcDay = 31;
static uint32_t rtcHour = 21;
static uint32_t rtcMinutes = 15;
static uint32_t rtcSeconds = 1;
static uint32_t rtcTime;
static uint32_t rtcDate;


DWORD get_fattime()
{
	rtcTime = RTC_GetTime();
    rtcDate = RTC_GetDate();
    rtcYear = RTC_GetYear(rtcDate);
    rtcMonth = RTC_GetMonth(rtcDate);
    rtcDay = RTC_GetDay(rtcDate);
    if(RTC_GetAmPm(rtcTime) == RTC_AM)
    {
        rtcHour = RTC_GetHours(rtcTime);
    }else
    {
        rtcHour = RTC_GetHours(rtcTime)+12;
    }
    rtcMinutes = RTC_GetMinutes(rtcTime);
    rtcSeconds = RTC_GetSecond(rtcTime);
    /* Pack date and time into a DWORD variable */
	return (((DWORD)rtcYear - 1980) << 25) | ((DWORD)rtcMonth << 21) | ((DWORD)rtcDay << 16)| (WORD)(rtcHour << 11)| 
            (WORD)(rtcMinutes << 5)	| (WORD)(rtcSeconds >> 1);
}

/* [] END OF FILE */
