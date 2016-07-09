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
#include <stdint.h>
// For XBEE Uart
#include <UART_XB.h>
#include <UART_XB_SPI_UART.h>

#ifdef DEBUG_W_UART
    #include <UART_PC.h>
    #include <UART_PC_SPI_UART.h>
#endif
    
#include <CyLib.h>
#include <crc32.h>
#include <svt.h>

#define FR_TIMER               (1000u)

#define CONN_TIME_TO_RD        (1000u)

#define TimeToTicks(Data)       (Data)           

#define RDY                    (0x1A)
#define GTM                    (0x1B)
#define OKR                    (0x20)

#define FRM0                    ("!")
#define FRM1                    ("@")
#define FRM2                    ("#")


#define BUFF_LEN                 100u

char szSeq[20];
char szData[50];
char szCheckSum[20];

struct Resp TX_RESP;
uint8_t RXSTATUS;
char RespBuff[50];

void NetworkInit();
uint32_t CheckConnection();
uint32_t NTP_Send();

uint8_t PackData(char *buff, char* data, uint32_t Sequence);

/* [] END OF FILE */
