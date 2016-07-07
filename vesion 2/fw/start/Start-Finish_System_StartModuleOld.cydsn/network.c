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
#include <network.h>

uint32_t CheckConnection()
{
    uint32_t Stat = 0;
    uint32_t Resp = 0;
    uint32_t Ticks = 0;

    
    UART_XB_UartPutChar(XBEE_COMM_RD);
    
    #ifdef DEBUG_W_UART
    UART_PC_UartPutString("Sending Packet For Ready Start Module\r\n");
    #endif
    
    while ((++Ticks<50) && !Stat)
    {
        CyDelay(100);
        Resp = (UART_XB_UartGetChar() & 0xFF);
        if (XBEE_COMM_OK == Resp)
        {
            Stat = 1;
            
            #ifdef DEBUG_W_UART
            UART_PC_UartPutString("OK RECIEVED\r\n");
            #endif
        }
    }
    
    #ifdef DEBUG_W_UART
    if (!Stat)
        UART_PC_UartPutString("ERR: TIMEOUT\r\n");
    #endif    
    
    return Stat;
}

uint32_t NTP_Send()
{
    return 1u;
}

/* [] END OF FILE */
