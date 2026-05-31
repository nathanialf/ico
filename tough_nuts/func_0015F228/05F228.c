#include "matching.h"
extern int D_00292540[];

/*
 * GCC explicit-register vars below are regalloc directives (see 0E8D30.c).
 * The original encodes the base+offset add as `addu $2, $2, $4` (rd in the
 * rs slot); ee-gcc 2.9 canonicalizes the pointer add to `addu $2, $4, $2`
 * (rd==rt). ADDU_RS forces the original's commutative operand order in C,
 * so this matches WITHOUT the swap_addu postprocess (COOKBOOK §8.11).
 */
void func_0015F228(int idx, int val)
{
    register int s = 0x18;
    register int prod = idx * s;
    register int *b = D_00292540;
    ADDU_RS(b, prod);
    *(int *)((char *)b + 8) = val;
}
