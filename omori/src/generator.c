#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", CheckGeneratorCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", GetGeneratorSafePosition);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", endfunc_BGA);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", IsNeedGenerator);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", CallEnemy);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", Generator_QuickCall);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", GetMotherGenerator);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", ReadGeneratorPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", MakeGeneratorPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", generatorBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", GeneratorGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", GeneratorDL);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", InitGeneratorGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/generator", Generator_Call);

void Generator_ResetCount(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    *((char *)q + 0xE) = 1;
}

void Generator_Mask(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    *((char *)q + 0xC) = 1;
}

void Generator_MaskOff(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    *((char *)q + 0xC) = 0;
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
