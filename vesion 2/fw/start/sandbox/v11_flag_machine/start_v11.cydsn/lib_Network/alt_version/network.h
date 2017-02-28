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
#define DEBUG_W_UART
#ifdef DEBUG_W_UART
    #include <UART_PC.h>
#endif
    
#include <CyLib.h>
//#include <crc32.h>
#include <lib_network\svt.h>
#include "lib_RTC\RTC_WDT.h"

#define FR_TIMER               (1000u)

#define CONN_TIME_TO_RD        (1000u)

#define TimeToTicks(Data)       (Data)           

#define STX_S                   ("<")
#define FRM0                    ("!")
#define FRM1                    ("@")
#define FRM2                    ("#")
#define ETX_S                   (">")

#define BUFF_LEN                100u


struct Resp TX_RESP;
uint8_t RXSTATUS;

void NetworkInit();

uint32_t CheckConnection();
uint32_t CheckFinishReady();
uint32_t RTC_Sync();

uint32_t SendSkierStart(uint64_t UnixTimeStart, uint16_t MillsTimeStart);
uint8_t PackData(char *buff, uint8_t* data, uint32_t Sequence);

/* [] END OF FILE */
