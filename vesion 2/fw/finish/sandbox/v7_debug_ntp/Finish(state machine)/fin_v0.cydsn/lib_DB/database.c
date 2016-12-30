
#include "lib_DB\database.h"

#define BUFFER_SIZE         MAX_SKIERS_ON_WAY + 4u
#define MAX_SKIERS_ON_DB    20u

struct elementBuff
{
    uint64_t unixStartSkier;
    uint16_t millsStartSkier;
    struct elementBuff* nextSki;
} bufferSkiersOnWay[BUFFER_SIZE];

typedef struct
{
    uint16_t    size;
    uint16_t    firstElement;                                
    uint16_t    lastElement; 
    
    uint16_t totalSize;
    /*buffer*/
    skierDB_El buffer[MAX_FIFO_SIZE]; 
    /*last output element*/
    skierDB_El last;
}fifoTimeSkier;

skierDB_El skierDB[MAX_SKIERS_ON_DB];
skierDB_El bufferFifo[MAX_SKIERS_ON_BUF];

uint32_t currentSizeBuff;
struct elementBuff *currentElementStart;
struct elementBuff *currentElementFinish;

uint16_t skiersStarted;
uint16_t skiersFinished;

fifoTimeSkier fifo;


uint32_t DataBaseStart(void)
{
    uint8_t result; 
    
    result = LogStart();
    if(result == FR_OK)
    {
        result = DB_NO_ERROR;
    }else
    {
        result = DB_ERROR;
    }
    return result;
}

void InitBuff()
{
    uint8_t i;
    
    /*init fifo*/
    fifo.totalSize = MAX_FIFO_SIZE;
    
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


void WriteStartTime(uint64_t unixTime, uint16_t mills)
{
    putSkiOnWay(unixTime, mills);
}


void WriteFinishTime(uint64_t unixTime, uint16_t mills)
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
}

uint32_t SkierOnWay()
{
    return currentSizeBuff;
}

uint32_t TimeOnWay(uint32_t Number)
{
    skierDB[Number].secondsWay =  skierDB[Number].unixFinishSkier - skierDB[Number].unixStartSkier;  
    skierDB[Number].millsWay =  skierDB[Number].millsFinishSkier - skierDB[Number].millsStartSkier;  
    if (skierDB[Number].millsWay > 1000u)
    {
        skierDB[Number].secondsWay--;
        skierDB[Number].millsWay = 0 - skierDB[Number].millsWay;
    }
    return 1u;
}

uint32_t LastSecTimeOnWay()
{
    uint32_t tmpData;
    if (skiersFinished == 0)
    {
        tmpData = skierDB[MAX_SKIERS_ON_DB - 1].secondsWay;
    }
    else
    {
        tmpData = skierDB[skiersFinished - 1].secondsWay;
    }

    return tmpData;
}

uint32_t LastMillsTimeOnWay()
{
    uint32_t tmpData;
    if (skiersFinished == 0)
    {
        tmpData = skierDB[MAX_SKIERS_ON_DB - 1].millsWay;
    }
    else
    {
        tmpData = skierDB[skiersFinished-1].millsWay;
    }
    return tmpData;
}


/*FIFO*/
uint16_t FifoGetSize(void)
{
    return fifo.size;
}

void FifoPush(skierDB_El data)
{
    if (fifo.size<fifo.totalSize)           
    {                                                  
        ++fifo.size;                               
                                                       
        fifo.buffer[fifo.lastElement++] = data;  
                                                       
        if (fifo.lastElement == fifo.totalSize) 
            fifo.lastElement = 0;
    }  
}

void FifoGet(skierDB_El *data)                    
{                                                   
    if (fifo.size != 0)                             
    {                                                           
        *data = fifo.buffer[fifo.firstElement++];
                                                        
        if (fifo.firstElement == fifo.totalSize) 
            fifo.firstElement = 0;  
        
        --fifo.size;                               
    }                                                  
}

void FifoPushLast(skierDB_El data)
{
    fifo.last = data;
}

skierDB_El FifoGetLast(void)
{
    return fifo.last;
}

void FifoPushLastFinished()
{
    if (skiersFinished == 0)
    {
        FifoPush(skierDB[MAX_SKIERS_ON_DB - 1]);
    }
    else
    {
        FifoPush(skierDB[skiersFinished-1]);    
    }
}

/* [] END OF FILE */