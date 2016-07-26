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
#include "ff.h"
#include "diskio.h"

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    BYTE buff[50]  = {0,0,0,0,0,0,0,0,0,0,0,0}; //буфер для чтения файла
    UINT br; //счетчик прочитанных байт
    const char tfile[] = "TEST.TXT";
    
    FATFS FatFs; //объявление объекта FATFS
    FRESULT fr; //переменная для возвращаемых значений
    FIL fil;		/* File information */
    
    fr = f_mount(&FatFs, "", 0);
    if(fr == FR_OK)
    {
        fr = f_open(&fil, "TEST.TXT", FA_READ);
        for(;;)
        {
            fr = f_read(&fil, buff, 10, &br);
            if (fr || br == 0) break; /* error or eof */
        }
        f_close(&fil);
    }
    for(;;)
    {
        
    }
}

/* [] END OF FILE */
