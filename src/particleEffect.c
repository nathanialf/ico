#include "common.h"

typedef struct { long long q[20]; } PE160;

struct PE_elem { int f0; char pad[0x10]; int f14; };



extern int D_0070A3F0[];
extern void MatrixDrive_TurnObjectMatrix();
extern void GetInverseQuaternion();
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", setParticleEffectGeometry);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", setParticleEffect);

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
extern struct PE_elem D_007030C0a[] __asm__("D_007097F0");
extern void debug_assertMessage();

void ExecParticleEffects(int a0, int a1, int a2) {
    if (a0 >= 0) {
        if (D_007030C0a[a0].f0 == 0) {
            debug_assertMessage(D_00619E40);
        } else {
            execParticleEffect(D_007030C0a[a0].f14, a1, a2);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", ResetParticleEffectPackages);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectPackage);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", DispParticleEffects);

extern PE160 D_004C5F40;
extern char D_00619E80[];
extern unsigned char D_0070A3F0__p4[] __asm__("D_0070A3F0");
extern void debug_assertMessage__p4(char *fmt, ...) __asm__("debug_assertMessage");
extern void func_00264128(void *dst, int *a1, int a2);

void InitParticleEffects(int a0, int *a1, int a2) {
    *(PE160 *)&D_0070A3F0__p4[a0 * 0xA0] = D_004C5F40;
    if (*(int *)&D_004C5F40 != *a1) {
        debug_assertMessage__p4(D_00619E80, *a1);
    }
    func_00264128(&D_0070A3F0__p4[a0 * 0xA0], a1, a2);
}

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", DeleteParticleEffect);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectActiveSensing);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", GetParticleEffectPackage);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001E8B48);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001E8B68);

int *DeleteParticleEffectsByID(int idx)
{
    return (int *)((char *)D_0070A3F0 + idx * 0xA0);
}

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", GetParticleEffectData);

