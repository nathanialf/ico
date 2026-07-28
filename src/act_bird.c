#include "common.h"



extern void func_00243B60(void *dst, void *src);
extern int InitParticleLayoutGeo();
extern int iosOmBeforeFuncStandard();
INCLUDE_ASM("asm/nonmatchings/src/act_bird", interp_vector_sa);

void birdBeforeFunc(int a0, int a1, int a2, int a3)
{
    iosOmBeforeFuncStandard(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/act_bird", trans_bird);

INCLUDE_ASM("asm/nonmatchings/src/act_bird", subBirdBrainMain);

INCLUDE_ASM("asm/nonmatchings/src/act_bird", Debug_WireString_Bird);

void Debug_StickControl(void) {}

INCLUDE_ASM("asm/nonmatchings/src/act_bird", BirdGeo);

void BirdDL(int a0, int a1)
{
    if (a0 >= 0) {
        int v;
        v = InitParticleLayoutGeo(a0);
        func_00243B60(v + 0x40, a1);
    }
}

