/* libpkt.a member vifpk044.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef unsigned int u128_241778 __attribute__((mode(TI)));

typedef struct {
    int *end;
    int pad[2];
    int *cur;
} Pool241748;

void sceVif1PkAlign(int *a0, int a1, int a2)
{
    unsigned int m = 0xFFFFFFFF >> (32 - ((a1 + 2) & 31));
    int *p = (int *)a0[0];
    int *q;
    unsigned int a = ((unsigned int)p & ~m) + a2 * 4;

    if (a < (unsigned int)p) {
        /* one past the wrapped address, then up by the block mask; written as
         * two values because fold rewrites (a + 1) + m into a + (m + 1) and
         * the ROM adds the mask to a + 1. */
        unsigned int t = a + 1;
        a = t + m;
    }
    /* the fill loop is a goto loop: a while loop here is rotated with the
     * pointer copy coalesced away, the ROM keeps the copy at the loop head. */
    if ((unsigned int)p < a) {
        goto fill;
        do {
            p = q;
        fill:
            q = p + 1;
            *p = 0;
            a0[0] = (int)q;
        } while ((unsigned int)q < a);
    }
}
