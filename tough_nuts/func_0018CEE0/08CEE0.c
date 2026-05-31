#include "regpin.h"
extern unsigned char D_00633D8C;

int func_0018CEE0(void)
{
    register int v REG("$2") = 1;
    D_00633D8C = v;
    return v;
}
