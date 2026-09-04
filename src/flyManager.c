#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/flyManager", DispFlyInfo);
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
