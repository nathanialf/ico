#include "common.h"

#include "ico/types.h"
struct GEl { int f0; char _4[0x6C]; };
struct GGeo { char _0[0x24]; struct GEl *f24; char _28[8]; int f30; };

INCLUDE_ASM("asm/nonmatchings/src/gather_effect", GatherEffect_SetGoal);
INCLUDE_ASM("asm/nonmatchings/src/gather_effect", GatherEffect_Proc);
INCLUDE_ASM("asm/nonmatchings/src/gather_effect", GatherEffect_Set);
extern void *GetParticleEffectData(void *a0);

int GatherEffect_InqEnd(int a0) {
    int acc = 0;
    if (a0 >= 0) {
        struct GGeo *geo = (struct GGeo *)GetParticleEffectData((void *)a0);
        if (geo == 0) {
            return 1;
        }
        {
            int n = geo->f30;
            int i;
            for (i = 0; i < n; i++) {
                acc |= geo->f24[i].f0;
            }
        }
    }
    return acc == 0;
}
