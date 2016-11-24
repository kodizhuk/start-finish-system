#include <lib_BLE/bluetooth.h>
#include "stdio.h"
#include "project.h"

#define LENGHT_DATA_BUFFER 4
#define LENGHT_STATUS_BUFFER 7

int notifycaiton;
uint32_t bleUnixTime = 0;

uint16_t sendIdSkier = 0;
uint16_t sendBufferStart[LENGHT_DATA_BUFFER];
uint16_t sendBufferFinish[LENGHT_DATA_BUFFER];
uint16_t sendBufferResult[LENGHT_DATA_BUFFER];
uint8_t sendBufferStatus[LENGHT_STATUS_BUFFER];

char uartBuffer[30];

void updateData(void);


void BleCallBack(uint32 event, void* eventParam)
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;

    switch(event)
    {
        /* if there is a disconnect or the stack just turned on from a reset then start the advertising and turn on the LED blinking */
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            notifycaiton = 0;
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            pwm_Start();
        break;
        
        /* when a connection is made*/    
        case CYBLE_EVT_GATT_CONNECT_IND:
            pwm_Stop();
            updateData();
		break;

        /* handle a write request */
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;	
            
            /* request write the unixTime value */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SFSYSTEMSERVICE_UNIXTIME_CHAR_HANDLE)
            {
                /* only update the value and write the response if the requested write is allowed */
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    int i;
                    bleUnixTime = 0;
                    for(i=3;i>=0;i--)
                    {
                        uint8_t tmpData;
                        tmpData = wrReqParam->handleValPair.value.val[i];
                        bleUnixTime = (bleUnixTime << 8) | tmpData;
                    }
                    
                    #ifdef DEBUG_BLE
                        sprintf(uartBuffer,"unix: %d",bleUnixTime);
                        SW_UART_DEBUG_PutString(uartBuffer);
                    #endif
                    
                    CyBle_GattsWriteRsp(cyBle_connHandle);
                }
            }
            
            /* request to update the  notification */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SFSYSTEMSERVICE_ID_ID_CCCD_DESC_HANDLE ||
            wrReqParam->handleValPair.attrHandle == CYBLE_SFSYSTEMSERVICE_TIME_START_TIMESTARTCCCD_DESC_HANDLE ||
            wrReqParam->handleValPair.attrHandle == CYBLE_SFSYSTEMSERVICE_TIME_FINISH_TIMEFINISHCCCD_DESC_HANDLE ||
            wrReqParam->handleValPair.attrHandle == CYBLE_SFSYSTEMSERVICE_TIME_RESULT_TIMERESULTCCCD_DESC_HANDLE ||
            wrReqParam->handleValPair.attrHandle == CYBLE_SFSYSTEMSERVICE_SYSTEM_STATUS_STATUSCCCD_DESC_HANDLE) 
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                notifycaiton = wrReqParam->handleValPair.value.val[0] & 0x01;
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
			break;  
        
        default:
            break;
    }
} 

/***************************************************************
 * Function to update the id skier state in the GATT database
 **************************************************************/
void updateData(void)
{
    CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;
    
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;
    
    tempHandle.attrHandle = CYBLE_SFSYSTEMSERVICE_ID_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *) &sendIdSkier;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );  
    if (notifycaiton  )
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
        
    tempHandle.attrHandle = CYBLE_SFSYSTEMSERVICE_TIME_START_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *) &sendBufferStart;
    tempHandle.value.len = 8;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );  
    if (notifycaiton  )
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
    
    tempHandle.attrHandle = CYBLE_SFSYSTEMSERVICE_TIME_FINISH_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *) &sendBufferFinish;
    tempHandle.value.len = 8;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );  
    if (notifycaiton  )
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle); 
    
    tempHandle.attrHandle = CYBLE_SFSYSTEMSERVICE_TIME_RESULT_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *) &sendBufferResult;
    tempHandle.value.len = 8;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );  
    if (notifycaiton  )
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
        
    tempHandle.attrHandle = CYBLE_SFSYSTEMSERVICE_SYSTEM_STATUS_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *) &sendBufferStatus;
    tempHandle.value.len = 7;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );  
    if (notifycaiton  )
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
}

static void updateTimeOneSkier(void)
{
    CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;
    
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;
    
    tempHandle.attrHandle = CYBLE_SFSYSTEMSERVICE_ID_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *) &sendIdSkier;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );
    if (notifycaiton  )
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
        
    tempHandle.attrHandle = CYBLE_SFSYSTEMSERVICE_TIME_START_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *) &sendBufferStart;
    tempHandle.value.len = 8;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );  
    if (notifycaiton  )
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
    
    tempHandle.attrHandle = CYBLE_SFSYSTEMSERVICE_TIME_FINISH_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *) &sendBufferFinish;
    tempHandle.value.len = 8;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );  
    if (notifycaiton  )
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle); 
    
    tempHandle.attrHandle = CYBLE_SFSYSTEMSERVICE_TIME_RESULT_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *) &sendBufferResult;
    tempHandle.value.len = 8;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED );  
    if (notifycaiton  )
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
}

void BLE_start(void)
{
    CyBle_Start(BleCallBack);
    
    #ifdef DEBUG_BLE
        SW_UART_DEBUG_Start();
        SW_UART_DEBUG_PutString("Im ready\n\r");
    #endif
}


void BLE_processEvents(void)
{
    CyBle_ProcessEvents();
    CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
}


uint32_t BLE_getUnixTime(void)
{
    if(bleUnixTime == 0)
    {
        return 0;
    }
    else
    {
        return bleUnixTime;
    }
}

void BLE_sendOneSkierTime(skierDB_El *data)
{   
    RTC_DATE_TIME time;
    
    /*read unix time*/
    RTC_UnixToDateTime(&time, data->unixStartSkier, RTC_24_HOURS_FORMAT);
    sendBufferStart[BLE_SEND_HOUR] = RTC_GetHours(time.time);
    sendBufferStart[BLE_SEND_MIN] = RTC_GetMinutes(time.time);
    sendBufferStart[BLE_SEND_SEC] = RTC_GetSecond(time.time);
    sendBufferStart[BLE_SEND_MS] = data->millsStartSkier;
    
    RTC_UnixToDateTime(&time, data->unixFinishSkier, RTC_24_HOURS_FORMAT);
    sendBufferFinish[BLE_SEND_HOUR] = RTC_GetHours(time.time);
    sendBufferFinish[BLE_SEND_MIN] = RTC_GetMinutes(time.time);
    sendBufferFinish[BLE_SEND_SEC] = RTC_GetSecond(time.time);
    sendBufferFinish[BLE_SEND_MS] = data->millsFinishSkier;
    
    uint16_t minResult = (data->secondsWay)/60;
    sendBufferResult[BLE_SEND_HOUR] = 0;
    sendBufferResult[BLE_SEND_MIN] = minResult;
    sendBufferResult[BLE_SEND_SEC] = (data->secondsWay) - minResult*60;
    sendBufferResult[BLE_SEND_MS] = data->millsWay;
    
    //updateTimeOneSkier();
    updateData();
}

void BLE_sendOneSkierTimeStart(uint64_t unixTime, uint16_t mills)
{
    RTC_DATE_TIME time;
    
    /*read unix time*/
    RTC_UnixToDateTime(&time, unixTime, RTC_24_HOURS_FORMAT);
    sendBufferStart[0] = RTC_GetHours(time.time);
    sendBufferStart[1] = RTC_GetMinutes(time.time);
    sendBufferStart[2] = RTC_GetSecond(time.time);
    sendBufferStart[3] = mills;
    
    sendBufferFinish[0] = 0;
    sendBufferFinish[1] = 0;
    sendBufferFinish[2] = 0;
    sendBufferFinish[3] = 0;
    
    sendBufferResult[0] = 0;
    sendBufferResult[1] = 0;
    sendBufferResult[2] = 0;
    sendBufferResult[3] = 0;
    
    //updateTimeOneSkier();
    updateData();
}


void BLE_sendAllSkierTime(uint16_t IdSkier,uint16_t sendStartTime[],uint16_t sendFinishTime[],
                          uint16_t sendResultTime[],uint8_t sendStatus[])
{
    sendIdSkier = IdSkier;
    
    sendBufferStart[0] = sendStartTime[0];
    sendBufferStart[1] = sendStartTime[1];
    sendBufferStart[2] = sendStartTime[2];
    sendBufferStart[3] = sendStartTime[3];
    
    sendBufferFinish[0] = sendFinishTime[0];
    sendBufferFinish[1] = sendFinishTime[1];
    sendBufferFinish[2] = sendFinishTime[2];
    sendBufferFinish[3] = sendFinishTime[3];
    
    sendBufferResult[0] = sendResultTime[0];
    sendBufferResult[1] = sendResultTime[1];
    sendBufferResult[2] = sendResultTime[2];
    sendBufferResult[3] = sendResultTime[3];
    
    sendBufferStatus[0] = sendStatus[0];
    sendBufferStatus[1] = sendStatus[1];
    sendBufferStatus[2] = sendStatus[2];
    sendBufferStatus[3] = sendStatus[3];
    sendBufferStatus[4] = sendStatus[4];
    sendBufferStatus[5] = sendStatus[5];
    sendBufferStatus[6] = sendStatus[6];
    
    updateData();
}
/* [] END OF FILE */
