#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", dispClothes);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", execClothes);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", InitLightLineGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", LightLineDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", InitBoyGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", BoyGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", dispCrown);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", BoyDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", SelectBoyCrown);

void LightLineGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    q[0] = a1;
}
