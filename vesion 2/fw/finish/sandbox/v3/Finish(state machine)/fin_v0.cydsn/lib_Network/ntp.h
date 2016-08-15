#ifndef _CY_NTP_H
#define _CY_NTP_H

#include <stdint.h>
#include <stdio.h>

typedef struct
{
	uint16_t Id;
	uint32_t Data1;
	uint16_t DataMs1;
	uint16_t DataMs2;
	uint32_t Data2;
	uint32_t CheckSum;
	uint8_t EndPacket;
}NtpResp;

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

enum NTP_ERRORS 
{
	NTP_PARSED_OK,   	// 0
	//WAIT_FOR_PCKT,	// 1
	NTP_BAD_ID,		// 2 | 1
	NTP_NO_FR1,			// 3 | 2
	NTP_INV_DA1,		// 6 | 5
	NTP_INV_DM1,		// 6 | 5
	NTP_INV_DA2,		// 7 | 6
	NTP_INV_DM2,		// 6 | 5
	NTP_NO_FR2,			// 8 | 7
	NTP_INV_CKECKSUM,	// 9 | 8
	NTP_NO_ETX,			// 10| 9

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


//
uint8_t NtpUnpackData(NtpResp *Data, uint8_t InByte);
uint8_t NtpDecodeByte(uint8_t Inp);
uint8_t NtpCheckSymb(uint8_t Inp);
void 	NtpResetPacket(NtpResp *Data);

#endif