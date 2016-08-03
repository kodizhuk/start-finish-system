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
#include "diskio.h"
#include "ff.h"
#include <stdio.h>

#define LEN_NAME    12
#define LEN_DATA    20
#define LEN_DATA_ALL    100

struct skierDB
{
    uint64_t unixtTimeStart;
    uint32_t millisTimeStart;
    uint64_t unixTimeFin;
    uint32_t millisTimeFin;
    uint64_t unixTimeResult;
    uint32_t millisResult;
};

FATFS fatFs;    /* File object */
FIL fileO;      /* File objects */

/*flag who shows that the establishment of the file*/
DWORD createFlag;   

uint32_t dataBaseStart(void);
uint32_t WriteSkierRezult(struct skierDB *data);

/* [] END OF FILE */
