#include <project.h>
#include <stdio.h>     
#include <stdbool.h>

/* max number skier */
#define MAXSKIER 9    

/*Commands*/
#define COMMAND_START       's'
#define COMMAND_READ        'r'
#define COMMAND_ST_CONNECT  'q'

/*button click*/
#define PRESSED 0
  
/* Structure for have current skyer time */
typedef struct time{
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
    uint16_t msec;
}TIME_T;

/* Structure for have start, finish 
*   and rezult  skier time
*/
struct SKIERRESULT{
    TIME_T start;
    TIME_T finish;
    TIME_T rezult;
}skierRezult[MAXSKIER];      


void LedIndication(bool start_press);
void DisplayIndication(int numSkier, int numSkiers, struct SKIERRESULT *skierTime);
void ReadTime(void);
//void displaySkierInfoOneSkier(int numSkier, struct time *skierInfo);
//void displaySkierInfoAllTable(struct SKIERRESULT skierInfo[]);
void sleepSystem(void);


/*flags pressed button */
bool startPress = false;  

/*flags, true if skier on track*/
bool onTrack = false;

/*number sportsmen last started and finished*/
uint32_t last_started = 0;
uint32_t last_finished = 0;


/*interrupt for start button*/
CY_ISR(buttonHandler)        
{
        if(last_started < MAXSKIER)
        { 
            /*put simbol start and number for skier*/  
            xbee_PutChar(COMMAND_START);  
            
            last_started++;
            /*skier on track*/
            onTrack = true;
            /* LED indication*/
            startPress = true;
            LedIndication(startPress);
            startPress = false;
        }
    start_ClearInterrupt();


}


CY_ISR(statusHandler)
{
    xbee_PutChar(COMMAND_ST_CONNECT);
    
    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
}



int main(void)
{
    CyGlobalIntEnable;   
    
    xbee_Start();                       
    //display_Start();
            
    int_button_StartEx(buttonHandler); 
    int_status_StartEx(statusHandler);
    
    
    for(;;)
    {  
        LedIndication(startPress);
        sleepSystem();

        /*print skier rezult to display*/
        //int skierToDisplay = last_finished;
        //displaySkierInfoOneSkier(skierToDisplay, &skierRezult[skierToDisplay].rezult);
        //displaySkierInfoAllTable(skierRezult);
    }
}


/*******************************************************
* Function name: displaySkierInfoAllTable
*
* Function  print time all skier on display
* display - row = 2, column = 16
*
* Parameters:
* numSkier - num skier, you want to print
* *skierInfo - struct from data about time skiers
*
*******************************************************/
void displaySkierInfoAllTable(struct SKIERRESULT skierInfo[])
{
    int i;
    /*row and column display*/
    int row = 2;
    int column = 16;
    char string_buff[column];

    for(i=0; i<row;i++)
    {
        sprintf(string_buff,"%i - %d:%d:%d:%d",  
            i+1,skierInfo[i].rezult.hour, skierInfo[i].rezult.min, 
            skierInfo[i].rezult.sec, skierInfo[i].rezult.msec);
        display_Position(i,0);
        display_PrintString(string_buff);        
    }  
}


/*******************************************************
* Function name: displaySkierInfoOneSkier
*
* Function  print time one skier on display
* time skier print in position (0,0)
*
* Parameters:
* numSkier - num skier, you want to print
* *skierInfo - struct from data about time skiers
*
*******************************************************/
void displaySkierInfoOneSkier(int numSkier, struct time *skierInfo)
{    
    char string_buff[16];
    
    sprintf(string_buff,"%i - %d:%d:%d:%d",  
        numSkier+1,skierInfo->hour, skierInfo->min, 
        skierInfo->sec, skierInfo->msec);
    display_ClearDisplay();
    display_Position(0,0);
    display_PrintString(string_buff);
}


/*******************************************************
* Function name: LedIndication
*
* Function  blink led 
* when the key pressed:
* if pressed "start", blinc blue led 6 times
*
* Parameters:
* startPress - press button Start. Valid range - true, falsh. Valid range - true, false
*
*******************************************************/
void LedIndication(bool start_press)
{
    int i;
    int LED_ON = 0;
    int LED_OFF = 1;
    
    /**blinc led*/   
    led_blue_Write(LED_ON);
    CyDelay(5);
    led_blue_Write(LED_OFF);
    
    /*func blinc blue led(start)*/
    if(start_press){          
        for(i=0;i<6;i++){
            led_blue_Write(~led_blue_Read());
            CyDelay(50);
        }
    } 
}

/*******************************************************
* Function name: sleepSystem
*
* Function  sleep the system
*
*******************************************************/
void sleepSystem(void)
{
    CyDelay(1000);
}