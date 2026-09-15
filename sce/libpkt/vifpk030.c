/* libpkt.a member vifpk030.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef unsigned int u128_241778 __attribute__((mode(TI)));

typedef struct {
    int *end;
    int pad[2];
    int *cur;
} Pool241748;

extern int *sceVif1PkTerminate(void *a0);

void sceVif1PkCnt(void *a0, int a1)
{
    int *p;
    *(int **)((char *)a0 + 8) = sceVif1PkTerminate(a0);
    p = *(int **)a0;
    *p++ = a1 | 0x10000000;
    *(int *)((char *)a0 + 0xC) = 0;
    *(int **)a0 = p + 1;
    *p = 0;
}
