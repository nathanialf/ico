#include "common.h"



extern int D_0070A3F0[];
extern char D_007097F0[];
INCLUDE_ASM("asm/nonmatchings/src/particleLayout", DeleteParticleLayout);

INCLUDE_ASM("asm/nonmatchings/src/particleLayout", InitParticleLayoutGeo);

int ParticleLayoutGeo(int idx)
{
    char *base = &D_007097F0[idx * 0x18];
    *((int *)((&D_007097F0[idx * 0x18]) + 0x4)) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/particleLayout", ParticleLayoutDL);

int func_001E8DE0(int a0)
{
    int *p;
    if (a0 < 0) {
        return -1;
    }
    p = (int *)((char *)D_0070A3F0 + a0 * 0xA0);
    return p[1] == 1;
}

INCLUDE_ASM("asm/nonmatchings/src/particleLayout", func_001E8E10);

void func_001E8E80(int idx, int a1)
{
    int *p;
    char *base;
    if (idx < 0) {
        return;
    }
    base = &D_007097F0[idx * 0x18];
    ;
    *((int *)(((char *)(*((int **)((&D_007097F0[idx * 0x18]) + 0x14)))) + 0x34)) = a1;
}

INCLUDE_ASM("asm/nonmatchings/src/particleLayout", func_001E8EA8);

INCLUDE_ASM("asm/nonmatchings/src/particleLayout", func_001E8EB8);

void func_001E8F28(void) {}

