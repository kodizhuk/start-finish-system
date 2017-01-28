#ifndef _MY_DELAY_H
    #define _MY_DELAY_H
    
#include <project.h>
/*user lib*/
#include "lib_RTC\RTC_WDT.h"
#include "lib_DS1307\DS1307.h"
#include "lib_LED\LED.h"
#include "lib_Display\display.h"
#include "lib_Network\network.h"
#include "lib_Gate\gate.h"
#include "lib_Fat\ff.h"
#include "lib_DB\database.h"
#include "lib_MyDelay\myDelay.h"
#include "lib_BLE\bluetooth.h"
#include "lib_Batt\batt.h"
#include "lib_testMode\testMode.h"
    
#define NO_ERROR    1
#define ERROR       0

/*timeout*/
#define TIMEOUT_NEXT_SKIER  1000
#define TIMEOUT_DELAY   500
#define TIMEOUT_USER_READ_INFO  500

/*all state for state-machine*/
typedef enum {TIME_SYNC = 0, READY, CHECK_GATE, SAVE_RESULT} StateType; 
StateType currentState;

static uint32_t result;

uint32_t SystemInit(void);
uint32_t TimeSynchronize();
uint32_t CheckReady(void);
uint32_t CheckGate(void);
void SaveResult(void);


#endif

/* [] END OF FILE */
