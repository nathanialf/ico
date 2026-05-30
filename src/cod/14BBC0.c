#include "matching.h"
extern char D_00717764[];
extern char D_0071776C[];

/*
 * The original encodes the base+offset add as `addu $3, $3, $4` (rd==rs);
 * ee-gcc 2.9 canonicalizes `base + idx_off` to rd==rt. ADDU_RS forces the
 * operand order — folding the sum into idx_off's reg ($3) — so this matches
 * WITHOUT the swap_addu postprocess (COOKBOOK §8.11).
 */
void func_0024BBC0(int a0, int a1, int a2)
{
    register int idx_off REG("$3");
    register char *base REG("$4");
    char *p;
    idx_off = a0 * 8;
    if (a0 < 0) {
        base = *(char **)D_00717764;
    } else {
        base = *(char **)D_0071776C;
    }
    ADDU_RS(idx_off, base);              /* addu $3, $3, $4 */
    p = (char *)idx_off;
    *(int *)p = a1;                      /* swap order in C */
    *(int *)(p + 4) = a2;
}
