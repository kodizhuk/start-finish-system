
#include "lib_Network/network.h"
#include <lib_BLE/bluetooth.h>
#include <UART_XB.h>
#include <UART_XB_SPI_UART.h>

#ifdef DEBUG_INFO
    #include <DEBUG_UART.h>
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

#include "lib_Network/svt.h"
#include "lib_DB/database.h"
#include "lib_RTC/RTC_WDT.h"
#include "lib_Network/ntp.h"
#include "lib_Display/display.h"


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
    uint8_t testMode;
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
    uint8_t testMode;
    uint8_t reboot;     /*reboot=1, no reboot=0*/
    
    uint8_t readStatus;     /*flag successful read data in start*/
}StartData;

FinishData outData ;
StartData inData;
uint8_t rebootFlag ;

uint16_t numAttemps,noConnect, networkStatus;
uint32_t unixTime[4];
uint16_t millisTime[4];
/*new ntp*/
uint8_t ntpFlagEndReceivePacket;        //indicator end receive packet
uint8_t ntpFlagReadyForReceive;         //indicator ready for receive next packet
NtpResp recvDataNTP;
uint8_t onNtpSync = 0;

/*timer time sync*/
uint32_t oldUnixTime;


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
    DEBUG_UART_Start();     
    DEBUG_UART_UartPutString("HElLO, IM READY(fin)\n\r");
    #endif
    
    inData.readStatus = READ_OK;
    outData.writeStatus = NO_WRITE;
    UART_XB_SpiUartClearRxBuffer();
    
    rebootFlag = REBOOT;
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
        sprintf(sendData,"%02X:%016X%02X%02X%02X%02X", outData.testMode, 0u, outData.ready, outData.reboot, \
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
                    inData.testMode = recvData.Command;
                    
                    /*if new skier on track*/
                    if(inData.newSkier == NEW_SKIER_IN_TARCK )
                    {
                        WriteStartTime(inData.unixStartTime, inData.startMsTime);
                        BLE_sendOneSkierTimeStart(inData.unixStartTime, inData.startMsTime,GetIDskierStarted(),SkierOnWay(),MAX_SKIERS_ON_WAY);
                        IncrementID();
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
void SendFinStatus(uint32_t status)
{
    outData.ready = status;
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
    
    if((inData.reboot == 1 && outData.reboot == 0) || (rebootFlag == REBOOT))
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
    rebootFlag = NO_REBOOT;
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
    inData.reboot = 0;
    rebootFlag = REBOOT;
}

/*******************************************************************************
* Function Name: NetworkReadTestModeStatus
********************************************************************************
*
* Summary:
*   reading adopted flag test mode
*
* Returns:
*   testMode status
*******************************************************************************/
uint8_t NetworkReadTestModeStatus()
{
    return inData.testMode;
}

/*******************************************************************************
* Function Name: NetworkSendTestModeStatus
********************************************************************************
*
* Summary:
*   exhibiting a test mode for future shipping
*
* Parametrs:
*   0 - test mode stopped
*   1 - test mode started
*******************************************************************************/
void NetworkSendTestModeStatus(uint8_t testMode)
{
    if(testMode > 0)
    {
        outData.testMode = 1;
    }
    else
    {
        outData.testMode = 0;
    }
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
    uint16_t IDpacket;
    UART_XB_SpiUartClearRxBuffer();
    
    /*----------------------------------------------------------
    send real unix time
    ----------------------------------------------------------*/
    uint16_t delayReceivePacket ;
    uint16_t numAttemptSendPacket = NTP_CONNECT_ATTEMPS;
    result = ERROR;
    ntpFlagReadyForReceive = 1;
    onNtpSync = 1;
    
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
        uint32_t oldUnixTime = RTCGetUnixTime();
        delayReceivePacket += RTCgetRecentMs();
        
        #ifdef DEBUG_INFO
//                DEBUG_UART_UartPutString("send new packet\n\r");
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
//                        DEBUG_UART_UartPutString(uartBuff);
                #endif
                
                ntpFlagReadyForReceive = 1;
            }
            
            if((oldUnixTime<RTCGetUnixTime()) && (delayReceivePacket >= 1000))
            {
                delayReceivePacket -= 1000;
                oldUnixTime++;
                
                #ifdef DEBUG_INFO
//                        sprintf(uartBuff,"delayReceive=%d, realTimeMs=%d\n\r",delayReceivePacket,(uint32_t)RTCgetRecentMs());
//                        DEBUG_UART_UartPutString(uartBuff);
//                        sprintf(uartBuff,"unix[T1]=%d, realTimeunix=%d\n\r",unixTime[T1],(uint32_t)RTCGetUnixTime());
//                        DEBUG_UART_UartPutString(uartBuff);
                #endif
            }
        }
        numAttemptSendPacket--;
    }
    
    
    
    /*----------------------------------------------------------
    calculate difference time
    ----------------------------------------------------------*/
    uint8_t numSuccessuflPacket = 0;
    int32_t unixTimeDifference = 0;
    int32_t msTimeDifference = 0;
    numAttemptSendPacket = 0;
    IDpacket = 2;

    if(result == OK)
    {
        numSuccessuflPacket = NTP_SUCCESSFUL_PACKET;
        numAttemptSendPacket = NTP_CONNECT_ATTEMPS;
    }
    
    while(numAttemptSendPacket && numSuccessuflPacket )
    {
        result = ERROR;
        unixTime[T1] = RTCGetUnixTime();
        millisTime[T1] = RTCgetRecentMs();
        #ifdef DEBUGNTP
            pinDebugNtp_Write(1);
            pinDebugNtp_Write(0);
            pinDebugNtp_Write(1);
            pinDebugNtp_Write(0);
        #endif 
        NTPsendTime(unixTime[T1], millisTime[T1], IDpacket);
        
        delayReceivePacket =  2*NTP_DELAY_RECEIVED_PACKET ;
        delayReceivePacket += RTCgetRecentMs();
        uint32_t oldUnixTime = RTCGetUnixTime();
        #ifdef DEBUG_INFO
//                DEBUG_UART_UartPutString("send new packet\n\r");
//                sprintf(uartBuff,"numSuccesful=%d\n\n\r",numSuccessuflPacket);
//                DEBUG_UART_UartPutString(uartBuff);
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
                    unixTimeDifference += tmpUnix;
                    msTimeDifference += tmpMs;
                    
                    #ifdef DEBUG_INFO
//                        sprintf(uartBuff,"diff unix=%d, diff ms-%d\n\r",tmpUnix, tmpMs);
//                        DEBUG_UART_UartPutString(uartBuff);
//                        int32_t tmpU;
//                        int16_t tmpms;
//
//                        FuncTake(unixTime[T3],millisTime[T3],unixTime[T2],millisTime[T2],&tmpU,&tmpms);
//                        sprintf(uartBuff,"T3-T2=%d.%d\n\r",tmpU, tmpms);
//                        DEBUG_UART_UartPutString(uartBuff);
//                        
//                        FuncTake(unixTime[T4],millisTime[T4],unixTime[T1],millisTime[T1],&tmpU,&tmpms);
//                        sprintf(uartBuff,"T4-T1=%d.%d\n\r",tmpU, tmpms);
//                        DEBUG_UART_UartPutString(uartBuff);
//                        
//                        FuncTake(unixTime[T2],millisTime[T2],unixTime[T1],millisTime[T1],&tmpU,&tmpms);
//                        sprintf(uartBuff,"T2-T1=%d.%d\n\r",tmpU, tmpms);
//                        DEBUG_UART_UartPutString(uartBuff);
                    #endif
                }
                
                #ifdef DEBUG_INFO
//                        sprintf(uartBuff,"succesful=%d\n\r",numSuccessuflPacket);
//                        DEBUG_UART_UartPutString(uartBuff);
                #endif
                
                ntpFlagReadyForReceive = 1;
            }
            if((oldUnixTime<RTCGetUnixTime()) && (delayReceivePacket >= 1000))
            {
                delayReceivePacket -= 1000;
                oldUnixTime++;
            }
        }
        numAttemptSendPacket--;
        IDpacket++;
    }
    
    
    if(result == OK)
    {
        unixTimeDifference /= NTP_SUCCESSFUL_PACKET;
        msTimeDifference /= NTP_SUCCESSFUL_PACKET;
        msTimeDifference += 13; //add static diff time to send packet 
    }
    
    #ifdef DEBUG_INFO
        sprintf(uartBuff,"---------diff_sum=%d.%d\n\r",unixTimeDifference, msTimeDifference);
        DEBUG_UART_UartPutString(uartBuff);
    #endif
    
    
    
    /*----------------------------------------------------------
    send to start difference time
    ----------------------------------------------------------*/
    numAttemptSendPacket = 0;
    if(result == OK)
    {
        numAttemptSendPacket = NTP_CONNECT_ATTEMPS;
    }
    ntpFlagReadyForReceive = 1;
    IDpacket = 0;
    
    while(numAttemptSendPacket)
    {
        result = ERROR;
        
        #ifdef DEBUGNTP
            pinDebugNtp_Write(1);
            pinDebugNtp_Write(0);
            pinDebugNtp_Write(1);
            pinDebugNtp_Write(0);
        #endif 
        /*send difference time*/
        NTPsendTime(0, (uint16)-msTimeDifference, IDpacket);
        
        delayReceivePacket = NTP_DELAY_RECEIVED_PACKET;
        uint32_t oldUnixTime = RTCGetUnixTime();       
        delayReceivePacket += RTCgetRecentMs();
        
        #ifdef DEBUG_INFO
//            DEBUG_UART_UartPutString("send new packet\n\r");
//            sprintf(uartBuff, "numAttemptSendPacket=%d\n\r",numAttemptSendPacket);
//            DEBUG_UART_UartPutString(uartBuff);
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
//                        DEBUG_UART_UartPutString(uartBuff);
                #endif
                
                ntpFlagReadyForReceive = 1;
            }
            
            if((oldUnixTime<RTCGetUnixTime()) && (delayReceivePacket >= 1000))
            {
                delayReceivePacket -= 1000;
                oldUnixTime++;
                
                #ifdef DEBUG_INFO
//                        sprintf(uartBuff,"delayReceive=%d, realTimeMs=%d\n\r",delayReceivePacket,(uint32_t)RTCgetRecentMs());
//                        DEBUG_UART_UartPutString(uartBuff);
//                        sprintf(uartBuff,"unix[T1]=%d, realTimeunix=%d\n\r",unixTime[T1],(uint32_t)RTCGetUnixTime());
//                        DEBUG_UART_UartPutString(uartBuff);
                #endif
            }
        }
        numAttemptSendPacket--;
        if(result == OK)
            numAttemptSendPacket = 0;
    }
    
    #ifdef DEBUG_INFO
        if(result == OK)
        DEBUG_UART_UartPutString("okey\n\r");
        else
        DEBUG_UART_UartPutString("error\n\r");
    #endif
    
    if(result == OK)
        result = TIME_SYNC_OK;
    else
        result = TIME_SYNC_ERR;
    
    onNtpSync = 0;

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
    UART_XB_UartPutChar('0');
    
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

uint8_t ChekTimerForTimeSync(void)
{
    uint8_t result;
    
    result = SYNC_NO_REQUIRES;
    
    if((oldUnixTime + TIME_BY_SYNC) < RTC_GetUnixTime())
    {
        result = SYNC_REQUIRES;
    }   
    
    return result;
}

void ResetTimerForTimeSync(void)
{
    oldUnixTime = RTC_GetUnixTime();
}
/* [] END OF FILE */
