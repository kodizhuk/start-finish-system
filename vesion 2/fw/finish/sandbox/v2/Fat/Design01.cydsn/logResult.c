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


/*******************************************************************************
* Function Name: logStart
********************************************************************************
*
* Summary:
*  mount file system
*
*******************************************************************************/
uint32_t logStart(void)
{
    uint8 resultF;
    
    /*/* Register work area to the default drive */
    resultF = f_mount(&fatFs, "", 1);
    
    return resultF;   
}


/*******************************************************************************
* Function Name: WriteSkierResult
********************************************************************************
*
* Summary:
*  Save data in SD card
* Parametrs:
*   *data -  structure results skiers
* Return:
*   Error code 
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
                
        RTC_UnixToDateTime(&time, data->unixStartSkier, RTC_24_HOURS_FORMAT);
        sprintf(start, "\t\t%lu.%lu.%lu.%u",RTC_GetHours(time.time),RTC_GetMinutes(time.time),RTC_GetSecond(time.time),data->millsStartSkier);
        RTC_UnixToDateTime(&time, data->unixFinishSkier, RTC_24_HOURS_FORMAT);
        sprintf(finish, "\t\t%lu.%lu.%lu.%u",RTC_GetHours(time.time),RTC_GetMinutes(time.time),RTC_GetSecond(time.time),data->millsFinishSkier);
        sprintf(result, "\t\t%lu.%u",(uint32)data->SecondsWay,data->millsWay);
        sprintf(writeData,"%d%s%s%s\n",position, start, finish, result); 
        
        if((position == 1) || (createFlag == 1))
        {
            f_printf(&fileO,"--------------------------------------------------\n");
            f_printf(&fileO,"NUM\t\tSTART\t\t\tFINISH\t\t\tRESULT\n");
            f_printf(&fileO,"--------------------------------------------------\n");
            
        }
        
        /*write data*/
        resultF = f_write(&fileO, writeData, strlen(writeData),&count);
        resultF = f_close(&fileO);
        position++;
    }else 
    {
        /*If the error recording, then try again mounted sd card*/
        resultF = f_mount(&fatFs, "", 1);
        if(resultF == RES_OK)
        {
            resultF = WriteSkierResult(data);
        }
    }
    
    return resultF;
}
/* [] END OF FILE */
