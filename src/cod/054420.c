#include "regpin.h"

extern int *D_00631AE4;

int func_00154420(void)
{
    int *v0 = D_00631AE4;
    int *v1 = (int *)v0[0x164 / 4];
    unsigned int a = v1[0x30 / 4];
    register int ret REG("$2");
    ret = 1;
    if (a >= 0x5D) goto end;
    ret = a < 0x5B;
end:
    return ret;
}
