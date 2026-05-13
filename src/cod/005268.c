#include "regpin.h"

extern int D_00631B40;

int func_00105268(void)
{
    register int r REG("$2") = D_00631B40 - 1;
    D_00631B40 = r;
    return r;
}
