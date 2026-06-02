#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_gflag", itouGFlagInit);

extern void effect_end_func(void);

void itouGflagLoad(void) {
    effect_end_func();
}

void itouGflagSave(void) {
    effect_end_func();
}

void func_00195B80(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_gflag", func_00195B88);
