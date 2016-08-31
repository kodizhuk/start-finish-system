#ifndef _CY_SVT
#define _CY_SVT
    
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <CyLib.h>

#ifdef DEBUG_W_UART
    #include <UART_PC.h>
#endif

struct Resp
{
	uint16_t Seq;
	int Command;
	uint64_t Data1;
	uint16_t Data2;
	uint16_t Data3;
	uint32_t CheckSum;
	uint8_t EndPacket;
};

enum PRO_ERRORS 
{
	PARSED_OK,   	//  0
	BAD_SEQ,		//  1
	NO_FR1,			//  2
	INV_COMM,		//  3
	NO_FR2,			//  4
	INV_DA1,		//  5
	INV_DA2,		//  6
	NO_FR3,			//  7
	INV_CKECKSUM,	//  8
	NO_ETX,			//  9
	INV_DA3,
};

uint8_t UnpackData(struct Resp *Data, uint8_t InByte);
uint8_t PackData(char *buff, uint8_t *data, uint16_t Sequence);

#endif