/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "LED.h"
#include <Timer_LED.h>
#include <Int_Timer_Led.h>
//#include "appGlobal.h"
#ifdef START_MODULE
#include <LED_RED_PIN.h>
#include <LED_GREEN_PIN.h>
#endif
#ifdef FINISH_MODULE
#include <LED_PIN.h>
#endif
// Max pulses in 16-Bit Resolution
#define MAX_TICKS_16BIT                      (65535)

// Frequency Timer for Led in Hz. 
#define FREQ_TIMER_LED                       (1000u)

/*******************************************
    Change Frequency value to count pulses
    Macros which value count pulses
    Arguments
                Freq: Frequency with which want 
                    light LED indicator
    Macro
                FREQ_TIMER_LED : 
                    Input Clock Timer_LED Frequency
    Result 
                Count pulses which need 
                    upload as Period in Timer
                
                Diving 2 because One Period have Low 
                    and Hidh Levels
    
*******************************************/

#define FreqToTicks(Freq)        FREQ_TIMER_LED/(2*Freq)  
CY_ISR_PROTO(LedHandler); /* Interrupt Timer */

uint8_t LED_InitValue;


/*
    Initialization timer and add interrupt to him 
*/
void LedInit(void)
{
    Timer_LED_Init();
    if (!LED_InitValue)
    {
        Int_Timer_Led_StartEx(LedHandler);
    }
    LED_InitValue = 1;
}

/*
    Interrupt handler after lefting time one period light
*/
#ifdef START_MODULE
CY_ISR(LedHandler)
{
    LED_RED_PIN_Write(~LED_RED_PIN_Read());
    Timer_LED_ClearInterrupt(Timer_LED_INTR_MASK_CC_MATCH);
}
#endif 
#ifdef FINISH_MODULE
CY_ISR(LedHandler)
{
    LED_PIN_Write(~LED_PIN_Read());
    Timer_LED_ClearInterrupt(Timer_LED_INTR_MASK_CC_MATCH);
}
#endif

/* 
    Blinking Led with Frequency
    Arguments: 
        uint16_t Frequency: 
        Frequency with which LED will blinking
        Value in Hz
*/
#ifdef START_MODULE
void LedRedBlink(uint16_t Frequency)
{
    uint32_t time_l;
    time_l = FreqToTicks(Frequency);
    Timer_LED_WritePeriod(time_l);
    Timer_LED_Enable();
}
#endif
#ifdef FINISH_MODULE
void LedBlink(uint16_t Frequency)
{
    uint32_t time_l;
    time_l = FreqToTicks(Frequency);
    Timer_LED_WritePeriod(time_l);
    Timer_LED_Enable();
}
#endif

/* 
    Set static state LED indicator
    Arguments: 
        uint8_t State: 
        High or low state.
        High - ENABLE (1u), Low - Disable(0u)
*/
#ifdef START_MODULE
void SetLedsState(uint8_t stateRed, uint8_t stateGreen)
{
    Timer_LED_Stop();
    LED_RED_PIN_Write(stateRed);
    LED_GREEN_PIN_Write(stateGreen);
}
#endif
#ifdef FINISH_MODULE
void SetLedState(uint8_t State)
{
    Timer_LED_Stop();
    LED_PIN_Write(State);
}
#endif

/* [] END OF FILE */
