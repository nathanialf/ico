#include "matching.h"
#include "regpin.h"

extern int *func_001ADED8(int a0, int a3);

void func_001AE420(int a0, int a1, int a2, int a3)
{
    register int *p REG("$3");
    register int s0 REG("$16") = a1;
    register int s1 REG("$17") = a2;
    KEEP_LIVE(s0);
    KEEP_LIVE(s1);
    p = func_001ADED8(a0, a3);
    MATERIALIZE(p);
    p[12] = s0;
    p[13] = s1;
}
