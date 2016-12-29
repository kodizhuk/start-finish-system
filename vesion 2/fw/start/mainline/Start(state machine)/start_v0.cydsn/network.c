
#include "lib_Network/network.h"
#include <UART_XB.h>
#include <UART_XB_SPI_UART.h>
#include <RTC.h>

#ifdef DEBUG_INFO
    #include "SW_UART_DEBUG.h"
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
#ifdef DEBUGUART
    #include <project.h>
#endif

#include <stdio.h>
#include "lib_Network/svt.h"
#include "lib_RTC/RTC_WDT.h"
#include "lib_Network/ntp.h"
#include "lib_Display/display.h"

#define MIN_DELAYMS 150

/*size buffer*/
#define DATA_BUFFER   50
#define RX_BUFFER   

#define ADRESS_READY        8
#define ADRESS_REBOOT       9
#define ADRESS_COUNT_SK     10

#define MASK_HIGH   0xFFFFFFFF00000000
#define MASK_LOW    0x00000000FFFFFFFF
#define DATA_SHIFT  32

#define TIMEOUT_FIN_READY   3

/*for NTP protocol*/
#define NUM_TRY_SYNC        14
#define NUM_CONNECT_ATTEMPS 1000

#define SAVE_TIME           1
#define NETWORK_TIMEOUT     50
#define NEW_SKIER_IN_TARCK   1
#define NTP_DELAY_RECEIVED_PACKET 500


/*segment time*/
#define T1                  0
#define T2                  1
#define T3                  2
#define T4                  3

#define CORRECTION_TIME     0

typedef struct
{
    uint8_t IDpacket;
    uint8_t ready;
    uint8_t reboot;
    uint8_t countSkiers;
    uint64_t tmpTime;
    uint16_t tmpMsTime;
    uint8_t readStatus;
}FinishData;

typedef struct
{
    uint8_t IDpacket;
    uint64_t unixStartTime;
    uint16_t startMsTime;
    uint8_t newSkier;
    uint8_t writeStatus;
    uint8_t reboot;     /*reboot=1, not reboot=0*/
}StartData;

FinishData inData;
StartData outData;

char previousData[100];

static uint32_t networkStatus;
static int noConnect;
static int finNoReady;
uint32_t unixTime[4];
uint16_t millisTime[4];

/*------TEST---------*/
uint8_t onNtpSync = 0;      //зміння для індикації що зара відбуваєтсья синхронізація часу. а не передача повідомлень
uint8_t flagStartSendPacket = 0;    //флажки показують що почалася/закінчилася передача повідомлення
uint8_t flagFinSendPacket = 0;      //

uint32_t resultReceive;
uint16_t IDreceivePacket;
typedef enum {ROUGH_SET_TIME, SYNC_TIME, SET_DIFF_TIME}stageSync;

/*global variable for new ntp protocol*/
uint8_t ntpFlagEndReceivePacket;        //indicator end receive packet
uint8_t ntpFlagReadyForReceive;         //indicator ready for receive next packet
NTPResp recvDataNTP;                    //struct for data to ntpd receive data
/*end */

#ifdef DEBUG_INFO
    char uartBuff[50];
#endif

#ifdef DEBUGUART
    char buffer[100];
#endif

uint32_t ReceiveRealTime(void);
void NTPsendTime(uint32_t unixTime2,uint32_t unixTime3,uint16_t millis2,uint16_t millis3, uint16_t ID);
uint32_t NTPreceiveTime(uint32_t *unixTime2,uint16_t *millis2, uint16_t *IDreceive, uint32_t saveTime);
void CustomInterruptHandler(void);

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
        SW_UART_DEBUG_Start();
        SW_UART_DEBUG_PutString("HElLO, IM READY(start)\n\r");
    #endif
    
    #ifdef DEBUGUART
        uartDebug_Start();
        uartDebug_UartPutString("uart started\n\r");
    #endif
    
    inData.readStatus = NO_READ;
    outData.writeStatus = WRITE_OK;
    outData.IDpacket = 0xFF;
    networkStatus = NETWORK_DISCONN;   
    UART_XB_SpiUartClearRxBuffer();
}




void CustomInterruptHandler(void)
{
    if(onNtpSync)
    {
        uint8_t byte = 0;
        
        if(UART_XB_SpiUartGetRxBufferSize() > 0)
            byte=UART_XB_UartGetChar();
            
        if(ntpFlagReadyForReceive && byte != 0)
        {
            NtpUnpackData(&recvDataNTP, (uint8_t)(byte & 0xFF));
            
            if(recvDataNTP.EndPacket)
            {
                unixTime[T2] = RTC_GetUnixTime();
                millisTime[T2] = RTCgetRecentMs();
                unixTime[T1] = recvDataNTP.Data1;
                millisTime[T1] = recvDataNTP.DataMs1;
                #ifdef DEBUGNTP
                    pinDebugNtp_Write(1);
                    pinDebugNtp_Write(0);
                #endif
                
                ntpFlagEndReceivePacket = 1;
                ntpFlagReadyForReceive = 0;
            }
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
void SendData(void)
{
    if(outData.writeStatus == NO_WRITE && inData.readStatus == READ_OK)
    { 
        if (inData.IDpacket == outData.IDpacket)
        {
            /*send previous packet*/
            
            UART_XB_UartPutString(previousData);
            outData.writeStatus = WRITE_OK;
            inData.readStatus = NO_READ;
        }
        else
        {
            /*send nex packet*/
            
            char sendBuffer[DATA_BUFFER];
            char sendData[DATA_BUFFER];
            
            /*pack data*/
            sprintf(sendData,"%02X:%08X%08X%04X%02X%02X",
                    0u,
                    (uint32_t)((outData.unixStartTime & MASK_HIGH) >> DATA_SHIFT), 
                    (uint32_t)(outData.unixStartTime & MASK_LOW), 
                    outData.startMsTime, 
                    outData.newSkier, 
                    outData.reboot);
            
            
            PackData(sendBuffer, (uint8_t *)sendData, inData.IDpacket);
            UART_XB_UartPutString(sendBuffer);            

            outData.newSkier = !NEW_SKIER_IN_TARCK;
                
            outData.writeStatus = WRITE_OK;
            outData.IDpacket = inData.IDpacket;
            inData.readStatus = NO_READ;
            strcpy(previousData, sendBuffer);
            
            CyDelay(50);
        }
    }
}


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
    uint32_t ReceiveData(void)
    {
    if(outData.writeStatus == WRITE_OK && inData.readStatus == NO_READ)
    {
        uint32_t byte;
        struct Resp recvData;
          
        while((UART_XB_SpiUartGetRxBufferSize() > 0) && ((byte=UART_XB_UartGetChar()) != 0))
        { 
            UnpackData(&recvData, (uint8_t)(byte & 0xFF));
            
            CyDelay(2);
            
            if(recvData.EndPacket == 1)
            {                      
                inData.IDpacket = recvData.Seq;
                
                inData.readStatus = READ_OK;
                outData.writeStatus = NO_WRITE;
                
                /*connect network*/
                networkStatus = NETWORK_CONN;
                noConnect = 0;
                /*write data*/
                inData.countSkiers = (recvData.Data3 & 0x00FF) << 8;
                //inData.unixStartTime = recvData.Data1;
                inData.ready = (recvData.Data2 & 0xFF00) >> 8;
                inData.reboot = recvData.Data2 & 0x00FF;
                
                CyDelay(50);

                return  NETWORK_CONN;  
            }
        }
        
        /*tyme to respond*/
        if(noConnect++ >= NETWORK_TIMEOUT)
        {
            networkStatus = NETWORK_DISCONN;
        }
        return  NETWORK_DISCONN;
    }
    return 0;
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



void SendSkierStart(uint64_t unixTimeStart, uint32_t recentMs)
{
    outData.unixStartTime = unixTimeStart;
    outData.startMsTime = recentMs;
    outData.newSkier = NEW_SKIER_IN_TARCK;
}


uint32_t FinReady(void)
{
    return inData.ready;
}


uint32_t FinWriteInDB(void)
{
    uint32_t result;
    
    if(outData.newSkier == NEW_SKIER_IN_TARCK)
    {
        result = NO_WRITE;
    }
    else
    {
        result = WRITE_OK;
    }
    
    return result;
}

uint32_t IsRebootFinishFlag(void)
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

void SetRebootFlag(void)
{
    outData.reboot = 1;
}

void ClearRebootFlag(void)
{
    inData.reboot = 0;
    outData.reboot = 0;
}


/*******************************************************************************
* Function Name: NTPsync
********************************************************************************
*
* Summary:
*   NTP time synchronization protocol on
    1) відбуваєтсья вимірювання часу прийняття  та передачі пакету.
    2) визначення часу передачі пакету за допомогою __ пакетів
    3) встановлення часу з врахуванням часу передачі
* Return:
*   TIME_SYNC_OK or TIME_SYNC_ERR
*
*******************************************************************************/
uint32_t NTPsync(void)
{
    uint16_t result;    
    
    result = TIME_SYNC_ERR; 
    ntpFlagEndReceivePacket = 0;
    ntpFlagReadyForReceive = 1;
    uint16_t delayReceivePacket;
    uint32_t oldUnixTime;
    
    delayReceivePacket = 4*NTP_DELAY_RECEIVED_PACKET;
    oldUnixTime = RTCGetUnixTime();
    delayReceivePacket += RTCgetRecentMs();
    onNtpSync = 1;
    
    UART_XB_SpiUartClearRxBuffer();
    
    while((RTCgetRecentMs() < delayReceivePacket) )//&& (result != TIME_SYNC_OK))
    {
        if(ntpFlagEndReceivePacket)
        {
            #ifdef DEBUGNTP
                pinDebugNtp_Write(1);
                pinDebugNtp_Write(0);
            #endif
            
            if(recvDataNTP.Id == 1 )//&& (currentStage == ROUGH_SET_TIME)) /*set real unix time*/
            {
                ntpFlagEndReceivePacket = 0;
                
                RTCSync(unixTime[T1], millisTime[T1]);
                oldUnixTime = unixTime[T1];
                delayReceivePacket = NTP_DELAY_RECEIVED_PACKET+millisTime[T1];
                
                /*send response*/
                NTPsendTime(0,0,0,0,recvDataNTP.Id);
                
                
                #ifdef DEBUG_INFO
//                sprintf(uartBuff, "set unix=%d,ms=%d   ",unixTime[T1], millisTime[T1]);
//                SW_uartDebug_PutString(uartBuff);
//                SW_uartDebug_PutString("receive id=1\n\r");
                #endif
                ntpFlagReadyForReceive = 1;
            }
            else if(recvDataNTP.Id == 0) /*set difference time*/
            {
                ntpFlagEndReceivePacket = 0;
                
                uint32_t unixTimeReal;
                uint16_t millisTimeReal;
                
                if(result == TIME_SYNC_ERR)
                {
                    unixTimeReal = RTC_GetUnixTime();
                    millisTimeReal = RTCgetRecentMs();
                    
                    /*add difference time*/
                    unixTimeReal += unixTime[T1];
                    millisTimeReal += millisTime[T1];
                    if(millisTimeReal  >= 1000)
                    {
                        unixTimeReal++;
                        millisTimeReal -= 1000;
                    }
                    RTCSync(unixTimeReal, millisTimeReal);
                }
                oldUnixTime = RTCGetUnixTime();;
                delayReceivePacket = NTP_DELAY_RECEIVED_PACKET+RTCgetRecentMs();;
                /*send response*/
                NTPsendTime(0,0,0,0,recvDataNTP.Id);
                result = TIME_SYNC_OK;
                                
                #ifdef DEBUG_INFO    
//                SW_uartDebug_PutString("receive id=0\n\r");
                #endif
                
                ntpFlagReadyForReceive = 1;
            }
            else    /*packet for determite the difference time */
            {
                ntpFlagEndReceivePacket = 0;
                
                CyDelay(100);
                
                /*read real time*/
                millisTime[T3] = RTCgetRecentMs();
                unixTime[T3] = RTC_GetUnixTime();

                #ifdef DEBUGNTP
                    pinDebugNtp_Write(1);
                    pinDebugNtp_Write(0);
                    pinDebugNtp_Write(1);
                    pinDebugNtp_Write(0);
                #endif
                
                if((unixTime[T2] == unixTime[T3]) || ((unixTime[T2] == (unixTime[T3])-1)))
                {
                    NTPsendTime(unixTime[T2], unixTime[T3], millisTime[T2], millisTime[T3], recvDataNTP.Id);
                }
                
                #ifdef DEBUG_INFO
//                sprintf(uartBuff,"uT2=%d,uT3=%d, mT2=%d,mT3=%d   ",unixTime[T2], unixTime[T3], millisTime[T2], millisTime[T3]);
//                SW_uartDebug_PutString(uartBuff);
//                sprintf(uartBuff,"receive id>1 id=%d\n\r",recvDataNTP.Id);
//                SW_uartDebug_PutString(uartBuff);
                #endif
                
                ntpFlagReadyForReceive = 1;
            }
            delayReceivePacket = NTP_DELAY_RECEIVED_PACKET;
            oldUnixTime = RTCGetUnixTime();
            delayReceivePacket += RTCgetRecentMs();
        }
        
        if((oldUnixTime < RTCGetUnixTime()) && (delayReceivePacket >= 1000))
        {
            delayReceivePacket -= 1000;
            oldUnixTime++;
        }
    }

    onNtpSync = 0;
    
    return result;
}



/*******************************************************************************
* Function Name: NTPsendTime
********************************************************************************
*
* Summary:
*   send time t2 and t3 to NTP protocol
* Parametrs:
*   unixTime2,unixTime3 - time in unix format
*   millis2, millis3 - millis time
*   ID - ID packet
*
*******************************************************************************/
void NTPsendTime(uint32_t unixTime2,uint32_t unixTime3,uint16_t millis2,uint16_t millis3, uint16_t ID)
{
    char sendBuffer[DATA_BUFFER];
    char sendData[DATA_BUFFER];
    
    /*pack data*/
    sprintf(sendData,"%08X%03X%08X%03X", unixTime2, millis2, unixTime3, millis3); 
    PackData(sendBuffer, (uint8_t *)sendData, ID);
    UART_XB_UartPutString(sendBuffer);
    UART_XB_UartPutChar('0');
    #ifdef DEBUG_INFO
//    SW_uartDebug_PutString("send time ");
//    SW_uartDebug_PutString(sendBuffer);
//    SW_uartDebug_PutString("\n\r");
    #endif
}
/* [] END OF FILE */
