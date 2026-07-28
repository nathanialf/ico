#include "common.h"



extern int D_006337B4;
extern int D_006337BC;
extern int D_006337B8;
INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", font_CheckAlign);

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", func_001FA910);

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", font_Print);

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", font_GetWidth);

void font_GetHeight(void)
{
    D_006337B8 = 0;
    D_006337BC = 0;
}

void font_Init(int val) {
    D_006337B4 = val;
}

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", func_001FAA58);

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", func_001FAAA8);

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", func_001FAAB0);

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", func_001FAE98);

