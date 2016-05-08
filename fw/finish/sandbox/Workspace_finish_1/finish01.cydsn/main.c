#include <project.h>
#include <stdio.h>          //include for sprintf()
#define MAXSKIER 9          //max skier in distance

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
bool runStopwach = false;     //flag run stopwatch
int skier = 0;
char lastPressed;       //for read number skiers for add or delet

CY_ISR(finishHandler)
{
    crossFin = true;
    if(skier>0)skier--;
    led_green_Write(0);
    CyDelay(100);
    
    finish_ClearInterrupt();
}

CY_ISR(timerHandler)
{
    if(runStopwach){        //if run stopwach, timer start
        if (++first.sec==59){
            first.sec = 0;   
            if (++first.min==59){
                first.min = 0;    
                if (++first.hour==24) 
                    first.hour = 0;   
            }  
        }
        led_green_Write(0);
    }
    
    timer_ClearInterrupt(timer_INTR_MASK_CC_MATCH); //delet interrupt timer
}

CY_ISR(xbeeHandler)
{
    char input = xbee_GetChar();
    
    switch (input){
        case 's':       //xbee recived start
            first.msec = timer_ReadCounter();
            runStopwach = true;
            break;
        case 'c':       //xbee resived cancel
            break;
        default:
            if(lastPressed == 's')skier = input-'0';    //write number skier add distance
            else if(lastPressed == 'c'){             //delet number skier
                    if(skier>0)skier--;
                }
            break;       
    }
    lastPressed = input;
}


int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    timer_Start();
    xbee_Start();

    isr_finish_StartEx(finishHandler);      //interrupt for button finish
    isr_timer_StartEx(timerHandler);        //interrupt for counter timer 
    isr_xbee_StartEx(xbeeHandler);          //interrupt for input simbol from xbee
    
    for(;;)
    {
        show_time();        //output time
        led_indication();   //blink led (period - 1s)
    }
}

void show_time()
{
    char buffer[32];    ////buffer for two rows
    sprintf(buffer, "%i:%i:%i-%i\n\r",first.hour, first.min, first.sec, skier);
    xbee_PutString(buffer);
    CyDelay(100);
}

void led_indication()
{
    led_green_Write(1);     //off led(on in interrupt in timer)
}