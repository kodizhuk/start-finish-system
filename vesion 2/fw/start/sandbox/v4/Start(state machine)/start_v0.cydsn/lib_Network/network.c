
#include "lib_Network\network.h"
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

#include <stdio.h>
#include "lib_Network\svt.h"
#include "lib_RTC\RTC_WDT.h"
#include "lib_Network\ntp.h"
#include "lib_Display\display.h"

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

#ifdef DEBUG_INFO
    char uartBuff[50];
#endif

uint32_t ReceiveRealTime(void);
void NTPsendTime(uint32_t unixTime2,uint32_t unixTime3,uint16_t millis2,uint16_t millis3, uint16_t ID);
uint32_t NTPreceiveTime(uint32_t *unixTime2,uint16_t *millis2, uint16_t *IDreceive, uint32_t saveTime);

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
    
    #ifdef DEBUG_INFO
        SW_UART_DEBUG_Start();
        SW_UART_DEBUG_PutString("HElLO, IM READY(start)\n\r");
    #endif
    
    inData.readStatus = NO_READ;
    outData.writeStatus = WRITE_OK;
    outData.IDpacket = 0xFF;
    networkStatus = NETWORK_DISCONN;   
    UART_XB_SpiUartClearRxBuffer();
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
* Return:
*   TIME_SYNC_OK or TIME_SYNC_ERR
*
*******************************************************************************/
uint32_t NTPsync(void)
{
    int i;
    uint16_t result;
    uint16_t IDreceivePacket;
    uint16_t lastIDpacket;
    uint32_t resultReceive;
    
    /*calculaiton delivery time*/
    lastIDpacket = 1;
    result = TIME_SYNC_ERR;
    
    #ifdef DEBUG_INFO
        SW_UART_DEBUG_PutString("start ntp sync start\n\r");
    #endif  
    
    for(i=1; (i < 2000) && (result == TIME_SYNC_ERR); )
    {      
        /*receive time */
        resultReceive = NTPreceiveTime(&unixTime[T2],&millisTime[T2], &IDreceivePacket, !SAVE_TIME);
        CyDelay(9);

        if(resultReceive == READ_OK)
        {          
            if(IDreceivePacket == 0)
            {
                /*receive delivery time*/
                uint32_t unixTimeReal;
                uint16_t millisTimeReal;
                
                unixTimeReal = RTC_GetUnixTime();
                millisTimeReal = RTCgetRecentMs();
                
                unixTimeReal += unixTime[T2];
                if((millisTimeReal += millisTime[T2]) >= 1000)
                {
                    unixTimeReal++;
                    millisTimeReal -= 1000;
                }
                
                RTCSync(unixTimeReal, millisTimeReal);
                
                NTPsendTime(0,0,0,0,IDreceivePacket);
                
                #ifdef DEBUG_NTP
//                    debugntp_Write(1);
//                    debugntp_Write(0);
//                    debugntp_Write(1);
//                    debugntp_Write(0);                        
                #endif
                
                result = TIME_SYNC_OK;
                i = NUM_TRY_SYNC;
                
                /*display loading sync time*/
                for(i=0;i<13;i++)
                {
                    DisplayLoading(i);
                    CyDelay(100);
                }
                
                #ifdef DEBUG_INFO
                    sprintf(uartBuff,"receive delivery time %u:%u\n\r", unixTime[T2], millisTime[T2]); 
                    SW_UART_DEBUG_PutString(uartBuff);
                #endif                    
            }
            else //if(IDreceivePacket != 0)
            {
                /*no error, send time*/
                CyDelay(100);
                millisTime[T3] = RTCgetRecentMs();
                unixTime[T3] = RTCGetUnixTime();
                
                #ifdef DEBUG_NTP
                    debugntp_Write(1);
                    debugntp_Write(0);
                    debugntp_Write(1);
                    debugntp_Write(0);                        
                #endif
                
                if((unixTime[T2] == unixTime[T3]) || ((unixTime[T2] == (unixTime[T3])-1)))
                {
                    NTPsendTime(unixTime[T2], unixTime[T3], millisTime[T2], millisTime[T3], IDreceivePacket);

                    #ifdef DEBUG_INFO
                        sprintf(uartBuff,"receive and send time %u:%u",unixTime[T2],millisTime[T2]); 
                        SW_UART_DEBUG_PutString(uartBuff);
                        sprintf(uartBuff,"- %u:%u\n\r",unixTime[T3],millisTime[T3]); 
                        SW_UART_DEBUG_PutString(uartBuff);                        
                    #endif
                }
                i=0;
            }           
        }
        else 
        {
            i++;
        }
    }

    return result;
}

/*******************************************************************************
* Function Name: ReceiveRealTime
********************************************************************************
*
* Summary:
*   receive and set real time
* Return:
*   READ_OK or NO_READ
*
*******************************************************************************/
uint32_t ReceiveRealTime(void)
{
    uint32_t result;
    uint16_t IDpacket;
    
    result = NO_READ;
    noConnect = 0;
    
    #ifdef DEBUG_INFO
        SW_UART_DEBUG_PutString("start receive real time\n\r");
    #endif
    
    while(result == NO_READ && noConnect < NUM_CONNECT_ATTEMPS)
    {
        result = NTPreceiveTime(&unixTime[T1], &millisTime[T1], &IDpacket,SAVE_TIME);

        if((result == READ_OK) && (IDpacket == 1))
        {
            if((millisTime[T1]) > 1000)
            {
                unixTime[T1]++;
                millisTime[T1] -= 1000;
            }
            
            RTCSync(unixTime[T1], millisTime[T1]);

            NTPsendTime(0,0,0,0,IDpacket);
            
            #ifdef DEBUG_INFO
                sprintf(uartBuff,"set time %u:%u\n\r",unixTime[T1],millisTime[T1]);
                SW_UART_DEBUG_PutString(uartBuff);
            #endif
        }
        else
        {
            result = NO_READ;
            noConnect++;
            CyDelay(100);
        }
    }
    
    return result;
}
/*******************************************************************************
* Function Name: NTPreceiveTime
********************************************************************************
*
* Summary:
*   receive time to NTP protocol
* Parametrs:
*   *unixTime2 - time in unix format
*   *millisTime2 - millis time
*   *IDreceive - ID packet
*   saveTime - command save time from finish
* Return:
*   READ_OK or NO_READ
*
*******************************************************************************/
uint32_t NTPreceiveTime(uint32_t *unixTime2,uint16_t *millisTime2, uint16_t *IDreceive,uint32_t saveTime)
{
    uint8_t byte;
    uint32_t result;
    
    result = READ_OK;
    
    NTPResp recvDataNTP;
    while((UART_XB_SpiUartGetRxBufferSize() > 0) && ((byte=UART_XB_UartGetChar()) != 0))
    {                    
        result = NtpUnpackData(&recvDataNTP, (uint8_t)(byte & 0xFF));
        
        CyDelay(1);
                    
        if(recvDataNTP.EndPacket == 1)
        {
            /*save unix time*/            
            *IDreceive = recvDataNTP.Id;
            #ifdef DEBUG_INFO
                sprintf(uartBuff,"receive ID=%u",recvDataNTP.Id);
                SW_UART_DEBUG_PutString(uartBuff);
            #endif
            
            if((saveTime == SAVE_TIME) || (recvDataNTP.Id == 0))
            {
                /*save receive data*/
                *unixTime2 = recvDataNTP.Data1;
                *millisTime2 = recvDataNTP.DataMs1;
            }
            else
            {
                /*set real time*/
                RTCSync(recvDataNTP.Data1, recvDataNTP.DataMs1);
                
                /*save time T2*/
                *millisTime2 = RTCgetRecentMs();
                *unixTime2 = RTC_GetUnixTime();
                
                #ifdef DEBUG_NTP
                    debugntp_Write(1);
                    debugntp_Write(0);
                #endif
                #ifdef DEBUG_INFO
                    sprintf(uartBuff,"\n\rT2 %u:%u\n\r",*unixTime2,*millisTime2); 
                    SW_UART_DEBUG_PutString(uartBuff);
                #endif
                
            }

            return READ_OK;
        }
        result = NO_READ;
    }
    result = NO_READ;
    
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
    
    #ifdef DEBUG_INFO
       //SW_UART_DEBUG_PutString(sendBuffer);
       //SW_UART_DEBUG_PutString("\n\r"); 
    #endif
}
/* [] END OF FILE */
