#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", setParticleEffectGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", setParticleEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", execParticleEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", dispParticleEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffectGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffectUpperLimit);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", ExecParticleEffects);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", ResetParticleEffectPackages);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffectPackage);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", DispParticleEffects);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", InitParticleEffects);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", DeleteParticleEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffectActiveSensing);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", GetParticleEffectPackage);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", DeleteParticleEffectsByPackage);

extern unsigned char D_00703CC0[];

void *DeleteParticleEffectsByID(int a0) {
    return &D_00703CC0[a0 * 0xA0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", GetParticleEffectData);
