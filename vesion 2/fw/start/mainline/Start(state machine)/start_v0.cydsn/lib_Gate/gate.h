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
#include <CyLib.h>
#include <GatePin.h>
#include <GATE_INT.h>
#include "lib_RTC\RTC_WDT.h"

#define GATE_OPEN    1
#define GATE_CLOSE   0

static uint64_t savedUnixTime;
static uint32_t savedRecentMs;
static uint32_t gateOpen ;

void GateInit(void);

void AllowNextSkier(void);
void DisAllowNextSkier(void);
uint32_t  GateIsOpen(void);

void GetStartTime(uint64_t *unixTime,  uint32_t *recentMs);

#define DEBUG_PC
#ifdef DEBUG_PC

#endif
/* [] END OF FILE */