#include <project.h>
#include <stdio.h>          //include for sprintf()

void show_time(void);       //out time
void led_indication(void);  

typedef enum {false, true} bool;
struct time{            //struct for saved time
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
    uint16_t msec;
};
struct time first = {0,0,0,0};
bool crossFin = false;      //flag cross the finish
bool startStopwach = false;     //flag start stopwatch

CY_ISR(finishHandler)
{
    crossFin = true;
    finish_ClearInterrupt();
}

CY_ISR(timerHandler)
{
    if (++first.sec==59){
        first.sec = 0;   
        if (++first.min==59){
            first.min = 0;    
            if (++first.hour==24) 
                first.hour = 0;   
        }  
    }
    led_green_Write(0);
    timer_ClearInterrupt(timer_INTR_MASK_CC_MATCH); //delet interrupt timer
}

CY_ISR(xbeeHandler)
{
    if(xbee_GetChar() == 's');
    if(xbee_GetChar() == 'c');
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    timer_Start();
    xbee_Start();

    isr_finish_StartEx(finishHandler);
    isr_timer_StartEx(timerHandler);
    isr_xbee_StartEx(xbeeHandler);
    
    for(;;)
    {
        show_time();
        led_indication();
        
    }
}

void show_time()
{
    char buffer[32];    ////buffer for two rows
    sprintf(buffer, "%i:%i:%i\n\r",first.hour, first.min, first.sec);
    xbee_PutString(buffer);
    //CyDelay(100);
}

void led_indication()
{
    led_green_Write(1);
}