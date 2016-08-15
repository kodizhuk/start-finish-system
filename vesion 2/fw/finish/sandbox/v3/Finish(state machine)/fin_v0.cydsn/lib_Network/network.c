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
    uint16_t deliveryMs;
    uint32_t resultReceive;
    uint32_t noConnect;
    signed int sumTime;
    signed int sumMillis;
    
    deliveryTime = 0;
    deliveryMs = 0;
    IDpacket = 0;
    noConnect = 0;
    for(i=0; i < NUM_TRY_SYNC && noConnect <= NUM_CONNECT_ATTEMPS;)
    {
        /*send real time to start*/
        unixTime[T1] = RTCGetUnixTime();
        millisTime[T1] = RTCgetRecentMs();
        NTPsendTime(unixTime[T1], millisTime[T1], IDpacket);
        
        #ifdef DEBUG_PC 
        char buffer[100];
        sprintf(buffer,"\n\rsend time t1= %u\n\r",unixTime[T1]);
        SW_UART_DEBUG_PutString(buffer);
        #endif
        
        /*receive time from start*/
        resultReceive = NTPreceiveTime(&unixTime[T2],&millisTime[T2], &unixTime[T3], &millisTime[T3], &IDreceivePacket);
        
        #ifdef DEBUG_PC 
        if(resultReceive == READ_OK)
        {
            sprintf(buffer,"\n\rt2= %u:%u, t3= %u:%u\n\r",unixTime[T2],millisTime[T2],unixTime[T3], millisTime[T3]);
            SW_UART_DEBUG_PutString(buffer);
        }
        sprintf(buffer,"\n\rFinish i= %u, noConnect= %u\n\r",i,noConnect);
        SW_UART_DEBUG_PutString(buffer);
        #endif
        
        if((resultReceive == READ_OK) && (IDreceivePacket == IDpacket))
        {
            /*delivery timing*/
            unixTime[T4] = RTCGetUnixTime();
            millisTime[T4] = RTCgetRecentMs();
            //sumTime = ((unixTime[T2]-unixTime[T1])+(unixTime[T4]-unixTime[T3]))/2;
            //sumMillis = ((millisTime[T2]-millisTime[T1])+(millisTime[T4]-millisTime[T3]))/2;
            sumTime = ((unixTime[T4] - unixTime[T1]) - (unixTime[T3] - unixTime[T2]))/2;
            sumMillis = ((millisTime[T4] - millisTime[T1]) - (millisTime[T3] - millisTime[T2]))/2;
            if (sumMillis < 0)
            {
                sumMillis += 1000;
                sumTime++;
            }
            deliveryTime += sumTime;
            deliveryMs += sumMillis;
            if (deliveryTime >= 1000)
            {
                int SSS = 10;
                deliveryTime = 0;
            }
            if (deliveryMs >= 1000)
            {
                deliveryTime++;
                deliveryMs-=1000;
            }
            #ifdef DEBUG_PC 
            sprintf(buffer,"\n\r DEV!!! time s= %u, ms = %u\n\r",deliveryTime,deliveryMs);
            SW_UART_DEBUG_PutString(buffer);
            #endif            
            IDpacket++;
            noConnect=0;
            i++;
        }else
        {
            noConnect++;
            
            #ifdef DEBUG_PC
            CyDelay(500);
            #endif
        }
    }
    if(noConnect >= NUM_CONNECT_ATTEMPS)
    {
        result = TIME_SYNC_ERR;
    }else
    {
        uint16_t outMs;
        uint16_t tmpData;
        
        deliveryTime  = 0;///= NUM_TRY_SYNC;
        tmpData = deliveryTime*1000;
        deliveryMs = (tmpData+deliveryMs)/(NUM_TRY_SYNC);
        while (deliveryMs>=1000)
        {
            deliveryMs-=1000;
            deliveryTime++;
        }
        deliveryMs /= NUM_TRY_SYNC;
        
        unixTime[T4] = RTCGetUnixTime()+deliveryTime;
        millisTime[T4] = RTCgetRecentMs()+deliveryMs;
        
        if((millisTime[T4]) >= 1000)
        {
            unixTime[T4] ++;
            millisTime[T4] -= 1000;
        }
        
        /*send real time to start*/  
        NTPsetTimeToStart(unixTime[T4], millisTime[T4], IDpacket);
        #ifdef DEBUG_PC 
        char buffer[100];
        SW_UART_DEBUG_PutString("SAVE REAL TIME!!!!!!!!!!!!!!!");
        sprintf(buffer,"\n\rreal time= %u, delivery= %u\n\r",unixTime[T4],deliveryTime);
        SW_UART_DEBUG_PutString(buffer);
        CyDelay(2000);
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
    
    #ifdef DEBUG_PC
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
        
        #ifdef DEBUG_PC
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
    UART_XB_UartPutString(sendBuffer);
    #ifdef DEBUG_PC
        SW_UART_DEBUG_PutString("SEND READL TIME TO START!!!");
        SW_UART_DEBUG_PutString(sendBuffer);
    #endif
}
/* [] END OF FILE */
