#include "common.h"



extern int D_00633FDC;
extern int D_00633B88;
#include "r5900.h"
extern char D_0028CA30[];
extern int  D_00633B8C;
extern void allocObjectData(int *p);
void func_0023EFB0(void) {}

void viBufCreate(int a0) {
    *(volatile unsigned int *)0x1000A030 = a0 & 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000A020 = 0;
    *(volatile unsigned int *)0x1000A000 = 0x105;
}

int viBufReset(void)
{
    if (D_00633B8C != 0) {
        allocObjectData(D_0028CA30);
        D_00633B8C = 0;
    }
    SYNC();
    EI();
    return 0;
}

extern int D_00633B84;
extern int func_002425A8(int a0);

void viBufBeginPut(int a0) {
    while (func_002425A8(0) == a0);
    *(volatile int *)&D_00633B88 = 1;
    D_00633FDC = 0;
    *(volatile int *)&D_00633B84 = 0;
}

void viBufEndPut(void) {
    D_00633B88 = 0;
    D_00633FDC = 0;
}

void *viBufAddDMA(void *a0, int a1, unsigned int a2, int a3, int p4, int p5, int p6) {
    unsigned long long g1 = ((unsigned long long)a1 << 63) | (unsigned int)p6;
    unsigned long long g2 = ((unsigned long long)(unsigned int)p4 << 28)
        | ((unsigned long long)(unsigned int)a3 << 31);
    unsigned long long g3 = ((unsigned long long)(a2 & 0xFFFFFFF0) << 32)
        | ((unsigned long long)(unsigned int)p5 << 26);
    *(long long *)a0 = g1 | g2 | g3;
    return (char *)a0 + 0x10;
}

void *viBufStopDMA(int *a0, long long a1, int a2, int a3, int p4, int p5, int p6, int p7) {
    int hi = (p5 << 14) | (a2 << 28);
    int lo = (a3 << 26) | (p4 << 15);
    a0[0] = (p6 << 15) | p7;
    a0[1] = hi | lo;
    a0[2] = (int)(a1 & 0xFFFFFFFFLL);
    a0[3] = (int)(a1 >> 32);
    return (char *)a0 + 0x10;
}

void *viBufRestartDMA(int *a0, int a1, long long a2) {
    a0[0] = (int)(a2 & 0xFFFFFFFFLL);
    a0[1] = (int)(a2 >> 32);
    a0[2] = a1;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

char *viBufFlush(char *p) {
    *(int *)(p + 0) = 0;
    *(int *)(p + 8) = 0x3F;
    *(int *)(p + 4) = 0;
    *(int *)(p + 0xC) = 0;
    return p + 0x10;
}

void *viBufModifyPts(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7) {
    long long t = (unsigned int)a1
        | ((unsigned long long)(unsigned int)a2 << 2)
        | ((unsigned long long)(unsigned int)a3 << 5)
        | ((unsigned long long)(unsigned int)p4 << 6)
        | ((unsigned long long)(unsigned int)p5 << 9)
        | ((unsigned long long)(unsigned int)p6 << 19)
        | ((long long)p7 << 32);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x14;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *viBufGetTs(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7,
                 unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11, unsigned int p12) {
    long long t = (unsigned int)a1
        | ((unsigned long long)(unsigned int)a2 << 14)
        | ((unsigned long long)(unsigned int)a3 << 20)
        | ((unsigned long long)(unsigned int)p4 << 26)
        | ((unsigned long long)(unsigned int)p5 << 30)
        | ((long long)p6 << 34)
        | ((long long)p7 << 35)
        | ((unsigned long long)p8 << 37)
        | ((unsigned long long)p9 << 51)
        | ((unsigned long long)p10 << 55)
        | ((unsigned long long)p11 << 56)
        | ((unsigned long long)p12 << 61);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 6;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *viBufDelete(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7, unsigned int p8, unsigned int p9) {
    long long t = (unsigned int)a1
        | ((unsigned long long)(unsigned int)a2 << 3)
        | ((unsigned long long)(unsigned int)a3 << 4)
        | ((unsigned long long)(unsigned int)p4 << 5)
        | ((unsigned long long)(unsigned int)p5 << 6)
        | ((unsigned long long)(unsigned int)p6 << 7)
        | ((unsigned long long)(unsigned int)p7 << 8)
        | ((unsigned long long)p8 << 9)
        | ((unsigned long long)p9 << 10);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *viBufCount(int *a0, int a1, int a2) {
    long long t = (unsigned int)a1 | ((unsigned long long)(unsigned int)a2 << 16);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 3;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *viBufPutTs(int *a0, int a1, int a2, int a3, int p4, int p5) {
    long long t = (unsigned int)a1
        | ((unsigned long long)(unsigned int)a2 << 8)
        | ((unsigned long long)(unsigned int)a3 << 16)
        | ((unsigned long long)(unsigned int)p4 << 24)
        | ((long long)p5 << 32);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 1;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F400);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F450);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F4B0);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F540);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F598);

void *func_0023F5D0(int *a0, int a1) {
    long long t = (unsigned int)a1;
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x1A;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F600);

