#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/cageFix", CageFixGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/cageFix", CageFixDL);

void InitCageFixGeo(void *a0, float a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    *(float *)((char *)q + 0x3C) = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/cageFix", func_001C0138);

void func_001C0180(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    *(int *)((char *)q + 0x40) = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/cageFix", func_001C0190);
