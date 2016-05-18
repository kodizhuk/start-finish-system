#include <project.h>
#include <stdio.h>     
#include <stdbool.h>

/* max number skier */
#define MAXSKIER 9    

/* do we want to enable the test mode? */
#define TEST_MODE_WIRED 0 

/*Commands*/
#define COMMAND_START   's'
#define COMMAND_CANCEL  'c'
#define COMMAND_READ    'r'

/*led indication*/
#define LED_ON  0
#define LED_OFF 1

/* Api to read (WDT) counter value
* WDT Counter 0 Read value 
* (uint32) CySysWdtGetCount(0u);  
*/

void LedIndication(void);
void DisplayIndication(int numSkier, int numSkiers);
void OutToDisplay(int numSkier, int position);
void WriteAllTime(char data);
  
/* Structure for have current skyer time */
struct time{
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
    uint16_t msec;
};

/*data for each skier*/
struct time tSkier[9] = {0,0,0,0};       

/*flags button */
bool startPress = false;    
bool cancelPress = false; 

/*number sportsmen last started*/
uint32_t skier = 0;

/*buffer for output string*/
char string_buff[16];   


/*interrupt for start button*/
CY_ISR(startHandler)        
{
    if(skier < MAXSKIER){
        skier++;
        /*put simbol start and number for skier*/
        sprintf(string_buff,"%c%c",COMMAND_START,skier+'0');  
        xbee_PutString(string_buff);  
        
        #if(TEST_MODE_WIRED)
        /*this code is used for test mode when two devices are connected via wire*/
        wired_Write(1);
        CyDelay(1);
        wired_Write(0);
        /*end of test code*/
        #endif
        
        /* LED indication*/
        startPress = true;
    }
    start_ClearInterrupt(); 
}

/*intettupt for incoming data*/
CY_ISR(dataHandler)    
{
    uint8_t c;
    
    /*record time skiers */
    writeAllTime(c);      
}

/*interrupt for cancel button*/
CY_ISR(cancelHandler)       
{
    if(skier){
        /*put simbol cancel and number for skier*/
        sprintf(string_buff,"%c%c",COMMAND_CANCEL,skier+'0');
        xbee_PutString(string_buff);
        
        skier--;
        /*LED indication*/
        cancelPress = true;
    }
    cancel_ClearInterrupt();
}

/*interrupt for blink led*/
CY_ISR(blincHandler)      
{
    /*if skier!=0 start blinc LED*/
    if(skier){
        led_blue_Write(LED_ON);
        CyDelay(1);
        led_blue_Write(LED_OFF);
    }
    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
}


int main(void)
{
    uint32 interruptState;
    CyGlobalIntEnable;    
    
    interruptState = CyEnterCriticalSection();
    xbee_Start();                       
    display_Start();                    
    CyExitCriticalSection(interruptState);
        
    int_blinc_StartEx(blincHandler);    
    int_inputData_StartEx(dataHandler);
    int_start_StartEx(startHandler);  
    int_cancel_StartEx(cancelHandler);
    
    
    while(1)
    {  
        LedIndication();
        DisplayIndication(1,2);
        CyDelay(1000);
    }
}


void LedIndication()
{
    int i;
    
    if(startPress)          //func blinc blue led
        for(i=0;i<6;i++){
            startPress = false;
            led_blue_Write(~led_blue_Read());
            CyDelay(50);
        }
    if(cancelPress)
        for(i=0;i<10;i++){       //func blinc cancel red led
            cancelPress = false;
            led_blue_Write(LED_OFF);
            led_red_Write(~led_red_Read());
            CyDelay(50);
        }
    led_blue_Write(LED_OFF);   
}

/*output to display a specified time skier*/
void DisplayIndication(int numSkier, int numSkiers)
{      
    int i;
    int position=0;
    
    for(i=0; i < numSkiers; i++,position++)
    {
        if(position > 1)position = 0;
        OutToDisplay(numSkier+i, position);
    }
}

/*******************************************************
* Function name: outToDisplay
*
* Function does print the skyer 
* results on display
*
* Parameters:
* num - skyer number. Valid range - [0-9]
* position - raw position where skyer results will be 
* printed on display 
*
* return - if void is returned thhis line could be 
* deleted.
*
*******************************************************/
void OutToDisplay(int num, int position)
{
    display_Position(position,0);
    sprintf(string_buff,"%i - %d:%d:%d:%d",
        num,tSkier[num].hour, tSkier[num].min,tSkier[num].sec,tSkier[num].msec);
    display_PrintString(string_buff);
}

void WriteAllTime(char data)
{
        
    //if((c>='0' && c<='9') || c==':') tSkier[i++].min = c;
}