#ifndef _BLUETOOTH_H
    #define _BLUETOOTH_H
    
    #include "project.h"
    #include "lib_DB\database.h"
    
//    #define DEBUG_BLE
    
    #define LENGHT_DATA_BUFFER 4
    #define LENGHT_STATUS_BUFFER 7
    
    #define BLE_SEND_HOUR 0
    #define BLE_SEND_MIN 1
    #define BLE_SEND_SEC 2
    #define BLE_SEND_MS 3
    
    #define BLE_SEND_SYSTEM_STATUS  0
    #define BLE_SEND_SD_STATUS      2
    #define BLE_SEND_NETWORK_STATUS 1
    
    typedef enum {STATUS_OK, STATUS_ERROR} BLEStatusFlag; 

    
    void BLE_start(void);
    void BLE_processEvents(void);
    
    uint32_t BLE_getUnixTime(void);
    uint8_t BLE_getFlagAdminOnly(void);
    
    /*send time skier for User profile*/
    void BLE_sendOneSkierTimeResult(skierDB_El *data, uint8_t idSkier,
                            uint8_t numSkierOnWay, uint8_t maxSkierOnWay);
    
    void BLE_sendOneSkierTimeStart(uint64_t unixTime, uint16_t mills, uint8_t idSkier,
                                    uint8_t numSkierOnWay, uint8_t maxSkierOnWay);
    
    /*send time skier for Admin profile*/
    void BLE_sendOneSkierTimeAll(uint16_t sendIdSkier,uint16_t sendStartTime[],
                                uint16_t sendFinishTime[], uint16_t sendResultTime[]);
    
    void BLE_sendSystemStatus(BLEStatusFlag systemStatus);
    void BLE_sendSDcardStatus(BLEStatusFlag SDcardStatus);
    void BLE_sendNetworkStatus(BLEStatusFlag networkStatus);
    void BLE_sendNumSkierOnWay(uint8_t numSkier, uint8_t maxSkier);
    
#endif

/* [] END OF FILE */
