/***************************************************************************//**
* \file Name: RTC2.c
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

#include "RTC2.h"

uint8  RTC2_initVar;

volatile uint64 RTC2_unixTime;
RTC2_DATE_TIME RTC2_currentTimeDate;

static uint32 RTC2_updateTimePeriod;
static uint32 RTC2_tickRefOneSec;

uint8  RTC2_dstStatus;
static uint32 RTC2_dstTimeOffset;
#if(0u != RTC2_INITIAL_DST_STATUS)
    static volatile uint64 RTC2_unixTimeDstStart;
    static volatile uint64 RTC2_unixTimeDstStop;
    RTC2_DST_TIME RTC2_dstStartTime;
    RTC2_DST_TIME RTC2_dstStopTime;
#endif /* (0u != RTC2_INITIAL_DST_STATUS) */

uint32 RTC2_alarmCurStatus;
#if(0u != RTC2_INITIAL_ALARM_STATUS)
    uint32  RTC2_alarmCfgMask = 0xFFu;
    static volatile uint64 RTC2_unixTimeAlarm;
    RTC2_DATE_TIME RTC2_alarmCfgTimeDate;
    void (*RTC2_alarmCallbackPtr)(void) = (void *)0;
#endif /* (0u != RTC2_INITIAL_ALARM_STATUS) */

const uint16 RTC2_daysBeforeMonthTbl[RTC2_MONTHS_PER_YEAR] = {
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

const uint8 RTC2_daysInMonthTbl[RTC2_MONTHS_PER_YEAR] = {RTC2_DAYS_IN_JANUARY,
                                                                                 RTC2_DAYS_IN_FEBRUARY,
                                                                                 RTC2_DAYS_IN_MARCH,
                                                                                 RTC2_DAYS_IN_APRIL,
                                                                                 RTC2_DAYS_IN_MAY,
                                                                                 RTC2_DAYS_IN_JUNE,
                                                                                 RTC2_DAYS_IN_JULY,
                                                                                 RTC2_DAYS_IN_AUGUST,
                                                                                 RTC2_DAYS_IN_SEPTEMBER,
                                                                                 RTC2_DAYS_IN_OCTOBER,
                                                                                 RTC2_DAYS_IN_NOVEMBER,
                                                                                 RTC2_DAYS_IN_DECEMBER};


/*******************************************************************************
* Function Name: RTC2_Start
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
void RTC2_Start(void)
{
    if(0u == RTC2_initVar)
    {
        RTC2_Init();
    }

    #if defined(CYDEV_RTC_SOURCE_WDT)
        #if((0u != CYDEV_WDT_GENERATE_ISR) && (0u == RTC2_INITIAL_UPDATE_MODE))
            RTC2_CySysRtcSetCallback(CYDEV_RTC_SOURCE_WDT);
        #endif /* ((0u != CYDEV_WDT_GENERATE_ISR) && (0u == RTC2_INITIAL_UPDATE_MODE)) */
    #endif /* (CYDEV_RTC_SOURCE_WDT) */
}


/*******************************************************************************
* Function Name: RTC2_Stop
****************************************************************************//**
*
* \brief
*  Stops the time and date updates.
*
*******************************************************************************/
void RTC2_Stop(void)
{
    #if defined(CYDEV_RTC_SOURCE_WDT)
        #if((0u != CYDEV_WDT_GENERATE_ISR) && (0u == RTC2_INITIAL_UPDATE_MODE))
            RTC2_CySysRtcResetCallback(CYDEV_RTC_SOURCE_WDT);
        #endif /* ((0u != CYDEV_WDT_GENERATE_ISR) && (0u == RTC2_INITIAL_UPDATE_MODE)) */
    #endif /* (CYDEV_RTC_SOURCE_WDT) */
}


/*******************************************************************************
* Function Name: RTC2_Init
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
void RTC2_Init(void)
{
    uint32 tmpDate;
    uint32 tmpTime;

    #if(0u != RTC2_INITIAL_DST_STATUS)
        RTC2_DST_TIME dstTimeTmp;
    #endif /* (0u != RTC2_INITIAL_DST_STATUS) */

    RTC2_initVar = 1u;
    RTC2_dstTimeOffset = 0uL;
    RTC2_currentTimeDate.status = 0uL;

    RTC2_dstStatus      = RTC2_INITIAL_DST_STATUS;
    RTC2_alarmCurStatus = RTC2_INITIAL_ALARM_STATUS;

    tmpDate = RTC2_ConstructDate(RTC2_INITIAL_MONTH,
                                          RTC2_INITIAL_DAY,
                                          RTC2_INITIAL_YEAR);

    tmpTime = RTC2_ConstructTime(RTC2_INITIAL_TIME_FORMAT,
                                          0u,
                                          RTC2_INITIAL_HOUR,
                                          RTC2_INITIAL_MINUTE,
                                          RTC2_INITIAL_SECOND);

    #if(0u != RTC2_INITIAL_DST_STATUS)
        RTC2_dstStatus = 0u;
        RTC2_currentTimeDate.status = (1uL << RTC2_STATUS_DST_OFFSET);

        dstTimeTmp.timeFormat    = RTC2_INITIAL_DST_DATE_TYPE;
        dstTimeTmp.hour          = RTC2_INITIAL_DST_START_HRS;
        dstTimeTmp.dayOfWeek     = RTC2_INITIAL_DST_START_DOW;
        dstTimeTmp.weekOfMonth   = RTC2_INITIAL_DST_START_WOM;
        dstTimeTmp.dayOfMonth    = RTC2_INITIAL_DST_START_DOM;
        dstTimeTmp.month         = RTC2_INITIAL_DST_START_MONTH;
        RTC2_SetDSTStartTime(&dstTimeTmp, (RTC2_DST_DATETYPE_ENUM)RTC2_INITIAL_DST_DATE_TYPE);

        dstTimeTmp.timeFormat    = RTC2_INITIAL_DST_DATE_TYPE;
        dstTimeTmp.hour          = RTC2_INITIAL_DST_STOP_HRS;
        dstTimeTmp.dayOfWeek     = RTC2_INITIAL_DST_STOP_DOW;
        dstTimeTmp.weekOfMonth   = RTC2_INITIAL_DST_STOP_WOM;
        dstTimeTmp.dayOfMonth    = RTC2_INITIAL_DST_STOP_DOM;
        dstTimeTmp.month         = RTC2_INITIAL_DST_STOP_MONTH;
        RTC2_SetDSTStopTime(&dstTimeTmp, (RTC2_DST_DATETYPE_ENUM)RTC2_INITIAL_DST_DATE_TYPE);

        RTC2_unixTimeDstStart = RTC2_GetDstUnixTime(&RTC2_dstStartTime);
        RTC2_unixTimeDstStop  = RTC2_GetDstUnixTime(&RTC2_dstStopTime);

        if((RTC2_unixTime >= RTC2_unixTimeDstStart) &&
           (RTC2_unixTime <= RTC2_unixTimeDstStop))
        {
            RTC2_dstStatus = 1u;
            RTC2_dstTimeOffset = RTC2_SECONDS_PER_HOUR;
        }
    #endif /* (0u != RTC2_INITIAL_DST_STATUS) */

    RTC2_SetDateAndTime(tmpTime, tmpDate);
}


/*******************************************************************************
* Function Name: RTC2_SetDateAndTime
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
void RTC2_SetDateAndTime(uint32 inputTime, uint32 inputDate)
{
    uint32 tmpDay;
    uint32 tmpMonth;
    uint32 tmpYear;

    tmpDay   = RTC2_GetDay(inputDate);
    tmpMonth = RTC2_GetMonth(inputDate);
    tmpYear  = RTC2_GetYear(inputDate);

    RTC2_unixTime = RTC2_DateTimeToUnix(inputDate, inputTime);
    RTC2_currentTimeDate.date = inputDate;
    RTC2_currentTimeDate.time = inputTime;
    RTC2_currentTimeDate.dayOfWeek = RTC2_GetDayOfWeek(tmpDay, tmpMonth, tmpYear);

    #if(0u != RTC2_INITIAL_DST_STATUS)
        RTC2_unixTimeDstStart = RTC2_GetDstUnixTime(&RTC2_dstStartTime);
        RTC2_unixTimeDstStop  = RTC2_GetDstUnixTime(&RTC2_dstStopTime);

        if((RTC2_unixTime >= RTC2_unixTimeDstStart) &&
           (RTC2_unixTime <= RTC2_unixTimeDstStop))
        {
            RTC2_dstStatus = 1u;
            RTC2_dstTimeOffset = RTC2_SECONDS_PER_HOUR;
            RTC2_unixTime -= RTC2_dstTimeOffset;
        }
        else
        {
            RTC2_dstStatus = 0u;
            RTC2_dstTimeOffset = 0uL;
        }
    #endif /* (0u != RTC2_INITIAL_DST_STATUS) */

    #if(0u != RTC2_INITIAL_ALARM_STATUS)
        RTC2_unixTimeAlarm = RTC2_ConstructUnixAlarmTime(&RTC2_alarmCfgTimeDate,
                                                                                 (uint8)RTC2_alarmCfgMask);
    #endif /* (0u != RTC2_INITIAL_ALARM_STATUS) */
}


/*******************************************************************************
* Function Name: RTC2_SetUnixTime
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
void RTC2_SetUnixTime(uint64 unixTime)
{
    RTC2_DATE_TIME tmpDateTime;

    RTC2_unixTime = unixTime;
    RTC2_UnixToDateTime(&tmpDateTime, unixTime, (uint32)RTC2_24_HOURS_FORMAT);

    #if(0u != RTC2_INITIAL_DST_STATUS)
        RTC2_unixTimeDstStart = RTC2_GetDstUnixTime(&RTC2_dstStartTime);
        RTC2_unixTimeDstStop  = RTC2_GetDstUnixTime(&RTC2_dstStopTime);

        if((RTC2_unixTime >= RTC2_unixTimeDstStart) &&
           (RTC2_unixTime <= RTC2_unixTimeDstStop))
        {
            RTC2_dstStatus = 1u;
            RTC2_dstTimeOffset = RTC2_SECONDS_PER_HOUR;
        }
        else
        {
            RTC2_dstStatus = 0u;
            RTC2_dstTimeOffset = 0uL;
        }
    #endif /* (0u != RTC2_INITIAL_DST_STATUS) */
}


/*******************************************************************************
* Function Name: RTC2_GetUnixTime
****************************************************************************//**
*
* \brief
*  Returns the time in the Unix/Epoch time format - the number of seconds 
* elapsed from January 1, 1970 UTC 00:00 hrs.
*
* \return time The time value in the Unix time/Epoch time format.
*
*******************************************************************************/
uint64 RTC2_GetUnixTime(void)
{
    return (RTC2_unixTime);
}


/*******************************************************************************
* Function Name: RTC2_SetPeriod
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
*  RTC2_Update() API is called.
*
* \param
*  ticks The clock period taken as a number of ticks.
*
* \param
* refOneSecTicks The reference number of ticks taken by the same clock source
*  for one second (the input clock frequency in Hz).
*
*******************************************************************************/
void RTC2_SetPeriod(uint32 ticks, uint32 refOneSecTicks)
{
    RTC2_updateTimePeriod = ticks;
    RTC2_tickRefOneSec    = refOneSecTicks;
}


/*******************************************************************************
* Function Name: RTC2_SetPeriod
****************************************************************************//**
*
* \brief
*  Gets the RTC time update API period.
*
* \return period The clock period taken as a number of ticks.
*
*******************************************************************************/
uint32 RTC2_GetPeriod(void)
{
    return(RTC2_updateTimePeriod);
}


/*******************************************************************************
* Function Name: RTC2_GetRefOneSec
****************************************************************************//**
* \brief
* Gets the RTC time update API period.
*
* \return
* period The reference number of ticks taken by the RTC clock source for one
* second.
*
*******************************************************************************/
uint32 RTC2_GetRefOneSec(void)
{
    return(RTC2_tickRefOneSec);
}


/*******************************************************************************
* Function Name: RTC2_GetDateAndTime
****************************************************************************//**
*
* Reads the current time and date.
*
* \param dateTime The pointer to the RTC_date_time structure to which time and 
* date is returned.
*
*******************************************************************************/
void RTC2_GetDateAndTime(RTC2_DATE_TIME* dateTime)
{
    RTC2_UnixToDateTime(dateTime, (RTC2_unixTime  + RTC2_dstTimeOffset),
                                                                            RTC2_INITIAL_TIME_FORMAT);
}


/*******************************************************************************
* Function Name: RTC2_GetTime
****************************************************************************//**
* \brief
* Reads the current time.
*
* \return
* date The value of date in the user selected format. The date value is 
* available in the BCD format.
*
* \warning
*  Using RTC2_GetTime and RTC_GetDate API separately might result
*  in errors when the time wraps around the end of the day. To avoid this,
*  use RTC2_GetDateAndTime API.
*
*******************************************************************************/
uint32 RTC2_GetTime(void)
{
    RTC2_UnixToDateTime(&RTC2_currentTimeDate,
                                    (RTC2_unixTime  + RTC2_dstTimeOffset),
                                     RTC2_INITIAL_TIME_FORMAT);

    return(RTC2_currentTimeDate.time);
}


/*******************************************************************************
* Function Name: RTC2_GetDate
****************************************************************************//**
*
* \brief Reads the current time.
*
* \return
* time The time value in the format selected by the user (12/24 hr);
* The time value is available in the BCD format.
*
* \note
*  Using RTC2_GetTime and RTC2_GetDate API separately
*  might result in errors when the time wraps around the end of the day. To
*  avoid this, use RTC2_GetDateAndTime API.
*
*******************************************************************************/
uint32 RTC2_GetDate(void)
{
    RTC2_UnixToDateTime(&RTC2_currentTimeDate,
                                    (RTC2_unixTime  + RTC2_dstTimeOffset),
                                     RTC2_INITIAL_TIME_FORMAT);

    return(RTC2_currentTimeDate.date);
}


#if(0u != RTC2_INITIAL_ALARM_STATUS)
    /*******************************************************************************
    * Function Name: RTC2_SetAlarmDateAndTime
    ****************************************************************************//**
    *
    * \brief
    *  Writes the time and date values as the current alarm time and date.
    *
    * \param
    *  alarmTime The pointer to the RTC2_date_time global structure where
    *  new values of the alarm time and date are stored.
    *
    * \note
    *  Invalid time entries are written with "00:00:00:00" for the 24-hour format and
    *  "AM 12:00:00:00" for the 12-hour format. Invalid date entries are written with
    *  a date equivalent to 01-JAN-2000.
    *
    *******************************************************************************/
    void RTC2_SetAlarmDateAndTime(const RTC2_DATE_TIME* alarmTime)
    {
        RTC2_alarmCfgTimeDate = *alarmTime;
        RTC2_unixTimeAlarm = RTC2_ConstructUnixAlarmTime(alarmTime, (uint8)RTC2_alarmCfgMask);
    }


    /*******************************************************************************
    * Function Name: RTC2_GetAlarmDateAndTime
    ****************************************************************************//**
    *
    * \brief
    *  Reads the current alarm time and date.
    *
    * \param
    *  alarmTimeDate The pointer to the RTC2_date_time structure to which
    *  the alarm date and time are returned.
    *
    *******************************************************************************/
    void RTC2_GetAlarmDateAndTime(RTC2_DATE_TIME* alarmTimeDate)
    {
        *alarmTimeDate = RTC2_alarmCfgTimeDate;
    }


    /*******************************************************************************
    * Function Name: RTC2_SetAlarmMask
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
    *  RTC2_ALARM_SEC_MASK The second alarm mask allows
    *  matching the alarm second register with the current second register.
    * \param
    *  RTC2_ALARM_MIN_MASK The minute alarm mask allows matching the
    *  alarm minute register with the current minute register.
    * \param
    *  RTC2_ALARM_HOUR_MASK The hour alarm mask allows
    * matching the alarm hour register with the current hour register.
    * \param
    *  RTC2_ALARM_DAYOFWEEK_MASK The day of the week alarm mask 
    * allows matching the alarm day of the week register with the current day of
    * the week register.
    * \param
    * RTC2_ALARM_DAYOFMONTH_MASK The day of the month alarm mask
    * allows matching the alarm day of the month register with the current day 
    * of the month register.
    * \param
    * RTC2_ALARM_MONTH_MASK The month alarm mask allows matching 
    * the alarm month register with the current month register.
    * \param
    * RTC2_ALARM_YEAR_MASK The year alarm mask allows matching the
    *  alarm year register with the current year register.
    *
    *******************************************************************************/
    void RTC2_SetAlarmMask(uint32 mask)
    {
        RTC2_alarmCfgMask = (uint8)mask;
        RTC2_unixTimeAlarm = RTC2_ConstructUnixAlarmTime(&RTC2_alarmCfgTimeDate, (uint8)mask);
    }


    /*******************************************************************************
    * Function Name: RTC2_GetAlarmMask
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
    *  RTC2_ALARM_SEC_MASK - The second alarm mask allows matching the
    * alarm second register with the current second register.
    *
    * \return
    * RTC2_ALARM_MIN_MASK - The minute alarm mask allows matching the 
    * alarm minute register with the current minute register.
    *
    * \return
    *  RTC2_ALARM_HOUR_MASK - The hour alarm mask allows matching the 
    * alarm hour register with the current hour register.
    *
    * \return
    *  RTC2_ALARM_DAYOFWEEK_MASK - The day of the week alarm mask allows
    * matching the alarm day of the week register with the current day of the 
    * week register.
    *
    * \return
    *  RTC2_ALARM_DAYOFMONTH_MASK - The day of the month alarm mask 
    * allows matching the alarm day of the month register with the current day of 
    * the month register.
    *
    * \return
    *  RTC2_ALARM_MONTH_MASK - The month alarm mask allows matching 
    * the alarm month register with the current month register.
    *
    * \return
    *  RTC2_ALARM_YEAR_MASK - The year alarm mask allows matching the
    * alarm year register with the current year register.
    *
    *******************************************************************************/
    uint32 RTC2_GetAlarmMask(void)
    {
        return((uint32)RTC2_alarmCfgMask);
    }


    /*******************************************************************************
    * Function Name: RTC2_GetAlarmStatus
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
    uint32 RTC2_GetAlarmStatus(void)
    {
        return((0uL != (RTC2_currentTimeDate.status & (1uL << RTC2_STATUS_ALARM_OFFSET))) ? 1uL : 0uL);
    }


    /*******************************************************************************
    * Function Name: RTC2_ClearAlarmStatus
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
    void RTC2_ClearAlarmStatus(void)
    {
        RTC2_currentTimeDate.status &= (~(1uL << RTC2_STATUS_ALARM_OFFSET));
        RTC2_alarmCurStatus = 0u;
    }


    /*******************************************************************************
    * Function Name: RTC2_SetAlarmHandler
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
    void* RTC2_SetAlarmHandler(void (*CallbackFunction)(void))
    {
        void (*tmpCallbackPtr)(void);

        tmpCallbackPtr = RTC2_alarmCallbackPtr;
        RTC2_alarmCallbackPtr = CallbackFunction;

        return((void*)tmpCallbackPtr);
    }


    /*******************************************************************************
    * Function Name: RTC2_GetNexAlarmTime
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
    uint64 RTC2_GetNexAlarmTime(uint64 curUnixTime, uint8 alarmCfgMask)
    {
        uint32 prevVal;
        uint32 nextVal;
        uint32 carryFlag;
        uint32 daysInMonth;
        RTC2_DATE_TIME curDateTime;

        carryFlag = 1u;
        RTC2_UnixToDateTime(&curDateTime, curUnixTime, (uint32)RTC2_24_HOURS_FORMAT);

        /* Calculates Second value of next alarm time based on current time and Alarm Config Mask. */
        if(0uL != ((~((uint32)alarmCfgMask)) & RTC2_ALARM_SEC_MASK))
        {
            prevVal = RTC2_GetSecond(curDateTime.time);
            nextVal = RTC2_GetNextMinSec(prevVal);
            curDateTime.time = RTC2_SetSecond(curDateTime.time, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Minute value of next alarm time based on current time and Alarm Config Mask. */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & RTC2_ALARM_MIN_MASK)))
        {
            prevVal = RTC2_GetMinutes(curDateTime.time);
            nextVal = RTC2_GetNextMinSec(prevVal);
            curDateTime.time = RTC2_SetMinutes(curDateTime.time, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Hour value of next alarm time based on current time and Alarm Config Mask. */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & RTC2_ALARM_HOUR_MASK)))
        {
            prevVal = RTC2_GetHours(curDateTime.time);
            nextVal = RTC2_GetNextHour(prevVal);
            curDateTime.time = RTC2_SetHours(curDateTime.time, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Day value of next alarm time based on current time and Alarm Config Mask. */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & RTC2_ALARM_DAYOFMONTH_MASK)))
        {
            prevVal = RTC2_GetDay(curDateTime.date);
            if(0u != (alarmCfgMask & RTC2_ALARM_DAYOFWEEK_MASK))
            {
                daysInMonth = RTC2_DaysInMonth(RTC2_GetMonth(curDateTime.date),
                                                           RTC2_GetYear(curDateTime.date));
                nextVal = prevVal + RTC2_DAYS_PER_WEEK;
                nextVal = (nextVal > daysInMonth) ? (nextVal - daysInMonth) : nextVal;
            }
            else
            {
                nextVal = RTC2_GetNextDay(RTC2_GetYear(curDateTime.date),
                                                      RTC2_GetMonth(curDateTime.date),
                                                      RTC2_GetDay(curDateTime.date),
                                                      (~((uint32)alarmCfgMask)));
            }
            curDateTime.date = RTC2_SetDay(curDateTime.date, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Month value of next alarm time based on current time and Alarm Config Mask. */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & RTC2_ALARM_MONTH_MASK)))
        {
            prevVal = RTC2_GetMonth(curDateTime.date);
            nextVal = RTC2_GetNextMonth(prevVal);
            curDateTime.date = RTC2_SetMonth(curDateTime.date, nextVal);
            carryFlag = (nextVal < prevVal) ? 1u : 0u;
        }

        /* Calculates Year value of next alarm time based on current time and Alarm Config Mask. */
        if((0uL != carryFlag) && (0uL != ((~((uint32)alarmCfgMask)) & RTC2_ALARM_YEAR_MASK)))
        {
            prevVal = RTC2_GetYear(curDateTime.date);
            nextVal = RTC2_GetNextYear(prevVal);
            curDateTime.date = RTC2_SetYear(curDateTime.date, nextVal);
        }

        return(RTC2_DateTimeToUnix(curDateTime.date, curDateTime.time));
    }


    /*******************************************************************************
    * Function Name: RTC2_ConstructUnixAlarmTime
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
    uint64 RTC2_ConstructUnixAlarmTime(const RTC2_DATE_TIME* alarmTime, uint8 alarmCfgMask)
    {
        uint32 tmpCurVal;
        uint32 tmpNextVal;
        uint32 carryFlag;
        uint32 tmpAlarmDate;
        uint32 tmpAlarmTime;
        uint32 daysInMonth;
        RTC2_DATE_TIME curDateTime;

        tmpAlarmDate = 0u;
        tmpAlarmTime = 0u;
        RTC2_UnixToDateTime(&curDateTime, RTC2_unixTime, (uint32)RTC2_24_HOURS_FORMAT);

        /* Calculates Seconds value of first Alarm based on current time and Alarm Config Mask. */
        tmpCurVal =  RTC2_GetSecond(curDateTime.time);
        tmpNextVal = RTC2_GetSecond(alarmTime->time);
        carryFlag = (tmpCurVal > tmpNextVal) ? 1u : 0u;
        if(0u != ((~((uint32)alarmCfgMask)) & RTC2_ALARM_SEC_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? 0u : tmpCurVal;
        }
        tmpAlarmTime = RTC2_SetSecond(tmpAlarmTime, tmpNextVal);

        /* Calculates Minutes value of first Alarm based on current time and Alarm Config Mask. */
        tmpCurVal  = RTC2_GetMinutes(curDateTime.time);
        if(0u != ((~((uint32)alarmCfgMask)) & RTC2_ALARM_MIN_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? RTC2_GetNextMinSec(tmpCurVal) : tmpCurVal;
        }
        else
        {
            tmpNextVal = RTC2_GetMinutes(alarmTime->time);
        }
        carryFlag  = (tmpNextVal < tmpCurVal) ? 1u : 0u;
        tmpAlarmTime =  RTC2_SetMinutes(tmpAlarmTime, tmpNextVal);

        /* Calculates Hours value of first Alarm based on current time and Alarm Config Mask. */
        tmpCurVal  = RTC2_GetHours(curDateTime.time);
        if(0u != ((~((uint32)alarmCfgMask)) & RTC2_ALARM_HOUR_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? RTC2_GetNextHour(tmpCurVal) : tmpCurVal;
        }
        else
        {
            tmpNextVal = RTC2_GetHours(alarmTime->time);
            if((uint32)RTC2_24_HOURS_FORMAT != RTC2_GetTimeFormat(alarmTime->time))
            {
                if((uint32)RTC2_AM != RTC2_GetAmPm(alarmTime->time))
                {
                    tmpNextVal += RTC2_HOURS_PER_HALF_DAY;
                }
            }
        }
        carryFlag  = (tmpNextVal < tmpCurVal) ? 1u : 0u;
        tmpAlarmTime =  RTC2_SetHours(tmpAlarmTime, tmpNextVal);

        /* Calculates Day value of first Alarm based on current time and Alarm Config Mask. */
        tmpCurVal  = RTC2_GetDay(curDateTime.date);
        tmpNextVal = RTC2_GetDay(alarmTime->date);
        if(0u != ((~((uint32)alarmCfgMask)) & RTC2_ALARM_DAYOFMONTH_MASK))
        {
            if(0u != (alarmCfgMask & RTC2_ALARM_DAYOFWEEK_MASK))
            {
                daysInMonth = RTC2_DaysInMonth(RTC2_GetMonth(curDateTime.date),
                                                           RTC2_GetYear(curDateTime.date));
                tmpNextVal = (curDateTime.dayOfWeek <= alarmTime->dayOfWeek) ? (alarmTime->dayOfWeek - curDateTime.dayOfWeek) :
                                ((RTC2_DAYS_PER_WEEK - curDateTime.dayOfWeek) + alarmTime->dayOfWeek);
                tmpNextVal = tmpCurVal + tmpNextVal;
                tmpNextVal = (tmpNextVal > daysInMonth) ? (tmpNextVal - daysInMonth) : tmpNextVal;
            }
            else
            {
                tmpNextVal = (0u == carryFlag) ? tmpCurVal : RTC2_GetNextDay(RTC2_GetYear(curDateTime.date),
                                                              RTC2_GetMonth(curDateTime.date),
                                                               tmpCurVal,
                                                              RTC2_ALARM_DAYOFMONTH_MASK);
            }
        }
        carryFlag  = (tmpNextVal < tmpCurVal) ? 1u : 0u;
        tmpAlarmDate =  RTC2_SetDay(tmpAlarmDate, tmpNextVal);

        /* Calculates Month value of first Alarm based on current time and Alarm Config Mask. */
        tmpCurVal  = RTC2_GetMonth(curDateTime.date);
        if(0u != ((~((uint32)alarmCfgMask)) & RTC2_ALARM_MONTH_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? RTC2_GetNextMonth(tmpCurVal) : tmpCurVal;
        }
        else
        {
            tmpNextVal = RTC2_GetMonth(alarmTime->date);
        }
        carryFlag  = (tmpNextVal < tmpCurVal) ? 1u : 0u;
        tmpAlarmDate =  RTC2_SetMonth(tmpAlarmDate, tmpNextVal);

        /* Calculates Year value of first Alarm based on current time and Alarm Config Mask. */
        tmpCurVal  = RTC2_GetYear(curDateTime.date);
        if(0u != ((~((uint32)alarmCfgMask)) & RTC2_ALARM_MONTH_MASK))
        {
            tmpNextVal = (0u != carryFlag) ? RTC2_GetNextYear(tmpCurVal) : tmpCurVal;
        }
        else
        {
            tmpNextVal = RTC2_GetYear(alarmTime->date);
        }
        tmpAlarmDate =  RTC2_SetYear(tmpAlarmDate, tmpNextVal);

        return(RTC2_DateTimeToUnix(tmpAlarmDate, tmpAlarmTime));
    }
#endif/* (0u != RTC2_INITIAL_ALARM_STATUS) */


/*******************************************************************************
* Function Name: RTC2_ReadStatus
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
* RTC2_STATUS_DST - Status of Daylight Saving Time. This bit
* goes high when the current time and date match the DST time and date and the 
* time is incremented. This bit goes low after the DST interval and the time is 
* decremented.
*
* \return
* RTC2_STATUS_LY - Status of Leap Year. This bit goes high when the 
* current year is a leap year.
*
* \return
* RTC2_STATUS_AM_PM - Status of Current Time. This bit is low from 
* midnight to noon and high from noon to midnight.
*
* \note
* Reading the status without sync with the date and time read may cause an
* error due to a roll-over at AM/PM, the end of a year, the end of a day;
* RTC2_GetDateAndTime() API is used to obtain the status and
* the status member of the returned structure can be checked with the masks.
*
*******************************************************************************/
uint32 RTC2_ReadStatus(void)
{
    uint32 tmpYear;
    RTC2_DATE_TIME tmpTimeDate;

    RTC2_GetDateAndTime(&tmpTimeDate);
    tmpYear = RTC2_GetYear(tmpTimeDate.date);

    if(0uL != RTC2_LeapYear(tmpYear))
    {
        RTC2_currentTimeDate.status |= (1uL << RTC2_STATUS_LY_OFFSET);
    }
    else
    {
        RTC2_currentTimeDate.status &= ~(1uL << RTC2_STATUS_LY_OFFSET);
    }


    if(0uL != RTC2_GetAmPm(tmpTimeDate.time))
    {
        RTC2_currentTimeDate.status |= (1uL << RTC2_STATUS_AM_PM_OFFSET);
    }
    else
    {
        RTC2_currentTimeDate.status &= ~(1uL << RTC2_STATUS_AM_PM_OFFSET);
    }

    return(RTC2_currentTimeDate.status);
}


#if(0u != RTC2_INITIAL_DST_STATUS)
    /*******************************************************************************
    * Function Name: RTC2_SetDSTStartTime
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
    void RTC2_SetDSTStartTime(const RTC2_DST_TIME* dstStartTime,
                                                RTC2_DST_DATETYPE_ENUM type)
    {
        RTC2_dstStartTime.timeFormat    = (uint8)type;
        RTC2_dstStartTime.hour          = dstStartTime->hour;
        RTC2_dstStartTime.dayOfWeek     = dstStartTime->dayOfWeek;
        RTC2_dstStartTime.weekOfMonth   = dstStartTime->weekOfMonth;
        RTC2_dstStartTime.dayOfMonth    = dstStartTime->dayOfMonth;
        RTC2_dstStartTime.month         = dstStartTime->month;

        RTC2_unixTimeDstStart = RTC2_GetDstUnixTime(&RTC2_dstStartTime);

        if((RTC2_unixTime >= RTC2_unixTimeDstStart) &&
           (RTC2_unixTime <= RTC2_unixTimeDstStop))
        {
            RTC2_dstStatus = 1u;
            RTC2_dstTimeOffset = RTC2_SECONDS_PER_HOUR;
        }
        else
        {
            RTC2_dstStatus = 0u;
            RTC2_dstTimeOffset = 0uL;
        }
    }


    /*******************************************************************************
    * Function Name: RTC2_SetDSTStopTime
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
    void RTC2_SetDSTStopTime(const RTC2_DST_TIME* dstStopTime,
                                               RTC2_DST_DATETYPE_ENUM type)
    {

        RTC2_dstStopTime.timeFormat  = (uint8)type;
        RTC2_dstStopTime.hour           = dstStopTime->hour;
        RTC2_dstStopTime.dayOfWeek      = dstStopTime->dayOfWeek;
        RTC2_dstStopTime.weekOfMonth = dstStopTime->weekOfMonth;
        RTC2_dstStopTime.dayOfMonth     = dstStopTime->dayOfMonth;
        RTC2_dstStopTime.month         = dstStopTime->month;

        RTC2_unixTimeDstStop  = RTC2_GetDstUnixTime(&RTC2_dstStopTime);

        if((RTC2_unixTime >= RTC2_unixTimeDstStart) &&
           (RTC2_unixTime <= RTC2_unixTimeDstStop))
        {
            RTC2_dstStatus = 1u;
            RTC2_dstTimeOffset = RTC2_SECONDS_PER_HOUR;
        }
        else
        {
            RTC2_dstStatus = 0u;
            RTC2_dstTimeOffset = 0uL;
        }
    }


    /*******************************************************************************
    * Function Name: RTC2_GetDstUnixTime
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
    uint64 RTC2_GetDstUnixTime(const RTC2_DST_TIME* dstTime)
    {
        uint32 tmpYear;
        uint32 tmpDate;
        uint64 dstUnixTime;

        RTC2_DATE_TIME tmpTimeDate;

        RTC2_UnixToDateTime(&tmpTimeDate, RTC2_unixTime, RTC2_INITIAL_TIME_FORMAT);
        tmpYear = RTC2_GetYear(tmpTimeDate.date);

        if(dstTime->timeFormat == (uint8)RTC2_DST_DATE_FIXED)
        {
            tmpDate =     RTC2_ConstructDate(dstTime->month, dstTime->dayOfMonth, tmpYear);
        }
        else
        {
            tmpDate = RTC2_RelativeToFixed(dstTime->dayOfWeek, dstTime->weekOfMonth, dstTime->month, tmpYear);
        }

        tmpTimeDate.time = RTC2_ConstructTime((uint32)RTC2_24_HOURS_FORMAT, 0u, dstTime->hour, 0u, 0u);
        dstUnixTime = RTC2_DateTimeToUnix(tmpDate, tmpTimeDate.time);

        return(dstUnixTime);
    }


#endif /* (0u != RTC2_INITIAL_DST_STATUS) */


/*******************************************************************************
* Function Name: RTC2_ConvertBCDToDec
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
uint32 RTC2_ConvertBCDToDec(uint32 bcdNum)
{
    uint32 i;
    uint32 mult;
    uint32 retVal;

    mult   = 1u;
    retVal = 0u;

    for(i = 0u; i < 16u; i++)
    {
        retVal += (bcdNum & RTC2_BCD_ONE_DIGIT_MASK) * mult;
        bcdNum >>= RTC2_BCD_NUMBER_SIZE;
        mult *= 10u;
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: RTC2_ConvertDecToBCD
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
uint32 RTC2_ConvertDecToBCD(uint32 decNum)
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
        shift  += RTC2_BCD_NUMBER_SIZE;
    }
    while(tmpVal >= 10u);

    retVal |= (tmpVal << shift);

    return(retVal);
}


/*******************************************************************************
* Function Name: RTC2_Update
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
void RTC2_Update(void)
{
    static volatile uint32 RTC2_currentTickNumber;
    RTC2_currentTickNumber += RTC2_updateTimePeriod;

    if(RTC2_currentTickNumber >= RTC2_tickRefOneSec)
    {
        RTC2_unixTime++;
        RTC2_currentTickNumber = 0u;

    #if(0u != RTC2_INITIAL_DST_STATUS)
        if(RTC2_unixTime == RTC2_unixTimeDstStart)
        {
            RTC2_dstStatus = 1u;
            RTC2_dstTimeOffset = RTC2_SECONDS_PER_HOUR;
        }

        if(RTC2_unixTime == (RTC2_unixTimeDstStop  - RTC2_dstTimeOffset))
        {
            RTC2_dstStatus = 0u;
            RTC2_dstTimeOffset = 0u;
            RTC2_unixTimeDstStart = RTC2_GetDstUnixTime(&RTC2_dstStartTime);
            RTC2_unixTimeDstStop  = RTC2_GetDstUnixTime(&RTC2_dstStopTime);
        }
    #endif /* (0u != RTC2_INITIAL_DST_STATUS) */

    #if(0u != RTC2_INITIAL_ALARM_STATUS)
        if((RTC2_unixTime + RTC2_dstTimeOffset) == RTC2_unixTimeAlarm)
        {
            RTC2_currentTimeDate.status |= (1uL << RTC2_STATUS_ALARM_OFFSET);
            RTC2_alarmCurStatus = RTC2_alarmCfgMask;
            if (RTC2_alarmCallbackPtr != (void *) 0)
            {
                RTC2_alarmCallbackPtr();
            }
            RTC2_unixTimeAlarm = RTC2_GetNexAlarmTime(RTC2_unixTime + RTC2_dstTimeOffset,
                                                                                                  (uint8)RTC2_alarmCfgMask);
        }
    #endif/* (0u != RTC2_INITIAL_ALARM_STATUS) */
    }
}


/*******************************************************************************
* Function Name: RTC2_DateTimeToUnix
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
uint64 RTC2_DateTimeToUnix(uint32 inputDate, uint32 inputTime)
{
    uint32 i;
    uint32 tmpYear;
    uint32 tmpMonth;
    uint32 tmpVal;
    uint64 unixTime;

    unixTime = 0u;
    tmpYear = RTC2_GetYear(inputDate);

    /* Calculate seconds from epoch start up to (but not including) current year. */
    for(i = RTC2_YEAR_0; i < tmpYear; i++)
    {
        if(0u != RTC2_LeapYear(i))
        {
            unixTime += RTC2_SECONDS_PER_LEAP_YEAR;
        }
        else
        {
            unixTime += RTC2_SECONDS_PER_NONLEAP_YEAR;
        }
    }

    /* Calculates how many seconds had elapsed in this year prior to the current month. */
    tmpMonth = RTC2_GetMonth(inputDate);
    tmpVal = RTC2_daysBeforeMonthTbl[tmpMonth - 1u];

    if((tmpMonth > 2u) && (0u != RTC2_LeapYear(tmpYear)))
    {
        tmpVal++;
    }

    /* Calculates how many seconds are in current month days prior to today. */
    unixTime += tmpVal * RTC2_SECONDS_PER_DAY;
    unixTime += (RTC2_GetDay(inputDate) - 1u) * RTC2_SECONDS_PER_DAY;

    /* Calculates how many seconds have elapsed today up to the current hour. */
    tmpVal = RTC2_GetHours(inputTime);
    if(((uint32)RTC2_24_HOURS_FORMAT != RTC2_GetTimeFormat(inputTime)) &&
       ((uint32)RTC2_AM != RTC2_GetAmPm(inputTime)) && (tmpVal < 12u))
    {
        tmpVal += RTC2_HOURS_PER_HALF_DAY;
    }
    unixTime += tmpVal * RTC2_SECONDS_PER_HOUR;

    /* Calculates how many seconds have elapsed today up to the current minute. */
    unixTime += RTC2_GetMinutes(inputTime) * RTC2_SECONDS_PER_MINUTE;

    /* Add remaining seconds of current minute. */
    unixTime += RTC2_GetSecond(inputTime);

    return(unixTime);
}


/*******************************************************************************
* Function Name: RTC2_UnixToDateTime
****************************************************************************//**
*
* \brief
*  This is an internal function to convert the date and time from
*  the UNIX time format into the regular time format.
*
* \param dayOfWeek A day of a week <br>
*                 RTC2_SUNDAY <br>
*                 RTC2_MONDAY <br>
*                 RTC2_TUESDAY <br>
*                 RTC2_WEDNESDAY <br>
*                 RTC2_THURSDAY <br>
*                 RTC2_FRIDAY <br>
*                 RTC2_SATURDAY <br>
*
* \param weekOfMonth A week of a month <br>
*                 RTC2_FIRST <br>
*                 RTC2_SECOND <br>
*                 RTC2_THIRD <br>
*                 RTC2_FOURTH <br>
*                 RTC2_LAST <br>
*
* \param month A month of a year <br>
*                   RTC2_JANUARY <br>
*                  RTC2_FEBRUARY <br>
*                  RTC2_MARCH <br>
*                  RTC2_APRIL <br>
*                  RTC2_MAY <br>
*                  RTC2_JUNE <br>
*                  RTC2_JULY <br>
*                  RTC2_AUGUST <br>
*                  RTC2_SEPTEMBER <br>
*                  RTC2_OCTOBER <br>
*                  RTC2_NOVEMBER <br>
*                  RTC2_DECEMBER <br>
*
* \param year A year value.
*
* \return A date in the "date format".
*
*******************************************************************************/
void RTC2_UnixToDateTime(RTC2_DATE_TIME* dateTime, uint64 unixTime, uint32 timeFormat)
{
    uint32 tmpMinute;
    uint32 tmpHour;
    uint32 tmpAmPmState;

    uint32 tmpDay;
    uint32 tmpMonth;
    uint32 tmpYear;

    uint32 tmpVar;

    tmpAmPmState = 0u;
    tmpYear = RTC2_YEAR_0;
    tmpVar = RTC2_SECONDS_PER_NONLEAP_YEAR;

    /* Calculates current year value. Variable tmpYear
    *  increments while it contains value greater than number
    *  of seconds in current year.
    */
    while(unixTime > tmpVar)
    {
        unixTime -= tmpVar;
        tmpYear++;

        if(0u != RTC2_LeapYear(tmpYear))
        {
            tmpVar = RTC2_SECONDS_PER_LEAP_YEAR;
        }
        else
        {
            tmpVar = RTC2_SECONDS_PER_NONLEAP_YEAR;
        }

    }

    /* Calculates current month value. tmpMonth variable increments
     * while unixTime variable value is greater than time
     * interval from beginning of current year to beginning of
     * current month
    */
    tmpMonth = (uint32)RTC2_JANUARY;
    tmpVar = RTC2_DaysInMonth(tmpMonth, tmpYear) * RTC2_SECONDS_PER_DAY;

    while(unixTime >= tmpVar)
    {
        unixTime -= tmpVar;
        tmpMonth++;
        tmpVar = RTC2_DaysInMonth(tmpMonth, tmpYear) * RTC2_SECONDS_PER_DAY;
    }

    /* Calculates current day value. */
    tmpDay = (unixTime / RTC2_SECONDS_PER_DAY);
    tmpVar = tmpDay * RTC2_SECONDS_PER_DAY;
    unixTime -= (unixTime >= tmpVar) ? tmpVar : 0u;
    tmpDay += 1u;

    /* Calculates current hour value. If function works in 12-Hour mode,
     * it converts time to 12-Hours mode and calculates AmPm status */
    tmpHour = unixTime / RTC2_SECONDS_PER_HOUR;
    tmpVar  = tmpHour * RTC2_SECONDS_PER_HOUR;
    if((uint32)RTC2_24_HOURS_FORMAT != timeFormat)
    {
        if(unixTime > RTC2_UNIX_TIME_PM)
        {
            tmpAmPmState = RTC2_PM;
            tmpHour = (tmpHour > 12u) ? (tmpHour - 12u) : tmpHour;
        }
        else
        {
            tmpAmPmState = RTC2_AM;
            tmpHour = (0u != tmpHour) ? tmpHour : 12u;
        }
    }
    unixTime -= (unixTime >= tmpVar) ? tmpVar : 0u;

    /* Calculates current minute.  */
    tmpMinute = unixTime / RTC2_SECONDS_PER_MINUTE;
    tmpVar = tmpMinute * RTC2_SECONDS_PER_MINUTE;

    /* Calculates current second. */
    unixTime -= (unixTime >= tmpVar) ? tmpVar : 0u;


    dateTime->date = RTC2_ConstructDate(tmpMonth, tmpDay, tmpYear);
    dateTime->time = RTC2_ConstructTime(timeFormat, tmpAmPmState, tmpHour, tmpMinute, unixTime);
    dateTime->dayOfWeek = RTC2_GetDayOfWeek(tmpDay, tmpMonth, tmpYear);
}


/*******************************************************************************
* Function Name: RTC2_RelativeToFixed
****************************************************************************//**
*
* \brief
* This is an internal function to convert a relative date into
* a fixed date.
*
* \param dayOfWeek A day of a week <br>
*                 RTC2_SUNDAY <br>
*                 RTC2_MONDAY <br>
*                 RTC2_TUESDAY <br>
*                 RTC2_WEDNESDAY <br>
*                 RTC2_THURSDAY <br>
*                 RTC2_FRIDAY <br>
*                 RTC2_SATURDAY <br>
*
*  \param weekOfMonth A week of a month <br>
*                 RTC2_FIRST <br>
*                 RTC2_SECOND <br>
*                 RTC2_THIRD <br>
*                 RTC2_FOURTH <br>
*                 RTC2_FIFTH <br>
*                 RTC2_LAST <br>
*
* \param month A month of a year <br>
*                  RTC2_JANUARY <br>
*                  RTC2_FEBRUARY <br>
*                  RTC2_MARCH <br>
*                  RTC2_APRIL <br>
*                  RTC2_MAY <br>
*                  RTC2_JUNE <br>
*                  RTC2_JULY <br>
*                  RTC2_AUGUST <br>
*                  RTC2_SEPTEMBER <br>
*                  RTC2_OCTOBER <br>
*                  RTC2_NOVEMBER <br>
*                  RTC2_DECEMBER <br>
*
* \param year A year value.
*
* \return A date in the "date format".
*
*******************************************************************************/
uint32 RTC2_RelativeToFixed(uint32 dayOfWeek, uint32 weekOfMonth, uint32 month, uint32 year)
{
    uint32 curDay;
    uint32 curWeek;
    uint32 daysInMonth;
    uint32 dayOfMonthTmp;

    uint32 retVal;

    curDay      = 1u;
    curWeek     = (uint32)RTC2_FIRST;
    daysInMonth = RTC2_DaysInMonth(month, year);
    dayOfMonthTmp = curDay;

    while((curWeek <= weekOfMonth) && (curDay <= daysInMonth))
    {
        if(dayOfWeek == RTC2_GetDayOfWeek(curDay, month, year))
        {
            dayOfMonthTmp = curDay;
            curWeek++;
        }
        curDay++;
    }

    retVal = RTC2_ConstructDate(month, dayOfMonthTmp, year);

    return(retVal);
}


/*******************************************************************************
* Function Name: RTC2_DaysInMonth
****************************************************************************//**
*
* \brief
*  Returns a number of days in a month passed through the parameters.
*
* \param
*  month A month of a year
*  RTC2_JANUARY
*  RTC2_FEBRUARY
*  RTC2_MARCH
*  RTC2_APRIL
*  RTC2_MAY
*  RTC2_JUNE
*  RTC2_JULY
*  RTC2_AUGUST
*  RTC2_SEPTEMBER
*  RTC2_OCTOBER
*  RTC2_NOVEMBER
*  RTC2_DECEMBER
*
* \param
* year A year value.
*
* \return
*  A number of days in a month in the year passed through the parameters.
*
*******************************************************************************/
uint32 RTC2_DaysInMonth(uint32 month, uint32 year)
{
    uint32 retVal;

    retVal = RTC2_daysInMonthTbl[month - 1u];
    if((uint32)RTC2_FEBRUARY == month)
    {
        if(0u != RTC2_LeapYear(year))
        {
            retVal++;
        }
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: RTC2_DaysBeforeMonth
****************************************************************************//**
*
* \brief
*  Calculates how many days elapsed from the beginning of the year to the
*  beginning of the current month.
*
* \param
*  month A month of a year
*  RTC2_JANUARY
*  RTC2_FEBRUARY
*  RTC2_MARCH
*  RTC2_APRIL
*  RTC2_MAY
*  RTC2_JUNE
*  RTC2_JULY
*  RTC2_AUGUST
*  RTC2_SEPTEMBER
*  RTC2_OCTOBER
*  RTC2_NOVEMBER
*  RTC2_DECEMBER
*
* \param
* year A year value.
*
* \return
*  A number of days elapsed from the beginning of the year to the
*  beginning of the current month passed through the parameters.
*
*******************************************************************************/
uint32 RTC2_DaysBeforeMonth(uint32 month, uint32 year)
{
    uint32 retVal;

    retVal = RTC2_daysBeforeMonthTbl[month];
    if((0u == RTC2_LeapYear(year)) && (month > (uint32)RTC2_FEBRUARY))
    {
        retVal++;
    }

    return(retVal);
}


/* [] END OF FILE */
