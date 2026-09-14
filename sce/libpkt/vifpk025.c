/* libpkt.a member vifpk025.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

typedef unsigned int u128_241778 __attribute__((mode(TI)));

typedef struct {
    int *end;
    int pad[2];
    int *cur;
} Pool241748;

void sceVif1PkInit(int *a0, int a1)
{
    a0[1] = a1;
    a0[0] = a1;
    a0[2] = 0;
}

extern void sceVif1PkAlign(void *a0, int a1, int a2);
