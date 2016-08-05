#include <stdint.h>
#include <stdio.h>
#include "gate.h"
#include "crc32.h"
#include "lib_DB\database.h"
#include "lib_RTC\RTC_WDT.h"

#ifdef DEBUG_W_UART
    #include <SW_UART_PC.h>
    //#include <UART_PC_SPI_UART.h>
#endif

#define RDY                    (0x1A) // Request: Ready = Has Connection
#define FIN_RDY_REQ            (0x1B) // Request: Ready = Gate closed & No skiers on way
#define GTM                    (0x1C) // Request: Get Finish Time for Sync
#define WRITE_START_TIME       (0x1D) // Request: After start need write DB

#define OKR                    (0x20) // Responce: Has Connection
#define RDY_RESP               (0x21) // Responce: Ready or not (gate closed etc)
#define GET_TIME_RESP          (0x22) // Responce: Fimish Time back to Start

#define RESP_TO_SEND            (10U) // Request: Packet need to send
#define RESP_ALL_OK             (20U) // Resonce: Packet sended to this device

struct Resp
{
	uint16_t Seq;
	int Command;
	uint64_t Data1;
	uint8_t Data2;
	uint32_t CheckSum;
	uint8_t EndPacket;
};

enum SVT_PRO_STATES 
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

enum SVT_PRO_ERRORS 
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