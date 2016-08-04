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
    SW_UART_DEBUG_PutString("\n\nI READY\n\n");
    #endif
    
    inData.readStatus = NO_READ;
    outData.writeStatus = WRITE_OK;
    networkStatus = NETWORK_DISCONN;   
}

void AppDelay(uint32_t delayMs)
{
    uint32_t runTime;
    
    if(delayMs < MIN_DELAYMS)
    {
        CyDelay(delayMs);
    }else
    {
        AppDelay_WriteCounter(131071);
        uint32_t counter = AppDelay_ReadCounter();
        //AppDelay_Wakeup();
        //AppDelay_Enable();
        AppDelay_Start();
        
        if((delayMs - runTime) > MIN_DELAYMS)
        {
            /*user function*/      
            if(outData.writeStatus == NO_WRITE && inData.readStatus == READ_OK)
            {
                SendData();           
            }
        
            if(outData.writeStatus == WRITE_OK && inData.readStatus == NO_READ)
            {
                ReceiveData();
            
                #ifdef DEBUG_PC
                //outData.writeStatus = READ_OK;
                #endif
                
            }
            CyDelay(50);
            uint32_t period = AppDelay_ReadPeriod();;
            counter = AppDelay_ReadCounter();
            runTime = (period -  counter)/32.768;
        }
        AppDelay_Stop();
        
        #ifdef DEBUG_PC
        char buffer[100];
        sprintf(buffer,"time send data %u\n\r", (runTime));
        SW_UART_DEBUG_PutString(buffer);
        #endif
        
        /*tyme to respond*/
        if(numAttemps++ >5)
        {
            numAttemps=0;
            if(noConnect++ == 5)
            {
                networkStatus = NETWORK_DISCONN;
            }
        }
        CyDelay(delayMs - runTime);
    }
    

}

void SendData(void)
{
    char sendBuffer[DATA_BUFFER];
    char sendData[DATA_BUFFER];
    int i;
    
    /*pack data*/
    sprintf(sendData,"%02X:%08X%08X%04X%02X",
            0u,
            (uint32_t)((outData.unixStartTime & 0xFFFFFFFF00000000) >> 32), 
            (uint32_t)(outData.unixStartTime & 0x00000000FFFFFFFF), 
            outData.startMsTime, 
            outData.gateStatus);
    
    PackData(sendBuffer, (uint8_t *)sendData, inData.IDpacket);
    UART_XB_UartPutString(sendBuffer);
    outData.writeStatus = WRITE_OK;
    inData.readStatus = NO_READ;
    #ifdef DEBUG_PC
    SW_UART_DEBUG_PutString("out data - "); 
    SW_UART_DEBUG_PutString(sendBuffer);   
    SW_UART_DEBUG_PutString("\n\r");
    #endif   
}


uint32_t ReceiveData(void)
{
    uint32_t result = 0;
    int i;
    uint8_t byte;
    struct Resp recvData;
      
    while((byte=UART_XB_UartGetChar()) != 0)
    { 
        result = UnpackData(&recvData, (uint8_t)(byte & 0xFF));
        
        #ifdef DEBUG_PC
        SW_UART_DEBUG_PutChar(byte);
        #endif
        if(recvData.EndPacket == 1)
        {
            inData.IDpacket = recvData.Seq;
            
            /*id packet ok*/
            if(inData.IDpacket == inData.IDpacket)
            {
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
                outData.IDpacket++;
                #ifdef DEBUG_PC
                SW_UART_DEBUG_PutString("       READ DATA OKEY");   
                SW_UART_DEBUG_PutString("\n\r");
                #endif 
            }  
            return  NO_ERROR;  
        }
    }
    
    #ifdef DEBUG_PC
    SW_UART_DEBUG_PutString("ERROR READ!!!!");   
    SW_UART_DEBUG_PutString("\n\r");
    #endif 
    return  ERROR;
}


uint32_t NetworkStatus(void)
{
    return networkStatus;
}
/* [] END OF FILE */
