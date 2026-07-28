#include "common.h"



extern void stage_KillPlayBgAnimation();
extern void AddWayPointTop();
extern int func_0017B230(int a0);
INCLUDE_ASM("asm/nonmatchings/src/deja", actDejaChk);

INCLUDE_ASM("asm/nonmatchings/src/deja", actDejaDemo);

INCLUDE_ASM("asm/nonmatchings/src/deja", actDejaAfter);

INCLUDE_ASM("asm/nonmatchings/src/deja", actDejaAfterChk);

INCLUDE_ASM("asm/nonmatchings/src/deja", actDeja);

INCLUDE_ASM("asm/nonmatchings/src/deja", actEnemySleep);

void func_00208740(void)
{
    AddWayPointTop(7, 0);
    if (func_0017B230(0x148) != 0) {
        AddWayPointTop(9, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00208780);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00208880);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_002089B0);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00208CC0);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209080);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209190);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209440);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_002095B8);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209908);

void func_00209AB0(void)
{
    stage_KillPlayBgAnimation(0xA2, 0, -1);
}

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209AC0);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209B78);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209C30);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209CC8);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209D40);

