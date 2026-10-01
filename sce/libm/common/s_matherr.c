/* libm.a member s_matherr.o */

#include <math.h>

int matherr(struct exception *x)
{
    int n = 0;

    if (x->arg1 != x->arg1)
        return 0;
    return n;
}
