#include <project.h>
#include <stdio.h>          
#include <string.h>
#include <stdbool.h>

/* max number skier */
#define MAXSKIER 10          

/*Commands*/
#define COMMAND_START   's'
#define COMMAND_CANCEL  'c'
#define COMMAND_READ    'r'

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


void ShowTime(int maxSkier,struct SKIERRESULT *rezult);       
void LedIndication(void);  

/*data for each skier*/
struct time first[MAXSKIER] = {0,0,0,0}; 


/*flags status*/    
bool runStopwach = false;     
bool writeStatus = false;

/*number sportsmen last started*/
int skier = 0;
/*the number of skiers who finished*/
int finish_skier = 0;

/*for read number skiers for add or delet*/
char lastCommand;  

/*number skiers should display*/
int write_time;        


/*interrupt for press finish button*/
CY_ISR(finishHandler)
{   
    int finish_time;
    
    /*write diffence time ms between finish-start*/
    finish_time= timer_ReadCounter() - first[finish_skier].msec;
    
    if(finish_time >= 0)first[finish_skier].msec = finish_time;
    else {
        first[finish_skier].msec = -(finish_time);
        first[finish_skier].sec--;
    }
    if(skier){
        skier--;
        finish_skier++;   
    }
    
    /*stop stopwath if skier = 0*/
    if(!skier) runStopwach = false;     
    
    finish_ClearInterrupt();
}

/*interrupt for counter timer */
CY_ISR(timerHandler)
{
    int i;
    
    /*if run stopwach, timer start*/
    if(runStopwach){
        for(i=finish_skier; i<skier; i++){
            if (++first[i].sec==59){
                first[i].sec = 0;   
                if (++first[i].min==59){
                    first[i].min = 0;    
                    if (++first[i].hour==24) 
                        first[i].hour = 0;   
                }  
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
            first[skier].msec = timer_ReadCounter();
            runStopwach = true;
            break;
        case COMMAND_CANCEL:       
            if(!skier)runStopwach = false;
            break;
        case COMMAND_READ:
            writeStatus = true;
            break;
        default:
            /*write number skier add distance*/
            if(lastCommand == COMMAND_START)skier = input-'0';
            /*delet number skier*/
            if(lastCommand == COMMAND_CANCEL)            
                    if(skier)skier--;
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
        LedIndication();   
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
* Function led off(led on in interrrupt timer
* if skier on distancion)
* 
*******************************************************/
void LedIndication(void)
{
    int LED_ON = 0;
    int LED_OFF = 1;
    
    /*off led(on in interrupt in timer)*/   
    led_green_Write(LED_ON);
    CyDelay(10);
    led_green_Write(LED_OFF);
}