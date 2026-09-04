#include "common.h"

#include "ico/types.h"

typedef struct { char _0[0x50]; } PLDLEntry;
typedef struct { char _0[4]; int f_4; char _8[0x98]; } ParticleLayout;
typedef struct { int w[6]; } ParticleRec;



extern int D_0070A3F0[];
extern ParticleRec D_007097F0[];
extern void iosMallocCheckLeak2(int p);
extern void prim_DispWireYCylinder(int x);

void DeleteParticleLayout(int a0) {
    ParticleLayout *target = &((ParticleLayout *)D_0070A3F0)[a0];
    int i;
    for (i = 0; i < 0x80; i++) {
        if (D_007097F0[i].w[0] != 0) {
            if (((int *)D_007097F0[i].w[5])[8] == (int)target) {
                int v;
                prim_DispWireYCylinder(((int *)D_007097F0[i].w[5])[0xA]);
                v = ((int *)D_007097F0[i].w[5])[9];
                ((int *)D_007097F0[i].w[5])[0xA] = 0;
                iosMallocCheckLeak2(v);
                iosMallocCheckLeak2(D_007097F0[i].w[5]);
                D_007097F0[i].w[5] = 0;
                D_007097F0[i].w[0] = 0;
            }
        }
    }
}

int InitParticleLayoutGeo(int a0) {
    return D_007097F0[a0].w[5];
}

int ParticleLayoutGeo(int idx)
{
    char *base = (char *)D_007097F0 + idx * 0x18;
    *((int *)(((char *)D_007097F0 + idx * 0x18) + 0x4)) = 0;
}

extern PLDLEntry D_006223D8[];
extern int strcmp(void *p, void *buf);

int ParticleLayoutDL(void *a0) {
    int i;
    for (i = 0; i < 0x35; i++) {
        if (strcmp(&D_006223D8[i], a0) == 0) {
            return i;
        }
    }
    return -1;
}

int GetParticleLoopFlag(int a0)
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
    base = (char *)D_007097F0 + idx * 0x18;
    ;
    *((int *)(((char *)(*((int **)(((char *)D_007097F0 + idx * 0x18) + 0x14)))) + 0x34)) = a1;
}

extern void GetParticleEffectPackage(int x);

void func_001E8EA8(GObj *a0) {
    GetParticleEffectPackage((int)((Obj7F0 *)GOBJ_SUB(a0)->p_800)->p_0);
}

INCLUDE_ASM("asm/nonmatchings/src/particleLayout", func_001E8EB8);

void func_001E8F28(void) {}

