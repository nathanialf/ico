#include "common.h"





extern void sceMpegAddStrCallback();
extern int func_00251AB0();
extern void viBufDelete();
extern void free_buf(int a0);
extern void iosMallocCheckLeak2();
extern void func_0023FDA0();
void strFileOpen(int a0)
{
    func_0023FDA0(a0 + 0x50);
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_strfile", videoDecFlush);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_strfile", strFileRead);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_strfile", func_0019DF38);

void func_0019E150(int a0)
{
    iosMallocCheckLeak2(a0 & 0x0FFFFFFF);
}

int videoDecDelete(int a0)
{
    viBufDelete(a0 + 0x50);
    func_00251AB0(a0);
    free_buf(a0);
    return 1;
}

int func_0019E1A0(void) {
    sceMpegAddStrCallback();
    return 1;
}

void videoDecAbort(int a0)
{
    *(int *)(a0 + 0xB8) = 1;
}

