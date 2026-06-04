#include "common.h"

extern void *InitParticleLayoutGeo(void);

int itouGFlagInit(void) {
    int rv = 1;
    void *r = InitParticleLayoutGeo();
    **(int **)((char *)r + 0x60) = rv;
    return rv;
}

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
