/* libgcc.a member _fixdfdi.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern unsigned long long __fixunsdfdi(double a);

long long __fixdfdi(double a)
{
    if (a < 0)
        return -__fixunsdfdi(-a);
    return __fixunsdfdi(a);
}
