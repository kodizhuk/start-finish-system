#include "ntp.h"

enum NTP_STATES 
{
	NTP_WAIT_STX,
	NTP_READ_ID,
	NTP_READ_FR1,
	NTP_READ_DA1,
	NTP_READ_DM1,	
	NTP_READ_DA2,
	NTP_READ_DM2,
	NTP_READ_FR2,
	NTP_READ_CHS,
	NTP_READ_ETX
};

#define NTP_LEN_ID  4
#define NTP_LEN_DA1 8
#define NTP_LEN_DM1 3
#define NTP_LEN_DA2 8
#define NTP_LEN_DM2 3
#define NTP_LEN_CHS 8

#define HALF_BYTE 4

#define NTP_STX '<'
#define NTP_ETX '>'
#define NTP_FR1 '!'
#define NTP_FR2 '@'

uint8_t NtpLenD1, NtpLenMsD1, NtpLenD2, NtpLenMsD2, NtpLenId, NtpLenChS;

uint8_t NtpDecodeByte(uint8_t Inp);
uint8_t NtpCheckSymb(uint8_t Inp);
void 	NtpResetPacket(NtpResp *Data);

uint8_t NTP_STATE = 0;

uint8_t NtpUnpackData(NtpResp *Data, uint8_t InByte)
{
	uint8_t RecvB = InByte;
	uint32_t ERR_CODE = 0;
	InByte = NtpDecodeByte(InByte);

	//printf("State: %X -- %d\n", InByte, NTP_STATE);
	switch(NTP_STATE){
		case NTP_WAIT_STX: 
		{
			NtpResetPacket(Data);
			NtpLenId = 0;
			NtpLenChS = 0;
			NtpLenD1 = 0;
            NtpLenMsD1 = 0;
            NtpLenMsD2 = 0;
			NtpLenD2 = 0;
			if (InByte == NTP_STX)
			{
				NTP_STATE = NTP_READ_ID;
			}
			else 
			{
				//ERR_CODE = WAIT_FOR_PCKT;
			}
			break;
		}
		
		case NTP_READ_ID:
		{
			if(NtpCheckSymb(InByte))
			{
				Data->Id |= InByte;
				NtpLenId++;
				if (NtpLenId == NTP_LEN_ID)
				{
					NTP_STATE = NTP_READ_FR1;
				}
				else
				{
					Data->Id = Data->Id << HALF_BYTE;
				}
			}
			else{
				NTP_STATE = NTP_WAIT_STX;
				ERR_CODE = NTP_BAD_ID;
			}
			break;
		}
		
		case NTP_READ_FR1:
		{
			if (InByte == NTP_FR1)
			{
				NTP_STATE = NTP_READ_DA1;
			}
			else
			{
				NtpResetPacket(Data);
				ERR_CODE = NTP_NO_FR1;
				NTP_STATE = NTP_WAIT_STX;
			}
			break;
		}
		case NTP_READ_DA1:
		{

			if(NtpCheckSymb(InByte))
			{
				Data->Data1 |= InByte;
				NtpLenD1++;
				if (NtpLenD1 == NTP_LEN_DA1)
				{
					NTP_STATE = NTP_READ_DM1;
				}
				else
				{
					Data->Data1 = Data->Data1 << HALF_BYTE;
				}
			}
			else{
				NtpResetPacket(Data);
				ERR_CODE = NTP_INV_DA1;
				NTP_STATE = NTP_WAIT_STX;
			}
			break;
		}
		case NTP_READ_DM1:
		{

			if(NtpCheckSymb(InByte))
			{
				Data->DataMs1 |= InByte;
				NtpLenMsD1++;
				if (NtpLenMsD1 == NTP_LEN_DM1)
				{
					NTP_STATE = NTP_READ_DA2;
				}
				else
				{
					Data->DataMs1 = Data->DataMs1 << HALF_BYTE;
				}
			}
			else{
				NtpResetPacket(Data);
				ERR_CODE = NTP_INV_DM1;
				NTP_STATE = NTP_WAIT_STX;
			}
			break;
		}
		case NTP_READ_DA2:
		{			
			if(NtpCheckSymb(InByte))
			{
				//printf("DATA2: %X -- %X\n", InByte, Data->Data2);
				Data->Data2 |= InByte;
				NtpLenD2++;
				if (NtpLenD2 == NTP_LEN_DA2)
				{
					NTP_STATE = NTP_READ_DM2;
				}
				else
				{
					Data->Data2 = Data->Data2 << HALF_BYTE;
				}
			}
			else{
				NtpResetPacket(Data);
				ERR_CODE = NTP_INV_DA2;
				NTP_STATE = NTP_WAIT_STX;
			}
			break;
		}
		case NTP_READ_DM2:
		{

			if(NtpCheckSymb(InByte))
			{
				Data->DataMs2 |= InByte;
				NtpLenMsD2++;
				if (NtpLenMsD2 == NTP_LEN_DM2)
				{
					NTP_STATE = NTP_READ_FR2;
				}
				else
				{
					Data->DataMs2 = Data->DataMs2 << HALF_BYTE;
				}
			}
			else{
				NtpResetPacket(Data);
				ERR_CODE = NTP_INV_DM2;
				NTP_STATE = NTP_WAIT_STX;
			}
			break;
		}
		case NTP_READ_FR2:
		{
			if (InByte == NTP_FR2)
			{
				NTP_STATE = NTP_READ_CHS;
			}
			else
			{
				NtpResetPacket(Data);
				ERR_CODE = NTP_NO_FR2;
				NTP_STATE = NTP_WAIT_STX;
			}
			break;
		}

		case NTP_READ_CHS:
		{
			if(NtpCheckSymb(InByte))
			{
				Data->CheckSum |= InByte;
				NtpLenChS++;
				if (NtpLenChS == NTP_LEN_CHS)
				{
					NTP_STATE = NTP_READ_ETX;
				}
				else
				{
					Data->CheckSum = Data->CheckSum << HALF_BYTE;
				}
			}
			else
			{
				NtpResetPacket(Data);
				ERR_CODE = NTP_INV_CKECKSUM;
				NTP_STATE = NTP_WAIT_STX;
			}
			break;
		}
		case NTP_READ_ETX:
		{
			if (InByte == NTP_ETX)
			{
				Data->EndPacket = 1;
				ERR_CODE = NTP_PARSED_OK;

			}
			else{
				ERR_CODE = NTP_NO_ETX;
				NtpResetPacket(Data);
			}
			NTP_STATE = NTP_WAIT_STX;
			break;
		}
	}
	
	/*if (Data->EndPacket)
	{
		char tempbuff[40];
		sprintf(tempbuff, "%04X:%08X_%03X %08X_%03X@%08X", Data->Id, Data->Data1, Data->DataMs1, Data->Data2, Data->DataMs2, Data->CheckSum);
		printf("ID + Data1: %s\n", tempbuff);
	}*/
	
	return ERR_CODE;

}

uint8_t NtpDecodeByte(uint8_t Inp)
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

uint8_t NtpCheckSymb(uint8_t Inp)
{
	uint8_t Val = 1;

	if ((Inp > 0xF) || (Inp < 0x0))
	{
		Val = 0;
	}
	return Val;
}

void NtpResetPacket(NtpResp *Data)
{
	Data->Id = 0;
	Data->Data1 = 0;
    Data->DataMs1 = 0;
	Data->Data2 = 0;
	Data->DataMs2 = 0;
    Data->CheckSum = 0;
	Data->EndPacket = 0;
}
