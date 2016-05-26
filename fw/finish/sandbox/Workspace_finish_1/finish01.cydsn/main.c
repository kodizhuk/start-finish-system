#include <project.h>
#include <stdio.h>          
#include <string.h>
#include <stdbool.h>

/* max number skier */
#define MAXSKIER 9       

/*Commands*/
#define COMMAND_START       's'
#define COMMAND_CANCEL      'c'
#define COMMAND_READ        'r'
#define COMMAND_ST_CONNECT  'q'

/* Structure for have current skier time */
struct time{           
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
    uint16_t msec;
};

/* Structure for have start, finish 
*   and rezult  skier time*/
struct SKIERRESULT{
    struct time start;
    struct time finish;
    struct time rezult;
}skierRezult[MAXSKIER];

/*struct for real time*/
struct time RealTime;


void ShowTime(int maxSkier,struct SKIERRESULT *skierTime);       
void LedIndication(void);  
void deletTimeSkier(int number, struct SKIERRESULT *skierTime);

/* flags status */
/* skiers on track */
bool onTrack = false;
/* request read time skiers  */
bool requestRead = false;

/*number sportsmen last started and finished*/
int last_started = 0;
int last_finished = 0;

/*number free slots*/
int free_slots = 0;
/*the number of skiers who finished*/
int finish_skier = 0;

/*for read number skiers for add or delet*/
char lastCommand;  
        


/*interrupt for press finish button*/
CY_ISR(finishHandler)
{       
    /*kopi real time in finished skier rezult*/
    skierRezult[last_finished].finish= RealTime;
    
    /*increment last skier finished*/
    last_finished++;     
    
    finish_ClearInterrupt();
}

/*interrupt for counter timer */
CY_ISR(timerHandler)
{   
    /*if run stopwach, timer start*/
    if(onTrack){
        if (++RealTime.sec==59){
            RealTime.sec = 0;   
            if (++RealTime.min==59){
                RealTime.min = 0;    
                if (RealTime.hour==24) 
                    RealTime.hour = 0;   
            }  
        }
    }
    
    timer_ClearInterrupt(timer_INTR_MASK_CC_MATCH); 
}

/*interrupt for input simbol from xbee*/
CY_ISR(xbeeHandler)
{
    char input = xbee_GetChar();
    
    switch (input){
        case COMMAND_START:       
            RealTime.msec = timer_ReadCounter();
            skierRezult[last_started].start = RealTime;
            
            /*command accepted*/
            xbee_PutString("OK");
            onTrack = true;
            break;
        case COMMAND_CANCEL:
            /*command accepted*/
            xbee_PutString("OK");
            break;
        case COMMAND_READ:
            requestRead = true;
            break;
        case COMMAND_ST_CONNECT:
            /*command accepted*/
            xbee_PutString("OK");
            break;
        default:
            /*delet number skier*/
            if(lastCommand == COMMAND_CANCEL)            
                    deletTimeSkier((input-'0'),&skierRezult[0]);
            break;       
    }
    lastCommand = input;
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
        if(onTrack) 
            LedIndication();   
        if(requestRead)
            ShowTime(MAXSKIER,&skierRezult[0]);
        /*reset struct first*/
        //if(!runStopwach)memset(&first,0,sizeof(first));     
    }
}

/*******************************************************
* Function name: ShowTime
*
* Function displays data for all skiers
* 
* Parameters:
* maxSkier - max skier on distancion.
* SKIERRESULT *skier - struct from time skiers
*******************************************************/
void ShowTime(int maxSkier,struct SKIERRESULT *skier)
{
    /*buffer for two rows*/
    char buffer[16]; 
    int num;
    
    for(num=0; num < maxSkier; num++){
        sprintf(buffer, "%i:%i:%i:%i\n\r",
            skier[num].rezult.hour, skier[num].rezult.min, 
            skier[num].rezult.sec ,skier[num].rezult.msec);
        xbee_PutString(buffer);
    }
}

/*******************************************************
* Function name: LedIndication
*
* Function blinc led
* 
*******************************************************/
void LedIndication(void)
{
    int LED_ON = 0;
    int LED_OFF = 1;
    
    /*blinc led*/   
    led_green_Write(LED_ON);
    CyDelay(10);
    led_green_Write(LED_OFF);
}


/*
*таймер зчитує мс . незабути вкінці їх відняти
*
*
*
*/