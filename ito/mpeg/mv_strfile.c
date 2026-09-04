#include "common.h"

extern void func_0023C2C0(void *a0);

void strFileOpen(void *a0) {
    func_0023C2C0((char *)a0 + 0x50);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_strfile", videoDecFlush);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_strfile", strFileRead);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_strfile", func_0019B508);

extern int iosMallocCheckLeak2(int a0);

void func_0019B720(int a0) {
    iosMallocCheckLeak2(a0 & 0xFFFFFFF);
}

extern void func_0023CE80(int a0);
extern void func_0024DE40(int a0);
extern void readBufEndPut(int a0);

int videoDecDelete(int a0)
{
    func_0023CE80(a0 + 0x50);
    func_0024DE40(a0);
    readBufEndPut(a0);
    return 1;
}

extern void sceMpegAddStrCallback(void);
int func_0019B770(void) {
    sceMpegAddStrCallback();
    return 1;
}

void videoDecAbort(int *a0) {
    a0[0x2E] = 1;
}
