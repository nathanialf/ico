#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/act_bird", interp_vector_sa);

extern void iosOmBeforeFuncStandard(void *a0);

void birdBeforeFunc(void *a0) {
    iosOmBeforeFuncStandard(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/act_bird", trans_bird);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/act_bird", subBirdBrainMain);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/act_bird", Debug_WireString_Bird);

void Debug_StickControl(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/act_bird", BirdGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/act_bird", BirdDL);
