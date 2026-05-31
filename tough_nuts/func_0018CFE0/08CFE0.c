#include "regpin.h"
extern int D_00632704;

int func_0018CFE0(void)
{
    register int v REG("$2") = 1;
    D_00632704 = v;
    return v;
}
