#ifndef _LOG_RESULT_H
    #define _LOG_RESULT_H

#include <CyLib.h>
#include "lib_DB\database.h"
#include "lib_Fat\ff.h"


uint32_t LogStart(void);
uint32_t WriteSkierResult(skierDB_El *data);

#endif
/* [] END OF FILE */
