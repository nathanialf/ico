/* libpkt.a member vifpk044.o */
#include <libpkt.h>

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
        /* one past the wrapped address, then up by the block mask */
        unsigned int t = a + 1;
        a = t + m;
    }
    /* clear the words up to a, advancing the packet pointer */
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
