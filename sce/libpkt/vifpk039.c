/* libpkt.a member vifpk039.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <libpkt.h>

typedef unsigned int u128_241778 __attribute__((mode(TI)));

typedef struct {
    int *end;
    int pad[2];
    int *cur;
} Pool241748;

void sceVif1PkOpenDirectCode(void *a0, int a1)
{
    int *v;
    int w;
    sceVif1PkAlign(a0, 2, 3);
    v = *(int **)a0;
    w = a1 ? 0xD0000000 : 0x50000000;
    *v = w;
    *(int **)((char *)a0 + 0xC) = v;
    *(int **)a0 = v + 1;
}
