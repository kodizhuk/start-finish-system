
#include <CyLib.h>
#include <GatePin.h>
#include <GATE_INT.h>
#include "lib_RTC\RTC_WDT.h"
#include "lib_DB\database.h"

#define GATE_OPEN    1
#define GATE_CLOSE   0

static uint64_t savedUnixTime;
static uint32_t savedRecentMs;
static uint32_t gateOpen ;


void GateInit(void);
uint32_t  GateIsOpen(void);
void GetFinTime(uint64_t *unixTime,  uint32_t *recentMs);
void AllowNextSkier(void);

/* [] END OF FILE */