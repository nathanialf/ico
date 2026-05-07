#include "regpin.h"
extern unsigned char D_00633D8D;

int func_0018CFD0(void)
{
    register int v REG("$2") = 1;
    D_00633D8D = v;
    return v;
}
