/* libm.a member s_matherr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */

#include <math.h>

int matherr(struct exception *x)
{
    int n = 0;

    if (x->arg1 != x->arg1)
        return 0;
    return n;
}
