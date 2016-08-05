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
#include <lib_Network\network.h>

void UART_Read(void)
{
    uint8_t ReadData;
    ReadData = UART_XB_UartGetChar();
    SW_UART_PC_PutChar(ReadData);

    uint32_t ERR;
	RXSTATUS = 0;
	ERR = UnpackData(&TX_RESP, ReadData);
	if (ERR)
	{   
        char _tmp[15];
	    sprintf(_tmp, "ERROR: %u\r\n", (unsigned int)ERR);
        SW_UART_PC_PutString(_tmp);
	}
    
    if (TX_RESP.EndPacket)
	{
        char RespBuff[50];
        if (ProcPacket(&TX_RESP, &RXSTATUS, RespBuff))
    	{
            if (RXSTATUS == RESP_TO_SEND)
            {
                char _tmprecv[50];
                PackData(_tmprecv, RespBuff, 0u); 
                SW_UART_PC_PutString("Data:\r\n");
                SW_UART_PC_PutString(_tmprecv);
                SW_UART_PC_PutString("\r\n"); 
                UART_XB_UartPutString(_tmprecv);
            }    
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
    SW_UART_PC_PutString("Sending Packet For Ready Start Module\r\n");
    #endif
    uint32_t Stat = 0;
    while((!OkResponse) && (Seq<5)){
        char szData[50];
        
        sprintf(szData, "%02X:%016LX%04X", RDY, (uint64_t)0u, (uint16_t)0u);

        PackData(buffer, szData, Seq);
    
        #ifdef DEBUG_W_UART
            SW_UART_PC_PutString("Data:\r\n");
            SW_UART_PC_PutString(buffer);
            SW_UART_PC_PutString("\r\n");    
        #endif    
        
        UART_XB_UartPutString(buffer);
        
        Ticks = 0U;
        
        while((Ticks<50) && (!OkResponse)){
            if (RXSTATUS == RESP_ALL_OK) 
		        {
			        SW_UART_PC_PutString("READY RESPONSE RECIEVED. HAVE CONNECTION\r\n");
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


uint8_t PackData(char *buff, char *data, uint32_t Sequence)
{
    uint32_t _crc;
    char * _p;
    char szSeq[20];
    char szCheckSum[20];
    
    _p = data;
    
    sprintf(szSeq, "%04X", (uint16_t)Sequence);
    
    _crc = crc32_reset();
    _crc = crc32_calc_block((uint8_t *)"A", 1, _crc);
    _crc = crc32_calc_block((uint8_t *)_p, strlen(_p), _crc);
    _crc = crc32_calc_block((uint8_t *)"F", 1, _crc);
    _crc = crc32_final(_crc);
    
    sprintf(szCheckSum, "%08X", _crc);
    
    strcpy(buff, "<");
    strcat(buff, szSeq);
    strcat(buff, FRM0);
    strcat(buff, _p);
    strcat(buff, FRM1);    
    strcat(buff, szCheckSum);
    strcat(buff, ">");
    
    return strlen(buff);
}


/* [] END OF FILE */
