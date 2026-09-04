#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainProcess);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainGetTargetGeneratorFromLabel);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainGetTarget);
extern int D_0063ABDC;
extern int D_0063ABE0;
extern int D_0063C2CC;
extern int D_0063C2D0;
extern int D_006E6750[];

void eBrainInit(void)
{
    int *p = D_006E6750;
    int i;
    D_0063ABE0 = 0;
    D_0063ABDC = 0;
    D_0063C2CC = 0;
    p = (int *)((char *)p + 0x37C);
    D_0063C2D0 = 0;
    i = 0x1F;
    do {
        *p = 0;
        p = (int *)((char *)p - 0x1C);
        i--;
    } while (i >= 0);
}
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainStatusSet);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainSendMes);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", GetStageFromLabel);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainGetTargetGeneratorFromLabelStage);
