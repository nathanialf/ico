#include "common.h"

extern void *D_0062C0E8;
extern void func_001003D0(void *a0);

void GetStageDifferenceMatrix(void) {
    func_001003D0(D_0062C0E8);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", StageOrientGet2);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", OtherStagePositionGet);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", StageOrientInit);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", StageOrientGet);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", func_0019AC48);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", func_0019AE20);
