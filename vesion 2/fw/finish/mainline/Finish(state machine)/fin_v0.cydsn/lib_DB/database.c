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
#include "lib_DB\database.h"

uint32_t DataBaseStart(void)
{
    uint32_t result; 
    result = logStart();
    return result;
}

void InitBuff()
{
    uint32_t i;
    for( i = 0; i< BUFFER_SIZE - 1; i++)
    {
        bufferSkiersOnWay[i].nextSki = &bufferSkiersOnWay[i+1];
    }
    bufferSkiersOnWay[BUFFER_SIZE - 1].nextSki = &bufferSkiersOnWay[0];
    currentElementStart = &bufferSkiersOnWay[0];
    currentElementFinish = &bufferSkiersOnWay[0];
}

void putSkiOnWay(uint64_t unixTime, uint16_t mills)
{
    currentElementFinish->millsStartSkier = mills;
    currentElementFinish->unixStartSkier = unixTime;
    currentElementFinish = currentElementFinish->nextSki;
    currentSizeBuff++;
}

void getSkiFromWay(uint64_t *unixTime, uint16_t *mills)
{
    *mills = currentElementStart->millsStartSkier;
    *unixTime = currentElementStart->unixStartSkier;
    currentElementStart = currentElementStart->nextSki;
    currentSizeBuff--;
}


bool WriteStartTime(uint64_t unixTime, uint16_t mills)
{
    putSkiOnWay(unixTime, mills);
/*
    if (skiersStarted == MAX_SKIERS_ON_DB)
    {
        skiersStarted = 0;
    }
    skierDB[skiersStarted].millsStartSkier = mills;
    skierDB[skiersStarted].unixStartSkier = unixTime;
    skiersStarted++;
    return true;
*/
    return 1u;
}


bool WriteFinishTime(uint64_t unixTime, uint16_t mills)
{
    
    if (skiersFinished == MAX_SKIERS_ON_DB)
    {
        skiersFinished = 0;
    }
    getSkiFromWay(&skierDB[skiersFinished].unixStartSkier, &skierDB[skiersFinished].millsStartSkier);
    skierDB[skiersFinished].millsFinishSkier = mills;
    skierDB[skiersFinished].unixFinishSkier = unixTime;
    TimeOnWay(skiersFinished);
    skiersFinished++;
    return true;
}

uint32_t SkierOnWay()
{
    return currentSizeBuff;
}

uint32_t TimeOnWay(uint32_t Number)
{
    skierDB[Number].SecondsWay =  skierDB[Number].unixFinishSkier - skierDB[Number].unixStartSkier;  
    skierDB[Number].millsWay =  skierDB[Number].millsFinishSkier - skierDB[Number].millsStartSkier;  
    if (skierDB[Number].millsWay > 1000u)
    {
        skierDB[Number].SecondsWay--;
        skierDB[Number].millsWay = 0 - skierDB[Number].millsWay;
    }
    return 1u;
}

uint32_t LastSecTimeOnWay()
{
    uint32_t tmpData;
    if (skiersFinished == 0)
    {
        tmpData = skierDB[MAX_SKIERS_ON_DB].SecondsWay;
    }
    else
    {
        tmpData = skierDB[skiersFinished-1].SecondsWay;
    }
    return tmpData;
}

uint32_t LastMillsTimeOnWay()
{
    uint32_t tmpData;
    if (skiersFinished == 0)
    {
        tmpData = skierDB[MAX_SKIERS_ON_DB].millsWay;
    }
    else
    {
        tmpData = skierDB[skiersFinished-1].millsWay;
    }
    return tmpData;
}

/* [] END OF FILE */