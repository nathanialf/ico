#include "matching.h"
#include "regpin.h"

extern int D_004C7710[];

void func_0010F710(void)
{
    register int *base = D_004C7710;
    register int *p = (int *)base[4];
    base[6] = 0;
    base[7] = 0;
    base[4] = (int)(p + 2);
    base[3] = (int)p;
    base[5] = (int)p;
    p[2] = 0x11000000;
    base[6] = (int)(p + 3);
    base[7] = (int)(p + 4);
    base[4] = (int)(p + 6);
    *(long long *)(p + 6) = 0xE;
    base[4] = (int)(p + 8);
}
