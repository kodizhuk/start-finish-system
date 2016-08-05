#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "crc32.h"
#include <CyLib.h>

struct Resp
{
	uint16_t Seq;
	int Command;
	uint64_t Data1;
	uint16_t Data2;
	uint8_t Data3;
	uint32_t CheckSum;
	uint8_t EndPacket;
};

enum PRO_STATES 
{
	WAIT_STX,
	READ_SQ,
	READ_FR1,
	READ_COM,
	READ_FR2,
	READ_DA1,
	READ_DA2,
	READ_DA3,
	READ_FR3,
	READ_CHS,
	READ_ETX
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

#define LEN_SEQ 4
#define LEN_COM 2
#define LEN_DA1 16
#define LEN_DA2 4
#define LEN_DA3 2
#define LEN_CHS 8

#define HALF_BYTE 4

#define STX '<'
#define ETX '>'
#define FR1 '!'
#define FR2 ':'
#define FR3 '@'

#define STX_S                   ("<")
#define FRM0                    ("!")
#define FRM1                    ("@")
#define FRM2                    ("#")
#define ETX_S                   (">")

uint8_t PROTO_STATE, LenD1, LenD2, LenD3, LenSeq, LenChS, LenC;


//
uint8_t UnpackData(struct Resp *Data, uint8_t InByte);
uint8_t DecodeByte(uint8_t Inp);
uint8_t CheckSymb(uint8_t Inp);
void 	ResetPacket(struct Resp *Data);
uint8_t PackData(char *buff, uint8_t *data, uint32_t Sequence);