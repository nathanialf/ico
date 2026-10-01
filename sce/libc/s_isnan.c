/* libc.a member s_isnan.o */
/* newlib's libm/math source, built into libc.a. */
#include "reent.h"
#include <math.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

int isnan(long long x)
{
    int lx, hx;
    do {
        lx = (int)x;
        hx = (int)(x >> 32);
    } while (0);
    hx &= 0x7fffffff;
    hx |= ((unsigned int)(lx | (-lx))) >> 31;
    hx = 0x7ff00000 - hx;
    do {
        return ((unsigned int)hx) >> 31;
    } while (0);
}
