#include "regpin.h"
extern int D_00633C90;

int func_0013B858(void)
{
    register int v REG("$2") = 1;
    D_00633C90 = v;
    return v;
}
