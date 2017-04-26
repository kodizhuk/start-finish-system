#ifndef _TASK_AUTOMAT_H
    #define _TASK_AUTOMAT_H
    
    #include <project.h>
  
    #define ACTION1_TIMEOUT          5      //ms
    #define ACTION2_TIMEOUT          5      //ms
    #define ACTION3_TIMEOUT          5      //ms
    #define ACTION4_TIMEOUT          1      //ms
    #define ACTION5_TIMEOUT          1    //ble, do not move
    
    enum {ACTION1=0, ACTION2, ACTION3, ACTION4, ACTION5};
    
    void TaskTimerInit();
    void TaskCheck(void);
    void SetTaskTimer(uint8_t newNumber, uint16_t newTime);
    
#endif
