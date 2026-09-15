/* libm.a member s_matherr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern int __ieee754_rem_pio2f(float x, float *y);
extern float __kernel_cosf(float x, float y);
extern float __kernel_sinf(float x, float y, int iy);
extern int dpcmp(long a0, long a1);

int matherr(void *a0)
{
    long p = *(long *)((char *)a0 + 8);
    dpcmp(p, p);
    return 0;
}
