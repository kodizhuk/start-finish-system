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
#include "ff/ff.h"
#include "ff/diskio.h"

FATFS FatFs;

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    FIL fil;       /* File object */
    char line[82]; /* Line buffer */
    FRESULT fr;    /* FatFs return code */
    UINT br, bw;         /* File read/write count */
    BYTE buffer[30] = "hello world";

    fr = f_mount(0 ,&FatFs);
    fr = f_open(&fil, "TEST2.TXT", FA_WRITE | FA_OPEN_ALWAYS);
    if(fr == FR_OK)
    {

        fr = f_write(&fil, buffer, br, &bw);
        //fr = f_read(&fil, buffer, 10, &bw);

    }
    f_close(&fil);
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
