#include "common.h"

extern void *D_0062C0E8;
extern void func_001003D0(void *a0);

void GetStageDifferenceMatrix(void) {
    func_001003D0(D_0062C0E8);
}

extern void func_0023A410(void *a0);
extern int D_006D5F98[];

void StageOrientGet2(void) {
    func_0023A410(D_006D5F98);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", OtherStagePositionGet);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", StageOrientInit);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", StageOrientGet);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", func_0019AC48);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/stage_orient", func_0019AE20);
