#include "regpin.h"
extern int D_00633024;

int func_001B0A58(void)
{
    register int v REG("$2") = 1;
    D_00633024 = v;
    return v;
}
