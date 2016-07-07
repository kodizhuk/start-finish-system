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
#include <network.h>

void UART_Read(void)
{
    uint8_t ReadData;
    ReadData = UART_XB_UartGetChar();
    UART_PC_UartPutChar(ReadData);

    uint32_t ERR;
	RXSTATUS = 0;
	ERR = UnpackData(&TX_RESP, ReadData);
	if (ERR)
	{   
        char _tmp[15];
	    sprintf(_tmp, "ERROR: %d\r\n", ERR);
        UART_PC_UartPutString(_tmp);
	}
    
    if (ProcPacket(&TX_RESP, &RXSTATUS, RespBuff))
	{
        if (RXSTATUS == 10U)
        {
            char _tmprecv[50];
            PackData(_tmprecv, RespBuff, 0u); 
            UART_PC_UartPutString("Data:\r\n");
            UART_PC_UartPutString(_tmprecv);
            UART_PC_UartPutString("\r\n"); 
            UART_XB_UartPutString(_tmprecv);
        }    
		//printf("RXSTATUS: %d\n", RXSTATUS);
	}   
    UART_XB_ClearRxInterruptSource(UART_XB_INTR_RX_NOT_EMPTY);
}

void NetworkInit()
{
    void (* XB)(void);
    XB = UART_Read;
    UART_XB_SetCustomInterruptHandler(XB);
}

uint32_t CheckConnection()
{
    char buffer[BUFF_LEN];
    uint32_t Seq = 0U, OkResponse = 0U;
    uint32_t Ticks = 0U;
    
    #ifdef DEBUG_W_UART
    UART_PC_UartPutString("Sending Packet For Ready Start Module\r\n");
    #endif
    uint32_t Stat = 0;
    while((!OkResponse) && (Seq<5)){
        sprintf(szData, "%02X:%016LX%04X", RDY, (uint64_t)0u, (uint32_t)0u);
    
        PackData(buffer, szData, Seq);
    
        #ifdef DEBUG_W_UART
            UART_PC_UartPutString("Data:\r\n");
            UART_PC_UartPutString(buffer);
            UART_PC_UartPutString("\r\n");    
        #endif    
        
        UART_XB_UartPutString(buffer);
        
        Ticks = 0U;
        
        while((Ticks<50) && (!OkResponse)){
            if (RXSTATUS == 20U) 
		        {
			        UART_PC_UartPutString("READY RESPONSE RECIEVED. HAVE CONNECTION\r\n");
		            OkResponse = 1;
                    Stat = 1;
                }
            CyDelay(50);      
            Ticks++;
            //char _tmp[20];
            //sprintf(_tmp, "Ticks: %d\r\n", Ticks);
            //UART_PC_UartPutString(_tmp);
        }
        Seq++;
    }
    
    return Stat;
}


uint32_t NTP_Send()
{
    return 1u;
}

uint8_t PackData(char *buff, char* data, uint32_t Sequence)
{
    uint32_t _crc;
    char* _p;
    
    _p = data;
    
    sprintf(szSeq, "%04X", Sequence);
    
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
