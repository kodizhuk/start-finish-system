#ifndef _LOG_RESULT_H
    #define _LOG_RESULT_H

#include <CyLib.h>
#include "..\..\common\lib\lib_DB\database.h"
#include "..\..\common\lib\lib_Fat\ff.h"


uint32_t LogStart(void);
uint32_t WriteSkierResult(skierDB_El *data);

uint32_t ReadSkierResultAndSendBLE(void);
uint32_t GetIDskierFinished(void);

#endif
/* [] END OF FILE */
