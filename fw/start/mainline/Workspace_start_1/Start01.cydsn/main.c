#include <project.h>
#include <stdio.h>      //include for sprintf
#define MAXSKIER 9     //max number skier

void led_indication(void);
void display_indication(void);

typedef enum {false, true} bool;
bool startPress = false,cancelPress = false;    //flags for press button
uint32_t skier = 0;      //number sportsmen in distance
char finish_time[13] = "00.00.00.000";   //hh.mm.ss.uuu\0


CY_ISR(startHandler)        //interrupt for start button
{
    if(skier < MAXSKIER){
        skier++;
        xbee_PutChar('s');      //simbol start
        xbee_PutChar(skier+'0');  //number sportsmen   
        //test---
        //wired_Write(1);
        //CyDelay(1);
        //wired_Write(0);
        //test---
        startPress = true;
    }
    CyDelay(10);
    start_ClearInterrupt(); 
}

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
        xbee_PutString("c");      //simbol cancel
        xbee_PutChar(skier+'0');  //number sportsmen
        skier--;
        cancelPress = true;
    }
    CyDelay(10);
    cancel_ClearInterrupt();
}

CY_ISR(isrHandler)      //interrupt for blink blue led
{
    led_blue_Write(0);
    CyDelay(5);
    timer_ClearInterrupt(timer_INTR_MASK_CC_MATCH);
}


int main(void)
{
    CyGlobalIntEnable;    
    xbee_Start();                       //start uart for xbee
    display_Start();                    //start lcd display
        
    isr_StartEx(isrHandler);            //interrupt for blink led
    isr_inputData_StartEx(dataHandler); //interrupt for RX data input
    int_start_StartEx(startHandler);    //interrupt start button
    int_cancel_StartEx(cancelHandler);  //interrupt cancel button
    
    
    while(1)
    {  
        led_indication();
        display_indication();
    }
}


void led_indication()
{
    int i;
    
    if(skier)timer_Start();   //start blinc led if number spotrsmen >0
    else timer_Stop();
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

void display_indication()
{
    char display_buff[16];      
    sprintf(display_buff,"    time     num");
    display_Position(0, 0);
    display_PrintString(display_buff);
    sprintf(display_buff,"%s  %d ",finish_time, skier);
    display_Position(1,0);
    display_PrintString(display_buff);
}