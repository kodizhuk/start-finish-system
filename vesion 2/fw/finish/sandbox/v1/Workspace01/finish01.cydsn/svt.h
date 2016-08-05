#include <stdint.h>
#include <stdio.h>

#ifdef DEBUG_W_UART
    #include <UART_PC.h>
    #include <UART_PC_SPI_UART.h>
#endif

struct Resp
{
	uint16_t Seq;
	int Command;
	uint64_t Data1;
	uint8_t Data2;
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
	READ_FR3,
	READ_CHS,
	READ_ETX
};

enum PRO_ERRORS 
{
	PARSED_OK,   	// 0
	//WAIT_FOR_PCKT,	// 1
	BAD_SEQ,		// 2 | 1
	NO_FR1,			// 3 | 2
	INV_COMM,		// 4 | 3
	NO_FR2,			// 5 | 4
	INV_DA1,		// 6 | 5
	INV_DA2,		// 7 | 6
	NO_FR3,			// 8 | 7
	INV_CKECKSUM,	// 9 | 8
	NO_ETX,			// 10| 9

};

#define LEN_SEQ 4
#define LEN_COM 2
#define LEN_DA1 16
#define LEN_DA2 4
#define LEN_CHS 8

#define HALF_BYTE 4

#define STX '<'
#define ETX '>'
#define FR1 '!'
#define FR2 ':'
#define FR3 '@'

uint8_t PROTO_STATE, LenD1, LenD2, LenSeq, LenChS, LenC;


//
uint8_t UnpackData(struct Resp *Data, uint8_t InByte);
uint8_t DecodeByte(uint8_t Inp);
uint8_t CheckSymb(uint8_t Inp);
void 	ResetPacket(struct Resp *Data);
uint32_t ProcPacket(struct Resp *Data, uint8_t *RX,  uint8_t *buff);