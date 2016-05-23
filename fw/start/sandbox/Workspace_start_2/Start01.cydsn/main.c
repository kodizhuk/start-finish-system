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

/*button click*/
#define PRESSED 0


void LedIndication(void);
void DisplayIndication(int numSkier, int numSkiers);
void ReadTime(void);
  
/* Structure for have current skyer time */
struct time{
    uint16_t hour;
    uint16_t min;
    uint16_t sec;
    uint16_t msec;
};

/*data for each skier*/
struct time tSkier[MAXSKIER] = {0,0,0,0};       

/*flags pressed button */
bool startPress = false;    
bool cancelPress = false; 

/*number sportsmen last started*/
uint32_t skier = 0;

/*buffer for output string on display*/
char string_buff[16];   


/*interrupt for start or cancel button*/
CY_ISR(buttonHandler)        
{
    if(start_Read()==PRESSED){
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
    else if(cancel_Read()==PRESSED){
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
}

/*intettupt for incoming data*/
CY_ISR(dataHandler)    
{       
    /*record time skiers */
    //ReadTime();
}


/*interrupt for blink led*/
CY_ISR(blincHandler)      
{
    /*blinc LED*/
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
    
    /*before initialisation disablle all interrupts*/
    interruptState = CyEnterCriticalSection();
    xbee_Start();                       
    display_Start();                    
    CyExitCriticalSection(interruptState);
        
    int_blinc_StartEx(blincHandler);    
    int_inputData_StartEx(dataHandler);
    int_button_StartEx(buttonHandler);  
    
    
    while(1)
    {  
        LedIndication();
        // SkierToDisplay = lastFinished;
        // string strSkierInfoOneSkier = SkierInforToStrOneSkier(skierInfo[SkierToDisplay]);
        // string strSkierInfoAllTable = SkierInforToStrAll(skierInfo);
        // displaySkierInfoOneSkier(strSkierInfoOneSkier)
        // displaySkierInfoAllTable(strSkierInfoAllTable)
        DisplayIndication(1,2);
    }
}


/*******************************************************
* Function name: LedIndication
*
* Function does blink led 
* when the key pressed
* if pressed "start", blinc blue led 6 times
* if pressed "cancel", blinc red led 10 times
*
*******************************************************/
void LedIndication(void)
{
    int i;
    
    /*func blinc blue led*/
    if(startPress)          
        for(i=0;i<6;i++){
            startPress = false;
            led_blue_Write(~led_blue_Read());
            CyDelay(50);
        }
    /*func blinc cancel red led*/
    if(cancelPress)
        for(i=0;i<10;i++){       
            cancelPress = false;
            led_blue_Write(LED_OFF);
            led_red_Write(~led_red_Read());
            CyDelay(50);
        }
    led_blue_Write(LED_OFF);   
}


/*******************************************************
* Function name: OutToDisplay
*
* Function does print the skyer 
* results on display
*
* Parameters:
* numSkier - skyer number which start printed 
* rezult on display. Valid range - [1-10]
* numSkiers - number of skiyers whose rezult  
* you want to print display. Valid range - [1-2]
*
*******************************************************/
void DisplayIndication(int numSkier, int numSkiers)
{
    int position;
    
    /*incorrect incoming data*/
    if(numSkier < 1)numSkier = 1;
    for(position=0; position < numSkiers; position++,numSkier++)
    {
        /*incorrect data*/
        if(position > 1)position = 0;
        if(numSkier > MAXSKIER )numSkier = 1;
        
        display_Position(position,0);
        sprintf(string_buff,"%i - %d:%d:%d:%d",
            numSkier,tSkier[numSkier-1].hour, tSkier[numSkier-1].min,
            tSkier[numSkier-1].sec,tSkier[numSkier-1].msec);
        display_PrintString(string_buff);   
    }

}

void ReadTime()
{
    
}