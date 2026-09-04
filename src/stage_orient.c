#include "common.h"



extern int D_006DC718[];
extern void audioDecSendToIOP();
extern void RotateThreadReadyQueue();
extern int D_00633DF8;
void GetStageDifferenceMatrix(void)
{
    RotateThreadReadyQueue(D_00633DF8);
}

void StageOrientGet2(void)
{
    audioDecSendToIOP(D_006DC718);
}

INCLUDE_ASM("asm/nonmatchings/src/stage_orient", OtherStagePositionGet);

INCLUDE_ASM("asm/nonmatchings/src/stage_orient", StageOrientInit);

INCLUDE_ASM("asm/nonmatchings/src/stage_orient", StageOrientGet);

INCLUDE_ASM("asm/nonmatchings/src/stage_orient", func_0019D678);

INCLUDE_ASM("asm/nonmatchings/src/stage_orient", movie_end);

