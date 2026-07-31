#include "common.h"

#include "r5900.h"



extern void iosMallocCheckLeak2();
extern void func_002407C0();
int func_0019E310(int a0_unused, int *a1, char *a2) {
    long long buf[4];
    func_002407C0((int *)(a2 + 0x50), (int *)buf);
    *(long long *)((char *)a1 + 0x8) = buf[0];
    *(long long *)((char *)a1 + 0x10) = buf[1];
    return 1;
}

extern void voBufIsFull(int a0);

void voBufCreate(self)
int *self;
{
    voBufIsFull(self[0]);
    voBufIsFull(self[1]);
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vobuf", voBufDelete);

extern void voBufCreate();

void voBufReset(void) {
    voBufCreate();
}

void voBufIsFull(int a0)
{
    iosMallocCheckLeak2(a0 & 0x0FFFFFFF);
}

void voBufIncCount(volatile int *self)
{
    self[3] = 0;
    self[2] = 0;
}

int voBufGetData(int *self) {
    return self[3] == self[4];
}

extern void func_00101A40(volatile int *a0);

void voBufGetTag(volatile int *a0) {
    int w, n;
    func_00101A40(a0);
    *(int *)(a0[1] + a0[2] * 0xA0A40) = 2;
    w = a0[3];
    n = a0[4];
    a0[3] = w + 1;
    a0[2] = (a0[2] + 1) % n;
    SYNC();
    EI();
}

