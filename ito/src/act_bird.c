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

extern void *InitParticleLayoutGeo(void);
extern void func_00240080(void *a0, void *a1);

void BirdDL(int a0, void *a1) {
    if (a0 >= 0) {
        void *r = InitParticleLayoutGeo();
        func_00240080((char *)r + 0x40, a1);
    }
}
