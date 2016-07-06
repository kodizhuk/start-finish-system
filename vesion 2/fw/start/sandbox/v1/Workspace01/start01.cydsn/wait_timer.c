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
#include <wait_timer.h>

static uint32_t minute;


/*******************************************************************************
*
* Interrupt handler after lefting time one period light
*
*******************************************************************************/
CY_ISR(WaitHandler)
{
    /*interruption occurring every minute*/
    if(minute > 0)
    {
        minute--;
    }
        
    Timer_Wait_ClearInterrupt(Timer_Wait_INTR_MASK_CC_MATCH);
}


/*******************************************************************************
* Function Name: InitWaitingTimer
********************************************************************************
*
* Initialization timer and add interrupt to him 
*
*******************************************************************************/
void InitWaitingTimer(uint32_t time)
{
    minute = time;
    Timer_Wait_Start();
    int_wait_StartEx(WaitHandler);
}


/*******************************************************************************
* Function Name: WaitingTime
********************************************************************************
*
* waiting time
*
* Parameters:
*  time (minute) when the box falshe be changed to true 
*
* Return:
*  true(time out) or false(while not out)
*******************************************************************************/
bool WaitingTimeOut(void)
{
    bool rezult;
    
    rezult = false;
    
    if(minute == 0)
    {
        rezult = true;
        Timer_Wait_Stop();
    }
    
    return rezult;
}
/* [] END OF FILE */
