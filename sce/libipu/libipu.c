/* Vendor SCE library member: libipu.a(libipu.o).  MAIN.MAP's member spans tile this
 * run at retail addresses (0xE8, 0x150, 0x68), VMA 0x272338..0x2725D8, 3 functions. */
#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

extern void setD3_CHCR(int *a0);
extern void setD4_CHCR(int *a0);

void sceIpuStopDMA(void *a0)
{
    setD4_CHCR((int *)1);
    ((int *)a0)[0] = *(volatile int *)0x1000B410;
    ((int *)a0)[1] = *(volatile int *)0x1000B430;
    ((int *)a0)[2] = *(volatile int *)0x1000B420;
    ((int *)a0)[3] = *(volatile int *)0x1000B400;
    while (*(volatile int *)0x10002010 & 0xF0) {}
    setD3_CHCR((int *)0);
    ((int *)a0)[4] = *(volatile int *)0x1000B010;
    ((int *)a0)[5] = *(volatile int *)0x1000B020;
    ((int *)a0)[6] = *(volatile int *)0x1000B000;
    ((int *)a0)[7] = *(volatile int *)0x10002020;
    ((int *)a0)[8] = *(volatile int *)0x10002010;
}

INCLUDE_ASM("asm/nonmatchings/sce/libipu/libipu", sceIpuRestartDMA);

int sceIpuSync(int a0)
{
    int r = 0;
    switch (a0) {
    case 0:
        while (*(volatile int *)0x10002010 < 0) {}
        r = 0;
        break;
    case 1:
        r = (unsigned)*(volatile int *)0x10002010 >> 31;
        break;
    }
    return r;
}
