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
#include <stdio.h>
#include "lib_Fat\diskio.h"
#include "lib_Fat\ff.h"
#include "lib_DB\database.h"


#define LEN_NAME    20
#define LEN_DATA    20
#define LEN_DATA_ALL    100


FATFS fatFs;    /* File object */
FIL fileO;      /* File info */

/*flag who shows that the establishment of the file*/
DWORD createFlag;   

uint32_t logStart(void);
uint32_t WriteSkierResult(skierDB_El *data);


/* [] END OF FILE */
