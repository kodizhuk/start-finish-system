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
#include <UART_XB.h>
#include <UART_XB_SPI_UART.h>

#ifdef DEBUG_W_UART
    #include <UART_PC.h>
    #include <UART_PC_SPI_UART.h>
#endif
    
#include <CyLib.h>

#define FR_TIMER               (1000u)

#define CONN_TIME_TO_RD        (1000u)

#define TimeToTicks(Data)      (Data)           

#define XBEE_COMM_RD           ('R')
#define XBEE_COMM_TM           ('T')
#define XBEE_COMM_OK           ('O')

uint32_t CheckConnection();
uint32_t NTP_Send();

/* [] END OF FILE */
