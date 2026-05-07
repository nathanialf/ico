#include "regpin.h"

long func_001F4228(int *a0)
{
    register int *v REG("$2") = (int *)a0[0x57];
    register int *v1 REG("$3");
    v = (int *)v[0x200];
    v1 = (int *)v[0x14];
    if (0 == v1) goto fail;
    v1 = (int *)v[0x15];
    return v1[0];
fail:
    return 0;
}
