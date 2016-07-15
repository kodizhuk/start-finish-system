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

static uint64_t time;
static uint16_t msRTC;

#ifdef USE_WDT_RTC
/*******************************************************************************
*
* Interrupt handler after lefting time one period light
*
*******************************************************************************/
  
CY_ISR_PROTO(Wdt0_Handler)
{
    msRTC++;
    if (msRTC == 1000u) 
    {
        msRTC = 0u; 
        RTC_Update();
    }
    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
    WDT0_ISR_ClearPending();
}

#endif

void RTCLib_Interrupt(void)
{
    msRTC++;
    if (msRTC == 1000u) 
    {
        msRTC = 0u; 
        RTC_Update();
    }    
}

/*******************************************************************************
* Function Name: RTC_WDT_Init
********************************************************************************
*
* Initialization RTC and watchdog timer
*
*******************************************************************************/
void RTCLib_WDT_Init()
{
    RTC_Start();
    
    #ifdef USE_WDT_RTC
        WDT0_ISR_StartEx(Wdt0_Handler);
    #endif
}

/*******************************************************************************
* Function Name: RTCLib_getTime
********************************************************************************
*
* Summary
*  Reads the current time.
*
* Return:
*  date: The value of date in the user selected format. The date value is available
*        in the BCD format.
*
*******************************************************************************/
uint64_t RTCLib_getTime(uint64_t timeFormat)
{
    uint32_t readTime;
    uint64_t hour, min, sec, ms, stateAmPm;

    
    readTime = RTC_GetTime();
    hour = RTC_GetHours(readTime);
    min = RTC_GetMinutes(readTime);
    sec = RTC_GetSecond(readTime);
    ms = RTCLib_getRecentMs();
    stateAmPm = RTC_GetAmPm(readTime);
    
    time  = timeFormat << RTC_TIME_FORMAT_SHIFT;
    time |= stateAmPm << RTC_PERIOD_OF_DAY_SHIFT;

    time |= (hour / 10u) << RTC_10_HOURS_SHIFT;
    time |= (hour % 10u) << RTC_HOURS_SHIFT;

    time |= (min / 10u) << RTC_10_MINUTES_SHIFT;
    time |= (min % 10u) << RTC_MINUTES_SHIFT;

    time |= (sec / 10u) << RTC_10_SECONDS_SHIFT;
    time |= (sec % 10u) << RTC_SECONDS_SHIFT;
    
    
    time |= (ms / 100u) << RTC_100_MILISECONDS_SHIFT;
    time |= ((ms / 10u)-(ms/100u)*10u) << RTC_10_MILISECONDS_SHIFT;
    time |= (ms % 10u) << RTC_MILISECONDS_SHIFT;
       
    return time;
}

/*******************************************************************************
* Function Name: RTCLib_getHours
****************************************************************************//**
*
* \brief
*  Returns the hours value 
*
* \return
*  The hours value.
*
*******************************************************************************/
uint32_t RTCLib_getHours(uint64_t readTime)
{
    uint64_t retVal;
    
    retVal  = ((readTime & RTC_MASK_10_HOURS) >> RTC_10_HOURS_SHIFT) * 10u;
    retVal += (readTime & RTC_MASK_HOURS) >> RTC_HOURS_SHIFT;
    
    return (int)(retVal);
}

/*******************************************************************************
* Function Name: RTCLib_getMinutes
****************************************************************************//**
*
* \brief
*  Returns the minutes value 
*
* \return
*  The minutes value.
*
*******************************************************************************/
uint32_t RTCLib_getMinutes(uint64_t readTime)
{
    uint64 retVal;

    retVal  = ((readTime & RTC_MASK_10_MINUTES) >> RTC_10_MINUTES_SHIFT) * 10u;
    retVal += (readTime & RTC_MASK_MINUTES) >> RTC_MINUTES_SHIFT;

    return (int)(retVal);
}

/*******************************************************************************
* Function Name: RTCLib_getSecond
****************************************************************************//**
*
* \brief
*  Returns the seconds value 
*
* \return
*  The seconds value.
*
*******************************************************************************/
uint32_t RTCLib_getSecond(uint64_t readTime)
{
    uint32 retVal;

    retVal  = ((readTime & RTC_MASK_10_SECONDS) >> RTC_10_SECONDS_SHIFT) * 10u;
    retVal += (readTime & RTC_MASK_SECONDS) >> RTC_SECONDS_SHIFT;

    return (int)(retVal);
}

/*******************************************************************************
* Function Name: RTCLib_GetMilisecond
****************************************************************************//**
*
* \brief
*  Returns the miliseconds value 
*
* \return
*  The miliseconds value.
*
*******************************************************************************/
uint32_t RTCLib_getMiliecond(uint64_t readTime)
{
    uint32 retVal;

    retVal  = ((readTime & RTC_MASK_100_MILISECONDS) >> RTC_100_MILISECONDS_SHIFT) * 100u;
    retVal  += ((readTime & RTC_MASK_10_MILISECONDS) >> RTC_10_MILISECONDS_SHIFT) * 10u;
    retVal += (readTime & RTC_MASK_MILISECONDS) >> RTC_MILISECONDS_SHIFT;

    return (int)(retVal);
}

/*******************************************************************************
* Function Name: RTCLib_getRecentMs
****************************************************************************//**
*
* \brief
*  reads the actual value of the millisecond timer
*
* \return
*  The miliseconds value.
*
*******************************************************************************/
uint32_t RTCLib_getRecentMs()
{
    uint16_t TmsRTC = 0;
    #ifdef USE_WDT_RTC
        TmsRTC = msRTC;
    #endif
    return TmsRTC;
}

/*******************************************************************************
* Function Name: RTCLibSync
********************************************************************************
*
* * synchronize time with an external RTC
*
* Return:
*  true(successful sync) or false(not successful sync))
*******************************************************************************/
bool RTCLibSync()
{
    return true;
}


/* [] END OF FILE */
