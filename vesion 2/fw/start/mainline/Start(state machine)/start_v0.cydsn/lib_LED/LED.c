#include "LED.h"

uint8_t LED_initValue;

/*******************************************************************************
* Interrupt function name: LedHandler
********************************************************************************
*
* After every interrupt inverts pin state and clear interrupt state. 
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
* Initialization timer for led, 
* and attach interrupt to output 
* timer termial. If LED is already 
* initialised, this function does nothing. 
*
*******************************************************************************/	

void LedInit(void)
{
        Timer_LED_Init();
        if (!LED_initValue)
        {
            Int_Timer_Led_StartEx(LedHandler);
        }
        LED_initValue = 1;
}

/*******************************************************************************
* Function Name: LedBlink
********************************************************************************
*
* Summary:
*  Writes a timer value period of ticks, equivalent transferred 
*  flashing frequency and enable timer. 
*
* Parameters:
*  frequency: Frequency with which LED will be blinking
* Note:
*  Transfered value must be in Hz
*
*******************************************************************************/

void LedBlink(uint16_t frequency)
{
    uint32_t time;
    time = FreqToTicks(frequency);
    Timer_LED_WritePeriod(time);
    Timer_LED_Enable();
}

/*******************************************************************************
* Function Name: SetLedState
********************************************************************************
*
* Summary:
*  Set static state LED indicator and disable timer. 
*
* Parameters:
*  state: Set high or low level on LED. 
* Note:
*  Macro definitions for LED:
*  LED_ENABLE - High level. 
*  LED_DISABLE - Low level. 
*
*******************************************************************************/

void SetLedState(uint8_t state)
{
    Timer_LED_Stop();
    LED_PIN_Write(state);
}

/* [] END OF FILE */
