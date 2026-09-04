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
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectGeometry);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectUpperLimit);
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
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001F52D8);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001F5310);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", DeleteParticleEffect);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectPauseFlag);
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
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", GetParticleEffectData);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", DisableParticleEffectGeometryControl);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", GetParticleIDWithName);
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
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectClipEnableFlag);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectDrainLevel);
