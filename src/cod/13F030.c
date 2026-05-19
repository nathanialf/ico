#include "matching.h"
#include "regpin.h"

extern int func_002425A8(int);
extern int D_00633B88;
extern int D_00633FDC;
extern int D_00633B84;

int func_0023F030(int a0)
{
    register int rv REG("$2");
    while (func_002425A8(0) == a0) ;
    rv = 1;
    D_00633B88 = rv;
    D_00633FDC = 0;
    D_00633B84 = 0;
    return rv;
}
