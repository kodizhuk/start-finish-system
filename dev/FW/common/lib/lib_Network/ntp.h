#ifndef _CY_NTP_H
#define _CY_NTP_H

#include <stdint.h>
#include <stdio.h>

typedef struct 
{
	uint16_t Id;
	uint32_t Data1;
	uint16_t DataMs1;
	uint32_t CheckSum;
	uint8_t EndPacket;
}NTPResp;

enum NTP_ERRORS 
{
	NTP_PARSED_OK,   	// 0
	//WAIT_FOR_PCKT,	// 1
	NTP_BAD_ID,		// 2 | 1
	NTP_NO_FR1,			// 3 | 2
	NTP_INV_DA1,		// 6 | 5
	NTP_INV_DM1,		// 6 | 5
	NTP_NO_FR2,			// 8 | 7
	NTP_INV_CKECKSUM,	// 9 | 8
	NTP_NO_ETX,			// 10| 9

};

//
uint8_t NtpUnpackData(NTPResp *Data, uint8_t InByte);

#endif