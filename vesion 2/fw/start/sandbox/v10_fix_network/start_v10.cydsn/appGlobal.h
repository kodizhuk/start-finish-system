
#include <project.h>
/*user lib*/
#include "lib_RTC\RTC_WDT.h"
#include "lib_LED\LED.h"
#include "lib_Display\display.h"
#include "lib_Network\network.h"
#include "lib_Gate\gate.h"
#include "lib_MyDelay\myDelay.h"
#include "lib_Batt\batt.h"
#include "lib_testMode\testMode.h"

#define NO_ERROR    1
#define ERROR       0

#define TIMEOUT_NEXT_SKIER  2000
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


/* [] END OF FILE */
