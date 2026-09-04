/* fill_inbuf (ios/iosCdvdBackGroundMgrInit.c) — iosCdvdBackGroundMgrInit read-fill loop: repeatedly call the
 * read fn ptr (base+4) to fill base+0x10008, accumulating into w[0x4C] until
 * the read returns 0/-1 or the count exceeds 0x7FFF.
 *
 * STATUS: 28 diffs (from 40). MATCHED so far: base->s0 / window->s1 regalloc
 * (pin $16/$17), the whole call-arg setup, and the len arg zero-ext (len param
 * = unsigned long long + pass (unsigned)(0x8000-cur) -> dsll32/dsrl32).
 * REMAINING (permuter targets — NO packed read here, so permuter is viable):
 *   - loop LAYOUT: original rotates to accumulate-first with an initial
 *     `b .L30` skip to the shared call block; ee-gcc gives call-first for every
 *     while/for/goto form I tried (goto breaks LICM -> 46).
 *   - ret SIGN-EXT: original `dsll32 v1,v0,0; dsra32 v1,v1,0; addiu v0,v1,1`;
 *     mine `daddu a0,v0,zero; addiu v0,a0,1` (no canonicalize of the int ret).
 *   - epilogue RECOMPUTES window = base+0x18000 (lui+ori+addu) instead of s1.
 *   - prologue reg SAVE order (s2 vs s1).
 */
#include "matching.h"

typedef int (*read_fn_00135AD8)(void *buf, unsigned long long len, int arg);

int fill_inbuf(unsigned char *a0)
{
    register unsigned char *base REG("$16") = a0;
    register int *w REG("$17") = (int *)(base + 0x18000);
    int ret;
    int cur;
    w[0x4C / 4] = 0;
    while (1)
    {
        cur = w[0x4C / 4];
        ret = (*(read_fn_00135AD8 *)(base + 4))(
            base + 0x10008 + cur, (unsigned int) (0x8000 - cur), *(int *) base);
        if (ret == 0 || ret == -1)
        {
            break;
        }
        cur = w[0x4C / 4] + ret;
        w[0x4C / 4] = cur;
        if ((unsigned int) cur > 0x7FFF)
        {
            break;
        }
    }
    if (w[0x4C / 4] == 0)
    {
        return -1;
    }
    w[0x50 / 4] = 1;
    return base[0x10008];
}
