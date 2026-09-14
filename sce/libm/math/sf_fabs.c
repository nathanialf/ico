/* libm.a member sf_fabs.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

extern int __ieee754_rem_pio2f(float x, float *y);
extern float __kernel_cosf(float x, float y);
extern float __kernel_sinf(float x, float y, int iy);
extern int dpcmp(long a0, long a1);

float fabsf(float a0)
{
    unsigned int ix;
    GET_FLOAT_WORD(ix, a0);
    SET_FLOAT_WORD(a0, ix & 0x7fffffff);
    return a0;
}
