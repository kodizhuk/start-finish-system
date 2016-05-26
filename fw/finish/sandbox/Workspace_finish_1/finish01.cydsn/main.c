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
#define COMMAND_OK          "OK\n\r"

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


void ShowTime(int maxSkier,struct SKIERRESULT skierTime[]);       
void LedIndication(void);  
void deletTimeSkier(int number, struct SKIERRESULT skierTime[]);
void deletTimeSkier(int numSkier, struct SKIERRESULT skier[]);
void quantifyTimeRezult(struct SKIERRESULT *skierTime);

/* flags status */
/* skiers on track */
bool onTrack = false;
/* request read time skiers  */
bool requestRead = false;

/*press button finish*/
bool pressFinish = false;

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
    if(last_finished < last_started){
        skierRezult[last_finished].finish= RealTime;
        skierRezult[last_finished].finish.msec = timer_ReadCounter();
        
        /*increment last skier finished*/
        last_finished++;
        
        /*button pressed flag*/
        pressFinish = true;
    }
    
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
            xbee_PutString(COMMAND_OK);
            onTrack = true;
            last_started++;
            break;
        case COMMAND_CANCEL:
            /*command accepted*/
            xbee_PutString(COMMAND_OK);
            break;
        case COMMAND_READ:
            requestRead = true;
            break;
        case COMMAND_ST_CONNECT:
            /*command accepted*/
            xbee_PutString(COMMAND_OK);
            break;
        default:
            /*delet number skier*/
            if(lastCommand == COMMAND_CANCEL)            
                    deletTimeSkier((input-'0'),skierRezult);
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
        /*check skiers on the track*/
        if(last_finished == last_started)
            onTrack = false;   
        if(onTrack) 
            LedIndication();
        /*if incomming command read*/
        if(requestRead){
            ShowTime(MAXSKIER,skierRezult);
            requestRead = false;
        }
        
        if(pressFinish){
            quantifyTimeRezult(&skierRezult[last_finished-1]);
            pressFinish = false;
        }
        
        CyDelay(1000);
    }
}


/*******************************************************
* Function name: quantifyTimeRezult
*
* Function write rezult subtraction between start and finish
* 
* Parameters:
* skierTime - struct from time skier
*******************************************************/
void quantifyTimeRezult(struct SKIERRESULT *skierTime)
{
    int rezult;
    int negative = 0;
       
    rezult = skierTime->finish.msec - skierTime->start.msec;
    if(rezult < 0){
        rezult =1000+rezult;
        negative = -1;
    }
    skierTime->rezult.msec = rezult;
    
    rezult = skierTime->finish.sec - skierTime->start.sec;
    if(rezult < 0){
        rezult = 60+rezult+negative; 
        negative = -1;
    }
    else {
        rezult = rezult+negative;
        negative = 0;
    }
    skierTime->rezult.sec = rezult;
       
    rezult = skierTime->finish.min - skierTime->start.min;
    if(rezult < 0){
        rezult = 60+rezult+negative; 
        negative = -1;
    }
    else {
        rezult = rezult+negative;
        negative = 0;
    }
    skierTime->rezult.min = rezult;
   
    rezult = skierTime->finish.hour - skierTime->start.hour + negative;
    if(rezult > 0)skierTime->rezult.hour = rezult + negative;
}


/*******************************************************
* Function name: deletTimeSkier
*
* Function remove rezult from the table
* 
* Parameters:
* numSkier - number skier for remove.
* skier[] - struct from time skiers
*******************************************************/
void deletTimeSkier(int numSkier, struct SKIERRESULT skier[])
{
    memset(&skier[numSkier-1],0,sizeof(skier[numSkier-1]));
}


/*******************************************************
* Function name: ShowTime
*
* Function displays data for all skiers
* 
* Parameters:
* maxSkier - max skier on distancion.
* skier[] - struct from time skiers
*******************************************************/
void ShowTime(int maxSkier,struct SKIERRESULT skier[])
{
    char buffer[16]; 
    int num;
    
    for(num=0; num < maxSkier; num++){
        sprintf(buffer, "%i:%i:%i:%i   ",
            skier[num].start.hour, skier[num].start.min, 
            skier[num].start.sec ,skier[num].start.msec);
        xbee_PutString(buffer);
        sprintf(buffer, "%i:%i:%i:%i   ",
            skier[num].finish.hour, skier[num].finish.min, 
            skier[num].finish.sec ,skier[num].finish.msec);
        xbee_PutString(buffer);
        sprintf(buffer, "%i:%i:%i:%i\n\r",
            skier[num].rezult.hour, skier[num].rezult.min, 
            skier[num].rezult.sec ,skier[num].rezult.msec);
        xbee_PutString(buffer);
    }
}

/*******************************************************
* Function name: LedIndication
*
* Function led off(led on in interrrupt timer
* if skier on distancion)
* 
*******************************************************/
void LedIndication(void)
{
    int LED_ON = 0;
    int LED_OFF = 1;
    
    /*blink led*/
    led_green_Write(LED_ON);
    CyDelay(10);
    led_green_Write(LED_OFF);
}