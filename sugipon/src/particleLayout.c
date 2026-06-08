#include "common.h"

/* particleLayout 0x7F0 view (local) */
typedef struct { int f_0; } PLGeo;
#include "ico/types.h"

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

typedef struct { char _0[4]; int f_4; char _8[0x98]; } ParticleLayout;
extern ParticleLayout D_00703CC0[];

int func_001E6040(int a0) {
    ParticleLayout *p;
    if (a0 < 0) {
        return -1;
    }
    p = &D_00703CC0[a0];
    return p->f_4 == 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleLayout", func_001E6070);

void func_001E60E0(int a0, int a1) {
    if (a0 >= 0) {
        int *q = (int *)D_007030C0[a0].w[5];
        q[0xD] = a1;
    }
}

extern int GetParticleEffectPackage(int a0);

void func_001E6108(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    PLGeo *q = *(PLGeo **)((char *)p + 0x7F0);
    GetParticleEffectPackage(q->f_0);
}

extern int   D_0062A310;
extern int  *iosFree(int handle, int size, char *file, int line);
extern int   SetParticleEffectUpperLimit(int x, int *p, char *q);

extern char D_006128B0[];

int *func_001E6118(int *self, int *other)
{
    int *r;
    Sub15C *p_15c;
    r = iosFree(D_0062A310, 0x4, (char *)D_006128B0, 0xC);
    p_15c = ((GObj *)self)->p_15C;
    *r = SetParticleEffectUpperLimit(other[0x30 / 4], other, (char *)p_15c + 0x60);
    return r;
}

void func_001E6188(void) {
}
