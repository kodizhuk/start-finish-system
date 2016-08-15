
#include <project.h>
#include <stdio.h>

#include "lib_Fat\diskio.h"
#include "lib_Fat\ff.h"
#include "lib_DB\database.h"

/*lenth name .txt file*/
#define LEN_NAME        20
/*lenth buffer from time skier*/
#define LEN_DATA        20
/*len buffer to save information on SD card*/
#define LEN_DATA_ALL    100


FATFS fatFs;    /* File object */
FIL fileO;      /* File info */

/*flag who shows that the establishment of the file*/
DWORD createFlag;   


uint32_t LogStart(void);
uint32_t WriteSkierResult(skierDB_El *data);


/* [] END OF FILE */
