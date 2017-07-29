#ifndef _APP_GLOBAL_H
    #define _APP_GLOBAL_H
    
#define FINISH_MODULE    
#include <project.h>
/*user lib*/
#include "..\..\common\lib\lib_RTC\RTC_WDT.h"
#include "..\..\common\lib\lib_DS1307\DS1307.h"
#include "..\..\common\lib\lib_LED\LED.h"
#include "..\..\common\lib\lib_Display\display.h"
#include "lib_Network\network.h"
#include "..\..\common\lib\lib_Gate\gate.h"
#include "..\..\common\lib\lib_Fat\ff.h"
#include "..\..\common\lib\lib_DB\database.h"
//#include "lib_MyDelay\myDelay.h"
#include "..\..\common\lib\lib_BLE\bluetooth.h"
#include "..\..\common\lib\lib_Batt\batt.h"
#include "..\..\common\lib\lib_testMode\testMode.h"
#include "..\..\common\lib\lib_TaskTimer\taskAutomat.h"
    
#define NO_ERROR    1
#define ERROR       0

/*timeout*/
#define TIMEOUT_NEXT_SKIER  1000
#define TIMEOUT_DELAY   500
#define TIMEOUT_USER_READ_INFO  500
    
/*all state for state-machine*/
typedef enum {TIME_SYNC = 0, READY, CHECK_GATE, SAVE_RESULT} StateType; 
StateType currentState;


void SystemInit(void);
uint32_t InitRTC(void);
uint32_t TimeSynchronize();
uint32_t CheckReady(void);
uint32_t CheckGate(void);
void SaveResult(void);
void Delay(uint32_t delayMs);


#endif

/* [] END OF FILE */
