#include "matching.h"
extern int D_0070D4D8[];

/*
 * GCC explicit-register vars below are regalloc directives (see 0E8D30.c).
 * The original encodes the base+offset add as `addu $2, $2, $4` (rd in the
 * rs slot); ee-gcc 2.9 canonicalizes the pointer add to `addu $2, $4, $2`
 * (rd==rt). ADDU_RS forces the original's commutative operand order, and
 * computing the mult before materializing the base keeps mult ahead of the
 * %lo addiu — matching WITHOUT the swap_addu postprocess (COOKBOOK §8.11).
 */
void func_001F1148(int idx, int val)
{
    register int s = 0x18;
    register int prod = idx * s;
    register int *b = D_0070D4D8;
    ADDU_RS(b, prod);
    *(int *)((char *)b + 0x14) = val;
}
