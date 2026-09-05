#include "common.h"

extern int D_0063B234;
extern int D_0063B898;
extern int DrawGObjFloorCollision();
extern void memset(void *a0, int a1, int a2);
extern void CopyVector(void *dst, void *src);
extern void ClipFloorByGObj(void *work, int gobj);
extern int stage_no;
typedef struct {
    float floorY;
    float limitY;
    float limitOfs;
    int flags;
} FlyLimitInfo;
/* prototypes: their order is the inline tail's emission order */
int InitFlyInfo(int *self);
void InitFlyManager(void);
int GetFlyLimitHeight(FlyLimitInfo *info, void *pos);
int GetFlyLimitClearance(void *pos);
static inline int getFloorLimitValue(int attr)
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
static inline int clipFlyFloor(char *work, void *pos)
{
    CopyVector(work, pos);
    CopyVector(work + 0x10, pos);
    *(float *)(work + 0x14) += 100000.0f;
    ClipFloorByGObj(work, D_0063B898);
    return *(int *)(work + 0x94);
}
inline int InitFlyInfo(int *self)
{
    int *p = (int *)self[0x57];
    D_0063B898 = self;
    p[0x1D] = 0;
    return 0;
}
void DispFlyInfo(void)
{
    int v0 = D_0063B234;
    int a0 = D_0063B898;
    if (v0 == 0) {
        return;
    }
    if (a0 == 0) {
        return;
    }
    return DrawGObjFloorCollision(a0, 0);
}
inline void InitFlyManager(void) {
    D_0063B898 = 0;
}
inline int GetFlyLimitClearance(void *pos)
{
    char work[0xC0];

    if (D_0063B898 != 0) {
        memset(work, 0, 0xC0);
        if (clipFlyFloor(work, pos) != 0) {
            return -getFloorLimitValue(*(int *)(work + 0x98));
        }
    }
    return -10000;
}
inline int GetFlyLimitHeight(FlyLimitInfo *info, void *pos)
{
    char work[0xC0];

    if (D_0063B898 != 0) {
        memset(work, 0, 0xC0);
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
