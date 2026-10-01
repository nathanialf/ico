/* libgcc.a member _fixdfdi.o */
#include "libgcc2.h"

long long __fixdfdi(double a)
{
    if (a < 0)
        return -__fixunsdfdi(-a);
    return __fixunsdfdi(a);
}
