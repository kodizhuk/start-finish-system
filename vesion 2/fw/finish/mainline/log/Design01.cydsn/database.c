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
#include "database.h"


uint32_t dataBaseStart(void)
{
    uint8 resultF;
    
    /*/* Register work area to the default drive */
    resultF = f_mount(&fatFs, "", 1);
    
    return resultF;   
}


uint32_t WriteSkierRezult(struct skierDB *data)
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
    
    /*Construct name of file in format dd.mm.yyyy*/
    sprintf(nameFile,"%d_%d_%d.txt",nameDay,nameMonth,nameYear);
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
                
        RTC_UnixToDateTime(&time, data->unixtTimeStart, RTC_24_HOURS_FORMAT);
        sprintf(start, "\t\t%lu.%lu.%lu.%u",RTC_GetHours(time.time),RTC_GetMinutes(time.time),RTC_GetSecond(time.time),data->millisTimeStart);
        RTC_UnixToDateTime(&time, data->unixTimeFin, RTC_24_HOURS_FORMAT);
        sprintf(finish, "\t\t%lu.%lu.%lu.%u",RTC_GetHours(time.time),RTC_GetMinutes(time.time),RTC_GetSecond(time.time),data->millisTimeFin);
        RTC_UnixToDateTime(&time, data->unixTimeResult, RTC_24_HOURS_FORMAT);
        sprintf(result, "\t\t%lu.%lu.%lu.%u",RTC_GetHours(time.time),RTC_GetMinutes(time.time),RTC_GetSecond(time.time),data->millisResult);
        sprintf(writeData,"%d%s%s%s\n",position, start, finish, result); 
        
        if((position == 1) || (createFlag == 1))
        {
            f_printf(&fileO,"--------------------------------------------------\n");
            f_printf(&fileO,"NUM\t\tSTART\t\t\tFINISH\t\t\tRESULT\n");
            f_printf(&fileO,"--------------------------------------------------\n");
            
        }
        
        resultF = f_write(&fileO, writeData, strlen(writeData),&count);
        resultF = f_close(&fileO);
        position++;
    }    
    
    return resultF;
}
/* [] END OF FILE */
