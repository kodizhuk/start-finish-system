/***************************************************************************//**
* \file Name: RTCtime.c
* \version 1.10
*
* \brief
*  This file provides the source code to the API for the RTC_P4 Component.
*
********************************************************************************
* \copyright
* Copyright 2015-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RTCtime.h"

uint8  RTCtime_initVar;

volatile uint64 RTCtime_unixTime;
RTCtime_DATE_TIME RTCtime_currentTimeDate;

static uint32 RTCtime_updateTimePeriod;
static uint32 RTCtime_tickRefOneSec;

uint8  RTCtime_dstStatus;
static uint32 RTCtime_dstTimeOffset;
#if(0u != RTCtime_INITIAL_DST_STATUS)
    static volatile uint64 RTCtime_unixTimeDstStart;
    static volatile uint64 RTCtime_unixTimeDstStop;
    RTCtime_DST_TIME RTCtime_dstStartTime;
    RTCtime_DST_TIME RTCtime_dstStopTime;
#endif /* (0u != RTCtime_INITIAL_DST_STATUS) */

uint32 RTCtime_alarmCurStatus;
#if(0u != RTCtime_INITIAL_ALARM_STATUS)
    uint32  RTCtime_alarmCfgMask = 0xFFu;
    static volatile uint64 RTCtime_unixTimeAlarm;
    RTCtime_DATE_TIME RTCtime_alarmCfgTimeDate;
    void (*RTCtime_alarmCallbackPtr)(void) = (void *)0;
#endif /* (0u != RTCtime_INITIAL_ALARM_STATUS) */

const uint16 RTCtime_daysBeforeMonthTbl[RTCtime_MONTHS_PER_YEAR] = {
                                                 (0u), /* JANUARY */
                                                 (0u + 31u), /* FEBRUARY */
                                                 (0u + 31u + 28u), /* MARCH */
                                                 (0u + 31u + 28u + 31u), /* APRIL */
                                                 (0u + 31u + 28u + 31u + 30u), /* MAY */
                                                 (0u + 31u + 28u + 31u + 30u + 31u), /* JUNE */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u), /* JULY */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u), /* AUGUST */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u + 31u), /* SEPTEMBER */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u + 31u + 30u), /* OCTOBER */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u + 31u + 30u + 31u), /* NOVEMBER */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u + 31u + 30u + 31u + 30u)}; /* DECEMBER */

const uint8 RTCtime_daysInMonthTbl[RTCtime_MONTHS_PER_YEAR] = {RTCtime_DAYS_IN_JANUARY,
                                                                                 RTCtime_DAYS_IN_FEBRUARY,
                                                                                 RTCtime_DAYS_IN_MARCH,
                                                                                 RTCtime_DAYS_IN_APRIL,
                                                                                 RTCtime_DAYS_IN_MAY,
                                                                                 RTCtime_DAYS_IN_JUNE,
                                                                                 RTCtime_DAYS_IN_JULY,
                                                                                 RTCtime_DAYS_IN_AUGUST,
                                                                                 RTCtime_DAYS_IN_SEPTEMBER,
                                                                                 RTCtime_DAYS_IN_OCTOBER,
                                                                                 RTCtime_DAYS_IN_NOVEMBER,
                                                                                 RTCtime_DAYS_IN_DECEMBER};


/*******************************************************************************
* Function Name: RTCtime_Start
****************************************************************************//**
*
* \brief
*  Performs all the required calculations for the time and date registers and
*  initializes the component along with the date and time selected in the
*  customizer. 
*
*  If "Implement RTC update manually" is disabled in the customizer
*  and if WDT or WCO timer is selected as a source in the clocks configuration 
*  window (low frequency clocks tab), attaches RTC_Update API to a corresponding
*  WDT's or WCO's ISR callback.
*
* \note "Implement RTC update manually" checkbox is available for PSoC 4200L / 
* PSoC 4100M / PSoC 4200M / PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4000S / PSoC 
* 4100S and Analog Coprocessor.
*
*******************************************************************************/
void RTCtime_Start(void)
{
    if(0u == RTCtime_initVar)
    {
        RTCtime_Init();
    }

    #if defined(CYDEV_RTC_SOURCE_WDT)
        #if((0u != CYDEV_WDT_GENERATE_ISR) && (0u == RTCtime_INITIAL_UPDATE_MODE))
            RTCtime_CySysRtcSetCallback(CYDEV_RTC_SOURCE_WDT);
        #endif /* ((0u != CYDEV_WDT_GENERATE_ISR) && (0u == RTCtime_INITIAL_UPDATE_MODE)) */
    #endif /* (CYDEV_RTC_SOURCE_WDT) */
}


/*******************************************************************************
* Function Name: RTCtime_Stop
****************************************************************************//**
*
* \brief
*  Stops the time and date updates.
*
*******************************************************************************/
void RTCtime_Stop(void)
{
    #if defined(CYDEV_RTC_SOURCE_WDT)
        #if((0u != CYDEV_WDT_GENERATE_ISR) && (0u == RTCtime_INITIAL_UPDATE_MODE))
            RTCtime_CySysRtcResetCallback(CYDEV_RTC_SOURCE_WDT);
        #endif /* ((0u != CYDEV_WDT_GENERATE_ISR) && (0u == RTCtime_INITIAL_UPDATE_MODE)) */
    #endif /* (CYDEV_RTC_SOURCE_WDT) */
}


/*******************************************************************************
* Function Name: RTCtime_Init
****************************************************************************//**
*
* \brief
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. 
*
* It is not necessary to call RTC_Init() because
*  RTC_Start() API calls this function and is the preferred method to begin
*  component operation.
*
*  All registers are set to values according to the customizer Configure
*  dialog. The default date value, if not set by the user before this function 
*  call, is 12:00:00 AM January 1, 2000.
*
*******************************************************************************/
void RTCtime_Init(void)
{
    uint32 tmpDate;
    uint32 tmpTime;

    #if(0u != RTCtime_INITIAL_DST_STATUS)
        RTCtime_DST_TIME dstTimeTmp;
    #endif /* (0u != RTCtime_INITIAL_DST_STATUS) */

    RTCtime_initVar = 1u;
    RTCtime_dstTimeOffset = 0uL;
    RTCtime_currentTimeDate.status = 0uL;

    RTCtime_dstStatus      = RTCtime_INITIAL_DST_STATUS;
    RTCtime_alarmCurStatus = RTCtime_INITIAL_ALARM_STATUS;

    tmpDate = RTCtime_ConstructDate(RTCtime_INITIAL_MONTH,
                                          RTCtime_INITIAL_DAY,
                                          RTCtime_INITIAL_YEAR);

    tmpTime = RTCtime_ConstructTime(RTCtime_INITIAL_TIME_FORMAT,
                                          0u,
                                          RTCtime_INITIAL_HOUR,
                                          RTCtime_INITIAL_MINUTE,
                                          RTCtime_INITIAL_SECOND);

    #if(0u != RTCtime_INITIAL_DST_STATUS)
        RTCtime_dstStatus = 0u;
        RTCtime_currentTimeDate.status = (1uL << RTCtime_STATUS_DST_OFFSET);

        dstTimeTmp.timeFormat    = RTCtime_INITIAL_DST_DATE_TYPE;
        dstTimeTmp.hour          = RTCtime_INITIAL_DST_START_HRS;
        dstTimeTmp.dayOfWeek     = RTCtime_INITIAL_DST_START_DOW;
        dstTimeTmp.weekOfMonth   = RTCtime_INITIAL_DST_START_WOM;
        dstTimeTmp.dayOfMonth    = RTCtime_INITIAL_DST_START_DOM;
        dstTimeTmp.month         = RTCtime_INITIAL_DST_START_MONTH;
        RTCtime_SetDSTStartTime(&dstTimeTmp, (RTCtime_DST_DATETYPE_ENUM)RTCtime_INITIAL_DST_DATE_TYPE);

        dstTimeTmp.timeFormat    = RTCtime_INITIAL_DST_DATE_TYPE;
        dstTimeTmp.hour          = RTCtime_INITIAL_DST_STOP_HRS;
        dstTimeTmp.dayOfWeek     = RTCtime_INITIAL_DST_STOP_DOW;
        dstTimeTmp.weekOfMonth   = RTCtime_INITIAL_DST_STOP_WOM;
        dstTimeTmp.dayOfMonth    = RTCtime_INITIAL_DST_STOP_DOM;
        dstTimeTmp.month         = RTCtime_INITIAL_DST_STOP_MONTH;
        RTCtime_SetDSTStopTime(&dstTimeTmp, (RTCtime_DST_DATETYPE_ENUM)RTCtime_INITIAL_DST_DATE_TYPE);

        RTCtime_unixTimeDstStart = RTCtime_GetDstUnixTime(&RTCtime_dstStartTime);
        RTCtime_unixTimeDstStop  = RTCtime_GetDstUnixTime(&RTCtime_dstStopTime);

        if((RTCtime_unixTime >= RTCtime_unixTimeDstStart) &&
           (RTCtime_unixTime <= RTCtime_unixTimeDstStop))
        {
            RTCtime_dstStatus = 1u;
            RTCtime_dstTimeOffset = RTCtime_SECONDS_PER_HOUR;
        }
    #endif /* (0u != RTCtime_INITIAL_DST_STATUS) */

    RTCtime_SetDateAndTime(tmpTime, tmpDate);
}


/*******************************************************************************
* Function Name: RTCtime_SetDateAndTime
****************************************************************************//**
*
* \brief
* Sets the time and date values as the current time and date.
*
* \param
* inputTime The time value in the HH:MM:SS format. <br>
* "HH"- The 2nd 8-bit MSB that denotes the hour value.
* (0-23 for the 24-hour format and 1-12 for the 12-hour format. The MSB bit of the
* value denotes AM/PM for the 12-hour format (0-AM and 1-PM). <br>
* "MM" - The 3nd 8-bit MSB denotes the minutes value, the valid entries -> 0-59.<br>
* "SS" - The 8-bit LSB denotes the seconds value, the valid entries -> 0-59.
* Each byte is in the BCD format. Invalid time entries retain the
* previously set values.
*
* \param
*  inputDate The date value in the format selected in the customizer.
* For the MM/DD/YYYY format: <br>
* "MM" - The 8-bit MSB denotes the month value in BCD, the valid entries -> 1-12<br>
* "DD" - The 2nd 8-bit MSB denotes a day of the month value in BCD, the valid
* entries -> 1-31.<br>
* "YYYY" - The 16-bit LSB denotes a year in BCD, the valid entries -> 1900-2200.
* Each byte is in the BCD format. Invalid date entries retain the
* previously set values.
*
*******************************************************************************/
void RTCtime_SetDateAndTime(uint32 inputTime, uint32 inputDate)
{
    uint32 tmpDay;
    uint32 tmpMonth;
    uint32 tmpYear;

    tmpDay   = RTCtime_GetDay(inputDate);
    tmpMonth = RTCtime_GetMonth(inputDate);
    tmpYear  = RTCtime_GetYear(inputDate);

    RTCtime_unixTime = RTCtime_DateTimeToUnix(inputDate, inputTime);
    RTCtime_currentTimeDate.date = inputDate;
    RTCtime_currentTimeDate.time = inputTime;
    RTCtime_currentTimeDate.dayOfWeek = RTCtime_GetDayOfWeek(tmpDay, tmpMonth, tmpYear);

    #if(0u != RTCtime_INITIAL_DST_STATUS)
        RTCtime_unixTimeDstStart = RTCtime_GetDstUnixTime(&RTCtime_dstStartTime);
        RTCtime_unixTimeDstStop  = RTCtime_GetDstUnixTime(&RTCtime_dstStopTime);

        if((RTCtime_unixTime >= RTCtime_unixTimeDstStart) &&
           (RTCtime_unixTime <= RTCtime_unixTimeDstStop))
        {
            RTCtime_dstStatus = 1u;
            RTCtime_dstTimeOffset = RTCtime_SECONDS_PER_HOUR;
            RTCtime_unixTime -= RTCtime_dstTimeOffset;
        }
        else
        {
            RTCtime_dstStatus = 0u;
            RTCtime_dstTimeOffset = 0uL;
        }
    #endif /* (0u != RTCtime_INITIAL_DST_STATUS) */

    #if(0u != RTCtime_INITIAL_ALARM_STATUS)
        RTCtime_unixTimeAlarm = RTCtime_ConstructUnixAlarmTime(&RTCtime_alarmCfgTimeDate,
                                                                                 (uint8)RTCtime_alarmCfgMask);
    #endif /* (0u != RTCtime_INITIAL_ALARM_STATUS) */
}


/*******************************************************************************
* Function Name: RTCtime_SetUnixTime
****************************************************************************//**
*
* \brief
* Sets the time in the Unix/Epoch time format - the number of seconds elapsed 
*  from January 1, 1970 UTC 00:00 hrs.
*
* \param
*  time The time value in the Unix time/Epoch time format.
*
*******************************************************************************/
void RTCtime_SetUnixTime(uint64 unixTime)
{
    RTCtime_DATE_TIME tmpDateTime;

    RTCtime_unixTime = unixTime;
    RTCtime_UnixToDateTime(&tmpDateTime, unixTime, (uint32)RTCtime_24_HOURS_FORMAT);

    #if(0u != RTCtime_INITIAL_DST_STATUS)
        RTCtime_unixTimeDstStart = RTCtime_GetDstUnixTime(&RTCtime_dstStartTime);
        RTCtime_unixTimeDstStop  = RTCtime_GetDstUnixTime(&RTCtime_dstStopTime);

        if((RTCtime_unixTime >= RTCtime_unixTimeDstStart) &&
           (RTCtime_unixTime <= RTCtime_unixTimeDstStop))
        {
            RTCtime_dstStatus = 1u;
            RTCtime_dstTimeOffset = RTCtime_SECONDS_PER_HOUR;
        }
        else
        {
            RTCtime_dstStatus = 0u;
            RTCtime_dstTimeOffset = 0uL;
        }
    #endif /* (0u != RTCtime_INITIAL_DST_STATUS) */
}


/*******************************************************************************
* Function Name: RTCtime_GetUnixTime
****************************************************************************//**
*
* \brief
*  Returns the time in the Unix/Epoch time format - the number of seconds 
* elapsed from January 1, 1970 UTC 00:00 hrs.
*
* \return time The time value in the Unix time/Epoch time format.
*
*******************************************************************************/
uint64 RTCtime_GetUnixTime(void)
{
    return (RTCtime_unixTime);
}


/*******************************************************************************
* Function Name: RTCtime_SetPeriod
****************************************************************************//**
*
* \brief
*  Sets the RTC time update API period.
*
*  The user needs to pass the period as
*  a number of ticks and also a reference number of ticks taken by the same clock
*  source for one second. For instance, for a 32 kHz clock source and RTC
*  period of 100 ms, the "ticks" value is 3200 and the "refOneSecTicks" value
*  is 32000. This value is used to increment the time every time
*  RTCtime_Update() API is called.
*
* \param
*  ticks The clock period taken as a number of ticks.
*
* \param
* refOneSecTicks The reference number of ticks taken by the same clock source
*  for one second (the input clock frequency in Hz).
*
*******************************************************************************/
void RTCtime_SetPeriod(uint32 ticks, uint32 refOneSecTicks)
{
    RTCtime_updateTimePeriod = ticks;
    RTCtime_tickRefOneSec    = refOneSecTicks;
}


/*******************************************************************************
* Function Name: RTCtime_SetPeriod
****************************************************************************//**
*
* \brief
*  Gets the RTC time update API period.
*
* \return period The clock period taken as a number of ticks.
*
*******************************************************************************/
uint32 RTCtime_GetPeriod(void)
{
    return(RTCtime_updateTimePeriod);
}


/*******************************************************************************
* Function Name: RTCtime_GetRefOneSec
****************************************************************************//**
* \brief
* Gets the RTC time update API period.
*
* \return
* period The reference number of ticks taken by the RTC clock source for one
* second.
*
*******************************************************************************/
uint32 RTCtime_GetRefOneSec(void)
{
    return(RTCtime_tickRefOneSec);
}


/*******************************************************************************
* Function Name: RTCtime_GetDateAndTime
****************************************************************************//**
*
* Reads the current time and date.
*
* \param dateTime The pointer to the RTC_date_time structure to which time and 
* date is returned.
*
*******************************************************************************/
void RTCtime_GetDateAndTime(RTCtime_DATE_TIME* dateTime)
{
    RTCtime_UnixToDateTime(dateTime, (RTCtime_unixTime  + RTCtime_dstTimeOffset),
                                                                            RTCtime_INITIAL_TIME_FORMAT);
}


/*******************************************************************************
* Function Name: RTCtime_GetTime
****************************************************************************//**
* \brief
* Reads the current time.
*
* \return
* date The value of date in the user selected format. The date value is 
* available in the BCD format.
*
* \warning
*  Using RTCtime_GetTime and RTC_GetDate API separately might result
*  in errors when the time wraps around the end of the day. To avoid this,
*  use RTCtime_GetDateAndTime API.
*
*******************************************************************************/
uint32 RTCtime_GetTime(void)
{
    RTCtime_UnixToDateTime(&RTCtime_currentTimeDate,
                                    (RTCtime_unixTime  + RTCtime_dstTimeOffset),
                                     RTCtime_INITIAL_TIME_FORMAT);

    return(RTCtime_currentTimeDate.time);
}


/*******************************************************************************
* Function Name: RTCtime_GetDate
****************************************************************************//**
*
* \brief Reads the current time.
*
* \return
* time The time value in the format selected by the user (12/24 hr);
* The time value is available in the BCD format.
*
* \note
*  Using RTCtime_GetTime and RTCtime_GetDate API separately
*  might result in errors when the time wraps around the end of the day. To
*  avoid this, use RTCtime_GetDateAndTime API.
*
*******************************************************************************/
uint32 RTCtime_GetDate(void)
{
    RTCtime_UnixToDateTime(&RTCtime_currentTimeDate,
                                    (RTCtime_unixTime  + RTCtime_dstTimeOffset),
                                     RTCtime_INITIAL_TIME_FORMAT);

    return(RTCtime_currentTimeDate.date);
}


#if(0u != RTCtime_INITIAL_ALARM_STATUS)
    /*******************************************************************************
    * Function Name: RTCtime_SetAlarmDateAndTime
    ****************************************************************************//**
    *
    * \brief
    *  Writes the time and date values as the current alarm time and date.
    *
    * \param
    *  alarmTime The pointer to the RTCtime_date_time global structure where
    *  new values of the alarm time and date are stored.
    *
    * \note
    *  Invalid time entries are written with "00:00:00:00" for the 24-hour format and
    *  "AM 12:00:00:00" for the 12-hour format. Invalid date entries are written with
    *  a date equivalent to 01-JAN-2000.
    *
    *******************************************************************************/
    void RTCtime_SetAlarmDateAndTime(const RTCtime_DATE_TIME* alarmTime)
    {
        RTCtime_alarmCfgTimeDate = *alarmTime;
        RTCtime_unixTimeAlarm = RTCtime_ConstructUnixAlarmTime(alarmTime, (uint8)RTCtime_alarmCfgMask);
    }


    /*******************************************************************************
    * Function Name: RTCtime_GetAlarmDateAndTime
    ****************************************************************************//**
    *
    * \brief
    *  Reads the current alarm time and date.
    *
    * \param
    *  alarmTimeDate The pointer to the RTCtime_date_time structure to which
    *  the alarm date and time are returned.
    *
    *******************************************************************************/
    void RTCtime_GetAlarmDateAndTime(RTCtime_DATE_TIME* alarmTimeDate)
    {
        *alarmTimeDate = RTCtime_alarmCfgTimeDate;
    }


    /*******************************************************************************
    * Function Name: RTCtime_SetAlarmMask
    ****************************************************************************//**
    *
    * \brief
    *  Writes the Alarm Mask software register with one bit per time/date entry.
    *  The alarm is true when all masked time/date values match the Alarm values.
    *  Generated only if the alarm functionality is enabled.
    *
    * \param
    *  mask The Alarm Mask software register value. The values shown below can be
    *  OR'ed and passed as an argument as well.
    * \param
    *  RTCtime_ALARM_SEC_MASK The second alarm mask allows
    *  matching the alarm second register with the current second register.
    * \param
    *  RTCtime_ALARM_MIN_MASK The minute alarm mask allows matching the
    *  alarm minute register with the current minute register.
    * \param
    *  RTCtime_ALARM_HOUR_MASK The hour alarm mask allows
    * matching the alarm hour register with the current hour register.
    * \param
    *  RTCtime_ALARM_DAYOFWEEK_MASK The day of the week alarm mask 
    * allows matching the alarm day of the week register with the current day of
    * the week register.
    * \param
    * RTCtime_ALARM_DAYOFMONTH_MASK The day of the month alarm mask
    * allows matching the alarm day of the month register with the current day 
    * of the month register.
    * \param
    * RTCtime_ALARM_MONTH_MASK The month alarm mask allows matching 
    * the alarm month register with the current month register.
    * \param
    * RTCtime_ALARM_YEAR_MASK The year alarm mask allows matching the
    *  alarm year register with the current year register.
    *
    *******************************************************************************/
    void RTCtime_SetAlarmMask(uint32 mask)
    {
        RTCtime_alarmCfgMask = (uint8)mask;
        RTCtime_unixTimeAlarm = RTCtime_ConstructUnixAlarmTime(&RTCtime_alarmCfgTimeDate, (uint8)mask);
    }


    /*******************************************************************************
    * Function Name: RTCtime_GetAlarmMask
    ****************************************************************************//**
    *
    * \brief
    *  Reads the Alarm Mask software register. Generated only if the alarm 
    * functionality is enabled.
    *
    * \return
    *  The Alarm Mask value with each bit representing the status of the alarm 
    * time/date match enable.
    *
    * \return
    *  RTCtime_ALARM_SEC_MASK - The second alarm mask allows matching the
    * alarm second register with the current second register.
    *
    * \return
    * RTCtime_ALARM_MIN_MASK - The minute alarm mask allows matching the 
    * alarm minute register with the current minute register.
    *
    * \return
    *  RTCtime_ALARM_HOUR_MASK - The hour alarm mask allows matching the 
    * alarm hour register with the current hour register.
    *
    * \return
    *  RTCtime_ALARM_DAYOFWEEK_MASK - The day of the week alarm mask allows
    * matching the alarm day of the week register with the current day of the 
    * week register.
    *
    * \return
    *  RTCtime_ALARM_DAYOFMONTH_MASK - The day of the month alarm mask 
    * allows matching the alarm day of the month register with the current day of 
    * the month register.
    *
    * \return
    *  RTCtime_ALARM_MONTH_MASK - The month alarm mask allows matching 
    * the alarm month register with the current month register.
    *
    * \return
    *  RTCtime_ALARM_YEAR_MASK - The year alarm mask allows matching the
    * alarm year register with the current year register.
    *
    *******************************************************************************/
    uint32 RTCtime_GetAlarmMask(void)
    {
        return((uint32)RTCtime_alarmCfgMask);
    }


    /*******************************************************************************
    * Function Name: RTCtime_GetAlarmStatus
    ****************************************************************************//**
    *
    * \brief
    *  Returns the alarm status of RTC.
    *
    * \return
    *  The Alarm active status. This bit is high when the current time and date match the alarm
    *  time and date.
    *
    * \return
    *  0 - The Alarm status is not active.
    * \return
    *  1 - The Alarm status is active.
    *
    *******************************************************************************/
    uint32 RTCtime_GetAlarmStatus(void)
    {
        return((0uL != (RTCtime_currentTimeDate.status & (1uL << RTCtime_STATUS_ALARM_OFFSET))) ? 1uL : 0uL);
    }


    /*******************************************************************************
    * Function Name: RTCtime_ClearAlarmStatus
    ****************************************************************************//**
    *
    * \brief
    *  Clears the alarm status of RTC.
    *
    * \note
    * The Alarm active (AA) flag clears after read. This bit will be set in the next
    * alarm match event only. If Alarm is set on only minutes and the alarm
    * minutes is 20 minutes - the alarm triggers once every 20th minute of
    * every hour.
    *
    *******************************************************************************/
    void RTCtime_ClearAlarmStatus(void)
    {
        RTCtime_currentTimeDate.status &= (~(1uL << RTCtime_STATUS_ALARM_OFFSET));
        RTCtime_alarmCurStatus = 0u;
    }


    /*******************************************************************************
    * Function Name: RTCtime_SetAlarmHandler
    ****************************************************************************//**
    *
    * \brief
    *  This API sets the function to be called when the alarm goes off / triggers.
    *  This API is generated only if the alarm functionality is enabled in the
    *  customizer.
    *
    * \param
    *  CallbackFunction The callback function address.
    *
    * \return
    *  A previous callback function address.
    *
    *******************************************************************************/
    void* RTCtime_SetAlarmHandler(void (*CallbackFunction)(void))
    {
        void (*tmpCallbackPtr)(void);

        tmpCallbackPtr = RTCtime_alarmCallbackPtr;
        RTCtime_alarmCallbackPtr = CallbackFunction;

        return((void*)tmpCallbackPtr);
    }


    /*******************************************************************************
    * Function Name: RTCtime_GetNexAlarmTime
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal function that calculates the time of the next alarm
    *  in the UNIX format taking into account the current "Alarm Config Mask".
    *
    * \param
    *  curUnixTime The current time value in the UNIX format.
    *
    * \param
    *  alarmCfgMask The current Alarm Config Mask.
    *
    * \return Returns time of the next alarm in the UNIX format.
    *
    *******************************************************************************/
    uint64 RTCtime_GetNexAlarmTime(uint64 curUnixTime, uint8 alarmCfgMask)
    {
        uint32 prevVal;
        uint32 nextVal;
        uint32 carryFlag;
        uint32 daysInMonth;
        RTCtime_DATE_TIME curDateTime;

        carryFlag = 1u;
        RTCtime_UnixToDateTime(&curDateTime, curUnixTime, (uint32)RTCtime_24_HOURS_FORMAT);

        /* Calculates Second value of next alarm time based on current time and Alarm Config Mask. */
        if(0uL != ((~((uint32)alarmCfgMask)) & RTCtime_ALARM_SEC_MASK))
        {
            prevVal = RTCtime_GetSecond(curDateTime.time);
            nextVal = RTCtime_GetNextMinSec(prevVal);
            curDateTime.time = RTCtime_SetSecond(curDateTime.time, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Minute value of next alarm time based on current time and Alarm Config Mask. */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & RTCtime_ALARM_MIN_MASK)))
        {
            prevVal = RTCtime_GetMinutes(curDateTime.time);
            nextVal = RTCtime_GetNextMinSec(prevVal);
            curDateTime.time = RTCtime_SetMinutes(curDateTime.time, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Hour value of next alarm time based on current time and Alarm Config Mask. */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & RTCtime_ALARM_HOUR_MASK)))
        {
            prevVal = RTCtime_GetHours(curDateTime.time);
            nextVal = RTCtime_GetNextHour(prevVal);
            curDateTime.time = RTCtime_SetHours(curDateTime.time, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Day value of next alarm time based on current time and Alarm Config Mask. */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & RTCtime_ALARM_DAYOFMONTH_MASK)))
        {
            prevVal = RTCtime_GetDay(curDateTime.date);
            if(0u != (alarmCfgMask & RTCtime_ALARM_DAYOFWEEK_MASK))
            {
                daysInMonth = RTCtime_DaysInMonth(RTCtime_GetMonth(curDateTime.date),
                                                           RTCtime_GetYear(curDateTime.date));
                nextVal = prevVal + RTCtime_DAYS_PER_WEEK;
                nextVal = (nextVal > daysInMonth) ? (nextVal - daysInMonth) : nextVal;
            }
            else
            {
                nextVal = RTCtime_GetNextDay(RTCtime_GetYear(curDateTime.date),
                                                      RTCtime_GetMonth(curDateTime.date),
                                                      RTCtime_GetDay(curDateTime.date),
                                                      (~((uint32)alarmCfgMask)));
            }
            curDateTime.date = RTCtime_SetDay(curDateTime.date, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Month value of next alarm time based on current time and Alarm Config Mask. */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & RTCtime_ALARM_MONTH_MASK)))
        {
            prevVal = RTCtime_GetMonth(curDateTime.date);
            nextVal = RTCtime_GetNextMonth(prevVal);
            curDateTime.date = RTCtime_SetMonth(curDateTime.date, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Year value of next alarm time based on current time and Alarm Config Mask. */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & RTCtime_ALARM_YEAR_MASK)))
        {
            prevVal = RTCtime_GetYear(curDateTime.date);
            nextVal = RTCtime_GetNextYear(prevVal);
            curDateTime.date = RTCtime_SetYear(curDateTime.date, nextVal);
        }

        return(RTCtime_DateTimeToUnix(curDateTime.date, curDateTime.time));
    }


    /*******************************************************************************
    * Function Name: RTCtime_ConstructUnixAlarmTime
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal function that calculates the time of the first alarm
    *  in the UNIX format taking into account the current "Alarm Config Mask".
    *
    * \param
    *  alarmTime Desired alarm time in the regular time format.
    *
    * \param
    *  alarmCfgMask The current Alarm Config Mask.
    *
    * \return
    *  time of the first alarm in the UNIX format.
    *
    *******************************************************************************/
    uint64 RTCtime_ConstructUnixAlarmTime(const RTCtime_DATE_TIME* alarmTime, uint8 alarmCfgMask)
    {
        uint32 tmpCurVal;
        uint32 tmpNextVal;
        uint32 carryFlag;
        uint32 tmpAlarmDate;
        uint32 tmpAlarmTime;
        uint32 daysInMonth;
        RTCtime_DATE_TIME curDateTime;

        tmpAlarmDate = 0u;
        tmpAlarmTime = 0u;
        RTCtime_UnixToDateTime(&curDateTime, RTCtime_unixTime, (uint32)RTCtime_24_HOURS_FORMAT);

        /* Calculates Seconds value of first Alarm based on current time and Alarm Config Mask. */
        tmpCurVal =  RTCtime_GetSecond(curDateTime.time);
        tmpNextVal = RTCtime_GetSecond(alarmTime->time);
        carryFlag = (tmpCurVal > tmpNextVal) ? 1u : 0u;
        if(0u != ((~((uint32)alarmCfgMask)) & RTCtime_ALARM_SEC_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? 0u : tmpCurVal;
        }
        tmpAlarmTime = RTCtime_SetSecond(tmpAlarmTime, tmpNextVal);

        /* Calculates Minutes value of first Alarm based on current time and Alarm Config Mask. */
        tmpCurVal  = RTCtime_GetMinutes(curDateTime.time);
        if(0u != ((~((uint32)alarmCfgMask)) & RTCtime_ALARM_MIN_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? RTCtime_GetNextMinSec(tmpCurVal) : tmpCurVal;
        }
        else
        {
            tmpNextVal = RTCtime_GetMinutes(alarmTime->time);
        }
        carryFlag  = (tmpNextVal < tmpCurVal) ? 1u : 0u;
        tmpAlarmTime =  RTCtime_SetMinutes(tmpAlarmTime, tmpNextVal);

        /* Calculates Hours value of first Alarm based on current time and Alarm Config Mask. */
        tmpCurVal  = RTCtime_GetHours(curDateTime.time);
        if(0u != ((~((uint32)alarmCfgMask)) & RTCtime_ALARM_HOUR_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? RTCtime_GetNextHour(tmpCurVal) : tmpCurVal;
        }
        else
        {
            tmpNextVal = RTCtime_GetHours(alarmTime->time);
            if((uint32)RTCtime_24_HOURS_FORMAT != RTCtime_GetTimeFormat(alarmTime->time))
            {
                if((uint32)RTCtime_AM != RTCtime_GetAmPm(alarmTime->time))
                {
                    tmpNextVal += RTCtime_HOURS_PER_HALF_DAY;
                }
            }
        }
        carryFlag  = (tmpNextVal < tmpCurVal) ? 1u : 0u;
        tmpAlarmTime =  RTCtime_SetHours(tmpAlarmTime, tmpNextVal);

        /* Calculates Day value of first Alarm based on current time and Alarm Config Mask. */
        tmpCurVal  = RTCtime_GetDay(curDateTime.date);
        tmpNextVal = RTCtime_GetDay(alarmTime->date);
        if(0u != ((~((uint32)alarmCfgMask)) & RTCtime_ALARM_DAYOFMONTH_MASK))
        {
            if(0u != (alarmCfgMask & RTCtime_ALARM_DAYOFWEEK_MASK))
            {
                daysInMonth = RTCtime_DaysInMonth(RTCtime_GetMonth(curDateTime.date),
                                                           RTCtime_GetYear(curDateTime.date));
                tmpNextVal = (curDateTime.dayOfWeek <= alarmTime->dayOfWeek) ? (alarmTime->dayOfWeek - curDateTime.dayOfWeek) :
                                ((RTCtime_DAYS_PER_WEEK - curDateTime.dayOfWeek) + alarmTime->dayOfWeek);
                tmpNextVal = tmpCurVal + tmpNextVal;
                tmpNextVal = (tmpNextVal > daysInMonth) ? (tmpNextVal - daysInMonth) : tmpNextVal;
            }
            else
            {
                tmpNextVal = (0u == carryFlag) ? tmpCurVal : RTCtime_GetNextDay(RTCtime_GetYear(curDateTime.date),
                                                              RTCtime_GetMonth(curDateTime.date),
                                                               tmpCurVal,
                                                              RTCtime_ALARM_DAYOFMONTH_MASK);
            }
        }
        carryFlag  = (tmpNextVal < tmpCurVal) ? 1u : 0u;
        tmpAlarmDate =  RTCtime_SetDay(tmpAlarmDate, tmpNextVal);

        /* Calculates Month value of first Alarm based on current time and Alarm Config Mask. */
        tmpCurVal  = RTCtime_GetMonth(curDateTime.date);
        if(0u != ((~((uint32)alarmCfgMask)) & RTCtime_ALARM_MONTH_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? RTCtime_GetNextMonth(tmpCurVal) : tmpCurVal;
        }
        else
        {
            tmpNextVal = RTCtime_GetMonth(alarmTime->date);
        }
        carryFlag  = (tmpNextVal < tmpCurVal) ? 1u : 0u;
        tmpAlarmDate =  RTCtime_SetMonth(tmpAlarmDate, tmpNextVal);

        /* Calculates Year value of first Alarm based on current time and Alarm Config Mask. */
        tmpCurVal  = RTCtime_GetYear(curDateTime.date);
        if(0u != ((~((uint32)alarmCfgMask)) & RTCtime_ALARM_MONTH_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? RTCtime_GetNextYear(tmpCurVal) : tmpCurVal;
        }
        else
        {
            tmpNextVal = RTCtime_GetYear(alarmTime->date);
        }
        tmpAlarmDate =  RTCtime_SetYear(tmpAlarmDate, tmpNextVal);

        return(RTCtime_DateTimeToUnix(tmpAlarmDate, tmpAlarmTime));
    }
#endif/* (0u != RTCtime_INITIAL_ALARM_STATUS) */


/*******************************************************************************
* Function Name: RTCtime_ReadStatus
****************************************************************************//**
*
* \brief
* Reads the Status software register, which has flags for DST (DST),
* Leap Year (LY), AM/PM (AM_PM).
*
* \return
* The values shown below are OR'ed and returned if more than one status
* bits are set.
*
* \return
* RTCtime_STATUS_DST - Status of Daylight Saving Time. This bit
* goes high when the current time and date match the DST time and date and the 
* time is incremented. This bit goes low after the DST interval and the time is 
* decremented.
*
* \return
* RTCtime_STATUS_LY - Status of Leap Year. This bit goes high when the 
* current year is a leap year.
*
* \return
* RTCtime_STATUS_AM_PM - Status of Current Time. This bit is low from 
* midnight to noon and high from noon to midnight.
*
* \note
* Reading the status without sync with the date and time read may cause an
* error due to a roll-over at AM/PM, the end of a year, the end of a day;
* RTCtime_GetDateAndTime() API is used to obtain the status and
* the status member of the returned structure can be checked with the masks.
*
*******************************************************************************/
uint32 RTCtime_ReadStatus(void)
{
    uint32 tmpYear;
    RTCtime_DATE_TIME tmpTimeDate;

    RTCtime_GetDateAndTime(&tmpTimeDate);
    tmpYear = RTCtime_GetYear(tmpTimeDate.date);

    if(0uL != RTCtime_LeapYear(tmpYear))
    {
        RTCtime_currentTimeDate.status |= (1uL << RTCtime_STATUS_LY_OFFSET);
    }
    else
    {
        RTCtime_currentTimeDate.status &= ~(1uL << RTCtime_STATUS_LY_OFFSET);
    }


    if(0uL != RTCtime_GetAmPm(tmpTimeDate.time))
    {
        RTCtime_currentTimeDate.status |= (1uL << RTCtime_STATUS_AM_PM_OFFSET);
    }
    else
    {
        RTCtime_currentTimeDate.status &= ~(1uL << RTCtime_STATUS_AM_PM_OFFSET);
    }

    return(RTCtime_currentTimeDate.status);
}


#if(0u != RTCtime_INITIAL_DST_STATUS)
    /*******************************************************************************
    * Function Name: RTCtime_SetDSTStartTime
    ****************************************************************************//**
    *
    * \brief
    *  Stores the DST Start time.
    *
    *  Only generated if DST is enabled. The date passed can be relative or fixed. 
    *  For a relative date, the user needs to provide a valid day of a week, a 
    *  week of a month and a month in the dstStartTime structure.
    *  For a fixed date, the user needs to enter a valid day of a month and a month in
    *  the dstStartTime structure. The hour value is optional and if invalid
    *  taken as 00 hrs. Invalid entries are not stored and the DST start date
    *  retains a previous value or no value at all.
    *
    * \param
    *  dstStartTime The DST Start time register value.
    *
    * \param
    *  type Defines the DST operation mode <br>
    *  DST_DATE_RELATIVE - The DST start time is relative. <br>
    *  DST_DATE_FIXED - The DST start time is fixed.
    *
    *******************************************************************************/
    void RTCtime_SetDSTStartTime(const RTCtime_DST_TIME* dstStartTime,
                                                RTCtime_DST_DATETYPE_ENUM type)
    {
        RTCtime_dstStartTime.timeFormat    = (uint8)type;
        RTCtime_dstStartTime.hour          = dstStartTime->hour;
        RTCtime_dstStartTime.dayOfWeek     = dstStartTime->dayOfWeek;
        RTCtime_dstStartTime.weekOfMonth   = dstStartTime->weekOfMonth;
        RTCtime_dstStartTime.dayOfMonth    = dstStartTime->dayOfMonth;
        RTCtime_dstStartTime.month         = dstStartTime->month;

        RTCtime_unixTimeDstStart = RTCtime_GetDstUnixTime(&RTCtime_dstStartTime);

        if((RTCtime_unixTime >= RTCtime_unixTimeDstStart) &&
           (RTCtime_unixTime <= RTCtime_unixTimeDstStop))
        {
            RTCtime_dstStatus = 1u;
            RTCtime_dstTimeOffset = RTCtime_SECONDS_PER_HOUR;
        }
        else
        {
            RTCtime_dstStatus = 0u;
            RTCtime_dstTimeOffset = 0uL;
        }
    }


    /*******************************************************************************
    * Function Name: RTCtime_SetDSTStopTime
    ****************************************************************************//**
    *
    * \brief
    *  Stores the DST Stop time.
    * 
    *  Only generated if DST is enabled. The date passed can be relative or fixed. 
    *  For a relative date, the user needs to provide a valid day of a week, a week 
    *  of a month and a month in the dstStopTime structure.
    *  For a fixed date, the user needs to enter a valid day of a month and a month in the
    *  dstSoptTime structure. The hour value is optional and if invalid taken
    *  as 00 hrs. Invalid entries are not stored and the DST start date retains
    *  a previous value or no value at all.
    *
    * \param
    *  dstStopTime DST Stop time register values.
    *
    * \param
    *  type Defines the DST operation mode <br>
    *  DST_DATE_RELATIVE - The DST start time is relative. <br>
    *  DST_DATE_FIXED - The DST start time is fixed.
    *
    *******************************************************************************/
    void RTCtime_SetDSTStopTime(const RTCtime_DST_TIME* dstStopTime,
                                               RTCtime_DST_DATETYPE_ENUM type)
    {

        RTCtime_dstStopTime.timeFormat  = (uint8)type;
        RTCtime_dstStopTime.hour           = dstStopTime->hour;
        RTCtime_dstStopTime.dayOfWeek      = dstStopTime->dayOfWeek;
        RTCtime_dstStopTime.weekOfMonth = dstStopTime->weekOfMonth;
        RTCtime_dstStopTime.dayOfMonth     = dstStopTime->dayOfMonth;
        RTCtime_dstStopTime.month         = dstStopTime->month;

        RTCtime_unixTimeDstStop  = RTCtime_GetDstUnixTime(&RTCtime_dstStopTime);

        if((RTCtime_unixTime >= RTCtime_unixTimeDstStart) &&
           (RTCtime_unixTime <= RTCtime_unixTimeDstStop))
        {
            RTCtime_dstStatus = 1u;
            RTCtime_dstTimeOffset = RTCtime_SECONDS_PER_HOUR;
        }
        else
        {
            RTCtime_dstStatus = 0u;
            RTCtime_dstTimeOffset = 0uL;
        }
    }


    /*******************************************************************************
    * Function Name: RTCtime_GetDstUnixTime
    ****************************************************************************//**
    *
    * \brief
    *  Calculates the DST Start/Stop time in the UNIX format.
    *
    * \param
    *  dstTime The DST Start/Stop time in the regular time format.
    *
    * \return
    *  The DST Start/Stop time in the UNIX format.
    *
    *******************************************************************************/
    uint64 RTCtime_GetDstUnixTime(const RTCtime_DST_TIME* dstTime)
    {
        uint32 tmpYear;
        uint32 tmpDate;
        uint64 dstUnixTime;

        RTCtime_DATE_TIME tmpTimeDate;

        RTCtime_UnixToDateTime(&tmpTimeDate, RTCtime_unixTime, RTCtime_INITIAL_TIME_FORMAT);
        tmpYear = RTCtime_GetYear(tmpTimeDate.date);

        if(dstTime->timeFormat == (uint8)RTCtime_DST_DATE_FIXED)
        {
            tmpDate =     RTCtime_ConstructDate(dstTime->month, dstTime->dayOfMonth, tmpYear);
        }
        else
        {
            tmpDate = RTCtime_RelativeToFixed(dstTime->dayOfWeek, dstTime->weekOfMonth, dstTime->month, tmpYear);
        }

        tmpTimeDate.time = RTCtime_ConstructTime((uint32)RTCtime_24_HOURS_FORMAT, 0u, dstTime->hour, 0u, 0u);
        dstUnixTime = RTCtime_DateTimeToUnix(tmpDate, tmpTimeDate.time);

        return(dstUnixTime);
    }


#endif /* (0u != RTCtime_INITIAL_DST_STATUS) */


/*******************************************************************************
* Function Name: RTCtime_ConvertBCDToDec
****************************************************************************//**
*
* \brief
*  Converts a 4-byte BCD number into a 4-byte hexadecimal number. Each byte is
*  converted individually and returned as an individual byte in the 32-bit
*  variable.
*
* \param
*  bcdNum A 4-byte BCD number. Each byte represents BCD.
*  0x11223344 -> 4 bytes 0x11, 0x22, 0x33 and 0x44 the in BCD format.
*
* \return
*  decNum A 4-byte hexadecimal equivalent number of the BCD number.
*  BCD number 0x11223344 -> returned hexadecimal number 0x0B16212C.
*
*******************************************************************************/
uint32 RTCtime_ConvertBCDToDec(uint32 bcdNum)
{
    uint32 i;
    uint32 mult;
    uint32 retVal;

    mult   = 1u;
    retVal = 0u;

    for(i = 0u; i < 16u; i++)
    {
        retVal += (bcdNum & RTCtime_BCD_ONE_DIGIT_MASK) * mult;
        bcdNum >>= RTCtime_BCD_NUMBER_SIZE;
        mult *= 10u;
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: RTCtime_ConvertDecToBCD
****************************************************************************//**
*
* \brief
*  Converts a 4-byte hexadecimal number into a 4-byte BCD number. Each byte
*  is converted individually and returned as an individual byte in the 32-bit
*  variable.
*
* \param 
*  decNum A 4-byte hexadecimal number. Each byte is represented in hex.
*  0x11223344 -> 4 bytes 0x11, 0x22, 0x33 and 0x44 in the hex format.
*
* \return
*  bcdNum - A 4-byte BCD equivalent of the passed hexadecimal number. Hexadecimal
*  number 0x11223344 -> returned BCD number 0x17345168.
*
*******************************************************************************/
uint32 RTCtime_ConvertDecToBCD(uint32 decNum)
{
    uint32 shift;
    uint32 tmpVal;
    uint32 retVal;

    shift  = 0u;
    retVal = 0u;
    tmpVal = decNum;

    do
    {
        retVal |= ((tmpVal % 10u) << shift);
        tmpVal /= 10u;
        shift  += RTCtime_BCD_NUMBER_SIZE;
    }
    while(tmpVal >= 10u);

    retVal |= (tmpVal << shift);

    return(retVal);
}


/*******************************************************************************
* Function Name: RTCtime_Update
****************************************************************************//**
*
* \brief
*  This API updates the time registers and performs alarm/DST check.
*
*  This function increments the time/date registers by an input clock period.
*  The period is set by RTC_SetPeriod() API or WDT period selected for RTC
*  in the clocks configuration window (low frequency clocks tab) interface
*  every time it is called.
*
*  API is automatically mapped to the WDT's callback slot and period if the
*  configuration is as follows: 1) Option "Implement RTC update manually" in
*  the customizer is unchecked 2) One of WDTs is selected in the "Use for RTC"
*  panel of the low frequency clocks tab 3) Option "Implementation by IDE" is
*  selected in the "Timer (WDT) ISR" panel.
*
*  If option "Implement RTC update manually" is checked in the customizer or
*  option "None" is selected in the "Use for RTC" panel,it is the user's
*  responsibility: 1) to call this API from the clock ISR to be
*  used as the RTC's input 2) set the period of the RTC through
*  RTC_SetPeriod() API.
*
* \note Updates the Unix time register, updates the alarm and DST status.
*
*******************************************************************************/
void RTCtime_Update(void)
{
    static volatile uint32 RTCtime_currentTickNumber;
    RTCtime_currentTickNumber += RTCtime_updateTimePeriod;

    if(RTCtime_currentTickNumber >= RTCtime_tickRefOneSec)
    {
        RTCtime_unixTime++;
        RTCtime_currentTickNumber = 0u;

    #if(0u != RTCtime_INITIAL_DST_STATUS)
        if(RTCtime_unixTime == RTCtime_unixTimeDstStart)
        {
            RTCtime_dstStatus = 1u;
            RTCtime_dstTimeOffset = RTCtime_SECONDS_PER_HOUR;
        }

        if(RTCtime_unixTime == (RTCtime_unixTimeDstStop  - RTCtime_dstTimeOffset))
        {
            RTCtime_dstStatus = 0u;
            RTCtime_dstTimeOffset = 0u;
            RTCtime_unixTimeDstStart = RTCtime_GetDstUnixTime(&RTCtime_dstStartTime);
            RTCtime_unixTimeDstStop  = RTCtime_GetDstUnixTime(&RTCtime_dstStopTime);
        }
    #endif /* (0u != RTCtime_INITIAL_DST_STATUS) */

    #if(0u != RTCtime_INITIAL_ALARM_STATUS)
        if((RTCtime_unixTime + RTCtime_dstTimeOffset) == RTCtime_unixTimeAlarm)
        {
            RTCtime_currentTimeDate.status |= (1uL << RTCtime_STATUS_ALARM_OFFSET);
            RTCtime_alarmCurStatus = RTCtime_alarmCfgMask;
            if (RTCtime_alarmCallbackPtr != (void *) 0)
            {
                RTCtime_alarmCallbackPtr();
            }
            RTCtime_unixTimeAlarm = RTCtime_GetNexAlarmTime(RTCtime_unixTime + RTCtime_dstTimeOffset,
                                                                                                  (uint8)RTCtime_alarmCfgMask);
        }
    #endif/* (0u != RTCtime_INITIAL_ALARM_STATUS) */
    }
}


/*******************************************************************************
* Function Name: RTCtime_DateTimeToUnix
****************************************************************************//**
*
* \brief
*  This is an internal function to convert the date and time from
*  the regular time format into the UNIX time format.
*
* \param
*  inputDate The date in the selected in the customizer "date format".
* \param
*  inputTime The time in the defined "time format".
*
* \return Returns the date and time in the UNIX format.
*
*******************************************************************************/
uint64 RTCtime_DateTimeToUnix(uint32 inputDate, uint32 inputTime)
{
    uint32 i;
    uint32 tmpYear;
    uint32 tmpMonth;
    uint32 tmpVal;
    uint64 unixTime;

    unixTime = 0u;
    tmpYear = RTCtime_GetYear(inputDate);

    /* Calculate seconds from epoch start up to (but not including) current year. */
    for(i = RTCtime_YEAR_0; i < tmpYear; i++)
    {
        if(0u != RTCtime_LeapYear(i))
        {
            unixTime += RTCtime_SECONDS_PER_LEAP_YEAR;
        }
        else
        {
            unixTime += RTCtime_SECONDS_PER_NONLEAP_YEAR;
        }
    }

    /* Calculates how many seconds had elapsed in this year prior to the current month. */
    tmpMonth = RTCtime_GetMonth(inputDate);
    tmpVal = RTCtime_daysBeforeMonthTbl[tmpMonth - 1u];

    if((tmpMonth > 2u) && (0u != RTCtime_LeapYear(tmpYear)))
    {
        tmpVal++;
    }

    /* Calculates how many seconds are in current month days prior to today. */
    unixTime += tmpVal * RTCtime_SECONDS_PER_DAY;
    unixTime += (RTCtime_GetDay(inputDate) - 1u) * RTCtime_SECONDS_PER_DAY;

    /* Calculates how many seconds have elapsed today up to the current hour. */
    tmpVal = RTCtime_GetHours(inputTime);
    if(((uint32)RTCtime_24_HOURS_FORMAT != RTCtime_GetTimeFormat(inputTime)) &&
       ((uint32)RTCtime_AM != RTCtime_GetAmPm(inputTime)) && (tmpVal < 12u))
    {
        tmpVal += RTCtime_HOURS_PER_HALF_DAY;
    }
    unixTime += tmpVal * RTCtime_SECONDS_PER_HOUR;

    /* Calculates how many seconds have elapsed today up to the current minute. */
    unixTime += RTCtime_GetMinutes(inputTime) * RTCtime_SECONDS_PER_MINUTE;

    /* Add remaining seconds of current minute. */
    unixTime += RTCtime_GetSecond(inputTime);

    return(unixTime);
}


/*******************************************************************************
* Function Name: RTCtime_UnixToDateTime
****************************************************************************//**
*
* \brief
*  This is an internal function to convert the date and time from
*  the UNIX time format into the regular time format.
*
* \param dayOfWeek A day of a week <br>
*                 RTCtime_SUNDAY <br>
*                 RTCtime_MONDAY <br>
*                 RTCtime_TUESDAY <br>
*                 RTCtime_WEDNESDAY <br>
*                 RTCtime_THURSDAY <br>
*                 RTCtime_FRIDAY <br>
*                 RTCtime_SATURDAY <br>
*
* \param weekOfMonth A week of a month <br>
*                 RTCtime_FIRST <br>
*                 RTCtime_SECOND <br>
*                 RTCtime_THIRD <br>
*                 RTCtime_FOURTH <br>
*                 RTCtime_LAST <br>
*
* \param month A month of a year <br>
*                   RTCtime_JANUARY <br>
*                  RTCtime_FEBRUARY <br>
*                  RTCtime_MARCH <br>
*                  RTCtime_APRIL <br>
*                  RTCtime_MAY <br>
*                  RTCtime_JUNE <br>
*                  RTCtime_JULY <br>
*                  RTCtime_AUGUST <br>
*                  RTCtime_SEPTEMBER <br>
*                  RTCtime_OCTOBER <br>
*                  RTCtime_NOVEMBER <br>
*                  RTCtime_DECEMBER <br>
*
* \param year A year value.
*
* \return A date in the "date format".
*
*******************************************************************************/
void RTCtime_UnixToDateTime(RTCtime_DATE_TIME* dateTime, uint64 unixTime, uint32 timeFormat)
{
    uint32 tmpMinute;
    uint32 tmpHour;
    uint32 tmpAmPmState;

    uint32 tmpDay;
    uint32 tmpMonth;
    uint32 tmpYear;

    uint32 tmpVar;

    tmpAmPmState = 0u;
    tmpYear = RTCtime_YEAR_0;
    tmpVar = RTCtime_SECONDS_PER_NONLEAP_YEAR;

    /* Calculates current year value. Variable tmpYear
    *  increments while it contains value greater than number
    *  of seconds in current year.
    */
    while(unixTime > tmpVar)
    {
        unixTime -= tmpVar;
        tmpYear++;

        if(0u != RTCtime_LeapYear(tmpYear))
        {
            tmpVar = RTCtime_SECONDS_PER_LEAP_YEAR;
        }
        else
        {
            tmpVar = RTCtime_SECONDS_PER_NONLEAP_YEAR;
        }

    }

    /* Calculates current month value. tmpMonth variable increments
     * while unixTime variable value is greater than time
     * interval from beginning of current year to beginning of
     * current month
    */
    tmpMonth = (uint32)RTCtime_JANUARY;
    tmpVar = RTCtime_DaysInMonth(tmpMonth, tmpYear) * RTCtime_SECONDS_PER_DAY;

    while(unixTime >= tmpVar)
    {
        unixTime -= tmpVar;
        tmpMonth++;
        tmpVar = RTCtime_DaysInMonth(tmpMonth, tmpYear) * RTCtime_SECONDS_PER_DAY;
    }

    /* Calculates current day value. */
    tmpDay = (unixTime / RTCtime_SECONDS_PER_DAY);
    tmpVar = tmpDay * RTCtime_SECONDS_PER_DAY;
    unixTime -= (unixTime >= tmpVar) ? tmpVar : 0u;
    tmpDay += 1u;

    /* Calculates current hour value. If function works in 12-Hour mode,
     * it converts time to 12-Hours mode and calculates AmPm status */
    tmpHour = unixTime / RTCtime_SECONDS_PER_HOUR;
    tmpVar  = tmpHour * RTCtime_SECONDS_PER_HOUR;
    if((uint32)RTCtime_24_HOURS_FORMAT != timeFormat)
    {
        if(unixTime > RTCtime_UNIX_TIME_PM)
        {
            tmpAmPmState = RTCtime_PM;
            tmpHour = (tmpHour > 12u) ? (tmpHour - 12u) : tmpHour;
        }
        else
        {
            tmpAmPmState = RTCtime_AM;
            tmpHour = (0u != tmpHour) ? tmpHour : 12u;
        }
    }
    unixTime -= (unixTime >= tmpVar) ? tmpVar : 0u;

    /* Calculates current minute.  */
    tmpMinute = unixTime / RTCtime_SECONDS_PER_MINUTE;
    tmpVar = tmpMinute * RTCtime_SECONDS_PER_MINUTE;

    /* Calculates current second. */
    unixTime -= (unixTime >= tmpVar) ? tmpVar : 0u;


    dateTime->date = RTCtime_ConstructDate(tmpMonth, tmpDay, tmpYear);
    dateTime->time = RTCtime_ConstructTime(timeFormat, tmpAmPmState, tmpHour, tmpMinute, unixTime);
    dateTime->dayOfWeek = RTCtime_GetDayOfWeek(tmpDay, tmpMonth, tmpYear);
}


/*******************************************************************************
* Function Name: RTCtime_RelativeToFixed
****************************************************************************//**
*
* \brief
* This is an internal function to convert a relative date into
* a fixed date.
*
* \param dayOfWeek A day of a week <br>
*                 RTCtime_SUNDAY <br>
*                 RTCtime_MONDAY <br>
*                 RTCtime_TUESDAY <br>
*                 RTCtime_WEDNESDAY <br>
*                 RTCtime_THURSDAY <br>
*                 RTCtime_FRIDAY <br>
*                 RTCtime_SATURDAY <br>
*
*  \param weekOfMonth A week of a month <br>
*                 RTCtime_FIRST <br>
*                 RTCtime_SECOND <br>
*                 RTCtime_THIRD <br>
*                 RTCtime_FOURTH <br>
*                 RTCtime_FIFTH <br>
*                 RTCtime_LAST <br>
*
* \param month A month of a year <br>
*                  RTCtime_JANUARY <br>
*                  RTCtime_FEBRUARY <br>
*                  RTCtime_MARCH <br>
*                  RTCtime_APRIL <br>
*                  RTCtime_MAY <br>
*                  RTCtime_JUNE <br>
*                  RTCtime_JULY <br>
*                  RTCtime_AUGUST <br>
*                  RTCtime_SEPTEMBER <br>
*                  RTCtime_OCTOBER <br>
*                  RTCtime_NOVEMBER <br>
*                  RTCtime_DECEMBER <br>
*
* \param year A year value.
*
* \return A date in the "date format".
*
*******************************************************************************/
uint32 RTCtime_RelativeToFixed(uint32 dayOfWeek, uint32 weekOfMonth, uint32 month, uint32 year)
{
    uint32 curDay;
    uint32 curWeek;
    uint32 daysInMonth;
    uint32 dayOfMonthTmp;

    uint32 retVal;

    curDay      = 1u;
    curWeek     = (uint32)RTCtime_FIRST;
    daysInMonth = RTCtime_DaysInMonth(month, year);
    dayOfMonthTmp = curDay;

    while((curWeek <= weekOfMonth) && (curDay <= daysInMonth))
    {
        if(dayOfWeek == RTCtime_GetDayOfWeek(curDay, month, year))
        {
            dayOfMonthTmp = curDay;
            curWeek++;
        }
        curDay++;
    }

    retVal = RTCtime_ConstructDate(month, dayOfMonthTmp, year);

    return(retVal);
}


/*******************************************************************************
* Function Name: RTCtime_DaysInMonth
****************************************************************************//**
*
* \brief
*  Returns a number of days in a month passed through the parameters.
*
* \param
*  month A month of a year
*  RTCtime_JANUARY
*  RTCtime_FEBRUARY
*  RTCtime_MARCH
*  RTCtime_APRIL
*  RTCtime_MAY
*  RTCtime_JUNE
*  RTCtime_JULY
*  RTCtime_AUGUST
*  RTCtime_SEPTEMBER
*  RTCtime_OCTOBER
*  RTCtime_NOVEMBER
*  RTCtime_DECEMBER
*
* \param
* year A year value.
*
* \return
*  A number of days in a month in the year passed through the parameters.
*
*******************************************************************************/
uint32 RTCtime_DaysInMonth(uint32 month, uint32 year)
{
    uint32 retVal;

    retVal = RTCtime_daysInMonthTbl[month - 1u];
    if((uint32)RTCtime_FEBRUARY == month)
    {
        if(0u != RTCtime_LeapYear(year))
        {
            retVal++;
        }
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: RTCtime_DaysBeforeMonth
****************************************************************************//**
*
* \brief
*  Calculates how many days elapsed from the beginning of the year to the
*  beginning of the current month.
*
* \param
*  month A month of a year
*  RTCtime_JANUARY
*  RTCtime_FEBRUARY
*  RTCtime_MARCH
*  RTCtime_APRIL
*  RTCtime_MAY
*  RTCtime_JUNE
*  RTCtime_JULY
*  RTCtime_AUGUST
*  RTCtime_SEPTEMBER
*  RTCtime_OCTOBER
*  RTCtime_NOVEMBER
*  RTCtime_DECEMBER
*
* \param
* year A year value.
*
* \return
*  A number of days elapsed from the beginning of the year to the
*  beginning of the current month passed through the parameters.
*
*******************************************************************************/
uint32 RTCtime_DaysBeforeMonth(uint32 month, uint32 year)
{
    uint32 retVal;

    retVal = RTCtime_daysBeforeMonthTbl[month];
    if((0u == RTCtime_LeapYear(year)) && (month > (uint32)RTCtime_FEBRUARY))
    {
        retVal++;
    }

    return(retVal);
}


/* [] END OF FILE */
