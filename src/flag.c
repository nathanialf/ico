#include "common.h"


extern int D_006333D8;
extern int D_00632DB4;
extern int ClipWallDebug();
INCLUDE_ASM("asm/nonmatchings/src/flag", InitFlagGeo);

int FlagGeo(char *self) {
    char *p = *(char **)(self + 0x4);
    *(int *)(p + 0x30) = 1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/flag", FlagDL);

INCLUDE_ASM("asm/nonmatchings/src/flag", func_001CFB58);

INCLUDE_ASM("asm/nonmatchings/src/flag", func_001D00F8);

INCLUDE_ASM("asm/nonmatchings/src/flag", func_001D01E8);

void func_001D03A0(void)
{
    int v0 = D_00632DB4;
    int a0 = D_006333D8;
    if (v0 == 0) {
        return;
    }
    if (a0 == 0) {
        return;
    }
    return ClipWallDebug(a0, 0);
}

int func_001D03C8(int *self)
{
    int *p = (int *)self[0x57];
    D_006333D8 = self;
    p[0x1D] = 0;
    return 0;
}

