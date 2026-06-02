#include "common.h"

extern void playSEConditionID(int a0, int a1);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", CreateWaySystemManagerGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", RequestGetWayBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", actWaySystemCore);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EF310);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EF360);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EF380);

void func_001EF3B0(int a0) {
    playSEConditionID(a0, 0x42);
}

void func_001EF3B8(int a0) {
    playSEConditionID(a0, 0x57);
}

void func_001EF3C0(int a0) {
    playSEConditionID(a0, 0x58);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EF3C8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EF4F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EF8E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/waySystemManager", func_001EFAF8);
