#include <RTC.h>
#include "lib_RTC\RTC_WDT.h"
#include <CyLFClk.h>

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


static uint64_t time;
static uint16_t msRTC = 0;

void CallBackCounter();


/*******************************************************************************
* Function Name: CallBackCounter
********************************************************************************
*
* Summary
*  miliseconds counter
*  RTC update each seconds
*
*******************************************************************************/
void CallBackCounter(void)
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
    }
}

/*******************************************************************************
* Function Name: RTC_WDT_Init
********************************************************************************
*
* Summary
*  Init watchdog counter
*
*******************************************************************************/
void RTC_WDT_Init(void)
{
    void (*CallBackWDT0)(void);   
    CallBackWDT0 = CallBackCounter;  
    RTC_Start();  
    CySysWdtSetInterruptCallback(0, CallBackWDT0);
    //WDT0_ISR_StartEx(Wdt0_Handler);
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
    return msRTC;
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

void RTCSync(uint32_t unixTime, uint16_t recentMs)
{
    msRTC = recentMs;
    RTC_SetUnixTime(unixTime);
}

/* [] END OF FILE */
