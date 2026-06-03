#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleLayout", DeleteParticleLayout);

typedef struct { int w[6]; } ParticleRec;
extern ParticleRec D_007030C0[];

int InitParticleLayoutGeo(int a0) {
    return D_007030C0[a0].w[5];
}

void ParticleLayoutGeo(int a0) {
    D_007030C0[a0].w[1] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleLayout", ParticleLayoutDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleLayout", func_001E6040);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleLayout", func_001E6070);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleLayout", func_001E60E0);

extern int GetParticleEffectPackage(int a0);

void func_001E6108(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    GetParticleEffectPackage(*(int *)q);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleLayout", func_001E6118);

void func_001E6188(void) {
}
