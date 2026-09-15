/* libpkt.a member vifpk027.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef unsigned int u128_241778 __attribute__((mode(TI)));

typedef struct {
    int *end;
    int pad[2];
    int *cur;
} Pool241748;

int *sceVif1PkTerminate(int **a0)
{
    int *p = a0[0];
    int *q = (int *)a0[2];
    while ((int)p & 0xC) {
        *p = 0;
        p++;
    }
    if (q) {
        int n = (((char *)p - (char *)q) >> 4) - 1;
        *q += n;
    }
    a0[0] = p;
    a0[2] = 0;
    return p;
}

extern void sceVif1PkAlign(void *a0, int a1, int a2);
