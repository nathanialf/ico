#include "matching.h"
extern char D_00717764[];
extern char D_0071776C[];

/* See 14BBC0.c: ADDU_RS forces the original's rd==rs `addu $3, $3, $4`
 * operand order, dropping the swap_addu postprocess (COOKBOOK §8.11). */
void func_0024BBF0(int a0)
{
    register int idx_off;
    register char *base REG("$4");
    idx_off = a0 * 8;
    if (a0 < 0) {
        base = *(char **)D_00717764;
    } else {
        base = *(char **)D_0071776C;
    }
    ADDU_RS(idx_off, base);              /* addu $3, $3, $4 */
    *(int *)(char *)idx_off = 0;
}
