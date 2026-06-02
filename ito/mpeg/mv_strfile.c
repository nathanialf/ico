#include "common.h"

extern void func_0023C2C0(void *a0);

void strFileOpen(void *a0) {
    func_0023C2C0((char *)a0 + 0x50);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_strfile", strFileClose);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_strfile", strFileRead);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_strfile", func_0019B508);

extern int iosMallocCheckLeak2(int a0);

void func_0019B720(int a0) {
    iosMallocCheckLeak2(a0 & 0xFFFFFFF);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_strfile", func_0019B730);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_strfile", func_0019B770);

void func_0019B790(int *a0) {
    a0[0x2E] = 1;
}
