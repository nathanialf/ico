#include "common.h"

extern void playSEConditionID(int a0, int a1);

void RopeFixGeo(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/ropeFix", RopeFixDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/ropeFix", InitRopeFixGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/ropeFix", func_001E6B28);

int func_001E6B70(void) {
    return 0;
}

void func_001E6B78(int a0) {
    playSEConditionID(a0, 0x33);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/ropeFix", func_001E6B80);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/ropeFix", func_001E6BB0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/ropeFix", func_001E6BE0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/ropeFix", func_001E6C48);
