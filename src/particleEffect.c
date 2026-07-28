#include "common.h"



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

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", ExecParticleEffects);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", ResetParticleEffectPackages);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", SetParticleEffectPackage);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", DispParticleEffects);

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", InitParticleEffects);

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

