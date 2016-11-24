#ifndef _BLUETOOTH_H
    #define _BLUETOOTH_H
    
    #include "project.h"
    #include "lib_DB\database.h"
    
    #define DEBUG_BLE
    
    #define LENGHT_DATA_BUFFER 4
    #define LENGHT_STATUS_BUFFER 7
    
    #define BLE_SEND_HOUR 0
    #define BLE_SEND_MIN 1
    #define BLE_SEND_SEC 2
    #define BLE_SEND_MS 3
    
    typedef enum {STATUS_SYSTEM, STATUS_SD_CARD, STATUS_NETWORK} BLEStatusFlag; 
    
    void BLE_start(void);
    void BLE_processEvents(void);
    
    uint32_t BLE_getUnixTime(void);
    
    /*send time skier for User profile*/
    void BLE_sendOneSkierTime(skierDB_El *data);
    void BLE_sendOneSkierTimeStart(uint64_t unixTime, uint16_t mills);
    
    /*send time skier for Admin profile*/
    void BLE_sendAllSkierTime(uint16_t sendIdSkier,uint16_t sendStartTime[],
                                uint16_t sendFinishTime[], uint16_t sendResultTime[],
                                uint8_t sendStatus[]);
    
#endif

/* [] END OF FILE */
