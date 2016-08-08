#ifndef _DATABASE_H
#define _DATABASE_H

#include <stdint.h>
#include <stdbool.h>

/* The maximum number of skiers that may be issued on the track */
#define MAX_SKIERS_ON_WAY   4u

/* Description FIFO which is used to record deferred to SD card*/
/* The maximum number of skiers that may be saved on the main part FIFO */
#define MAX_SKIERS_ON_BUF   8u
/* Backup buffer share further to the FIFO may contain the maximum number of skiers on the track */
#define MAX_FIFO_SIZE       MAX_SKIERS_ON_BUF + MAX_SKIERS_ON_WAY
/* End description FIFO*/

/* Buffer which saved start time skiers until they not finish */
#define BUFFER_SIZE         MAX_SKIERS_ON_WAY
/* Max saved skiers which can be saved on internal database*/
#define MAX_SKIERS_ON_DB    150u

/* */
#define DB_START            1
#define DB_NO_START         0
   
/* Struct one element on database*/   
typedef struct 
{
    uint64_t unixStartSkier;
    uint16_t millsStartSkier;
    uint64_t unixFinishSkier;
    uint16_t millsFinishSkier;   
    uint64_t SecondsWay;
    uint16_t millsWay;
}skierDB_El;

#include "lib_DB\logResult.h"

/* Struct one element on buffer*/
struct elementBuff
{
    uint64_t unixStartSkier;
    uint16_t millsStartSkier;
    struct elementBuff* nextSki;
} bufferSkiersOnWay[BUFFER_SIZE];

/* FIFO which is used to record deferred to SD card */
skierDB_El bufferFifo[MAX_SKIERS_ON_BUF];

/* Current size Buffer */
uint32_t currentSizeBuff;

/* Tail and Head buffer */
struct elementBuff *currentElementStart;
struct elementBuff *currentElementFinish;

/* Count finished skiers*/
uint16_t skiersFinished;

/* Internal database*/
skierDB_El skierDB[MAX_SKIERS_ON_DB];

uint32_t DataBaseStart(void);
void InitBuff();

bool WriteStartTime(uint64_t unixTime, uint16_t mills);
bool WriteFinishTime(uint64_t unixTime, uint16_t mills);

uint32_t TimeOnWay(uint32_t Number);
uint32_t SkierOnWay();
uint32_t LastSecTimeOnWay();
uint32_t LastMillsTimeOnWay();

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

fifoTimeSkier fifo;

uint16_t FifoGetSize(void);
void FifoPush(skierDB_El data);
void FifoGet(skierDB_El *data); 
void FifoPushLast(skierDB_El data);


#endif /* _DATABASE_H */
/* [] END OF FILE */