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
#include "logResult.h"


uint32_t logStart(void)
{
    uint8 resultF;
    
    /*/* Register work area to the default drive */
    resultF = f_mount(&fatFs, "", 1);
    
    return resultF;   
}


uint32_t WriteSkierResult(skierDB_El *data)
{
    uint8 resultF;
    uint count;
    
    char nameFile[LEN_NAME];
    uint32_t nameYear;
    uint32_t nameMonth;
    uint32_t nameDay;
    uint32_t date;
    
    date = RTC_GetDate();
    nameYear = RTC_GetYear(date)-2000;
    nameMonth = RTC_GetMonth(date);
    nameDay = RTC_GetDay(date);
    
    /*Construct name of file in format ddmmyyyy*/
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
                
        RTC_UnixToDateTime(&time, data->unixStartSkier, RTC_24_HOURS_FORMAT);
        sprintf(start, "\t\t%02lu:%02lu:%02lu:%03u",RTC_GetHours(time.time),RTC_GetMinutes(time.time),RTC_GetSecond(time.time),data->millsStartSkier);
        RTC_UnixToDateTime(&time, data->unixFinishSkier, RTC_24_HOURS_FORMAT);
        sprintf(finish, "\t\t%02lu:%02lu:%02lu:%03u",RTC_GetHours(time.time),RTC_GetMinutes(time.time),RTC_GetSecond(time.time),data->millsFinishSkier);
        sprintf(result, "\t\t%02lu:%03u",(uint32)data->SecondsWay,data->millsWay);
        sprintf(writeData,"%d%s%s%s\n",position, start, finish, result); 
        
        if((position == 1) || (createFlag == 1))
        {
            uint32_t tmpTime ;
            
            tmpTime = RTC_GetTime();
            f_printf(&fileO,"\nSystem started %02d:%02d:%02d\n", RTC_GetHours(tmpTime),RTC_GetMinutes(tmpTime),RTC_GetSecond(tmpTime));
            f_printf(&fileO,"--------------------------------------------------\n");
            f_printf(&fileO,"NUM\t\tSTART\t\t\t\tFINISH\t\t\t\tRESULT\n");
            f_printf(&fileO,"--------------------------------------------------\n");
            
        }
        
        /*write data*/
        resultF = f_write(&fileO, writeData, strlen(writeData),&count);
        resultF = f_close(&fileO);
        position++;
    }
    
    return resultF;
}

/* [] END OF FILE */
