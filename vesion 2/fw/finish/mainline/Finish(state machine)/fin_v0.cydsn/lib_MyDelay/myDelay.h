
#include <CyLib.h>
#include <AppDelay.h>
#include <SDinsert.h>
#include "lib_DB\logResult.h"
#include "lib_Network\network.h"
#include "lib_Display\display.h"

#define MIN_DELAY_MS    150
#define WRITE_ERROR     1
#define WRITE_NO_ERROR  0

//static uint32_t networkStatus;
static uint16_t writeFlag;

//static int numAttemps ;
//static int noConnect;

void MyDelay(uint32_t miliseconds);

/*user func*/
static void UserFunc_1(void);
static void UserFunc_2(void);
static void UserFunc_3(void);
static void UserFunc_4(void);