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
#include "lib_network\network.h"

#define GATE_OPEN    1
#define GATE_CLOSE   0


void GateInit(void);
uint32_t  GateIsOpen(void);
void GateClose(void);
void AllowNextSkier(void);
/* [] END OF FILE */