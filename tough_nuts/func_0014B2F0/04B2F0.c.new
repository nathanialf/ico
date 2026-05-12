#include "regpin.h"
int func_0014B2F0(int *a0, int a1)
{
    register int v0 REG("$2") = 0;
    register int *p REG("$3");
    long long bits;
    int mask;
    p = (int *)a0[0x59];
    if (p != 0) {
        v0 = 1;
        bits = *(long long *)((char *)p + 0x58);
        mask = 1 << a1;
        if ((mask & bits) == 0) v0 = 0;
    }
    return v0;
}
