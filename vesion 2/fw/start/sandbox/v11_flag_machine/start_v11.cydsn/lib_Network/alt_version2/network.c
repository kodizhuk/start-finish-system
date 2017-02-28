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


//void UART_XB_SPI_UART_ISR_ExitCallback(void)
void UART_Read()
{
    uint8_t ReadData;
    ReadData = UART_XB_UartGetChar();
    //UART_PC_PutChar(ReadData);

    uint32_t ERR;
	RXSTATUS = 0;
	ERR = UnpackData(&TX_RESP, ReadData);
	if (ERR)
	{   
        char _tmp[15];
	    sprintf(_tmp, "ERROR: %u\r\n",  (unsigned int)ERR);
        UART_PC_PutString(_tmp);
	}
    
    if (TX_RESP.EndPacket)
	{
        uint8_t RespBuff[50];
        if (ProcPacket(&TX_RESP, &RXSTATUS, RespBuff))
    	{
            if (RXSTATUS == RESP_TO_SEND)
            {
                char _tmprecv[50];
                PackData(_tmprecv, RespBuff, 0u); 
                //UART_PC_PutString("Data:\r\n");
                //UART_PC_PutString(_tmprecv);
                //UART_PC_PutString("\r\n"); 
                UART_XB_UartPutString(_tmprecv);
            }    
    		//printf("RXSTATUS: %d\n", RXSTATUS);
    	}   
    }
    UART_XB_ClearRxInterruptSource(UART_XB_INTR_RX_NOT_EMPTY);
}

void NetworkInit()
{
    UART_XB_Start();
    void (* XB)(void);
    XB = UART_Read;
    UART_XB_SetCustomInterruptHandler(XB);
}

uint32_t CheckConnection()
{
    char buffer[BUFF_LEN];
    uint32_t Seq = 0U, OkResponse = 0U;
    uint32_t Ticks = 0U;
    RXSTATUS = 0;
    
    #ifdef DEBUG_W_UART
    UART_PC_PutString("Sending Packet For Ready Start Module\r\n");
    #endif
    uint32_t Stat = 0;
    while((!OkResponse) && (Seq<5)){
        char szData[50];
        sprintf(szData, "%02X:%016LX%04X", RDY, (uint64_t)0u, (uint16_t)0u);
    
        PackData(buffer, (uint8_t *)szData, Seq);
    
        #ifdef DEBUG_W_UART
            UART_PC_PutString("Data:\r\n");
            UART_PC_PutString(buffer);
            UART_PC_PutString("\r\n");    
        #endif    
        
        UART_XB_UartPutString(buffer);
        
        Ticks = 0U;
        
        while((Ticks<50) && (!OkResponse)){
            if (RXSTATUS == RESP_ALL_OK) 
		    {
			    UART_PC_PutString("READY RESPONSE RECIEVED. HAVE CONNECTION\r\n");
		        OkResponse = 1;
                Stat = 1;
            }
            CyDelay(50);      
            Ticks++;
        }
        Seq++;
    }
    return Stat;
}

uint32_t CheckFinishReady()
{
    char buffer[BUFF_LEN];
    uint32_t Seq = 0U, OkResponse = 0U;
    uint32_t Ticks = 0U;
    RXSTATUS = 0;
    
    #ifdef DEBUG_W_UART
    UART_PC_PutString("Sending Packet for Checking ReadyFinish\r\n");
    #endif
    uint32_t Stat = 50;
    
    while((!OkResponse) && (Seq<5)){
        char szData[50];
        sprintf(szData, "%02X:%016LX%04X", FIN_RDY, (uint64_t)0u, (uint16_t)0u);
    
        PackData(buffer, szData, Seq);
    
        #ifdef DEBUG_W_UART
            UART_PC_PutString("Data:\r\n");
            UART_PC_PutString(buffer);
            UART_PC_PutString("\r\n");    
        #endif    
        
        UART_XB_UartPutString(buffer);
        
        Ticks = 0U;
        
        while((Ticks<10) && (!OkResponse)){
            if (RXSTATUS == RESP_ALL_OK) 
		    {    
		        OkResponse = 1;
                if (TX_RESP.Data1 == 0x1u)
                {
                    UART_PC_PutString("Finish Not Ready: OPEN GATE\r\n");
                    Stat = 30u;
                }
                else if (TX_RESP.Data1 == 0x2u)
                {
                    UART_PC_PutString("Finish Not Ready: MAX SKIERS ON WAY ALREADY GO\r\n");
                    Stat = 40u;
                }
                else
                {
                    UART_PC_PutString("FINISH RDY. CAN GO\r\n");
                    Stat = TX_RESP.Data2;
                }
            }
            CyDelay(50);      
            Ticks++;
        }
        Seq++;
    }
    return Stat;
}

uint32_t SendSkierSrart(uint64_t UnixTimeStart, uint16_t MillsTimeStart)
{
    char buffer[BUFF_LEN];
    uint32_t Seq = 0U, OkResponse = 0U;
    uint32_t Ticks = 0U;
    RXSTATUS = 0;
    
    #ifdef DEBUG_W_UART
    UART_PC_PutString("Sending Packet for Write Starttime to DB\r\n");
    #endif
    uint32_t Stat = 0;
    
    while((!OkResponse) && (Seq<15)){
        char szData[100];
        uint64_t TmpUnixTime;
        uint32_t UnixHigh, UnixLow;
        TmpUnixTime = UnixTimeStart;
        UnixHigh = (TmpUnixTime & 0xFFFFFFFF00000000) >> 32;
        UnixLow = TmpUnixTime & 0x00000000FFFFFFFF;
        sprintf(szData, "%02X:%08X%08X%04X", WRITE_START_TIME, UnixHigh, UnixLow, (uint16_t)MillsTimeStart);
    
        PackData(buffer, szData, Seq);
    
        #ifdef DEBUG_W_UART
            UART_PC_PutString("Data:\r\n");
            UART_PC_PutString(buffer);
            UART_PC_PutString("\r\n");    
        #endif    
        
        UART_XB_UartPutString(buffer);
        
        Ticks = 0U;
        
        while((Ticks<50) && (!OkResponse)){
            if (RXSTATUS == RESP_ALL_OK) 
		    {    
		        OkResponse = 1;
                Stat = 1;
            }
            CyDelay(50);      
            Ticks++;
        }
        Seq++;
    }
    return Stat;
}


uint32_t RTC_Sync()
{
    char buffer[BUFF_LEN];
    uint32_t Seq = 0U, OkResponse = 0U;
    uint32_t Ticks = 0U;
    RXSTATUS = 0;
    
    #ifdef DEBUG_W_UART
    UART_PC_PutString("Sending Packet for ntp sync\r\n");
    #endif
    uint32_t Stat = 0;
    
    while((!OkResponse) && (Seq<5)){
        char szData[100];
        uint64_t ReqUnixTime;
        uint32_t UnixHigh, UnixLow;
        uint32_t ReqMills = RTCgetRecentMs();
        ReqUnixTime = RTC_1_GetUnixTime();
        UnixHigh = (ReqUnixTime & 0xFFFFFFFF00000000) >> 32;
        UnixLow = ReqUnixTime & 0x00000000FFFFFFFF;
        sprintf(szData, "%02X:%08X%08X%04X", GTM, UnixHigh, UnixLow, (uint16_t)ReqMills);
    
        PackData(buffer, szData, Seq);
    
        #ifdef DEBUG_W_UART
            UART_PC_PutString("Data:\r\n");
            UART_PC_PutString(buffer);
            UART_PC_PutString("\r\n");    
        #endif    
        
        UART_XB_UartPutString(buffer);
        
        Ticks = 0U;
        
        while((Ticks<50u*50u) && (!OkResponse)){
            if (RXSTATUS == RESP_ALL_OK) 
		    {    
                UART_PC_PutString("ALL OK : NTP\r\n");
                OkResponse = 1;
                if (TX_RESP.Data1 != 0x0u)
                {
                    uint64_t ServerUnix = TX_RESP.Data1;
                    uint16_t ServerMills = TX_RESP.Data2;
                    uint64_t UnixResp = RTCGetUnixTime();
                    uint16_t MillsResp = RTCgetRecentMs();
                    uint16_t TmpMills = (MillsResp - ReqMills) * 16/ 26;
                    uint64_t TmpUnix = (UnixResp - ReqUnixTime)* 4/ 6;
                    if (TmpMills >= 1000u)
                    {
                        TmpMills = 0u - TmpMills;
                        TmpUnix--;
                    }
                    uint64_t EndUnix = ServerUnix + TmpUnix;
                    uint16_t EndMills = ServerMills + TmpMills;
                    if (EndMills >= 1000u)
                    {
                        EndUnix++;
                        EndMills-=1000u;
                    }
                    RTCSetRecentMs(EndMills);                    
                    RTCSetUnixTime(EndUnix);                                   
                    Stat = 1;
                }
                UART_PC_PutString("EXITED : NTP\r\n");
            }
            //CyDelay(50);      
            Ticks++;
        }
        Seq++;
    }
    return Stat;

}

/* [] END OF FILE */
