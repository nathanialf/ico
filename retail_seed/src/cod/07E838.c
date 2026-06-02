#include "ico/types.h"
extern int func_00105F00(void *p, void *buf);
int func_0017E838(char *a0, float f12, float f13, float f14)
{
    union { float f[4]; int i[4]; } local;
    local.f[0] = f12;
    local.f[1] = f13;
    local.f[2] = f14;
    local.i[3] = 0;
    return func_00105F00((char *)GOBJ_SUB(a0) + 0x670, local.f);
}
