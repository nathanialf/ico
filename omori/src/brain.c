#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainAddLevelGirl);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainInit);

void OverrideBrainStatusByGObj(int *p) {
    *p = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainStatusDefaultSet);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainLevelProcess);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainGetTarget);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainStatusSet);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainStatusDel);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainGetLevel);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainClsTargetLevel);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainInitGirlSet);
