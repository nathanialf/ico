/* libpkt.a member vifpk036.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <libpkt.h>

typedef unsigned int u128_241778 __attribute__((mode(TI)));

typedef struct {
    int *end;
    int pad[2];
    int *cur;
} Pool241748;

void sceVif1PkEnd(int **a0, int a1)
{
    int *p;
    a0[2] = sceVif1PkTerminate(a0);
    p = a0[0];
    *p++ = a1 | 0x70000000;
    a0[3] = 0;
    a0[0] = p + 1;
    *p = 0;
}
