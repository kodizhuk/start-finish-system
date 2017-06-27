#ifndef _TASK_AUTOMAT_H
    #define _TASK_AUTOMAT_H
    
    #include <project.h>
    #include "appGlobal.h"
	
	#ifdef START_MODULE
    #define ACTION1_TIMEOUT 500
    #define ACTION2_TIMEOUT 100
    #define ACTION3_TIMEOUT 500
    #define ACTION4_TIMEOUT 500
    #define ACTION5_TIMEOUT 500
	#endif
	#ifdef	FINISH_MODULE
	#define ACTION1_TIMEOUT          5      
    #define ACTION2_TIMEOUT          5      
    #define ACTION3_TIMEOUT          5      
    #define ACTION4_TIMEOUT          1      
    #define ACTION5_TIMEOUT          1    //ble, do not move
	#endif
 
    enum {ACTION1, ACTION2, ACTION3, ACTION4, ACTION5};
    
    void TaskTimerInit();
    void TaskCheck(void);
    void SetTaskTimer(uint8_t newNumber, uint16_t newTime);
    
#endif
