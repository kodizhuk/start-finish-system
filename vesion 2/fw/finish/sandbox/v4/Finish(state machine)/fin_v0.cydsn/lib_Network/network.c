
#include "lib_Network\network.h"
#include <UART_XB.h>
#include <UART_XB_SPI_UART.h>

#ifdef DEBUG_INFO
    #include <SW_UART_DEBUG.h>
#endif
#ifdef DEBUG_TIME
    #include <debug.h>
#endif
#ifdef DEBUG_NTP
    #include <debugntp.h>
#endif

#include "lib_Network\svt.h"
#include "lib_DB\database.h"
#include "lib_RTC\RTC_WDT.h"
#include "lib_Network\ntp.h"
#include "lib_Display\display.h"


/*size buffer*/
#define DATA_BUFFER   50
 
#define ADRESS_READY        8
#define ADRESS_REBOOT       9
#define ADRESS_COUNT_SK     10

#define NETWORK_TIMEOUT     50

/*for NTP protocol*/
#define NUM_TRY_SYNC        14
#define NUM_CONNECT_ATTEMPS 50
#define NUM_TRU_SEND_PACKET 6
    
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


uint32_t SendRealTimeToStart(void);
void NTPsendTime(uint32_t unixTime1,uint16_t millis1, uint16_t ID);
uint32_t NTPreceiveTime(uint32_t *unixTime2,uint16_t *millis2, uint32_t *unixTime3, uint16_t *millis3, uint16_t *IDreceive);
uint32_t NTPsetTimeToStart(uint32_t unixTime4,uint16_t millis4,  uint16_t ID);
void NTPcalculateTime(uint32_t unixTime[], uint16_t msTime[], int32_t *sumTime, int32_t *sumMs);



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
    SW_UART_DEBUG_PutString("HElLO, IM READY(fin)\n\r");
    #endif
    
    inData.readStatus = READ_OK;
    outData.writeStatus = NO_WRITE;
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
    if( outData.writeStatus == NO_WRITE || inData.readStatus == READ_OK)
    {
        char sendBuffer[DATA_BUFFER];
        char sendData[DATA_BUFFER];
        
        outData.countSkiers = SkierOnWay();
        
        /*pack data*/
        sprintf(sendData,"%02X:%016X%02X%02X%02X%02X", 0u, 0u, outData.ready, outData.reboot, \
            outData.countSkiers, 0u);    
        PackData(sendBuffer, (uint8_t *)sendData, outData.IDpacket);
        UART_XB_UartPutString(sendBuffer);
        
        
        /*flag transmit data*/
        outData.writeStatus = WRITE_OK;
        inData.readStatus = NO_READ;
        
        /*set timeout*/
        noConnect = 0; 
        
        CyDelay(50);
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
uint32_t  ReceiveData(void)
{   
    if(inData.readStatus == NO_READ && outData.writeStatus == WRITE_OK)
    {
        uint32_t result = 0;
        int i;
        uint8_t byte;
        struct Resp recvData;
          
        while((UART_XB_SpiUartGetRxBufferSize() > 0) && ((byte=UART_XB_UartGetChar()) != 0))
        { 
            result = UnpackData(&recvData, (uint8_t)(byte & 0xFF));
            CyDelay(2);
            
            
            if(recvData.EndPacket == 1)
            {
                inData.IDpacket = recvData.Seq;
                
                /*id packet ok*/
                if(outData.IDpacket == inData.IDpacket)
                {
                    inData.readStatus = READ_OK;
                    outData.writeStatus = NO_WRITE;
                    
                    /*connect network*/
                    networkStatus = NETWORK_CONNECT;
                    noConnect = 0;
                    
                    /*write data*/
                    inData.newSkier = (recvData.Data3 & 0xFF00) >> 8;
                    inData.unixStartTime = recvData.Data1;
                    inData.startMsTime = recvData.Data2;
                    inData.reboot = (recvData.Data3 & 0x00FF);
                    
                    /*if new skier on track*/
                    if(inData.newSkier == NEW_SKIER_IN_TARCK )
                    {
                        WriteStartTime(inData.unixStartTime, inData.startMsTime);
                    }
                    
                    /*next packet*/
                    outData.IDpacket++;
                    CyDelay(50);
                }  
                /* if prev packet late*/
                else if(outData.IDpacket == (inData.IDpacket + 1))
                {
                    inData.newSkier = recvData.Data3;
                    inData.unixStartTime = recvData.Data1;
                    inData.startMsTime = recvData.Data2;
                    
                    networkStatus = NETWORK_CONNECT;
                    noConnect = 0;
                    CyDelay(50);
                }
                return  NETWORK_CONNECT;  
            }
        }
        
        noConnect++;
        if(noConnect >= NETWORK_TIMEOUT)
        {
            outData.writeStatus = NO_WRITE;
            inData.readStatus = NO_READ;
            networkStatus = NETWORK_DISCONNECT;
        }
        
        return  NETWORK_DISCONNECT;
    }
    return 0;
}


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
    outData.reboot = 1;
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
    uint32_t unixTime[4];
    uint16_t millisTime[4];
    int32_t sumTime;
    int32_t sumMillis;   
    uint32_t numAttempsReseive;
    uint32_t numTruReceive;
    
    #ifdef DEBUG_INFO
        char uartBuff[100];
    #endif  
    
    IDpacket = 1;
    IDreceivePacket = 0;
    numAttempsReseive = 0;
    result = TIME_SYNC_ERR;
    
    #ifdef DEBUG_INFO
        SW_UART_DEBUG_PutString("start ntp sync\n\r");
    #endif  
    /*sync milisecond and second*/
    for(i=1; i < NUM_TRY_SYNC; )
    {
        /*send time T1*/
        unixTime[T1] = RTCGetUnixTime();
        millisTime[T1] = RTCgetRecentMs();
        
        #ifdef DEBUG_NTP
            debugntp_Write(1);
            debugntp_Write(0);
        #endif
        
        NTPsendTime(unixTime[T1], millisTime[T1], IDpacket);
        
        /*reseive data*/
        resultReceive = NO_READ;
        numAttempsReseive = 0;
        while((resultReceive == NO_READ) && (numAttempsReseive < NUM_CONNECT_ATTEMPS*4))
        {
            /*receive time from start*/
            resultReceive = NTPreceiveTime(&unixTime[T2],&millisTime[T2], &unixTime[T3], &millisTime[T3], &IDreceivePacket);
                    
            if((resultReceive == READ_OK) && (IDreceivePacket == IDpacket))
            {
                /*delivery timing*/
                unixTime[T4] = RTCGetUnixTime();
                millisTime[T4] = RTCgetRecentMs();
                
                #ifdef DEBUG_NTP
//                    millisTime[T4] = millisTime[T1]+193;
//                    unixTime[T4] = unixTime[T1];
//                    if(millisTime[T4] >= 1000)
//                    {
//                        millisTime[T4] -= 1000;
//                        unixTime[T4]++;
//                    }
                    debugntp_Write(1);
                    debugntp_Write(0);
                    debugntp_Write(1);
                    debugntp_Write(0);                    
                #endif
                NTPcalculateTime(unixTime, millisTime,&sumTime, &sumMillis);
                CyDelay(1000); 
                #ifdef DEBUG_INFO 
                    SW_UART_DEBUG_PutString("calculate time\n\r");
                #endif  
                
                /* send delivery time */
                IDpacket = 0;
                result = NTPsetTimeToStart(sumTime, sumMillis, IDpacket);
                
                if(result == WRITE_OK)
                {
                    /*display loading sync time*/
                    for(i=0;i<13;i++)
                    {
                        DisplayLoading(i);
                        CyDelay(100);
                    }
                    result = TIME_SYNC_OK;
                }
                else
                {
                    result = TIME_SYNC_ERR;
                }
                                            
                i = NUM_TRY_SYNC; 
                resultReceive = READ_OK;
            }
            else
            {
                numAttempsReseive++;
                resultReceive = NO_READ;
                CyDelay(10);
            }
        }
        
        CyDelay(100);
        
        IDpacket++;
        i++;  
    }

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
    
    /*pack data*/
    sprintf(sendData,"%08X%03X", unixTime,millis); 
    PackData(sendBuffer, (uint8_t *)sendData, ID);
    UART_XB_UartPutString(sendBuffer);
    
    #ifdef DEBUG_INFO 
        SW_UART_DEBUG_PutString(sendBuffer);
        SW_UART_DEBUG_PutString("\n\r");
    #endif  
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
        #ifdef DEBUG_INFO
            //SW_UART_DEBUG_PutChar(byte);
        #endif
            
        if(recvDataNTP.EndPacket == 1)
        {
            /*save unix time*/
            *IDreceive = recvDataNTP.Id;
            *unixTime2 = recvDataNTP.Data1;
            *millisTime2 = recvDataNTP.DataMs1;
            *unixTime3 = recvDataNTP.Data2;
            *millisTime3 = recvDataNTP.DataMs2;

            #ifdef DEBUG_INFO
                char uartBuff[100];
                sprintf(uartBuff,"id receive=%u\n\r",recvDataNTP.Id);
                SW_UART_DEBUG_PutString(uartBuff);
            #endif
        
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
            #ifdef DEBUG_INFO 
                SW_UART_DEBUG_PutString("send delivery time ok\n\r");
            #endif 
        }
        else
        {
            result = NO_WRITE;
            noConnect++;
            CyDelay(500);
            
            #ifdef DEBUG_INFO 
                char uartBuff[100];
                sprintf(uartBuff,"noConnect=%u",noConnect);
                SW_UART_DEBUG_PutString(uartBuff);
            #endif             
        }
    }
    
    return result;
}

void NTPcalculateTime(uint32_t unixTime[], uint16_t msTime[], int32_t *sumTime, int32_t *sumMs)
{
    /*calculate ms time*/
    int32_t tmpMsMaster;
    int32_t tmpTimeMaster;    
    int32_t tmpMsSlave;
    int32_t tmpTimeSlave;
    int32_t tmpDiffTime;
    int32_t tmpDiffMs;
    
    tmpTimeMaster = unixTime[T4] - unixTime[T1];
    tmpMsMaster = (msTime[T4] - msTime[T1]);
    if(tmpMsMaster < 0)
    {
        tmpMsMaster += 1000;
        tmpTimeMaster--;
    }
    
    tmpTimeSlave = unixTime[T3] - unixTime[T2];
    tmpMsSlave = msTime[T3] - msTime[T2];
    if(tmpMsSlave < 0)
    {
        tmpMsSlave += 1000;
        tmpTimeSlave--;
    }
    
    tmpDiffTime = tmpTimeMaster - tmpTimeSlave;
    tmpDiffMs = tmpMsMaster - tmpMsSlave;
    
    tmpDiffMs /= 2;
    if(tmpDiffTime%2 == 1)
    {
        tmpDiffMs += 500;
    }
    tmpDiffTime /= 2;
    
    *sumTime = tmpDiffTime;
    *sumMs = tmpDiffMs;   
}
/* [] END OF FILE */
