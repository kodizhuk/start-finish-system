#ifndef _NETWORK_H
    #define _NETWORK_H
   
#include <UART_XB.h>
#include <UART_XB_SPI_UART.h>
#include <project.h>
#include <stdio.h>
#include "lib_Network\svt.h"
#include "lib_DB\database.h"
#include "lib_RTC\RTC_WDT.h"
#include "lib_Network\ntp.h"

#define DEBUG_PC
#ifdef DEBUG_PC
    #include <SW_UART_DEBUG.h>
#endif


#define READ_OK     1
#define NO_READ     0
#define WRITE_OK     1
#define NO_WRITE     0
#define FIN_READY       1
#define FIN_NO_READY    0

#define NEW_SKIER_IN_TARCK   1

/*size buffer*/
#define DATA_BUFFER   50
#define RX_BUFFER   

#define ADRESS_READY        8
#define ADRESS_REBOOT       9
#define ADRESS_COUNT_SK     10

/*network status*/
#define NETWORK_CONN        1
#define NETWORK_DISCONN     0

#define NETWORK_TIMEOUT     30

/*for NTP protocol*/
#define NUM_TRY_SYNC        10
#define NUM_CONNECT_ATTEMPS 20

#define TIME_SYNC_ERR       1
#define TIME_SYNC_OK        0
/*segment time*/
#define T1                  0
#define T2                  1
#define T3                  2
#define T4                  3

typedef struct
{
    /*data to transmit*/
    uint8_t IDpacket;    
    uint8_t ready;          /*flag readu finish*/
    uint8_t reboot;         /*flag finish reboot*/
    uint8_t countSkiers;
    
    uint64_t tmpTime;
    uint16_t tmpMsTime;
    uint8_t writeStatus;    /*flag transmitt data*/
}FinishData;

typedef struct
{
    /*data to receive*/
    uint8_t IDpacket;
    uint64_t unixStartTime;
    uint16_t startMsTime;
    uint8_t newSkier;
    
    uint8_t readStatus;     /*flag successful read data in start*/
}StartData;

FinishData outData ;
StartData inData;



uint32_t numAttemps,noConnect, networkStatus;


void InitNetwork(void);
uint32_t NetworkStatus(void);
void SendFinStatus(uint32_t ready);
void SendData(void);
uint32_t ReceiveData(void);

/*NTP protocol sync*/
uint32_t NTPsync(void);
static void NTPsendTime(uint32_t unixTime1,uint16_t millis1, uint32_t ID);
static uint32_t NTPreceiveTime(uint32_t *unixTime2,uint16_t *millis2, uint32_t *unixTime3, uint16_t *millis3, uint32_t *IDreceive);
static void NTPsetTimeToStart(uint32_t unixTime4,uint16_t millis4,  uint32_t ID);

#endif
/* [] END OF FILE */
