#include "regpin.h"

extern int D_0027E4C0[];
extern void func_0013A5B8(int *a0, char *a1, int a2);

void func_001325D8(char *a0, int a1)
{
    register char *p REG("$3") = a0;
    long long *pp = (long long *)p;
    *(int *)(p + 4) = 1;
    *pp = (*pp & ~1LL) | (a1 & 1);
    return func_0013A5B8(D_0027E4C0, p, 0);
}
