#include "common.h"



extern int D_006DC718[];
extern void func_0023DEB0();
extern void func_001003D0();
extern int D_00633DF8;
void GetStageDifferenceMatrix(void)
{
    func_001003D0(D_00633DF8);
}

void StageOrientGet2(void)
{
    func_0023DEB0(D_006DC718);
}

INCLUDE_ASM("asm/nonmatchings/src/stage_orient", OtherStagePositionGet);

INCLUDE_ASM("asm/nonmatchings/src/stage_orient", StageOrientInit);

INCLUDE_ASM("asm/nonmatchings/src/stage_orient", StageOrientGet);

INCLUDE_ASM("asm/nonmatchings/src/stage_orient", func_0019D678);

INCLUDE_ASM("asm/nonmatchings/src/stage_orient", func_0019D850);

