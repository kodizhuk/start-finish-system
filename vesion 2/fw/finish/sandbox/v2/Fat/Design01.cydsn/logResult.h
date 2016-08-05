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
#include <project.h>
#include "FatFs\diskio.h"
#include "FatFs\ff.h"
#include <stdio.h>

#define LEN_NAME    12
#define LEN_DATA    20
#define LEN_DATA_ALL    100

typedef struct 
{
    uint64_t unixStartSkier;
    uint16_t millsStartSkier;
    uint64_t unixFinishSkier;
    uint16_t millsFinishSkier;   
    uint64_t SecondsWay;
    uint16_t millsWay;
} skierDB_El;

FATFS fatFs;    /* File object */
FIL fileO;      /* File objects */

/*flag who shows that the establishment of the file*/
DWORD createFlag;   

uint32_t logStart(void);
uint32_t WriteSkierResult(skierDB_El *data);

/* [] END OF FILE */
