#include "svt.h"


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
    				Data->EndPacket = 1;
    				ERR_CODE = PARSED_OK;

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
	uint8_t Res;
	if (Data->EndPacket)
	{
		UART_PC_UartPutString("Packet Recieved\r\n");
		switch (Data->Command)
		{
			case 0x1A:
			{
				UART_PC_UartPutString("Packet Ok Sended\r\n");
				sprintf(buff, "%02X:%016X%04X", (0x20), 0x0, 0x0);
				UART_PC_UartPutString("Data Sended: ");
                UART_PC_UartPutString(buff);
                UART_PC_UartPutString("\r\n");
				*RX = 10U;
				Res = 1;
				break;
			}
			case 0x20:
			{
				UART_PC_UartPutString("Packet Ok Recieved\r\n");
				*RX = 20U;
				Res = 1;
				break;
			}
		}
	}
	else{
		Res = 0;
	}
	return Res;
}