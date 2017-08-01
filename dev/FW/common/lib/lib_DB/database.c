
#include "..\..\common\lib\lib_DB\database.h"

#define BUFFER_SIZE         MAX_SKIERS_ON_WAY

void putSkiOnWay(uint8_t id, uint64_t unixTime, uint16_t mills);
void getSkiFromWay(uint8_t *id, uint64_t *unixTime, uint16_t *mills, uint8_t permiss);

struct elementBuff
{
    uint8_t idStartSkier;
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

/*******************************************************************************
* Function Name: DataBaseStart
********************************************************************************
*
* Summary:
*  init log from write to SD card
*
* Return:
*   result - DB_NO_ERROR or DB_ERROR
*******************************************************************************/
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

/*******************************************************************************
* Function Name: InitBuff
********************************************************************************
*
* Summary:
*  init ring buffer from write started skier
*
*******************************************************************************/
void InitBuff(void)
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
void putSkiOnWay(uint8_t idSkier, uint64_t unixTime, uint16_t mills)
{
    currentElementStart->idStartSkier = idSkier;
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
void getSkiFromWay(uint8_t *id,uint64_t *unixTime, uint16_t *mills, uint8_t permiss)
{
    *id = currentElementEnd->idStartSkier;
    *mills = currentElementEnd->millsStartSkier;
    *unixTime = currentElementEnd->unixStartSkier;
    if(permiss)
    {
        currentElementEnd = currentElementEnd->nextSki;
        currentSizeBuff--;
    }
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

/*******************************************************************************
* Function Name: WriteFinishTime
********************************************************************************
*
* Summary:
*  write finish time in tmp buffer and put in fifo
*
* Parametrs:
*   unixTime - skier finished time, seconds
*   mills - skier finished time, miliseconds
*******************************************************************************/
void WriteFinishTime(uint64_t unixTime, uint16_t mills, uint8_t permiss)
{   
    getSkiFromWay(&skierDB.idSkier, &skierDB.unixStartSkier, &skierDB.millsStartSkier, permiss);
    skierDB.millsFinishSkier = mills;
    skierDB.unixFinishSkier = unixTime;
    skierDB.permiss = permiss;
    
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

/*******************************************************************************
* Function Name: SkierOnWay
********************************************************************************
*
* Summary:
*  skier on way
*
* Return:
*   num skier on way
*******************************************************************************/
uint32_t SkierOnWay()
{
    return currentSizeBuff;
}

/*******************************************************************************
* Function Name: LastSecTimeOnWay
********************************************************************************
*
* Summary:
*  last time skier, sec
*
* Return:
*   time second on way
*******************************************************************************/
uint32_t LastSecTimeOnWay()
{
    uint32_t tmpData;
    
    tmpData = skierDB.secondsWay;

    return tmpData;
}

/*******************************************************************************
* Function Name: LastMillsTimeOnWay
********************************************************************************
*
* Summary:
*  last time skier, milliseconds
*
* Return:
*   time milliseconds on way
*******************************************************************************/
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