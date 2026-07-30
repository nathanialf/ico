#include "common.h"





extern void func_00250F90();
extern int func_00251AB0();
extern void func_00240960();
extern void readBufEndPut(int a0);
extern void iosMallocCheckLeak2();
extern void func_0023FDA0();
void strFileOpen(int a0)
{
    func_0023FDA0(a0 + 0x50);
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_strfile", strFileClose);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_strfile", strFileRead);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_strfile", func_0019DF38);

void func_0019E150(int a0)
{
    iosMallocCheckLeak2(a0 & 0x0FFFFFFF);
}

int func_0019E160(int a0)
{
    func_00240960(a0 + 0x50);
    func_00251AB0(a0);
    readBufEndPut(a0);
    return 1;
}

int func_0019E1A0(void) {
    func_00250F90();
    return 1;
}

void func_0019E1C0(int a0)
{
    *(int *)(a0 + 0xB8) = 1;
}

