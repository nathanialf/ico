#include "common.h"

/* Generator 0x7F0 view (local) */
typedef struct { char _0[8]; int f_8; char f_C; char _pad_d; char f_E; } GenGeo;

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", CheckGeneratorCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", GetGeneratorSafePosition);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", endfunc_BGA);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", IsNeedGenerator);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", CallEnemy);

extern void func_001AB9F8(void *a0);
extern void iosOmBeforeFuncStandard(void *a0, int a1, void *a2);

void Generator_QuickCall(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    GenGeo *q = *(GenGeo **)((char *)p + 0x7F0);
    *(int *)((char *)q + 0x50) = 1;
    func_001AB9F8(a0);
    iosOmBeforeFuncStandard(a0, 1, a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", GetMotherGenerator);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", ReadGeneratorPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", MakeGeneratorPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", generatorBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", GeneratorGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", GeneratorDL);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", InitGeneratorGeo);

void Generator_Call(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    GenGeo *q = *(GenGeo **)((char *)p + 0x7F0);
    q->f_8++;
}

void Generator_ResetCount(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    GenGeo *q = *(GenGeo **)((char *)p + 0x7F0);
    q->f_E = 1;
}

void Generator_Mask(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    GenGeo *q = *(GenGeo **)((char *)p + 0x7F0);
    q->f_C = 1;
}

void Generator_MaskOff(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    GenGeo *q = *(GenGeo **)((char *)p + 0x7F0);
    q->f_C = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", SetMotherGenerator);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", Generator_Init);

extern int D_006CA620[];

void *GetbufpGeneratorPacket(void) {
    return D_006CA620;
}

int GetsizeGeneratorPacket(void) {
    return 0x280B;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_2C;  /* 0x2C */
    unsigned int       f_30;  /* 0x30 */
    unsigned int       f_34;  /* 0x34 */
    unsigned short     f_40;  /* 0x40 */
    short              f_42;  /* 0x42 */
    unsigned short     f_44;  /* 0x44 */
    unsigned char      f_46;  /* 0x46 */
    unsigned int       f_48;  /* 0x48 */
} S_002A0A90;  /* stride 0x4C */

/* end struct shapes */
