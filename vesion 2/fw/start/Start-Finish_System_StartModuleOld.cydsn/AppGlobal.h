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

#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <project.h>
#include <time.h>


// Defines a frequency blinking led indicator in Hz
#define FREQ_INIT_BLINK         (3u)
#define FREQ_ERR_BLINK         (10u)

#define LED_ENABLE              (1u)
#define LED_DISABLE             (0u)

#define CURSOR_ROW_0            (0u)
#define CURSOR_ROW_1            (1u)
#define CURSOR_COL_0            (0u)

static const char default_format[] = "%a %b %d %Y %T";
static const char ERR_RTC_SYNC[]   = "RTC Not Sync";
static const char ERR_CHECK_CON[]  = "No Conn wth Fin";
static const char LR[] = "\r\n";

char ResTime[32];
struct tm lt;

char buff[50];
uint8_t GateState;
uint32_t InChar;
uint64_t UTime;

void SystemInit(void);
uint32_t SystemStart(void);

/* [] END OF FILE */
