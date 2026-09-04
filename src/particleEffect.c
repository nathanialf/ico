#include "common.h"

#include "ico/types.h"

typedef struct { long long q[20]; } PE160;

extern void CopyQuaternion();
extern void CopyVector();

extern int CopyQuaternion__pn(int a0, int a1) __asm__("CopyQuaternion");
extern void CopyVector__pn(int a0) __asm__("CopyVector");
void setParticleEffectGeometry(int a0, int a1, int a2)
{
    CopyVector(a0);
    CopyQuaternion(a0 + 0x10, a2);
}
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", _setParticleEffect);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", setParticleEffect);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", execParticleEffect);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", dispParticleEffect);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectByPartition);
typedef struct { int w[7]; } PEffect;
extern PEffect D_00720220[];
extern char D_00620940[];
void SetParticleEffectGeometry(int a0, int a1, int a2) {
    if (a0 >= 0) {
        if (D_00720220[a0].w[0] == 0) {
            debug_StdPrintfDummy(D_00620940);
        } else {
            setParticleEffectGeometry(D_00720220[a0].w[6], a1, a2);
        }
    }
}
extern void execParticleEffect(void *a0);
void SetParticleEffectUpperLimit(int no, float f) {
    char *o;
    if (no >= 0) {
        o = (char *)D_00720220[no].w[6];
        *(int *)(o + 0x38) = 1;
        *(float *)(o + 0x3C) = f;
        execParticleEffect(o);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", ExecParticleEffect);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", ResetParticleEffectPackages);
extern PE160 D_004ECDF0;
extern char D_00620980[];
extern int D_00721020[];
extern void debug_StdPrintfDummy();
extern void memcpy(void *dst, int *a1, int a2);

void SetParticleEffectPackage(int a0, int *a1, int a2) {
    *(PE160 *)((unsigned char *)D_00721020 + a0 * 0xA0) = D_004ECDF0;
    if (*(int *)&D_004ECDF0 != *a1) {
        debug_StdPrintfDummy(D_00620980, *a1);
    }
    memcpy(((unsigned char *)D_00721020 + a0 * 0xA0), a1, a2);
}
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", InitParticleEffects);
void func_001F52D8(void) {
    int i;
    for (i = 0; i < 0x80; i++) {
        ExecParticleEffect(i);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001F5310);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", DeleteParticleEffect);
void SetParticleEffectPauseFlag(int a0, int a1) {
    D_00720220[a0].w[1] = a1;
}
extern int D_0063A450;
extern int SetParticleEffectByPartition(int a0, void *a1, int a2, int a3);

int SetParticleEffect(int a0, void *a1, int a2)
{
    return SetParticleEffectByPartition(a0, a1, a2, D_0063A450);
}
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectActiveSensing);
int *GetParticleEffectPackage(int idx)
{
    return (int *)((char *)D_00721020 + idx * 0xA0);
}
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", DeleteParticleEffectsByPackage);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", DeleteParticleEffectsByID);
int GetParticleEffectData(int a0) {
    return D_00720220[a0].w[6];
}
void DisableParticleEffectGeometryControl(int a0) {
    D_00720220[a0].w[2] = 0;
}
extern char D_0062A278[];
int GetParticleIDWithName(char *name) {
    int i;
    for (i = 0; i < 0x3D; i++) {
        if (strcmp(D_0062A278 + i * 0x50, name) == 0) {
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
    p = (int *)((char *)D_00721020 + a0 * 0xA0);
    return p[1] == 1;
}
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", ParticleEffects_SetAllGoal);
void SetParticleEffectClipEnableFlag(int a0, int a1) {
    if (a0 >= 0) {
        *(int *)((char *)D_00720220[a0].w[6] + 0x34) = a1;
    }
}
void SetParticleEffectDrainLevel(int a0, float f) {
    if (a0 >= 0) {
        *(float *)((char *)D_00720220[a0].w[6] + 0x40) = f;
    }
}
