#include <CyLib.h>
#include <stdio.h>
#include <RTC.h>
#include <project.h>

#include "lib_Fat\diskio.h"
#include <lib_BLE/bluetooth.h>
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

static char nameFile[LEN_NAME];
static uint32_t idSkier = 1;
static uint32_t position = 1;

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

/*read and send bluetooth skier result*/
uint32_t ReadSkierResultAndSendBLE(void)
{
    uint32_t resultF;
    char line[82];
    
    /*for send to buetooth*/
    uint16_t sendIdSkier ;
    uint16_t sendStartTime[LENGHT_DATA_BUFFER];
    uint16_t sendFinishTime[LENGHT_DATA_BUFFER];
    uint16_t sendResultTime[LENGHT_DATA_BUFFER];
    
    createFlag = 0;    
    resultF = f_open(&fileO, nameFile, FA_READ , &createFlag);
    
    while (f_gets(line, sizeof line, &fileO))
    {    
        uint32_t pointer = 0;
        uint32_t coeff = 1;
        uint8_t counterMas = 0;
        
        typedef enum {MAS_START_TIME,MAS_FINISH_TIME, MAS_RESULT_TIME}numMas;
        numMas currentMas ;
        
        if(isdigit(line[pointer]))
        {
            /*clear buffer*/
            int i;
            for(i=0;i<4; i++)
            {
                sendStartTime[i] = 0;
                sendFinishTime[i] = 0;
                sendResultTime[i] = 0;
            }
            
            /*write id skier*/
            sendIdSkier = 0;
            while(isdigit(line[pointer]))
            {
                sendIdSkier = sendIdSkier*coeff + (line[pointer]-'0');
                pointer++;
                coeff *= 10;
            }
            
            currentMas = MAS_START_TIME;
            while((line[pointer] != '\n') && (line[pointer] != '\r'))
            {            
                /*write time start skier*/
                coeff = 1;
                counterMas = 0;
                while(isdigit(line[pointer]) || (line[pointer] == ':'))
                {
                    if(line[pointer] == ':')
                    {
                        counterMas++;
                        coeff = 1;
                    }
                    else
                    {
                        switch (currentMas){
                            case MAS_START_TIME:
                                sendStartTime[counterMas] = sendStartTime[counterMas]*coeff + (line[pointer]-'0');
                                break;
                            case MAS_FINISH_TIME:
                                sendFinishTime[counterMas] = sendFinishTime[counterMas]*coeff + (line[pointer]-'0');
                                break;
                            case MAS_RESULT_TIME:
                                sendResultTime[counterMas+2] = sendResultTime[counterMas+2]*coeff + (line[pointer]-'0');
                                break;
                        }
                        coeff = 10;
                    }
                    pointer++;
                }
                if(coeff != 1)
                {
                    if(currentMas == MAS_RESULT_TIME)
                    {
                        currentMas = MAS_START_TIME;
                    }else{
                        currentMas++;
                    }
                    
                    counterMas = 0;
                    
                }
                pointer++;
            }
                       
            
            BLE_sendOneSkierTimeAll(sendIdSkier, sendStartTime, sendFinishTime, sendResultTime);
            BLE_processEvents();
            CyDelay(100);
        }
    }
    resultF = f_close(&fileO);
        
    return resultF;
}

uint32_t GetIDskierStarted(void)
{
    return idSkier;
}

uint32_t GetIDskierFinished(void)
{
    return position-1;
}

void IncrementID(void)
{
    idSkier++;
}
/* [] END OF FILE */
