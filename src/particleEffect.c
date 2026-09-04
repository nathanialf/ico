#include "common.h"

typedef struct { long long q[20]; } PE160;

struct PE_elem { int f0; int f4; int f8; int fC; int f10; int f14; };



extern int D_0070A3F0[];
extern void MatrixDrive_TurnObjectMatrix();
extern void GetInverseQuaternion();
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", setParticleEffectGeometry);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", DispMultiBgaManagerWithKind);

void execParticleEffect(int a0, int a1, int a2)
{
    MatrixDrive_TurnObjectMatrix(a0);
    GetInverseQuaternion(a0 + 0x10, a2);
}

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", dispParticleEffect);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffect);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectGeometry);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectUpperLimit);

extern char D_00619E40[];
extern struct PE_elem D_007097F0[];
extern void debug_StdPrintfDummy();

void ExecParticleEffects(int a0, int a1, int a2) {
    if (a0 >= 0) {
        if (D_007097F0[a0].f0 == 0) {
            debug_StdPrintfDummy(D_00619E40);
        } else {
            execParticleEffect(D_007097F0[a0].f14, a1, a2);
        }
    }
}

struct PE_obj { char pad0[0x38]; int f38; float f3C; };
extern void SetParticleEffect(struct PE_obj *o);

void ResetParticleEffectPackages(int no, float f)
{
    struct PE_obj *o;

    if (no >= 0) {
        o = (struct PE_obj *)D_007097F0[no].f14;
        o->f38 = 1;
        o->f3C = f;
        SetParticleEffect(o);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectPackage);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", DispParticleEffects);

extern PE160 D_004C5F40;
extern char D_00619E80[];
extern void memcpy(void *dst, int *a1, int a2);

void InitParticleEffects(int a0, int *a1, int a2) {
    *(PE160 *)((unsigned char *)D_0070A3F0 + a0 * 0xA0) = D_004C5F40;
    if (*(int *)&D_004C5F40 != *a1) {
        debug_StdPrintfDummy(D_00619E80, *a1);
    }
    memcpy(((unsigned char *)D_0070A3F0 + a0 * 0xA0), a1, a2);
}

typedef struct { char c[0x18]; } Blob24;
extern char D_004C5F20[];

void DeleteParticleEffect(void)
{
    int i;

    for (i = 0; i < 128; i++) {
        *(Blob24 *)&D_007097F0[i] = *(Blob24 *)D_004C5F20;
    }
}

extern void SetParticleEffectGeometry(int a0);

void SetParticleEffectActiveSensing(void)
{
    int i;

    for (i = 0; i < 128; i++) {
        if (D_007097F0[i].f0 != 0) {
            SetParticleEffectGeometry(D_007097F0[i].f14);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", GetParticleEffectPackage);

extern int D_00632028;
extern int SetParticleEffectUpperLimit(int a0, void *a1, int a2, int a3);

int func_001E8B48(int a0, void *a1, int a2)
{
    return SetParticleEffectUpperLimit(a0, a1, a2, D_00632028);
}

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001E8B68);

int *DeleteParticleEffectsByID(int idx)
{
    return (int *)((char *)D_0070A3F0 + idx * 0xA0);
}

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", GetParticleEffectData);

