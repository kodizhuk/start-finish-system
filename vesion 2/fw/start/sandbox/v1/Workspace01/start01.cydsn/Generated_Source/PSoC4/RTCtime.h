/***************************************************************************//**
* \file Name: RTCtime.h
* \version 1.10
*
* \brief
*  This file provides constants and parameter values for the RTC_P4 Component.
*
********************************************************************************
* Copyright 2015-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_RTC_P4_RTCtime_H)
#define CY_RTC_P4_RTCtime_H

#include <cytypes.h>
#include <CyLib.h>


/*******************************************************************************
*    Data types definition
*******************************************************************************/

typedef enum
{
    RTCtime_DST_DATE_RELATIVE = 0u,
    RTCtime_DST_DATE_FIXED = 1u
}RTCtime_DST_DATETYPE_ENUM;

/**
* \addtogroup group_structures
* @{
*/

/**
* This is the data structure that is used to save the current time and date 
* (RTC_currentTimeDate), and Alarm time and date (RTC_alarmCfgTimeDate).
*/
typedef struct
{
    uint32 time;
    uint32 date;
    uint32 dayOfWeek;
    uint32 status;
}RTCtime_DATE_TIME;

/**
* This is the data structure that is used to save time and date values for 
* Daylight Savings Time Start and Stop (RTC_dstTimeDateStart and 
* RTC_dstTimeDateStop).
*/
typedef struct
{
    uint32 hour;
    uint32 dayOfWeek;
    uint32 dayOfMonth;
    uint32 weekOfMonth;
    uint32 month;
    uint8  timeFormat;
}RTCtime_DST_TIME;

/** @} structures */

/*******************************************************************************
*    Enumerated Types and Parameters
*******************************************************************************/
/* Time Format setting constants */
#define RTCtime__HOUR_12 1
#define RTCtime__HOUR_24 0

/*  Date Format setting constants */
#define RTCtime__MM_DD_YYYY 0
#define RTCtime__DD_MM_YYYY 1
#define RTCtime__YYYY_MM_DD 2

/* Date Type setting constants */
#define RTCtime__RELATIVE 0
#define RTCtime__FIXED 1

/* DST Hour setting constants */
#define RTCtime__H0000 0
#define RTCtime__H0100 1
#define RTCtime__H0200 2
#define RTCtime__H0300 3
#define RTCtime__H0400 4
#define RTCtime__H0500 5
#define RTCtime__H0600 6
#define RTCtime__H0700 7
#define RTCtime__H0800 8
#define RTCtime__H0900 9
#define RTCtime__H1000 10
#define RTCtime__H1100 11
#define RTCtime__H1200 12
#define RTCtime__H1300 13
#define RTCtime__H1400 14
#define RTCtime__H1500 15
#define RTCtime__H1600 16
#define RTCtime__H1700 17
#define RTCtime__H1800 18
#define RTCtime__H1900 19
#define RTCtime__H2000 20
#define RTCtime__H2100 21
#define RTCtime__H2200 22
#define RTCtime__H2300 23

/* DST DayOfWeek setting constants */
#define RTCtime__SUNDAY 1
#define RTCtime__MONDAY 2
#define RTCtime__TUESDAY 3
#define RTCtime__WEDNESDAY 4
#define RTCtime__THURSDAY 5
#define RTCtime__FRIDAY 6
#define RTCtime__SATURDAY 7

/* DST Month setting constants */
#define RTCtime__JAN 1
#define RTCtime__FEB 2
#define RTCtime__MAR 3
#define RTCtime__APR 4
#define RTCtime__MAY 5
#define RTCtime__JUN 6
#define RTCtime__JUL 7
#define RTCtime__AUG 8
#define RTCtime__SEP 9
#define RTCtime__OCT 10
#define RTCtime__NOV 11
#define RTCtime__DEC 12

/* DST WeekOfMonth setting constants */
#define RTCtime__FIRST 1
#define RTCtime__SECOND 2
#define RTCtime__THIRD 3
#define RTCtime__FOURTH 4
#define RTCtime__FIFTH 5
#define RTCtime__LAST 6


#define RTCtime_INITIAL_DATA_FORMAT     (0u)
#define RTCtime_INITIAL_TIME_FORMAT     (1u)
#define RTCtime_INITIAL_UPDATE_MODE     (0u)
#define RTCtime_INITIAL_SECOND          (42u)
#define RTCtime_INITIAL_MINUTE          (23u)
#define RTCtime_INITIAL_HOUR            (18u)
#define RTCtime_INITIAL_DAY             (6u)
#define RTCtime_INITIAL_MONTH           (7u)
#define RTCtime_INITIAL_YEAR            (2016u)

#define RTCtime_INITIAL_ALARM_STATUS    (0u)

#define RTCtime_INITIAL_DST_STATUS      (0u)
#define RTCtime_INITIAL_DST_DATE_TYPE   (0u)
#define RTCtime_INITIAL_DST_START_MONTH (3uL)
#define RTCtime_INITIAL_DST_START_WOM   (6uL)
#define RTCtime_INITIAL_DST_START_DOM   (22uL)
#define RTCtime_INITIAL_DST_START_DOW   (1uL)
#define RTCtime_INITIAL_DST_START_HRS   (0uL)
#define RTCtime_INITIAL_DST_STOP_MONTH  (10uL)
#define RTCtime_INITIAL_DST_STOP_DOM    (22uL)
#define RTCtime_INITIAL_DST_STOP_DOW    (1uL)
#define RTCtime_INITIAL_DST_STOP_WOM    (6uL)
#define RTCtime_INITIAL_DST_STOP_HRS    (0uL)

/* Day of week definitions */
#define RTCtime_SUNDAY     (RTCtime__SUNDAY)
#define RTCtime_MONDAY     (RTCtime__MONDAY)
#define RTCtime_TUESDAY    (RTCtime__TUESDAY)
#define RTCtime_WEDNESDAY  (RTCtime__WEDNESDAY)
#define RTCtime_THURSDAY   (RTCtime__THURSDAY)
#define RTCtime_FRIDAY     (RTCtime__FRIDAY)
#define RTCtime_SATURDAY   (RTCtime__SATURDAY)

/* DST WeekOfMonth setting constants definitions */
#define RTCtime_FIRST      (RTCtime__FIRST)
#define RTCtime_SECOND     (RTCtime__SECOND)
#define RTCtime_THIRD      (RTCtime__THIRD)
#define RTCtime_FOURTH     (RTCtime__FOURTH)
#define RTCtime_FIFTH      (RTCtime__FIFTH)
#define RTCtime_LAST       (RTCtime__LAST)

/* Month definitions */
#define RTCtime_JANUARY    (RTCtime__JAN)
#define RTCtime_FEBRUARY   (RTCtime__FEB)
#define RTCtime_MARCH      (RTCtime__MAR)
#define RTCtime_APRIL      (RTCtime__APR)
#define RTCtime_MAY        (RTCtime__MAY)
#define RTCtime_JUNE       (RTCtime__JUN)
#define RTCtime_JULY       (RTCtime__JUL)
#define RTCtime_AUGUST     (RTCtime__AUG)
#define RTCtime_SEPTEMBER  (RTCtime__SEP)
#define RTCtime_OCTOBER    (RTCtime__OCT)
#define RTCtime_NOVEMBER   (RTCtime__NOV)
#define RTCtime_DECEMBER   (RTCtime__DEC)

#define RTCtime_DAYS_PER_WEEK       (7u)

/* Number of days in month definitions */
#define RTCtime_DAYS_IN_JANUARY     (31u)
#define RTCtime_DAYS_IN_FEBRUARY    (28u)
#define RTCtime_DAYS_IN_MARCH       (31u)
#define RTCtime_DAYS_IN_APRIL       (30u)
#define RTCtime_DAYS_IN_MAY         (31u)
#define RTCtime_DAYS_IN_JUNE        (30u)
#define RTCtime_DAYS_IN_JULY        (31u)
#define RTCtime_DAYS_IN_AUGUST      (31u)
#define RTCtime_DAYS_IN_SEPTEMBER   (30u)
#define RTCtime_DAYS_IN_OCTOBER     (31u)
#define RTCtime_DAYS_IN_NOVEMBER    (30u)
#define RTCtime_DAYS_IN_DECEMBER    (31u)

#define RTCtime_MONTHS_PER_YEAR     (12uL)

#define RTCtime_HOURS_PER_DAY       (24uL)
#define RTCtime_HOURS_PER_HALF_DAY  (12uL)

#define RTCtime_SECONDS_PER_MINUTE  (60uL)
#define RTCtime_SECONDS_PER_HOUR    (3600uL)
#define RTCtime_SECONDS_PER_DAY     (24uL * 3600uL)

#define RTCtime_SECONDS_PER_LEAP_YEAR    (366uL * 24uL * 3600uL)
#define RTCtime_SECONDS_PER_NONLEAP_YEAR (365uL * 24uL * 3600uL)

#define RTCtime_UNIX_TIME_PM   ((12uL * 3600uL) + 1uL)

/* AM/PM status definitions */
#define RTCtime_AM                 (0u)
#define RTCtime_PM                 (1u)

/* Time format definitions */
#define RTCtime_12_HOURS_FORMAT    (RTCtime__HOUR_12)
#define RTCtime_24_HOURS_FORMAT    (RTCtime__HOUR_24)

/* UNIX time begins in 1970 year.  */
#define RTCtime_YEAR_0             (1970u)

/* Definition of date register fields */
#if(RTCtime_INITIAL_DATA_FORMAT == RTCtime__MM_DD_YYYY)
    #define RTCtime_10_MONTH_OFFSET   (28u)
    #define RTCtime_MONTH_OFFSET      (24u)
    #define RTCtime_10_DAY_OFFSET     (20u)
    #define RTCtime_DAY_OFFSET        (16u)
    #define RTCtime_1000_YEAR_OFFSET  (12u)
    #define RTCtime_100_YEAR_OFFSET   (8u)
    #define RTCtime_10_YEAR_OFFSET    (4u)
    #define RTCtime_YEAR_OFFSET       (0u)
#elif(RTCtime_INITIAL_DATA_FORMAT == RTCtime__DD_MM_YYYY)
    #define RTCtime_10_MONTH_OFFSET   (20u)
    #define RTCtime_MONTH_OFFSET      (16u)
    #define RTCtime_10_DAY_OFFSET     (28u)
    #define RTCtime_DAY_OFFSET        (24u)
    #define RTCtime_1000_YEAR_OFFSET  (12u)
    #define RTCtime_100_YEAR_OFFSET   (8u)
    #define RTCtime_10_YEAR_OFFSET    (4u)
    #define RTCtime_YEAR_OFFSET       (0u)
#else
    #define RTCtime_10_MONTH_OFFSET   (12u)
    #define RTCtime_MONTH_OFFSET      (8u)
    #define RTCtime_10_DAY_OFFSET     (4u)
    #define RTCtime_DAY_OFFSET        (0u)
    #define RTCtime_1000_YEAR_OFFSET  (28u)
    #define RTCtime_100_YEAR_OFFSET   (24u)
    #define RTCtime_10_YEAR_OFFSET    (20u)
    #define RTCtime_YEAR_OFFSET       (16u)
#endif /* (RTCtime_INITIAL_DATA_FORMAT == RTCtime__MM_DD_YYYY) */

#define RTCtime_10_MONTH_MASK          (0x00000001uL << RTCtime_10_MONTH_OFFSET)
#define RTCtime_MONTH_MASK             (0x0000000FuL << RTCtime_MONTH_OFFSET)
#define RTCtime_10_DAY_MASK            (0x00000003uL << RTCtime_10_DAY_OFFSET)
#define RTCtime_DAY_MASK               (0x0000000FuL << RTCtime_DAY_OFFSET)
#define RTCtime_1000_YEAR_MASK         (0x00000003uL << RTCtime_1000_YEAR_OFFSET)
#define RTCtime_100_YEAR_MASK          (0x0000000FuL << RTCtime_100_YEAR_OFFSET)
#define RTCtime_10_YEAR_MASK           (0x0000000FuL << RTCtime_10_YEAR_OFFSET)
#define RTCtime_YEAR_MASK              (0x0000000FuL << RTCtime_YEAR_OFFSET)

#define  RTCtime_MONTH_FULL_MASK       (RTCtime_10_MONTH_MASK  | RTCtime_MONTH_MASK)
#define  RTCtime_DAY_FULL_MASK         (RTCtime_10_DAY_MASK    | RTCtime_DAY_MASK)
#define  RTCtime_YEAR_FULL_MASK        (RTCtime_1000_YEAR_MASK | RTCtime_100_YEAR_MASK |\
                                                 RTCtime_10_YEAR_MASK   | RTCtime_YEAR_MASK)


/* Definition of time register fields */
#define RTCtime_TIME_FORMAT_OFFSET     (23u)
#define RTCtime_PERIOD_OF_DAY_OFFSET   (22u)
#define RTCtime_10_HOURS_OFFSET        (20u)
#define RTCtime_HOURS_OFFSET           (16u)
#define RTCtime_10_MINUTES_OFFSET      (12u)
#define RTCtime_MINUTES_OFFSET         (8u)
#define RTCtime_10_SECONDS_OFFSET      (4u)
#define RTCtime_SECONDS_OFFSET         (0u)

#define RTCtime_TIME_FORMAT_MASK       (0x00000001uL << RTCtime_TIME_FORMAT_OFFSET)
#define RTCtime_PERIOD_OF_DAY_MASK     (0x00000001uL << RTCtime_PERIOD_OF_DAY_OFFSET)
#define RTCtime_10_HOURS_MASK          (0x00000003uL << RTCtime_10_HOURS_OFFSET)
#define RTCtime_HOURS_MASK             (0x0000000FuL << RTCtime_HOURS_OFFSET)
#define RTCtime_10_MINUTES_MASK        (0x00000007uL << RTCtime_10_MINUTES_OFFSET)
#define RTCtime_MINUTES_MASK           (0x0000000FuL << RTCtime_MINUTES_OFFSET)
#define RTCtime_10_SECONDS_MASK        (0x00000007uL << RTCtime_10_SECONDS_OFFSET)
#define RTCtime_SECONDS_MASK           (0x0000000FuL << RTCtime_SECONDS_OFFSET)

#define RTCtime_HOURS_FULL_MASK        (RTCtime_10_HOURS_MASK   | RTCtime_HOURS_MASK)
#define RTCtime_MINUTES_FULL_MASK      (RTCtime_10_MINUTES_MASK | RTCtime_MINUTES_MASK)
#define RTCtime_SECONDS_FULL_MASK      (RTCtime_10_SECONDS_MASK | RTCtime_SECONDS_MASK)

#define RTCtime_ALARM_SEC_MASK         (0x00000001uL)
#define RTCtime_ALARM_MIN_MASK         (0x00000002uL)
#define RTCtime_ALARM_HOUR_MASK        (0x00000004uL)
#define RTCtime_ALARM_DAYOFWEEK_MASK   (0x00000008uL)
#define RTCtime_ALARM_DAYOFMONTH_MASK  (0x00000010uL)
#define RTCtime_ALARM_MONTH_MASK       (0x00000020uL)
#define RTCtime_ALARM_YEAR_MASK        (0x00000040uL)

#define RTCtime_STATUS_DST_OFFSET      (1u)
#define RTCtime_STATUS_ALARM_OFFSET    (2u)
#define RTCtime_STATUS_LY_OFFSET       (3u)
#define RTCtime_STATUS_AM_PM_OFFSET    (4u)

/* Definition of the RTC status values. */
#define RTCtime_STATUS_DST             (1uL << RTCtime_STATUS_DST_OFFSET)
#define RTCtime_STATUS_LY              (1uL << RTCtime_STATUS_LY_OFFSET)
#define RTCtime_STATUS_AM_PM           (1uL << RTCtime_STATUS_AM_PM_OFFSET)

/* Number of bits per one BCD digit. */
#define RTCtime_BCD_NUMBER_SIZE        (4u)
#define RTCtime_BCD_ONE_DIGIT_MASK     (0x0000000FuL)

/*******************************************************************************
*    Function Prototypes
*******************************************************************************/
/**
* \addtogroup group_api
* @{
*/
void   RTCtime_Start(void);
void   RTCtime_Stop(void);
void   RTCtime_Init(void);
void   RTCtime_SetUnixTime(uint64 unixTime);
uint64 RTCtime_GetUnixTime(void);
void   RTCtime_SetPeriod(uint32 ticks, uint32 refOneSecTicks);
uint32 RTCtime_GetPeriod(void);
uint32 RTCtime_GetRefOneSec(void);
void   RTCtime_SetDateAndTime(uint32 inputTime, uint32 inputDate);
void   RTCtime_GetDateAndTime(RTCtime_DATE_TIME* dateTime);
uint32 RTCtime_GetTime(void);
uint32 RTCtime_GetDate(void);
void   RTCtime_SetAlarmDateAndTime(const RTCtime_DATE_TIME* alarmTime);
void   RTCtime_GetAlarmDateAndTime(RTCtime_DATE_TIME* alarmTimeDate);
void   RTCtime_SetAlarmMask(uint32 mask);
uint32 RTCtime_GetAlarmMask(void);
uint32 RTCtime_ReadStatus(void);
uint32 RTCtime_GetAlarmStatus(void);
void   RTCtime_ClearAlarmStatus(void);
void   RTCtime_SetDSTStartTime(const RTCtime_DST_TIME* dstStartTime,
                                              RTCtime_DST_DATETYPE_ENUM type);
void   RTCtime_SetDSTStopTime(const RTCtime_DST_TIME* dstStopTime,
                                             RTCtime_DST_DATETYPE_ENUM type);
uint32 RTCtime_ConvertBCDToDec(uint32 bcdNum);
uint32 RTCtime_ConvertDecToBCD(uint32 decNum);
void   RTCtime_Update(void);
void*  RTCtime_SetAlarmHandler(void (*CallbackFunction)(void));

static uint32 RTCtime_ConstructDate(uint32 month, uint32 day, uint32 year);
static uint32 RTCtime_ConstructTime(uint32 timeFormat, uint32 stateAmPm, uint32 hour, uint32 min, uint32 sec);
/** @} api */

static uint32 RTCtime_GetTimeFormat(uint32 inputTime);
static uint32 RTCtime_SetTimeFormat(uint32 inputTime, uint32 timeFormat);

/**
* \addtogroup group_api
* @{
*/
static uint32 RTCtime_LeapYear(uint32 year);
static uint32 RTCtime_IsBitSet(uint32 var, uint32 mask);
static uint32 RTCtime_GetSecond(uint32 inputTime);
static uint32 RTCtime_GetMinutes(uint32 inputTime);
static uint32 RTCtime_GetHours(uint32 inputTime);
static uint32 RTCtime_GetAmPm(uint32 inputTime);
static uint32 RTCtime_GetDay(uint32 date);
static uint32 RTCtime_GetMonth(uint32 date);
static uint32 RTCtime_GetYear(uint32 date);
/** @} api */

static uint32 RTCtime_SetSecond(uint32 inputTime, uint32 inputSecond);
static uint32 RTCtime_SetMinutes(uint32 inputTime, uint32 inputMinute);
static uint32 RTCtime_SetHours(uint32 inputTime, uint32 inputHours);
static uint32 RTCtime_SetAmPm(uint32 inputTime, uint32 periodOfDay);
static uint32 RTCtime_SetDay(uint32 inputDate, uint32 inputDay);
static uint32 RTCtime_SetMonth(uint32 inputDate, uint32 inputMonth);
static uint32 RTCtime_SetYear(uint32 inputDate, uint32 inputYear);

uint64 RTCtime_ConstructUnixAlarmTime(const RTCtime_DATE_TIME* alarmTime, uint8 alarmCfgMask);
uint64 RTCtime_GetDstUnixTime(const RTCtime_DST_TIME* dstTime);
uint64 RTCtime_GetNexAlarmTime(uint64 curUnixTime, uint8 alarmCfgMask);

static uint32 RTCtime_GetNextMinSec(uint32 curVal);
static uint32 RTCtime_GetNextHour(uint32 curVal);
static uint32 RTCtime_GetNextDay(uint32 curYear, uint32 curMonth, uint32 curDay, uint32 alarmCfgMask);
static uint32 RTCtime_GetNextMonth(uint32 curMonth);
static uint32 RTCtime_GetNextYear(uint32 curYear);
static uint32 RTCtime_GetDayOfWeek(uint32 day, uint32 month, uint32 year);

uint32 RTCtime_DaysInMonth(uint32 month, uint32 year);
uint32 RTCtime_DaysBeforeMonth(uint32 month, uint32 year);

/**
* \addtogroup group_api
* @{
*/
void   RTCtime_UnixToDateTime(RTCtime_DATE_TIME* dateTime, uint64 unixTime, uint32 timeFormat);
uint64 RTCtime_DateTimeToUnix(uint32 inputDate, uint32 inputTime);
/** @} api */

uint32 RTCtime_RelativeToFixed(uint32 dayOfWeek, uint32 weekOfMonth, uint32 month, uint32 year);


#if defined(CYDEV_RTC_SOURCE_WDT)
    #if((0u != CYDEV_WDT_GENERATE_ISR) && (0u == RTCtime_INITIAL_UPDATE_MODE))
        static void RTCtime_CySysRtcSetCallback(uint32 wdtNumber);
        static void RTCtime_CySysRtcResetCallback(uint32 wdtNumber);
    #endif /* ((0u != CYDEV_WDT_GENERATE_ISR) && (0u == RTCtime_INITIAL_UPDATE_MODE)) */
#endif /* (CYDEV_RTC_SOURCE_WDT) */

/*******************************************************************************
* Function Name: RTCtime_IsBitSet
****************************************************************************//**
*
* \brief
*  Checks the state of a bit passed through parameter.
*
* \param
*  var The variable to be checked.
* \param
*  mask The mask for a bit to be checked.
*
* \return
*  0u - Bit is not set.
* \return
*  1u - Bit is set.
*
*******************************************************************************/
static CY_INLINE uint32 RTCtime_IsBitSet(uint32 var, uint32 mask)
{
    return ((mask == (var & mask)) ? 1Lu : 0Lu);
}


/*******************************************************************************
* Function Name: RTCtime_LeapYear
****************************************************************************//**
*
* \brief
* Checks whether the year passed through the parameter is
* leap or no.
*
* \param
*  year The year to be checked.
*
*
* \return
*  0u - The year is not leap.
* \return
*  1u - The year is leap.
*
*******************************************************************************/
static CY_INLINE uint32 RTCtime_LeapYear(uint32 year)
{
    uint32 retVal;

    if(((0u == (year % 4Lu)) && (0u != (year % 100Lu))) || (0u == (year % 400Lu)))
    {
        retVal = 1uL;
    }
    else
    {
        retVal = 0uL;
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: RTCtime_GetSecond
****************************************************************************//**
*
* \brief
*  Returns the seconds value from the time value that is passed as a/the parameter.
*
* \param
*  time The time value.
*
* \return
*  The seconds value.
*
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetSecond(uint32 inputTime)
{
    uint32 retVal;

    retVal  = ((inputTime & RTCtime_10_SECONDS_MASK) >> RTCtime_10_SECONDS_OFFSET) * 10u;
    retVal += (inputTime & RTCtime_SECONDS_MASK) >> RTCtime_SECONDS_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: RTCtime_GetMinutes
****************************************************************************//**
*
* \brief
*  Returns the minutes value from the time value that is passed as a/the 
* parameter.
*
* \param
*  time The time value.
*
* \return
*  The minutes value.
*
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetMinutes(uint32 inputTime)
{
    uint32 retVal;

    retVal  = ((inputTime & RTCtime_10_MINUTES_MASK) >> RTCtime_10_MINUTES_OFFSET) * 10u;
    retVal += (inputTime & RTCtime_MINUTES_MASK) >> RTCtime_MINUTES_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: RTCtime_GetHours
****************************************************************************//**
*
* \brief
*  Returns the hours value from the time value that is passed as a/the parameter.
*
* \param
*  time The time value.
*
* \return
*  The hours value.
*
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetHours(uint32 inputTime)
{
    uint32 retVal;

    retVal  = ((inputTime & RTCtime_10_HOURS_MASK) >> RTCtime_10_HOURS_OFFSET) * 10u;
    retVal += (inputTime & RTCtime_HOURS_MASK) >> RTCtime_HOURS_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: RTCtime_GetAmPm
****************************************************************************//**
*
* \brief
*  Returns the AM/PM status from the time value that is passed as parameter.
*
* \param
*  time The time value.
*
* \return
*  RTCtime_AM - AM.
* \return
*  RTCtime_PM - PM.
*
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetAmPm(uint32 inputTime)
{
    return (RTCtime_IsBitSet(inputTime, RTCtime_PERIOD_OF_DAY_MASK));
}


/*******************************************************************************
* Function Name: RTCtime_GetDay
****************************************************************************//**
*
* \brief
*  Returns the day value from the date value that is passed as parameter.
*
* \param
*  date The date value.
*
* \return
*  The day value.
*
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetDay(uint32 date)
{
    uint32 retVal;

    retVal  = ((date & RTCtime_10_DAY_MASK) >> RTCtime_10_DAY_OFFSET) * 10u;
    retVal += (date & RTCtime_DAY_MASK) >> RTCtime_DAY_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: RTCtime_GetMonth
****************************************************************************//**
*
* \brief
*  Returns the month value from the date value that is passed as parameter.
*
* \param
*  date The date value.
*
* \return
*  The month value.
*
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetMonth(uint32 date)
{
    uint32 retVal;

    retVal  = ((date & RTCtime_10_MONTH_MASK) >> RTCtime_10_MONTH_OFFSET) * 10u;
    retVal += (date & RTCtime_MONTH_MASK) >> RTCtime_MONTH_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: RTCtime_GetYear
****************************************************************************//**
*
* \brief
*  Returns the year value from the date value that is passed as parameter.
*
* \param
*  date The date value.
*
* \return
*  The year value.
*
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetYear(uint32 date)
{
    uint32 retVal;

    retVal  = ((date & RTCtime_1000_YEAR_MASK) >> RTCtime_1000_YEAR_OFFSET) * 1000u;
    retVal += ((date & RTCtime_100_YEAR_MASK) >> RTCtime_100_YEAR_OFFSET) * 100u;
    retVal += ((date & RTCtime_10_YEAR_MASK) >> RTCtime_10_YEAR_OFFSET) * 10u;
    retVal += (date & RTCtime_YEAR_MASK) >> RTCtime_YEAR_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: RTCtime_SetSecond
****************************************************************************//**
*\internal
* \brief
*  Updates the time with the new second value.
*
* \param
* time The current date.
* \param
* second The seconds value to be set to the time variable.
*
* \return
*  The updated time variable.
*\endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_SetSecond(uint32 inputTime, uint32 inputSecond)
{
    inputTime &= ~(RTCtime_SECONDS_FULL_MASK);

    inputTime |= (inputSecond / 10u) << RTCtime_10_SECONDS_OFFSET;
    inputTime |= (inputSecond % 10u) << RTCtime_SECONDS_OFFSET;

    return(inputTime);
}


/*******************************************************************************
* Function Name: RTCtime_SetMinutes
****************************************************************************//**
*\internal
* \brief
*  Updates the time with the new minute value.
*
* \param
*  time The current date.
* \param
*  minutes The minutes value to be set to the time variable.
*
* \return
*  The updated time variable.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_SetMinutes(uint32 inputTime, uint32 inputMinute)
{
    inputTime &= ~(RTCtime_MINUTES_FULL_MASK);

    inputTime |= (inputMinute / 10u) << RTCtime_10_MINUTES_OFFSET;
    inputTime |= (inputMinute % 10u) << RTCtime_MINUTES_OFFSET;

    return(inputTime);
}


/*******************************************************************************
* Function Name: RTCtime_SetHours
****************************************************************************//**
*\internal
* \brief
*  Updates the time with the new hour value.
*
* \param
* time The current date.
* \param
* hours The hours value to be set to the time variable.
*
* \return
*  The updated time variable.
*\endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_SetHours(uint32 inputTime, uint32 inputHours)
{
    inputTime &= ~(RTCtime_HOURS_FULL_MASK);

    inputTime |= (inputHours / 10u) << RTCtime_10_HOURS_OFFSET;
    inputTime |= (inputHours % 10u) << RTCtime_HOURS_OFFSET;

    return(inputTime);
}


/*******************************************************************************
* Function Name: RTCtime_SetAmPm
****************************************************************************//**
*\internal
* \brief
*  Updates the time variable with the AmPm status.
*
* \param
* time The current date.
* \param
* periodOfDay The AmPm status to be set to the time variable.
*
* \return
*  The updated time variable.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_SetAmPm(uint32 inputTime, uint32 periodOfDay)
{
    if(0u != periodOfDay)
    {
        inputTime &= ~(RTCtime_PERIOD_OF_DAY_MASK);
    }
    else
    {
        inputTime |= RTCtime_PERIOD_OF_DAY_MASK;
    }

    return(inputTime);
}


/*******************************************************************************
* Function Name: RTCtime_SetDay
****************************************************************************//**
*\internal
* \brief
*  Updates the date variable with the new day value.
*
* \param
* date The current date.
* \param
* day The month to be set to the date variable.
*
* \return
*  The updated date variable.
*\endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_SetDay(uint32 inputDate, uint32 inputDay)
{
    inputDate &= ~(RTCtime_DAY_FULL_MASK);

    inputDate |= (inputDay / 10u) << RTCtime_10_DAY_OFFSET;
    inputDate |= (inputDay % 10u) << RTCtime_DAY_OFFSET;

    return(inputDate);
}


/*******************************************************************************
* Function Name: RTCtime_SetMonth
****************************************************************************//**
*\internal
* \brief
*  Updates the date variable with the new month value.
*
* \param
* date The current date.
* \param
* month The month that to be set to the date variable.
*
* \return
*  The updated date variable.
*\endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_SetMonth(uint32 inputDate, uint32 inputMonth)
{
    inputDate &= ~(RTCtime_MONTH_FULL_MASK);

    inputDate |= (inputMonth / 10u) << RTCtime_10_MONTH_OFFSET;
    inputDate |= (inputMonth % 10u) << RTCtime_MONTH_OFFSET;

    return(inputDate);
}


/*******************************************************************************
* Function Name: RTCtime_SetYear
****************************************************************************//**
*\internal
* \brief
*  Updates the date variable with the new year value.
*
* \param
* date The current date.
* \param
* year The year to be set to the date variable.
*
* \return
* The updated date variable.
*\endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_SetYear(uint32 inputDate, uint32 inputYear)
{
    inputDate  &= ~(RTCtime_YEAR_FULL_MASK);

    inputDate |= (inputYear / 1000u) << RTCtime_1000_YEAR_OFFSET;
    inputYear %= 1000u;

    inputDate |= (inputYear / 100u) << RTCtime_100_YEAR_OFFSET;
    inputYear %= 100u;

    inputDate |= (inputYear / 10u) << RTCtime_10_YEAR_OFFSET;
    inputDate |= (inputYear % 10u) << RTCtime_YEAR_OFFSET;

    return(inputDate);
}


/*******************************************************************************
* Function Name: RTCtime_GetNextMinSec
****************************************************************************//**
*\internal
* \brief
* This is an internal function that calculates the value of the next Second/Minute
* that follows after the current Minute/Second.
*
* \param
* curVal The current Second/Minute value.
*
* \return
* Returns the Second/Minute which follows after the current Second/Minute.
*\endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetNextMinSec(uint32 curVal)
{
    return((curVal < 59u) ? (curVal + 1u) : 0u);
}


/*******************************************************************************
* Function Name: RTCtime_GetNextHour
****************************************************************************//**
*\internal
* \brief
*  This is an internal function that calculates the value of the next Hour
*  that follows after the current Hour.
*
* \param
* curVal The current Hour value.
*
* \return
*  Returns the Hour which follows after the current Hour.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetNextHour(uint32 curVal)
{
    return((curVal < 23u) ? (curVal + 1u) : 0u);
}


/*******************************************************************************
* Function Name: RTCtime_GetNextDay
****************************************************************************//**
* \internal
* \brief
*  This is an internal function that calculates the value of the next Day
*  that follows after the current Day.
*
* \param
*  curYear The current year.
* \param
*  curMonth The current month.
* \param
*  curDay The current day.
* \param
*  alarmCfgMask Alarm Config Mask.
*
* \return
*  Returns the day which follows after the current Day.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetNextDay(uint32 curYear, uint32 curMonth, uint32 curDay, uint32 alarmCfgMask)
{
    uint32 daysInMonth;
    uint32 tmpVal;

    daysInMonth = RTCtime_DaysInMonth(curMonth, curYear);

    if(0u != (alarmCfgMask & RTCtime_ALARM_DAYOFWEEK_MASK))
    {
        tmpVal = curDay + RTCtime_DAYS_PER_WEEK;
        tmpVal = (tmpVal > daysInMonth) ? (tmpVal - daysInMonth) : tmpVal;
    }
    else
    {
        tmpVal = (curDay < daysInMonth) ? (curDay + 1u) : 1u;
    }

    return(tmpVal);
}


/*******************************************************************************
* Function Name: RTCtime_GetNextMonth
****************************************************************************//**
* \internal
* \brief
*  This is an internal function that calculates the value of the next month
*  that follows after the current month.
*
* \param
*  curMonth The current month.
*
* \return
*  Returns the month which follows after the current month.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetNextMonth(uint32 curMonth)
{
    return((curMonth < 12u) ? (curMonth + 1u) : 1u);
}


/*******************************************************************************
* Function Name: RTCtime_GetNextYear
****************************************************************************//**
* \internal
* \brief
*  This is an internal function that calculates the value of the next year
*  that follows after the current year.
*
* \param
*  curYear The current year.
*
* \return
*  Returns the year which follows after the current year.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetNextYear(uint32 curYear)
{
    return(curYear + 1u);
}


/*******************************************************************************
* Function Name: RTCtime_SetTimeFormat
****************************************************************************//**
* \internal
* \brief
*  Updates the "Time Format" value in the variable that contains time in the
*  "HH:MM:SS" format.
*
* \param
*  inputTime The current value of the time in the "HH:MM:SS" format.
*
* \return
*  Returns the updated value of the time in the "HH:MM:SS" format.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_SetTimeFormat(uint32 inputTime, uint32 timeFormat)
{
    inputTime &= ~(RTCtime_TIME_FORMAT_MASK);

    if((uint32)RTCtime_12_HOURS_FORMAT != timeFormat)
    {
        inputTime |= RTCtime_TIME_FORMAT_MASK;
    }

    return(inputTime);
}


/*******************************************************************************
* Function Name: RTCtime_GetTimeFormat
****************************************************************************//**
* \internal
* \brief
*  Reads the time format from the variable that contains time in the
*  "HH:MM:SS" format.
*
* \param
*  inputTime The current value of the time in the "HH:MM:SS" format.
*
* \return
*  Returns the time format that is stored in the variable that contains time
*  in the "HH:MM:SS" format.
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetTimeFormat(uint32 inputTime)
{
    return ((0uL != (inputTime & (1uL << RTCtime_TIME_FORMAT_OFFSET))) ? (uint32)RTCtime_12_HOURS_FORMAT :
                                                                                  (uint32)RTCtime_24_HOURS_FORMAT);
}


/*******************************************************************************
* Function Name: RTCtime_ConstructTime
****************************************************************************//**
*
* \brief
*  Returns the time in the format used in APIs from individual elements
*  passed (hour, min, sec etc)
*
* \param
* timeFormat The 12/24 hours time format <br>
* RTCtime_24_HOURS_FORMAT - The 24 hours format. <br>
* RTCtime_12_HOURS_FORMAT - The 12 hours format.
*
* \param
* stateAmPm  The AM/PM status <br>
* RTCtime_AM - AM. <br>
* RTCtime_PM - PM.
*
* \param
*  hour The hour.
*
* \param
*  min The minute.
*
* \param
*  sec The second.
*
* \return
*  Time in the format used in API.
*
*******************************************************************************/
static CY_INLINE uint32 RTCtime_ConstructTime(uint32 timeFormat, uint32 stateAmPm, uint32 hour, uint32 min, uint32 sec)
{
    uint32 retVal;

    retVal  = timeFormat << RTCtime_TIME_FORMAT_OFFSET;
    retVal |= stateAmPm << RTCtime_PERIOD_OF_DAY_OFFSET;

    retVal |= (hour / 10u) << RTCtime_10_HOURS_OFFSET;
    retVal |= (hour % 10u) << RTCtime_HOURS_OFFSET;

    retVal |= (min / 10u) << RTCtime_10_MINUTES_OFFSET;
    retVal |= (min % 10u) << RTCtime_MINUTES_OFFSET;

    retVal |= (sec / 10u) << RTCtime_10_SECONDS_OFFSET;
    retVal |= (sec % 10u) << RTCtime_SECONDS_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: RTCtime_ConstructDate
****************************************************************************//**
*
* \brief
*  Returns the date in the format used in APIs from individual elements
*  passed (day. Month and year)
*
* \param
*  month The month.
*
* \param
*  day The day.
*
* \param
*  year The year.
*
* \return
*  The date in the format used in API.
*
*******************************************************************************/
static CY_INLINE uint32 RTCtime_ConstructDate(uint32 month, uint32 day, uint32 year)
{
    uint32 retVal;
    uint32 tmpVal = year;

    retVal  = (month / 10u) << RTCtime_10_MONTH_OFFSET;
    retVal |= (month % 10u) << RTCtime_MONTH_OFFSET;

    retVal |= (day / 10u) << RTCtime_10_DAY_OFFSET;
    retVal |= (day % 10u) << RTCtime_DAY_OFFSET;

    retVal |= (year / 1000u) << RTCtime_1000_YEAR_OFFSET;
    tmpVal %= 1000u;

    retVal |= (tmpVal / 100u) << RTCtime_100_YEAR_OFFSET;
    tmpVal %= 100u;

    retVal |= (tmpVal / 10u) << RTCtime_10_YEAR_OFFSET;
    retVal |= (tmpVal % 10u) << RTCtime_YEAR_OFFSET;

    return (retVal);
}


/*******************************************************************************
* Function Name: RTCtime_GetDayOfWeek
****************************************************************************//**
* \internal
*
* \brief
*  Returns a day of the week for a year, month, and day of month that are passed
*  through parameters. Zeller's congruence is used to calculate the day of
*  the week.
*
*  For the Georgian calendar, Zeller's congruence is:
*  h = (q + [13 * (m + 1)] + K + [K/4] + [J/4] - 2J) mod 7
*
*  h - The day of the week (0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday).
*  q - The day of the month.
*  m - The month (3 = March, 4 = April, 5 = May, ..., 14 = February)
*  K - The year of the century (year \mod 100).
*  J - The zero-based century (actually [year/100]) For example, the zero-based
*  centuries for 1995 and 2000 are 19 and 20 respectively (not to be
*  confused with the common ordinal century enumeration which indicates
*  20th for both cases).
*
* \note In this algorithm January and February are counted as months 13 and 14
* of the previous year.
*
* \param
*  day The day of the month(1..31)
*
* \param
*  month The month of the year
* RTCtime_JANUARY <br>
* RTCtime_FEBRUARY <br>
* RTCtime_MARCH <br>
* RTCtime_APRIL <br>
* RTCtime_MAY <br>
* RTCtime_JUNE <br>
* RTCtime_JULY <br>
* RTCtime_AUGUST <br>
* RTCtime_SEPTEMBER <br>
* RTCtime_OCTOBER <br>
* RTCtime_NOVEMBER <br>
* RTCtime_DECEMBER <br>
*
* \param
*  year The year value.
*
* \return
* Returns a day of the week
* RTCtime_SUNDAY <br>
* RTCtime_MONDAY <br>
* RTCtime_TUESDAY <br>
* RTCtime_WEDNESDAY <br>
* RTCtime_THURSDAY <br>
* RTCtime_FRIDAY <br>
* RTCtime_SATURDAY <br>
*
* \endinternal
*******************************************************************************/
static CY_INLINE uint32 RTCtime_GetDayOfWeek(uint32 day, uint32 month, uint32 year)
{
    uint32 retVal;

    /* Converts month number from regular convention
     * (1=January,..., 12=December) to convention required for this
     * algorithm(January and February are counted as months 13 and 14 of
     * previous year).
    */
    if(month < (uint32)RTCtime_MARCH)
    {
        month = 12u + month;
        year--;
    }

    /* Calculates Day of Week using Zeller's congruence algorithms.
    */
    retVal = (day + (((month + 1u) * 26u) / 10u) + year + (year / 4u) + (6u * (year / 100u)) + (year / 400u)) % 7u;

    /* Makes correction for Saturday. Saturday number should be 7 instead of 0. */
    if(0u == retVal)
    {
        retVal = (uint32)RTCtime_SATURDAY;
    }

    return(retVal);
}


#if defined(CYDEV_RTC_SOURCE_WDT)
    #if((0u != CYDEV_WDT_GENERATE_ISR) && (0u == RTCtime_INITIAL_UPDATE_MODE))

        /*******************************************************************************
        * Function Name: RTCtime_CySysRtcSetCallback
        ****************************************************************************//**
        * \internal
        * \brief
        *  This is an internal function that registers a callback for the
        *  RTCtime_Update() function by address "0".
        *
        * \param
        *  wdtNumber The number of the WDT or WCO timer to be used to pull the
        *  RTCtime_Update() function.
        *
        *  The callback registered before by address "0" is replaced
        *  by the RTCtime_Update() function.
        * \endinternal
        *******************************************************************************/
        static CY_INLINE void RTCtime_CySysRtcSetCallback(uint32 wdtNumber)
        {
            #if((0u != CY_IP_WCO_WDT_EN) && (0u != CY_IP_SRSSLT))
                (void)CySysTimerSetInterruptCallback(wdtNumber, RTCtime_Update);
            #else
                (void)CySysWdtSetIsrCallback(wdtNumber, RTCtime_Update);
            #endif /* ((0u != CY_IP_WCO_WDT_EN) && (0u != CY_IP_SRSSLT)) */
        }


        /*******************************************************************************
        * Function Name: RTCtime_CySysRtcResetCallback
        ****************************************************************************//**
        * \internal
        * \brief
        *  This is an internal function that clears a callback by address "0".
        *
        * \param
        *  wdtNumber The number of the WDT or WCO timer to be cleared callback for.
        *
        *  The callback registered before by address "0" is replaced
        *  by the NULL pointer.
        * \endinternal
        *******************************************************************************/
        static CY_INLINE void RTCtime_CySysRtcResetCallback(uint32 wdtNumber)
        {
            #if((0u != CY_IP_WCO_WDT_EN) && (0u != CY_IP_SRSSLT))
                (void)CySysTimerSetInterruptCallback(wdtNumber, (void *)0);
            #else
                (void)CySysWdtSetIsrCallback(wdtNumber, (void *)0);
            #endif /* ((0u != CY_IP_WCO_WDT_EN) && (0u != CY_IP_SRSSLT)) */
        }

    #endif /* ((0u != CYDEV_WDT_GENERATE_ISR) && (0u == RTCtime_INITIAL_UPDATE_MODE)) */
#endif /* (CYDEV_RTC_SOURCE_WDT) */

/*******************************************************************************
*    External Variables
*******************************************************************************/

/**
* \addtogroup group_globals
* @{
*/

/**
* Indicates whether the RTC has been initialized; The variable is initialized to
* 0 and set to 1 the first time RTC_Start() is called. This allows the component
* to restart without reinitialization after the first call to the RTC_Start() 
* routine.
*/
extern uint8  RTCtime_initVar;

/** The DST start/stop status */
extern uint8  RTCtime_dstStatus;

/**
* The uint64 variable represents the standard Unix time (number of seconds 
* elapsed from January 1, 1970 00:00 hours UTC) in 64-bit 
*/
extern volatile uint64 RTCtime_unixTime;

/** The values for the time and date of the DST start */
extern RTCtime_DST_TIME RTCtime_dstStartTime;

/** The values for the time and date of the DST stop */
extern RTCtime_DST_TIME RTCtime_dstStopTime;

/**
* The last updated time and date values are stored in this structure (update 
* happens in Get time/date APIs)
*/
extern RTCtime_DATE_TIME RTCtime_currentTimeDate;

/** The alarm time and date values are stored in this variable */
extern RTCtime_DATE_TIME RTCtime_alarmCfgTimeDate;

/**
* This variable is used to mask alarm events; mask seconds alarm, mask minutes 
* alarm, and so on. It will have bit masks for each time item masking that item 
* for alarm generation
*/
extern uint32  RTCtime_alarmCfgMask;

/**
* This variable is used to indicate current active alarm status per time item 
* used in the alarm; whether seconds alarm is active, minute's alarm is active, 
* and so on. It will have bit masks for each time item (seconds, minutes, hours,
* day, and so on) showing the status
*/
extern uint32 RTCtime_alarmCurStatus;

/** @} globals */

extern void (*RTCtime_alarmCallbackPtr)(void);

extern const uint16 RTCtime_daysBeforeMonthTbl[RTCtime_MONTHS_PER_YEAR];
extern const uint8  RTCtime_daysInMonthTbl[RTCtime_MONTHS_PER_YEAR];


#endif /* CY_RTC_P4_RTCtime_H */

/* [] END OF FILE */
