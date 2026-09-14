/* libpkt.a member vifpk041.o.  MAIN.MAP member spans tile this run exactly and
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

extern void sceVif1PkAlign(void *a0, int a1, int a2);

void sceVif1PkOpenGifTag(void *a0, u128_241778 a1)
{
    void **pp = (void **)a0;
    void *p = *pp;
    *(u128_241778 *)p = a1;
    *(void **)((char *)a0 + 0x14) = p;
    *pp = (char *)p + 0x10;
}
