#include "common.h"



extern void iosMallocCheckLeak2();
extern void func_002407C0();
int func_0019E310(int a0_unused, int *a1, char *a2) {
    long long buf[4];
    func_002407C0((int *)(a2 + 0x50), (int *)buf);
    *(long long *)((char *)a1 + 0x8) = buf[0];
    *(long long *)((char *)a1 + 0x10) = buf[1];
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vobuf", voBufCreate);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vobuf", voBufDelete);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vobuf", voBufReset);

void voBufIsFull(int a0)
{
    iosMallocCheckLeak2(a0 & 0x0FFFFFFF);
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vobuf", voBufIncCount);

int voBufGetData(int *self) {
    return self[3] == self[4];
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vobuf", voBufGetTag);

