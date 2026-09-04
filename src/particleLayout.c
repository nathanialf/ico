#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/particleLayout", ParticleLayoutGeo);
INCLUDE_ASM("asm/nonmatchings/src/particleLayout", InitParticleLayoutGeo);
void ParticleLayoutDL(void) {}
INCLUDE_ASM("asm/nonmatchings/src/particleLayout", DeleteParticleLayout);
