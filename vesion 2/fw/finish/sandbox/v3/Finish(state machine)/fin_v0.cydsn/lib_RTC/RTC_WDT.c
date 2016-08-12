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

#include "lib_RTC\RTC_WDT.h"
#include <SW_UART_PC.h>

static uint64_t time;

uint32_t RTCSyncWithDS = 0;

#ifdef USE_WDT_RTC

    uint16_t msRTC = 0;

void CallBackCounter()
{
    msRTC++;
    if (msRTC == 1000u) 
    {
        msRTC = 0u; 
        RTC_Update();
        #ifdef DEBUG_RTC
            debug_Write(1);
            debug_Write(0);
        #endif
        //SW_UART_PC_PutString("Second Goes\r\n");
    }
}

#endif

#ifdef DEBUG_TIME

static uint16_t timeRestart = 0;

void CallBackCounter2()
{
    timeRestart++;
    if (timeRestart == 120) 
    {
        timeRestart = 0u; 
        debug_reset_fin_Write(0);
        CyDelay(100);
        debug_reset_fin_Write(1);
    }
}

#endif

void RTC_WDT_Init(){
    void (*CallBackWDT0)(void);
    
    CallBackWDT0 = CallBackCounter;
    
    #ifdef DEBUG_TIME
    void (*CallBackWDT1)(void);  
    CallBackWDT1 = CallBackCounter2;
    #endif
    
    RTC_Start();
    
    #ifdef USE_WDT_RTC
        CySysWdtSetInterruptCallback(0, CallBackWDT0);
        //WDT0_ISR_StartEx(Wdt0_Handler);
    #endif
    
    #ifdef DEBUG_TIME
        CySysWdtSetInterruptCallback(1, CallBackWDT1);
        //WDT0_ISR_StartEx(Wdt0_Handler);
    #endif
}

uint32_t RTCSynced(void)
{
    return RTCSyncWithDS;
}

/*******************************************************************************
* Function Name: RTCgetTime
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
uint64_t RTCgetTime(uint64_t timeFormat)
{
    uint32_t readTime;
    uint64_t hour, min, sec, ms, stateAmPm;

    
    readTime = RTC_GetTime();
    hour = RTC_GetHours(readTime);
    min = RTC_GetMinutes(readTime);
    sec = RTC_GetSecond(readTime);
    ms = RTCgetRecentMs();
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
* Function Name: RTCgetHours
****************************************************************************//**
*
* \brief
*  Returns the hours value 
*
* \return
*  The hours value.
*
*******************************************************************************/

uint64_t RTCGetUnixTime(void)
{
    return RTC_GetUnixTime();
}


uint32_t RTCgetHours(uint64_t readTime)
{
    uint64_t retVal;
    
    retVal  = ((readTime & RTC_MASK_10_HOURS) >> RTC_10_HOURS_SHIFT) * 10u;
    retVal += (readTime & RTC_MASK_HOURS) >> RTC_HOURS_SHIFT;
    
    return (int)(retVal);
}

/*******************************************************************************
* Function Name: RTCgetMinutes
****************************************************************************//**
*
* \brief
*  Returns the minutes value 
*
* \return
*  The minutes value.
*
*******************************************************************************/
uint32_t RTCgetMinutes(uint64_t readTime)
{
    uint64 retVal;

    retVal  = ((readTime & RTC_MASK_10_MINUTES) >> RTC_10_MINUTES_SHIFT) * 10u;
    retVal += (readTime & RTC_MASK_MINUTES) >> RTC_MINUTES_SHIFT;

    return (int)(retVal);
}

/*******************************************************************************
* Function Name: RTCgetSecond
****************************************************************************//**
*
* \brief
*  Returns the seconds value 
*
* \return
*  The seconds value.
*
*******************************************************************************/
uint32_t RTCgetSecond(uint64_t readTime)
{
    uint32 retVal;

    retVal  = ((readTime & RTC_MASK_10_SECONDS) >> RTC_10_SECONDS_SHIFT) * 10u;
    retVal += (readTime & RTC_MASK_SECONDS) >> RTC_SECONDS_SHIFT;

    return (int)(retVal);
}

/*******************************************************************************
* Function Name: RTCgetMilisecond
****************************************************************************//**
*
* \brief
*  Returns the miliseconds value 
*
* \return
*  The miliseconds value.
*
*******************************************************************************/
uint32_t RTCgetMiliecond(uint64_t readTime)
{
    uint32 retVal;

    retVal  = ((readTime & RTC_MASK_100_MILISECONDS) >> RTC_100_MILISECONDS_SHIFT) * 100u;
    retVal  += ((readTime & RTC_MASK_10_MILISECONDS) >> RTC_10_MILISECONDS_SHIFT) * 10u;
    retVal += (readTime & RTC_MASK_MILISECONDS) >> RTC_MILISECONDS_SHIFT;

    return (int)(retVal);
}

/*******************************************************************************
* Function Name: RTCgetRecentMs
****************************************************************************//**
*
* \brief
*  reads the actual value of the millisecond timer
*
* \return
*  The miliseconds value.
*
*******************************************************************************/
uint32_t RTCgetRecentMs()
{
    uint16_t TmsRTC = 0;
    #ifdef USE_WDT_RTC
        TmsRTC = msRTC;
    #endif
    return TmsRTC;
}

/*******************************************************************************
* Function Name: RTS_Sync
********************************************************************************
*
* * synchronize time with an external RTC
*
* Return:
*  true(successful sync) or false(not successful sync))
*******************************************************************************/
/*
bool RTCSync()
{
    return true;
}
*/
/* [] END OF FILE */
