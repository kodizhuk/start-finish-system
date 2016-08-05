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
#include <Cylib.h>

#define NO_ERROR    1
#define ERROR       0

/*timeout*/
#define TIMEOUT_NEXT_SKIER  1000
#define TIMEOUT_STATE   500
#define TIMEOUT_USER_READ_INFO  500

uint32_t SystemInit(void);
uint32_t Ready(void);
uint32_t CheckGate(void);
uint32_t SaveResult(void);
uint32_t ReinitDB(void);

/* [] END OF FILE */
