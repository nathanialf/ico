#include "common.h"
#include "r5900.h"

void func_0023B4D0(void) {
}

void loadImage(int a0) {
    *(volatile unsigned int *)0x1000A030 = a0 & 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000A020 = 0;
    *(volatile unsigned int *)0x1000A000 = 0x105;
}

extern int D_0062BE94;
extern char D_00288C30[];
extern void voBufDecCount(void *a0);

int viBufReset(void) {
    if (D_0062BE94) {
        voBufDecCount(D_00288C30);
        D_0062BE94 = 0;
    }
    SYNC();
    EI();
    return 0;
}

extern int D_0062BE90;
extern int D_0062C2DC;
extern int D_0062BE8C;
extern int sceGsSyncV(int a0);

void startDisplay(int a0) {
    while (sceGsSyncV(0) == a0);
    *(volatile int *)&D_0062BE90 = 1;
    D_0062C2DC = 0;
    *(volatile int *)&D_0062BE8C = 0;
}

extern int D_0062BE90;
extern int D_0062C2DC;

void viBufEndPut(void) {
    D_0062BE90 = 0;
    D_0062C2DC = 0;
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

void *viBufFlush(void *a0) {
    int *p = (int *)a0;
    p[0] = 0;
    p[2] = 0x3F;
    p[1] = 0;
    p[3] = 0;
    return (char *)a0 + 0x10;
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

void *setRGBAQ(int *a0, int a1, int a2, int a3, int p4, int p5) {
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

void *setXYZ2(int *a0, int a1, int a2, int a3) {
    long long t = (unsigned int)a1 | ((unsigned long long)(unsigned int)a2 << 16) | ((long long)a3 << 32);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 5;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *setFRAME_1(int *a0, int a1, int a2, int a3, int p4) {
    long long t = (unsigned int)a1
        | ((unsigned long long)(unsigned int)a2 << 16)
        | ((unsigned long long)(unsigned int)a3 << 24)
        | ((long long)p4 << 32);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x4C;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *setTEST_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7, unsigned int p8) {
    long long t = (unsigned int)a1
        | ((unsigned long long)(unsigned int)a2 << 1)
        | ((unsigned long long)(unsigned int)a3 << 4)
        | ((unsigned long long)(unsigned int)p4 << 12)
        | ((unsigned long long)(unsigned int)p5 << 14)
        | ((unsigned long long)(unsigned int)p6 << 15)
        | ((unsigned long long)(unsigned int)p7 << 16)
        | ((unsigned long long)p8 << 17);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x47;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *setSCISSOR_1(int *a0, int a1, int a2, int a3, int p4) {
    long long t = (unsigned int)a1
        | ((unsigned long long)(unsigned int)a2 << 16)
        | ((long long)a3 << 32)
        | ((long long)p4 << 48);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x40;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *setXYOFFSET_1(int *a0, unsigned int a1, unsigned int a2) {
    unsigned long long v = (unsigned int)a1 | ((unsigned long long)a2 << 32);
    int new_var;
    a0[0] = (int)(v << 32 >> 32);
    new_var = (int)(v >> 32);
    a0[1] = new_var;
    a0[2] = 0x18;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *setPRMODECONT(int *a0, unsigned int a1) {
    unsigned long long v = (unsigned int)a1;
    int new_var;
    a0[2] = 0x1A;
    a0[0] = (int)v;
    new_var = (int)(v >> 32);
    a0[1] = new_var;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *setPRMODE(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7, unsigned int p8) {
    long long t = ((unsigned long long)(unsigned int)a1 << 3)
        | ((unsigned long long)(unsigned int)a2 << 4)
        | ((unsigned long long)(unsigned int)a3 << 5)
        | ((unsigned long long)(unsigned int)p4 << 6)
        | ((unsigned long long)(unsigned int)p5 << 7)
        | ((unsigned long long)(unsigned int)p6 << 8)
        | ((unsigned long long)(unsigned int)p7 << 9)
        | ((unsigned long long)p8 << 10);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x1B;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}
