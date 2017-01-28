#ifndef _DISPALY_H
    #define _DISPALY_H

#include <CyLib.h>


/*indicator sd card*/
typedef enum {SD_INSERT, SD_NO_INSERT} SDindicator; 
typedef enum {CONNECT, DISCONNECT} NetworkIndicator; 


void DisplayStart(void);	
void Display(char *message);
void DisplayIndicatorSD(SDindicator indicator);
void DisplayIndicatorNetwork(NetworkIndicator indicator);
void DisplayRealTime(void);
void DisplayLoading(uint32_t numLoad);
void DisplayTestMode(uint8_t state);


#endif
/* [] END OF FILE */