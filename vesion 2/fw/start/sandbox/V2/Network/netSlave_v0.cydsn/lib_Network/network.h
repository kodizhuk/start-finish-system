/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
   
#include <UART_XB.h>
#include <UART_XB_SPI_UART.h>
#include <project.h>
#include <AppDelay.h>
#include <stdio.h>
#include <lib_Network\svt.h>

#define DEBUG_PC

#ifdef DEBUG_PC
    #include <SW_UART_DEBUG.h>
#endif

#define ERROR       0
#define NO_ERROR    1

#define READ_OK     1
#define NO_READ     0
#define WRITE_OK     1
#define NO_WRITE     0

#define MIN_DELAYMS 150

/*size buffer*/
#define DATA_BUFFER   50
#define RX_BUFFER   

#define ADRESS_READY        8
#define ADRESS_REBOOT       9
#define ADRESS_COUNT_SK     10

typedef struct
{
    uint8_t IDpacket;
    uint8_t ready;
    uint8_t reboot;
    uint8_t countSkiers;
    uint64_t tmpTime;
    uint16_t tmpMsTime;
    uint8_t readStatus;
}FinishData;

typedef struct
{
    uint8_t IDpacket;
    uint64_t unixStartTime;
    uint16_t startMsTime;
    uint8_t gateStatus;
    uint8_t writeStatus;
}StartData;

FinishData inData ;
StartData outData;


void InitNetwork(void);
void AppDelay(uint32_t delayMs);

void SendData(void);
uint32_t ReceiveData(void);

/* [] END OF FILE */
