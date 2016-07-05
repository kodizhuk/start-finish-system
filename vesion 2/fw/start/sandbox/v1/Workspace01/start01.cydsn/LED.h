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

CY_ISR(LedHandler); // Interrupt Timer 

void LedInit(void);

void LedBlink(uint16_t Frequency);

void SetLedState(uint8_t State) ;

void SetPWMValue(uint8_t Value) ;

extern uint8_t LED_InitValue;

/* [] END OF FILE */
