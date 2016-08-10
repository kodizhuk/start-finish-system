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
#include "lib_Network\network.h"



void InitNetwork(void)
{
    UART_XB_Start();
    
    #ifdef DEBUG_PC
    SW_UART_DEBUG_Start();
    #endif
    
    inData.readStatus = READ_OK;
    outData.writeStatus = NO_WRITE;
    UART_XB_SpiUartClearRxBuffer();
    
}


void SendData(void)
{   
    if( outData.writeStatus == NO_WRITE || inData.readStatus == READ_OK)
    {
        char sendBuffer[DATA_BUFFER];
        char sendData[DATA_BUFFER];
        
        outData.countSkiers = SkierOnWay();
        
        /*for ntp protocol*/
        outData.reboot = 0;
        
        /*pack data*/
        sprintf(sendData,"%02X:%016X%02X%02X%02X", 0u, 0u, outData.ready, outData.reboot, outData.countSkiers);    
        PackData(sendBuffer, (uint8_t *)sendData, outData.IDpacket);
        UART_XB_UartPutString(sendBuffer);
        
        /*flag transmit data*/
        outData.writeStatus = WRITE_OK;
        inData.readStatus = NO_READ;
        
        /*set timeout*/
        noConnect = 0;
        
        #ifdef DEBUG_PC
        SW_UART_DEBUG_PutString("out data - "); 
        SW_UART_DEBUG_PutString(sendBuffer);   
        SW_UART_DEBUG_PutString("\n\r");
        #endif  
    }
}


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
            
            #ifdef DEBUG_PC
            SW_UART_DEBUG_PutChar(byte);
            #endif
            
            if(recvData.EndPacket == 1)
            {
                inData.IDpacket = recvData.Seq;
                
                /*id packet ok*/
                if(outData.IDpacket == inData.IDpacket)
                {
                    inData.readStatus = READ_OK;
                    outData.writeStatus = NO_WRITE;
                    
                    /*connect network*/
                    networkStatus = NETWORK_CONN;
                    noConnect = 0;
                    
                    /*write data*/
                    inData.newSkier = recvData.Data3;
                    inData.unixStartTime = recvData.Data1;
                    inData.startMsTime = recvData.Data2;
                    
                    /*if new skier on track*/
                    if(inData.newSkier == NEW_SKIER_IN_TARCK )
                    {
                        WriteStartTime(inData.unixStartTime, inData.startMsTime);
                    }
                    
                    /*next packet*/
                    outData.IDpacket++;
                    
                    #ifdef DEBUG_PC
                    SW_UART_DEBUG_PutString("       READ DATA OKEY");   
                    SW_UART_DEBUG_PutString("\n\r");
                    #endif 
                }  
                /* if prev packet late*/
                else if(outData.IDpacket == (inData.IDpacket + 1))
                {
                    inData.newSkier = recvData.Data3;
                    inData.unixStartTime = recvData.Data1;
                    inData.startMsTime = recvData.Data2;
                    
                    networkStatus = NETWORK_CONN;
                    noConnect = 0;
                    
                    #ifdef DEBUG_PC
                    SW_UART_DEBUG_PutString("       READ PREV DATA OKEY");   
                    SW_UART_DEBUG_PutString("\n\r");
                    #endif 
                }
                return  NETWORK_CONN;  
            }

        }
        
        noConnect++;
        if(noConnect >= NETWORK_TIMEOUT)
        {
            outData.writeStatus = NO_WRITE;
            inData.readStatus = NO_READ;
            networkStatus = NETWORK_DISCONN;
        }

        #ifdef DEBUG_PC
        //SW_UART_DEBUG_PutString("ERROR READ!!!!");   
        SW_UART_DEBUG_PutString("\n\r");
        #endif 
        
        return  NETWORK_DISCONN;
    }
    return 0;
}



void SendFinStatus(uint32_t ready)
{
    outData.ready = ready;
}

uint32_t NetworkStatus(void)
{
    return networkStatus;
}

/*NTP */

uint32_t NTPsync(void)
{
    int i;
    uint16_t result;
    uint32_t IDpacket;
    uint32_t IDreceivePacket;
    uint32_t unixTime[4];
    uint16_t millisTime[4];
    uint32_t deliveryTime;
    uint32_t deliveryMs;
    uint32_t resultReceive;
    uint32_t noConnect;
    int32_t sumTime;
    int32_t sumMillis;
    
    deliveryTime = 0;
    deliveryMs = 0;
    IDpacket = 0;
    IDreceivePacket = 0;
    noConnect = 0;
    #ifdef DEBUG_NTP
    SW_UART_DEBUG_PutString("START\n\r");                
    #endif
    #ifdef DEBUG_TIME
    char buffer[100];                
    #endif
    
    for(i=0; i < NUM_TRY_SYNC && noConnect <= NUM_CONNECT_ATTEMPS;)
    {
        /*send real time to start*/

        unixTime[T1] = RTCGetUnixTime();
        millisTime[T1] = RTCgetRecentMs();
        NTPsendTime(unixTime[T1], millisTime[T1], IDpacket);
        
        #ifdef DEBUG_TIME
        sprintf(buffer,"T1 = %u:%u\n\r",unixTime[T1],millisTime[T1]);
        SW_UART_DEBUG_PutString(buffer);                
        #endif
        #ifdef DEBUG_PC 
        char buffer[100];
        //sprintf(buffer,"\n\rsend time t1= %u\n\r",unixTime[T1]);
        //SW_UART_DEBUG_PutString(buffer);
        #endif
        CyDelay(300);
        /*receive time from start*/
        resultReceive = NTPreceiveTime(&unixTime[T2],&millisTime[T2], &unixTime[T3], &millisTime[T3], &IDreceivePacket);
        
        #ifdef DEBUG_PC 
        if(resultReceive == READ_OK)
        {
            //sprintf(buffer,"\n\rt2= %u:%u, t3= %u:%u\n\r",unixTime[T2],millisTime[T2],unixTime[T3], millisTime[T3]);
            //SW_UART_DEBUG_PutString(buffer);
        }
        sprintf(buffer,"\n\rFinish i= %u, noConnect= %u\n\r",i,noConnect);
        SW_UART_DEBUG_PutString(buffer);
        #endif
        
        if((resultReceive == READ_OK) && (IDreceivePacket == IDpacket))
        {
            /*delivery timing*/
            unixTime[T4] = RTCGetUnixTime();
            millisTime[T4] = RTCgetRecentMs();
            
            #ifdef DEBUG_TIME
            sprintf(buffer,"T2 = %u:%u, T3 = %u:%u\n\r",unixTime[T2],millisTime[T2],unixTime[T3],millisTime[T3]);
            SW_UART_DEBUG_PutString(buffer);                
            sprintf(buffer,"T4 = %u:%u\n\r",unixTime[T4],millisTime[T4]);
            SW_UART_DEBUG_PutString(buffer);                
            #endif  
            
            NTPcalculateTime(unixTime, millisTime,&sumTime, &sumMillis);

            deliveryTime += sumTime;
            deliveryMs += sumMillis;
            
            #ifdef DEBUG_TIME
            sprintf(buffer,"deliveryTime = %i:%u\n\r",sumTime,sumMillis);
            SW_UART_DEBUG_PutString(buffer);                
            #endif
            
            IDpacket++;
            noConnect=0;
            i++;
            #ifdef DEBUG_NTP
                if(i>=NUM_TRY_SYNC)i=0;
                SW_UART_DEBUG_PutString("\n\rReceive okey ID++");
            #endif
            #ifdef DEBUG_PC 
            //sprintf(buffer,"\n\r DEV!!! time s= %u, ms = %u\n\r",deliveryTime,deliveryMs);
            //SW_UART_DEBUG_PutString(buffer);
            #endif            
        }else
        {
            noConnect++;
            //CyDelay(500);
            #ifdef DEBUG_NTP
            //CyDelay(30);
            #endif
        }
    }
    
    
    if(noConnect >= NUM_CONNECT_ATTEMPS)
    {
        result = TIME_SYNC_ERR;
    }else
    {
        uint16_t outMs;
        uint16_t tmpDataMs;
                
        tmpDataMs = deliveryTime*1000;
        deliveryTime  = 0;///= NUM_TRY_SYNC;
        deliveryMs = (tmpDataMs + deliveryMs)/(NUM_TRY_SYNC);
        while (deliveryMs>=1000)
        {
            deliveryMs-=1000;
            deliveryTime++;
        }

        #ifdef DEBUG_TIME
        sprintf(buffer,"result calculate delivery = %i:%u\n\r",deliveryTime,deliveryMs);
        SW_UART_DEBUG_PutString(buffer);                
        #endif
        uint64_t unix = RTCGetUnixTime();
        uint32_t ms = RTCgetRecentMs();
        #ifdef DEBUG_TIME
            debug_Write(1);
            debug_Write(0);
            CyDelay(10);
        #endif
        
        unixTime[T4] = unix+deliveryTime;
        millisTime[T4] = ms+deliveryMs;
        
        if((millisTime[T4]) >= 1000)
        {
            unixTime[T4] ++;
            millisTime[T4] -= 1000;
        }
        
        #ifdef DEBUG_TIME
        sprintf(buffer,"real time = %lu",unix);
        SW_UART_DEBUG_PutString(buffer);
         sprintf(buffer,":%u\n\r",ms);
        SW_UART_DEBUG_PutString(buffer);
        sprintf(buffer,"send real time = %u:%u\n\r",unixTime[T4],millisTime[T4]);
        SW_UART_DEBUG_PutString(buffer);                
        #endif
        /*send real time to start*/  
        //debug_Write(1);
        //debug_Write(0);
        NTPsetTimeToStart(unixTime[T4], millisTime[T4], IDpacket);
        //debug_Write(1);
        //debug_Write(0);
        #ifdef DEBUG_PC 
        char buffer[100];
        SW_UART_DEBUG_PutString("SAVE REAL TIME!!!!!!!!!!!!!!!");
        sprintf(buffer,"\n\rreal time= %u, delivery= %u\n\r",unixTime[T4],deliveryTime);
        SW_UART_DEBUG_PutString(buffer);
        //CyDelay(2000);
        #endif
        
        result = TIME_SYNC_OK;
    }
    return result;
}

static void NTPsendTime(uint32_t unixTime1,uint16_t millis2, uint32_t ID)
{
    char sendBuffer[DATA_BUFFER];
    char sendData[DATA_BUFFER];
    
    /*pack data*/
    sprintf(sendData,"%08X%03X", unixTime1,millis2); 
    PackData(sendBuffer, (uint8_t *)sendData, ID);
    UART_XB_UartPutString(sendBuffer);
    
    #ifdef DEBUG_NTP
    SW_UART_DEBUG_PutString("\n\r");    
    SW_UART_DEBUG_PutString(sendBuffer);
    #endif
}


static uint32_t NTPreceiveTime(uint32_t *unixTime2, uint16_t *millisTime2, uint32_t *unixTime3, uint16_t *millisTime3, uint32_t *IDreceive)
{
    uint8_t byte;
    uint32_t result;
    /*debug*/
    result = READ_OK;
    
    NtpResp recvDataNTP;
    while((UART_XB_SpiUartGetRxBufferSize() > 0) && ((byte=UART_XB_UartGetChar()) != 0))
    {
        result = NtpUnpackData(&recvDataNTP, (uint8_t)(byte & 0xFF));
        
        #ifdef DEBUG_NTP
        SW_UART_DEBUG_PutChar(byte);
        #endif
                    
        if(recvDataNTP.EndPacket == 1)
        {
            /*save unix time*/
            *IDreceive = recvDataNTP.Id;
            *unixTime2 = recvDataNTP.Data1;
            *millisTime2 = recvDataNTP.DataMs1;
            *unixTime3 = recvDataNTP.Data2;
            *millisTime3 = recvDataNTP.DataMs2;
            #ifdef DEBUG_NTP
            SW_UART_DEBUG_PutString("    Receive okey\n\r");
            #endif
            return READ_OK;
        }
        result = NO_READ;
    }
    result = NO_READ;
    
    return result;
}


static void NTPsetTimeToStart(uint32_t unixTime4, uint16_t millisTime4, uint32_t ID)
{
    char sendBuffer[DATA_BUFFER];
    char sendData[DATA_BUFFER];
    
    /*pack data*/
    sprintf(sendData,"%08X%03X", unixTime4,millisTime4); 
    PackData(sendBuffer, (uint8_t *)sendData, ID);
    #ifdef DEBUG_TIME
    debug_Write(1);
    debug_Write(0);
    #endif
    UART_XB_UartPutString(sendBuffer);
    #ifdef DEBUG_TIME
        SW_UART_DEBUG_PutString("SEND READL TIME TO START!!!\n\r");
        SW_UART_DEBUG_PutString(sendBuffer);
    #endif
}

static void NTPcalculateTime(uint32_t unixTime[], uint16_t msTime[], int32_t *sumTime, int32_t *sumMs)
{
    /*calculate ms time*/
    int32_t tmpMsMaster;
    int32_t tmpTimeMaster;    
    int32_t tmpMsSlave;
    int32_t tmpTimeSlave;
    int32_t tmpDiffTime;
    int32_t tmpDiffMs;
    
    tmpTimeMaster = unixTime[T4] - unixTime[T1];
    if((tmpMsMaster = (msTime[T4] - msTime[T1])) < 0)
    {
        tmpMsMaster += 1000;
        tmpTimeMaster--;
    }
    
    tmpTimeSlave = unixTime[T3] - unixTime[T2];
    if((tmpMsSlave = (msTime[T3] - msTime[T2])) < 0)
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
