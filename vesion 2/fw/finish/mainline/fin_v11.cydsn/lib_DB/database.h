
#ifndef _DATABASE_H
    #define _DATABASE_H

#include <CyLib.h>


#define MAX_SKIERS_ON_WAY   4u
#define MAX_SKIERS_ON_BUF   8u
#define MAX_FIFO_SIZE       MAX_SKIERS_ON_BUF + MAX_SKIERS_ON_WAY
#define DB_NO_ERROR            1
#define DB_ERROR        0
    
typedef struct 
{
    uint64_t unixStartSkier;
    uint16_t millsStartSkier;
    uint64_t unixFinishSkier;
    uint16_t millsFinishSkier;
    uint64_t secondsWay;
    uint16_t millsWay;
}skierDB_El;

#include "lib_DB\logResult.h"

uint32_t DataBaseStart(void);
void InitBuff();

void WriteStartTime(uint64_t unixTime, uint16_t mills);
void WriteFinishTime(uint64_t unixTime, uint16_t mills);

uint32_t TimeOnWay(uint32_t Number);
uint32_t SkierOnWay();
uint32_t LastSecTimeOnWay();
uint32_t LastMillsTimeOnWay();


uint16_t FifoGetSize(void);
void FifoPush(skierDB_El data);
void FifoGet(skierDB_El *data); 
void FifoPushLast(skierDB_El data);
skierDB_El FifoGetLast(void);
void FifoPushLastFinished();

#endif
/* [] END OF FILE */