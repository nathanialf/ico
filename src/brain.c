#include "common.h"


extern int D_0028A89C[];
INCLUDE_ASM("asm/nonmatchings/src/brain", brainAddLevelGirl);

INCLUDE_ASM("asm/nonmatchings/src/brain", brainInit);

void OverrideBrainStatusByGObj(char *self) {
    *(int *)(self + 0x0) = 0;
}

float brainStatusDefaultSet(void *a0, void *a1)
{
    if (*(void **)((char *)a0 + 4) == a1) {
        return *(float *)((char *)a1 + 4) + *(float *)((char *)a0 + 0x14);
    }
    return *(float *)((char *)a1 + 4);
}

INCLUDE_ASM("asm/nonmatchings/src/brain", brainLevelProcess);

INCLUDE_ASM("asm/nonmatchings/src/brain", brainGetTarget);

INCLUDE_ASM("asm/nonmatchings/src/brain", brainStatusSet);

INCLUDE_ASM("asm/nonmatchings/src/brain", brainStatusDel);

INCLUDE_ASM("asm/nonmatchings/src/brain", brainGetLevel);

INCLUDE_ASM("asm/nonmatchings/src/brain", brainClsTargetLevel);

void brainInitGirlSet(void) {
    D_0028A89C[0] = 1;
}

