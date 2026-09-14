/* libm.a member sf_sin.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

extern int __ieee754_rem_pio2f(float x, float *y);
extern float __kernel_cosf(float x, float y);
extern float __kernel_sinf(float x, float y, int iy);

float sinf(float x)
{
    float y[2];
    int n;
    int ix;

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;

    if (ix <= 0x3f490fd8) {
        return __kernel_sinf(x, 0.0f, 0);
    } else if (ix >= 0x7f800000) {
        return x - x;
    } else {
        n = __ieee754_rem_pio2f(x, y);
        switch (n & 3) {
        case 0:
            return __kernel_sinf(y[0], y[1], 1);
        case 1:
            return __kernel_cosf(y[0], y[1]);
        case 2:
            return -__kernel_sinf(y[0], y[1], 1);
        default:
            return -__kernel_cosf(y[0], y[1]);
        }
    }
}
