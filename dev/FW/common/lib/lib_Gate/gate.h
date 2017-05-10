#ifndef _GATE_H
    #define _GATE_H
    
#include <CyLib.h>
#include "appGlobal.h"
    
#define GATE_OPEN    1
#define GATE_CLOSE   0


void GateInit(void);
uint32_t  GateIsOpen(void);

#ifdef START_MODULE
void GetStartTime(uint64_t *unixTime,  uint32_t *recentMs);
#endif

#ifdef FINISH_MODULE
void GetFinTime(uint64_t *unixTime,  uint32_t *recentMs);
#endif

void AllowNextSkier(void);
void DisAllowNextSkier(void);

#endif
/* [] END OF FILE */