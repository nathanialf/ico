#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainAddLevelGirl);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainInit);

void OverrideBrainStatusByGObj(int *p) {
    *p = 0;
}

float brainStatusDefaultSet(void *a0, void *a1) {
    if (*(void **)((char *)a0 + 0x4) == a1) {
        return *(float *)((char *)a1 + 0x4) + *(float *)((char *)a0 + 0x14);
    }
    return *(float *)((char *)a1 + 0x4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainLevelProcess);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainGetTarget);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainStatusSet);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainStatusDel);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainGetLevel);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainClsTargetLevel);

extern int D_00286A9C[];

void brainInitGirlSet(void) {
    D_00286A9C[0] = 1;
}
