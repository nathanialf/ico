#include "fieldCollision.h"
#include "matrixDrive.h"
#include "main.h"

/* the flying object the manager tracks */
static GObj *flyGObj = 0; /* derived name */

#include "flyManager.h"
#include "debug.h"
#include <string.h>
#include "include_asm.h"

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

static inline void *clipFlyFloor(ClipWork *work, void *pos) /* derived name */
{
    CopyVector(work->pt[0], pos);
    CopyVector(work->pt[1], pos);
    work->pt[1][1] += 100000.0f;
    ClipFloorByGObj(work, flyGObj);
    return work->floor.elem;
}

void DispFlyInfo(void)
{
    int test = debug_fly_limit_test;
    GObj *g = flyGObj;
    if (test == 0) {
        return;
    }
    if (g == 0) {
        return;
    }
    DrawGObjFloorCollision(g, 0);
}

INCLUDE_ASM(InitFlyInfo);

INCLUDE_ASM(InitFlyManager);

INCLUDE_ASM(GetFlyLimitHeight);

INCLUDE_ASM(GetFlyLimitClearance);
