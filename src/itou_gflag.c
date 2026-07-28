#include "common.h"


extern void effect_end_func();
INCLUDE_ASM("asm/nonmatchings/src/itou_gflag", itouGFlagInit);

void itouGflagLoad(int a0, int a1, int a2, int a3)
{
    effect_end_func(a0, a1, a2, a3);
}

void itouGflagSave(int a0, int a1, int a2, int a3)
{
    effect_end_func(a0, a1, a2, a3);
}

void func_00198430(void) {}

INCLUDE_ASM("asm/nonmatchings/src/itou_gflag", func_00198438);

