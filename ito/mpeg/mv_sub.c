#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", ErrMessage);

extern void func_0023A6D0(void *a0);

void copy2area(int a0) {
    func_0023A6D0(*(void **)(a0 + 0x30));
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_00239E18);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_00239FC0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A0E0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A410);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A5E8);

extern int iosMallocCheckLeak2(int a0);

void func_0023A6D0(void *a0) {
    iosMallocCheckLeak2((int)a0 & 0xFFFFFFF);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A6E0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A748);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A7A0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A7B8);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A850);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A888);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023A920);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023AA98);

extern int func_0023AA98(void *a0, int a1, int a2);

void func_0023AC90(void *a0, int a1, int a2) {
    int v = *(int *)((char *)a0 + 0x3C);
    func_0023AA98(a0, a1, v < a2 ? a2 : v);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023ACA0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023AD08);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023ADB0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023B310);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_sub", func_0023B348);
