#ifndef _NETWORK_H
    #define _NETWORK_H

#include <CyLib.h>

//#define DEBUG_INFO
//#define DEBUG_TIME
//#define DEBUG_NTP


#define READ_OK     1
#define NO_READ     0
#define WRITE_OK    1
#define NO_WRITE    0
#define READY       1
#define NO_READY    0

/*network status*/
#define NETWORK_CONN        1
#define NETWORK_DISCONN     0
#define REBOOT              (0xFF)
#define NO_REBOOT           (0xFE)

/*for NTP protocol*/
#define TIME_SYNC_ERR       1
#define TIME_SYNC_OK        0




void     InitNetwork(void);
uint32_t NetworkStatus(void);
void     SendSkierStart(uint64_t unixTimeStart, uint32_t recentMs);
uint32_t FinWriteInDB(void);
uint32_t FinReady(void);
uint32_t IsRebootFinishFlag(void);
void     SetRebootFlag(void);
void     ClearRebootFlag(void);


void     SendData(void);
uint32_t ReceiveData(void);

/*NTP protocol sync*/
uint32_t     NTPsync(void);


#endif
/* [] END OF FILE */
