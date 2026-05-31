#include "matching.h"
extern int D_007097F0[];

/*
 * GCC explicit-register vars below are NOT inline asm — they're regalloc
 * directives. ee-gcc 2.9-991111 otherwise reuses $a0 for the addu result
 * and folds the +0x14 offset into the lui+addiu. The pins force stride to
 * $v0, base to $v1, mult result to $a0, leaving the lw to use the +0x14
 * offset against the base in $v1. The original encodes the base+offset add
 * as `addu $3, $3, $4` (rd==rs); ee-gcc canonicalizes the pointer add to
 * rd==rt, so ADDU_RS forces the operand order and computing the mult before
 * the base keeps mult ahead of the %lo addiu — matching WITHOUT the
 * swap_addu postprocess (COOKBOOK §8.11).
 */
int func_001E8D30(int idx)
{
    register int s = 0x18;
    register int prod = idx * s;
    register int *b = D_007097F0;
    ADDU_RS(b, prod);
    return *(int *)((char *)b + 0x14);
}
