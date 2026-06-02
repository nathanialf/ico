#include "matching.h"
#include "regpin.h"

extern int D_004C7710[];

/* The packet's 64-bit tag word overlaps the int cells the ring pointers also
 * address, so the store must may-alias those int writes (else gcc DSEs the
 * earlier base[4]=p+6 update). A union spells that alias out in the type system
 * — and still lowers to a single `sd` — instead of a per-file -fno-strict-aliasing. */
typedef union { int w[2]; long long d; } DmaTag;

void func_0010F710(void)
{
    register int *base = D_004C7710;
    register int *p = (int *)base[4];
    base[6] = 0;
    base[7] = 0;
    base[4] = (int)(p + 2);
    base[3] = (int)p;
    base[5] = (int)p;
    p[2] = 0x11000000;
    base[6] = (int)(p + 3);
    base[7] = (int)(p + 4);
    base[4] = (int)(p + 6);
    ((DmaTag *)(p + 6))->d = 0xE;
    base[4] = (int)(p + 8);
}
