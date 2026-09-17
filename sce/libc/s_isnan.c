/* libc.a member s_isnan.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
/* The listing puts this source under newlib libm/math; the archive is libc.a. */
#include "common.h"
#include "reent.h"

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern void fiprintf();
extern void abort(void);

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
