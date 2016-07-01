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

uint8_t LED_InitValue;

void LedInit(void)
{
        Timer_LED_Init();
        if (!LED_InitValue)
        {
            Int_Timer_Led_StartEx(LedHandler);
        }
        LED_InitValue = 1;
}

CY_ISR(LedHandler)
{
    LED_PIN_Write(~LED_PIN_Read());
    Timer_LED_ClearInterrupt(Timer_LED_INTR_MASK_CC_MATCH);
}

void LedBlink(uint16_t Frequency)
{
    uint32_t time_l;
    time_l = FreqToTicks(Frequency);
    Timer_LED_WritePeriod(time_l);
    Timer_LED_Enable();
    time_l = Timer_LED_ReadPeriod();
}

void SetPWMValue(uint8_t Value)
{
    /* TBD: Implementation Here; */
}

void SetLedState(uint8_t State)
{
    Timer_LED_Stop();
    LED_PIN_Write(State);
}

/* [] END OF FILE */
