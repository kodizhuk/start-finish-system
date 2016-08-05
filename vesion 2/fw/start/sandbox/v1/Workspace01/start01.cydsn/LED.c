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

/*******************************************************************************
*
* Interrupt handler after lefting time one period light
*
*******************************************************************************/
CY_ISR(LedHandler)
{
    LED_PIN_Write(~LED_PIN_Read());
    Timer_LED_ClearInterrupt(Timer_LED_INTR_MASK_CC_MATCH);
}


/*******************************************************************************
* Function name: LedInit
********************************************************************************
*
* Initialization timer and add interrupt to him 
*
*******************************************************************************/
void LedInit(void)
{
        Timer_LED_Init();
        if (!LED_InitValue)
        {
            Int_Timer_Led_StartEx(LedHandler);
        }
        LED_InitValue = 1;
}

/*******************************************************************************
* Function name: LedBlink
********************************************************************************
*
* Blinking Led with Frequency
*
*    Parameters: 
*        uint16_t Frequency: 
*        Frequency with which LED will blinking
*        Value in Hz
*
*******************************************************************************/	
void LedBlink(uint16_t Frequency)
{
    uint32_t time_l;
    time_l = FreqToTicks(Frequency);
    Timer_LED_WritePeriod(time_l);
    Timer_LED_Enable();
    time_l = Timer_LED_ReadPeriod();
}

/*******************************************************************************
* Function name: SetLedState
********************************************************************************
*
*    Set static state LED indicator
*    Parameters: 
*        uint8_t State: 
*        High or low state.
*        High - ENABLE (1u), Low - Disable(0u)
*
*******************************************************************************/
void SetLedState(uint8_t State)
{
    Timer_LED_Stop();
    LED_PIN_Write(State);
}

/*******************************************************************************
* Function name: SetPWMValue
********************************************************************************
*
*    PWM. Different light; 
*    TBD Implementation
*
*******************************************************************************/
void SetPWMValue(uint8_t Value)
{
    /* TBD: Implementation Here; */
}

/* [] END OF FILE */
