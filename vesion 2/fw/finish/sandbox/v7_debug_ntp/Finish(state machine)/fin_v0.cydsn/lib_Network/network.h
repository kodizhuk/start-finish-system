#ifndef _NETWORK_H
    #define _NETWORK_H
  
#include <CyLib.h>

//#define DEBUG_INFO
//#define DEBUG_TIME
#define DEBUG_NTP
    
    
#define READ_OK         1
#define NO_READ         0
#define WRITE_OK        1
#define NO_WRITE        0
#define FIN_READY       1
#define FIN_NO_READY    0

#define NEW_SKIER_IN_TARCK   1

/*network status*/
#define NETWORK_CONNECT        1
#define NETWORK_DISCONNECT     0
#define REBOOT              (0xFF)
#define NO_REBOOT           (0xFE)

#define TIME_SYNC_ERR       1
#define TIME_SYNC_OK        0


void     InitNetwork(void);
uint32_t NetworkStatus(void);
void     SendFinStatus(uint32_t ready);

/*reboot flag*/
uint32_t IsRebootStartFlag(void);
void     SetRebootFlag(void);
void     ClearRebootFlag(void);

void     SendData(void);
uint32_t ReceiveData(void);


/*NTP protocol*/
uint32_t NTPsync(void);

#endif
/* [] END OF FILE */
