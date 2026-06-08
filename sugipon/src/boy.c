#include "common.h"
#include "ico/types.h"

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
    GOBJ_SUB(a0)->p_7F0->p_0 = (void *)a1;
}
