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
#include <stdbool.h>
#include <stdint.h>
#include <CyLib.h>
#include <int_wait.h>
#include <Timer_Wait.h>

CY_ISR(WaitHandler); // Interrupt Timer 

void InitWaitingTimer(uint32_t time);
bool WaitingTimeOut(void);



/* [] END OF FILE */
