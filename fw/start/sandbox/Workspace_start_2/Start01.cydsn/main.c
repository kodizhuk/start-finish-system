#include <project.h>
#include <stdio.h>      //include for sprintf

#define MAXSKIER 9     //max number skier
#define TEST_MODE_WIRED 0 // do we want to enable the test mode?

/*Commands*/
#define COMMAND_START   's'
#define COMMAND_CANCEL  'c'
#define COMMAND_READ    'r'

/* Api to read (WDT) counter value
* WDT Counter 0 Read value 
* (uint32) CySysWdtGetCount(0u);  
*/

void led_indication(void);
void display_indication(int numSkier);
  
typedef enum {false, true} bool;

bool startPress = false;
bool cancelPress = false;    //flags for press button

uint32_t skier = 0;      //number sportsmen last started

char finish_time[13] = "00.00.00.000";   //hh.mm.ss.uuu\0
char string_buff[16];   //buffer for output string

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
        
        // LED indication
        startPress = true;
    }
    start_ClearInterrupt(); 
}
/*intettupt for incoming data*/
CY_ISR(dataHandler)     //incoming data
{
    char c;
    static int i = 0;
    
    c = xbee_GetChar();
    if((c>='0' && c<='9') || c==':') finish_time[i++] = c;        
    if(c == '\n')i=0;
}

CY_ISR(cancelHandler)       //interrupt for cancel button
{
    if(skier){
        /*put simbol cancel and number for skier*/
        sprintf(string_buff,"%c%c",COMMAND_CANCEL,skier+'0');
        xbee_PutString(string_buff);
        skier--;
        cancelPress = true;
    }
    cancel_ClearInterrupt();
}
/*interrupt for blink led*/
CY_ISR(blincHandler)      
{
    if(skier){
        led_blue_Write(0);
        CyDelay(1);
        led_blue_Write(1);
    }
    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
}


int main(void)
{
    int_blinc_Disable();
    CyGlobalIntEnable;    
    xbee_Start();                       //start uart for xbee
    display_Start();                    //start lcd display
    int_blinc_Enable();
        
    int_blinc_StartEx(blincHandler);    //interrupt for blink led
    int_inputData_StartEx(dataHandler); //interrupt for RX data input
    int_start_StartEx(startHandler);    //interrupt start button
    int_cancel_StartEx(cancelHandler);  //interrupt cancel button
    
    
    while(1)
    {  
        led_indication();
        display_indication(1);
        CyDelay(100);
    }
}


void led_indication()
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
            led_blue_Write(1);
            led_red_Write(~led_red_Read());
            CyDelay(50);
        }
    led_blue_Write(1);   
}

void display_indication(int numSkier)
{      
    sprintf(string_buff,"    time     num");
    display_Position(0, 0);
    display_PrintString(string_buff);
    sprintf(string_buff,"%s  %i ",finish_time, skier);
    display_Position(1,0);
    display_PrintString(string_buff);
    if(skier){
        xbee_PutChar(COMMAND_READ);          //read data from the finish
        xbee_PutChar(skier+'0');
    }
}