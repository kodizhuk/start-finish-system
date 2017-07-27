#ifndef _APP_GLOBAL_H
    #define _APP_GLOBAL_H
#define START_MODULE
#include <project.h>
/*user lib*/
#include "..\..\common\lib\lib_RTC\RTC_WDT.h"
#include "..\..\common\lib\lib_LED\LED.h"
#include "..\..\common\lib\lib_Display\display.h"
#include "lib_Network\network.h"
#include "..\..\common\lib\lib_Gate\gate.h"
#include "..\..\common\lib\lib_Batt\batt.h"
#include "..\..\common\lib\lib_testMode\testMode.h"
#include "..\..\common\lib\lib_TaskTimer\taskAutomat.h"
#include "..\..\common\lib\lib_IDskier\IDskier.h"

   
#define NO_ERROR    1
#define ERROR       0

#define TIMEOUT_NEXT_SKIER  3000
#define TIMEOUT_STATE   500
#define TIMEOUT_USER_READ_INFO  500

typedef enum {TIME_SYNC = 0, GET_FIN_STATUS, CHECK_GATE, SAVE_RESULT} StateType; 
StateType currentState;

static uint32_t result;

void SystemInit(void);
uint32_t TimeSynchronize(void);
uint32_t GetFinishStatus(void);
uint32_t CheckGate(void);
uint32_t SaveResult(void);
void Delay(uint32_t delayMs);


/* [] END OF FILE */
#endif