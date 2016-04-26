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
#include <project.h>

void Stack_Handler(uint32 eventCode, void *eventParam)
{
    switch(eventCode)
    {
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;
    }
}

void IasHandler(uint32 eventCode, void *eventParam)
{
    CYBLE_IAS_CHAR_VALUE_T *param = (CYBLE_IAS_CHAR_VALUE_T *)eventParam;
    if(*param->value->val == 0)
        PWM_WriteCompare(0);
    else if(*param->value->val == 1)
        PWM_WriteCompare(500);
    else PWM_WriteCompare(1000);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    CyBle_Start(Stack_Handler);
    CyBle_IasRegisterAttrCallback(IasHandler);
    
    PWM_Start();

    for(;;)
    {
        CyBle_ProcessEvents();
    }
}

/* [] END OF FILE */
