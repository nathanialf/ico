#include "common.h"

struct E24_pe { char pad[0x14]; int *f14; };

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", setParticleEffectGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", setParticleEffect);

extern void MatrixDrive_TurnObjectMatrix(int a0);
extern int GetInverseQuaternion(int a0, int a1);

void execParticleEffect(int a0, int a1, int a2)
{
    MatrixDrive_TurnObjectMatrix(a0);
    GetInverseQuaternion(a0 + 0x10, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", dispParticleEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffectGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffectUpperLimit);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", ExecParticleEffects);

extern char D_007030C0[];
extern void SetParticleEffect(int *p);

void ResetParticleEffectPackages(int a0, float f)
{
    struct E24_pe *new_var;
    int *p;
    if (a0 < 0) return;
    new_var = (struct E24_pe *)D_007030C0;
    new_var = (struct E24_pe *)((char *)new_var - (-(a0 * 0x18)));
    p = new_var->f14;
    p[0x38 / 4] = 1;
    *(float *)((char *)p + 0x3C) = f;
    SetParticleEffect(p);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", SetParticleEffectPackage);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", DispParticleEffects);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", InitParticleEffects);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/particleEffect", DeleteParticleEffect);

extern void SetParticleEffectGeometry(int);

void SetParticleEffectActiveSensing(void)
{
    char *p = D_007030C0;
    char *end = p + 0xC00;
    do {
        if (*(int *)p != 0) {
            SetParticleEffectGeometry(*(int *)(p + 0x14));
        }
        p += 0x18;
    } while ((int)p < (int)end);
}

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
