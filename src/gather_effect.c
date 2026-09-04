#include "common.h"

#include "ico/types.h"
struct GEl { int f0; char _4[0x6C]; };
struct GGeo { char _0[0x24]; struct GEl *f24; char _28[8]; int f30; };

INCLUDE_ASM("asm/nonmatchings/src/gather_effect", GatherEffect_SetGoal);
INCLUDE_ASM("asm/nonmatchings/src/gather_effect", GatherEffect_Proc);
INCLUDE_ASM("asm/nonmatchings/src/gather_effect", GatherEffect_Set);
extern void *GetParticleEffectData(void *a0);

INCLUDE_ASM("asm/nonmatchings/src/gather_effect", GatherEffect_InqEnd);
