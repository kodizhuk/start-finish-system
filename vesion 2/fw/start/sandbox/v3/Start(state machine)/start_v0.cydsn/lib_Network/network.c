
#include "lib_Network\network.h"



void InitNetwork(void)
{
    UART_XB_Start();
    
    #ifdef DEBUG_PC
    SW_UART_DEBUG_Start();
    SW_UART_DEBUG_PutString("\n\nInit network start\n\n");
    #endif
    
    inData.readStatus = NO_READ;
    outData.writeStatus = WRITE_OK;
    outData.IDpacket = 0xFF;
    networkStatus = NETWORK_DISCONN;   
    UART_XB_SpiUartClearRxBuffer();
}

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
        }else
        {
            /*send nex packet*/
            
            char sendBuffer[DATA_BUFFER];
            char sendData[DATA_BUFFER];
            
            /*pack data*/
            sprintf(sendData,"%02X:%08X%08X%04X%02X",
                    0u,
                    (uint32_t)((outData.unixStartTime & MASK_HIGH) >> DATA_SHIFT), 
                    (uint32_t)(outData.unixStartTime & MASK_LOW), 
                    outData.startMsTime, 
                    outData.newSkier);
            
            
            PackData(sendBuffer, (uint8_t *)sendData, inData.IDpacket);
            UART_XB_UartPutString(sendBuffer);
            

            outData.newSkier = !NEW_SKIER_IN_TARCK;
                
            outData.writeStatus = WRITE_OK;
            outData.IDpacket = inData.IDpacket;
            inData.readStatus = NO_READ;
            #ifdef DEBUG_PC
            SW_UART_DEBUG_PutString("out data - "); 
            SW_UART_DEBUG_PutString(sendBuffer);   
            SW_UART_DEBUG_PutString("\n\r");
            #endif   
            strcpy(previousData, sendBuffer);
        }
    }
}


uint32_t ReceiveData(void)
{
    if(outData.writeStatus == WRITE_OK && inData.readStatus == NO_READ)
    {
        uint32_t byte;
        struct Resp recvData;
          
        while((UART_XB_SpiUartGetRxBufferSize() > 0) && ((byte=UART_XB_UartGetChar()) != 0))
        { 
            UnpackData(&recvData, (uint8_t)(byte & 0xFF));
            
            #ifdef DEBUG_PC
            //SW_UART_DEBUG_PutString("\nbyte - ");
            SW_UART_DEBUG_PutChar(byte);
            #endif
            
            if(recvData.EndPacket == 1)
            {                      
                inData.IDpacket = recvData.Seq;
                
                inData.readStatus = READ_OK;
                outData.writeStatus = NO_WRITE;
                
                /*connect network*/
                networkStatus = NETWORK_CONN;
                noConnect = 0;
                /*write data*/
                inData.countSkiers = recvData.Data3;
                //inData.unixStartTime = recvData.Data1;
                inData.ready = (recvData.Data2 & 0xFF00) >> 8;
                inData.reboot = recvData.Data2 & 0x00FF;
                /*next packet*/
                //outData.IDpacket++;
                #ifdef DEBUG_PC
                SW_UART_DEBUG_PutString("       READ DATA OKEY");   
                SW_UART_DEBUG_PutString("\n\r");
                #endif 

                return  NETWORK_CONN;  
            }
        }
        
        #ifdef DEBUG_PC
        //SW_UART_DEBUG_PutString("\nERROR READ!!!!");   
        //SW_UART_DEBUG_PutString("\n\r");
        #endif 
        
        /*tyme to respond*/
        if(noConnect++ >= NETWORK_TIMEOUT)
        {
            networkStatus = NETWORK_DISCONN;
        }
        return  NETWORK_DISCONN;
    }
    return 0;
}


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
    /*uint32_t result;
    
    if(finNoReady <= TIMEOUT_FIN_READY )
    {
        if(inData.ready == READY)
        {
            finNoReady = 0;
        }else
        {
            finNoReady++;    
        }
        
        result = READY;
    }else 
    {
        result = NO_READY;
        finNoReady = TIMEOUT_FIN_READY;
    }
    
    return result;*/
    return inData.ready;
}


uint32_t FinWriteInDB(void)
{
    uint32_t result;
    
    if(outData.newSkier == NEW_SKIER_IN_TARCK)
    {
        result = NO_WRITE;
    }else
    {
        result = WRITE_OK;
    }
    
    return result;
}
/* [] END OF FILE */
