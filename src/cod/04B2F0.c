#include "regpin.h"

int func_0014B2F0(char *a0, int a1)
{
    char *p;
    long long val;
    int mask;
    register int ret REG("$2");
    p = *(char **)(a0 + 0x164);
    ret = 0;
    if (p == 0) goto end;
    ret = 1;
    val = *(long long *)(p + 0x58);
    mask = 1 << a1;
    if ((val & mask) == 0) ret = 0;
end:
    return ret;
}
