#include "lib_Network\svt.h"


uint8_t UnpackData(struct Resp *Data, uint8_t InByte)
{
	uint32_t ERR_CODE = 0;
	InByte = DecodeByte(InByte);
    if (InByte == STX)
	{
	    PROTO_STATE = READ_SQ;
		ResetPacket(Data);
		LenSeq = 0;
		LenC = 0;
		LenChS = 0;
		LenD1 = 0;
		LenD2 = 0;
    }
    else
    {
    	switch(PROTO_STATE){
    		case READ_SQ:
    		{
    			if(CheckSymb(InByte))
    			{
    				Data->Seq |= InByte;
    				LenSeq++;
    				if (LenSeq == LEN_SEQ)
    				{
    					PROTO_STATE = READ_FR1;
    				}
    				else
    				{
    					Data->Seq = Data->Seq << HALF_BYTE;
    				}
    			}
    			else{
    				PROTO_STATE = WAIT_STX;
    				ERR_CODE = BAD_SEQ;
    			}
    			break;
    		}  		
    		case READ_FR1:
    		{
    			if (InByte == FR1)
    			{
    				PROTO_STATE = READ_COM;
    			}
    			else
    			{
    				ResetPacket(Data);
    				ERR_CODE = NO_FR1;
    				PROTO_STATE = WAIT_STX;
    			}
    			break;
    		}
    		case READ_COM:
    		{
    			//printf("InByte Command: %02X\n", InByte);
    			if(CheckSymb(InByte))
    			{
    				Data->Command |= InByte;
    				LenC ++;
    				//printf("LenC Command: %d\n", LenC);
    				if (LenC == LEN_COM)
    				{
    					PROTO_STATE = READ_FR2;
    				}
    				else
    				{
    					Data->Command = Data->Command << HALF_BYTE;
    				}
    			}
    			else
    			{
    				ResetPacket(Data);
    				PROTO_STATE = WAIT_STX;
    				ERR_CODE = INV_COMM;
    			}
    			break;
    		}
    		case READ_FR2:
    		{
    			if (InByte == FR2)
    			{
    				PROTO_STATE = READ_DA1;
    			}
    			else
    			{
    				ResetPacket(Data);
    				ERR_CODE = NO_FR2;
    				PROTO_STATE = WAIT_STX;
    			}
    			break;
    		}
    		case READ_DA1:
    		{

    			if(CheckSymb(InByte))
    			{
    				Data->Data1 |= InByte;
    				LenD1++;
    				if (LenD1 == LEN_DA1)
    				{
    					PROTO_STATE = READ_DA2;
    				}
    				else
    				{
    					Data->Data1 = Data->Data1 << HALF_BYTE;
    				}
    			}
    			else{
    				ResetPacket(Data);
    				ERR_CODE = INV_DA1;
    				PROTO_STATE = WAIT_STX;
    			}
    			break;
    		}
    		case READ_DA2:
    		{
    			

    			if(CheckSymb(InByte))
    			{
    				Data->Data2 |= InByte;
    				LenD2++;
    				if (LenD2 == LEN_DA2)
    				{
    					PROTO_STATE = READ_FR3;
    				}
    				else
    				{
    					Data->Data2 = Data->Data2 << HALF_BYTE;
    				}
    			}
    			else{
    				ResetPacket(Data);
    				ERR_CODE = INV_DA2;
    				PROTO_STATE = WAIT_STX;
    			}
    			break;
    		}
    		case READ_FR3:
    		{
    			if (InByte == FR3)
    			{
    				PROTO_STATE = READ_CHS;
    			}
    			else
    			{
    				ResetPacket(Data);
    				ERR_CODE = NO_FR3;
    				PROTO_STATE = WAIT_STX;
    			}
    			break;
    		}
    		case READ_CHS:
    		{
    			if(CheckSymb(InByte))
    			{
    				Data->CheckSum |= InByte;
    				LenChS++;
    				if (LenChS == LEN_CHS)
    				{
    					PROTO_STATE = READ_ETX;
    				}
    				else
    				{
    					Data->CheckSum = Data->CheckSum << HALF_BYTE;
    				}
    			}
    			else
    			{
    				ResetPacket(Data);
    				ERR_CODE = INV_CKECKSUM;
    				PROTO_STATE = WAIT_STX;
    			}
    			break;
    		}
    		case READ_ETX:
    		{
    			if (InByte == ETX)
    			{
                    uint32_t _tmpcrc;
                    char _tmpdata[40];
                    sprintf(_tmpdata, "%02X:%016LX%04X", Data->Command, Data->Data1, Data->Data2);
                    _tmpcrc = crc32_reset();
                    _tmpcrc = crc32_calc_block((uint8_t *)"A", 1, _tmpcrc);
                    _tmpcrc = crc32_calc_block((uint8_t *)_tmpdata, sizeof(_tmpdata), _tmpcrc);
    				_tmpcrc = crc32_calc_block((uint8_t *)"F", 1, _tmpcrc);
                    _tmpcrc = crc32_final(_tmpcrc);
                    if (_tmpcrc != Data->CheckSum)
                    {
                        Data->EndPacket = 1;
    				    ERR_CODE = PARSED_OK;
                    }
                    else
                    {
                        Data->EndPacket = 0;
                        ERR_CODE = 10;
                    }
    			}
    			else{
    				ERR_CODE = NO_ETX;
    				ResetPacket(Data);
    			}
    			PROTO_STATE = WAIT_STX;
    			break;
    		}
            default: 
            {
                ResetPacket(Data);
            }
    	}
    } 
    return ERR_CODE;
}

uint8_t DecodeByte(uint8_t Inp)
{
	if ((Inp >= 'A') && (Inp <= 'F'))
	{
		Inp -= 0x37;
	}
	else if ((Inp >= '0') && (Inp <= '9')){
		Inp -= 0x30;
	}
	return Inp;
}

uint8_t CheckSymb(uint8_t Inp)
{
	uint8_t Val = 1;

	if ((Inp > 0xF) || (Inp < 0x0))
	{
		Val = 0;
	}
	return Val;
}

void ResetPacket(struct Resp *Data)
{
	Data->Seq = 0;
	Data->Command = 0;
	Data->Data1 = 0;
	Data->Data2 = 0;
	Data->CheckSum = 0;
	Data->EndPacket = 0;
}

uint32_t ProcPacket(struct Resp *Data, uint8_t *RX, uint8_t *buff)
{
	uint8_t Res = 0;
		UART_PC_PutString("Packet Recieved\r\n");
		switch (Data->Command)
		{
			case RDY:
			{
				UART_PC_PutString("Packet Ok Sended\r\n");
				sprintf(buff, "%02X:%016X%04X", (0x20), 0x0, 0x0);
				UART_PC_PutString("Data Sended: ");
                UART_PC_PutString(buff);
                UART_PC_PutString("\r\n");
				*RX = RESP_TO_SEND;
				Res = 1;
				break;
			}
			case OKR:
			{
				UART_PC_PutString("Packet Ok Recieved\r\n");
				*RX = RESP_ALL_OK;
				Res = 1;
				break;
			}
            case GET_TIME_RESP:
			{
				UART_PC_PutString("Packet NTP Recieved\r\n");
				*RX = RESP_ALL_OK;
				Res = 1;
				break;
			}
            case RDY_TO_START_REQ:
            {
                UART_PC_PutString("Packet Rdy Recieved\r\n");
                *RX = RESP_ALL_OK;
				Res = 1;
				break;
            }
		}

	return Res;
}