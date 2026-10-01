#include "fieldCollision.h"
#include "matrixDrive.h"
#include "main.h"

/* the flying object the manager tracks */
static GObj *flyGObj = 0; /* derived name */

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

static inline int clipFlyFloor(char *work, void *pos) /* derived name */
{
    CopyVector(work, pos);
    CopyVector(work + 0x10, pos);
    *(float *)(work + 0x14) += 100000.0f;
    ClipFloorByGObj(work, flyGObj);
    return *(int *)(work + 0x94);
}

inline int InitFlyInfo(GObj *self)
{
    Sub15C *d = self->dobj;
    flyGObj = self;
    d->disp = 0;
    return 0;
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

inline void InitFlyManager(void)
{
    flyGObj = 0;
}

inline int GetFlyLimitClearance(void *pos)
{
    char work[192];

    if (flyGObj != 0) {
        memset(work, 0, 192);
        if (clipFlyFloor(work, pos) != 0) {
            return -getFloorLimitValue(*(int *)(work + 0x98));
        }
    }
    return -10000;
}

inline int GetFlyLimitHeight(FlyLimitInfo *info, void *pos)
{
    char work[192];

    if (flyGObj != 0) {
        memset(work, 0, 192);
        if (clipFlyFloor(work, pos) != 0) {
            info->floorY = *(float *)(work + 0x24);
            info->limitOfs = -getFloorLimitValue(*(int *)(work + 0x98));
            info->limitY = info->floorY + info->limitOfs;
            info->flags = 0;
            return 1;
        }
    }
    return 0;
}
