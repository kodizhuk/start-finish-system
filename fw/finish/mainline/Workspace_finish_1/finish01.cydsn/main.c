#include <project.h>
#include <stdio.h>          //include for sprintf()
#include <string.h>         //include for memset()
#define MAXSKIER 9          //max skier in distance

void show_time(int number_skier);       //out time
void led_indication(void);  

typedef enum {false, true} bool;
struct time{            //struct for saved time
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
    uint16_t msec;
};

struct time first[9] = {0,0,0,0};  //hh.mm.ss.uuu  array struct
bool crossFin = false;      //flag cross the finish
bool runStopwach = false;     //flag run stopwatch
bool writeStatus = false;
int skier = 0;
char lastPressed;       //for read number skiers for add or delet
int write_time;         //number skiers should display


CY_ISR(finishHandler)
{
    crossFin = true;
    
    if(skier)skier--;
    if(!skier) runStopwach = false;     //stop stopwath
    
    finish_ClearInterrupt();
}

CY_ISR(timerHandler)
{
    if(runStopwach){        //if run stopwach, timer start
        if (++first[1].sec==59){
            first[1].sec = 0;   
            if (++first[1].min==59){
                first[1].min = 0;    
                if (++first[1].hour==24) 
                    first[1].hour = 0;   
            }  
        }
        led_green_Write(0);
        CyDelay(5);
    }
    
    timer_ClearInterrupt(timer_INTR_MASK_CC_MATCH); //delet interrupt timer
}

CY_ISR(xbeeHandler)
{
    char input = xbee_GetChar();
    
    switch (input){
        case 's':       //xbee recived start
            first[1].msec = timer_ReadCounter();
            runStopwach = true;
            break;
        case 'c':       //xbee resived cancel
            if(!skier)runStopwach = false;
            break;
        case 'r':
            break;
        default:
            if(lastPressed == 's')skier = input-'0';    //write number skier add distance
            if(lastPressed == 'c')            //delet number skier
                    if(skier)skier--;
            if(lastPressed == 'r') {
                write_time = (input-'0');      //out time skier
                writeStatus = true;
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
        led_indication();   //blink led (period - 1s)
        if(writeStatus)show_time(write_time);
        //if(!runStopwach)memset(&first,0,sizeof(first));     //reset struct first
    }
}


void show_time(int num)
{
    char buffer[16];    ////buffer for two rows
    
    sprintf(buffer, "%d:%d:%d:%d\n\r",first[num].hour, first[num].min, first[num].sec ,first[num].msec);
    xbee_PutString(buffer);
    CyDelay(100);
    writeStatus = false;
}

void led_indication()
{
    led_green_Write(1);     //off led(on in interrupt in timer)
}