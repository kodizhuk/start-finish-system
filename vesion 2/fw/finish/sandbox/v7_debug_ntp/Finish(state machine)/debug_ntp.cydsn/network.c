
#include "network.h"
//#include <lib_BLE/bluetooth.h>
#include <UART_XB.h>
#include <UART_XB_SPI_UART.h>
#include "project.h"

#ifdef DEBUG_INFO
    #include <SW_uartDebug.h>
#endif
#ifdef DEBUG_TIME
    #include <debug.h>
#endif
#ifdef DEBUG_NTP
    #include <debugntp.h>
#endif
#ifdef DEBUGNTP
    #include <pinDebugNtp.h>
#endif

#include "svt.h"
//#include "lib_DB\database.h"
#include "RTC_WDT.h"
#include "ntp.h"
#include "display.h"


/*size buffer*/
#define DATA_BUFFER   50
 
#define ADRESS_READY        8
#define ADRESS_REBOOT       9
#define ADRESS_COUNT_SK     10

#define NETWORK_TIMEOUT     50

/*for NTP protocol*/
#define NTP_TRY_SYNC        14
#define NTP_CONNECT_ATTEMPS 6       //кількість спроб надсилання пакету
#define NTP_SUCCESSFUL_PACKET 5       //кількість пакетів для синхронізації 
#define NTP_DELAY_RECEIVED_PACKET 500

/*define for result ntp sync*/
#define OK      1
#define ERROR   0
    
/*segment time for NTP*/
#define T1                  0
#define T2                  1
#define T3                  2
#define T4                  3

typedef struct
{
    /*data to transmit*/
    uint8_t IDpacket;    
    uint8_t ready;          /*flag readu finish*/
    uint8_t reboot;         /*flag finish reboot*/
    uint8_t countSkiers;
    
    uint64_t tmpTime;
    uint16_t tmpMsTime;
    uint8_t writeStatus;    /*flag transmitt data*/
}FinishData;

typedef struct
{
    /*data to receive*/
    uint8_t IDpacket;
    uint64_t unixStartTime;
    uint16_t startMsTime;
    uint8_t newSkier;
    uint8_t reboot;     /*reboot=1, no reboot=0*/
    
    uint8_t readStatus;     /*flag successful read data in start*/
}StartData;

FinishData outData ;
StartData inData;

uint32_t numAttemps,noConnect, networkStatus;
uint32_t unixTime[4];
uint16_t millisTime[4];

/*new ntp*/
uint8_t ntpFlagEndReceivePacket;        //indicator end receive packet
uint8_t ntpFlagReadyForReceive;         //indicator ready for receive next packet
NtpResp recvDataNTP;

char mas[100];
uint16_t poinMas = 0;
/*end*/

#ifdef DEBUG_INFO
char uartBuff[100];
#endif

uint32_t SendRealTimeToStart(void);
void NTPsendTime(uint32_t unixTime1,uint16_t millis1, uint16_t ID);
uint32_t NTPreceiveTime(uint32_t *unixTime2,uint16_t *millis2, uint32_t *unixTime3, uint16_t *millis3, uint16_t *IDreceive);
uint32_t NTPsetTimeToStart(uint32_t unixTime4,uint16_t millis4,  uint16_t ID);
void NTPcalculateTime(uint32_t unixTime[], uint16_t msTime[], int32_t *sumTime, int32_t *sumMs);
void CustomInterruptHandler(void);
void FuncTake(uint32_t sec1, uint16_t ms1, uint32_t sec2, uint16_t ms2, int32_t *resultSec, int16_t *resultMs);



/*******************************************************************************
* Function Name: InitNetwork
********************************************************************************
*
* Summary:
*   initialization UART for XBee module
*
*******************************************************************************/
void InitNetwork(void)
{
    UART_XB_Start();
    UART_XB_SetCustomInterruptHandler(&CustomInterruptHandler);
    
    #ifdef DEBUG_INFO
    SW_uartDebug_Start();     
    SW_uartDebug_PutString("HElLO, IM READY(fin)\n\r");
    #endif
    
    inData.readStatus = READ_OK;
    outData.writeStatus = NO_WRITE;
    UART_XB_SpiUartClearRxBuffer();
    
}


void CustomInterruptHandler(void)
{
    uint8_t byte = 0;
    
    if(UART_XB_SpiUartGetRxBufferSize() > 0)
        byte=UART_XB_UartGetChar();
    
    if(ntpFlagReadyForReceive && byte != 0)
    {
        NtpUnpackData(&recvDataNTP, (uint8_t)(byte & 0xFF));
        
        if(recvDataNTP.EndPacket)
        {
            unixTime[T4] = RTC_GetUnixTime();
            millisTime[T4] = RTCgetRecentMs();
            unixTime[T2] = recvDataNTP.Data1;
            millisTime[T2] = recvDataNTP.DataMs1;
            unixTime[T3] = recvDataNTP.Data2;
            millisTime[T3] = recvDataNTP.DataMs2;
            
            #ifdef DEBUGNTP
                pinDebugNtp_Write(1);
                pinDebugNtp_Write(0);
            #endif
            
            ntpFlagEndReceivePacket = 1;
            ntpFlagReadyForReceive = 0;
        }
    }
    
}
/*******************************************************************************
* Function Name: SendData
********************************************************************************
*
* Summary:
*   send data to start from struct "outData"
*
*******************************************************************************/
//void SendData(void)
//{   
//    if( outData.writeStatus == NO_WRITE || inData.readStatus == READ_OK)
//    {
//        char sendBuffer[DATA_BUFFER];
//        char sendData[DATA_BUFFER];
//        
//        outData.countSkiers = SkierOnWay();
//        
//        /*pack data*/
//        sprintf(sendData,"%02X:%016X%02X%02X%02X%02X", 0u, 0u, outData.ready, outData.reboot, \
//            outData.countSkiers, 0u);    
//        PackData(sendBuffer, (uint8_t *)sendData, outData.IDpacket);
//        UART_XB_UartPutString(sendBuffer);
//        
//        
//        /*flag transmit data*/
//        outData.writeStatus = WRITE_OK;
//        inData.readStatus = NO_READ;
//        
//        /*set timeout*/
//        noConnect = 0; 
//        
//        CyDelay(50);
//    }
//}

/*******************************************************************************
* Function Name: ReceiveData
********************************************************************************
*
* Summary:
*   receive data from start in struct "inData"
* Return:
*   NETWORK_CONNECT or NETWORK_DISCONNECT
*
*******************************************************************************/
//uint32_t  ReceiveData(void)
//{   
//    if(inData.readStatus == NO_READ && outData.writeStatus == WRITE_OK)
//    {
//        uint32_t result = 0;
//        int i;
//        uint8_t byte;
//        struct Resp recvData;
//          
//        while((UART_XB_SpiUartGetRxBufferSize() > 0) && ((byte=UART_XB_UartGetChar()) != 0))
//        { 
//            result = UnpackData(&recvData, (uint8_t)(byte & 0xFF));
//            CyDelay(2);
//            
//            
//            if(recvData.EndPacket == 1)
//            {
//                inData.IDpacket = recvData.Seq;
//                
//                /*id packet ok*/
//                if(outData.IDpacket == inData.IDpacket)
//                {
//                    inData.readStatus = READ_OK;
//                    outData.writeStatus = NO_WRITE;
//                    
//                    /*connect network*/
//                    networkStatus = NETWORK_CONNECT;
//                    noConnect = 0;
//                    
//                    /*write data*/
//                    inData.newSkier = (recvData.Data3 & 0xFF00) >> 8;
//                    inData.unixStartTime = recvData.Data1;
//                    inData.startMsTime = recvData.Data2;
//                    inData.reboot = (recvData.Data3 & 0x00FF);
//                    
//                    /*if new skier on track*/
//                    if(inData.newSkier == NEW_SKIER_IN_TARCK )
//                    {
//                        WriteStartTime(inData.unixStartTime, inData.startMsTime);
//                        BLE_sendOneSkierTimeStart(inData.unixStartTime, inData.startMsTime,GetIDskierStarted(),SkierOnWay(),MAX_SKIERS_ON_WAY);
//                        IncrementID();
//                    }
//                    
//                    /*next packet*/
//                    outData.IDpacket++;
//                    CyDelay(50);
//                }  
//                /* if prev packet late*/
//                else if(outData.IDpacket == (inData.IDpacket + 1))
//                {
//                    inData.newSkier = recvData.Data3;
//                    inData.unixStartTime = recvData.Data1;
//                    inData.startMsTime = recvData.Data2;
//                    
//                    networkStatus = NETWORK_CONNECT;
//                    noConnect = 0;
//                    CyDelay(50);
//                }
//                return  NETWORK_CONNECT;  
//            }
//        }
//        
//        noConnect++;
//        if(noConnect >= NETWORK_TIMEOUT)
//        {
//            outData.writeStatus = NO_WRITE;
//            inData.readStatus = NO_READ;
//            networkStatus = NETWORK_DISCONNECT;
//        }
//        
//        return  NETWORK_DISCONNECT;
//    }
//    return 0;
//}


/*******************************************************************************
* Function Name: SendFinStatus
********************************************************************************
*
* Summary:
*   set fin status
* Parametrs:
*   FIN_READY or FIN_NO_READY
*
*******************************************************************************/
void SendFinStatus(uint32_t ready)
{
    outData.ready = ready;
}

/*******************************************************************************
* Function Name: NetworkStatus
********************************************************************************
*
* Summary:
*   read network status
* Return:
*   NETWORK_CONNECT or NETWORK_DISCONNECT
*
*******************************************************************************/
uint32_t NetworkStatus(void)
{
    return networkStatus;
}

/*******************************************************************************
* Function Name: ReadRebootStartFlag
********************************************************************************
*
* Summary:
*   read reboot flag from start
* Return:
*   REBOOT or NO_REBOOT
*
*******************************************************************************/
uint32_t IsRebootStartFlag(void)
{
    uint32_t result;
    
    if(inData.reboot == 1 && outData.reboot == 0)
    {
        result = REBOOT;
        inData.reboot = 0;
    }
    else 
    {
        outData.reboot = 0;
        inData.reboot = 0;
        result = NO_REBOOT;
    }
    return result;
}

void ClearRebootFlag(void)
{
    outData.reboot = 0;
    inData.reboot = 0;
}
/*******************************************************************************
* Function Name: WriteRebootFlag
********************************************************************************
*
* Summary:
*   write reboot flag to start
*
*******************************************************************************/
void SetRebootFlag(void)
{
    outData.reboot = 0;
    inData.reboot = 1;
}


/*******************************************************************************
* Function Name: NTPsync
********************************************************************************
*
* Summary:
*   NTP time synchronization protocol on
* Return:
*   TIME_SYNC_OK or TIME_SYNC_ERR
*
*******************************************************************************/
uint32_t NTPsync(void)
{
    uint16_t result;
    uint32_t resultReceive; 
    int i;
    uint16_t IDpacket;
    uint16_t IDreceivePacket;
    int32_t sumTime;
    int32_t sumMillis;   
    uint32_t numAttempsReseive;
    uint32_t numTruReceive;
    
    
//    IDpacket = 1;
//    IDreceivePacket = 0;
//    numAttempsReseive = 0;
//    result = TIME_SYNC_ERR;
    
    /*new ntp*/
    
    while(1)
    {
        /*send real unix time*/
        uint16_t delayReceivePacket ;
        uint16_t numAttemptSendPacket = NTP_CONNECT_ATTEMPS;
        result = ERROR;
        ntpFlagReadyForReceive = 1;
        while(numAttemptSendPacket && result != OK)
        {
            IDpacket = 1;
            unixTime[T1] = RTCGetUnixTime();
            millisTime[T1] = RTCgetRecentMs();
            #ifdef DEBUGNTP
                pinDebugNtp_Write(1);
                pinDebugNtp_Write(0);
                pinDebugNtp_Write(1);
                pinDebugNtp_Write(0);
            #endif 
            NTPsendTime(unixTime[T1], millisTime[T1], IDpacket);
            
            delayReceivePacket = NTP_DELAY_RECEIVED_PACKET;
            uint32_t oldUnixTime = unixTime[T1];
            delayReceivePacket += millisTime[T1];
            #ifdef DEBUG_INFO
//                SW_uartDebug_PutString("send new packet\n\r");
            #endif
            
            while((RTCgetRecentMs() < delayReceivePacket) && (result != OK))
            {
                if(ntpFlagEndReceivePacket)
                {
                    ntpFlagEndReceivePacket = 0;
                    
                    if(recvDataNTP.Id == IDpacket)
                    {
                        result = OK;
                    }
                    
                    #ifdef DEBUG_INFO
//                        sprintf(uartBuff,"idreceive=%d\n\r",recvDataNTP.Id);
//                        SW_uartDebug_PutString(uartBuff);
                    #endif
                    
                    ntpFlagReadyForReceive = 1;
                }
                if((oldUnixTime<RTCGetUnixTime()) && (delayReceivePacket >= 1000))
                {
                    delayReceivePacket -= 1000;
                    oldUnixTime++;
                    
                    #ifdef DEBUG_INFO
//                        sprintf(uartBuff,"delayReceive=%d, realTimeMs=%d\n\r",delayReceivePacket,(uint32_t)RTCgetRecentMs());
//                        SW_uartDebug_PutString(uartBuff);
//                        sprintf(uartBuff,"unix[T1]=%d, realTimeunix=%d\n\r",unixTime[T1],(uint32_t)RTCGetUnixTime());
//                        SW_uartDebug_PutString(uartBuff);
                    #endif
                }
            }
            numAttemptSendPacket--;
        }
        
        /*calculate difference time*/
        result = ERROR;
        numAttemptSendPacket = NTP_CONNECT_ATTEMPS;
        IDpacket = 2;
        uint8_t numSuccessuflPacket = NTP_SUCCESSFUL_PACKET;
        int32_t unixTimeDifference = 0;
        int32_t msTimeDifference = 0;
        while(numAttemptSendPacket && numSuccessuflPacket)
        {
            unixTime[T1] = RTCGetUnixTime();
            millisTime[T1] = RTCgetRecentMs();
            #ifdef DEBUGNTP
                pinDebugNtp_Write(1);
                pinDebugNtp_Write(0);
                pinDebugNtp_Write(1);
                pinDebugNtp_Write(0);
            #endif 
            NTPsendTime(unixTime[T1], millisTime[T1], IDpacket);
            
            delayReceivePacket = 1000;
            delayReceivePacket += millisTime[T1];
            uint32_t oldUnixTime = unixTime[T1];
            #ifdef DEBUG_INFO
//                SW_uartDebug_PutString("send new packet\n\r");
//                sprintf(uartBuff,"numSuccesful=%d\n\n\r",numSuccessuflPacket);
//                SW_uartDebug_PutString(uartBuff);
            #endif
            while((RTCgetRecentMs() < delayReceivePacket) && (result != OK) )
            {
                if(ntpFlagEndReceivePacket)
                {
                    ntpFlagEndReceivePacket = 0;
                    
                    if(recvDataNTP.Id == IDpacket)
                    {
                        numSuccessuflPacket--;  
                        numAttemptSendPacket = NTP_CONNECT_ATTEMPS;
                        result = OK;
                        
                        /*calculate difference time*/
                        int32_t tmpUnix, tmpMs;
                        NTPcalculateTime(unixTime,millisTime,&tmpUnix,&tmpMs);
//                        unixTimeDifference += tmpUnix;
//                        msTimeDifference += tmpMs;
                        
                        #ifdef DEBUG_INFO
                        sprintf(uartBuff,"diff unix=%d, diff ms-%d\n\r",tmpUnix, tmpMs);
                        SW_uartDebug_PutString(uartBuff);
                        int32_t tmpU;
                        int16_t tmpms;

                        FuncTake(unixTime[T3],millisTime[T3],unixTime[T2],millisTime[T2],&tmpU,&tmpms);
                        sprintf(uartBuff,"T3-T2=%d.%d\n\r",tmpU, tmpms);
                        SW_uartDebug_PutString(uartBuff);
                        
                        FuncTake(unixTime[T4],millisTime[T4],unixTime[T1],millisTime[T1],&tmpU,&tmpms);
                        sprintf(uartBuff,"T4-T1=%d.%d\n\r",tmpU, tmpms);
                        SW_uartDebug_PutString(uartBuff);
                        
                        FuncTake(unixTime[T2],millisTime[T2],unixTime[T1],millisTime[T1],&tmpU,&tmpms);
                        sprintf(uartBuff,"T2-T1=%d.%d\n\r",tmpU, tmpms);
                        SW_uartDebug_PutString(uartBuff);
                        #endif
                    }
                    
                    #ifdef DEBUG_INFO
//                        sprintf(uartBuff,"succesful=%d\n\r",numSuccessuflPacket);
//                        SW_uartDebug_PutString(uartBuff);
                    #endif
                    
                    ntpFlagReadyForReceive = 1;
                }
                if((oldUnixTime<RTCGetUnixTime()) && (delayReceivePacket >= 1000))
                {
                    delayReceivePacket -= 1000;
                    oldUnixTime++;
                }
            }
            result = ERROR;
            numAttemptSendPacket--;
            IDpacket++;
        }
        if(numSuccessuflPacket == 0)result = OK;
        
        
        
        #ifdef DEBUG_INFO
            if(result == OK)
            SW_uartDebug_PutString("okey\n\r");
            else
            SW_uartDebug_PutString("error\n\r");
        #endif
        
        while(1)
        {
            uint32_t recMs;
            recMs = RTCgetRecentMs();
            
            pinDebugNtp_Write(1);
            pinDebugNtp_Write(0);
            
            sprintf(uartBuff,"%d\n\r",recMs);
            UART_XB_UartPutString(uartBuff);
            
            CyDelay(300);
        }
    }
   
    /*sync milisecond and second*/
//    for(i=1; i < NUM_TRY_SYNC; )
//    {
//        /*send time T1*/
//        unixTime[T1] = RTCGetUnixTime();
//        millisTime[T1] = RTCgetRecentMs();
//        
//        NTPsendTime(unixTime[T1], millisTime[T1], IDpacket);
//        
//        /*reseive data*/
//        resultReceive = NO_READ;
//        numAttempsReseive = 0;
//        while((resultReceive == NO_READ) && (numAttempsReseive < NUM_CONNECT_ATTEMPS*4))
//        {
//            /*receive time from start*/
//            resultReceive = NTPreceiveTime(&unixTime[T2],&millisTime[T2], &unixTime[T3], &millisTime[T3], &IDreceivePacket);
//                    
//            if((resultReceive == READ_OK) && (IDreceivePacket == IDpacket))
//            {
//                /*delivery timing*/
//                unixTime[T4] = RTCGetUnixTime();
//                millisTime[T4] = RTCgetRecentMs();
//                
//                
//                /*Packaging data lasts 2 ms, so add it to the read time
//                send data lasts 43ms*/
//                millisTime[T4] -= 44;
//                if(millisTime[T4] < 0)
//                {
//                    unixTime[T4]--;
//                    millisTime[T4] += 1000;
//                }
//                
//                NTPcalculateTime(unixTime, millisTime,&sumTime, &sumMillis);
//                CyDelay(1000); 
// 
//                
//                /* send delivery time */
//                IDpacket = 0;
//                result = NTPsetTimeToStart(sumTime, sumMillis, IDpacket);
//                
//                if(result == WRITE_OK)
//                {
//                    /*display loading sync time*/
//                    for(i=0;i<13;i++)
//                    {
//                        DisplayLoading(i);
//                        CyDelay(100);
//                    }
//                    result = TIME_SYNC_OK;
//                }
//                else
//                {
//                    result = TIME_SYNC_ERR;
//                }
//                                            
//                i = NUM_TRY_SYNC; 
//                resultReceive = READ_OK;
//            }
//            else
//            {
//                numAttempsReseive++;
//                resultReceive = NO_READ;
//                CyDelay(10);
//            }
//        }
//        
//        CyDelay(100);
//        
//        IDpacket++;
//        i++;  
//    }

    return result;
}


/*******************************************************************************
* Function Name: NTPsendTime
********************************************************************************
*
* Summary:
*   send time to NTP protocol
* Parametrs:
*   unixTime - time in unix format
*   millis - millis time
*   ID - ID packet
*
*******************************************************************************/
void NTPsendTime(uint32_t unixTime,uint16_t millis, uint16_t ID)
{
    char sendBuffer[DATA_BUFFER];
    char sendData[DATA_BUFFER];
    
    /*Packaging data lasts 1 ms, so add it to the read time
    send data lasts 31ms*/
//    millis += (1+31);
//    if(millis >= 1000)
//    {
//        millis -= 1000;
//        unixTime++;
//    }
    
    /*pack data*/
    sprintf(sendData,"%08X%03X", unixTime,millis); 
    PackData(sendBuffer, (uint8_t *)sendData, ID);
    UART_XB_UartPutString(sendBuffer);
    UART_XB_UartPutChar('0');
    
}

/*******************************************************************************
* Function Name: NTPreceiveTime
********************************************************************************
*
* Summary:
*   receive time to NTP protocol
* Parametrs:
*   *unixTime2,unixTime3 - time in unix format
*   *millisTime2,millisTime3 - millis time
*   *IDreceive - ID packet
* Return:
*   READ_OK or NO_READ
*
*******************************************************************************/
uint32_t NTPreceiveTime(uint32_t *unixTime2, uint16_t *millisTime2, uint32_t *unixTime3, uint16_t *millisTime3, uint16_t *IDreceive)
{
    uint8_t byte;
    uint32_t result;
    
    result = READ_OK;   
    NtpResp recvDataNTP;
    while((UART_XB_SpiUartGetRxBufferSize() > 0) && ((byte = UART_XB_UartGetChar()) != 0))
    {
        result = NtpUnpackData(&recvDataNTP, (uint8_t)(byte & 0xFF));
        CyDelay(1);
            
        if(recvDataNTP.EndPacket == 1)
        {
            /*save unix time*/
            *IDreceive = recvDataNTP.Id;
            *unixTime2 = recvDataNTP.Data1;
            *millisTime2 = recvDataNTP.DataMs1;
            *unixTime3 = recvDataNTP.Data2;
            *millisTime3 = recvDataNTP.DataMs2;
        
            return READ_OK;
        }
        result = NO_READ;
    }
    result = NO_READ;
    
    return result;
}

/*******************************************************************************
* Function Name: NTPsetTimeToStart
********************************************************************************
*
* Summary:
*   sending start time based on the time of delivery
* Parametrs:
*   unixTime4 - time in unix format
*   millisTime4 - millis time
*   ID - ID packet
*
*******************************************************************************/
uint32_t NTPsetTimeToStart(uint32_t unixTime4, uint16_t millisTime4, uint16_t ID)
{
    
    uint32_t resultReceive;
    uint16_t IDreceivePacket;
    uint32_t result;
    
    noConnect = 0;
    result = NO_WRITE;
    
    while((result == NO_WRITE) && (noConnect < 10))
    {      
        NTPsendTime(unixTime4, millisTime4,ID); 
        
        CyDelay(500);
        resultReceive = NTPreceiveTime(&unixTime[T2], &millisTime[T2], &unixTime[T3], &millisTime[T3], &IDreceivePacket);
        if((resultReceive == READ_OK) && (IDreceivePacket == ID))
        {
            result = WRITE_OK;
        }
        else
        {
            result = NO_WRITE;
            noConnect++;
            CyDelay(500);            
        }
    }
    
    return result;
}

void NTPcalculateTime(uint32_t unixTime[], uint16_t msTime[], int32_t *sumTime, int32_t *sumMs)
{
    /*calculate ms time*/
    int16_t tmpMs21;
    int32_t tmpTime21;    
    int16_t tmpMs34;
    int32_t tmpTime34;
    int32_t tmpDiffTime;
    int16_t tmpDiffMs;
    
//    millisTime[T1] += 32;
//    millisTime[T2] -= 32;
//    millisTime[T3] += 45;
//    millisTime[T4] -= 45;
//    if(millisTime[T1]>=1000)
//    {
//        millisTime[T1] -= 1000;
//        unixTime[T1] ++;
//    }
//    if(millisTime[T2]< 0)
//    {
//        millisTime[T2] += 1000;
//        unixTime[T2] --;
//    }
//    if(millisTime[T3]>=1000)
//    {
//        millisTime[T3] -= 1000;
//        unixTime[T3] ++;
//    }
//    if(millisTime[T4]>=1000)
//    {
//        millisTime[T4] += 1000;
//        unixTime[T4] --;
//    }
    #ifdef DEBUG_INFO
    sprintf(uartBuff,"T1=%d, T2=%d, T3=%d, T4=%d\n\r",unixTime[T1], unixTime[T2],unixTime[T3],unixTime[T4]);
    SW_uartDebug_PutString(uartBuff);
    sprintf(uartBuff,"T1ms=%d, T2ms=%d, T3ms=%d, T4ms=%d\n\r",millisTime[T1],millisTime[T2],millisTime[T3],millisTime[T4]);
    SW_uartDebug_PutString(uartBuff);
    #endif    
    
    FuncTake(unixTime[T2],msTime[T2],unixTime[T1],msTime[T1],&tmpTime21,&tmpMs21);
    FuncTake(unixTime[T3],msTime[T3],unixTime[T4],msTime[T4],&tmpTime34,&tmpMs34);

    
    tmpDiffTime = tmpTime21 + tmpTime34;
    tmpDiffMs = tmpMs21 + tmpMs34;
    if(tmpDiffMs >= 1000)
    {
        tmpDiffTime += 1;
        tmpDiffMs -= 1000;
    }
    else if(tmpDiffMs <= -1000)
    {
        tmpDiffTime -= 1;
        tmpDiffMs += 1000;
    }
    
    tmpDiffMs /= 2;
    if(tmpDiffTime%2 == 1)
    {
        tmpDiffMs += 500;
    }
    tmpDiffTime /= 2;
    
    *sumTime = tmpDiffTime;
    *sumMs = tmpDiffMs; 

}

void FuncTake(uint32_t sec1, uint16_t ms1, uint32_t sec2, uint16_t ms2, int32_t *resultSec, int16_t *resultMs)
{
	*resultSec = sec1 - sec2;
	*resultMs = ms1 - ms2;
	if (*resultSec < 0)
	{	
		if (*resultMs > 0)
		{
			*resultMs -= 1000;
			*resultSec += 1;
		}
	}
	else if(*resultSec > 0)
	{
		if (*resultMs < 0)
		{
			*resultMs += 1000;
			*resultSec -= 1;
		}
	}
}
/* [] END OF FILE */
