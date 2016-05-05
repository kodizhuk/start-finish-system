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

int capsenseNitifity;
int bleConected = 0;
CYBLE_CONN_HANDLE_T connectionHandler;

void stakHandler(uint32 eventCode, void *eventParam)
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReg;
    switch (eventCode)
    {
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED :
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            bleConected = 0;
            break;
        case CYBLE_EVT_GATT_CONNECT_IND:
            connectionHandler = *(CYBLE_CONN_HANDLE_T *)eventParam;
            break;
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReg = (CYBLE_CONN_HANDLE_T *)eventParam;
            if(wrReg->handleValPair.attrHandle == CYBLE_CAPSENSE_SLIDER_SLIDERCCCD_DESC_HANDLE)
            {
                CyBle_GattsWriteAttributeValue(&wrReg->handleValPair,0,&connectionHandler,CYBLE_GATT_DB_LOCALLY_INITIATED);
                capsenseNitifity = wrReg->handleValPair.value.val[0];
            }
            CyBle_GattsWriteRsp(connectionHandler);
            break;
            default:
            break;
    }
}
int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    CapSense_ScanEnabledWidgets();
    
    CyBle_Start(stakHandler);

    for(;;)
    {
        CyBle_ProcessEvents();
        if(!CapSense_IsBusy() && bleConected)
        {
            uint8 pos = (uint8)CapSense_GetCentroidPos(CapSense_LINEAR_SLIDERS_POS_FILTERS_MASK);
            CapSense_UpdateEnabledBaselines();
            CapSense_ScanEnabledWidgets();
            if(pos!=0xFF)
            {  
                CYBLE_GATTS_HANDLE_VALUE_NTF_T capsenseHandler;
                capsenseHandler.attrHandle = CYBLE_CAPSENSE_SLIDER_CHAR_HANDLE;
                capsenseHandler.value.val = &pos;
                capsenseHandler.value.len = 1;
                CyBle_GattsWriteAttributeValue(&capsenseHandler,0,&connectionHandler,0);
                if(capsenseNitifity)
                {
                    CyBle_GattsNotification(connectionHandler,&capsenseHandler);
                    
                }
            }
        }
    }
}

/* [] END OF FILE */
