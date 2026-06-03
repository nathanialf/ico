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


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
} S_007030C0;  /* stride 0x18 */

/* end struct shapes */
