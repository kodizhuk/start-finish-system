
#include "..\..\common\lib\lib_DB\database.h"

#define BUFFER_SIZE         MAX_SKIERS_ON_WAY

void putSkiOnWay(uint8_t id, uint64_t unixTime, uint16_t mills);
void getSkiFromWay(uint8_t *id, uint64_t *unixTime, uint16_t *mills);

struct elementBuff
{
    uint8_t idSkier;
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

skierDB_El skierDB;

uint32_t currentSizeBuff;
struct elementBuff *currentElementStart;
struct elementBuff *currentElementEnd;

fifoTimeSkier fifo;     //if no SD card


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
    currentElementEnd = &bufferSkiersOnWay[0];
}

/*******************************************************************************
* Function Name: putSkiOnWay
********************************************************************************
*
* Summary:
*  save start time skier
*
*******************************************************************************/
void putSkiOnWay(uint8_t id, uint64_t unixTime, uint16_t mills)
{
    currentElementStart->idSkier = id;
    currentElementStart->millsStartSkier = mills;
    currentElementStart->unixStartSkier = unixTime;
    currentElementStart = currentElementStart->nextSki;
    currentSizeBuff++;
}

/*******************************************************************************
* Function Name: getSkiFromWay
********************************************************************************
*
* Summary:
*  get start time skier
*
*******************************************************************************/
void getSkiFromWay(uint8_t *id,uint64_t *unixTime, uint16_t *mills)
{
    *id = currentElementEnd->idSkier;
    *mills = currentElementEnd->millsStartSkier;
    *unixTime = currentElementEnd->unixStartSkier;
    currentElementStart = currentElementEnd->nextSki;
    currentSizeBuff--;
}

/*******************************************************************************
* Function Name: WriteStartTime
********************************************************************************
*
* Summary:
*  save start time skier
*
*******************************************************************************/
void WriteStartTime(uint8_t id, uint64_t unixTime, uint16_t mills)
{
    putSkiOnWay(id, unixTime, mills);
}


void WriteFinishTime(uint64_t unixTime, uint16_t mills)
{   
    getSkiFromWay(&skierDB.idSkier, &skierDB.unixStartSkier, &skierDB.millsStartSkier);
    skierDB.millsFinishSkier = mills;
    skierDB.unixFinishSkier = unixTime;
    
    /*calculate time on way*/
    skierDB.secondsWay =  skierDB.unixFinishSkier - skierDB.unixStartSkier;  
    skierDB.millsWay =  skierDB.millsFinishSkier - skierDB.millsStartSkier;  
    if (skierDB.millsWay > 1000u)
    {
        skierDB.secondsWay--;
        skierDB.millsWay = 0 - skierDB.millsWay;
    }
    FifoPush(skierDB);
}

uint32_t SkierOnWay()
{
    return currentSizeBuff;
}


uint32_t LastSecTimeOnWay()
{
    uint32_t tmpData;
    
    tmpData = skierDB.secondsWay;

    return tmpData;
}

uint32_t LastMillsTimeOnWay()
{
    uint32_t tmpData;

    tmpData = skierDB.millsWay;

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

/* [] END OF FILE */