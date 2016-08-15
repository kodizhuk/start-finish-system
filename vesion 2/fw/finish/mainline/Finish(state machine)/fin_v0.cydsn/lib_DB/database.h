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

#ifndef _DATABASE_H
#define _DATABASE_H

#include <stdint.h>
#include <stdbool.h>


#define MAX_SKIERS_ON_WAY   4u
#define MAX_SKIERS_ON_BUF   8u
#define BUFFER_SIZE         MAX_SKIERS_ON_WAY + 4u
#define MAX_SKIERS_ON_DB    150u
#define MAX_FIFO_SIZE       MAX_SKIERS_ON_BUF + MAX_SKIERS_ON_WAY
#define DB_START            1
#define DB_NO_START         0
    
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

struct elementBuff
{
    uint64_t unixStartSkier;
    uint16_t millsStartSkier;
    struct elementBuff* nextSki;
} bufferSkiersOnWay[BUFFER_SIZE];

skierDB_El bufferFifo[MAX_SKIERS_ON_BUF];

uint32_t currentSizeBuff;
struct elementBuff *currentElementStart;
struct elementBuff *currentElementFinish;

uint16_t skiersStarted;
uint16_t skiersFinished;

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


#endif
/* [] END OF FILE */