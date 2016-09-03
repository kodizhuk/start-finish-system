#include <CyLib.h>
#include <stdio.h>
#include <RTC.h>

#include "lib_Fat\diskio.h"
#include "logResult.h"

/* lenth name .txt file */
#define LEN_NAME        20

/* lenth buffer from time skier */
#define LEN_DATA        20

/* len buffer to save information on SD card */
#define LEN_DATA_ALL    100


FATFS fatFs;    /* File object */
FIL fileO;      /* File info */

/* flag who shows that the establishment of the file */
DWORD createFlag;  



/*******************************************************************************
* Function Name: LogStart
********************************************************************************
*
* Summary:
*  Start log system(mount fat)
*
* Return:
*   resultF - result mount FAT system (from enum FRESULT)
*
*******************************************************************************/
uint32_t LogStart(void)
{
    uint8 resultF;
    
    /* Register work area to the default drive */
    resultF = f_mount(&fatFs, "", 1);
    
    return resultF;   
}


/*******************************************************************************
* Function Name: WriteSkierResult
********************************************************************************
*
* Summary:
*  Start log system(mount fat)
*
* Parametrs:
*   *data - pointer from result skiers
* Return:
*   resultF - result mount FAT system (from enum FRESULT)
*
*******************************************************************************/
uint32_t WriteSkierResult(skierDB_El *data)
{
    uint8 resultF;
    uint count;
    
    char nameFile[LEN_NAME];
    uint32_t nameYear;
    uint32_t nameMonth;
    uint32_t nameDay;
    uint32_t date;
    
    /*get date from RTC*/
    date = RTC_GetDate();
    nameYear = RTC_GetYear(date)-2000;
    nameMonth = RTC_GetMonth(date);
    nameDay = RTC_GetDay(date);
    
    /*Construct name of file in format dd_mm_yyyy*/
    sprintf(nameFile,"%02d_%02d_%d.txt",nameDay,nameMonth,nameYear);
    createFlag = 0;
    resultF = f_open(&fileO, nameFile, FA_WRITE | FA_OPEN_APPEND, &createFlag);
    
    if(resultF == RES_OK)
    {
        /*Construct save data*/
        char start[LEN_DATA];
        char finish[LEN_DATA];
        char result[LEN_DATA];
        char writeData[LEN_DATA_ALL];
        
        RTC_DATE_TIME time;
        static uint32_t position = 1;
        
        /*read unix time*/
        RTC_UnixToDateTime(&time, data->unixStartSkier, RTC_24_HOURS_FORMAT);
        sprintf(start, "\t\t%02lu:%02lu:%02lu:%03u",RTC_GetHours(time.time),RTC_GetMinutes(time.time),RTC_GetSecond(time.time),data->millsStartSkier);
        RTC_UnixToDateTime(&time, data->unixFinishSkier, RTC_24_HOURS_FORMAT);
        sprintf(finish, "\t\t%02lu:%02lu:%02lu:%03u",RTC_GetHours(time.time),RTC_GetMinutes(time.time),RTC_GetSecond(time.time),data->millsFinishSkier);
        sprintf(result, "\t\t%02lu:%03u",(uint32)data->secondsWay,data->millsWay);
        sprintf(writeData,"\n\r%d%s%s%s\n\r",position, start, finish, result); 
              
        if((position == 1) || (createFlag == 1))
        {
            /*write new "cap"*/
            uint32_t tmpTime ;
            
            tmpTime = RTC_GetTime();
            f_printf(&fileO,"\r\nSystem started %02d:%02d:%02d\n\r", RTC_GetHours(tmpTime),RTC_GetMinutes(tmpTime),RTC_GetSecond(tmpTime));
            f_printf(&fileO,"--------------------------------------------------\n\r");
            f_printf(&fileO,"NUM\t\tSTART\t\t\tFINISH\t\t\tRESULT\n\r");
            f_printf(&fileO,"--------------------------------------------------\n\r");
            
        }
        
        /*write data*/
        resultF = f_write(&fileO, writeData, strlen(writeData),&count);
        resultF = f_close(&fileO);
        position++;
    }
    
    return resultF;
}

/* [] END OF FILE */
