#include "matching.h"
#include "regpin.h"

extern int D_004C7710[];

void func_0010F710(void)
{
    register int *base REG("$3") = D_004C7710;
    register int *p REG("$2") = (int *)base[4];
    base[6] = 0;
    base[7] = 0;
    base[4] = (int)(p + 2);
    base[3] = (int)p;
    base[5] = (int)p;
    p[2] = 0x11000000;
    base[4] = (int)(p + 6);
    *(volatile int *)(base + 6) = (int)(p + 3);
    *(volatile int *)(base + 7) = (int)(p + 4);
    *(volatile long long *)(p + 6) = 0xE;
    *(volatile int *)(base + 4) = (int)(p + 8);
}
