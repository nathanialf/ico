#include "matching.h"

void func_00245228(int *a0)
{
    int v = a0[0];
    int *p = (int *)a0[3];
    int pv;
    v -= 4;
    MATERIALIZE(v);
    a0[3] = 0;
    v -= (int)p;
    pv = *p;
    KEEP_LIVE(pv);
    *p = pv + (int)((unsigned)((int)v >> 2) >> 2);
}
