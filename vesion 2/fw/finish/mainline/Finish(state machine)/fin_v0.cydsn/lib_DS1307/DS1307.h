#ifndef _DS1307_H
    #define _DS1307_H
    
#include <CyLib.h>

uint64_t DS1307_GetUnixTime(void);
void DS1307_SetUnixTime(uint64_t time);
void DS1307_Start(void);
void DS1307_Stop(void);

#endif  /*_DS1307_H*/

/* [] END OF FILE */
