#include "regpin.h"

int *func_0023F130(int *a0, int a1, long long a2)
{
    register int lo REG("$2") = (int)(a2 & 0xFFFFFFFFLL);
    a0[2] = a1;
    a0[3] = 0;
    a0[0] = lo;
    a0[1] = (int)(a2 >> 32);
    return a0 + 4;
}
