#include "common.h"


extern int func_00240EA0();
extern int D_006332A4;
extern void actClipCollisionCore();
INCLUDE_ASM("asm/nonmatchings/src/chandelier", ChandelierGeo);

INCLUDE_ASM("asm/nonmatchings/src/chandelier", ChandelierDL);

INCLUDE_ASM("asm/nonmatchings/src/chandelier", InitChandelierGeo);

int func_001C34B8(void)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/chandelier", func_001C34C0);

int func_001C36E0(void) {
    int v = func_00240EA0(0, 0, 0, 0, (int)&actClipCollisionCore, 0, 0);
    D_006332A4 = v;
    return v;
}

INCLUDE_ASM("asm/nonmatchings/src/chandelier", func_001C3720);

