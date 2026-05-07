#include "regpin.h"
extern int D_00632780;

int func_00192040(void)
{
    register int v REG("$2") = 1;
    D_00632780 = v;
    return v;
}
