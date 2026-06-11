#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actDejaChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actDejaDemo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actDejaAfter);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actDejaAfterChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actDeja);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actEnemySleep);

extern void AddWayPointTop(int a0, int a1);
extern int func_00178DB0(int a0);

void func_00205BA8(void) {
    AddWayPointTop(7, 0);
    if (func_00178DB0(0x147) != 0) {
        AddWayPointTop(9, 0);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00205BE8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00205CE8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00205E18);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206128);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_002064E8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_002065F8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_002068A8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206A20);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206D70);

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_00206F18(void) {
    stage_KillPlayBgAnimation(0xA1, 0, -1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206F28);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206FE0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00207098);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00207130);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_002071A8);
