/* ========================================
 *
 * Copyright CYPRESS, 2016 YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF CYPRESS.
 *
 * ========================================
 Using TIMER, DIGITAL PIN AND INTERRUPT
 Name components
 Timer     : Timer_LED
 Pin       : LED_PIN
 Interrupt : Int_Timer_Led
*/

#include <stdint.h>
#include <CyLib.h>
#include <Timer_LED.h>
#include <LED_PIN.h>
#include <Int_Timer_Led.h>

// Max pulses in 16-Bit Resolution
#define MAX_TICKS_16BIT                      (65535)

// Frequency Timer for Led in Hz. 
#define FREQ_TIMER_LED                       (1000u)

#define FREQ_INIT_BLINK         (10u)
#define FREQ_ERR_BLINK         (3u)

#define LED_ENABLE              (1u)
#define LED_DISABLE             (0u)

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

/*
    Initialization timer and add interrupt to him 

*/

void LedInit(void);

/* 
    Blinking Led with Frequency
    Arguments: 
        uint16_t Frequency: 
        Frequency with which LED will blinking
        Value in Hz
*/

void LedBlink(uint16_t Frequency);
/* 
    Set static state LED indicator
    Arguments: 
        uint8_t State: 
        High or low state.
        High - ENABLE (1u), Low - Disable(0u)
*/

void SetLedState(uint8_t State) ;

/*
    PWM. Different light; 
    TBD Implementation
*/
void SetPWMValue(uint8_t Value) ;

extern uint8_t LED_InitValue;

/*
    Interrupt handler after lefting time one period light
*/
CY_ISR(LedHandler); // Interrupt Timer 

/* [] END OF FILE */
