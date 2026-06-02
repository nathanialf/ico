#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", font_CheckAlign);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", func_001F7578);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", font_Print);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", font_GetWidth);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", font_GetHeight);

extern int D_0062BA9C;

void font_Init(int a0) {
    D_0062BA9C = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", func_001F76C0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", func_001F7710);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", func_001F7718);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayFont", func_001F7B00);
