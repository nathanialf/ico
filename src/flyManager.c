#include "common.h"

extern int D_0063B234;
extern int D_0063B898;
extern int DrawGObjFloorCollision();

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
extern int D_0063B898;

int InitFlyInfo(int *self)
{
    int *p = (int *)self[0x57];
    D_0063B898 = self;
    p[0x1D] = 0;
    return 0;
}
void InitFlyManager(void) {
    D_0063B898 = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/flyManager", GetFlyLimitHeight);
INCLUDE_ASM("asm/nonmatchings/src/flyManager", GetFlyLimitClearance);
