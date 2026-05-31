#include "regpin.h"
extern int D_006337B8;

int func_001FAA30(void)
{
    register int v REG("$2") = 1;
    D_006337B8 = v;
    return v;
}
