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
#ifndef _CY_LED_H
#define _CY_LED_H
    
#include <stdint.h>
#include <CyLib.h>

#define FREQ_INIT_BLINK         (10u)
#define FREQ_ERR_BLINK         (3u)

#define LED_ENABLE              (1u)
#define LED_DISABLE             (0u)

void LedInit(void);
void LedBlink(uint16_t Frequency);
void SetLedState(uint8_t State);

extern uint8_t LED_InitValue;
#endif
/* [] END OF FILE */
