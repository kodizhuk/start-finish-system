#ifndef _GATE_H
    #define _GATE_H
    
#include <CyLib.h>

#define GATE_OPEN    1
#define GATE_CLOSE   0


void GateInit(void);
uint32_t  GateIsOpen(void);
void GetStartTime(uint64_t *unixTime,  uint32_t *recentMs);
void AllowNextSkier(void);
void DisAllowNextSkier(void);

#endif
/* [] END OF FILE */