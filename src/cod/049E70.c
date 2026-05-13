#include "regpin.h"

extern int *D_00631AE4;

int func_00149E70(int *a0)
{
    int *inner;
    long long val;
    register int ret REG("$2");
    if (a0 == 0) goto fail;
    if (a0 != D_00631AE4) goto fail;
    inner = (int *)a0[0x164 / 4];
    if (inner == 0) goto fail;
    val = *(long long *)((char *)inner + 0x20);
    ret = (int)((val << 8) >> 32) & 1;
    return ret;
fail:
    ret = 0;
    return ret;
}
