#include "lib_MyDelay\myDelay.h"

/*******************************************************************************
* Function Name: MyDelay
********************************************************************************
*
* Summary:
*   delay feature where users performed free time
*
* Parameters:
*  delayMs - delay time in miliseconds
*
*******************************************************************************/
void MyDelay(uint32_t delayMs)
{
    
    if(delayMs < MIN_DELAY_MS)
    {
        CyDelay(delayMs);
    }else
    {
        uint32_t runTime;
        uint32_t counter ;
        uint32_t period;
        
        runTime = 0;
        period = AppDelay_ReadPeriod();
        AppDelay_WriteCounter(period);       
        AppDelay_Start();
        
        while(((delayMs - runTime) > MIN_DELAY_MS) && (runTime <= delayMs))
        {
            /*user function*/      
            UserFunc_1();
            UserFunc_2();
            UserFunc_3();
            
            CyDelay(MIN_DELAY_MS);
                            
            counter = AppDelay_ReadCounter();
            runTime = (period -  counter)/32.768;
            
            /*user function*/  
        }
        AppDelay_Stop();
        
        #ifdef DEBUG_PC
        char buffer[100];
        sprintf(buffer,"time send data %u\n\r", (runTime));
        SW_UART_DEBUG_PutString(buffer);
        #endif
        
        if (delayMs > runTime)
        {
            CyDelay(delayMs - runTime);
        }
    }
}

static void UserFunc_1(void)
{
    /*network*/
        
    ReceiveData();
    SendData(); 
    
    #ifdef DEBUG_PC
    //inData.readStatus = READ_OK;
    #endif
 
}


static void UserFunc_2(void)
{
    DisplayPrintfRealTime();
}

static void UserFunc_3(void)
{
    /*indicator network*/
    if(NetworkStatus() == NETWORK_CONN)
    {
        DisplayPutIndicatorNetwork(CONNECT);
    }else
    {
        DisplayPutIndicatorNetwork(DISCONNECT);
    }
       
}