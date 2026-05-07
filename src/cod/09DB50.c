#include "regpin.h"
void func_0019DB50(int a0, int a1)
{
    register int v REG("$2") = *(int *)(a0 + 0xC);
    register int orig REG("$6") = v;
    if (a1 < v) v = a1;
    orig -= v;
    *(int *)(a0 + 0xC) = orig;
}
