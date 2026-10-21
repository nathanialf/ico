#include "fieldCollision.h"
#include "matrixDrive.h"
#include "main.h"
#include "flyManager.h"
#include "debug.h"
#include <string.h>

static inline int getFloorLimitValue(int attr) /* derived name */
{
    int type = attr & 0xF;

    if (type == 1) {
        return 0;
    }
    if (type == 15 && (stage_no == 19 || stage_no == 28)) {
        type = 20;
    }
    return type * 100;
}
