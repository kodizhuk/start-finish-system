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

//void AppDelay(uint32_t delayMs)
//{
//    uint32_t runTime;
//    
//    runTime = 0;
//    
//    if(delayMs < MIN_DELAYMS)
//    {
//        CyDelay(delayMs);
//    }else
//    {
//        AppDelay_WriteCounter(131071);
//        uint32_t counter = AppDelay_ReadCounter();
//        
//        AppDelay_Start();
//        
//        while(((delayMs - runTime) > MIN_DELAYMS) && (runTime <= delayMs))
//        {
//            /*user function*/      
//            if(inData.readStatus == READ_OK && outData.writeStatus == NO_WRITE )
//            {
//                SendData();           
//            }
//            
//            if(inData.readStatus == READ_OK && outData.writeStatus == WRITE_OK)
//            {
//                ReceiveData();
//                
//                #ifdef DEBUG_PC
//                inData.readStatus = READ_OK;
//                #endif
//            }
//            
//            /*write result skier on log*/
//            if((FifoGetSize() > 0) || (writeFlag == ERROR))
//            {
//                uint32_t result;
//                skierDB_El tmpStruct;
//                if (writeFlag == NO_ERROR)
//                {
//                    FifoGet(&tmpStruct);
//                    FifoPushLast(tmpStruct);
//                }
//                else
//                {
//                    tmpStruct = fifo.last;
//                }
//                result = WriteSkierResult(&tmpStruct);
//                if(result != FR_OK)
//                {
//                    logStart();
//                    writeFlag = ERROR;
//                }
//                else
//                {
//                    writeFlag = NO_ERROR;
//                }
//            }
//            
//            CyDelay(MIN_DELAYMS);
//
//            uint32_t period = AppDelay_ReadPeriod();
//            counter = AppDelay_ReadCounter();
//            runTime = (period -  counter)/32.768;
//            
//            /*user function*/  
//        }
//        AppDelay_Stop();
//        
//        #ifdef DEBUG_PC
//        char buffer[100];
//        sprintf(buffer,"time send data %u\n\r", (runTime));
//        SW_UART_DEBUG_PutString(buffer);
//        #endif
//        
//        /*tyme to respond*/
//        if(numAttemps++ >= 2)
//        {
//            numAttemps=0;
//            outData.writeStatus = NO_WRITE;
//        }
//        if(noConnect++ >= 4)
//        {
//            networkStatus = NETWORK_DISCONN;
//        }
//        
//        
//        if (delayMs > runTime)
//        {
//            CyDelay(delayMs - runTime);
//        }
//    }   
//}

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
}



void SendFinStatus(uint32_t ready)
{
    outData.ready = ready;
}

uint32_t NetworkStatus(void)
{
    return networkStatus;
}
/* [] END OF FILE */
