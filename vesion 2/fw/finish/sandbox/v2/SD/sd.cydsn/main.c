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
#include "pff.h"
#include "xitoa.h"
#include "suart.h"

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    BYTE buff[50] = "NUMBER FINISH START REZULT"; //буфер для чтения файла
    UINT br; //счетчик прочитанных байт
    const char tfile[] = "TEST.TXT";
    FATFS fs; //объявление объекта FATFS
    FRESULT res; //переменная для возвращаемых значений
    FILINFO fno;		/* File information */
    
    res = pf_mount(&fs);
    if (res == FR_OK)
    { 
        if(pf_open(tfile) == FR_OK)
        {
            //pf_lseek(0);
            
            //res = pf_write(buff, 50, &br);
            res = pf_read(buff,50, &br);
            //res = pf_write(buff, 20, &br);
            if(res == FR_OK)
            {
                //pf_write(0, 0, &br);
                if (br != 32)
                {
                    
                } 
  
            }
        }
    }
    else
    {
            //не удалось смонтировать диск
     
    }
    
    for(;;)
    {
        
    }
}

/* [] END OF FILE */
