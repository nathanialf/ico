#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/particleLayout", ParticleLayoutGeo);
extern char D_006209C0[];
extern int D_0063A438;
int *InitParticleLayoutGeo(char *self, int *other) {
    int *r;
    r = iosMallocDebug(D_0063A438, 4, D_006209C0, 0xC);
    *r = SetParticleEffect(other[0x30 / 4], other, *(char **)(self + 0x15C) + 0x60);
    return r;
}
void ParticleLayoutDL(void) {}
INCLUDE_ASM("asm/nonmatchings/src/particleLayout", DeleteParticleLayout);
